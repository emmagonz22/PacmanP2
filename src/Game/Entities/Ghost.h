#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityManager.h"

//enum to determine the facing of the ghost
enum GHOST_FACING
{
    UP_GHOST,
    DOWN_GHOST,
    LEFT_GHOST,
    RIGHT_GHOST,
};
//enum to determine the color of the ghost
enum COLOR //!--------------
{
    RED,
    BLUE,
    PINK,
    ORANGE,
    EAT
};

class Ghost : public Entity
{
private:
    int cropY, cropX;
    int speed = 1; //Speed can be incresed here
    int ghostFacing = UP_GHOST;
    bool canMoveGhost = true;
    COLOR color; //!--------------

public:
    Ghost(int, int, int, int, ofImage);
    Ghost();                                                               //default ghost constructor
    Ghost(int, int, int, int, ofImage, int cropX, int cropY, COLOR color); //constructor include sprite sheet
    //^---ghostWalking animation---^//
    Animation *ghostWalkDown;
    Animation *ghostWalkUp;
    Animation *ghostWalkLeft;
    Animation *ghostWalkRight;
    Animation *ghostEat;
    Animation *ghostEatGray;
    //^---ghostWalking animation---^//
    void checkCollisionsGhost(vector<Block *> b);
    void setFacingGhost(int);
    void tick();
    //*--Getter and Setter of Ghost--*//
    int getX() { return x; }
    int getY() { return y; }
    void setColor(COLOR c) { color = c; }
    void setX(int nx) { x = nx; }
    void setY(int ny) { y = ny; }
    void setCropX(int cx) { cropX = cx; }
    void setCropY(int cy) { cropY = cy; }
    void setCanMoveGhost(bool canMove) { this->canMoveGhost = canMove; }
    void setRandomFacing();
    int getGhostFacing() { return ghostFacing; }
    std::string getColor() //!--------------
    {
        if (this->color == EAT)
        {
            return "EAT";
        }
        else
        {
            return "Primary colors";
        }
    }
    //*--Getter and Setter of Ghost--*//
    bool canEatGhost = false;
    int grayCounter = 0; //!--------------
    int getFacing() { return ghostFacing; }
    COLOR originalColor;
};
