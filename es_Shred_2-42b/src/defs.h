/* Common structs/classes used by many different parts of the program.

 */

#ifndef DEFS_H
#define DEFS_H

#include <vector>
#include <list>

struct es_momentum{
int head,strafe,vert,spin;

};
struct point2i {
	int x,z;
};
struct point3i {
	int x,y,z;
};
struct point2f {
	float x,z;
};
struct point3f :public point2f{
	float y;
};

struct es_ship4
{
point3f Center,C2;
point3f Front,Back,Left,Right;
};

struct es_netship{
int ID;
es_ship4 Ship;
int Theta;
float Health;
int sideTilt;
int headTilt;
float custom;
unsigned char colorIndex;
};

struct es_move
{
bool left, right,up,down,jump,crouch,
turnright, turnleft;
};



struct es_brick {
	point3i cor1,cor2;				// points for visual
	float topColor[3];
};
struct es_bound {
	point2i cor1,cor2;
};

struct es_respawn{
point3f location;
int theta;
};


enum CORNER {NL, NR, FR, FL};
enum COLLIDE {X1,X2,Z1,Z2,Y1,Y2};
enum ES_SHIP_SIDE {FRONT,BACK,LEFT,RIGHT};
enum WEAPON_LIST {ENERGY,FIRE,BOMB,THROW,SLIME};

struct es_pickup {
point3f location;
WEAPON_LIST type;
int timer;
int amount;
};

struct es_collision_report {
COLLIDE Wall_Side;
ES_SHIP_SIDE Avatar_Side;
std::vector<es_bound>::const_iterator BoundPtr;
};


#endif
