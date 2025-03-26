#include "JHMG engine.h"
using namespace JHMG_ENGINE;
Game* mainGame;

void awake()
{
	// �����������͸��
	setbkmode(TRANSPARENT);
	// ���ñ�����ɫ
	setbkcolor(RGB(136, 85, 85));
}

static float a1 = 0;
static float b1 = 0;
static int status = 0;

// ��ť����¼�
void onClick(int mouseMessage, Vector2 position, GameUI* self);

int main()
{
	// ������Ϸ
	mainGame = new Game;
	// ���ô��ڴ�С
	mainGame->setWindowSize(Vector2(300, 500));
	// ���ô��ڱ���
	mainGame->setWindowTitle("������");
	// ��������
	GameScene* scene = new GameScene;
	// ���ó���
	mainGame->setScene(scene);
	// ���ó������Ѻ���
	scene->setAwakeFunc(awake);

	// �������ְ�ť
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// ����λ��
			Vector2 pos = Vector2(30 + 60 * j, 250 + 60 * i);
			// ���ɰ�ť
			GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
			// ���ɰ�ť����
			GameUIText* text = new GameUIText(std::to_string(i * 3 + j + 1), pos + Vector2(5, 5),WHITE,Vector2(0,25),true);
			// ���ð�ť����¼�
			button->mouseAction->setClickFunc(onClick);
			// ��Ӱ�ť������
			scene->addGameUI("button" + std::to_string(i * 3 + j), button);
			// ��Ӱ�ť���ֵ�����
			scene->addGameUIText(std::to_string(i * 3 + j), text);
		}
	}

	//����0��ť
	Vector2 pos = Vector2(90, 430);
	//���ɰ�ť
	GameUI* button_0 = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	GameUIText* text_0 = new GameUIText("0", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
	//���ð�ť����¼�
	button_0->mouseAction->setClickFunc(onClick);
	//��Ӱ�ť������
	scene->addGameUI("button9", button_0);
	//��Ӱ�ť���ֵ�����
	scene->addGameUIText("t0", text_0);

	//���ɼӼ��˳���ť
	for (int i = 0; i < 4; i++)
	{
		// ���ɷ���
		const char* con[] = { "+", "-", "��", "��" };
		// ����λ��
		Vector2 pos = Vector2(230, 250 + 60 * i);
		// ���ɰ�ť
		GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
		// ���ɰ�ť����
		GameUIText* text = new GameUIText(con[i], pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
		// ���ð�ť����¼�
		button->mouseAction->setClickFunc(onClick);
		// ��Ӱ�ť������
		scene->addGameUI("control" + std::to_string(i), button);
		// ��Ӱ�ť���ֵ�����
		scene->addGameUIText(con[i], text);

	}
	//���ɵȺŰ�ť
	pos = Vector2(150, 430);
	//���ɰ�ť
	GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	GameUIText* text = new GameUIText("=", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
	//���ð�ť����¼�
	button->mouseAction->setClickFunc(onClick);
	//��Ӱ�ť������
	scene->addGameUI("control4", button);
	//��Ӱ�ť���ֵ�����
	scene->addGameUIText("=", text);

	//�������㰴ť
	
	//����λ��
	pos = Vector2(30, 430);
	//���ɰ�ť
	GameUI* button0 = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	GameUIText* text0 = new GameUIText("C", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
	//���ð�ť����¼�
	button0->mouseAction->setClickFunc(onClick);
	//��Ӱ�ť������
	scene->addGameUI("control5", button0);
	//��Ӱ�ť���ֵ�����
	scene->addGameUIText("C", text0);

	//������ʾ��
	//����λ��
	pos = Vector2(30, 80);
	//������ʾ���ı�
	GameUIText* text1 = new GameUIText("", pos,BLACK,Vector2(0,25), true);
	//�����ʾ�򵽳���
	scene->addGameUIText("���", text1);

	// ��ʼ�����ڿ�ʼ��Ϸѭ��
	mainGame->initWindow();
}

void onClick(int mouseMessage, Vector2 position, GameUI* self)
{
	if (mouseMessage == MouseMessage::leftDown)
	{
		String name = mainGame->getScene()->getName(self);
		if (name == "button0")
		{
			b1 = b1 * 10 + 1;
		}
		if (name == "button1")
		{
			b1 = b1 * 10 + 2;
		}
		if (name == "button2")
		{
			b1 = b1 * 10 + 3;
		}
		if (name == "button3")
		{
			b1 = b1 * 10 + 4;
		}
		if (name == "button4")
		{
			b1 = b1 * 10 + 5;
		}
		if (name == "button5")
		{
			b1 = b1 * 10 + 6;
		}
		if (name == "button6")
		{
			b1 = b1 * 10 + 7;
		}
		if (name == "button7")
		{
			b1 = b1 * 10 + 8;
		}
		if (name == "button8")
		{
			b1 = b1 * 10 + 9;
		}
		if (name == "button9")
		{
			b1 = b1 * 10;
		}
		if (name == "control0")
		{
			status = 0;
			a1 = b1;
			b1 = 0;
		}
		if (name == "control1")
		{
			status = 1;
			a1 = b1;
			b1 = 0;
		}
		if (name == "control2")
		{
			status = 2;
			a1 = b1;
			b1 = 0;
		}
		if (name == "control3")
		{
			status = 3;
			a1 = b1;
			b1 = 0;
		}
		if (name == "control4")
		{
			if (status == 0)
			{
				b1 = a1 + b1;
			}
			if (status == 1)
			{
				b1 = a1 - b1;
			}
			if (status == 2)
			{
				b1 = a1 * b1;
			}
			if (status == 3)
			{
				if (b1 != 0)
				b1 = a1 / b1;
				else
				{
					b1 = 0;
				}
			}
		}
		if (name == "control5")
		{
			b1 = 0;
			a1 = 0;
		}
		// ��ʾ���
		mainGame->getScene()->getGameUIText("���")->text = std::to_string(b1);
	}
}