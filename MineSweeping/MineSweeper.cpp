#include "MineSweeper.h"

MineSweeper::MineSweeper()
{
	Window_Width = 800;
	Window_Height = 600;

	gamelvl = 2;
	imgBGNo = 1;
	imgSkinNo = 1;
	window.create(sf::VideoMode(Window_Width, Window_Height), L"MineSweeper by HANG");
}

MineSweeper::~MineSweeper()
{

}


void MineSweeper::Initial() {
	window.setFramerateLimit(60);	//设置游戏帧率
	gridSize = GRIDSIZE;		//点击的位置的块的大小

	switch (gamelvl)
	{
	case 1:
		stageWidth = LVL1_WIDTH;
		stageHeight = LVL1_HEIGHT;
		mMineNum = LVL1_NUM;
		break;
	case 2:
		stageWidth = LVL2_WIDTH;
		stageHeight = LVL2_HEIGHT;
		mMineNum = LVL2_NUM;
		break;
	case 3:
		stageWidth = LVL3_WIDTH;
		stageHeight = LVL3_HEIGHT;
		mMineNum = LVL3_NUM;
		break;
	default:
		break;
	}

	gameOver = false;
	gameQuit = false;

	isGameOverState = ncNo;	//初始化游戏的结束状态（未结束）
	mFlagCalc = 0;		//初始化棋子的数量
	isGameBegin = false;	//初始化游戏是否开始
	mTime = 0;				//初始化游戏进行的时间

	mCornPoint.x = (Window_Width - stageWidth * GRIDSIZE) / 2;	//设置舞台左上角坐标
	mCornPoint.y = (Window_Height - stageHeight * GRIDSIZE) / 2;
	IniData();
	LoadMaterialData();

}
//初始化数据
void MineSweeper::IniData()
{
	//初始化雷的状态
	int i, j;
	for (j = 0; j < stageHeight; j++)
	{
		for (i = 0; i < stageWidth; i++)
		{
			mGameData[j][i].mState = ncUNDOWN;
			mGameData[j][i].isPress = false;
		}
	}
}
//加载素材material
void MineSweeper::LoadMaterialData()
{
	std::stringstream ss;
	ss << "../data/images/BK0" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str()))
	{
		std::cout << "No bkground image found." << std::endl;
	}

	ss.str("");	//清空字符串
	ss << "../data/images/Game" << imgSkinNo << ".jpg";
	if (!tTiles.loadFromFile(ss.str()))
	{
		std::cout << "No Skin image found." << std::endl;
	}

	if (!tButtons.loadFromFile("../data/images/button.jpg"))
	{
		std::cout << "No Button image found." << std::endl;
	}
	if (!tNum.loadFromFile("../data/images/num.jpg"))
	{
		std::cout << "No Num image found." << std::endl;
	}
	if (!tTimer.loadFromFile("../data/images/jishiqi.jpg"))
	{
		std::cout << "No jishiqi image found." << std::endl;
	}
	if (!tCounter.loadFromFile("../data/images/jishuqi.jpg"))
	{
		std::cout << "No jishuqi image found." << std::endl;
	}
	if (!tGameOver.loadFromFile("../data/images/gameover.jpg"))
	{
		std::cout << "No GameOver image found." << std::endl;
	}
	sBackground.setTexture(tBackground);
	sTiles.setTexture(tTiles);
	sButtons.setTexture(tButtons);
	sNum.setTexture(tNum);
	sTimer.setTexture(tTimer);
	sCounter.setTexture(tCounter);
	sGameOver.setTexture(tGameOver);

}
//布雷（Py、Px为按下的第一个方格）
void MineSweeper::MineSet(int Py, int Px)
{
	int mCount, i, j, m, n;
	mCount = 0;

	srand(time(NULL));	//用当前系统时间作为随机数生成器的种子
	//布雷
	bool flag;
	do {
		m = rand() % stageHeight;
		n = rand() % stageWidth;
		flag = true;

		//确保第一次点击周边九个都不雷
		for (int y = m - 1; y < m + 2; y++)
		{
			for (int x = n - 1; x < n + 2; x++)
			{
				if (y == Py && x == Px)
				{
					flag = false;
					break;
				}
			}
		}
		if (flag == false)
		{
			continue;
		}
		if (mGameData[m][n].mState == ncUNDOWN)
		{
			mGameData[m][n].mState = ncMINE;
			mGameData[m][n].mStateBackUp = ncMINE;	//备份状态
			mCount++;
		}

	} while (mCount != mMineNum);

	//方格赋值
	for (i = 0; i < stageHeight; i++)
	{
		for (j = 0; j < stageWidth; j++)
		{

			if (mGameData[i][j].mState != ncMINE)
			{
				mCount = 0;
				//周边八个方格
				for (m = i - 1; m < i + 2; m++)
				{
					for (n = j - 1; n < j + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							//std::cout << "mGameData[m][n].mState:" << mGameData[m][n].mState << std::endl;
							if (mGameData[m][n].mState == ncMINE)
							{
								mCount++;	//统计周围雷的数量
								//std::cout << "mCount:" << mCount << std::endl;
							}
						}
					}
				}
				//std::cout << "mCount:" << mCount << std::endl;
				switch (mCount)
				{
				case 0:
					mGameData[i][j].mStateBackUp = ncNULL;
					break;
				case 1:
					mGameData[i][j].mStateBackUp = ncONE;
					break;
				case 2:
					mGameData[i][j].mStateBackUp = ncTWO;
					break;
				case 3:
					mGameData[i][j].mStateBackUp = ncTHREE;
					break;
				case 4:
					mGameData[i][j].mStateBackUp = ncFOUR;
					break;
				case 5:
					mGameData[i][j].mStateBackUp = ncFIVE;
					break;
				case 6:
					mGameData[i][j].mStateBackUp = ncSIX;
					break;
				case 7:
					mGameData[i][j].mStateBackUp = ncSEVEN;
					break;
				case 8:
					mGameData[i][j].mStateBackUp = ncEIGHT;
					break;
				default:
					break;
				}
				//右键先行，是旗帜或者问号的方格不赋值
				if (mGameData[i][j].mState != ncFLAG && mGameData[i][j].mState != ncQ)
				{
					mGameData[i][j].mState = mGameData[i][j].mStateBackUp;
				}

			}

		}
	}

}

