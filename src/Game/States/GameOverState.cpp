#include "GameOverState.h"
#include "Entity.h"

GameOverState::GameOverState() {
	font.load("font/pac.ttf", 28); //font load for use as string
	tryScreen.load("images/tryagain1.png"); //GameOverState1 screen load
	tryScreen2.load("images/tryagain.png"); //GameOverState2 screen load
	tryAgain = new Button(ofGetWidth() / 2 - 401, ofGetHeight() / 2 - 66, 802, 132, "TryAgain"); //Button to change the state


}
void GameOverState::tick() {
	tryAgain->tick(); //update
	if(tryAgain->wasPressed()){ // change button transition
		setNextState("Menu");
		setFinished(true);
	}
}
void GameOverState::render() {
	if(ofGetMouseX() > 111 && ofGetMouseX() < 904  && ofGetMouseY() < 430 && ofGetMouseY() > 307)
	{
		tryScreen2.draw(ofGetWidth() / 2 - tryScreen.getWidth() / 2 + 10, ofGetHeight() / 2 - tryScreen.getHeight() / 2);//Draw screen if mouse is over thos coordinates
		ofSetColor(255,0,0);
		font.drawString("Score: " + to_string(getScore()), 90, 100); // Draw last score
		font.drawString("Highest Score: " + to_string(getHighestScore()), 90, 150);  //Draw Highest score
		ofSetColor(255,255,255);
	}else
	{
		tryScreen.draw(ofGetWidth() / 2 - tryScreen.getWidth() / 2 + 10, ofGetHeight() / 2 - tryScreen.getHeight() / 2); // draw GameOverState screen 1	
		font.drawString("Score: " + to_string(getScore()), 90, 100); // Draw last score
		font.drawString("Highest Score: " + to_string(getHighestScore()), 90, 150); //Draw Highest score
	}
	
	//ofDrawBitmapString("This is X " + to_string(ofGetMouseX()) + " This is Y " + to_string(ofGetMouseY()), 100, 100); //testing purpose
	
	
}

void GameOverState::keyPressed(int key){
	
}

void GameOverState::mousePressed(int x, int y, int button){
	tryAgain->mousePressed(x, y);
}

void GameOverState::reset(){
	setFinished(false);
	setNextState("");
	tryAgain->reset();
}