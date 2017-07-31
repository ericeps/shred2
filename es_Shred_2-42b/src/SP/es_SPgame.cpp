#include "es_SPgame.h"

#include "es_SPbegin.h"
#include "es_SPSett.h"
#include "es_qtgl.h"
#include "es_mainwindow.h"
#include "es_gamework.h"
#include "es_pInfo.h"
#include "chooseGame.h"
#include <QPushButton>

es_SPgame::es_SPgame(chooseGame *Ch):es_basegame(Ch){
	isMulti=0;
	}
void es_SPgame::newUI(){
	Begin = new es_SPbegin(this);
	SPSett = new es_SPSett(this);
	Es_qtgl = new es_qtgl(this);
	Begin->setupUI();
	MainWindow = new es_SPwindow(Begin,Es_qtgl);
	GameWork = new es_gamework(this);
	}
es_SPSett* es_SPgame::getSPSett(){
	return SPSett;
	}
es_pInfo* es_SPgame::getPInfo(){
return pInfo;
}
void es_SPgame::startGame(int map, int difficulty){
//	Begin->startGameButton->setEnabled(0);
	SPSett->setEnabled(0);
	GameWork->SPStart(map,difficulty);
	MainWindow->showGL(1);
	Es_qtgl->showFullScreen();
	GameOn=1;
}
void es_SPgame::stopGame(){
	if(GameOn)
	{	GameOn=0;
		GameWork->stopGame();
		MainWindow->showGL(0);
//		Begin->startGameButton->setEnabled(1);
		SPSett->setEnabled(1);
	}
}
es_SPgame::~es_SPgame(){
delete Begin;
delete MainWindow;
delete GameWork;
delete Es_qtgl;
}