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
	window.setFramerateLimit(60);	//������Ϸ֡��
	gridSize = GRIDSIZE;		//�����λ�õĿ�Ĵ�С

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

	isGameOverState = ncNo;	//��ʼ����Ϸ�Ľ���״̬��δ������
	mFlagCalc = 0;		//��ʼ�����ӵ�����
	isGameBegin = false;	//��ʼ����Ϸ�Ƿ�ʼ
	mTime = 0;				//��ʼ����Ϸ���е�ʱ��

	mCornPoint.x = (Window_Width - stageWidth * GRIDSIZE) / 2;	//������̨���Ͻ�����
	mCornPoint.y = (Window_Height - stageHeight * GRIDSIZE) / 2;
	IniData();
	LoadMaterialData();

}
//��ʼ������
void MineSweeper::IniData()
{
	//��ʼ���׵�״̬
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
//�����ز�material
void MineSweeper::LoadMaterialData()
{
	std::stringstream ss;
	ss << "../data/images/BK0" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str()))
	{
		std::cout << "No bkground image found." << std::endl;
	}

	ss.str("");	//����ַ���
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
//���ף�Py��PxΪ���µĵ�һ������
void MineSweeper::MineSet(int Py, int Px)
{
	int mCount, i, j, m, n;
	mCount = 0;

	srand(time(NULL));	//�õ�ǰϵͳʱ����Ϊ�����������������
	//����
	bool flag;
	do {
		m = rand() % stageHeight;
		n = rand() % stageWidth;
		flag = true;

		//ȷ����һ�ε���ܱ߾Ÿ�������
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
			mGameData[m][n].mStateBackUp = ncMINE;	//����״̬
			mCount++;
		}

	} while (mCount != mMineNum);

	//����ֵ
	for (i = 0; i < stageHeight; i++)
	{
		for (j = 0; j < stageWidth; j++)
		{

			if (mGameData[i][j].mState != ncMINE)
			{
				mCount = 0;
				//�ܱ߰˸�����
				for (m = i - 1; m < i + 2; m++)
				{
					for (n = j - 1; n < j + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							//std::cout << "mGameData[m][n].mState:" << mGameData[m][n].mState << std::endl;
							if (mGameData[m][n].mState == ncMINE)
							{
								mCount++;	//ͳ����Χ�׵�����
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
				//�Ҽ����У������Ļ����ʺŵķ��񲻸�ֵ
				if (mGameData[i][j].mState != ncFLAG && mGameData[i][j].mState != ncQ)
				{
					mGameData[i][j].mState = mGameData[i][j].mStateBackUp;
				}

			}

		}
	}

}

void MineSweeper::Input() {

	//event types����Window��Keyboard��Mouse��Joystick������Ϣ
	//ͨ��bool Window::pollEvent(sf::Event&event)�Ӵ���˳��ѯ�ʣ�polled���¼�
	//�����һ���¼��ȴ������ú���������true������ʱ���������䣨filled���¼�����
	//������ǣ���ú�������false��ͬ����Ҫ����Ҫע�⣬һ�ο����ж���¼���������Ǳ���ȷ������ÿһ���¼�
	sf::Event event;

	while (window.pollEvent(event))
	{
		//����ͨ�����ȡ���Ͱ��¼���Esc���˳���Ϸ
		if (event.type == sf::Event::Closed)
		{
			window.close();	//���ڿ����ƶ���������С����С�������������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();	//���ڿ����ƶ���������С����С�������������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}

		//��꽻��
		//������Pressed
		//sf::Vector2i P1, P2;	//����λ�ÿ��ٵ������˫����BUG�޸�
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			P2 = Mouse::getPosition(window);
			
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady++;	//���������RL˫��׼��
				mouseRLClickTimer_L.restart();
				if (mouse_RL_ClkReady == 2 && mouseRLClickTimer_R.getElapsedTime().asMilliseconds() < 300)
				{
					RLButtonDown(Mouse::getPosition(window));
					RecoverGridTimer.restart();
				}
				else
				{
					//windowsϵͳ��Ĭ�ϵ�˫�����ʱ�����500����,500����о�̫����
					//����λ�ÿ��ٵ������˫����BUG�޸�
					//std::cout << "Mouse1:" << P1.x << "mouse1:" << P1.y << std::endl;
					//std::cout << "Mouse2:" << P2.x << "mouse2:" << P2.y << std::endl;
					if (mouseClickTimer.getElapsedTime().asMilliseconds() < 300 && (P2.x - P1.x) < gridSize && (P2.y - P1.y) < gridSize)
					{
						//std::cout << "Mouse::Left Double Clicked" << std::endl;
						//LButtinDblClk(Mouse::getPosition(window));	//���˫��
						LButtonDblClk(P2);
						mouseDlbClkReady = false;
					}
					else
					{
						//std::cout << "Mouse::Left Pressed" << std::endl;
						//LButtonDown(Mouse::getPosition(window));	//��굥��
						LButtonDown(P2);
						mouseDlbClkReady = true;

					}
				}
				
			}
		}
		//������Released
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			P1 = Mouse::getPosition(window);	//����λ�ÿ��ٵ������˫����BUG�޸�
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady = 0;//״̬���
				RecoverGrid(Mouse::getPosition(window));
			}
			if (isGameOverState == ncNo)
			{
				mouseClickTimer.restart();	//SFML��clock����getElapsedTime()��restart()��������
				
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
					Initial();	//��ʱˢ����̨
				}
			}
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGNo++;
				if (imgBGNo > 7)	//���ڱ���ͼ������
				{
					imgBGNo = 1;//�����ֻ�����ͼ
				}
				LoadMaterialData();
			}
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgSkinNo++;
				if (imgSkinNo > 6)	//����Ƥ��������
				{
					imgSkinNo = 1;//�����ֻ�Ƥ��
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
		//����Ҽ�Pressed
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
					RButtonDown(Mouse::getPosition(window));	//��굥��
				}
			
			}
			/*std::cout << "Mouse::Right Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;*/
		}
		//����Ҽ�Released
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
		{
			if (isGameOverState == ncNo)
			{
				mouse_RL_ClkReady = 0;//״̬���
				RecoverGrid(Mouse::getPosition(window));
			}
		}
		//��������
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::T)
		{
			unCoverGrid();	//��Ϸ��ʼ��ҿ�����դ��
		}
	}
}

