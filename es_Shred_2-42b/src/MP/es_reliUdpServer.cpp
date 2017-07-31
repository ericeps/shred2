
#include "es_reliUdpServer.h"
#include <QByteArray>
#include <QUdpSocket>
#include <QTimer>
#include <QString>
#include <QHostAddress>
#include <algorithm>
#include <utility>

#include <iostream>

bool es_reliUdpServer::setConnectionInfo( QString tmpIP, int rea, int wri){
	if(!myIP.setAddress(tmpIP))
	{
	errorCode = 2;
	errorMessage = "Invalid IP Address";
	return 0;
	}
	else if( (rea < 10000 || rea > 65535) || (wri < 10000 || wri > 65535) )
	{
	errorCode = 3;
	errorMessage = "Invalid Port Number (use 10000 to 65535)";
	return 0;
	}
	readPort = rea;
	writePort = wri;
	return 1;
}


bool es_reliUdpServer::start(){
		Udp = new QUdpSocket;
		if(Udp->bind(myIP, readPort))
		{
		connect(Udp, SIGNAL(readyRead()), this, SLOT(teleRead()));
		resendTimer->start(resendLOT);
		checkTimeOff->start(1000);
		return 1;
		}
		else
		{
		errorCode = 4;
		errorMessage = "Failed to Bind Socket";
		return 0;
		}
}
bool es_reliUdpServer::stop(){
	disconnect(Udp, SIGNAL(readyRead()), 0, 0);
	resendTimer->stop();
	checkTimeOff->stop();
	errorCode = 0;
	errorMessage = "";
	stateStatus = -1;
//	sequence = 0;
	resendLOT = 25;
	clearTemp();
	delete Udp;
	return 1;
}


void es_reliUdpServer::sendVerify(QByteArray &datagram){
	datagram.prepend("es_v00");
	packet_info tmpPacket;
	tmpPacket.resendAttempt = 0;
	tmpPacket.data = datagram;
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{
		icli->addPacket(tmpPacket);
		++icli;
	}
	}
void es_reliUdpServer::sendNoverify(QByteArray &datagram){
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{
		datagram.prepend( "es_n" );
		Udp->writeDatagram(datagram, icli->IP ,writePort);
		++icli;
	}
	}
void es_reliUdpServer::sendToIP(QByteArray &datagram,QHostAddress &tmpIP){
	datagram.prepend("es_v00");
	packet_info tmpPacket;
	tmpPacket.resendAttempt = 0;
	tmpPacket.data = datagram;
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{	
		if(icli->IP == tmpIP)
		{icli->addPacket(tmpPacket);
		break;
		}
		++icli;
	}
	}

int es_reliUdpServer::getErrorCode(){
	return errorCode;
	}
QString es_reliUdpServer::getErrorMessage(){
	return errorMessage;
	}
int es_reliUdpServer::getState(){
	return stateStatus;
	}
int es_reliUdpServer::countClients(){
	return ClientList.size();
	}

void es_reliUdpServer::clearTemp(){
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{	icli->saveTemp.clear();
		icli->teleTimeOff = 0;
		++icli;
	}
	}



void es_reliUdpServer::pipeNoverify(QByteArray &datagram, QHostAddress &cliIP){
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{
		if(icli->IP != cliIP)
		{
		Udp->writeDatagram(datagram, icli->IP,writePort);
		}
		++icli;
	}
	}

void es_reliUdpServer::receivePacket(QByteArray &datagram, QHostAddress &cliIP){
		if( datagram.at(3)=='?' )
		{	newClient(cliIP);
			return;
		}
		else if('$' == datagram.at(3))
		{
			addClient(cliIP);
			return;
		}
		std::list<es_clientInfo>::iterator icli = find(ClientList.begin(), ClientList.end(), cliIP);
	//IF client is in list, then check datagram
		if( ClientList.end() == icli)
		return;


		if('g' == datagram.at(3))
		{	confirmedData(es_sequence::imagine(datagram.at(4),datagram.at(5)),icli);
		}
		else if('v' == datagram.at(3))
		{
			if(sendConfirm(es_sequence::imagine(datagram.at(4),datagram.at(5)),cliIP))
			distributeData(datagram,cliIP);
		}
		else if('n' == datagram.at(3))
			pipeNoverify(datagram,cliIP);
		else if('s' == datagram.at(3))		//for server
		{
			if(sendConfirm(es_sequence::imagine(datagram.at(4),datagram.at(5)),cliIP))
			storeData(datagram,cliIP);
		}
		else if('a' == datagram.at(3))
			vteleSig(icli);

	}
void es_reliUdpServer::storeData(QByteArray &datagram,QHostAddress &cliIP){
	es_fromClient tmpFrom;
	tmpFrom.IP = cliIP;
	tmpFrom.data = datagram.right(datagram.size()-6);
	fromClient->push_back( tmpFrom );
	emit dataSaved();
}
void es_reliUdpServer::confirmedData(es_sequence aseq, std::list<es_clientInfo>::iterator icli){
		std::list<packet_info>::iterator aniter = find(icli->saveTemp.begin(), icli->saveTemp.end(), aseq);
		if(aniter!=icli->saveTemp.end())
		icli->saveTemp.erase(  aniter  );
	}
