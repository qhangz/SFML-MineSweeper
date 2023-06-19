#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

using namespace sf;

#define GRIDSIZE 25
#define LVL1_WIDTH 9	//不同难度的舞台大小以及雷的数量
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99

//枚举定义栅格
typedef enum GRIDSTATE
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
	ncFLAG,			//标记，旗帜
	ncQ,			//问号
	ncX,			//备用
	ncBOMBING,		//爆炸的雷
	ncUNFOUND,		//未检测出来的雷

};

//枚举定义游戏状态
typedef enum GAMEOVERSTATE
{
	ncNo,	//游戏未结束
	ncWIN,	//游戏胜利
	ncLOSE,	//游戏失败
};

class LEI
{
public:
	int mState;		//雷的状态，用枚举的GRIDSTATE去定义
	int mStateBackUp;	//栅格原始状态备份
	bool isPress;	//雷是否被点击
};

class MineSweeper
{
public:
	sf::RenderWindow window;

	MineSweeper();
	~MineSweeper();

	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	int gamelvl, mTime;	//游戏难度、游戏计时
	int mMineNum, mFlagCalc;	//雷和旗帜的数量
	int imgBGNo, imgSkinNo;		//定义选取那一张背景图和游戏素材（雷）
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];	//数组取最高难度的舞台尺寸
	bool isGameBegin;	//判断游戏是否开始
	int isGameOverState;	//游戏结束的状态
	bool mouseDlbClkReady;	//判断鼠标是否双击
	sf::Vector2i P1, P2;	//两处位置快速点击触发双击的BUG修复
	int mouse_RL_ClkReady;
	sf::Vector2i mCornPoint;	//舞台左顶点坐标
	int gridSize;	//块的大小

	bool RLClkJudgeFlag;	//左右键双击预览判断

	/*t
		tTiles加载的是舞台里雷和数字的素材
		tNum加载的是得分数字的素材
		tButton加载的是按钮的素材
		tTimer加载的是计时器的素材（游戏运行时间）
		tCounter加载的是计数器的素材（雷的余数）
	*/
	sf::Texture tBackground, tNum, tTiles, tButtons, tTimer, tCounter, tGameOver;		//创建纹理对象
	sf::Sprite sBackground, sNum, sTiles, sButtons, sTimer, sCounter, sGameOver;		//创建精灵对象
	sf::IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;	//记录7个按钮坐标的位置

	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkmusic;

	//SFML的clock类在对象实例化的时候就开始计时
	//鼠标点击计时器（用于判断单击双击）
	sf::Clock mouseClickTimer, gameClock;
	sf::Clock mouseRLClickTimer_L, mouseRLClickTimer_R;


	void Run();

	void Initial();
	void IniData();
	void LoadMaterialData();
	void MineSet(int py, int px);	//布雷

	void Input();
	void RButtonDown(Vector2i mPoint);	//鼠标右击
	void LButtonDown(Vector2i mPoint);	//鼠标左击
	void LButtonDblClk(Vector2i mPoint);	//鼠标左键双击
	void RLButtonDown(Vector2i mPoint);		//鼠标左右键同时按下
	void NullClick(int j, int i);
	void unCoverGrid();		//揭开所有方格，调试用
	void RecoverGrid(Vector2i mPoint);	//恢复方格状态
	void RLClkJudge(Vector2i mPoint);	//左右键双击判定

	void Logic();
	void isWin();
	void unCover();

	void Draw();
	void DrawGrid();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();

};

