#include "JHMG engine.h"
using namespace JHMG_ENGINE;
Game* mainGame;
GameSound* bgm;
GameSound* hit;
IMAGE* p1;
IMAGE* p2;
IMAGE* e1;
IMAGE* e2;

void sceneAwake();
void playerUpdate(GameObject* self);
void playerRevive();
void PbulletUpdate(GameObject* self);
void onTriggleEnter_Pbullet(GameObject* self,GameObject* other);
void onTriggleEnter_Ebullet(GameObject* self, GameObject* other);
void sceneUpdate();
void createEnemy();
void EbulletUpdate(GameObject* self);
void enemyUpdate(GameObject* self);
int score = 100;

int main()
{
	mainGame = new Game;
	mainGame->setWindowSize(Vector2(800, 600));
	mainGame->setWindowTitle("飞机大战");
	mainGame->setTargetFrame(60);
	GameScene* scene = new GameScene;
	scene->setAwakeFunc(sceneAwake);
	mainGame->setScene(scene);
	mainGame->initWindow();

}

//场景初始化
void sceneAwake()
{
	//加载图片
	p1 = new IMAGE;
	loadimage(p1, ".\\res\\plane1.png", 85, 85, true);
	p2 = new IMAGE;
	loadimage(p2, ".\\res\\plane2.png", 85, 85, true);
	e1 = new IMAGE;
	loadimage(e1, ".\\res\\bullet1.png", 10, 10, true);
	e2 = new IMAGE;
	loadimage(e2, ".\\res\\bullet2.png", 14, 14, true);

	//生成背景
	GameUI* bg = new GameUI(Vector2(0, 0), Vector2(800, 600), ".\\res\\bg.png", true);
	mainGame->getScene()->addGameUI("bg", bg);
	GameUIText* tips = new GameUIText("Move:WASD Fight:space", Vector2(mainGame->getWindowSize().x - 250, mainGame->getWindowSize().y - 20), RGB(255, 147, 0), Vector2(0, 20), true);
	mainGame->getScene()->addGameUIText("tips", tips);
	//生成角色
	playerRevive();
	//生成敌人
	createEnemy();
	//生成分数
	GameUIText* scoreText = new GameUIText("", Vector2(10, 10), RGB(255, 147, 0), Vector2(0, 30), true);
	mainGame->getScene()->addGameUIText("score", scoreText);
	mainGame->getScene()->setGameLoopFunc(sceneUpdate);
	//生成背景音乐
	bgm = new GameSound;
	bgm->open("bgm", ".\\res\\bgm.mp3");
	bgm->play(1);
	bgm->setVolume(300);
	//生成碰撞音效
	hit = new GameSound;
	hit->open("hit", ".\\res\\bom.mp3");
	hit->setVolume(500);
}

//生成敌人
void createEnemy()
{
	//产生随机x坐标
	srand(time(NULL) * rand());
	int x = rand() % 800;
	while (x < 50 || x>750)
	{
		srand(time(NULL) * rand());
		x = rand() % 800;
	}
	GameObject* enemy = new GameObject(new Circle(45, Vector2(x, 50)),p2, true);
	enemy->tag = String("enemy");
	enemy->setGameLoopFunc(enemyUpdate);
	mainGame->getScene()->addGameObject("enemy", enemy);
}

//场景更新
void sceneUpdate()
{
	if (GetHWnd() == NULL)
	{
		exit(0);
	}
	GameUIText* scoreText = mainGame->getScene()->getGameUIText("score");
	scoreText->text = ("分数:" + std::to_string(score));
	if (score < 0)
	{
		GameMessageBox("warning", "游戏结束！").show();
		exit(0);
	}
}

