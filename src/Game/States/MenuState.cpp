#include "MenuState.h"

MenuState::MenuState() {

	font.load("font/pac.ttf", 14); //font load
	startScreen.load("images/pacmanScreen.png"); //startscreen load
	startScreen2.load("images/pacmanScreen2.png"); // startscreen2 load
	startScreen3Quit.load("images/quit-pacman.png"); //startscreen3 highlighted quit button 
	startSound.load("sounds/pacman_beginning.wav"); // Beginning music
	startButton = new Button(ofGetWidth() / 2 - 109, ofGetHeight() / 2 - 57 / 2, 216, 57, "Start"); //Start button
	quitButton = new Button(ofGetWidth() / 2  + 442 - 107/2, ofGetHeight() / 2 + 269 - 142 / 2, 107, 142, "Quit" );//Quit button
	guiPanel.setup("Press h hide/show","settings.xml", 20,20);
	guiPanel.add(color.setup("Pacman color", ofColor(255,255, 0),ofColor(0,0,0), ofColor(255,255,255)));
	guiPanel.add(label.setup(labelText, guiPanel.getWidth(), 20));
	guiHide = false;
	
}
void MenuState::tick() {
	if(startSound.isPlaying()==false){ // Beginning music play
	startSound.play();
	}
	startButton->tick();
	if(startButton->wasPressed()){ //change state transition
		startSound.stop();
		setNextState("Game");
		setFinished(true);
	}
	quitButton->tick();
	if(quitButton->wasPressed()){ //Quit game transition
		ofExit();
	
	}
}
void MenuState::render() {
	//^ Change image depending on mouse location ^//  
	if(ofGetMouseX() >= 403 && ofGetMouseX() < 621  && ofGetMouseY() < 412.5 && ofGetMouseY() > 355.5)
	{
		startScreen2.draw(ofGetWidth() / 2 - startScreen.getWidth() / 2, ofGetHeight() / 2 - startScreen.getHeight() / 2);
	}else if(ofGetMouseX() >= 900 && ofGetMouseX() <= 1008  && ofGetMouseY() <= 726 && ofGetMouseY() >= 581)
	{
		startScreen3Quit.draw(ofGetWidth() / 2 - startScreen.getWidth() / 2, ofGetHeight() / 2 - startScreen.getHeight() / 2);
		font.drawString("Quit" , 954 - font.stringWidth("Quit") / 2, 654); //Quit button text
	}else
	{
		startScreen.draw(ofGetWidth() / 2 - startScreen.getWidth() / 2, ofGetHeight() / 2 - startScreen.getHeight() / 2);
		ofSetColor(1,1,1);
		font.drawString("Quit" , 954 - font.stringWidth("Quit") / 2, 654); //Quit button text
		ofSetColor(255,255,255);
	}
	if (!guiHide)
    {
        guiPanel.draw();
    }
}

void MenuState::keyPressed(int key){
	switch (key)
	{
	case 'h':
	case 'H':
		guiHide = !guiHide;
		break;
	}
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y); //Check is mouse is pressed in location
	quitButton->mousePressed(x, y); //Check is mouse is pressed in location
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}