/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// draw text "Hello, World !" with font file
// reference : https://riptutorial.com/sfml

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <cassert>

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{
    const unsigned int 	WIN_WIDTH = 600;
    const unsigned int 	WIN_HEIGHT = 360;
    const sf::String WIN_TITLE = "sfml: hello world";
    const sf::String SAMPLE_TEXT =  "Hello, World !";

    const std::string FONT_FILEPATH = (char *)"fonts/LiberationSans-Regular.ttf";

    sf::RenderWindow sfmlWin(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE);

    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile(FONT_FILEPATH)) {
        return EXIT_FAILURE;
    }

    sf::Text message(SAMPLE_TEXT, font);

    while (sfmlWin.isOpen()) {

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
            } // switch
        }  // while

        sfmlWin.clear();
        sfmlWin.draw(message);
        sfmlWin.display();
    } // while

    return EXIT_SUCCESS;
}

