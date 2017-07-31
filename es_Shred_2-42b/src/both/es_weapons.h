/*  Weapons class.  Live bombs, bullets, etc are stored and created in this class.


 */

#ifndef ES_WEAPONS
#define ES_WEAPONS

#include "defs.h"
#include "physDefs.h"
#include <list>

class es_avatar;
class es_net;
class es_basegame;

class es_weapons
{
friend class es_draw;
friend class es_collision;
public:
	es_weapons(es_basegame*);
	~es_weapons();
	void setNet(es_net *anet);
	void setVars(es_avatar* anav);
//	void setAvatar(es_avatar*);

private:
	es_avatar *Avatar;
	es_net *Net;
public:
	void action();

	void onFire();
	void offFire();
	void addEnergy();
	void addFire();
	void addBomb();
	void startThrow();
	void finishThrow();
	void addThrow(float);
	void addSlime();

	void netEnergy(phelit*);
	void netBomb(phelit*);
	void netThrow(phelit*);
	void netSlime(phelit*);
	void netFire(phelcit*);

private:

//	void addEnergyExplosion(point3f&);
//	void addFireExplosion(point3f&);
//	void addBombExplosion(point3f&,unsigned char);
//	void addSlimeExplosion(point3f&);

private:
es_basegame *GameInfo;

bool fireStatus;
int throwWind;
bool throwStatus;

phlist Energy;
phlist Bombs;
phlist Throw;
phlist Slime;
phlist Fire;//phelcit

/*std::list< es_energy > Energy;
std::list< es_fire > Fire;
std::list< es_bomb > Bombs;
std::list< es_throw > Throw;
std::list< es_slime > Slime;
*/

/*std::list< loc_customf > explosionEnergy;
std::list< loc_customf > explosionFire;
std::list< loc_customf > explosionBomb;
std::list< loc_customf > explosionSlime;
*/
};

#endif
