#include "GameState.h"
#include "Entity.h"

GameState::GameState()
{
	//map->setScoreMap(0);
	font.load("font/pac.ttf", 8); //font load
	mapImage.load("images/map1.png"); //map load
	backgroundMusic.load("sounds/background_music_2.wav"); //music load
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick()
{
	map->getPlayer()->setPlayerColor(pacManColor);
	if (backgroundMusic.isPlaying() == false) //BAckground music play
	{
		backgroundMusic.play();
	}
	if (map->getHealthMap() == 0) //Change state transition
	{
		backgroundMusic.stop();
		setNextState("TryAgain");
		setFinished(true);
		map->setHealthMap(3); // set initial health
		endScore = map->getPlayer()->getScore(); // last score
		if(endScore >= highestScore)
		{
			highestScore = endScore; // record highest score in all the gameplayed
		}
		map->setScore(0); //setScore to 0
		map = MapBuilder().createMap(mapImage); //reseting map
	}
	map->tick();
	//font.drawString("Last Score: " + to_string(endScore), 100, 100);
}
void GameState::render()
{
	map->render(); // Map draw
}

void GameState::keyPressed(int key)
{
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button)
{
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key)
{
	map->keyReleased(key);
}

void GameState::reset()
{
	setFinished(false);
	setNextState("");
}