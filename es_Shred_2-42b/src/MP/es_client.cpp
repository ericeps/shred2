#include "es_client.h"
#include "es_reliUdp.h"
#include "es_net.h"
#include "es_MPgame.h"
#include "es_pInfo.h"
#include "es_UIStats.h"
#include <algorithm>
#include <iostream>
#include <QString>
#include <QHostAddress>
#define DELIM 1

es_client::es_client(es_MPgame *ainfo, QObject *parent) : es_reliUdp(&saveData,parent){
//	ReliUdp = new es_reliUdp(&saveData);
	connect(this, SIGNAL(dataSaved()), this, SLOT(newDataSlot()));
	GameInfo = ainfo;
	statusTimer = new QTimer;
//	connect(this, SIGNAL(teleFound()), this, SLOT(cteleFound()));
	connect(statusTimer, SIGNAL(timeout()), this, SLOT(teleCheck()));
	canTimeout=1;
	}

void es_client::setNet(es_net *anet){
	Net = anet;
	}


bool es_client::startClient(QString cIP, QString sIP, QString rPort, QString wPort){
	if( this->setConnectionInfo(cIP,sIP,rPort.toInt(),wPort.toInt()) )
	{	if(this->start())
		{
		statusTimer->start(1000);
		return 1;
		}
		else
		return 0;
	}
	else
	return 0;
	}
void es_client::stopClient(){
	statusTimer->stop();
	stop();
	}
void es_client::cteleFound(){
	GameInfo->setClientStatus(2);
	}

void es_client::connectToServer(QString aname){
	QByteArray tmpver("ta");
	tmpver.append(DELIM).append(aname);
	this->sendtoServer(tmpver);
	}
void es_client::disconnectFromServer(){
	QByteArray tmpver("td");
	this->sendtoServer(tmpver);
	GameInfo->setClientStatus(0);
	}
void es_client::changeMap(int amap){
	QByteArray tmpver("om");
	tmpver.append(DELIM).append(QByteArray::number(amap));
	this->sendtoServer(tmpver);
	}
void es_client::changeDuration(int minutes){
	QByteArray tmpver("od");
	tmpver.append(DELIM).append(QByteArray::number(minutes));
	this->sendtoServer(tmpver);
	}
void es_client::killConnection(){
	stop();
	}
void es_client::teleCheck(){
	if(this->getTeleTimeOff() > 5)
	{	if(canTimeout)
		{	if(getState()>=1)
			GameInfo->setClientStatus(-3);
			else
			GameInfo->setClientStatus(-5);
		}
	}
	}
void es_client::dieAtTimeout(bool tmp){
	teleTimeOff=0;
	canTimeout=tmp;
	}
void es_client::newDataSlot(){
	while(!saveData.empty())
	{
	interpretData(saveData.front());
	saveData.pop_front();
	}
	}

void es_client::interpretData(QByteArray &datagram){
	if(datagram.at(0)=='p'&&GameInfo->isGameOn())
	{Net->processDatagram(datagram);
	}
	else
	{	QList<QByteArray> tmplist = datagram.split(DELIM);

		if(tmplist.startsWith("cm"))
		{	QString tmpname = tmplist.at(1).data();
			QString tmpmes = tmplist.at(2).data();
			emit newMessage(tmpname,tmpmes);
		}
		else if(tmplist.startsWith("cn"))
		{	QString tmpname = tmplist.at(1).data();
			emit newPlayer(tmpname);
		}
		else if(tmplist.startsWith("cd"))
		{	QString tmpname = tmplist.at(1).data();
			emit delPlayer(tmpname);
		}
		else if(tmplist.startsWith("tb"))	//connection established, and list of current players
		{	std::list<QString> namelist;
			for(int ii=1;ii<tmplist.size();ii++)
			namelist.push_back(tmplist.at(ii).data());
			GameInfo->setClientStatus(4);
			GameInfo->startChat(namelist);
		}
		else if(tmplist.startsWith("tz"))	//name is taken
		{	GameInfo->setClientStatus(3);
		}
		else if(tmplist.startsWith("tr"))
		{	this->cteleFound();
		}
		else if(tmplist.startsWith("sg"))	//start game
		{	std::list<unsigned char> oplist;
			std::list<const char*> opnames;
			int amap = tmplist.at(1).toInt();
			GameInfo->setmyID(tmplist.at(2).at(0)/*.toUInt()*/);
			for(int ii=3; ii<tmplist.size(); ii+=2)
			{oplist.push_back(tmplist.at(ii).at(0)/*.toUInt()*/);
			opnames.push_back(tmplist.at(ii+1).data());
			}

//			for(int ii=tmplist.at(3).toInt()+4; ii<tmplist.size(); ii++)
//			opnames.push_back(tmplist.at(ii).data());

			GameInfo->startGame(oplist,opnames, amap);
		}
		else if(tmplist.startsWith("eg"))
		{
			GameInfo->stopGame();
		}
		else if(tmplist.startsWith("ei"))
		{	std::list<es_pstats> statList;
			for(int ii=2;ii<tmplist.size();ii+=4)
			{
				es_pstats tmpStats( tmplist.at(ii).at(0) );
			tmpStats.Damage = tmplist.at(ii+1).toFloat();
			tmpStats.Kills = tmplist.at(ii+2).toInt();
			tmpStats.Slows = tmplist.at(ii+3).toInt();
				statList.push_back(tmpStats);
			}
			GameInfo->getUIStats()->setData(tmplist.at(1).at(0),statList);
		}
	}
	}


void es_client::requestStart(){
	QByteArray tmpreq("rs");
	
	this->sendtoServer(tmpreq);
	}
void es_client::sendMessage(QString name,QString &message){
	QByteArray tmpmes("cm");
	tmpmes.append(DELIM).append(name).append(DELIM).append(message);
	this->sendVerify(tmpmes);
	}

void es_client::sendEndInfo(es_pInfo *aninfo){
	QByteArray tmpBytes("ei");
	tmpBytes.append(DELIM).append(GameInfo->getmyID());
	std::list<es_pstats> pStats = aninfo->getList();
	std::list<es_pstats>::iterator ii;
	for(ii=pStats.begin();ii!=pStats.end();ii++)
	{tmpBytes.append(DELIM).append(ii->ID)
	.append(DELIM).append(QByteArray::number(ii->Damage,'g'))
	.append(DELIM).append(QByteArray::number(ii->Kills))
	.append(DELIM).append(QByteArray::number(ii->Slows));
	}
	this->sendVerify(tmpBytes);
	}