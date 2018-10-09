#include <SFML/Graphics.hpp>
//#include <windows.h>
//#include <iostream>
#include "Player.h"
#include "view.h"
#include <sstream>
static sf::String TileMap[HEIGHT_MAP] = {  // ����� ����
   "0000000000000000000000000000000000000000",
   "0                                      0",
   "0   sss                           000000",
   "0                                 0    0",
   "0                ss               0    0",
   "0                ss               0    0",
   "0                                 000000",
   "0               s                      0",
   "0              s                       0",
   "0              s s                     0",
   "0               s                      0",
   "0                s                     0",
   "0              s                       0",
   "0                s                     0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0                                      0",
   "0000000000000000000000000000000000000000",
};  // ����� ����
extern double accelerationPlayerAnimation;
void interactionWithMap(Player &p); //�������������� ������ � ������

int main()
{
	setlocale(0, ""); 
	sf::Font font; 
	font.loadFromFile("fonts/12417.ttf");
	sf::Text text("", font, 20); // sf::Text(text, font, size of font)
	text.setFillColor(sf::Color::Red); //setColor �������
	text.setStyle(sf::Text::Bold);
	sf::RenderWindow window(sf::VideoMode(640, 480), "LTITLE");
	view.reset(sf::FloatRect(0, 0, 640, 480)); // ������ ���� ������
	double currentFrame = 0; // ������ ���� ������� ��������
	sf::Clock clock;
	sf::Image map_image;
	map_image.loadFromFile("images/Gamemap.png");//��������� ���� ��� �����
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	Player p("hero.png", 300, 300, 96.0, 96.0);  //player(pathimage, ��������� ����������, ������ � ������)
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			p.direction = Player::directions::LEFT; p.SetSpeed(speed);//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 96, 96, 96)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
			p.direction = p.directions::RIGHT; p.SetSpeed(speed);//����������� ������, �� ����
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 192, 96, 96));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
			p.direction = Player::directions::UP; p.SetSpeed(speed);//����������� ����, �� ����
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 288, 96, 96));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
			p.direction = Player::directions::DOWN; p.SetSpeed(speed);//����������� �����, �� ����
			currentFrame += accelerationPlayerAnimation *time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (currentFrame > 3) currentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 0, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			p.SetSpeed(speed*2); //�������� ���������
			//accelerationPlayerAnimation *= 2;
		}
		
		//accelerationPlayerAnimation = 0.005;
		GetPlayerCoordinateView(p.GetX(), p.GetY());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		p.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		interactionWithMap(p); //�������������� ������ � ������
		ViewMap(time);
		ChangeView(); // ���������� �������
		window.setView(view);
					   /////////////////////////////������ �����/////////////////////
		window.clear(sf::Color(128,106,89));
		for (int i = 0; i < HEIGHT_MAP; i++) 
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  map_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
				if (TileMap[i][j] == 's')  map_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
				if (TileMap[i][j] == '0') map_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
				map_sprite.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(map_sprite);//������ ���������� �� �����
			}
		std::ostringstream playerStoneScoreString;
		playerStoneScoreString << p.countStones;
		text.setString("COUNT STONES " + playerStoneScoreString.str()); // set text
		text.setPosition(view.getCenter().x + 165, view.getCenter().y - 200);
		window.draw(p.sprite);//������ ������ ������� p ������ player
		window.draw(text);
		window.display();
	}

	return 0;
}

void interactionWithMap(Player &p)
{
	for (int i = p.GetY() / 32; i < (p.GetY() + p.GetHeight()) / 32; i++)
		for (int j = p.GetX() / 32; j < (p.GetX() + p.GetWidth()) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (p.dy > 0)
				{
					p.SetY(i * 32 - p.GetHeight());
				}
				if (p.dy < 0)
				{
					p.SetY(i * 32 + 32);
				}
				if (p.dx > 0)
				{
					p.SetX(j * 32 - p.GetWidth());
				}
				if (p.dx < 0)
				{
					p.SetX(j * 32 + 32);
				}
			}
			if (TileMap[i][j] == 's') // catch stone
			{
				//p.positionX = 300; p.positionY = 300;
#if CONSOLE_DEBUG == 1
				std::cout << "������ ��� ����" << std::endl;
#endif // CONSOLE_DEBUG
				p.countStones++;
				TileMap[i][j] = ' ';
			}
		}
}