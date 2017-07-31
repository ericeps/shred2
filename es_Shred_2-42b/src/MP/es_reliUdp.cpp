#include "es_reliUdp.h"
#include "netdefs.h"

#include <iostream>
#include <QTimer>
#include <QUdpSocket>
#include <QByteArray>
#include <algorithm>

using std::cout;
using std::endl;

bool es_reliUdp::setConnectionInfo(QString myadd, QString fradd, int rea, int wri){
	if(!myIP.setAddress(myadd) || !frnIP.setAddress(fradd))
	{
	errorCode = 2;
	errorMessage = "Invalid IP Address";
	return 0;
	}
	else if( (rea < 10000 || rea > 65535) || (wri < 10000 || wri > 65535) )
	{
	errorCode = 3;
	errorMessage = "Bad Port Number (use 10000 to 65535)";
	return 0;
	}
	readPort = rea;
	writePort = wri;
	return 1;
}
bool es_reliUdp::start( ){
		Udp = new QUdpSocket;
		if(Udp->bind(myIP, readPort))
		{
		connect(Udp, SIGNAL(readyRead()), this, SLOT(teleRead()));
		connect(teleTimer, SIGNAL(timeout()), this, SLOT(teleAsk()));
		teleTimer->start(1000);
		resendTimer->start(resendLOT);
		return 1;
		}
		else
		{
		errorCode = 4;
		errorMessage = "Failed to Bind Socket";
		return 0;
		}
	}
bool es_reliUdp::stop(){
	disconnect(Udp, SIGNAL(readyRead()),0,0);
	disconnect(teleTimer,SIGNAL(timeout()),0,0);
	resendTimer->stop();
	errorCode = 0;
	errorMessage = "";
	stateStatus = -1;
//	sequence=0;
	gotThese.clear();
	teleTimer->stop();
	teleTimeOff = 0;
	resendLOT = 25;
	clearTemp();
	clearData();
	delete Udp;
	return 1;
	}


void es_reliUdp::sendNoverify(QByteArray &datagram){
	datagram.prepend( "es_n" );
	Udp->writeDatagram(datagram, frnIP, writePort);
	}

void es_reliUdp::sendVerify(QByteArray &datagram){
	++Seq;
	datagram.prepend(Seq.low);
	datagram.prepend(Seq.high);
	datagram.prepend("es_v");
	packet_info packfo;
	packfo.data = datagram;
	packfo.resendAttempt = 0;
	saveTemp.push_back(packfo);
	Udp->writeDatagram(datagram, frnIP, writePort);
	}
void es_reliUdp::sendtoServer(QByteArray &datagram){
	++Seq;
	datagram.prepend(Seq.low);
	datagram.prepend(Seq.high);
	datagram.prepend("es_s");
	packet_info packfo;
	packfo.data = datagram;
	packfo.resendAttempt = 0;
	saveTemp.push_back(packfo);
	Udp->writeDatagram(datagram, frnIP, writePort);
	}

int es_reliUdp::getErrorCode(){
	return errorCode;
	}
QString es_reliUdp::getErrorMessage(){
	return errorMessage;
	}
int es_reliUdp::getState(){
	return stateStatus;
	}
unsigned int es_reliUdp::getTeleTimeOff(){
	return teleTimeOff;
	}
int es_reliUdp::sizeTemp(){
	return saveTemp.size();
	}
void es_reliUdp::clearTemp(){
	saveTemp.clear();
	}

int es_reliUdp::sizeData(){
	return saveData->size();
	}
void es_reliUdp::clearData(){
	saveData->clear();
	}
bool es_reliUdp::hasData(){
	return ( !saveData->empty());
	}

void es_reliUdp::receivePacket(QByteArray &datagram){
		if(     'g'==datagram.at(3))	// server verifying it got data
		{
			confirmedData(es_sequence::imagine(datagram.at(4),datagram.at(5)));
		}
		else if('v'==datagram.at(3))	// server sent data that needs verified
		{
			if(sendConfirm(es_sequence::imagine(datagram.at(4),datagram.at(5))))
			storeData( datagram );
		}
		else if('n'==datagram.at(3))	// server sent data that doesn't need verified
			storeData(datagram);
		else if('b'==datagram.at(3))		// reply from server
			teleReceive();
		else if('!'==datagram.at(3))
			teleAnswer();
	}

