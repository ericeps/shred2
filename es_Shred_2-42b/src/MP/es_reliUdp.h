/* UDP client.  Must be connected to a es_reliUdpServer before packets can be sent.
    Reliable transfer to server or other clients.
 */
#ifndef ES_RELIUDP
#define ES_RELIUDP

#include "netdefs.h"
#include <QByteArray>
#include <QObject>
#include <QHostAddress>
#include <string>
#include "es_sequence.h"
class QTimer;
class QUdpSocket;


class es_reliUdp : public QObject
{
	Q_OBJECT
public:
es_reliUdp(std::list<QByteArray> *, QObject *parent=0);

bool setConnectionInfo(QString,QString,int, int);
bool start();
bool stop();
void sendVerify(QByteArray &datagram);
void sendNoverify(QByteArray &datagram);
void sendtoServer(QByteArray &datagram);
//QByteArray getNext();

int getErrorCode();
QString getErrorMessage();
int getState();

unsigned int getTeleTimeOff();
void resetTeleTimeoff();
int sizeTemp();
void clearTemp();
int sizeData();
void clearData();
bool hasData();

private:
void receivePacket(QByteArray &datagram);
void confirmedData(es_sequence );
bool sendConfirm(es_sequence );
void storeData(QByteArray &datagram);
void teleReceive();
void teleAnswer();
void sync();

private slots:
void teleAsk();
void teleSig();
void teleRead();
void resendTemp();

signals:
//void teleFound();
void dataSaved();

protected:
unsigned int teleTimeOff;

private:
quint16 writePort;
quint16 readPort;
QHostAddress frnIP;
QHostAddress myIP;

int errorCode;
QString errorMessage;
int stateStatus;

std::list<es_sequence> gotThese;
es_sequence Seq;
QTimer *teleTimer;
int resendLOT;
QTimer *resendTimer;

std::list<packet_info> saveTemp;
std::list<QByteArray> *saveData;
QUdpSocket *Udp;

};

#endif
