#pragma once
#include<SFML/Graphics.hpp>

sf::View view;

sf::View GetPlayerCoordinateView(float x, float y)
{
	int tempX = x, tempY = y;
	if (x < 318) tempX = 320;
	if (y < 240) tempY = 240;
	if (y < 554) tempY = 554;

	view.setCenter(x + 100, y);
	return view;
}

sf::View ViewMap(float time) // функция для перемещения камеры за время
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
		view.zoom(1.0006f);//Масштабируем, уменьшение.
	//view zoom 1.0006f медленнее
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		view.rotate(1); // вращает
	// setRotation - сразу поворачивает
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		view.setSize(640, 480);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		view.setSize(540, 380);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1)); // экран для двоих. нужно сделать еще один объект view и привязаться в нему
	return view;
}