void es_reliUdp::confirmedData(es_sequence aseq){
	std::list<packet_info>::iterator aniter = find(saveTemp.begin(), saveTemp.end(), aseq);
	if(aniter!=saveTemp.end())
	saveTemp.erase(  aniter  );
	}
bool es_reliUdp::sendConfirm(es_sequence aseq){
	QByteArray datagram("es_g");
	datagram.append( aseq.high );
	datagram.append( aseq.low);
	Udp->writeDatagram(datagram, frnIP, writePort);
		while(gotThese.size() > 40)
		gotThese.pop_back();
		if( gotThese.end() == find(gotThese.begin(),gotThese.end(), aseq) )
		{gotThese.push_front(aseq);
		return 1;
		}
		else
		{
		return 0;
		}
	}
void es_reliUdp::storeData(QByteArray &datagram){
	if('v' == datagram.at(3))
	{
		saveData->push_back( datagram.right(datagram.size()-6));
		emit dataSaved();
	}else if('n' == datagram.at(3))
	{	saveData->push_back( datagram.right(datagram.size()-4));
		emit dataSaved();
	}
	}
void es_reliUdp::sync(){
	gotThese.clear();
	QByteArray datagram( "es_$" );
	Udp->writeDatagram(datagram, frnIP, writePort);
	}
void es_reliUdp::teleAnswer(){
	teleTimeOff = 0;
	stateStatus=1;
	disconnect(teleTimer, SIGNAL(timeout()), this, SLOT(teleAsk()));
	connect(teleTimer, SIGNAL(timeout()), this, SLOT(teleSig()));
	sync();
	}
void es_reliUdp::teleAsk(){
	QByteArray datagram( "es_?" );
	Udp->writeDatagram(datagram, frnIP, writePort);
	++teleTimeOff;
	}
void es_reliUdp::teleSig(){
	QByteArray datagram( "es_a" );
	Udp->writeDatagram(datagram, frnIP, writePort);
	++teleTimeOff;
	}
	
void es_reliUdp::teleReceive(){
		teleTimeOff = 0;
	}
void es_reliUdp::teleRead(){
		while(Udp->hasPendingDatagrams())
		{
		QByteArray datagram;
		datagram.resize(Udp->pendingDatagramSize());
		Udp->readDatagram(datagram.data(), datagram.size(), NULL, NULL);
		if(datagram.startsWith("es_"))
		receivePacket(datagram);
		}
	}
void es_reliUdp::resendTemp(){
	std::list<packet_info>::iterator ipack = saveTemp.begin();
	while( ipack != saveTemp.end() )
	{	//if(0 != ipack->resendAttempt)
		Udp->writeDatagram(ipack->data, frnIP, writePort);
		++ipack->resendAttempt;
		if(ipack->resendAttempt > 120)
		{ipack=saveTemp.erase(ipack);
		std::cout<<"Resend Attempts 120, ruClient"<<std::endl;
		}
		else
		++ipack;
	}
	}


//void es_reliUdp::teleFound(){
//}

es_reliUdp::es_reliUdp(std::list<QByteArray> *tmpsave, QObject *parent) : QObject(parent){
saveData=tmpsave;
	errorCode = 0;
	errorMessage = "";
	stateStatus = -1;
//	sequence = 0;
	teleTimeOff = 0;
	resendLOT = 25;
	resendTimer = new QTimer;
	connect(resendTimer, SIGNAL(timeout()), this, SLOT(resendTemp()));
	teleTimer = new QTimer;
//	connect(teleTimer, SIGNAL(timeout()), this, SLOT(teleSig()));
//	connect(teleTimer, SIGNAL(timeout()), this, SLOT(teleAsk()));
	}
