#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "GhostSpawner.h"

Player::Player(int x, int y, int width, int height, EntityManager *em) : Entity(x, y, width, height)
{
    font.load("font/pac.ttf", 8);
    spriteBackground.load("images/Background.png");
    sprite.load("images/pacman.png");
    eatSound.load("sounds/pacman_chomp_fast_2.wav");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);

    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1, downAnimframes);
    walkUp = new Animation(1, upAnimframes);
    walkLeft = new Animation(1, leftAnimframes);
    walkRight = new Animation(1, rightAnimframes);

    this->em = em;
    //&------------------------------------------

    //^------------------------------------------
    //create ghost spawner and add ghost to the entity list of player
    //***VERIFICAR COMMENT EN MAPBUILDER.CPP***
}
void Player::tick()
{
    for (int i = 0; i < ghostSpawner->ghostManager.size(); i++) //Check collision of the ghost soo it can move
    {
        ghostSpawner->ghostManager[i]->checkCollisionsGhost(em->blocks);
        ghostSpawner->ghostManager[i]->tick();
    }
    turnAllBlue(); //Change ghost to edible sprite "BLUE" if only if isBigDot is true
    canMove = true;
    checkCollisions();

    turnOffBigDot();
    spawnGhostTime(); //respawn ghost
    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
            walkUp->tick();
        }
        else if (facing == DOWN)
        {
            y += speed;
            walkDown->tick();
        }
        else if (facing == LEFT)
        {
            x -= speed;
            walkLeft->tick();
        }
        else if (facing == RIGHT)
        {
            x += speed;
            walkRight->tick();
        }
    }
}

