#include "Player.h"
#include "globalvars.h"
#define CONSOLE_DEBUG 1


void Player::update(double time)
{
	switch (direction)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT: dx = speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT: dx = -speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN: dx = 0; dy = speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP: dx = 0; dy = -speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}
	positionX += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	positionY += dy*time;//���������� �� ������
	if (positionX < 0) positionX = 32; // �������� ������
	if (positionY < 0) positionY = 32;
	if (positionX > 1183) positionX = 1183; //����������� �����
	if (positionY > 675) positionY = 675; //����������� �����
	speed = 0; //�������� ��������, ����� �������� �����������.
	sprite.setPosition(positionX,positionY); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
}

Player::Player(const std::string & path, const double & posX, const double & posY, const double & player_width, const double & player_height)
{
	image_path = path;
	width = player_width;
	height = player_height;
	image.loadFromFile("images/" + image_path);
	image.createMaskFromColor(sf::Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	positionX = posX;
	positionY = posY;
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
	sprite.setPosition(positionX, positionY);
}

Player::~Player()
{

}

