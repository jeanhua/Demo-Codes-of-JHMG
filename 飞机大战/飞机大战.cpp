#include "JHMG engine.h"

Game* mainGame;
void sceneAwake();
void playerUpdate(gameObject* self);
void playerRevive();
void PbulletUpdate(gameObject* self);
void onTriggleEnter_Pbullet(gameObject* self,gameObject* other);
void onTriggleEnter_Ebullet(gameObject* self, gameObject* other);
void sceneUpdate();
void createEnemy();
void EbulletUpdate(gameObject* self);
void enemyUpdate(gameObject* self);
int score = 0;

int main()
{
	mainGame = new Game;
	mainGame->setWindowSize(jhVector2(800, 600));
	mainGame->setWindowTitle("�ɻ���ս");
	mainGame->setTargetFrame(60);
	gameScene* scene = new gameScene;
	scene->setAwakeFunc(sceneAwake);
	mainGame->setScene(scene);
	mainGame->initWindow();

}

//������ʼ��
void sceneAwake()
{
	//���ɱ���
	gameUI* bg = new gameUI(jhVector2(0, 0), jhVector2(800, 600), ".\\res\\bg.png", true);
	mainGame->getScene()->addGameUI("bg", bg);
	//���ɽ�ɫ
	playerRevive();
	//���ɵ���
	createEnemy();
	//���ɷ���
	gameUIText* scoreText = new gameUIText("", jhVector2(10, 10), RGB(255, 147, 0), jhVector2(0, 30), true);
	mainGame->getScene()->addGameUIText("score", scoreText);
	mainGame->getScene()->setGameLoopFunc(sceneUpdate);
	//���ɱ�������
	mainGame->Sound.setSound(".\\res\\bgm.mp3");
	mainGame->Sound.play(1);
	mainGame->Sound.setVolume(100);
}

//���ɵ���
void createEnemy()
{
	//�������x����
	srand(time(NULL) * rand());
	int x = rand() % 800;

	gameObject* enemy = new gameObject(new jhObject2D::circle(45, jhVector2(x, 50)), ".\\res\\plane2.png", 85, 85, true);
	enemy->tag = jhString("enemy");
	enemy->setGameLoopFunc(enemyUpdate);
	mainGame->getScene()->addGameObject("enemy", enemy);
}

//��������
void sceneUpdate()
{
	gameUIText* scoreText = mainGame->getScene()->getGameUIText("score");
	scoreText->text = ("����:" + to_string(score));
	if (score < 0)
	{
		gameMessageBox("warning", "��Ϸ������").show();
		exit(0);
	}
}

//��ɫ����
void playerUpdate(gameObject* self)
{
	gameObject* player = mainGame->getScene()->getGameObject("player");
	int key = mainGame->Input.getKey();
	jhVector2 currentPos = player->transform.circle->getPosition();
	if (key == KeyMessage::a)
	{
		if(currentPos.x>0)
		player->transform.circle->move(jhVector2(-5, 0) + currentPos);
	}
	if (key == KeyMessage::d)
	{
		if(currentPos.x < 800)
		player->transform.circle->move(jhVector2(5, 0) + currentPos);
	}
	if (key == KeyMessage::w)
	{
		if(currentPos.y>0)
		player->transform.circle->move(jhVector2(0, -5) + currentPos);
	}
	if (key == KeyMessage::s)
	{
		if (currentPos.y<600)
		player->transform.circle->move(jhVector2(0, 5) + currentPos);
	}
	if (key == KeyMessage::space)
	{
		static clock_t time1 = clock();
		if (clock() - time1 > 300)
		{
			gameObject* bullet = new gameObject(new jhObject2D::circle(15, jhVector2(currentPos - jhVector2(-8, 60))), ".\\res\\bullet1.png", 10, 10, true);
			//�����������
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
			time1 = clock();
		}
	}

}
//����ӵ�����
void PbulletUpdate(gameObject* self)
{
	gameObject* bullet = self;
	bullet->transform.circle->move(jhVector2(0, -5) + bullet->transform.circle->getPosition());
	if (bullet->transform.circle->getPosition().y < -10)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}
//����ӵ���ײ
void onTriggleEnter_Pbullet(gameObject* self, gameObject* other)
{
	if (other->tag == jhString("enemy"))
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(self));
		createEnemy();
		score += 10;
	}
}
//���˸���
void enemyUpdate(gameObject* self)
{
	gameObject* enemy = self;
	gameObject* player = mainGame->getScene()->getGameObject("player");
	if (player == NULL)
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
			gameObject* bullet = new gameObject(new jhObject2D::circle(15, jhVector2(EcurrentPos + jhVector2(0, 60))), ".\\res\\bullet2.png", 14, 14, true);
			//�����������
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
//�����ӵ�����
void EbulletUpdate(gameObject* self)
{
	gameObject* bullet = self;
	bullet->transform.circle->move(jhVector2(0, 5) + bullet->transform.circle->getPosition());
	if (bullet->transform.circle->getPosition().y > 610)
	{
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(bullet));
	}
}
//�����ӵ���ײ
void onTriggleEnter_Ebullet(gameObject* self, gameObject* other)
{
	if (other->tag == jhString("player"))
	{
		score -= 10;
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(self));
		mainGame->getScene()->removeGameObject(mainGame->getScene()->getName(other));
		playerRevive();
	}
}

//��ɫ����
void playerRevive()
{
	//�������x����
	srand(time(NULL) * rand());
	int x = rand() % 800;

	gameObject* player = new gameObject(new jhObject2D::circle(45, jhVector2(x, 500)), ".\\res\\plane1.png", 85, 85, true);
	player->setGameLoopFunc(playerUpdate);
	player->tag = jhString("player");
	mainGame->getScene()->addGameObject("player", player);
}