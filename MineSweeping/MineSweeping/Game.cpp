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
	window.setFramerateLimit(60);	//������Ϸ֡��

	gameOver = false;
	gameQuit = false;
}

void Game::Input() {
	sf::Event event;	//event types����Window��Keyboard��Mouse��Joystick������Ϣ
						//ͨ��bool Window::pollEvent(sf::Event&event)�Ӵ���˳��ѯ�ʣ�polled���¼�
						//�����һ���¼��ȴ������ú���������true������ʱ���������䣨filled���¼�����
						//������ǣ���ú�������false��ͬ����Ҫ����Ҫע�⣬һ�ο����ж���¼���������Ǳ���ȷ������ÿһ���¼�
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
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (mouseClickTimer.getElapsedTime().asMilliseconds() > 500)	//windowsϵͳ��Ĭ�ϵ�˫�����ʱ�����500����
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