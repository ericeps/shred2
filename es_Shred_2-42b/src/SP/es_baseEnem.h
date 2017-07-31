/* Single-Player Enemy that scopes an area and shoots at Avatar.
 
 */

#ifndef ES_BASEENEM
#define ES_BASEENEM

#include <vector>
#include <list>
#include "defs.h"
#include "physDefs.h"
#include "enemyDefs.h"
//#include <iostream>

class es_world;

class es_baseEnem{
public:
	es_baseEnem(float x,float y,float z,float atheta, float aspeed, std::vector<int> alayers, es_idleGest);
    void setVars(es_world* awor);
	void addSight(float aa, float bb, int dist, int adelay, std::vector<es_moving> amove=std::vector<es_moving>());
    
    void actIdle();
    void fixSpeed(float amt);
	void calcGestToOrig(es_orig &aspot);
    
	int Health;
	point3f body;
	point3f feet;
	float Theta;
	float mSpeed;
	std::vector<int> Layers;
    es_sight Sight;
	std::vector<es_idleGest> Gestures;
	//unsigned int iiIdle;
	int seeState;
	int gestState;
	bool inSight;
	es_orig origSpot;

    es_world* World;
    int memory;
};

class es_baseEnemList{
    friend class es_draw;
    //friend class es_enemies;
public:
	es_baseEnemList();
	virtual ~es_baseEnemList();
	void setVars(es_world* awor);
	void push_back(es_baseEnem);
	void action();
    
	bool Damage(point3f &apoint,int prox,float dmg);
	void AllDamage(point3f &apoint,int prox,float dmg);
	bool Slow(point3f &apoint, int prox,float amt,float ttimer);
    
    virtual void justSpotted(std::list<es_baseEnem>::iterator apoint);
	virtual void spottedInMem(std::list<es_baseEnem>::iterator apoint);
	virtual void leftSight(std::list<es_baseEnem>::iterator apoint);
	virtual void leftMem(std::list<es_baseEnem>::iterator apoint);

	es_world *World;
    clost colList;
    std::list<es_baseEnem> Units;

	virtual void SightWithin(point3f &apoint,int layer);
};

#endif
