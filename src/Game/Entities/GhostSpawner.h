#pragma once
#include "Entity.h"
#include "Ghost.h"
class GhostSpawner : public Entity
{
private:

    int cropX = 0;
    int cropY = 0;
    int width, height;

public:
    std::vector<Ghost *> ghostManager; //Vector Ghost
    GhostSpawner(int centerX, int centerY);
    //^Ghost that can be added^//
    void addPink()//This will add a pink Ghost to vector
    {
        Ghost *pinkGhost = new Ghost(505, 360 + 20, 13, 13, sprite, 456, 80, PINK);
        ghostManager.push_back(pinkGhost);
    }
        void addOrange()//This will add a red Ghost to vector
    {
        Ghost *orangeGhost = new Ghost(505, 360 + 20, 13, 13, sprite, 456, 112, ORANGE);
        ghostManager.push_back(orangeGhost);
    }
        void addBlue() //This will add a red Ghost to vector
    {
        Ghost *blueGhost = new Ghost(505, 360 + 20, 13, 13, sprite, 456, 96, BLUE);
        ghostManager.push_back(blueGhost);
    }
    void addRed() //This will add a red Ghost to vector
    {
        Ghost *redGhost = new Ghost(505, 360 + 20, 13, 13, sprite, 456, 64, RED);
        ghostManager.push_back(redGhost);
    }
};
