#pragma once
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>

class Game
{
public:
	sf::RenderWindow window;

	Game();
	~Game();

	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;

	//鼠标点击计时器（用于判断单击双击）
	sf::Clock mouseClickTimer;

	void Initial();
	void Input();
	void Logic();
	void Draw();
	void Run();
};

