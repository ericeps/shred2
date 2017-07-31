/* The Avatar class is specifically the main player running this game.
    Mostly contains data related to location, health, weapon stock,
    and functions for manipulating them.
 */

#ifndef ES_AVATAR_H
#define ES_AVATAR_H
#include "defs.h"
#include <vector>
#include <utility>
//#include "es_draw.h"

class es_world;
class es_net;
class es_control;
class es_pInfo;

class es_avatar
{
friend class es_draw;
friend class es_collision;
friend class es_net;
public:
es_avatar(bool ismul);
void setVars(es_world* awor,es_control *acon, es_pInfo* ap=0);
/*void setWorld(es_world *);
void setControl(es_control *);
void setPInfo(es_pInfo *);
*/
void setColorIndex(unsigned char);
void setNet(es_net *);

	void action();
	void reset();
	void Placement(point3f apoint, int atheta);
	void punchME(COLLIDE,COLLIDE);

	int stockEnergy();
	int stockFire();
	int stockBombs();
	int stockThrow();
	int stockSlime();

	void takeEnergy();
	void takeFire();
	void takeBomb();
	void takeThrow();
	void takeSlime();
	void refillWeapon(WEAPON_LIST weap, int amount);

	bool isWithin(point3f&, int);

	point3f Center();
	point3f Front();
	point3f Back();
	point3f Left();
	point3f Right();
	
	int getTheta();
	int getHeadMomentum();
	
	
	es_move move;
	void onBoost();
	void offBoost();

	void dealDamage(float,unsigned char);
	void changeSpeed(float,float,unsigned char);
private:

	void calcMomentum();
	es_ship4 imagineTheta(int);
	es_ship4 imagineShift(float x,float z);
	es_ship4 imagineMove(float x,float z, float vert);
	void shiftVert(float);
	void shiftXZ(float,float);
	void setVert(float);

	bool isMulti;
	es_world *World;
	es_net *Net;
	es_control *Control;
	es_pInfo *pInfo;

	// mechanic info
	es_ship4 Ship; //collision Points
	int Theta;
	float Health;
	int sideTilt;
	int headTilt;
	unsigned char colorIndex;
	es_momentum Momentum;

	// player info
	void calcHealth();
	std::vector<std::pair<float,float> > chSpeedList;
	float Speed,chSpeed,sBoost;
	bool boostStatus;
	//int slowCount;
	int regenCount;
	int respawnCount;
	int Deaths;
	float JumpFluid;
	int stock_energy;
	int stock_fire;
	int stock_bombs;
	int stock_slime;
};

#endif
