/* UDP Server.  Facilitates reliable transfer of packets between
    clients of class es_reliUdp.

 */

#ifndef RELIUPDSERVER_H
#define RELIUPDSERVER_H

#include "netdefs.h"
#include "es_sequence.h"
#include <QByteArray>
#include <list>
//#include <QUdpSocket>
#include <QHostAddress>
#include <QObject>
class QTimer;
class QUdpSocket;
#include <string>


struct es_clientInfo{
	QHostAddress IP;
	unsigned int teleTimeOff;
	std::list<packet_info> saveTemp;
	es_sequence Seq;
	std::list<es_sequence> gotThese;

	bool operator==(const QHostAddress& aadd){
		return (IP == aadd);
		}
	void addPacket(packet_info &pack){
		++Seq;
		pack.data[4] = Seq.high;
		pack.data[5] = Seq.low;
		saveTemp.push_back(pack);
		}
/*	void reset(){
		teleTimeOff=0;
//		saveTemp.clear();
//		Seq.high=0;
//		Seq.low=0;
		gotThese.clear();
		}
*/
	es_clientInfo(){teleTimeOff=0;}
};

struct es_fromClient{
	QHostAddress IP;
	QByteArray data;
	};

class es_reliUdpServer : public QObject
{
	Q_OBJECT
public:
es_reliUdpServer(std::list<es_fromClient>*, QObject *parent=0);

bool setConnectionInfo(QString,int, int);
bool start();
bool stop();
void sendVerify(QByteArray &datagram);
void sendNoverify(QByteArray &datagram);
void sendToIP(QByteArray &datagram,QHostAddress &tmpIP);
void addSyncCli(QHostAddress &cliIP);
void delClient(QHostAddress &cliIP);

int getErrorCode();
QString getErrorMessage();
int getState();
int countClients();

void clearTemp();
void lock(bool );

private:
bool newClient(QHostAddress &cliIP);
void addClient(QHostAddress &cliIP);
void receivePacket(QByteArray &datagram,QHostAddress&);
void confirmedData(es_sequence, std::list<es_clientInfo>::iterator);
bool sendConfirm(es_sequence, QHostAddress&);
void distributeData(QByteArray &datagram,QHostAddress&);
void pipeNoverify(QByteArray &datagram,QHostAddress&);
void storeData(QByteArray &datagram,QHostAddress &cliIP);
void vteleSig(std::list<es_clientInfo>::iterator);

private slots:
void teleRead();
void resendTemp();
void testTimeout();

signals:
void dataSaved();
void clientAsk(QHostAddress&);
void clientSynced(QHostAddress&);
void cliTimedOut(QHostAddress&);

private:
bool autoadd;
bool locked;
quint16 writePort;
quint16 readPort;
QHostAddress myIP;


int errorCode;
QString errorMessage;
int stateStatus;

int resendLOT;
QTimer *resendTimer;
QTimer *checkTimeOff;
unsigned int maxCliTimeOff;

std::list<QHostAddress> syncList;
std::list<es_clientInfo> ClientList;

std::list<es_fromClient> *fromClient;
QUdpSocket *Udp;


};

#endif
