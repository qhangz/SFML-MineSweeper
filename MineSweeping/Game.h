#pragma once
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>

#define GRIDSIZE 25
#define LVL1_WIDTH 9	//不同难度的舞台大小
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99
//枚举定义栅格
typedef enum DRIDSTATE
{
	ncNULL,			//空地
	ncUNDOWN,		//背景方块
	ncMINE,			//地雷
	ncONE,			//数字1
	ncTWO,			//数字2
	ncTHREE,		//数字3
	ncFOUR,			//数字4
	ncFIVE,			//数字5
	ncSIX,			//数字6
	ncSEVEN,		//数字7
	ncEIGHT,		//数字8
	ncFLAG,			//数字9
	ncQ,			//问号
	ncX,			//备用
	ncBOMBING,		//爆炸的雷
	ncUNFOUND,		//未检测出来的雷

};

class LEI
{
public:
	int mState;		//雷的状态
	int mStateBackUp;	//栅格原始状态备份
	int isPress;	//栅格是否被点击
};

class Game
{
public:
	sf::RenderWindow window;

	Game();
	~Game();

	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	int gamelvl, mTime;	//游戏难度、游戏计时
	LEI mGaneData[LVL3_HEIGHT][LVL3_WIDTH];	//数组取最高难度的舞台尺寸

	//鼠标点击计时器（用于判断单击双击）
	sf::Clock mouseClickTimer;

	void Initial();
	void Input();
	void Logic();
	void Draw();
	void Run();
};

