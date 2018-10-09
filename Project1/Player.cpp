#include "Player.h"

#define CONSOLE_DEBUG 1
Player::Player(const std::string F, float X, float Y, float W, float H)
{
	File = F;//��� �����+����������
	w = W; h = H;//������ � ������
	image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
	image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	x = X; y = Y;//���������� ��������� �������
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
	sprite.setPosition(x, y);
}

void Player::interactionWithMap()
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (dy > 0)
				{
					y = i * 32 - h;
				}
				if (dy < 0)
				{
					y = i * 32 + 32;
				}
				if (dx > 0)
				{
					x = j * 32 - w;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
				}
			}
			if (TileMap[i][j] == 's')
			{
				x = 300; y = 300;
				TileMap[i][j] = ' ';
			}
		}
}

void Player::update(float time)
{
	switch (direction)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT: dx = speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT: dx = -speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN: dx = 0; dy = speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP: dx = 0; dy = -speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}
	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	y += dy*time;//���������� �� ������
	if (x < 0) x = 0; // �������� ������
	if (y < 0) y = 0;
	if (x > 1183) x = 1183;
	if (y > 675) y = 675;
	//if (x > 600) x = 0;
	//if (y > 300) y = 0;
	speed = 0; //�������� ��������, ����� �������� �����������.
#if CONSOLE_DEBUG == 1
	std::cout << "position of player = " << x << ' ' << y << std::endl;
#endif // CONSOLE_DEBUG
	sprite.setPosition(x,y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	//interactionWithMap();
}

Player::~Player()
{
}

