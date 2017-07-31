/* Widget for changing network connection settings.

 */

#ifndef ES_UINet
#define ES_UINet

//class es_server;
//class es_client;
class es_MPgame;

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QListWidget;
class QMenuBar;
class QAction;
class QMenu;
#include <QWidget>

class es_UINet : public QWidget
{
	Q_OBJECT
public:
	es_UINet(es_MPgame*,QWidget *parent=0);
void setClientStatus(int astat,QString sstat="");
void setServerStatus(int astat,QString sstat="");
void nameDialog(QString message="");

private slots:
	void servCBoxChanged(bool);
	void startServer();
	void startClient();
	void stopClient();
	void stopServer();
private:

	QString Port1,Port2;
//	es_server *myServer;
//	es_client *myClient;
	es_MPgame *GameInfo;

QLabel *clientStatus;
QLabel *serverStatus;

QLineEdit *clientLineEdit;
QPushButton *clientButton;

QLineEdit *servLineEdit;
QCheckBox *servCBox;
//QPushButton *serverButton;

};

#endif
