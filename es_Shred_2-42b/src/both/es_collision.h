/* On each main game loop moves things in the game world
   and checks for collisions.

 */

#ifndef ES_COLLISION
#define ES_COLLISION

#include "defs.h"
#include "physDefs.h"

class es_avatar;
class es_world;
class es_weapons;
class es_players;
class es_pickupcon;
class es_enemies;

class es_collision
{
public:
es_collision(bool);

void setVars(es_world* awor, es_avatar* anav, es_weapons* aweap, es_pickupcon* apick,es_players* aplay,es_enemies* anem=0);
void action();

	void isPickup();
void molim(phelit *item);	// move linearly
void mogim(phelit *item, float wgt);  // move with gravity

void changeCustom(phlist &, int ch);

void worldstops(phlist &);
void worldstops(phlist &,int he); //he is height above ground (y2+he)
void worldkills(phlist &);
void worldkillsFiAvadax(phlist &alist,int prox,int dmg);
void worldkillsAvadax(phlist &alist,int prox,int dmg);

void killsecond(phlist &first, phlist &second, int prox);
void killboth(phlist &first, phlist &second, int prox);

void damage(phlist &alist, int prox, float dmg);
void damageProx(phlist &alist,int prox, float dmg,int prox2, float dmg2);
void damageEnemies(phlist &alist,int prox, float dmg);
void damageAllEnemies(phlist &alist,int prox, float dmg,int prox2, float dmg2);
void chaserWithin(point3f &apoint, int prox, float dmg);
void changeSpeed(phlist &alist, int prox,float amt,float ttimer);
void chaserSlow(phlist &alist,int prox,float amt,float ttimer);
void compPlr(phlist &alist, int prox);

	void moveAvatar();
	bool Check_Move();
	void collisionDetail(es_ship4&);
	void Collision_Process();

void avDeath();
void avLive();

private:
es_avatar *Avatar;
es_weapons *Weapons;
es_pickupcon *Pickup;
es_world *World;
es_players *Players;
es_enemies *Enemies;
bool isMulti;
bool isAlive;
};

#endif

