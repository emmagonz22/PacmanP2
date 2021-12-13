#include "GhostSpawner.h"

GhostSpawner::GhostSpawner(int centerX, int centerY) : Entity(centerX, centerY, width, height)
{
    sprite.load("images/Background.png");
    Ghost *redGhost = new Ghost(centerX, centerY + 20, 14, 14, sprite, 456, 64, RED);
    Ghost *blueGhost = new Ghost(centerX, centerY + 20, 14, 14, sprite, 456, 96, BLUE);
    Ghost *pinkGhost = new Ghost(centerX, centerY + 20, 14, 14, sprite, 456, 80, PINK);
    Ghost *orangeGhost = new Ghost(centerX, centerY + 20, 14, 14, sprite, 456, 112, ORANGE);
    //First ghost of the game
    ghostManager.push_back(redGhost);
    ghostManager.push_back(blueGhost);
    ghostManager.push_back(pinkGhost);
    ghostManager.push_back(orangeGhost);
}
