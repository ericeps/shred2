/* Composes levels.
    Creates walls, respawn points, pickups, enemies.
 */
#ifndef ES_COMPOSE_H
#define ES_COMPOSE_H
#include "defs.h"
#include <vector>

class es_world;
class es_control;
class es_pickupcon;
class es_enemies;

class es_compose
{
public:
es_compose(bool);
void setVars(es_world* aw,es_control* acon, es_pickupcon* apick, es_enemies* enem=0);
//	void setWorld(es_world*);
//	void setControl(es_control*);
//	void setPickup(es_pickupcon*);
	void makeMap(int);
	void map_1(int);
	void map_1_respawn(int);
	void map_1_pickup(int);
	void map_1_enemies(int);
	void map_2(int);
	void map_2_respawn(int);
	void map_2_pickup(int);
	void map_2_enemies(int);
	void map_3(int);
	void map_3_respawn(int);
	void map_3_pickup(int);
	void map_3_enemies(int);
        void map_4(int);
        void map_4_respawn(int);
        void map_4_pickup(int);
        void map_4_enemies(int);
	
void calcOuterBound(std::vector< std::vector <es_bound> > &boundList, unsigned int ax, unsigned int az, unsigned int aLevels);
static es_bound makeBound(int x, int z, unsigned int xl, unsigned int zl, CORNER Corner = NL);
static es_bound makeBound(es_brick&);

static es_brick makeBrick(int x, int z, unsigned int xl, unsigned int zl, int y1, int y2, CORNER Corner = NL,float ar=.7,float ag=.7,float ab=.7);
static es_brick makeBrick(es_bound&, int y1, int y2,float ar=.7,float ag=.7,float ab=.7);

private:
	es_world *World;
	es_control *Control;
	es_pickupcon *Pickup;
	es_enemies *Enemies;
bool isMulti;
};


#endif
