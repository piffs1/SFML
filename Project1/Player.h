#pragma once

#include <SFML/Graphics.hpp>
#include "globalvars.h"
#include <iostream>

class Player { // ����� ������
public:
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	enum directions { LEFT, RIGHT, UP, DOWN } direction;
	std::string File; //���� � �����������
	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������
	void update(float time);
	Player(const std::string F, const float X,const float Y,const float W,const float H);
	void interactionWithMap(); //�������������� � ������

	~Player();
};