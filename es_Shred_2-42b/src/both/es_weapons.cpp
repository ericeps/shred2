


#include "es_weapons.h"
#include <list>
#include "defs.h"
#include "es_avatar.h"
#include "es_net.h"
#include "es_basegame.h"
#include <cmath>

es_weapons::es_weapons(es_basegame *agm)
{
GameInfo=agm;
fireStatus = 0;
throwWind = 0;
throwStatus = 0;
Energy.Collision = new phelColl(0);
Bombs.Collision = new phelColl(0);
Throw.Collision = new phelColl(0);
Slime.Collision = new phelColl(0);
Fire.Collision = new phelColl(-5);
}
es_weapons::~es_weapons()
{
}

void es_weapons::setNet(es_net *anet){
	Net = anet;
	}

void es_weapons::setVars(es_avatar *anav){
	Avatar = anav;
	}

void es_weapons::action()
	{
		if(fireStatus == 1)
		addFire();
		if(throwStatus ==1)
		{	if(++throwWind > 130)
			throwWind=130;
		}

	}



void es_weapons::onFire(){
fireStatus=1;
}
void es_weapons::offFire(){
fireStatus=0;
}
void es_weapons::startThrow() {
throwStatus=1;
}
void es_weapons::finishThrow() {
throwStatus=0;
	addThrow(-3.5-(throwWind*.04));
	throwWind=0;
}

void es_weapons::addEnergy(){
	if(Avatar->stockEnergy() > 0)
	{	phelit *tmpenergy = new phelit;
	tmpenergy->shift.x = sin(Avatar->getTheta()*3.14159/180)*-6;
	tmpenergy->shift.z = cos(Avatar->getTheta()*3.14159/180)*-6;
	tmpenergy->shift.y = 0;
	tmpenergy->location.x = Avatar->Front().x + tmpenergy->shift.x;
	tmpenergy->location.z = Avatar->Front().z + tmpenergy->shift.z;
	tmpenergy->location.y = Avatar->Front().y;
	tmpenergy->pID = GameInfo->getmyID();
		Energy.push_back(tmpenergy);
		Avatar->takeEnergy();
	if(GameInfo->isMultigame())
	Net->sendEnergy(tmpenergy);
	}
}
void es_weapons::addBomb(){
	if(Avatar->stockBombs() > 0)
	{	phelit *tmpbomb = new phelit;
	tmpbomb->shift.x = 0;
	tmpbomb->shift.z = 0;
	tmpbomb->shift.y = -.5;
	tmpbomb->location.x = Avatar->Back().x + (sin(Avatar->getTheta()*3.14159/180)*12);
	tmpbomb->location.z = Avatar->Back().z + (cos(Avatar->getTheta()*3.14159/180)*12);
	tmpbomb->location.y = Avatar->Back().y+3;
	tmpbomb->pID = GameInfo->getmyID();
		Bombs.push_back(tmpbomb);
		Avatar->takeBomb();
	if(GameInfo->isMultigame())
	Net->sendBomb(tmpbomb);
	}
}
void es_weapons::addThrow(float windup){
	if(Avatar->stockThrow() > 0)
	{	phelit *tmpthrow = new phelit;
		tmpthrow->shift.x = sin(Avatar->getTheta()*3.14159/180)*(windup);
		tmpthrow->shift.z = cos(Avatar->getTheta()*3.14159/180)*(windup);
		tmpthrow->shift.y = -windup*.7;
		tmpthrow->location.x = Avatar->Center().x;// + tmpthrow->shift.x;
		tmpthrow->location.z = Avatar->Center().z;// + tmpthrow->shift.z;
		tmpthrow->location.y = Avatar->Front().y + 8;
		tmpthrow->pID = GameInfo->getmyID();
			Throw.push_back(tmpthrow);
			Avatar->takeThrow();
	if(GameInfo->isMultigame())
		Net->sendThrow(tmpthrow);
	}
}
void es_weapons::addSlime(){
	if(Avatar->stockSlime() > 0)
	{	phelit *tmpslime = new phelit;
	tmpslime->shift.x = sin(Avatar->getTheta()*3.14159/180)*(-3+(Avatar->getHeadMomentum()*.05));
	tmpslime->shift.z = cos(Avatar->getTheta()*3.14159/180)*(-3+(Avatar->getHeadMomentum()*.05));
	tmpslime->shift.y = .05;
	tmpslime->location.x = Avatar->Front().x + (tmpslime->shift.x*2);
	tmpslime->location.z = Avatar->Front().z + (tmpslime->shift.z*2);
	tmpslime->location.y = Avatar->Front().y;
	tmpslime->pID = GameInfo->getmyID();
		Slime.push_back(tmpslime);
		Avatar->takeSlime();

	if(GameInfo->isMultigame())
	Net->sendSlime(tmpslime);
	}
}
void es_weapons::addFire(){
	if(Avatar->stockFire() > 0)
	{	phelcit *tmpfire = new phelcit;
	tmpfire->shift.x = sin(Avatar->getTheta()*3.14159/180)*-6;
	tmpfire->shift.z = cos(Avatar->getTheta()*3.14159/180)*-6;
	tmpfire->shift.y = 0;
	tmpfire->location.x = Avatar->Front().x + tmpfire->shift.x;
	tmpfire->location.z = Avatar->Front().z + tmpfire->shift.z;
	tmpfire->location.y = Avatar->Front().y;
	tmpfire->custom = 15;
	tmpfire->pID = GameInfo->getmyID();
		Fire.push_back(tmpfire);
		Avatar->takeFire();
	if(GameInfo->isMultigame())
	Net->sendFire(tmpfire);
	}
}

void es_weapons::netEnergy(phelit *data){
Energy.push_back(data);
}
void es_weapons::netBomb(phelit *data){
Bombs.push_back(data);
}
void es_weapons::netThrow(phelit *data){
Throw.push_back(data);
}
void es_weapons::netSlime(phelit *data){
Slime.push_back(data);
}
void es_weapons::netFire(phelcit *data){
Fire.push_back(data);
}




/*
void es_weapons::addEnergyExplosion(point3f& apoint)
{
	es_ending tmpexp;
	tmpexp.location = apoint;
	tmpexp.custom = 0;
	Energy.Explosions.push_back(tmpexp);
}
void es_weapons::addFireExplosion(point3f& apoint)
{
	es_ending tmpexp;
	tmpexp.location = apoint;
	tmpexp.custom = -5;
	Fire.Explosions.push_back(tmpexp);
}
void es_weapons::addBombExplosion(point3f& apoint,unsigned char pID)
{
	es_ending tmpexp;
	tmpexp.location = apoint;
	tmpexp.custom = 0;
	if(Avatar->isWithin(apoint,30))
		Avatar->dealDamage(14,pID);
	Bombs.Explosions.push_back(tmpexp);
}
void es_weapons::addSlimeExplosion(point3f& apoint)
{
	es_ending tmpexp;
	tmpexp.location = apoint;
	tmpexp.custom = 0;
	Slime.Explosions.push_back(tmpexp);
}*/
