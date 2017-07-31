
#include "es_UIChat.h"
#include "es_client.h"
#include "es_MPbegin.h"
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QTextTable>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "es_MPgame.h"

es_UIChat::es_UIChat(es_MPgame *gm,QWidget *parent) : QWidget(parent)
{
	GameInfo = gm;

	lineEdit = new QLineEdit;
	lineEdit->setFocusPolicy(Qt::StrongFocus);
	lineEdit->setEnabled(0);
	messageArea = new QTextEdit;
	messageArea->setFocusPolicy(Qt::NoFocus);
	messageArea->setReadOnly(1);
	playerList = new QListWidget;
	playerList->setFocusPolicy(Qt::NoFocus);
	
	tableFormat.setBorder(0);

	connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
	
	QHBoxLayout *HLayout = new QHBoxLayout;
	HLayout->addWidget(messageArea);
	HLayout->addWidget(playerList);
	
	QVBoxLayout *VLayout = new QVBoxLayout;
	VLayout->addLayout(HLayout);
	VLayout->addWidget(lineEdit);

	setLayout(VLayout);
}

void es_UIChat::startChat(std::list<QString> namelist){
//	Client = GameInfo->getClient();

//	connect(Client, SIGNAL(newMessage(QString,QString&)),
//			UIChat, SLOT(appendMessage(QString,QString&)));
//	connect(Client, SIGNAL(newPlayer(QString&)),
//			UIChat, SLOT(newPlayer(QString&)));
//	connect(Client, SIGNAL(delPlayer(QString&)),
//			UIChat, SLOT(delPlayer(QString&)));

	std::list<QString>::iterator ii;
	for(ii=namelist.begin();ii!=namelist.end();ii++)
	playerList->addItem(*ii);
	QString myname = GameInfo->getName();
	newPlayer(myname);
	lineEdit->setEnabled(1);
	}

void es_UIChat::stopChat(){
	playerList->clear();
	messageArea->clear();
	lineEdit->setEnabled(0);
//	disconnect(Client, SIGNAL(newMessage(QString,QString&)),
//			UIChat, SLOT(appendMessage(QString,QString&)));
//	disconnect(Client, SIGNAL(newPlayer(QString&)),
//			UIChat, SLOT(newPlayer(QString&)));
//	disconnect(Client, SIGNAL(delPlayer(QString&)),
//			UIChat, SLOT(delPlayer(QString&)));
	}

void es_UIChat::returnPressed(){
	QString message = lineEdit->text();
	if (message.isEmpty())
	return;
//	Client->sendMessage(GameInfo->getName(), message);
	emit sendMessage(GameInfo->getName(), message);
	appendMessage(GameInfo->getName(),message);
	lineEdit->clear();
}

void es_UIChat::appendMessage(QString name,QString &message){
	QTextCursor cursor(messageArea->textCursor());
	cursor.movePosition(QTextCursor::End);
	QTextTable *tmpTable = cursor.insertTable(1,2,tableFormat);
	tmpTable->cellAt(0,0).firstCursorPosition().insertText('<'+name+"> ");
	tmpTable->cellAt(0,1).firstCursorPosition().insertText(message);
	messageArea->ensureCursorVisible();
}
void es_UIChat::newPlayer(QString &name){
	messageArea->setTextColor(Qt::gray);
	messageArea->append(tr("* %1 has joined").arg(name));
	messageArea->setTextColor(Qt::black);
	playerList->addItem(name);
}
void es_UIChat::delPlayer(QString &name){
	QList<QListWidgetItem *> items = playerList->findItems(name,Qt::MatchExactly);

	if(!items.isEmpty())
	delete items.at(0);
	messageArea->setTextColor(Qt::gray);
	messageArea->append(tr("* %1 has left").arg(name));
	messageArea->setTextColor(Qt::black);
}

//void es_UIChat::setVis(bool tmp){

//	}