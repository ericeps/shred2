
#include "es_control.h"
#include "es_key.h"
#include "es_avatar.h"
#include "es_collision.h"
#include "es_draw.h"
#include "es_enemies.h"
#include "defs.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

void es_control::setVars(es_key *akey,es_avatar* anav,es_collision *acol, es_draw *adraw, es_enemies *enem)
{
Key=akey;
Avatar=anav;
Draw=adraw;
Enemies=enem;
Collision=acol;
}
/*
void es_control::setKey(es_key *akey){
	Key = akey;
	}
void es_control::setAvatar(es_avatar *anav){
	Avatar = anav;
	}
*/


void es_control::death()
	{
	Key->enableMove(0);
	if(!isMulti)
	Enemies->killMemory();
	Alive=0;
	Draw->camDeath(Avatar->Center(), Avatar->getTheta());
	point3f tmploc;
	tmploc.x=-1000;
	tmploc.y=-1000;
	tmploc.z=-1000;
	Collision->avDeath();
	Avatar->Placement(tmploc,1);
	cout<<"DEATH1234"<<endl;
	}

void es_control::live()
	{
	Avatar->reset();
	int tmprand;
	tmprand = rand() % Respawn.size();
	Avatar->Placement(Respawn.at(tmprand).location,Respawn.at(tmprand).theta);
	Draw->camLive();
	Collision->avLive();
	Key->enableMove(1);
	Alive=1;
//	std::cout<<"REspawn size == "<< Respawn.size()<<std::endl;
	}
bool es_control::isAlive(){
	return Alive;
	}
void es_control::setupRespawn(std::vector<es_respawn>& ares)
	{
	Respawn = ares;
	}

es_control::es_control(bool isMul)
	{
//	GameInfo = agame;
	isMulti=isMul;
	tmploc.x=-3000;
	tmploc.y=-3000;
	tmploc.z=-3000;
	srand(time(0));
	}
