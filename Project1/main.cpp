#include <SFML/Graphics.hpp>
//#include <windows.h>
//#include <iostream>
#include "Player.h"
#include "view.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "LTITLE");
	view.reset(sf::FloatRect(0, 0, 640, 480)); // RAZMER VIDA KAMERI
	float CurrentFrame = 0;//хранит текущий кадр анимации
	sf::Clock clock;
	sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/Gamemap.png");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	Player p("hero.png", 250, 250, 96.0, 96.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
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
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			p.direction = Player::directions::LEFT; p.speed = speed;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame = 0;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
			p.direction = p.directions::RIGHT; p.speed = speed;//направление вправо, см выше
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
			p.direction = Player::directions::UP; p.speed = speed;//направление вниз, см выше
			CurrentFrame += accelerationPlayerAnimation *time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			//GetPlayerCoordinateView(p.x, p.y);
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
			p.direction = Player::directions::DOWN; p.speed = speed;//направление вверх, см выше
			CurrentFrame += accelerationPlayerAnimation *time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			p.sprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		}
		GetPlayerCoordinateView(p.x, p.y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		//p.interactionWithMap();
		ViewMap(time);
		ChangeView();
		window.setView(view);
					   /////////////////////////////Рисуем карту/////////////////////
		window.clear(sf::Color(128,106,89));
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
				if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}



		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		window.display();
	}

	return 0;
}