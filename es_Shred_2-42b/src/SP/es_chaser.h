/* Single player enemy with AI set to chase the player and explode on impact.

 */

#ifndef ES_CHASER
#define ES_CHASER

#include <vector>
#include <list>
#include "defs.h"
#include "physDefs.h"
#include "enemyDefs.h"
#include "es_baseEnem.h"
//#include <iostream>

class es_chaserList : public es_baseEnemList{
	public:
	es_chaserList();
	//void SightWithin(point3f &apoint,int layer);
	virtual void justSpotted(std::list<es_baseEnem>::iterator apoint);
	virtual void spottedInMem(std::list<es_baseEnem>::iterator apoint);
	virtual void leftSight(std::list<es_baseEnem>::iterator apoint);
	virtual void leftMem(std::list<es_baseEnem>::iterator apoint);
};

#endif
