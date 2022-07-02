#pragma once
/**
 * mainwindow.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "wall.h"
#include <fstream>
#include <iostream>
#include <string>

class MapCreator {
  public:
    MapCreator() = default;
    MapCreator(const std::string&);

    void setFile(const std::string&);

    void CreateMap(QGraphicsScene *scene);

  private:
    std::string file_name;
};

#endif // MAP_CREATOR_H
