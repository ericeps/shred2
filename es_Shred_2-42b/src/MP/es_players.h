/* Data and functions for all other players (as opposed to Avatar)

 */
#ifndef ES_PLAYERS
#define ES_PLAYERS

#include "defs.h"
#include <vector>
#include <list>

class es_players
{
friend class es_draw;
friend class es_collision;
public:
void updateNetShip(unsigned char anID, es_ship4&, int theta, float ahealth, int asidetilt,int aheadtilt);
void addEnemies(std::list<unsigned char> &oplist);
//void addIDShip(unsigned char anID,es_ship4 &aShip);
bool isWithin(point3f &apoint, int arad);
point3f Center(std::vector< es_netship >::iterator);

private:
std::vector< es_netship > PlayerShips;
std::list< unsigned char > deadID;

};

#endif

