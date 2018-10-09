#pragma once
#include<SFML/Graphics.hpp>
#include "globalvars.h"
sf::View view;
extern double speed;
sf::View GetPlayerCoordinateView(double x, double y) // ������� ������ ������ �� ����������� ������
{
	view.setCenter(x + 100, y);
	return view;
}

sf::View ViewMap(double time) // ����������� ������
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(speed*time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(-speed*time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(0, speed*time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0, -speed*time);
	}
	return view;
}
sf::View ChangeView()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		view.zoom(1.0006f);//������������, ����������.
	//view zoom 1.0006f ���������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		view.rotate(1); // �������
	// setRotation - ����� ������������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		view.setSize(640, 480);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		view.setSize(540, 380);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1)); // ����� ��� �����. ����� ������� ��� ���� ������ view � ����������� � ����
	return view;
}