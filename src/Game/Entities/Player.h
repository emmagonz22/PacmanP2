#pragma once
#include "Animation.h"
#include "Ghost.h"
#include "GhostSpawner.h"
#include "EntityManager.h"

enum FACING
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public Entity
{

private:
    int health = 3;
    int score = 0;
    bool canMove;
    int speed = 8;
    bool walking = false;
    FACING facing = DOWN;
    ofImage up, down, left, right;
    //Animation//
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    ofImage spriteBackground;
    EntityManager *em;
    bool isBigDot = false;
    int ghostDeadReferenceTime;
    bool isCreatingGhost = false;
    int ghostCountManager = 0;
    ofTrueTypeFont font;
    int bigDotReferenceTime;
    GhostSpawner *ghostSpawner;
    ofColor pacManColor = ofColor(255,255,0);

public:
    Player(int, int, int, int, EntityManager *);
    int getHealth() { return health; }
    virtual int getScore() { return score; }
    virtual void setScore(int s) { score = s; }
    void tick();
    void render();
    void keyPressed(int);
    void keyReleased(int);
    void damage(Entity *damageSource);
    void mousePressed(int, int, int);
    void reset();
    void setFacing(FACING facing);
    void checkCollisions();
    void die(); //This method will reduce pac-man life and return his initial position
    void addLife();
    void setHealth(int h) { health = h; }
    void pacManLife();
    const int quantityOfPacman = 24;
    void displayScore();
    void addGhost();
    void pacManCollisionGhost();
    void turnAllBlue(); //Change all ghost to blue
    ofSoundPlayer eatSound;
    void setGhostDeadReferenceTime(int time) { ghostDeadReferenceTime = time; }
    int getGhostDeadReferenceTime() { return ghostDeadReferenceTime; }
    void spawnGhostTime(); //Timer for respawn
    void setIsCreatingGhost(bool b) { isCreatingGhost = b; }
    bool getIsCreatingGhost() { return isCreatingGhost; }
    int ghostCounter = 4;
    int ghostCounterTotal = 4;
    void ghostMovement();
    void turnOffBigDot();
    void setGhostSpawner(GhostSpawner* gs){this->ghostSpawner = gs;}
    void removeGhost(int);
    void setPlayerColor(ofColor c){pacManColor = c;}
};