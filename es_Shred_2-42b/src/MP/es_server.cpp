// have clients periodically send info to server, in-case player disconnects mid-game,
// or, if client suddenly exits game, send info

#include <QtGui>
#include "es_server.h"
#include <QHostAddress>
#include <QtNetwork>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <QTimer>

#include <iostream>
#define DELIM 1

bool es_server::start(QString aadd, QString rea, QString wri){
	if( ReliUdpServer->setConnectionInfo(aadd, rea.toInt(), wri.toInt()) )
	{	if(ReliUdpServer->start())
		return 1;
		else
		return 0;
	}
	else
	return 0;
}
void es_server::stop(){
	ReliUdpServer->stop();
	}
QString es_server::getErrorMessage(){
	return ReliUdpServer->getErrorMessage();
	}

void es_server::newDataSlot(){
	while(!fromClient.empty())
	{
	interpretData(fromClient.front());
	fromClient.pop_front();
	}
	}
void es_server::newClientRequest(QHostAddress &cliIP){
	ReliUdpServer->addSyncCli(cliIP);
	}
void es_server::newClientSynced(QHostAddress &cliIP){
	QByteArray trdata("tr");
	ReliUdpServer->sendToIP( trdata, cliIP);
	}


void es_server::addNewPlayer(QHostAddress &cliIP,QByteArray aname){
		static unsigned char currentID=2;
		if(++currentID==255)
		currentID=2;
		es_playerInfo tmpplayer;
		tmpplayer.ID = currentID;

		tmpplayer.name = aname;
		tmpplayer.IP = cliIP;
		PlayerList.push_back(tmpplayer);
		QByteArray cndata("cn");
			cndata.append(DELIM).append(tmpplayer.name);
		QByteArray tbdata("tb");
		std::list<es_playerInfo>::iterator ii;
		for(ii=PlayerList.begin();ii!=PlayerList.end();ii++)
		if(ii->name!=tmpplayer.name)
		{tbdata.append(DELIM).append(ii->name);
		ReliUdpServer->sendToIP(cndata,ii->IP);
		}
		ReliUdpServer->sendToIP(tbdata,cliIP);
	}
void es_server::deletePlayer(QHostAddress &cliIP){
std::list<es_playerInfo>::iterator tmpit = find(PlayerList.begin(),PlayerList.end(),cliIP);
QByteArray tmpname;
	if(PlayerList.end() != tmpit)
	{
	tmpname = tmpit->name;
	PlayerList.erase(tmpit);
	QByteArray cddata("cd");
	cddata.append(DELIM).append(tmpname);
	std::list<es_playerInfo>::iterator ii;
	for(ii=PlayerList.begin();ii!=PlayerList.end();ii++)
	ReliUdpServer->sendToIP( cddata, ii->IP);
//	ReliUdpServer->resetSeq( cliIP );
	}
	}
void es_server::interpretData(es_fromClient &cldatagram){
	if(cldatagram.data.startsWith("ta"))					//request server connection
	{	QList<QByteArray> tmplist = cldatagram.data.split(DELIM);
		std::list<es_playerInfo>::iterator tmpit;
		bool newIP = (PlayerList.end() == find(PlayerList.begin(),PlayerList.end(),cldatagram.IP));
		if(!newIP)
		{	deletePlayer(cldatagram.IP);
		}
		bool newName = (PlayerList.end() == find(PlayerList.begin(),PlayerList.end(),tmplist.at(1)));
		if(newName)
		{	addNewPlayer(cldatagram.IP,tmplist.at(1));
		}
		else
		{
		QByteArray czdata("tz");
		ReliUdpServer->sendToIP(czdata,cldatagram.IP);
		}
	}
	else if(cldatagram.data.startsWith("td"))				//player telling server it will(or has) disconnect
	{	QByteArray tedata("te");
		ReliUdpServer->sendToIP( tedata, cldatagram.IP);
		deletePlayer(cldatagram.IP);
	}
	else if(cldatagram.data.startsWith("om"))				//map change
	{	QList<QByteArray> tmplist = cldatagram.data.split(DELIM);
		Map = tmplist.at(1).toInt();
	}
	else if(cldatagram.data.startsWith("od"))				//game duration change
	{	QList<QByteArray> tmplist = cldatagram.data.split(DELIM);
		GameDuration = tmplist.at(1).toInt() * 60000;
	}
	else if(cldatagram.data.startsWith("rs")&&gameOn==0)	//request startgame
	{	gameOn=1;
		ReliUdpServer->lock(1);
		std::list<es_playerInfo>::iterator ii;
		for(ii=PlayerList.begin();ii!=PlayerList.end();ii++)
		{
			QByteArray sgdata("sg");
			sgdata.append(DELIM).append(QByteArray::number(Map));
			sgdata.append(DELIM).append(ii->ID);
			std::list<es_playerInfo>::iterator ia;
			for(ia=PlayerList.begin();ia!=PlayerList.end();ia++)
			{	if(ii->ID != ia->ID)
				{sgdata.append(DELIM).append(ia->ID);
				sgdata.append(DELIM).append(ia->name);
				}
			}
std::cout<<"PlayerList size == "<<PlayerList.size()<<std::endl;
std::cout<<"sgdata size == "<<sgdata.size()<<std::endl;
			ReliUdpServer->sendToIP(sgdata,ii->IP);
		}
		GameTimerCountdown->start(GameDuration);
	}
	}

void es_server::endGame(){
	QByteArray egdata("eg");
	ReliUdpServer->sendVerify(egdata);
	gameOn=0;
	ReliUdpServer->lock(0);
	}

void es_server::cliTimedOutSlot(QHostAddress &acli){
	deletePlayer(acli);
	ReliUdpServer->delClient(acli);
	}

es_server::es_server(QObject *parent) : QObject(parent){
	Map=1;
	GameDuration=30000;
	GameStock=5;
	gameOn=0;
	ReliUdpServer = new es_reliUdpServer(&fromClient);
	connect(ReliUdpServer, SIGNAL(dataSaved()),this,SLOT(newDataSlot()));
	GameTimerCountdown = new QTimer;
	connect(GameTimerCountdown, SIGNAL(timeout()),this,SLOT(endGame()));
	connect(ReliUdpServer, SIGNAL(clientAsk(QHostAddress&)),this,SLOT(newClientRequest(QHostAddress&)));
	connect(ReliUdpServer, SIGNAL(clientSynced(QHostAddress&)),this,SLOT(newClientSynced(QHostAddress&)));
	connect(ReliUdpServer, SIGNAL(cliTimedOut(QHostAddress&)),this,SLOT(cliTimedOutSlot(QHostAddress&)));
	}
