#include "JHMG engine.h"

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
void onClick(int mouseMessage, jhVector2 position, gameUI* self);

int main()
{
	// ������Ϸ
	mainGame = new Game;
	// ���ô��ڴ�С
	mainGame->setWindowSize(jhVector2(300, 500));
	// ���ô��ڱ���
	mainGame->setWindowTitle("������");
	// ��������
	gameScene* scene = new gameScene;
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
			jhVector2 pos = jhVector2(30 + 60 * j, 250 + 60 * i);
			// ���ɰ�ť
			gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
			// ���ɰ�ť����
			gameUIText* text = new gameUIText(to_string(i * 3 + j + 1), pos + jhVector2(5, 5),WHITE,jhVector2(0,25),true);
			// ���ð�ť����¼�
			button->mouseAction->setClickFunc(onClick);
			// ��Ӱ�ť������
			scene->addGameUI("button" + to_string(i * 3 + j), button);
			// ��Ӱ�ť���ֵ�����
			scene->addGameUIText(to_string(i * 3 + j), text);
		}
	}

	//����0��ť
	jhVector2 pos = jhVector2(90, 430);
	//���ɰ�ť
	gameUI* button_0 = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	gameUIText* text_0 = new gameUIText("0", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
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
		jhVector2 pos = jhVector2(230, 250 + 60 * i);
		// ���ɰ�ť
		gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
		// ���ɰ�ť����
		gameUIText* text = new gameUIText(con[i], pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
		// ���ð�ť����¼�
		button->mouseAction->setClickFunc(onClick);
		// ��Ӱ�ť������
		scene->addGameUI("control" + to_string(i), button);
		// ��Ӱ�ť���ֵ�����
		scene->addGameUIText(con[i], text);

	}
	//���ɵȺŰ�ť
	pos = jhVector2(150, 430);
	//���ɰ�ť
	gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	gameUIText* text = new gameUIText("=", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
	//���ð�ť����¼�
	button->mouseAction->setClickFunc(onClick);
	//��Ӱ�ť������
	scene->addGameUI("control4", button);
	//��Ӱ�ť���ֵ�����
	scene->addGameUIText("=", text);

	//�������㰴ť
	
	//����λ��
	pos = jhVector2(30, 430);
	//���ɰ�ť
	gameUI* button0 = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//���ɰ�ť����
	gameUIText* text0 = new gameUIText("C", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
	//���ð�ť����¼�
	button0->mouseAction->setClickFunc(onClick);
	//��Ӱ�ť������
	scene->addGameUI("control5", button0);
	//��Ӱ�ť���ֵ�����
	scene->addGameUIText("C", text0);

	//������ʾ��
	//����λ��
	pos = jhVector2(30, 80);
	//������ʾ���ı�
	gameUIText* text1 = new gameUIText("", pos,BLACK,jhVector2(0,25), true);
	//�����ʾ�򵽳���
	scene->addGameUIText("���", text1);

	// ��ʼ�����ڿ�ʼ��Ϸѭ��
	mainGame->initWindow();
}

void onClick(int mouseMessage, jhVector2 position, gameUI* self)
{
	if (mouseMessage == MouseMessage::leftDown)
	{
		jhString name = mainGame->getScene()->getName(self);
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
		mainGame->getScene()->getGameUIText("���")->text = to_string(b1);
	}
}