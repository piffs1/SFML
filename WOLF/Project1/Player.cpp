#include "Player.h"
#include "globalvars.h"
#define CONSOLE_DEBUG 1


void Player::update(double time)
{
	switch (direction)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}
	positionX += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	positionY += dy*time;//аналогично по игреку
	if (positionX < 0) positionX = 32; // Проверка границ
	if (positionY < 0) positionY = 32;
	if (positionX > 1183) positionX = 1183; //ограничения карты
	if (positionY > 675) positionY = 675; //ограничения карты
	speed = 0; //зануляем скорость, чтобы персонаж остановился.
	sprite.setPosition(positionX,positionY); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
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
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	sprite.setPosition(positionX, positionY);
}

Player::~Player()
{

}

