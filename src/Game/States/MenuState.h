#pragma once

#include "State.h"
#include "Button.h"
#include "ofxGui.h"
#include "Player.h"

class MenuState : public State {
private:
	//&Images variable&//
	ofImage startScreen;
	ofImage startScreen2;
	ofImage startScreen3Quit;
	//&-------&-------&//
	//*Button*//
	Button *startButton;
	Button *quitButton;
	//Font
	ofTrueTypeFont font;

	//pacman color
	ofxColorSlider color;

public:
	MenuState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	ofxPanel guiPanel;
	Player* playerColor;
	bool guiHide = false;
	ofSoundPlayer startSound; //music variable
	int count = 0;
	ofxLabel label;
	ofColor getColor(){return color;}
	const string labelText = "Change color Pac-Man";
};
