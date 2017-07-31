/* Network client for game/program.  Uses reliUdp to set up connection.

 */
#ifndef ES_CLIENT
#define ES_CLIENT

#include <QObject>
#include <QtNetwork>		// QT += network

class es_net;
class es_MPgame;
class es_pInfo;
#include "es_reliUdp.h"
#include <QHostAddress>
#include <QString>


class es_client : public es_reliUdp
{
	Q_OBJECT
public:
	es_client(es_MPgame*, QObject *parent=0);
	void setNet(es_net*);

	bool startClient(QString,QString,QString,QString);
	void stopClient();
	void connectToServer(QString aname);
	void disconnectFromServer();
	void interpretData(QByteArray &tmp);
	void dieAtTimeout(bool tmp);
	void requestStart();
	
	void sendEndInfo(es_pInfo*);
	void changeMap(int);
	void changeDuration(int);
private slots:
	void cteleFound();
	void teleCheck();
	void newDataSlot();
	void killConnection();
	void sendMessage(QString,QString&);

signals:
	void newPlayer(QString&);
	void delPlayer(QString&);
	void newMessage(QString,QString&);

private:
	bool canTimeout;
	std::list<QByteArray> saveData;
	es_net *Net;
	es_MPgame *GameInfo;
	QTimer *statusTimer;
};

#endif

