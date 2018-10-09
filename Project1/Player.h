#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player { // класс Игрока
public:
	Player(const std::string &path, const double &posX, const double &posY, const double &player_width, const double &player_height);
	~Player();
	sf::Sprite sprite;
	enum directions { LEFT, RIGHT, UP, DOWN } direction; // Направление путей(Исключен путь по диагонали)
	void update(double time);
	double GetX() { return positionX; }
	double GetY() { return positionY; }
	void SetX(double x) { positionX = x; }
	void SetY(double y) { positionY = y; }
	void SetSpeed(double speed) { this->speed = speed; }
	double GetWidth() { return width; }
	double GetHeight() { return height; }
	double GetSpeed() { return this->speed; }
	int countStones = 0;
	double dx, dy; // перемещение по x и y координатам
private:
	std::string image_path;
	sf::Image image;
	sf::Texture texture;
	double positionX, positionY; //Позиция игрока
	double width, height; //высота и ширина спрайта игрока
	double speed = 0; // Скорость персонажа
};