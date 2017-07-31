/* Class contains pickup (in game buffs that a player can pick up) data and handles some of the functions.

 */

#ifndef ES_PICKUPCON
#define ES_PICKUPCON

#include <list>
#include "defs.h"

//class es_avatar;
//class es_players;

class es_pickupcon
{
friend class es_draw;
friend class es_collision;
public:
	es_pickupcon();
	void action();
	void setupPickup(std::list<es_pickup>&);

	void pickupSpawn();

private:

	std::list<es_pickup> PickupList;


};

#endif
