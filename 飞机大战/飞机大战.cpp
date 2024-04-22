#include "JHMG engine.h"

Game* mainGame;
gameSound* sound;
void sceneAwake();
void playerUpdate(gameObject* self);
void playerRevive();
void PbulletUpdate(gameObject* self);
void onTriggleEnter_Pbullet(gameObject* other);
void onTriggleEnter_Ebullet(gameObject* other);
void sceneUpdate();
void createEnemy();
void EbulletUpdate(gameObject* self);
void enemyUpdate(gameObject* self);
int score = 0;

int main()
{
	mainGame = new Game;
	mainGame->setWindowSize(jhVector2(800, 600));
	mainGame->setWindowTitle("飞机大战");
	mainGame->setTargetFrame(60);
	gameScene* scene = new gameScene;
	scene->setAwakeFunc(sceneAwake);
	mainGame->setScene(scene);
	mainGame->initWindow();

}

void sceneAwake()
{
	//生成背景
	gameUI* bg = new gameUI(jhVector2(0, 0), jhVector2(800, 600), ".\\res\\bg.png", true);
	mainGame->getScene()->addGameUI("bg", bg);
	//生成角色
	playerRevive();
	//生成敌人
	createEnemy();
	//生成分数
	gameUIText* scoreText = new gameUIText("", jhVector2(10, 10), RGB(255, 147, 0), jhVector2(0, 30), true);
	mainGame->getScene()->addGameUIText("score", scoreText);
	mainGame->getScene()->setGameLoopFunc(sceneUpdate);
	//生成背景音乐
	sound = new gameSound();
	sound->setSound(".\\res\\bgm.mp3");
	sound->play(1);
}

void createEnemy()
{
	//产生随机x坐标
	srand(time(NULL) * rand());
	int x = rand() % 800;
	cout << x << endl;

	gameObject* enemy = new gameObject(new jhObject2D::circle(45, jhVector2(x, 50)), ".\\res\\plane2.png", 85, 85, true);
	enemy->tag = jhString("enemy");
	enemy->setGameLoopFunc(enemyUpdate);
	mainGame->getScene()->addGameObject("enemy", enemy);
}

void sceneUpdate()
{
	gameUIText* scoreText = mainGame->getScene()->getGameUIText("score");
	scoreText->text = ("分数:" + to_string(score));
	if (score < 0)
	{
		gameMessageBox("warning","游戏结束！").show();
		exit(0);
	}
}

void playerUpdate(gameObject* self)
{
	gameObject* player = mainGame->getScene()->getGameObject("player");
	int key = mainGame->Input.getKey();
	jhVector2 currentPos = player->transform.circle->getPosition();
	if (key == KeyMessage::a)
	{
		player->transform.circle->move(jhVector2(-5, 0) + currentPos);
	}
	if (key == KeyMessage::d)
	{
		player->transform.circle->move(jhVector2(5, 0) + currentPos);
	}
	if (key == KeyMessage::w)
	{
		player->transform.circle->move(jhVector2(0, -5) + currentPos);
	}
	if (key == KeyMessage::s)
	{
		player->transform.circle->move(jhVector2(0, 5) + currentPos);
	}
	if (key == KeyMessage::space)
	{
		gameObject* bullet = new gameObject(new jhObject2D::circle(15, jhVector2(currentPos - jhVector2(-8, 60))), ".\\res\\bullet1.png", 10, 10, true);
		//产生随机名字
		srand(time(NULL));
		string name = "Pbullet" + to_string(rand());
		while (mainGame->getScene()->getGameObject(name) != NULL)
		{
			srand(time(NULL) * rand());
			name = "Pbullet" + to_string(rand());
		}
		bullet->setOnCollision(onTriggleEnter_Pbullet);
		bullet->tag = jhString("Pbullet");
		mainGame->getScene()->addGameObject(name, bullet);
		bullet->setGameLoopFunc(PbulletUpdate);
	}

}

void PbulletUpdate(gameObject* self)
{
	gameObject* bullet = self;
	bullet->transform.circle->move(jhVector2(0, -5) + bullet->transform.circle->getPosition());
	if (bullet->transform.circle->getPosition().y < -10)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}

void onTriggleEnter_Pbullet(gameObject* other)
{
	if (other->tag == jhString("enemy"))
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		createEnemy();
		score += 10;
	}
}

void enemyUpdate(gameObject* self)
{
	gameObject* enemy = self;
	gameObject* player = mainGame->getScene()->getGameObject("player");
	if(player==NULL)
	{
		return;
	}
	jhVector2 EcurrentPos = enemy->transform.circle->getPosition();
	jhVector2 PcurrentPos = player->transform.circle->getPosition();
	if (EcurrentPos.x > PcurrentPos.x)
	{
		enemy->transform.circle->move(jhVector2(-1, 0) + EcurrentPos);
	}
	if (EcurrentPos.x < PcurrentPos.x)
	{
		enemy->transform.circle->move(jhVector2(1, 0) + EcurrentPos);
	}
	if (abs(EcurrentPos.x - PcurrentPos.x) < 20)
	{
		static int time1 = clock();
		if (clock() - time1 > 800)
		{
			gameObject* bullet = new gameObject(new jhObject2D::circle(15, jhVector2(EcurrentPos + jhVector2(0, 60))), ".\\res\\bullet2.png", 10, 10, true);
			//产生随机名字
			srand(time(NULL) * rand());
			string name = "Ebullet" + to_string(rand());
			while (mainGame->getScene()->getGameObject(name) != NULL)
			{
				srand(time(NULL) * rand());
				name = "Ebullet" + to_string(rand());
			}
			bullet->setOnCollision(onTriggleEnter_Ebullet);
			bullet->tag = jhString("Ebullet");
			mainGame->getScene()->addGameObject(name, bullet);
			bullet->setGameLoopFunc(EbulletUpdate);
			time1 = clock();
		}
	}

}

void EbulletUpdate(gameObject* self)
{
	gameObject* bullet = self;
	bullet->transform.circle->move(jhVector2(0, 5) + bullet->transform.circle->getPosition());
	if (bullet->transform.circle->getPosition().y > 610)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}

void onTriggleEnter_Ebullet(gameObject* other)
{
	if (other->tag == jhString("player"))
	{
		score-= 10;
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		playerRevive();
	}
}

//角色复活
void playerRevive()
{
	//产生随机x坐标
	srand(time(NULL) * rand());
	int x = rand() % 800;

	gameObject* player = new gameObject(new jhObject2D::circle(45, jhVector2(x, 500)), ".\\res\\plane1.png", 85, 85, true);
	player->setGameLoopFunc(playerUpdate);
	player->tag = jhString("player");
	mainGame->getScene()->addGameObject("player", player);
}