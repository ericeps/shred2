
#include "es_MPbegin.h"

#include "es_MPgame.h"
#include "es_UINet.h"
#include "es_MPSett.h"

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
#include <QToolBar>
#include <QWidget>



es_MPbegin::es_MPbegin(es_MPgame *agame,QWidget *parent) : QWidget(parent)
	{
		GameInfo = agame;
	}

void es_MPbegin::setupUI(){
	
		UINet = GameInfo->getUINet();
		MPSett = GameInfo->getMPSett();

		startGameButton = new QPushButton(tr("Start Game"));
		startGameButton->setEnabled(false);
		connect(startGameButton,SIGNAL(clicked()),this,SLOT(requestStartGame()));
		
		QPushButton *mullButt = new QPushButton(tr("MullAgain"));
		connect(mullButt,SIGNAL(clicked()),this,SLOT(mullAgain()));

		TabWidget = new QTabWidget;
		TabWidget->addTab(UINet,"Network");
		TabWidget->addTab(MPSett,"Settings");

		QVBoxLayout *VLayout = new QVBoxLayout;
		VLayout->addWidget(TabWidget);
		VLayout->addWidget(startGameButton);
	VLayout->addWidget(mullButt);

		setLayout(VLayout);
//		UINet->setFocus();
	}

void es_MPbegin::requestStartGame(){
	GameInfo->requestStartGame();
	}
void es_MPbegin::stopGame(){
	GameInfo->stopGame();
	}
void es_MPbegin::mullAgain(){
GameInfo->mullAgain();
}