void MineSweeper::Input() {

	//event types包括Window、Keyboard、Mouse、Joystick四类消息
	//通过bool Window::pollEvent(sf::Event&event)从窗口顺序询问（polled）事件
	//如果有一个事件等待处理，该函数将返回true，并且时间变量将填充（filled）事件数据
	//如果不是，则该函数返回false，同样重要的是要注意，一次可能有多个事件，因此我们必须确保捕获每一个事件
	sf::Event event;

	while (window.pollEvent(event))
	{
		//可以通过点击取消和按下键盘Esc键退出游戏
		if (event.type == sf::Event::Closed)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}

		//鼠标交互
		//鼠标左键Pressed
		//sf::Vector2i P1, P2;	//两处位置快速点击触发双击的BUG修复
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			P2 = Mouse::getPosition(window);
			
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady++;	//左键按下则RL双击准备
				mouseRLClickTimer_L.restart();
				if (mouse_RL_ClkReady == 2 && mouseRLClickTimer_R.getElapsedTime().asMilliseconds() < 300)
				{
					RLButtonDown(Mouse::getPosition(window));
					RecoverGridTimer.restart();
				}
				else
				{
					//windows系统中默认的双击间隔时间就是500毫秒,500毫秒感觉太慢了
					//两处位置快速点击触发双击的BUG修复
					//std::cout << "Mouse1:" << P1.x << "mouse1:" << P1.y << std::endl;
					//std::cout << "Mouse2:" << P2.x << "mouse2:" << P2.y << std::endl;
					if (mouseClickTimer.getElapsedTime().asMilliseconds() < 300 && (P2.x - P1.x) < gridSize && (P2.y - P1.y) < gridSize)
					{
						//std::cout << "Mouse::Left Double Clicked" << std::endl;
						//LButtinDblClk(Mouse::getPosition(window));	//鼠标双击
						LButtonDblClk(P2);
						mouseDlbClkReady = false;
					}
					else
					{
						//std::cout << "Mouse::Left Pressed" << std::endl;
						//LButtonDown(Mouse::getPosition(window));	//鼠标单击
						LButtonDown(P2);
						mouseDlbClkReady = true;

					}
				}
				
			}
		}
		//鼠标左键Released
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			P1 = Mouse::getPosition(window);	//两处位置快速点击触发双击的BUG修复
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady = 0;//状态清除
				RecoverGrid(Mouse::getPosition(window));
			}
			if (isGameOverState == ncNo)
			{
				mouseClickTimer.restart();	//SFML的clock类有getElapsedTime()和restart()两个函数
				
				if (isGameBegin == false)
				{
					if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gamelvl = 1;
					}
					if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gamelvl = 2;
					}
					if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
					{
						gamelvl = 3;
					}
					Initial();	//及时刷新舞台
				}
			}
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGNo++;
				if (imgBGNo > 7)	//大于背景图的总数
				{
					imgBGNo = 1;//重新轮换背景图
				}
				LoadMaterialData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgSkinNo++;
				if (imgSkinNo > 6)	//大于皮肤的总数
				{
					imgSkinNo = 1;//重新轮换皮肤
				}
				LoadMaterialData();
			}
			if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
			{
				Initial();
			}
			if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
			{
				window.close();
				gameQuit = true;
			}
			//std::cout << "Mouse::Left Released" << std::endl;

			
		}
		//鼠标右键Pressed
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady++;
				mouseRLClickTimer_R.restart();
				if (mouse_RL_ClkReady == 2 && mouseRLClickTimer_L.getElapsedTime().asMilliseconds() < 300)
				{
					RLButtonDown(Mouse::getPosition(window));
					RecoverGridTimer.restart();
				}
				else
				{
					RButtonDown(Mouse::getPosition(window));	//鼠标单击
				}
			
			}
			/*std::cout << "Mouse::Right Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;*/
		}
		//鼠标右键Released
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
		{
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady = 0;//状态清除
				RecoverGrid(Mouse::getPosition(window));
			}
		}
		//按键操作
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::T)
		{
			unCoverGrid();	//游戏开始后揭开所有栅格
		}
	}
}

