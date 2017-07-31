/* Base control center for game, inherited by SPgame and MPgame.
   Contains pointers to basic classes.
   Contains basic info and functions related to both Single player and multiplayer game states.

 */
#ifndef ES_BASEINFO
#define ES_BASEINFO

#include <QString>
#include <list>
class es_qtgl;
class es_gamework;
class chooseGame;
//#include "es_mainwindow.h"
//#include "es_begin.h"
//#include "es_qtgl.h"
//#include "es_gamework.h"

class es_basegame
{
public:
es_basegame(chooseGame*);
virtual ~es_basegame(){};

virtual void newUI()=0;
void switchGame();
void mullAgain();

void setmyName(QString);
QString getName();
void setmyID(unsigned char);
unsigned char getmyID();
bool isMultigame();

bool isGameOn();

//es_begin *getBegin();
es_qtgl* getGL();


protected:
QString myName;
unsigned char myID;
bool GameOn;
bool isMulti;
	es_qtgl *Es_qtgl;
	es_gamework *GameWork;
	chooseGame *myChoose;
};
#endif