bool es_reliUdpServer::sendConfirm(es_sequence aseq, QHostAddress &cliIP){
// returns true if it is new data, false if the data has already been processed
		QByteArray datagram("es_g");
		datagram.append( aseq.high ).append(aseq.low);
		Udp->writeDatagram(datagram, cliIP, writePort);
	std::list<es_clientInfo>::iterator cliiter = find(ClientList.begin(),ClientList.end(),cliIP);
	while(cliiter->gotThese.size() > 40)
	cliiter->gotThese.pop_back();
	if(cliiter->gotThese.end() == find(cliiter->gotThese.begin(),cliiter->gotThese.end(),aseq))
	{	cliiter->gotThese.push_front(aseq);
		return 1;
	}
	else
		return 0;
	}
void es_reliUdpServer::distributeData(QByteArray &datagram, QHostAddress &cliIP){
		packet_info tmpPacket;
		tmpPacket.resendAttempt = 0;
		tmpPacket.data = datagram;
		std::list<es_clientInfo>::iterator icli = ClientList.begin();
		while ( icli != ClientList.end() )
		{
//sendself
			if(icli->IP != cliIP)
			icli->addPacket(tmpPacket);
			++icli;
		}
	}

void es_reliUdpServer::lock(bool alock){
	locked=alock;
	}
bool es_reliUdpServer::newClient(QHostAddress &cliIP){
	if(!locked)
	{	if(autoadd)
		{
		addSyncCli(cliIP);
		return 1;
		}
		else
		emit clientAsk(cliIP);
	}
	return 0;
	}
void es_reliUdpServer::addSyncCli(QHostAddress &cliIP){
		std::list<es_clientInfo>::iterator tmpCliInfo = find(ClientList.begin(),ClientList.end(),cliIP);
		if(ClientList.end() != tmpCliInfo)
		ClientList.erase(tmpCliInfo);
		if(syncList.end() == find(syncList.begin(),syncList.end(),cliIP))
		{	syncList.push_back(cliIP);
		}
		QByteArray datagram( "es_!" );
		Udp->writeDatagram(datagram, cliIP, writePort);
	}
void es_reliUdpServer::addClient(QHostAddress &cliIP){
	std::list<QHostAddress>::iterator syncIter = find(syncList.begin(),syncList.end(),cliIP);
	if(syncList.end() != syncIter
		&& ClientList.end() == find(ClientList.begin(),ClientList.end(),cliIP))
	{
		syncList.erase(syncIter);
		es_clientInfo tmpCliInfo;
		tmpCliInfo.IP = cliIP;
		ClientList.push_back(tmpCliInfo);
		emit clientSynced(cliIP);
	}
}
void es_reliUdpServer::delClient(QHostAddress &cliIP){
	std::list<es_clientInfo>::iterator tmpiter = find(ClientList.begin(),ClientList.end(),cliIP);
	if(tmpiter != ClientList.end())
	ClientList.erase(tmpiter);
	}

void es_reliUdpServer::vteleSig(std::list<es_clientInfo>::iterator icli){
		icli->teleTimeOff = 0;
		QByteArray datagram( "es_b" );
		Udp->writeDatagram(datagram, icli->IP, writePort);
	}

void es_reliUdpServer::teleRead(){
		while(Udp->hasPendingDatagrams())
		{
		QByteArray datagram;
		datagram.resize(Udp->pendingDatagramSize());
		QHostAddress cliIP;
		Udp->readDatagram(datagram.data(), datagram.size(), &cliIP, NULL);
		if(datagram.startsWith("es_"))
		receivePacket(datagram,cliIP);
		}
	}

void es_reliUdpServer::resendTemp(){
	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	std::list<packet_info>::iterator ipack;
	if(!ClientList.empty())
	while ( icli != ClientList.end() )
	{	ipack = icli->saveTemp.begin();
		while( ipack != icli->saveTemp.end() )
		{
			Udp->writeDatagram(ipack->data, icli->IP, writePort);
			++(ipack->resendAttempt);
			if(ipack->resendAttempt > 120)
			{
			std::cout<<"Resend Attempts 120, ruServer"<<std::endl;
			std::cout<<"data = "<<ipack->data.at(3)<<std::endl;		
			ipack=icli->saveTemp.erase(ipack);
			}
			else
			++ipack;
		}
		++icli;
	}
	}

void es_reliUdpServer::testTimeout()
{	std::list<es_clientInfo>::iterator icli = ClientList.begin();
	while ( icli != ClientList.end() )
	{	++icli->teleTimeOff;
		if(icli->teleTimeOff > maxCliTimeOff)
		{	QHostAddress tmpIP(icli->IP);
			++icli;
			emit cliTimedOut(tmpIP);
		}
		else
		++icli;
	}
}

es_reliUdpServer::es_reliUdpServer(std::list<es_fromClient> *tmpsave,QObject *parent) : QObject(parent){
	fromClient = tmpsave;
	errorCode = 0;
	errorMessage = "";
	stateStatus = -1;
	autoadd =0;
	locked=0;
	maxCliTimeOff = 5;
	resendLOT = 25;
	resendTimer = new QTimer;
	connect(resendTimer, SIGNAL(timeout()), this, SLOT(resendTemp()));
	checkTimeOff = new QTimer;
	connect(checkTimeOff, SIGNAL(timeout()), this, SLOT(testTimeout()));
	}