//鼠标右击
void MineSweeper::RButtonDown(Vector2i mPoint)
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//获取鼠标当前点击的块
	j = (mPoint.y - mCornPoint.y) / gridSize;

	//如果在舞台内
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (mGameData[j][i].isPress == false)
		{
			mGameData[j][i].isPress = true;
			mGameData[j][i].mStateBackUp = mGameData[j][i].mState;	//将原本State的属性存在StateBackUp里
			mGameData[j][i].mState = ncFLAG;
			mFlagCalc++;
		}
		else
		{
			if (mGameData[j][i].mState == ncFLAG)
			{
				mGameData[j][i].isPress = true;
				mGameData[j][i].mState = ncQ;
				mFlagCalc--;
			}
			else if (mGameData[j][i].mState == ncQ)
			{
				mGameData[j][i].isPress = false;
				mGameData[j][i].mState = mGameData[j][i].mStateBackUp;
			}
		}
	}


}
//鼠标左击
void MineSweeper::LButtonDown(Vector2i mPoint)
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//获取鼠标当前点击的块
	j = (mPoint.y - mCornPoint.y) / gridSize;
	//std::cout << "i:" << i << "j:" << j << std::endl;
	//std::cout << "mGameData[m][n].mState:" << mGameData[j][i].mState << std::endl;

	//如果在舞台内
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (isGameBegin == false)	//游戏未开始
		{
			isGameBegin = true;	//游戏开始
			gameClock.restart();
			MineSet(j, i);		//点击之后在随机布雷
		}

		if (mGameData[j][i].mState != ncFLAG)	//状态不是旗子
		{
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;	//当前块被点击
				if (mGameData[j][i].mState == ncMINE)	//当前块为雷
				{
					isGameBegin = false;
					isGameOverState = ncLOSE;
					mGameData[j][i].mState = ncBOMBING;
					unCover();	//揭开剩下未被找到的雷
				}


			}
		}
		if (mGameData[j][i].mState == ncNULL)	//如果当前块为空
		{
			NullClick(j, i);	//查找未被点击的空块
		}
	}

}
//鼠标左键双击
void MineSweeper::LButtonDblClk(Vector2i mPoint)
{
	int i, j, m, n, lvl;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//如果点击是在范围内
	{
		if (mGameData[j][i].isPress == true)	//如果已经被点击
		{
			if (mGameData[j][i].mState != ncFLAG)	//如果当前块不是旗子
			{
				//遍历周围八个格子
				for (m = j - 1; m < j + 2; m++)
				{
					for (n = i - 1; n < i + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							if (mGameData[m][n].mState == ncFLAG)	//如果状态为旗子
							{
								if (mGameData[m][n].mStateBackUp != ncMINE)//如果原先状态为雷
								{
									isGameOverState = ncLOSE;
									isGameBegin = false;
									unCover();	//揭开剩下未被找到的雷
								}
							}
							else //如果状态不是旗子
							{
								if (mGameData[m][n].isPress == false)
								{
									mGameData[m][n].isPress = true;
									if (mGameData[m][n].mState == ncMINE)//如果为雷
									{
										isGameOverState = ncLOSE;
										isGameBegin = false;
										mGameData[m][n].mState = ncBOMBING;
										unCover();
									}
									if (mGameData[m][n].mState == ncNULL)//如果为空
									{
										NullClick(m, n);
									}
								}
							}

						}
					}
				}
			}
		}
	}

}
//鼠标左右键同时按下，预览
void MineSweeper::RLButtonDown(Vector2i mPoint)
{
	int i, j, m, n;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//获取鼠标当前点击的块
	j = (mPoint.y - mCornPoint.y) / gridSize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//如果点击是在范围内
	{
		if (mGameData[j][i].isPress == true)	//如果已经被点击
		{
			if (mGameData[j][i].mState != ncFLAG)	//如果当前块不是旗子
			{
				//遍历周围八个格子
				for (m = j - 1; m < j + 2; m++)
				{
					for (n = i - 1; n < i + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							if (mGameData[m][n].isPress == false)
							{
								mGameData[m][n].mStateBackUp = mGameData[m][n].mState;
								mGameData[m][n].mState = ncX;
							}
							//if (mGameData[m][n].mState == ncFLAG)	//如果状态为旗子
							//{
							//	if (mGameData[m][n].mStateBackUp != ncMINE)//如果原先状态不为雷
							//	{
							//		//isGameOverState = ncLOSE;
							//		//isGameBegin = false;
							//		//unCover();	//揭开剩下未被找到的雷
							//		break;
							//	}
							//}
							//else //如果状态不是旗子
							//{
							//	if (mGameData[m][n].isPress == false)	//未掀开的
							//	{
							//		
							//		if (mGameData[m][n].mState == ncMINE)//如果为雷
							//		{
							//			isGameOverState = ncLOSE;
							//			isGameBegin = false;
							//			mGameData[m][n].mState = ncBOMBING;
							//			unCover();
							//		}
							//		if (mGameData[m][n].mState == ncNULL)//如果为空
							//		{
							//			mGameData[m][n].isPress = true;
							//		}
							//	}
							//}

						}
					}
				}
			}
		}
	}
}
//查找未被点击的空块
void MineSweeper::NullClick(int j, int i)
{
	int n, m;
	for (m = j - 1; m < j + 2; m++)
	{
		for (n = i - 1; n < i + 2; n++)
		{
			if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
			{
				if (mGameData[m][n].isPress == false)
				{
					mGameData[m][n].isPress = true;
					if (mGameData[m][n].mState == ncNULL)	//如果状态为空
					{
						NullClick(m, n);	//递归调用继续查看
					}
				}
			}
		}
	}
}
//揭开剩下未被找到的雷
void MineSweeper::unCover()
{
	int i, j;
	for (j = 0; j < stageHeight; j++)
	{
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == false)
			{
				if (mGameData[j][i].mState == ncMINE)
				{
					mGameData[j][i].isPress = true;
					mGameData[j][i].mState = ncUNFOUND;
				}
			}
			//揭开标记错误的雷
			/*else if(mGameData[j][i].mState == ncFLAG || mGameData[j][i].mState == ncQ)
			{
				if(mGameData[j][i].mStateBackUp == ncMINE)
				{
					mGameData[j][i].isPress = true;
					mGameData[j][i].mState = ncUNFOUND;
				}
			}*/
		}
	}
}
//揭开所有游戏方格
void MineSweeper::unCoverGrid()
{
	for (int j = 0; j < stageHeight; j++)
	{
		for (int i = 0; i < stageWidth; i++)
		{
			mGameData[j][i].isPress = true;
		}
	}
}
//恢复方格状态
void MineSweeper::RecoverGrid(Vector2i mPoint)
{
	int i, j, m, n;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//获取鼠标当前点击的块
	j = (mPoint.y - mCornPoint.y) / gridSize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//如果点击是在范围内
	{
		if (mGameData[j][i].isPress == true)	//如果已经被点击
		{
			if (mGameData[j][i].mState != ncFLAG)	//如果当前块不是旗子
			{
				//遍历周围八个格子
				for (m = j - 1; m < j + 2; m++)
				{
					for (n = i - 1; n < i + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							if (mGameData[m][n].isPress == false)
							{
								mGameData[m][n].mState = mGameData[m][n].mStateBackUp;
								//mGameData[m][n].mState = ncX;
							}
				
						}
					}
				}
			}
		}
	}
}

