/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// draw pixcels from memory
// reference : https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
// reference : https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php
// reference : https://stackoverflow.com/questions/18805206/sfml-drawing-pixel-array

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System/String.hpp>

#include "pixels.h"

using namespace std;

/**
 * main
 */
int main(int argc, char** argv)
{
    const unsigned int 	WIN_WIDTH = 250;
    const unsigned int 	WIN_HEIGHT = 250;
    const sf::String WIN_TITLE = "sfml: pixels";

    // 128 x 128
    int size = 4;
    int scale = 32;

    if (argc > 2) {
        size = atoi(argv[1]);
        scale = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] <<  " [size] [scale] "  << endl;
    }

    // image size
    int width = size * scale;
    int height = size * scale;

sf::Texture texture;
texture.create(width, height);

    // create Pixel
    char *pixels = 
        createColorMatrixPixel32(size, scale);

    texture.update( (sf::Uint8*)pixels );

    sf::Sprite sprite;
    sprite.setTexture(texture);

// draw center
    float x = (WIN_WIDTH/2) - (width /2);
    float y = (WIN_HEIGHT/2) - (height/2);
    sprite.setPosition(x, y);

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE);


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

