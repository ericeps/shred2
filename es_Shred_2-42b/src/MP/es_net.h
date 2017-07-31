/* Translates data between the game and network client.

 */
#ifndef ES_NET
#define ES_NET

#include "defs.h"
#include "physDefs.h"
#include <QByteArray>

class es_client;
class es_weapons;
class es_players;
class es_MPgame;

class es_net{
public:
es_net(es_MPgame *);
//	void setAvatar(es_avatar*);
	void setClient(es_client*);
	void setWeapons(es_weapons*);
	void setPlayers(es_players* );

	void processDatagram(QByteArray &datagram);
	void readShip(QByteArray &datagram);
	void readWeapon(QByteArray &datagram);


	void sendShip(es_ship4&, int atheta, float ahealth, int sideTilt, int headTilt);
	void sendEnergy(phelit*);
	void sendBomb(phelit*);
	void sendThrow(phelit*);
	void sendSlime(phelit*);
	void sendFire(phelcit*);

private:
es_client *Client;
es_weapons *Weapons;
//es_avatar *Avatar;
es_players *Players;
es_MPgame *GameInfo;
};

#endif