void MineSweeper::Logic()
{
	isWin();
}

void MineSweeper::isWin()
{
	//只要舞台上只剩下雷那就宣布游戏胜利
	int i, j;
	int c = 0;	//记录错误数量
	//if (mFlagCalc == mMineNum)	//判断插的所有旗是不是都是雷
	//{
	//	for (i = 0; i < stageWidth; i++)
	//	{
	//		for (j = 0; j < stageHeight; j++)
	//		{
	//			if (mGameData[j][i].mState == ncFLAG)
	//			{
	//				if (mGameData[j][i].mStateBackUp == ncMINE)
	//				{
	//					c++;
	//				}
	//			}
	//		}
	//	}
	//}
	//else  //判断剩下没插旗的块是不是雷
	//{
	//	if(isGameOverState!=ncLOSE)
	//	{
	//		for (i = 0; i < stageWidth; i++)
	//		{
	//			for (j = 0; j < stageHeight; j++)
	//			{
	//				if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG)
	//				{
	//					c++;
	//				}
	//			}
	//		}
	//	}
	//}
	if (isGameOverState != ncLOSE)
	{
		for (i = 0; i < stageWidth; i++)
		{
			for (j = 0; j < stageHeight; j++)
			{
				if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG)
				{
					c++;
				}
			}
		}
	}

	if (c == mMineNum)		//如果所有旗子对应的都是雷，游戏胜利并结束
	{
		isGameBegin = false;
		isGameOverState = ncWIN;
	}
}


