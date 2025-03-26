#include "JHMG engine.h"
using namespace JHMG_ENGINE;
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
void onClick(int mouseMessage, Vector2 position, GameUI* self);

int main()
{
	// 创建游戏
	mainGame = new Game;
	// 设置窗口大小
	mainGame->setWindowSize(Vector2(300, 500));
	// 设置窗口标题
	mainGame->setWindowTitle("计算器");
	// 创建场景
	GameScene* scene = new GameScene;
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
			Vector2 pos = Vector2(30 + 60 * j, 250 + 60 * i);
			// 生成按钮
			GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
			// 生成按钮文字
			GameUIText* text = new GameUIText(std::to_string(i * 3 + j + 1), pos + Vector2(5, 5),WHITE,Vector2(0,25),true);
			// 设置按钮点击事件
			button->mouseAction->setClickFunc(onClick);
			// 添加按钮到场景
			scene->addGameUI("button" + std::to_string(i * 3 + j), button);
			// 添加按钮文字到场景
			scene->addGameUIText(std::to_string(i * 3 + j), text);
		}
	}

	//生成0按钮
	Vector2 pos = Vector2(90, 430);
	//生成按钮
	GameUI* button_0 = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//生成按钮文字
	GameUIText* text_0 = new GameUIText("0", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
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
		Vector2 pos = Vector2(230, 250 + 60 * i);
		// 生成按钮
		GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
		// 生成按钮文字
		GameUIText* text = new GameUIText(con[i], pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
		// 设置按钮点击事件
		button->mouseAction->setClickFunc(onClick);
		// 添加按钮到场景
		scene->addGameUI("control" + std::to_string(i), button);
		// 添加按钮文字到场景
		scene->addGameUIText(con[i], text);

	}
	//生成等号按钮
	pos = Vector2(150, 430);
	//生成按钮
	GameUI* button = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//生成按钮文字
	GameUIText* text = new GameUIText("=", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
	//设置按钮点击事件
	button->mouseAction->setClickFunc(onClick);
	//添加按钮到场景
	scene->addGameUI("control4", button);
	//添加按钮文字到场景
	scene->addGameUIText("=", text);

	//生成清零按钮
	
	//生成位置
	pos = Vector2(30, 430);
	//生成按钮
	GameUI* button0 = new GameUI(pos, Vector2(50, 50), "bt.jpg");
	//生成按钮文字
	GameUIText* text0 = new GameUIText("C", pos + Vector2(5, 5),WHITE,Vector2(0,25), true);
	//设置按钮点击事件
	button0->mouseAction->setClickFunc(onClick);
	//添加按钮到场景
	scene->addGameUI("control5", button0);
	//添加按钮文字到场景
	scene->addGameUIText("C", text0);

	//生成显示框
	//生成位置
	pos = Vector2(30, 80);
	//生成显示框文本
	GameUIText* text1 = new GameUIText("", pos,BLACK,Vector2(0,25), true);
	//添加显示框到场景
	scene->addGameUIText("结果", text1);

	// 初始化窗口开始游戏循环
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
		// 显示结果
		mainGame->getScene()->getGameUIText("结果")->text = std::to_string(b1);
	}
}