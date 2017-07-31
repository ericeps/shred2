
#include "es_pickupcon.h"
#include "es_players.h"
#include "es_avatar.h"
#include <list>
#include "defs.h"


es_pickupcon::es_pickupcon()
{
}

void es_pickupcon::setupPickup(std::list<es_pickup>& apick){
	PickupList = apick;
	}

void es_pickupcon::action(){
	pickupSpawn();
	}

void es_pickupcon::pickupSpawn(){
		std::list<es_pickup>::iterator ipickup;
		ipickup = PickupList.begin(); 
		while( ipickup != PickupList.end())
		{
			if(ipickup->timer > 0)
			{--ipickup->timer;
			++ipickup;
			}
			else
			++ipickup;
		}
}