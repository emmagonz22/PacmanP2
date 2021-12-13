#pragma once

#include "Button.h"
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"
//#include "MapBuilder.h"

class GameOverState: public State {
private:
	ofImage tryScreen; //Image if GameoverState 1
	ofImage tryScreen2; //Image if GameoverState 2
	Button *tryAgain; //Button for state changes
	ofTrueTypeFont font; // font for words
	int score, highestScore;

public:
	GameOverState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	int getScore(){return score;} //Get score for display 
	int getHighestScore(){return highestScore;} //Get Highest score for display 
	void setScore(int s){score = s;} //Change score optional
	void setHighestScore(int hs){ highestScore = hs;} //Change score optional
};
