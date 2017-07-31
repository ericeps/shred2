/* All openGL drawing code is in this class.

 */

#ifndef ES_DRAW
#define ES_DRAW

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif _WIN32
#include "windefs.h"
#include <GL/gl.h>
#endif

#include "physDefs.h"

class es_avatar;
class es_world;
class es_weapons;
class es_players;
class es_pickupcon;
class es_enemies;


class es_draw
{
public:
es_draw(bool);

void setVars(es_world *aw,es_avatar *av,es_weapons *aweap,es_pickupcon* apick, es_players* aplay,es_enemies* anem=0);
void drawAll();
void drawStats();

void camDeath(point3f ap,int atheta);
void camLive();

private:

void drawBricks();

void drawShip();
void drawNetShip();
void drawPickup();
void drawLookouts();
void drawChasers();

void drawEnergy(phelit*);
void drawFire();
void drawBombs();
void drawThrow();
void drawSlime();

void drawEnergyExplosions(phlist &alist);
void drawFireExplosions();
void drawBombExplosions(phlist &alist);
void drawBombExplosions(clost &aclost);
void drawSlimeExplosions();


es_avatar *Avatar;
es_weapons *Weapons;
es_pickupcon *Pickup;
es_world *World;
es_players *Players;
es_enemies *Enemies;
bool isMulti;
point3f camPos;
bool isAlive;
point3f deathPoint;
int deathTheta;
float deathCounter;

static GLfloat lgreen[3];
static GLfloat mgreen[3];
static GLfloat dgreen[3];
static GLfloat white[3];
static GLfloat blue[3];
static GLfloat lblue[3];
static GLfloat red[3];
static GLfloat yellow[3];
static GLfloat orange[3];
static GLfloat black[3];
static GLfloat maroon[3];
static GLfloat dmaroon[3];

static GLfloat ship1[10][3];
static GLfloat ship2[10][3];
static GLfloat ship3[10][3];
/*
lgreen ={.1,.8,.1};
mgreen ={.2,.7,.2};
dgreen ={.15,.5,.15};
blue =	{.2,.2,.8};
white = {1,1,1};
red =	{1,.2,0};
orange= {1,.4,0};
yellow= {1,.8,0};
maroon= {.6,.2,.2};
*/
};

#endif
