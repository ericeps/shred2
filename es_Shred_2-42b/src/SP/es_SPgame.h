/* Control center for Single player games.
    Starts/Stops and coordinates the main states of the program.

 */
#ifndef ES_SPGAME
#define ES_SPGAME

class es_SPwindow;
class es_SPbegin;
class es_qtgl;
class es_SPSett;
class es_pInfo;
class chooseGame;
#include <list>
#include <string>
#include "es_basegame.h"

class es_SPgame:public es_basegame
{
public:
es_SPgame(chooseGame*);
~es_SPgame();
virtual void newUI();

void startGame(int map, int difficulty);
void stopGame();

es_SPSett* getSPSett();
es_pInfo* getPInfo();
private:
es_SPbegin* Begin;
es_SPSett* SPSett;
es_SPwindow* MainWindow;
es_pInfo* pInfo;
chooseGame *myChoose;

};

#endif
