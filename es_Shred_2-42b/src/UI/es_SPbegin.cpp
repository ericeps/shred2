
#include "es_SPbegin.h"
#include "es_SPgame.h"
#include "es_SPSett.h"

#include <QApplication>
#include <QHostAddress>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QObject>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QTabWidget>


es_SPbegin::es_SPbegin(es_SPgame *agame,QWidget *parent) : QWidget(parent)
	{
		GameInfo = agame;
	}

void es_SPbegin::setupUI(){

		SPSett = GameInfo->getSPSett();

		startGameButton = new QPushButton(tr("Start Game"));
		connect(startGameButton,SIGNAL(clicked()),this,SLOT(requestStartGame()));

		QPushButton *mullButt = new QPushButton(tr("MullAgain"));
		connect(mullButt,SIGNAL(clicked()),this,SLOT(mullAgain()));

		TabWidget = new QTabWidget;
		TabWidget->addTab(SPSett,"Settings");

		QVBoxLayout *VLayout = new QVBoxLayout;
		VLayout->addWidget(TabWidget);
		VLayout->addWidget(startGameButton);
	VLayout->addWidget(mullButt);

		setLayout(VLayout);
	}

void es_SPbegin::requestStartGame(){
	GameInfo->startGame(SPSett->currentMap(),1);
	disconnect(startGameButton,SIGNAL(clicked()),this,SLOT(requestStartGame()));
	connect(startGameButton,SIGNAL(clicked()),this,SLOT(stopGame()));
	startGameButton->setText(tr("Stop Game"));
	}
void es_SPbegin::stopGame(){
	GameInfo->stopGame();
	disconnect(startGameButton,SIGNAL(clicked()),this,SLOT(stopGame()));
	connect(startGameButton,SIGNAL(clicked()),this,SLOT(requestStartGame()));
	startGameButton->setText(tr("Start Game"));
	}
void es_SPbegin::mullAgain(){
	GameInfo->mullAgain();
}