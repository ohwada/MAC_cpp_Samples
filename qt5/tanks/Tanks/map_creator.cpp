/**
 * map_creator.cpp
 * 2022-06-01 K.OHWADA
 */


// chang log
// 2022-06-01 K.OHWADA
// changed the coordinate origin to (0, 0)
// No correction by screen size

// original : https://github.com/magziim/Tanks

#include "map_creator.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>


/**
 * constractor
 */
MapCreator::MapCreator(const std::string& name_of_file) : file_name(name_of_file) 
{
     // none
}


/**
 * :setFile
 */
void MapCreator::setFile(const std::string& name_of_file) 
{
    file_name = name_of_file;
}


/**
 * CreateMap
 */
void MapCreator::CreateMap(QGraphicsScene *scene)
{

// wall size
const qreal WALL_SIZE = 51;

    std:: ifstream file(file_name);

    if (file.is_open())
    {
        int row = 0; // rows
        int col = 0; //columns
        int ch;

        while ((ch = file.get()) != EOF) //while file isn't ended
        {
            if ((char)ch == '\n') {
                ++row;
                col = 0;
            } else if ((char)ch != ' ') {
                ++col;
            }

            if (ch == '1') {

                Wall* wall = new Wall(scene);
                scene->addItem(wall);
                float x = (col - 1) * WALL_SIZE ;
                float y = row * WALL_SIZE + 1;
                wall->setPos(x, y);
            }
            /*
            else if (ch == '2') {

                Wall* wall = new Wall(scene);
                wall->is_box = 1;
                scene->addItem(wall);
                float x = (col - 1) * WALL_SIZE ;
                float y = -row * WALL_SIZE + 1;
                wall->setPos(x, y);
            }
            */
        }

        file.close();
    }
}