//����һ�
void MineSweeper::RButtonDown(Vector2i mPoint)
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//��ȡ��굱ǰ����Ŀ�
	j = (mPoint.y - mCornPoint.y) / gridSize;

	//�������̨��
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (mGameData[j][i].isPress == false)
		{
			mGameData[j][i].isPress = true;
			mGameData[j][i].mStateBackUp = mGameData[j][i].mState;	//��ԭ��State�����Դ���StateBackUp��
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
//������
void MineSweeper::LButtonDown(Vector2i mPoint)
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//��ȡ��굱ǰ����Ŀ�
	j = (mPoint.y - mCornPoint.y) / gridSize;
	//std::cout << "i:" << i << "j:" << j << std::endl;
	//std::cout << "mGameData[m][n].mState:" << mGameData[j][i].mState << std::endl;

	//�������̨��
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (isGameBegin == false)	//��Ϸδ��ʼ
		{
			isGameBegin = true;	//��Ϸ��ʼ
			gameClock.restart();
			MineSet(j, i);		//���֮�����������
		}

		if (mGameData[j][i].mState != ncFLAG)	//״̬��������
		{
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;	//��ǰ�鱻���
				if (mGameData[j][i].mState == ncMINE)	//��ǰ��Ϊ��
				{
					isGameBegin = false;
					isGameOverState = ncLOSE;
					mGameData[j][i].mState = ncBOMBING;
					unCover();	//�ҿ�ʣ��δ���ҵ�����
				}


			}
		}
		if (mGameData[j][i].mState == ncNULL)	//�����ǰ��Ϊ��
		{
			NullClick(j, i);	//����δ������Ŀտ�
		}
	}

}
//������˫��
void MineSweeper::LButtonDblClk(Vector2i mPoint)
{
	int i, j, m, n, lvl;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//���������ڷ�Χ��
	{
		if (mGameData[j][i].isPress == true)	//����Ѿ������
		{
			if (mGameData[j][i].mState != ncFLAG)	//�����ǰ�鲻������
			{
				//������Χ�˸�����
				for (m = j - 1; m < j + 2; m++)
				{
					for (n = i - 1; n < i + 2; n++)
					{
						if (m >= 0 && m < stageHeight && n >= 0 && n < stageWidth)
						{
							if (mGameData[m][n].mState == ncFLAG)	//���״̬Ϊ����
							{
								if (mGameData[m][n].mStateBackUp != ncMINE)//���ԭ��״̬Ϊ��
								{
									isGameOverState = ncLOSE;
									isGameBegin = false;
									unCover();	//�ҿ�ʣ��δ���ҵ�����
								}
							}
							else //���״̬��������
							{
								if (mGameData[m][n].isPress == false)
								{
									mGameData[m][n].isPress = true;
									if (mGameData[m][n].mState == ncMINE)//���Ϊ��
									{
										isGameOverState = ncLOSE;
										isGameBegin = false;
										mGameData[m][n].mState = ncBOMBING;
										unCover();
									}
									if (mGameData[m][n].mState == ncNULL)//���Ϊ��
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
//������Ҽ�ͬʱ���£�Ԥ��
void MineSweeper::RLButtonDown(Vector2i mPoint)
{
	int i, j, m, n;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//��ȡ��굱ǰ����Ŀ�
	j = (mPoint.y - mCornPoint.y) / gridSize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//���������ڷ�Χ��
	{
		if (mGameData[j][i].isPress == true)	//����Ѿ������
		{
			if (mGameData[j][i].mState != ncFLAG)	//�����ǰ�鲻������
			{
				//������Χ�˸�����
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
							//if (mGameData[m][n].mState == ncFLAG)	//���״̬Ϊ����
							//{
							//	if (mGameData[m][n].mStateBackUp != ncMINE)//���ԭ��״̬��Ϊ��
							//	{
							//		//isGameOverState = ncLOSE;
							//		//isGameBegin = false;
							//		//unCover();	//�ҿ�ʣ��δ���ҵ�����
							//		break;
							//	}
							//}
							//else //���״̬��������
							//{
							//	if (mGameData[m][n].isPress == false)	//δ�ƿ���
							//	{
							//		
							//		if (mGameData[m][n].mState == ncMINE)//���Ϊ��
							//		{
							//			isGameOverState = ncLOSE;
							//			isGameBegin = false;
							//			mGameData[m][n].mState = ncBOMBING;
							//			unCover();
							//		}
							//		if (mGameData[m][n].mState == ncNULL)//���Ϊ��
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
//����δ������Ŀտ�
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
					if (mGameData[m][n].mState == ncNULL)	//���״̬Ϊ��
					{
						NullClick(m, n);	//�ݹ���ü����鿴
					}
				}
			}
		}
	}
}
//�ҿ�ʣ��δ���ҵ�����
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
			//�ҿ���Ǵ������
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
//�ҿ�������Ϸ����
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
//�ָ�����״̬
void MineSweeper::RecoverGrid(Vector2i mPoint)
{
	int i, j, m, n;
	i = (mPoint.x - mCornPoint.x) / gridSize;	//��ȡ��굱ǰ����Ŀ�
	j = (mPoint.y - mCornPoint.y) / gridSize;
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)	//���������ڷ�Χ��
	{
		if (mGameData[j][i].isPress == true)	//����Ѿ������
		{
			if (mGameData[j][i].mState != ncFLAG)	//�����ǰ�鲻������
			{
				//������Χ�˸�����
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
	//ֻҪ��̨��ֻʣ�����Ǿ�������Ϸʤ��
	int i, j;
	int c = 0;	//��¼��������
	//if (mFlagCalc == mMineNum)	//�жϲ���������ǲ��Ƕ�����
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
	//else  //�ж�ʣ��û����Ŀ��ǲ�����
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

	if (c == mMineNum)		//����������Ӷ�Ӧ�Ķ����ף���Ϸʤ��������
	{
		isGameBegin = false;
		isGameOverState = ncWIN;
	}
}


void MineSweeper::Draw() {
	window.clear(); //����

	//���Ʊ���
	sBackground.setPosition(0, 0);
	window.draw(sBackground);

	//������̨
	DrawGrid();
	DrawButton();
	DrawScore();
	DrawTimer();

	if (isGameOverState)
		DrawGameEnd();

	window.display();	//����ʾ�����������ݣ���ʾ����Ļ�ϣ�SFML����˫������ƣ�

}

//������̨
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
//���ư�ť
void MineSweeper::DrawButton()
{
	Vector2i LeftCorner;	//���ڼ�¼��ť�ڴ��ڵ�λ��
	int ButtonWidth = 60;
	int ButtonHeight = 36;
	int detaX;
	detaX = (Window_Width - ButtonWidth * 7) / 8;	//7����ť�ڽ����ϵȷֿ��
	LeftCorner.y = Window_Height - GRIDSIZE * 3;	//ָ���߶�

	//��7����ť�����꼰�ߴ綼������
	//ButtonRectEasy,
	LeftCorner.x = detaX;
	sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));	//�ĸ�����ֵ���ֱ��ʾ���ϽǶ���ĺ�����������꣬�Լ����εĿ�Ⱥ͸߶ȡ�
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
//�����׵�������Ϣ����������
void MineSweeper::DrawScore()
{
	Vector2i LeftCorner;
	LeftCorner.x = Window_Width - sCounter.getLocalBounds().width * 1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x, LeftCorner.y);	//�������������ͼλ��
	window.draw(sCounter);

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;

	//���ƻ��ж��ٸ���
	int mScore = mMineNum - mFlagCalc;	//���׵�������
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));	//�ҵ�������ͼ�ϵ�����
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);


}
//������Ϸ����ʱ�䣨��ʱ����
void MineSweeper::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
	LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);	//��ʱ���������ͼλ��
	window.draw(sTimer);

	if (isGameBegin)
	{
		mTime = gameClock.getElapsedTime().asSeconds();
	}

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
	LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height * 0.5 - NumSize * 0.5;

	//����ʱ��
	int mScore = mTime;
	if (mScore > 999)
		mScore = 999;
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));	//�ҵ�������ͼ�ϵ�����
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//���ư�λ��������
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


