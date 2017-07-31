/* Handles certain functions such as deaths and respawn.

 */

#ifndef ES_CONTROL
#define ES_CONTROL

#include "defs.h"
//#include "es_basegame.h"
#include <vector>
class es_key;
class es_avatar;
class es_collision;
class es_draw;
class es_enemies;

class es_control
{
public:
es_control(bool isMul);
void setVars(es_key *akey,es_avatar* anav,es_collision *acol, es_draw *adraw, es_enemies *enem=0);
//void setKey(es_key *);
//void setAvatar(es_avatar *);

void death();
void live();
void setupRespawn(std::vector<es_respawn>&);
bool isAlive();
private:
es_key *Key;
es_avatar *Avatar;
es_collision *Collision;
es_draw *Draw;
es_enemies *Enemies;
//es_basegame *GameInfo;

bool Alive;
std::vector<es_respawn> Respawn;
point3f tmploc;
bool isMulti;
};

#endif


