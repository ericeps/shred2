/* Control center for Multiplayer games.
    Starts/Stops and coordinates the main states of the program.

 */
#ifndef ES_MPGAME
#define ES_MPGAME

class es_MPwindow;
class es_MPbegin;
class es_UINet;
class es_MPSett;
class es_UIStatus;
class es_UIChat;
class es_qtgl;
class es_client;
class es_server;
class es_gamework;
class es_pInfo;
class es_UIStats;
#include <list>
#include <QString>
#include <string>
#include "es_basegame.h"

class es_MPgame:public es_basegame
{
public:
es_MPgame(chooseGame *);
~es_MPgame();
virtual void newUI();

es_MPbegin *getBegin();
//es_qtgl *getGL();
es_UINet *getUINet();
es_MPSett *getMPSett();
es_UIChat *getUIChat();
es_client *getClient();
es_pInfo *getPInfo();
es_UIStats *getUIStats();

//void setmyName(QString);
//void setmyID(unsigned char);
//QString getName();
//unsigned char getmyID();
//bool isGameOn();

void startClient(QString,QString,QString,QString);
void startServer(QString,QString,QString);
void stopClient();
void stopServer();
void setClientStatus(int,QString = "");
void setServerStatus(int, QString = "");
void checkName(QString);

void startChat(std::list<QString> &);
void stopChat();
void requestStartGame();
void startGame(std::list<unsigned char> &oplist,std::list<const char*> &,int map);
void stopGame();

private:
//QString myName;
//unsigned char myID;

int ClientStatus;
int ServerStatus;
bool Chat;
//bool GameOn;
bool ServerMade;

private:
	es_MPwindow *MainWindow;
	es_MPbegin *Begin;
	es_UINet *UINet;
	es_MPSett *MPSett;
	es_UIChat *UIChat;
//	es_qtgl *Es_qtgl;
	es_server *myServer;
	es_client *myClient;
//	es_gamework *GameWork;
	es_pInfo *pInfo;
	es_UIStats *UIStats;
};
#endif
