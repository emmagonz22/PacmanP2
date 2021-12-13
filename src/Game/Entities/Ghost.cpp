#include "Ghost.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, int cropSpriteX, int cropSpriteY, COLOR color) : Entity(x, y, width, height)
{

    cropX = cropSpriteX;
    cropY = cropSpriteY;
    this->color = color;
    this->originalColor = color;
    sprite.cropFrom(spriteSheet, cropSpriteX, cropSpriteY, 16, 16);
    //creates a vector of images to form the animation for the movement depending on the color of the ghost
    vector<ofImage> downGhostAnimframes;
    vector<ofImage> upGhostAnimframes;
    vector<ofImage> leftGhostAnimframes;
    vector<ofImage> rightGhostAnimframes;
    vector<ofImage> blueEatGhost;
    vector<ofImage> grayEatGhost;
    ofImage temp;
    int yPosCrop;
    const int xPosCrop = 457;
    //determine the initial y position that will be used in the crop of the sprite depending on the color of ghost
    switch (color)
    {
    case RED:
        yPosCrop = 65;
        break;
    case BLUE:
        yPosCrop = 97;
        break;
    case PINK:
        yPosCrop = 81;
        break;
    case ORANGE:
        yPosCrop = 113;
        break;
    case EAT: //!--------------
        canEatGhost = true;
        break;
    }
    for (int k = 0; k < 4; k++) //The edible dark blue Ghost and gray
    {
        temp.cropFrom(spriteSheet, k * 16 + 584, 65, 16, 16);
        blueEatGhost.push_back(temp);
    }
    //for loops to capture the crops used in the movement animation

    for (int i = 0; i < 2; i++) //Ghost will depend on yPosCrop
    {
        temp.cropFrom(spriteSheet, i * 16 + xPosCrop + 96, yPosCrop, 16, 16);
        downGhostAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(spriteSheet, i * 16 + xPosCrop + 64, yPosCrop, 16, 16);
        upGhostAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(spriteSheet, i * 16 + xPosCrop + 32, yPosCrop, 16, 16);
        leftGhostAnimframes.push_back(temp);
    }
    for (int i = 0; i < 2; i++)
    {
        temp.cropFrom(spriteSheet, i * 16 + xPosCrop, yPosCrop, 16, 16);
        rightGhostAnimframes.push_back(temp);
    }

    //initializes the animation for each of the directions
    ghostEat = new Animation(1, blueEatGhost);
    ghostEatGray = new Animation(1, grayEatGhost);
    ghostWalkDown = new Animation(1, downGhostAnimframes);
    ghostWalkUp = new Animation(1, upGhostAnimframes);
    ghostWalkLeft = new Animation(1, leftGhostAnimframes);
    ghostWalkRight = new Animation(1, rightGhostAnimframes);
}
void Ghost::checkCollisionsGhost(vector<Block *> blocks)
{
    //iterates through every element in the block vector to stop the ghost if it collides with a wall
    for (Block *b : blocks)
    {
        switch (ghostFacing)
        {
        case UP_GHOST:
            if (this->getBounds(x, y - speed).intersects(b->getBounds()))
            {
                canMoveGhost = false;
                this->setRandomFacing();
            }
            break;
        case DOWN_GHOST:
            if (this->getBounds(x, y + speed).intersects(b->getBounds()))
            {
                canMoveGhost = false;
                this->setRandomFacing();
            }
            break;
        case LEFT_GHOST:
            if (this->getBounds(x - speed, y).intersects(b->getBounds()))
            {
                canMoveGhost = false;
                this->setRandomFacing();
            }
            break;
        case RIGHT_GHOST:
            if (this->getBounds(x + speed, y).intersects(b->getBounds()))
            {
                canMoveGhost = false;
                this->setRandomFacing();
            }
            break;
        }
    }
}

void Ghost::tick()
{
    grayCounter++;
    //makes posible the movement of the ghost depending on the facing of the ghost
    //by adding the speed value to the corresponding position
    canMoveGhost = true;
    if (canMoveGhost)
    {
        if (!canEatGhost)
        {
            //& Ghost's non edible sprite
            if (ghostFacing == UP_GHOST)
            {
                y -= speed;
                ghostWalkUp->tick();
            }
            else if (ghostFacing == DOWN_GHOST)
            {
                y += speed;
                ghostWalkDown->tick();
            }
            else if (ghostFacing == LEFT_GHOST)
            {
                x -= speed;
                ghostWalkLeft->tick();
            }
            else if (ghostFacing == RIGHT_GHOST)
            {
                x += speed;
                ghostWalkRight->tick();
            }
        }
        else
        { //& Ghost's edible sprite
            if (ghostFacing == UP_GHOST)
            {
                y -= speed;
            }
            else if (ghostFacing == DOWN_GHOST)
            {
                y += speed;
            }
            else if (ghostFacing == LEFT_GHOST)
            {
                x -= speed;
            }
            else if (ghostFacing == RIGHT_GHOST)
            {
                x += speed;
            }
        }
    }
}
void Ghost::setFacingGhost(int ghostFacing) //change ghostFacing
{
    this->ghostFacing = ghostFacing;
}
void Ghost::setRandomFacing()
{
    this->canMoveGhost = false;
    int newface;
    while (true)
    {

        //determines a random direction to assign the ghost a new direction once it collides with a wall
        //it utilizes integer value since direction is represented by an Enum
        //Collision with corner
        newface = static_cast<int>(ofRandom(0, 4));
        if (this->getX() < 233 && this->getX() > 216 && this->getY() > 81 && this->getY() < 97) //Upper left
        {
            if (newface == 0 || newface == 2)
            {
                continue;
            }
        }
        if (this->getX() < 804 && this->getX() > 789 && this->getY() > 675 && this->getY() < 682) //Upper right
        {
            if (newface == 0 || newface == 3)
            {
                continue;
            }
        }
        if (this->getX() < 233 && this->getX() > 217 && this->getY() > 665 && this->getY() < 684) //Down Left
        {
            if (newface == 1 || newface == 2)
            {
                continue;
            }
        }
        if (this->getX() < 804 && this->getX() > 789 && this->getY() > 682 && this->getY() < 675) //Down right
        {
            if (newface == 1 || newface == 3)
            {
                continue;
            }
        }

        if (this->ghostFacing == newface)
            continue;

        //if a ghost is near the spawning zone it will no be allowed to go down
        if (this->getX() < 520 && this->getX() > 502 && this->getY() > 313 && this->getY() < 334)
        {
            if (newface == 1)
            {
                continue;
            }
        }
        this->ghostFacing = newface;
        break;
    }
}
//UP is 0
//DOWN is 1
//LEFT is 2
//RIGHT is 3
