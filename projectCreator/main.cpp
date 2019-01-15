#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;



int main()
{
    RenderWindow app(VideoMode(800,600),"My application");
    while(app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        auto mouse_world = app.mapPixelToCoords(sf::Mouse::getPosition(app));
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            app.close();
        }
        app.clear();
        app.display();
    }
    return 0;
}
