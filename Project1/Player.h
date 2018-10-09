#pragma once

#include <SFML/Graphics.hpp>
#include "globalvars.h"
#include <iostream>

class Player { // класс Игрока
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	enum directions { LEFT, RIGHT, UP, DOWN } direction;
	std::string File; //файл с расширением
	sf::Image image;//сфмл изображение
	sf::Texture texture;//сфмл текстура
	sf::Sprite sprite;//сфмл спрайт
	void update(float time);
	Player(const std::string F, const float X,const float Y,const float W,const float H);
	void interactionWithMap(); //Взаимодействие с картой

	~Player();
};