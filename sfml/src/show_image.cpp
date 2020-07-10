/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// show image from file
// reference : https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "parse_filename.hpp"

using namespace std;

/**
 * main
 */
int main(int argc, char** argv)
{
    const unsigned int 	WIN_WIDTH = 500;
    const unsigned int 	WIN_HEIGHT = 500;

    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <imageFile> "  << endl;
        return EXIT_FAILURE;
    }

    char *input =  argv[1];

    string fname = getFileNameWithExt(input);
    sf::String win_title = "sfml: " + fname;

    sf::Texture texture;
    if (!texture.loadFromFile(input)) {
        cout << "loadFromFile faild: " <<  input << endl;
        return EXIT_FAILURE;
    }

    sf::Vector2u size = texture.getSize() ;
    unsigned int width = size.x;
    unsigned int height = size.y;
    cout << "loaded: " << input << " ( " << width << " x " << height << " )" << endl;

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), win_title);


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
        window.draw(sprite);
        window.display();
    } // while

    return EXIT_SUCCESS;
}

