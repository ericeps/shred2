#include "es_MPgame.h"

#include <list>
#include "es_mainwindow.h"
#include "chooseGame.h"
#include "es_MPbegin.h"
#include "es_UINet.h"
#include "es_MPSett.h"
#include "es_UIChat.h"
#include "es_qtgl.h"
#include "es_client.h"
#include "es_server.h"
#include "es_gamework.h"
#include "es_pInfo.h"
#include "es_UIStats.h"
#include <iostream>
#include <QObject>
#include <QPushButton>

es_MPgame::es_MPgame(chooseGame *Ch):es_basegame(Ch){
	Chat=0;
	ClientStatus=0;
	ServerStatus=0;
	isMulti=1;
	}
void es_MPgame::newUI(){
	Begin = new es_MPbegin(this);
	myClient = new es_client(this);
	UINet = new es_UINet(this);
	MPSett = new es_MPSett(this);
	MPSett->setEnabled(0);
	UIChat = new es_UIChat(this);
	Es_qtgl = new es_qtgl(this);
	UIStats = new es_UIStats(this);
	Begin->setupUI();
	MainWindow = new es_MPwindow(Begin,UIChat,Es_qtgl,UIStats);
	GameWork = new es_gamework(this);
	pInfo = new es_pInfo;
	}
es_MPgame::~es_MPgame(){
	if(ServerMade==1)
	delete myServer;

	delete Begin;
	delete MainWindow;
	delete myClient;
	delete GameWork;
	delete pInfo;
	delete UIChat;
	delete Es_qtgl;
	delete UIStats;
}

void es_MPgame::startClient(QString cliIP,QString servIP,QString port1,QString port2){
	if(myClient->startClient(cliIP,servIP,port1,port2))
		setClientStatus(1);
	else
		setClientStatus(-1,myClient->getErrorMessage());
	}
void es_MPgame::stopClient(){
	setClientStatus(-4);
	myClient->disconnectFromServer();
//	myClient->stop();
	}
void es_MPgame::setClientStatus(int tmp,QString message){
	ClientStatus = tmp;
	if(tmp==0||tmp==-3||tmp==-5)
	{	stopChat();
		stopGame();
		myClient->stopClient();
	}
	if(tmp==2||tmp==3)
	{	myClient->dieAtTimeout(0);
		stopChat();
	}
	if(tmp==4)
	{	Begin->startGameButton->setEnabled(1);
		MPSett->setEnabled(1);
	}
	else
	{	MPSett->setEnabled(0);
		Begin->startGameButton->setEnabled(0);
	}
	UINet->setClientStatus(tmp,message);
	}
void es_MPgame::startServer(QString servIP,QString port1,QString port2){
	myServer = new es_server;
	ServerMade=1;
	if(myServer->start(servIP,port1,port2))
		setServerStatus(1);
	else
		setServerStatus(-1,myServer->getErrorMessage());
	}
void es_MPgame::stopServer(){
	if(ServerMade)
	{myServer->stop();
	ServerMade=0;
	delete myServer;
	}
	setServerStatus(0);
	}
void es_MPgame::setServerStatus(int tmp,QString message){
	ServerStatus = tmp;
	if(tmp !=1 && ServerMade)
	{ServerMade=0;
	delete myServer;
	}
	UINet->setServerStatus(tmp,message);
	}

void es_MPgame::startChat(std::list<QString> &namelist){
	if(Chat)
	return;
		UIChat->startChat(namelist);
		Chat = 1;
		QObject::connect(myClient, SIGNAL(newMessage(QString,QString&)),
				UIChat, SLOT(appendMessage(QString,QString&)));
		QObject::connect(myClient, SIGNAL(newPlayer(QString&)),
				UIChat, SLOT(newPlayer(QString&)));
		QObject::connect(myClient, SIGNAL(delPlayer(QString&)),
				UIChat, SLOT(delPlayer(QString&)));
		QObject::connect(UIChat, SIGNAL(sendMessage(QString,QString&)),
				myClient,SLOT(sendMessage(QString,QString&)));
		MainWindow->showChat(1);
		std::cout<<"chat..."<<std::endl;
	}
void es_MPgame::stopChat(){
	if(!Chat)
	return;
		Chat=0;
		UIChat->stopChat();
		MainWindow->showChat(0);
		QObject::disconnect(myClient,0,UIChat,0);
		QObject::disconnect(UIChat,0,myClient,0);
	}

void es_MPgame::requestStartGame(){
	myClient->requestStart();
	}
void es_MPgame::startGame(std::list<unsigned char> &oplist,std::list<const char*> &opnames, int map){
	Begin->startGameButton->setEnabled(0);
	MPSett->setEnabled(0);
	pInfo->setup(oplist,myID);
	UIStats->setupPlayers(oplist,opnames);
	GameWork->MPStart(oplist,map);
	MainWindow->showGL(1);
	Es_qtgl->showFullScreen();
	GameOn=1;
	}
void es_MPgame::stopGame(){
	if(GameOn)
	{	GameOn=0;
		GameWork->stopGame();
		MainWindow->showGL(0);
		myClient->sendEndInfo(pInfo);
		UIStats->setData(myID,pInfo->getList());
		Begin->startGameButton->setEnabled(1);
		MPSett->setEnabled(1);
	}
	}
void es_MPgame::checkName(QString tmp){
	setmyName(tmp);
	myClient->connectToServer(tmp);
	myClient->dieAtTimeout(1);
	}

es_UINet* es_MPgame::getUINet(){
	return UINet;
	}
es_MPSett* es_MPgame::getMPSett(){
	return MPSett;
	}
es_UIChat* es_MPgame::getUIChat(){
	return UIChat;
	}

es_client* es_MPgame::getClient(){
	return myClient;
	}
es_pInfo* es_MPgame::getPInfo(){
	return pInfo;
	}
es_UIStats* es_MPgame::getUIStats(){
	return UIStats;
	}
