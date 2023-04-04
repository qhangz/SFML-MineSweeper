#pragma once
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>

#define GRIDSIZE 25
#define LVL1_WIDTH 9	//��ͬ�Ѷȵ���̨��С
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99
//ö�ٶ���դ��
typedef enum DRIDSTATE
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
	ncFLAG,			//����9
	ncQ,			//�ʺ�
	ncX,			//����
	ncBOMBING,		//��ը����
	ncUNFOUND,		//δ����������

};

class LEI
{
public:
	int mState;		//�׵�״̬
	int mStateBackUp;	//դ��ԭʼ״̬����
	int isPress;	//դ���Ƿ񱻵��
};

class Game
{
public:
	sf::RenderWindow window;

	Game();
	~Game();

	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	int gamelvl, mTime;	//��Ϸ�Ѷȡ���Ϸ��ʱ
	LEI mGaneData[LVL3_HEIGHT][LVL3_WIDTH];	//����ȡ����Ѷȵ���̨�ߴ�

	//�������ʱ���������жϵ���˫����
	sf::Clock mouseClickTimer;

	void Initial();
	void Input();
	void Logic();
	void Draw();
	void Run();
};

