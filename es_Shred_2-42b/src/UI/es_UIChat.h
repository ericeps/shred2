/* Chat dialog box.

 */

#ifndef ES_UIChat
#define ES_UIChat

#include <QWidget>
class QListWidget;
class QTextEdit;
class QLineEdit;
class es_client;
class es_MPgame;
#include <QTextTableFormat>

class es_UIChat : public QWidget
{
	Q_OBJECT
public:
	es_UIChat(es_MPgame*,QWidget *parent=0);
	void startChat(std::list<QString> namelist);
	void stopChat();

public slots:
	void returnPressed();
	void appendMessage(QString,QString&);
	void newPlayer(QString&);
	void delPlayer(QString&);
signals:
	void sendMessage(QString,QString&);

private:
QTextEdit *messageArea;
QListWidget *playerList;
QLineEdit *lineEdit;
QTextTableFormat tableFormat;

//es_client *Client;
es_MPgame *GameInfo;
};

#endif
