#include "Game.h"

Game::Game()
{
	Window_Width = 800;
	Window_Height = 600;
	window.create(sf::VideoMode(Window_Width, Window_Height), L"MineSweeper by HANG");
}

Game::~Game()
{

}


void Game::Initial() {
	window.setFramerateLimit(60);	//设置游戏帧率

	gameOver = false;
	gameQuit = false;
}

void Game::Input() {
	sf::Event event;	//event types包括Window、Keyboard、Mouse、Joystick四类消息
						//通过bool Window::pollEvent(sf::Event&event)从窗口顺序询问（polled）事件
						//如果有一个事件等待处理，该函数将返回true，并且时间变量将填充（filled）事件数据
						//如果不是，则该函数返回false，同样重要的是要注意，一次可能有多个事件，因此我们必须确保捕获每一个事件
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
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (mouseClickTimer.getElapsedTime().asMilliseconds() > 500)	//windows系统中默认的双击间隔时间就是500毫秒
			{
				std::cout << "Mouse::Left Pressed" << std::endl;
			}
			else
			{
				std::cout << "Mouse::Left Double Clicked" << std::endl;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			mouseClickTimer.restart();
			std::cout << "Mouse::Left Released" << std::endl;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "Mouse::Right Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;
		}

	}
}

void Game::Logic() {

}

void Game::Draw() {

}

void Game::Run() {
	do
	{
		Initial();
		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();
		}
	} while (!gameQuit);
}