#pragma once
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"

class GameState: public State{
    private:
		ofImage mapImage;
		Map* map;
		ofTrueTypeFont font;
		int endScore = 0, highestScore = 0;
		ofSoundPlayer backgroundMusic;
		ofColor pacManColor;
	public: 
		GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		int getFinalScore(){return endScore;} //last score
		int getHighestScore(){return highestScore;} //HighestScore in all games played
		void setColor(ofColor c){pacManColor = c;}
};