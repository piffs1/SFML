/*My realisation algorithm Lee. Graphic version */


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
/*
* Программа находит кратчайший путь между двумя точками.
* Управление:
* Чтобы построить препятствие необходимо навести курсор на ячейку и нажать ЛКМ.
* Чтоы удалить препятствие ПКМ.
* Чтобы установить начальную точку алгоритма необходимо навести курсор на необходимую ячейку
* и нажать кнопку B(английскую)
* Чтобы установить конечную точку алгоритма, кнопка Е(английская)
* Чтобы построить путь нажать кнопку S.
* Чтобы очистить карту полностью нажать кнопку R.
* Чтобы очистить карту без удаления стен и начальной точки кнопка C.
*/

// ПРОБЛЕМЫ:
// Если производится удаление ЛКМ или ПКМ начального и конечного пункта, то переменная
// startExist и endExist не меняется, из-за чгео могут возникнуть ошибки в построении путей
// ДОБАВИТЬ ОБНОВЛЕНИЕ ВОЛНЫ ПО ТАЙМЕРУ
const int widthOfBorder = 1;
const int sizeOfRectangleShape = 15;
const int windowWidth = 800;
const int windowHeight = 620;
const int sizeSquareWithBorders = widthOfBorder*2+sizeOfRectangleShape;
const int countSquaresX = (windowWidth-sizeSquareWithBorders) /(sizeSquareWithBorders-widthOfBorder); // (800 - 20) / 15 = countSquares
const int countSquaresY = (windowHeight-sizeSquareWithBorders) /(sizeSquareWithBorders-widthOfBorder);
///////////////////////
int adjacencyMatrix[countSquaresY+1][countSquaresX+1]; // Матрица смежности, по которой мы и будем считать
const int BLANK = -2;
const int WALL = -1;
const unsigned short int countDirections = 8; // смещения вправо, вниз, влево, вверх
// по диагонали вверх влево, вверх вправо, вниз влево, вниз вправо
int dx[countDirections] = {1, 0, -1, 0, -1, 1, -1, 1};   // смещения, соответствующие соседям ячейки
int dy[countDirections] = {0, 1, 0, -1, -1, -1, 1, 1};   // справа, снизу, слева и сверху
/////////////////////////////
//directions right, down, left, up, left up, right up, down left, down right.
///////////////////////
// рамки нового квадрата накладываются на правую рамку старого квадрата.
// Первый квадрат кладется полностью(поэтому windowWidth - sizeSquareWithBorders)
// делится на квадрат без одной рамки, поэтому вычитается одна граница
sf::Vector2i startPosition;
sf::Vector2i endPosition;
sf::RectangleShape rectangles[countSquaresY+1][countSquaresX+1];
///////////////////Задаем цвета для нашей визуализации/////////////////
const sf::Color backgroundColor = sf::Color(185,217,234);
const sf::Color cellOutline = sf::Color(123,123,123);
const sf::Color cellBeginColor = sf::Color(70,130,180);
const sf::Color cellEndColor = sf::Color(255,69,0);
const sf::Color wallColor = sf::Color(0,0,0);
const sf::Color waveColor = sf::Color(0,117,57);
const sf::Color wayColor = sf::Color(190,245,116);

using namespace std;
using namespace sf;


vector<int> px;
vector<int> py;


