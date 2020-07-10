/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// draw green circle
// reference : https://riptutorial.com/sfml

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System/String.hpp>


/**
 * printSfmlVersion
 */
void printSfmlVersion()
{
    printf("sfml version: %d.%d.%d \n", SFML_VERSION_MAJOR, SFML_VERSION_MINOR, SFML_VERSION_PATCH);
}


/**
 * main
 */
int main(int argc, char** argv)
{
    const unsigned int 	WIN_WIDTH = 200;
    const unsigned int 	WIN_HEIGHT = 200;
    const sf::String WIN_TITLE = "SFML works!";

    printSfmlVersion();
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        } // while

        window.clear();
        window.draw(shape);
        window.display();
    } // while

    return EXIT_SUCCESS;
}

