#include "chooseGame.h"

#include <QPushButton>
#include <QHBoxLayout>
#include "es_MPgame.h"
#include "es_SPgame.h"

chooseGame::chooseGame(QWidget *parent):QWidget(parent)
{
	Multi = new QPushButton(tr("Multiplayer"));
	Single = new QPushButton(tr("Single Player"));
	connect(Multi,SIGNAL(clicked()),this,SLOT(startMulti()));
	connect(Single,SIGNAL(clicked()),this,SLOT(startSingle()));
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(Single);
	layout->addWidget(Multi);
	setLayout(layout);
	gameStatus=0;
//	setAttribute(Qt::WA_DeleteOnClose,1);
}

void chooseGame::startMulti(){
MPgame = new es_MPgame(this);
MPgame->newUI();
gameStatus=1;
close();
}

void chooseGame::startSingle(){
SPgame = new es_SPgame(this);
SPgame->newUI();
gameStatus=2;
close();
}
void chooseGame::mullAgain(){
if(gameStatus==1)
delete MPgame;
else if(gameStatus==2)
delete SPgame;
gameStatus=0;
show();
}
void chooseGame::switchGame(){
	if(gameStatus==1)
	{	delete MPgame;
		startSingle();
	}
	else if(gameStatus==2)
	{	delete SPgame;
		startMulti();
	}
}