bool lee()   // поиск пути из ячейки (ax, ay) в ячейку (bx, by). From ax,ay to bx,by.
{

  bool stop;
  int ax = startPosition.x;
  int ay = startPosition.y;
  int bx = endPosition.x;
  int by = endPosition.y;
  if (adjacencyMatrix[ay][ax] == WALL || adjacencyMatrix[by][bx] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена. If start cell of finish cell is a wall

  // распространение волны
  // wave begins
  int d = 0; // level wave
  adjacencyMatrix[ay][ax] = 0;            // стартовая ячейка помечена 0. Start cell[ay][ax] = 0;
  do {
    stop = true;               // предполагаем, что все свободные клетки уже помечены
    for (int y = 0; y <= countSquaresY; ++y ) // каждый раз ищем наши d уровни, чтобы не потерять пути.
      for (int x = 0; x <= countSquaresX; ++x )
        if ( adjacencyMatrix[y][x] == d ) // current level wave(d)
        {
          for (int k = 0; k < countDirections; ++k )                    // проходим по всем непомеченным соседям
          {
             int iy=y + dy[k], ix = x + dx[k];
             if ( iy >= 0 && iy < countSquaresY && ix >= 0 && ix < countSquaresX &&
                  adjacencyMatrix[iy][ix] == BLANK ) // check borders and free cell == BLANK
             {
                stop = false;              // найдены непомеченные клетки . Find untagged cells
                adjacencyMatrix[iy][ix] = d + 1;      // increase wave
                rectangles[iy][ix].setFillColor(waveColor); // цвет волны
             }
          }
        }
    d++;
  } while ( !stop && adjacencyMatrix[by][bx] == BLANK ); // grid[by][bx] == BLANK while wave dont take final cell

  if (adjacencyMatrix[by][bx] == BLANK) return false;  // путь не найден, тупиковая ситуация

  // восстановление пути
  int length = adjacencyMatrix[by][bx];
  px.resize(length);
  py.resize(length);
  cout << px.size();
  int x = bx;
  int y = by;
  d = length;
  while ( d > 0 )
  {
    px[d] = x;
    py[d] = y;
    rectangles[y][x].setFillColor(wayColor); // отрисовка пути
                       // записываем ячейку (x, y) в путь
    d--;
    for (int k = 0; k < countDirections; ++k)
    {
       int iy=y + dy[k], ix = x + dx[k];
       if ( iy >= 0 && iy <= countSquaresY && ix >= 0 && ix <= countSquaresX &&
            adjacencyMatrix[iy][ix] == d)
      {
          x = x + dx[k];
          y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
          break;
      }
    }
  }
  rectangles[by][bx].setFillColor(cellEndColor);
  px[0] = ax;
  py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути
  return true;
}

int main()
{
    // s - start. b - begin point e - end point
    //cout << countSquaresY << ' ' << countSquaresX << endl;
    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Grid");
    Font font;
    font.loadFromFile("fonts/arial.ttf");
    Text text("START",font,20);
    text.setColor(Color::Red);
    text.setPosition(12,12);
    bool startExist = false;
    bool endExist = false;
    for(int i = 0; i <= countSquaresY; i++)
    {
        for(int j = 0; j <= countSquaresX; j++)
        {
            rectangles[i][j].setSize(Vector2f(sizeOfRectangleShape,sizeOfRectangleShape));
            rectangles[i][j].setOutlineColor(cellOutline); // цвет рамки
            rectangles[i][j].setFillColor(backgroundColor); // Устанавливаем цвет квадратной матрицы
            rectangles[i][j].setOutlineThickness(widthOfBorder);
            rectangles[i][j].setPosition(widthOfBorder+sizeSquareWithBorders*j,widthOfBorder+sizeSquareWithBorders*i); //отступаем от границ сразу
            //Устанавливаем позицию (отступ от границ для х и у и отступ идет ДОПИСАТЬ
            adjacencyMatrix[i][j] = BLANK;
        }
    }
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            /*if(event.type == sf::Event::MouseButtonPressed)
                if(event.key.code == sf::Mouse::Left)
                {
                    sf::Vector2f mouse_world = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    cout << mouse_world.x << ' ' << mouse_world.y << endl;
                }*/
        }
        sf::Vector2f mouse_world = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //Отслеживание мыши
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ //Левая кнопка устанавливает стену

            if(mouse_world.x>0 && mouse_world.y>0 && mouse_world.x < windowWidth && mouse_world.y < windowHeight)
            {
                //cout << mouse_world.x << ' ' << mouse_world.y << endl;
                //cout << countSquaresY << ' ' << countSquaresX << endl;
                int j = int(mouse_world.x) / sizeSquareWithBorders;
                int i = int(mouse_world.y) / sizeSquareWithBorders;
                //cout << "[" << i << "][" << j << "]" << endl;
                rectangles[i][j].setFillColor(wallColor);
                adjacencyMatrix[i][j] = WALL;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){//Правая кнопка мыши ее стирает. Очищение карты
            if(mouse_world.x>0 && mouse_world.y>0 && mouse_world.x < windowWidth && mouse_world.y < windowHeight)
            {
                //cout << mouse_world.x << ' ' << mouse_world.y << endl;
                //cout << countSquaresY << ' ' << countSquaresX << endl;
                int j = int(mouse_world.x) / sizeSquareWithBorders;
                int i = int(mouse_world.y) / sizeSquareWithBorders;
                //cout << "[" << i << "][" << j << "]" << adjacencyMatrix[i][j] << endl;
                rectangles[i][j].setFillColor(backgroundColor);
                adjacencyMatrix[i][j] = BLANK;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            if(mouse_world.x>0 && mouse_world.y>0 && mouse_world.x < windowWidth && mouse_world.y < windowHeight){
                int j = int(mouse_world.x) / sizeSquareWithBorders;
                int i = int(mouse_world.y) / sizeSquareWithBorders;
                if(!startExist){ //Если стартовой точки не существует, то рисуем...
                    adjacencyMatrix[i][j] = 0;
                    rectangles[i][j].setFillColor(cellBeginColor);
                    startPosition.x = j;
                    startPosition.y = i;
                    startExist = true;
                }
                else
                {
                    // обновляем старт. Старую стартовую позицию закрашиваем белым цветом
                    // и обновляем матрицу смежности на значение BLANK.
                    if(!(startPosition.x == j && startPosition.y == i))
                    {
                        rectangles[startPosition.y][startPosition.x].setFillColor(backgroundColor);
                        adjacencyMatrix[startPosition.y][startPosition.x] = BLANK; //
                        startPosition.x = j;
                        startPosition.y = i;
                        adjacencyMatrix[i][j] = 0;
                        rectangles[i][j].setFillColor(cellBeginColor); //blue
                    }
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if(mouse_world.x>0 && mouse_world.y>0 && mouse_world.x < windowWidth && mouse_world.y < windowHeight){
                int j = int(mouse_world.x) / sizeSquareWithBorders;
                int i = int(mouse_world.y) / sizeSquareWithBorders;
                if(!endExist){ //Если стартовой точки не существует, то рисуем...
                    rectangles[i][j].setFillColor(cellEndColor);
                    endPosition.x = j;
                    endPosition.y = i;
                    endExist = true;
                }
                else
                {
                    // обновляем старт. Старую стартовую позицию закрашиваем белым цветом
                    // и обновляем матрицу смежности на значение BLANK.
                    rectangles[endPosition.y][endPosition.x].setFillColor(backgroundColor);
                    adjacencyMatrix[endPosition.y][endPosition.x] = BLANK; // Обновляем матрицу старую
                    endPosition.x = j;
                    endPosition.y = i;
                    rectangles[i][j].setFillColor(cellEndColor); //orange
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(startExist && endExist)
                if(lee()) cout << "PATH FOUNDED " << endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // clear matrix
        {
            for(int i = 0; i <= countSquaresY;i++)
            {
                for(int j = 0; j <=countSquaresX;j++)
                {
                    adjacencyMatrix[i][j] = BLANK;
                    rectangles[i][j].setFillColor(backgroundColor);
                }
            }
            startExist = false;
            endExist = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) //debugging value
        {
            int j = int(mouse_world.x) / sizeSquareWithBorders;
            int i = int(mouse_world.y) / sizeSquareWithBorders;
            cout << "VALUE[" << i << "][" << j << "] is " << adjacencyMatrix[i][j] << endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) //Очищение матрицы без очищения стен
        {
            for(int i = 0; i < countSquaresY; i++)
            {
                for(int j = 0; j < countSquaresX;j++)
                {
                    if(adjacencyMatrix[i][j]!=WALL)
                    {
                        adjacencyMatrix[i][j] = BLANK; //Очищаем матрицу от волн, пути и точек начала и конца
                        rectangles[i][j].setFillColor(backgroundColor);
                    }
                }
            }
            // Подрисовываем начальный и конечный пункт алгоритма
            if(startExist && endExist){
                rectangles[startPosition.y][startPosition.x].setFillColor(cellBeginColor);
                rectangles[endPosition.y][endPosition.x].setFillColor(cellEndColor);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //DEBUG BUTTON
            if(startExist) cout <<"start" << startPosition.x << ' ' << startPosition.y << endl;
            if(endExist) cout <<"end"<< endPosition.x << ' ' << endPosition.y << endl;
            cout << "MOUSE TRACK "<< mouse_world.x << ' ' << mouse_world.y << endl;
        }
        window.clear();
        //draw
        for(int i = 0; i <= countSquaresY; i++)
        {
            for(int j = 0; j <= countSquaresX;j++)
                window.draw(rectangles[i][j]);
        }
        //window.draw(text); //worked text
        //cout << windowHeight << '-' << 20 + (countSquaresY)*15<< '=' << windowHeight-(20 +countSquaresY*15) << endl;
        window.display();
    }


    return 0;
}
