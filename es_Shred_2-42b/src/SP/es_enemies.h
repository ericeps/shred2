/* Container and functions for single player Enemies.

 */

#ifndef ES_ENEMIES
#define ES_ENEMIES

#include "defs.h"
#include <list>

#include "es_lookout.h"
#include "es_chaser.h"
//#include "'es_levlout.h"
class es_world;

class es_enemies{
friend class es_draw;
	public:
	es_enemies();
	void setVars(es_world* awor);
	void action();
	void CheckSights(point3f &aship, int shipLevel);
		bool Damage(point3f &apoint,int prox,float dmg);
		void AllDamage(point3f &apoint,int prox,float dmg);
        bool CheckSlow(point3f &aslow, int prox,float amt,float ttimer);
        void killMemory();
	es_world *World;
	phlist Energy;
	es_lookoutList *Lookouts;
	es_chaserList *Chasers;
};
#endif
