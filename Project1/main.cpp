#include <SFML/Graphics.hpp>
//#include <windows.h>
//#include <iostream>
#include "Player.h"
#include "view.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "LTITLE");
	view.reset(sf::FloatRect(0, 0, 640, 480)); // RAZMER VIDA KAMERI
	float CurrentFrame = 0;//������ ������� ���� ��������
	sf::Clock clock;
	sf::Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/Gamemap.png");//��������� ���� ��� �����
	sf::Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	sf::Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������
	Player p("hero.png", 250, 250, 96.0, 96.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

#if CONSOLE_DEBUG == 1
		std::cout << "time is " << time << std::endl;
#endif // CONSOLE_DEBUG
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// set/get playerclass
		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			p.direction = Player::directions::LEFT; p.speed = speed;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
			p.direction = p.directions::RIGHT; p.speed = speed;//����������� ������, �� ����
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
			p.direction = Player::directions::UP; p.speed = speed;//����������� ����, �� ����
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
			p.direction = Player::directions::DOWN; p.speed = speed;//����������� �����, �� ����
			CurrentFrame += accelerationPlayerAnimation *time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
		}
		GetPlayerCoordinateView(p.x, p.y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		p.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		//p.interactionWithMap();
		ViewMap(time);
		ChangeView();
		window.setView(view);
					   /////////////////////////////������ �����/////////////////////
		window.clear(sf::Color(128,106,89));
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������


				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}



		window.draw(p.sprite);//������ ������ ������� p ������ player
		window.display();
	}

	return 0;
}