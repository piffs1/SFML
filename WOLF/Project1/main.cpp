#include <SFML/Graphics.hpp>
//#include <windows.h>
//#include <iostream>
#include "Player.h"
#include "view.h"
#include <sstream>
static sf::String TileMap[HEIGHT_MAP] = {  // Карта игры
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
};  // Карта игры
extern double accelerationPlayerAnimation;
void interactionWithMap(Player &p); //Взаимодействие игрока с картой

int main()
{
	setlocale(0, ""); 
	sf::Font font; 
	font.loadFromFile("fonts/12417.ttf");
	sf::Text text("", font, 20); // sf::Text(text, font, size of font)
	text.setFillColor(sf::Color::Red); //setColor устарел
	text.setStyle(sf::Text::Bold);
	sf::RenderWindow window(sf::VideoMode(640, 480), "LTITLE");
	view.reset(sf::FloatRect(0, 0, 640, 480)); // размер вида камеры
	double currentFrame = 0; // хранит кадр текущей анимации
	sf::Clock clock;
	sf::Image map_image;
	map_image.loadFromFile("images/Gamemap.png");//загружаем файл для карты
	sf::Texture map_texture;
	map_texture.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	Player p("hero.png", 300, 300, 96.0, 96.0);  //player(pathimage, начальные координаты, высота и ширина)
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
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			p.direction = Player::directions::LEFT; p.SetSpeed(speed);//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame = 0;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 96, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
			p.direction = p.directions::RIGHT; p.SetSpeed(speed);//направление вправо, см выше
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 192, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
			p.direction = Player::directions::UP; p.SetSpeed(speed);//направление вниз, см выше
			currentFrame += accelerationPlayerAnimation *time;
			if (currentFrame > 3) currentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 288, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.positionX, p.positionY);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
			p.direction = Player::directions::DOWN; p.SetSpeed(speed);//направление вверх, см выше
			currentFrame += accelerationPlayerAnimation *time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 3) currentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			p.sprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			p.SetSpeed(speed*2); //Ускоряем персонажа
			//accelerationPlayerAnimation *= 2;
		}
		
		//accelerationPlayerAnimation = 0.005;
		GetPlayerCoordinateView(p.GetX(), p.GetY());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		interactionWithMap(p); //взаимодействие игрока с картой
		ViewMap(time);
		ChangeView(); // управление камерой
		window.setView(view);
					   /////////////////////////////Рисуем карту/////////////////////
		window.clear(sf::Color(128,106,89));
		for (int i = 0; i < HEIGHT_MAP; i++) 
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  map_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
				if (TileMap[i][j] == 's')  map_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
				if (TileMap[i][j] == '0') map_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
				map_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(map_sprite);//рисуем квадратики на экран
			}
		std::ostringstream playerStoneScoreString;
		playerStoneScoreString << p.countStones;
		text.setString("COUNT STONES " + playerStoneScoreString.str()); // set text
		text.setPosition(view.getCenter().x + 165, view.getCenter().y - 200);
		window.draw(p.sprite);//рисуем спрайт объекта p класса player
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
				std::cout << "Камень был взят" << std::endl;
#endif // CONSOLE_DEBUG
				p.countStones++;
				TileMap[i][j] = ' ';
			}
		}
}