void Player::render()
{
    displayScore();            //draw score
    pacManLife();              //draw pacman's life
    ofSetColor(256, 256, 256); // change color to white
    //
    //^^ Draw all the ghost ^^//
    for (int i = 0; i < ghostSpawner->ghostManager.size(); i++)
    {
        if (ghostSpawner->ghostManager[i]->getColor() != "EAT")
        {
            if (ghostSpawner->ghostManager[i]->getFacing() == 0)
            {
                ghostSpawner->ghostManager[i]->ghostWalkUp->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 1)
            {
                ghostSpawner->ghostManager[i]->ghostWalkDown->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 2)
            {
                ghostSpawner->ghostManager[i]->ghostWalkLeft->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 3)
            {
                ghostSpawner->ghostManager[i]->ghostWalkRight->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
            }
        }
        else //^^ Draw all the ghost when they are edible ^^//
        {
            if (ghostSpawner->ghostManager[i]->getFacing() == 0)
            {
                ghostSpawner->ghostManager[i]->ghostEat->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
                ghostSpawner->ghostManager[i]->ghostEat->tick();
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 1)
            {
                ghostSpawner->ghostManager[i]->ghostEat->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
                ghostSpawner->ghostManager[i]->ghostEat->tick();
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 2)
            {
                ghostSpawner->ghostManager[i]->ghostEat->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
                ghostSpawner->ghostManager[i]->ghostEat->tick();
            }
            else if (ghostSpawner->ghostManager[i]->getFacing() == 3)
            {
                ghostSpawner->ghostManager[i]->ghostEat->getCurrentFrame().draw(ghostSpawner->ghostManager[i]->getX(), ghostSpawner->ghostManager[i]->getY(), 16, 16);
                ghostSpawner->ghostManager[i]->ghostEat->tick();
            }
        }
    }

    // ofDrawRectangle(getBounds());

    ofSetColor(pacManColor);
    if (facing == UP)
    {
        walkUp->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == DOWN)
    {
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == LEFT)
    {
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }
    else if (facing == RIGHT)
    {
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    ofSetColor(255);
}

void Player::keyPressed(int key)
{
    switch (key)
    {
    case 'w': //Pacman go up
        setFacing(UP);
        break;
    case 's': //Pacman go down
        setFacing(DOWN);
        break;
    case 'a': //PAcman go left
        setFacing(LEFT);
        break;
    case 'd': //Pacman go right
        setFacing(RIGHT);
        break;
    case 'n': //decrease Health
        die();
        break;
    case 'm': //Increment Health
        addLife();
        break;
    case 'g':
        //adds ghost to the map when g is pressed
        //if (ghostCounterTotal == 8) //^Can be uncomented for a limit in how many ghost can spawn
        //  break;
        addGhost();
        break;
    }
}

void Player::keyReleased(int key)
{
    if (key == 'w' || key == 's' || key == 'a' || key == 'd')
    {
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button)
{
}

void Player::setFacing(FACING facing) //^Change pacman facing
{
    this->facing = facing;
}

void Player::checkCollisions() //^Check pacman collisions with block, ghost and entities
{
    for (Block *block : em->blocks)
    {
        switch (facing)
        {
        case UP:
            if (this->getBounds(x, y - speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case DOWN:
            if (this->getBounds(x, y + speed).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case LEFT:
            if (this->getBounds(x - speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        case RIGHT:
            if (this->getBounds(x + speed, y).intersects(block->getBounds()))
            {
                canMove = false;
            }
            break;
        }
    }
    for (Entity *entity : em->entities) //Iterate over entities and
    {
        if (collides(entity))
        {
            if (dynamic_cast<Dot *>(entity) || dynamic_cast<BigDot *>(entity))
            {
                if (dynamic_cast<Dot *>(entity))
                {
                    score = getScore() + 10; //adds 10pts for each small dot
                    eatSound.stop();
                    if (eatSound.isPlaying() == false)
                    {
                        eatSound.play();
                    }
                }
                else
                {
                    isBigDot = true;
                    bigDotReferenceTime = ofGetElapsedTimeMillis();

                    //enable the killing ghost after eating the big dot
                    score = getScore() + 50; //adds 50pts for each big dot
                    eatSound.stop();
                    if (eatSound.isPlaying() == false)
                    {
                        eatSound.play();
                    }
                }
                entity->remove = true;
            }
        }
    }
    for (int i = 0; i < ghostSpawner->ghostManager.size(); i++) // Iterate over ghostManager
    {
        if (collides(ghostSpawner->ghostManager[i])) //check if a ghost collide with pacman
        {
            if (!isBigDot) //if isBigDot is false
            {
                die(); //Lower life and return pacman to his original location if a ghost hit him
            }
            else
            {
                removeGhost(i); // i is the index and the function remove the ghost in that index in tha vector ghostManager
                ghostCounter--; //substract from counter soo it can respawn
                break;
            }
        }
    }
}
//---------------------------------------
void Player::displayScore() //Display score
{
    font.drawString("SCORE: ", 300, 35);             //display "score" over the current game score
    font.drawString(to_string(getScore()), 300, 50); //displays current score of the game
}
//---------------------------------------
//!Remove Ghost
void Player::removeGhost(int i) //Remove ghost from the vector vector<Ghost*> ghostManager
{
    ghostSpawner->ghostManager.erase(ghostSpawner->ghostManager.begin() + i);
}
//---------------------------------------
void Player::turnAllBlue() //!--------------
{
    if (isBigDot) //if true I will change all the Ghost color to EAT, this will change their sprite to their edible form
    {
        for (int i = 0; i < ghostSpawner->ghostManager.size(); i++)
        {
            ghostSpawner->ghostManager[i]->setColor(EAT);
        }
    }
    if (!isBigDot) //if false it will change their color "sprite" to their original
    {
        for (int i = 0; i < ghostSpawner->ghostManager.size(); i++)
        {
            ghostSpawner->ghostManager[i]->setColor(ghostSpawner->ghostManager[i]->originalColor);
        }
    }
}
//---------------------------------------
void Player::die()
{
    //remove pacman life i=until
    if (this->getHealth() != 0)
    {
        setHealth(this->getHealth() - 1);
        this->x = 312;
        this->y = 640;
    }
}
//---------------------------------------
void Player::addLife()
{
    if (this->getHealth() != 14) //Limitador de incremento de vida
    {
        setHealth(this->getHealth() + 1);
    }
}
//---------------------------------------
void Player::pacManLife() //& Print the health in the screen with a pacman icon in the left
{
    for (int i = 0; i < this->health; i++)
    {
        ofSetColor(256, 256, 0);
        ofDrawCircle(204.8 + i * quantityOfPacman, 721.92, 8);
        ofSetColor(0, 0, 0);
        ofDrawTriangle(204.8 + i * quantityOfPacman, 721.92, 220.16 + i * quantityOfPacman, 737.28, 220.16 + i * quantityOfPacman, 706.56);
        ofSetColor(256, 256, 256);
    }
}
//---------------------------------------
void Player::addGhost()
{
    ghostCounter++;      //Incremen ghost
    ghostCounterTotal++; //Incremen total ghost if the match
    if (ghostCountManager > 3)
    {
        ghostCountManager = 0;
    }
    if (ghostCountManager == 0)
    {
        ghostSpawner->addRed();
    }
    else if (ghostCountManager == 2)
    {
        ghostSpawner->addBlue();
    }
    else if (ghostCountManager == 1)
    {
        ghostSpawner->addPink();
    }
    else if (ghostCountManager == 3)
    {
        ghostSpawner->addOrange();
    }
    ghostCountManager++;
}
//---------------------------------------
void Player::spawnGhostTime()
{
    if (ghostCounter < ghostCounterTotal && getIsCreatingGhost() == false) //Reference time for the ghost to respawn
    {
        setGhostDeadReferenceTime(ofGetElapsedTimeMillis());
        setIsCreatingGhost(true);
    }
    if (ofGetElapsedTimeMillis() - ghostDeadReferenceTime > 5000 && getIsCreatingGhost() == true)
    {
        //creates a new ghost and adds it to the entities vector
        //allowing it to be displayed on the map
        //decide cual fantasma se va a crear

        if (ghostCountManager > 3)
        {
            ghostCountManager = 0;
        }

        //for vector crea y los elimina
        if (ghostCountManager == 0)
        {
            ghostSpawner->addRed();
        }
        else if (ghostCountManager == 2)
        {
            ghostSpawner->addBlue();
        }
        else if (ghostCountManager == 1)
        {
            ghostSpawner->addPink();
        }
        else if (ghostCountManager == 3)
        {
            ghostSpawner->addOrange();
        }
        ghostCounter++; //increment the ghost
        setIsCreatingGhost(false);
        ghostCountManager++; //change the ghost color that will spawn
    }
}
void Player::turnOffBigDot() //^Reference time for how much the duration of the BigDot
{
    if (ofGetElapsedTimeMillis() - bigDotReferenceTime > 6000 && isBigDot)
    {
        isBigDot = false;
    }
}
//^--------------------