#include "Player.h"

#define CONSOLE_DEBUG 1
Player::Player(const std::string F, float X, float Y, float W, float H)
{
	File = F;//имя файла+расширение
	w = W; h = H;//высота и ширина
	image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
	image.createMaskFromColor(sf::Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	x = X; y = Y;//координата появления спрайта
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
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
	switch (direction)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT: dx = speed; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT: dx = -speed; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN: dx = 0; dy = speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP: dx = 0; dy = -speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}
	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	y += dy*time;//аналогично по игреку
	if (x < 0) x = 0; // Проверка границ
	if (y < 0) y = 0;
	if (x > 1183) x = 1183;
	if (y > 675) y = 675;
	//if (x > 600) x = 0;
	//if (y > 300) y = 0;
	speed = 0; //зануляем скорость, чтобы персонаж остановился.
#if CONSOLE_DEBUG == 1
	std::cout << "position of player = " << x << ' ' << y << std::endl;
#endif // CONSOLE_DEBUG
	sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	//interactionWithMap();
}

Player::~Player()
{
}

