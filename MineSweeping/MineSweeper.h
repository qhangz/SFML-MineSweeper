#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

using namespace sf;

#define GRIDSIZE 25
#define LVL1_WIDTH 9	//��ͬ�Ѷȵ���̨��С�Լ��׵�����
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99

//ö�ٶ���դ��
typedef enum GRIDSTATE
{
	ncNULL,			//�յ�
	ncUNDOWN,		//��������
	ncMINE,			//����
	ncONE,			//����1
	ncTWO,			//����2
	ncTHREE,		//����3
	ncFOUR,			//����4
	ncFIVE,			//����5
	ncSIX,			//����6
	ncSEVEN,		//����7
	ncEIGHT,		//����8
	ncFLAG,			//��ǣ�����
	ncQ,			//�ʺ�
	ncX,			//����
	ncBOMBING,		//��ը����
	ncUNFOUND,		//δ����������

};

//ö�ٶ�����Ϸ״̬
typedef enum GAMEOVERSTATE
{
	ncNo,	//��Ϸδ����
	ncWIN,	//��Ϸʤ��
	ncLOSE,	//��Ϸʧ��
};

class LEI
{
public:
	int mState;		//�׵�״̬����ö�ٵ�GRIDSTATEȥ����
	int mStateBackUp;	//դ��ԭʼ״̬����
	bool isPress;	//���Ƿ񱻵��
};

class MineSweeper
{
public:
	sf::RenderWindow window;

	MineSweeper();
	~MineSweeper();

	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	int gamelvl, mTime;	//��Ϸ�Ѷȡ���Ϸ��ʱ
	int mMineNum, mFlagCalc;	//�׺����ĵ�����
	int imgBGNo, imgSkinNo;		//����ѡȡ��һ�ű���ͼ����Ϸ�زģ��ף�
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];	//����ȡ����Ѷȵ���̨�ߴ�
	bool isGameBegin;	//�ж���Ϸ�Ƿ�ʼ
	int isGameOverState;	//��Ϸ������״̬
	bool mouseDlbClkReady;	//�ж�����Ƿ�˫��
	sf::Vector2i P1, P2;	//����λ�ÿ��ٵ������˫����BUG�޸�
	int mouse_RL_ClkReady;
	sf::Vector2i mCornPoint;	//��̨�󶥵�����
	int gridSize;	//��Ĵ�С

	bool RLClkJudgeFlag;	//���Ҽ�˫��Ԥ���ж�

	/*t
		tTiles���ص�����̨���׺����ֵ��ز�
		tNum���ص��ǵ÷����ֵ��ز�
		tButton���ص��ǰ�ť���ز�
		tTimer���ص��Ǽ�ʱ�����زģ���Ϸ����ʱ�䣩
		tCounter���ص��Ǽ��������زģ��׵�������
	*/
	sf::Texture tBackground, tNum, tTiles, tButtons, tTimer, tCounter, tGameOver;		//�����������
	sf::Sprite sBackground, sNum, sTiles, sButtons, sTimer, sCounter, sGameOver;		//�����������
	sf::IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;	//��¼7����ť�����λ��

	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkmusic;

	//SFML��clock���ڶ���ʵ������ʱ��Ϳ�ʼ��ʱ
	//�������ʱ���������жϵ���˫����
	sf::Clock mouseClickTimer, gameClock;
	sf::Clock mouseRLClickTimer_L, mouseRLClickTimer_R;


	void Run();

	void Initial();
	void IniData();
	void LoadMaterialData();
	void MineSet(int py, int px);	//����

	void Input();
	void RButtonDown(Vector2i mPoint);	//����һ�
	void LButtonDown(Vector2i mPoint);	//������
	void LButtonDblClk(Vector2i mPoint);	//������˫��
	void RLButtonDown(Vector2i mPoint);		//������Ҽ�ͬʱ����
	void NullClick(int j, int i);
	void unCoverGrid();		//�ҿ����з��񣬵�����
	void RecoverGrid(Vector2i mPoint);	//�ָ�����״̬
	void RLClkJudge(Vector2i mPoint);	//���Ҽ�˫���ж�

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

