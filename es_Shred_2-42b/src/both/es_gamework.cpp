
#include "es_gamework.h"

#include "es_qtgl.h"
#include "es_key.h"
#include "es_avatar.h"
#include "es_control.h"
#include "es_weapons.h"
#include "es_world.h"
#include "es_compose.h"
#include "es_actionTimer.h"
#include "es_net.h"
#include "es_players.h"
#include "es_client.h"
#include "es_MPgame.h"
#include "es_SPgame.h"
#include "es_pickupcon.h"
#include "es_collision.h"
#include "es_draw.h"
#include "es_enemies.h"
#include <list>
#include <iostream>

es_gamework::es_gamework(es_MPgame *ainfo){
	MPgame = ainfo;
	isMultigame=1;
	}
es_gamework::es_gamework(es_SPgame *ainfo){
	SPgame = ainfo;
	isMultigame=0;
	}
void es_gamework::MPStart(std::list<unsigned char> &opponentList,int amap)
{
	Avatar = new es_avatar(isMultigame);
	Players = new es_players;
	Pickup = new es_pickupcon;
	World = new es_world;
	Weapons = new es_weapons(MPgame);
//	Enemies = new es_enemies;
	Control = new es_control(isMultigame);
	Compose = new es_compose(isMultigame);
	Key = new es_key;
	Action = new es_actionTimer(isMultigame);
	Draw = new es_draw(isMultigame);
	Collision = new es_collision(isMultigame);
	Es_qtgl = MPgame->getGL();


	Net = new es_net(MPgame);
	myClient = MPgame->getClient();

	myClient->setNet(Net);
	Net->setClient(MPgame->getClient());
	Net->setWeapons(Weapons);
	Net->setPlayers(Players);
	Avatar->setNet(Net);
	Weapons->setNet(Net);

	Es_qtgl->setVars(Key,Draw);
	Draw->setVars(World,Avatar,Weapons,Pickup,Players);
	Compose->setVars(World,Control,Pickup);
	Key->setVars(Avatar,Weapons);
	Control->setVars(Key,Avatar,Collision,Draw);
	Avatar->setVars(World,Control,MPgame->getPInfo());
	Avatar->setColorIndex(MPgame->getmyID()%10);
	Weapons->setVars(Avatar);
	Action->setVars(Avatar,Weapons,Pickup,World,Es_qtgl,Collision);
	Collision->setVars(World,Avatar,Weapons,Pickup,Players);

Players->addEnemies(opponentList);
Compose->makeMap(amap);
Control->live();

Action->startTimer();
}

void es_gamework::SPStart(int amap,int difficulty)
{
	Avatar = new es_avatar(isMultigame);
//	Players = new es_players;
	Pickup = new es_pickupcon;
	World = new es_world;
	Weapons = new es_weapons(SPgame);
	Enemies = new es_enemies;
	Control = new es_control(isMultigame);
	Compose = new es_compose(isMultigame);
	Key = new es_key;
	Action = new es_actionTimer(isMultigame);
	Draw = new es_draw(isMultigame);
	Collision = new es_collision(isMultigame);
	Es_qtgl = SPgame->getGL();

	Enemies->setVars(World);
	Es_qtgl->setVars(Key,Draw);
	Draw->setVars(World,Avatar,Weapons,Pickup,0,Enemies);
	Compose->setVars(World,Control,Pickup,Enemies);
	Key->setVars(Avatar,Weapons);
	Control->setVars(Key,Avatar,Collision,Draw,Enemies);
	Avatar->setVars(World,Control);
	Avatar->setColorIndex(SPgame->getmyID()%10);
	Weapons->setVars(Avatar);
	Action->setVars(Avatar,Weapons,Pickup,World,Es_qtgl,Collision,Enemies);
	Collision->setVars(World,Avatar,Weapons,Pickup,0,Enemies);

//Players->addEnemies(opponentList);
Compose->makeMap(amap);
Control->live();

Action->startTimer();
}
void es_gamework::stopGame()
{	Action->stopTimer();

	delete Avatar;
	delete Pickup;
	delete World;
	delete Weapons;
	delete Control;
	delete Compose;
	delete Key;
	delete Action;
	delete Draw;
	delete Collision;
	if(isMultigame)
	{	delete Net;
		delete Players;
	}
	else
	delete Enemies;
}
es_gamework::~es_gamework()
{es_basegame *GameInfo;
if(isMultigame)
GameInfo = MPgame;
else
GameInfo = SPgame;
if(GameInfo->isGameOn())
stopGame();
}
