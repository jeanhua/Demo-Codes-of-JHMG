#include "JHMG engine.h"

Game* mainGame;

void awake()
{
	// 设置字体填充透明
	setbkmode(TRANSPARENT);
	// 设置背景颜色
	setbkcolor(RGB(136, 85, 85));
}

static float a1 = 0;
static float b1 = 0;
static int status = 0;

// 按钮点击事件
void onClick(int mouseMessage, jhVector2 position, gameUI* self);

int main()
{
	// 创建游戏
	mainGame = new Game;
	// 设置窗口大小
	mainGame->setWindowSize(jhVector2(300, 500));
	// 设置窗口标题
	mainGame->setWindowTitle("计算器");
	// 创建场景
	gameScene* scene = new gameScene;
	// 设置场景
	mainGame->setScene(scene);
	// 设置场景唤醒函数
	scene->setAwakeFunc(awake);

	// 生成数字按钮
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 生成位置
			jhVector2 pos = jhVector2(30 + 60 * j, 250 + 60 * i);
			// 生成按钮
			gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
			// 生成按钮文字
			gameUIText* text = new gameUIText(to_string(i * 3 + j + 1), pos + jhVector2(5, 5),WHITE,jhVector2(0,25),true);
			// 设置按钮点击事件
			button->mouseAction->setClickFunc(onClick);
			// 添加按钮到场景
			scene->addGameUI("button" + to_string(i * 3 + j), button);
			// 添加按钮文字到场景
			scene->addGameUIText(to_string(i * 3 + j), text);
		}
	}

	//生成0按钮
	jhVector2 pos = jhVector2(90, 430);
	//生成按钮
	gameUI* button_0 = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//生成按钮文字
	gameUIText* text_0 = new gameUIText("0", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
	//设置按钮点击事件
	button_0->mouseAction->setClickFunc(onClick);
	//添加按钮到场景
	scene->addGameUI("button9", button_0);
	//添加按钮文字到场景
	scene->addGameUIText("t0", text_0);

	//生成加减乘除按钮
	for (int i = 0; i < 4; i++)
	{
		// 生成符号
		const char* con[] = { "+", "-", "×", "÷" };
		// 生成位置
		jhVector2 pos = jhVector2(230, 250 + 60 * i);
		// 生成按钮
		gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
		// 生成按钮文字
		gameUIText* text = new gameUIText(con[i], pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
		// 设置按钮点击事件
		button->mouseAction->setClickFunc(onClick);
		// 添加按钮到场景
		scene->addGameUI("control" + to_string(i), button);
		// 添加按钮文字到场景
		scene->addGameUIText(con[i], text);

	}
	//生成等号按钮
	pos = jhVector2(150, 430);
	//生成按钮
	gameUI* button = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//生成按钮文字
	gameUIText* text = new gameUIText("=", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
	//设置按钮点击事件
	button->mouseAction->setClickFunc(onClick);
	//添加按钮到场景
	scene->addGameUI("control4", button);
	//添加按钮文字到场景
	scene->addGameUIText("=", text);

	//生成清零按钮
	
	//生成位置
	pos = jhVector2(30, 430);
	//生成按钮
	gameUI* button0 = new gameUI(pos, jhVector2(50, 50), "bt.jpg");
	//生成按钮文字
	gameUIText* text0 = new gameUIText("C", pos + jhVector2(5, 5),WHITE,jhVector2(0,25), true);
	//设置按钮点击事件
	button0->mouseAction->setClickFunc(onClick);
	//添加按钮到场景
	scene->addGameUI("control5", button0);
	//添加按钮文字到场景
	scene->addGameUIText("C", text0);

	//生成显示框
	//生成位置
	pos = jhVector2(30, 80);
	//生成显示框文本
	gameUIText* text1 = new gameUIText("", pos,BLACK,jhVector2(0,25), true);
	//添加显示框到场景
	scene->addGameUIText("结果", text1);

	// 初始化窗口开始游戏循环
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
		// 显示结果
		mainGame->getScene()->getGameUIText("结果")->text = to_string(b1);
	}
}