/* Single-Player Enemy that scopes an area and shoots at Avatar.

 */

#ifndef ES_LOOKOUT
#define ES_LOOKOUT

#include <vector>
#include <list>
#include "defs.h"
#include "physDefs.h"
#include "enemyDefs.h"
#include "es_baseEnem.h"
//#include <iostream>



class es_lookoutList:public es_baseEnemList{
	public:
	es_lookoutList();
	void setVars(es_world* awor,phlist *aenergy);//overrides es_baseEnemList::setVars() function
	//void SightWithin(point3f &apoint,int layer);
	virtual void justSpotted(std::list<es_baseEnem>::iterator apoint);
	virtual void spottedInMem(std::list<es_baseEnem>::iterator apoint);
	virtual void leftSight(std::list<es_baseEnem>::iterator apoint);
	virtual void leftMem(std::list<es_baseEnem>::iterator apoint);

    // Specific to LookOuts
	void addEnergy(point3f &abod,float theta);
	phlist *Energy;
};

#endif