//角色更新
void playerUpdate(GameObject* self)
{
	GameObject* player = mainGame->getScene()->getGameObject("player");
	int key = mainGame->input.getKey();
	Vector2 currentPos = player->Transform.Circle->getPosition();
	if (key == KeyMessage::a)
	{
		if(currentPos.x>0)
		player->Transform.Circle->move(Vector2(-5, 0) + currentPos);
	}
	if (key == KeyMessage::d)
	{
		if(currentPos.x < 800)
		player->Transform.Circle->move(Vector2(5, 0) + currentPos);
	}
	if (key == KeyMessage::w)
	{
		if(currentPos.y>0)
		player->Transform.Circle->move(Vector2(0, -5) + currentPos);
	}
	if (key == KeyMessage::s)
	{
		if (currentPos.y<600)
		player->Transform.Circle->move(Vector2(0, 5) + currentPos);
	}
	if (key == KeyMessage::space)
	{
		static clock_t time1 = clock();
		if (clock() - time1 > 300)
		{
			GameObject* bullet = new GameObject(new Circle(15, Vector2(currentPos - Vector2(-8, 60))),e1, true);
			//产生随机名字
			srand(time(NULL));
			String name = "Pbullet" + std::to_string(rand());
			while (mainGame->getScene()->getGameObject(name) != NULL)
			{
				srand(time(NULL) * rand());
				name = "Pbullet" + std::to_string(rand());
			}
			bullet->setOnCollision(onTriggleEnter_Pbullet);
			bullet->tag = String("Pbullet");
			mainGame->getScene()->addGameObject(name, bullet);
			bullet->setGameLoopFunc(PbulletUpdate);
			time1 = clock();
		}
	}

}
//玩家子弹更新
void PbulletUpdate(GameObject* self)
{
	GameObject* bullet = self;
	bullet->Transform.Circle->move(Vector2(0, -5) + bullet->Transform.Circle->getPosition());
	if (bullet->Transform.Circle->getPosition().y < -10)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}
//玩家子弹碰撞
void onTriggleEnter_Pbullet(GameObject* self, GameObject* other)
{
	if (other->tag == String("enemy"))
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(self));
		hit->play(0);
		createEnemy();
		score += 10;
	}
}
//敌人更新
void enemyUpdate(GameObject* self)
{
	static float speed = 1;
	GameObject* enemy = self;
	GameObject* player = mainGame->getScene()->getGameObject("player");
	if (player == NULL)
	{
		return;
	}
	Vector2 EcurrentPos = enemy->Transform.Circle->getPosition();
	Vector2 PcurrentPos = player->Transform.Circle->getPosition();
	if (EcurrentPos.x > PcurrentPos.x)
	{
		enemy->Transform.Circle->move(Vector2(-speed, 0) + EcurrentPos);
	}
	if (EcurrentPos.x < PcurrentPos.x)
	{
		enemy->Transform.Circle->move(Vector2(speed, 0) + EcurrentPos);
	}
	if (abs(EcurrentPos.x - PcurrentPos.x) < 20)
	{
		static int time1 = clock();
		if (clock() - time1 > 800)
		{
			GameObject* bullet = new GameObject(new Circle(15, Vector2(EcurrentPos + Vector2(0, 60))), e2, true);
			//产生随机名字
			srand(time(NULL) * rand());
			String name = "Ebullet" + std::to_string(rand());
			while (mainGame->getScene()->getGameObject(name) != NULL)
			{
				srand(time(NULL) * rand());
				name = "Ebullet" + std::to_string(rand());
			}
			bullet->setOnCollision(onTriggleEnter_Ebullet);
			bullet->tag = String("Ebullet");
			mainGame->getScene()->addGameObject(name, bullet);
			bullet->setGameLoopFunc(EbulletUpdate);
			time1 = clock();
		}
	}

}
//敌人子弹更新
void EbulletUpdate(GameObject* self)
{
	GameObject* bullet = self;
	bullet->Transform.Circle->move(Vector2(0, 5) + bullet->Transform.Circle->getPosition());
	if (bullet->Transform.Circle->getPosition().y > 610)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}
//敌人子弹碰撞
void onTriggleEnter_Ebullet(GameObject* self, GameObject* other)
{
	if (other->tag == String("player"))
	{
		score -= 25;
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(self));
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		hit->play(0);
		playerRevive();
	}
}

//角色复活
void playerRevive()
{
	//产生随机x坐标
	srand(time(NULL) * rand());
	int x = rand() % 800;

	GameObject* player = new GameObject(new Circle(45, Vector2(x, 500)), p1, true);
	player->setGameLoopFunc(playerUpdate);
	player->tag = String("player");
	mainGame->getScene()->addGameObject("player", player);
}