void MineSweeper::Draw() {
	window.clear(); //清屏

	//绘制背景
	sBackground.setPosition(0, 0);
	window.draw(sBackground);

	//绘制舞台
	DrawGrid();
	DrawButton();
	DrawScore();
	DrawTimer();

	if (isGameOverState)
		DrawGameEnd();

	window.display();	//把显示缓冲区的内容，显示在屏幕上（SFML采用双缓冲机制）

}

//绘制舞台
void MineSweeper::DrawGrid()
{
	/*for (int j = 0; j < stageHeight; j++)
	{
		for (int i = 0; i < stageWidth; i++)
		{
			std::cout << "mGameData[m][n].mState:" << mGameData[j][i].mState << std::endl;
			mGameData[j][i].isPress = true;
		}
	}*/

	for (int j = 0; j < stageHeight; j++)
	{
		for (int i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == true)
			{
				sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			else
			{
				sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			window.draw(sTiles);
		}
	}
}
//绘制按钮
void MineSweeper::DrawButton()
{
	Vector2i LeftCorner;	//用于记录按钮在窗口的位置
	int ButtonWidth = 60;
	int ButtonHeight = 36;
	int detaX;
	detaX = (Window_Width - ButtonWidth * 7) / 8;	//7个按钮在界面上等分宽度
	LeftCorner.y = Window_Height - GRIDSIZE * 3;	//指定高度

	//把7个按钮的坐标及尺寸都更新了
	//ButtonRectEasy,
	LeftCorner.x = detaX;
	sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));	//四个整数值，分别表示左上角顶点的横坐标和纵坐标，以及矩形的宽度和高度。
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectEasy.left = LeftCorner.x;
	ButtonRectEasy.top = LeftCorner.y;
	ButtonRectEasy.width = ButtonWidth;
	ButtonRectEasy.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectNormal, 
	LeftCorner.x = detaX * 2 + ButtonWidth;
	sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectNormal.left = LeftCorner.x;
	ButtonRectNormal.top = LeftCorner.y;
	ButtonRectNormal.width = ButtonWidth;
	ButtonRectNormal.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectHard, 
	LeftCorner.x = detaX * 3 + ButtonWidth * 2;
	sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectHard.left = LeftCorner.x;
	ButtonRectHard.top = LeftCorner.y;
	ButtonRectHard.width = ButtonWidth;
	ButtonRectHard.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectSkin, 
	LeftCorner.x = detaX * 4 + ButtonWidth * 3;
	sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectSkin.left = LeftCorner.x;
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectBG, 
	LeftCorner.x = detaX * 5 + ButtonWidth * 4;
	sButtons.setTextureRect(IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectBG.left = LeftCorner.x;
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectRestart, 
	LeftCorner.x = detaX * 6 + ButtonWidth * 5;
	sButtons.setTextureRect(IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectRestart.left = LeftCorner.x;
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectQuit
	LeftCorner.x = detaX * 7 + ButtonWidth * 6;
	sButtons.setTextureRect(IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectQuit.left = LeftCorner.x;
	ButtonRectQuit.top = LeftCorner.y;
	ButtonRectQuit.width = ButtonWidth;
	ButtonRectQuit.height = ButtonHeight;
	window.draw(sButtons);
}
//绘制雷的余量信息（计数器）
void MineSweeper::DrawScore()
{
	Vector2i LeftCorner;
	LeftCorner.x = Window_Width - sCounter.getLocalBounds().width * 1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x, LeftCorner.y);	//计数器纹理的贴图位置
	window.draw(sCounter);

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;

	//绘制还有多少个雷
	int mScore = mMineNum - mFlagCalc;	//（雷的余数）
	//绘制个位数的数字
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));	//找到纹理贴图上的数字
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制十位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制百位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);


}
//绘制游戏运行时间（计时器）
void MineSweeper::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
	LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);	//计时器纹理的贴图位置
	window.draw(sTimer);

	if (isGameBegin)
	{
		mTime = gameClock.getElapsedTime().asSeconds();
	}

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
	LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height * 0.5 - NumSize * 0.5;

	//绘制时间
	int mScore = mTime;
	if (mScore > 999)
		mScore = 999;
	//绘制个位数的数字
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));	//找到纹理贴图上的数字
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制十位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制百位数的数字
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);

}
void MineSweeper::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 200;
	int ButtonHeight = sGameOver.getLocalBounds().height;
	LeftCorner.x = (Window_Width - ButtonWidth) / 2;
	LeftCorner.y = (Window_Height - ButtonHeight) / 2;

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);

	if (isGameOverState == ncWIN)
	{
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}
	if (isGameOverState == ncLOSE)
	{
		sGameOver.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}

	window.draw(sGameOver);
}

void MineSweeper::Run() {
	do
	{
		Initial();
		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();
		}
	} while (!gameQuit && window.isOpen());
}


