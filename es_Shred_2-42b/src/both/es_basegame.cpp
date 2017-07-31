#include "es_basegame.h"

#include <list>

#include "es_qtgl.h"
#include "es_gamework.h"
#include "chooseGame.h"

#include <iostream>
#include <QObject>
#include <QPushButton>

es_basegame::es_basegame(chooseGame* Ch){
	GameOn=0;
	myID = 1;
	myName="Default name";
	myChoose = Ch;
	}

void es_basegame::setmyID(unsigned char tmp){
	myID = tmp;
	std::cout<<"GameInfoID  "<<(int)myID<<std::endl;
	}
void es_basegame::setmyName(QString tmp){
	myName = tmp;
	}
unsigned char es_basegame::getmyID(){
	return myID;
	}

QString es_basegame::getName(){
	return myName;
	}
bool es_basegame::isGameOn(){
	return GameOn;
	}
bool es_basegame::isMultigame(){
return isMulti;
}
es_qtgl* es_basegame::getGL(){
	return Es_qtgl;
	}
void es_basegame::switchGame(){
	myChoose->switchGame();
}
void es_basegame::mullAgain(){
	myChoose->mullAgain();
}