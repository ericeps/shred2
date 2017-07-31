/* Widget showing end game stats.

 */
#ifndef UISTATS
#define UISTATS

#include <QWidget>
#include "es_pInfo.h"
#include <list>
#include <iostream>
#include <QTableWidget>

class es_MPgame;

struct es_rawStats{
//QString Name;
unsigned char ID;
std::list<es_pstats> Stats;
};

struct es_endStats{
QString Name;
unsigned char ID;
int Kills;
int Deaths;
int Damage;
int Slimes;
bool operator==(const unsigned char aID){return aID==ID;}
es_endStats(unsigned char aID, const char *aname){ID=aID;Name=aname;Kills=0;Deaths=0;Damage=0;Slimes=0;std::cout<<"endStats constructor "<<(int)ID<<std::endl;}
es_endStats(unsigned char aID, QString aname){ID=aID;Name=aname;Kills=0;Deaths=0;Damage=0;Slimes=0;}
void showInfo(){std::cout<<(int)ID<<" "<<Name.toStdString()<<" has "<<Kills<<" kills, "<<Deaths<<" deaths, "
	<<Damage<<" damage, and "<<Slimes<<" slimes."<<std::endl;}
};

class es_UIStats : public QWidget
{
	Q_OBJECT
public:
	es_UIStats(es_MPgame*,QWidget *parent=0);
	void setupPlayers(std::list<unsigned char> &oplist, std::list<const char*> &opnames);
	void setData(unsigned char, std::list<es_pstats>);
	void showStats();
	void showInfo(es_pstats astat);
private:
es_MPgame *GameInfo;
std::list<es_rawStats> RawStats;
std::list<es_endStats> EndStats;
QTableWidget *scoreTable;
};
#endif
