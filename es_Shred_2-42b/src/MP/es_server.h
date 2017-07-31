/* Network server for game/program.  Uses reliUdpServer to set up connection.
  */
#ifndef ES_SERVER
#define ES_SERVER

#include "es_reliUdpServer.h"

#include <QObject>
#include <QtNetwork>		// QT += network
#include <list>
#include <string>
class QTimer;

struct es_playerInfo{
unsigned char ID;
QByteArray name;
QHostAddress IP;

bool operator==(const QHostAddress& aadd){
	return (IP == aadd);
	}
bool operator==(const QByteArray& aname){
	return (name == aname);
	}

};

class es_server : public QObject
{
	Q_OBJECT
public:
es_server(QObject *parent=0);
//void setReliUdpServer( es_reliUdpServer*);


bool start(QString, QString, QString);
void stop();

QString getErrorMessage();

private slots:
void newDataSlot();
void endGame();
void newClientRequest(QHostAddress &cliIP);
void newClientSynced(QHostAddress &cliIP);
void cliTimedOutSlot(QHostAddress&);
private:
void addNewPlayer(QHostAddress &cliIP,QByteArray aname);
void interpretData(es_fromClient &cldatagram);
void deletePlayer(QHostAddress &cliIP);
bool gameOn;
es_reliUdpServer *ReliUdpServer;
std::list<es_fromClient> fromClient;
std::list<es_playerInfo> PlayerList;
QTimer *GameTimerCountdown;

int Map;
int GameDuration;
int GameStock;
};

#endif


