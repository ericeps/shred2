
#include "es_UIStats.h"
#include "es_MPgame.h"
#include <QVBoxLayout>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <QHeaderView>

es_UIStats::es_UIStats(es_MPgame *gm,QWidget *parent) : QWidget(parent){
	GameInfo = gm;
	scoreTable = new QTableWidget(this);
	scoreTable->setColumnCount(5);
	QStringList alist;
	alist << "Name"<<"Kills"<<"Deaths"<<"Damage"<<"Slimes";
	scoreTable->setHorizontalHeaderLabels(alist);
	scoreTable->verticalHeader()->hide();
	QVBoxLayout *alayout = new QVBoxLayout;
	alayout->addWidget(scoreTable);
	setLayout(alayout);
	}

void es_UIStats::setupPlayers(std::list<unsigned char> &oplist,std::list<const char*> &opnames){
EndStats.clear();
RawStats.clear();
scoreTable->clearContents();
	es_endStats tmpcalc(GameInfo->getmyID(),GameInfo->getName());
	EndStats.push_back(tmpcalc);
	std::list<unsigned char>::iterator ii;
	std::list<const char*>::iterator ia=opnames.begin();
	for(ii=oplist.begin();ii!=oplist.end();ii++)
	{
	es_endStats tmpCalc(*ii,*ia);
	EndStats.push_back(tmpCalc);
	ia++;
	}
	scoreTable->setRowCount(EndStats.size());
//	show();
	resize(550,400);
	move(100,200);
	}

void es_UIStats::setData(unsigned char aID, std::list<es_pstats> alist){
	std::list<es_pstats>::iterator ip;
	std::list<es_endStats>::iterator icalc;
	std::list<es_endStats>::iterator ihost;

		for(ip=alist.begin();ip!=alist.end();ip++)
		{
			icalc = std::find(EndStats.begin(),EndStats.end(),ip->ID);
			icalc->Kills += ip->Kills;
			icalc->Damage += ip->Damage+.5;	//add .5 for rounding purposes
			icalc->Slimes += ip->Slows;
			ihost = std::find(EndStats.begin(),EndStats.end(),aID);
			ihost->Deaths += ip->Kills;
		}

	es_rawStats tmpRaw;
	tmpRaw.ID = aID;
	tmpRaw.Stats = alist;
	RawStats.push_back(tmpRaw);
	
for_each( EndStats.begin(), EndStats.end(),std::mem_fun_ref(&es_endStats::showInfo) );
	showStats();
	}

void es_UIStats::showStats(){
	scoreTable->clearContents();
	int row=0;
	std::list<es_endStats>::iterator ie;
	for(ie=EndStats.begin();ie!=EndStats.end();ie++)
	{
		scoreTable->setItem(row,0,new QTableWidgetItem(ie->Name));
		scoreTable->setItem(row,1,new QTableWidgetItem(QString::number(ie->Kills)));
		scoreTable->setItem(row,2,new QTableWidgetItem(QString::number(ie->Deaths)));
		scoreTable->setItem(row,3,new QTableWidgetItem(QString::number(ie->Damage)));
		scoreTable->setItem(row,4,new QTableWidgetItem(QString::number(ie->Slimes)));
		
		scoreTable->item(row,0)->setFlags(Qt::NoItemFlags);
		scoreTable->item(row,1)->setFlags(Qt::NoItemFlags);
		scoreTable->item(row,2)->setFlags(Qt::NoItemFlags);
		scoreTable->item(row,3)->setFlags(Qt::NoItemFlags);
		scoreTable->item(row,4)->setFlags(Qt::NoItemFlags);
		
	++row;
	}
	show();
	raise();
	}