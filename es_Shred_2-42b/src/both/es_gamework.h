/*  Creates/destroys Game objects and distributes pointers to classes who use it
    for both Single-player and Multiplayer.
 */

#ifndef ES_GAMEWORK
#define ES_GAMEWORK

#include "defs.h"
#include <list>

class es_client;
class es_MPgame;
class es_SPgame;

class es_avatar;
class es_world;
class es_weapons;
class es_players;
class es_pickupcon;
class es_enemies;

class es_control;
class es_compose;
class es_key;
class es_actionTimer;
class es_draw;
class es_net;
class es_qtgl;
class es_collision;

class es_gamework
{
public:
es_gamework(es_MPgame *);
es_gamework(es_SPgame *);
~es_gamework();
void MPStart(std::list<unsigned char> &opponentList, int map);
void SPStart(int map, int difficulty);
void stopGame();

private:
es_client *myClient;
es_net *Net;

es_MPgame *MPgame;
es_SPgame *SPgame;

es_avatar *Avatar;
es_pickupcon *Pickup;
es_world *World;
es_weapons *Weapons;
es_players *Players;
es_control *Control;
es_key *Key;
es_collision *Collision;
es_enemies *Enemies;

es_compose *Compose;
es_actionTimer *Action;
es_draw *Draw;
es_qtgl *Es_qtgl;
bool isMultigame;
};

#endif
