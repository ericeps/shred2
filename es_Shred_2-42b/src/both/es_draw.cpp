#include "es_draw.h"
#include "es_avatar.h"
#include "es_weapons.h"
#include "es_pickupcon.h"
#include "es_world.h"
#include "es_players.h"
#include "es_enemies.h"
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif _WIN32
#include "windefs.h"
#include <GL/gl.h>
#include <GL/glu.h>
#endif


GLfloat es_draw::lgreen[3] = {.1,.8,.1};
GLfloat es_draw::mgreen[3] = {.2,.7,.2};
GLfloat es_draw::dgreen[3] = {.15,.5,.15};
GLfloat es_draw::blue[3] = {.2,.2,.8};
GLfloat es_draw::lblue[3] = {0,.5,1};
GLfloat es_draw::white[3] = {1,1,1};
GLfloat es_draw::red[3] = {1,.2,0};
GLfloat es_draw::orange[3] = {1,.4,0};
GLfloat es_draw::yellow[3] = {1,.8,0};
GLfloat es_draw::black[3] = {0,0,0};
GLfloat es_draw::maroon[3] = {.6,.2,.2};
GLfloat es_draw::dmaroon[3] = {.53,.13,.13};

GLfloat es_draw::ship1[10][3] = 
	{{.1, .8, .1},
	 { 0, .5,  1},
	 { 1, .8,  0},
	 { .9, .9,  .9},
	 {.13, .5,  .13},
	 {.2, .2, .8},
	 {.3, .1, .4},
	 {.34, .86, .2},
	 {.3, .6, .1},
	 {0,  0,  0}
	 };
GLfloat es_draw::ship2[10][3] = 
	{{.2, .7, .2},
	 { .2, .2, .8},
	 {1, .4, 0},
	 {1, .2, 0},
	 {.6, .2, 0},
	 {.1, .1, .6},
	 {.5, .8, .3},
	 {.87, .2, .1},
	 {.4, .05, .6},
	 { 1, .8,  0}
	};
GLfloat es_draw::ship3[10][3] = 
	{{.13, .4, .13},
	 {  0,  0,   .05},
	 {  .7, .1,   0},
	 {.53, .13, .13},
	 { .4, .05, .05},
	 { .2, .7, .2},
	 {.32, .54, .66},
	 { .6, .1, .4},
	 { .1, .05, .4},
	 { .2, .2, .2}
	};

es_draw::es_draw(bool ism)
{isMulti=ism;
camPos.x = 0;
camPos.y = 50;
camPos.z = 80;
}
void es_draw::setVars(es_world *aw,es_avatar *av,es_weapons *aweap,es_pickupcon* apick, es_players* aplay,es_enemies* anem)
{
World=aw;
Avatar=av;
Weapons=aweap;
Pickup=apick;
Players=aplay;
Enemies=anem;
}

void es_draw::camDeath(point3f apoint, int atheta)
{
isAlive=0;
deathPoint=apoint;
deathTheta=atheta;
deathCounter=0;
}
void es_draw::camLive()
{
isAlive=1;
}

void es_draw::drawAll()
{
gluLookAt (this->camPos.x, this->camPos.y, this->camPos.z, 0, 1, -20, 0.0, 1.0, 0.0);
drawShip();

if(isAlive)
{
glRotatef(-Avatar->Theta,0,1,0);
glTranslatef(-Avatar->Ship.Center.x,-Avatar->Ship.Center.y,-Avatar->Ship.Center.z);
}
else
{glRotatef(-deathTheta,0,1,0);
glTranslatef(-deathPoint.x,-deathPoint.y-deathCounter,-deathPoint.z);
deathCounter+=.1;
}
drawBricks();
drawPickup();
drawEnergy(Weapons->Energy.front());
drawFire();
drawBombs();
drawThrow();
drawSlime();
drawEnergyExplosions(Weapons->Energy);
drawFireExplosions();
drawBombExplosions(Weapons->Bombs);
drawBombExplosions(Weapons->Throw);
drawSlimeExplosions();
if(!isMulti){
	drawEnergy(Enemies->Energy.front());
	drawEnergyExplosions(Enemies->Energy);
	drawLookouts();
	drawChasers();
	drawBombExplosions(Enemies->Chasers->colList);
}
else
{	drawNetShip();

}
}

void es_draw::drawStats()
{
	// ENERGY stock
	if(Avatar->stock_energy>0)
	{
		glBegin(GL_POLYGON);
			glColor3f(.1,.2,.7);
			glVertex2f( 100,130);
			glVertex2f( 110,130);
			glVertex2f( 110,140);
			glVertex2f( 100,140);
		glEnd();
		glBegin(GL_QUADS);
			glVertex2f(95,155);
			glVertex2f(115,155);
			glVertex2f(115,155+Avatar->stock_energy);
			glVertex2f( 95,155+Avatar->stock_energy);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f(1,1,1);
			glVertex2f(100,130);
			glVertex2f(105,120);
			glVertex2f(110,130);
			
			glVertex2f(100,140);
			glVertex2f(105,150);
			glVertex2f(110,140);

			glVertex2f(110,130);
			glVertex2f(120,135);
			glVertex2f(110,140);
			
			glVertex2f(100,130);
			glVertex2f(90,135);
			glVertex2f(100,140);
		glEnd();
	}
	// FIRE	stock
	if(Avatar->stock_fire>0)
	{
		glBegin(GL_TRIANGLES);
			glColor3fv(yellow);
				glVertex2f(140,120);
				glVertex2f(145,130);
				glVertex2f(150,120);
				
				glVertex2f(160,120);
				glVertex2f(165,130);
				glVertex2f(170,120);
			glColor3fv(orange);
				glVertex2f(150,120);
				glVertex2f(155,150);
				glVertex2f(160,120);
		glEnd();
		glBegin(GL_QUADS);
				glVertex2f(145,155);
				glVertex2f(165,155);
				glVertex2f(165,155+(Avatar->stock_fire*.5));
				glVertex2f(145,155+(Avatar->stock_fire*.5));
		glEnd();
	}
	// BOMB stock
	if(Avatar->stock_bombs>0)
	{
		glBegin(GL_POLYGON);
			glColor3fv(maroon);
				glVertex2f(195,120);
				glVertex2f(205,125);
				glVertex2f(210,135);
				glVertex2f(205,145);
				glVertex2f(195,150);
				glVertex2f(185,145);
				glVertex2f(180,135);
				glVertex2f(185,125);
		glEnd();
		glBegin(GL_QUADS);
				glVertex2f(185,155);
				glVertex2f(205,155);
				glVertex2f(205,155+(Avatar->stock_bombs*4));
				glVertex2f(185,155+(Avatar->stock_bombs*4));
		glEnd();
	}
	// SLIME stock
	if(Avatar->stock_slime>0)
	{
		glBegin(GL_POLYGON);
			glColor3fv(mgreen);
				glVertex2f(220,140);
				glVertex2f(223,132);
				glVertex2f(230,130);
				glVertex2f(235,135);
				glVertex2f(229,145);
		glEnd();
		glBegin(GL_POLYGON);
				glVertex2f(230,130);
				glVertex2f(233,123);
				glVertex2f(240,120);
				glVertex2f(249,130);
				glVertex2f(242,138);
		glEnd();
		glBegin(GL_QUADS);
				glVertex2f(225,155);
				glVertex2f(245,155);
				glVertex2f(245,155+(Avatar->stock_slime*4));
				glVertex2f(225,155+(Avatar->stock_slime*4));
		glEnd();
	}
	//HEALTH AND FLUID
		glBegin(GL_POLYGON);
			glColor3f(.1,.2,.7);
			glVertex2f( 100,530);
			glVertex2f( 100,575);
			glVertex2f( 98,574);
			glVertex2f( 96,572);
			glVertex2f( 95,570);
			glVertex2f( 95,535);
			glVertex2f( 96,533);
			glVertex2f( 98,531);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f( 300,530);
			glVertex2f( 302,531);
			glVertex2f( 304,533);
			glVertex2f( 305,535);
			glVertex2f( 305,570);
			glVertex2f( 304,572);
			glVertex2f( 302,574);
			glVertex2f( 300,575);
		glEnd();
	//Health
		if(Avatar->Health>0)
		{
			glBegin(GL_QUADS);
				glColor3f(.8,.2,.05);
				glVertex2f(100,565);
				glVertex2f(100,555);
				glVertex2f(100+(Avatar->Health*10),555);
				glVertex2f(100+(Avatar->Health*10),565);
			glEnd();
		}
	// JumpFluid
		glBegin(GL_QUADS);
			glColor3f(.0,.5,.8);
			glVertex2f(100,545);
			glVertex2f(100,535);
			glVertex2f(100+(Avatar->JumpFluid*2),535);
			glVertex2f(100+(Avatar->JumpFluid*2),545);
		glEnd();
}

void es_draw::drawShip()
{
	if(Avatar->Health > 0)
	{
		glPushMatrix();
			glRotatef( Avatar->sideTilt, 0,0,1);
			glRotatef( Avatar->headTilt, 1,0,0);

				glBegin(GL_QUADS);
					glColor3fv(ship1[Avatar->colorIndex]);
						glVertex3f(-3,0,-15);
						glVertex3f(-3,5,4);
						glVertex3f(3,5,4);
						glVertex3f(3,0,-15);

					glColor3fv(ship3[Avatar->colorIndex]);
						glVertex3f(-3,0,10);
						glVertex3f(3,0,10);
						glVertex3f(3,5,4);
						glVertex3f(-3,5,4);
				glEnd();
				glBegin(GL_TRIANGLES);
						glVertex3f(-3, 5, 4);
						glVertex3f(-8, 0, 4);
						glVertex3f(-3, 0, 10);
				
						glVertex3f(3, 5, 4);
						glVertex3f(8, 0, 4);
						glVertex3f(3, 0, -15);
						
					glColor3fv(ship1[Avatar->colorIndex]);
						glVertex3f(-3, 5, 4);
						glVertex3f(-3, 0, -15);
						glVertex3f(-8, 0, 4);

					glColor3fv(ship2[Avatar->colorIndex]);
						glVertex3f(3, 5, 4);
						glVertex3f(3, 0, 10);
						glVertex3f(8, 0, 4);
					// 
				glEnd();
                               if(Avatar->sBoost!=0.0)
                                {
                                   glBegin(GL_TRIANGLES);
                                   glColor3fv(orange);
                                                   glVertex3f(-2, 3, 10);
                                                   glVertex3f(-2, 2, 17);
                                                   glVertex3f(-2, 1, 10);

                                                   glVertex3f( 2, 3, 10);
                                                   glVertex3f( 2, 2, 17);
                                                   glVertex3f( 2, 1, 10);

                                   glColor3fv(yellow);
                                                   glVertex3f(-3, 1, 10);
                                                   glVertex3f(-2, 1, 17);
                                                   glVertex3f(-1, 1, 10);

                                                   glVertex3f( 3, 1, 10);
                                                   glVertex3f( 2, 1, 17);
                                                   glVertex3f( 1, 1, 10);
                                   glEnd();

                               }
		glPopMatrix();
	}
	else if(Avatar->respawnCount <30)
	{	static float tmp;
		tmp = Avatar->respawnCount*.5;
	
			glBegin(GL_TRIANGLES);
				glColor3fv(orange);
			// vertical
				glVertex3f( 0,  3+tmp  , 0    );
				glVertex3f(-1 ,    tmp , 0    );
				glVertex3f(  1 ,    tmp , 0    );

				glVertex3f( 0     ,  3+tmp , 0    );
				glVertex3f( 0     , tmp ,  -1 );
				glVertex3f( 0     , tmp , 1 );
			// horizontal
				glVertex3f( 3+tmp , 0 , 0 );
				glVertex3f(tmp , -1 , 0    );
				glVertex3f( tmp , 1 , 0    );

				glVertex3f( -3-tmp , 0    , 0    );
				glVertex3f(   -tmp , -1 , 0    );
				glVertex3f(   -tmp , 1 , 0    );
			// depth
				glVertex3f( 0     , 0    , 3+tmp );
				glVertex3f( 0     , -1 , tmp );
				glVertex3f( 0     , 1 , tmp );

				glVertex3f( 0     , 0    , -3-tmp );
				glVertex3f( 0     , -1 ,   -tmp );
				glVertex3f( 0     , 1 ,   -tmp );
			// other
				glColor3fv(red);
				glVertex3f( 0	, tmp	, 0	);
				glVertex3f( -tmp	, 0	, 0	);
				glVertex3f( 0	, 0  ,  -tmp	);

				glVertex3f( 0	, tmp	, 0	);
				glVertex3f( tmp	, 0	, 0	);
				glVertex3f( 0	, 0  , tmp	);
				
				glVertex3f( 0	, tmp	, 0	);
				glVertex3f( tmp	, 0	, 0	);
				glVertex3f( 0	, 0  ,  -tmp	);
				
				glVertex3f( 0	, tmp	, 0	);
				glVertex3f(  -tmp	, 0	, 0	);
				glVertex3f( 0	, 0  , tmp	);
			glEnd();
	}
}




void es_draw::drawNetShip()
{

	std::vector<es_netship>::iterator iship;
	for(iship = Players->PlayerShips.begin(); iship != Players->PlayerShips.end(); iship++)
	{
//	glPushMatrix();

		if(  iship->Health >0 )
		{
		
		glPushMatrix();
			glTranslatef( iship->Ship.Center.x,iship->Ship.Center.y,iship->Ship.Center.z);

			glRotatef( iship->Theta, 0,1,0);
			glRotatef( iship->sideTilt, 0,0,1);
			glRotatef( iship->headTilt, 1,0,0);

				glBegin(GL_QUADS);
					glColor3fv(ship1[iship->colorIndex]);
						glVertex3f(-3,0,-15);
						glVertex3f(-3,5,4);
						glVertex3f(3,5,4);
						glVertex3f(3,0,-15);

					glColor3fv(ship3[iship->colorIndex]);
						glVertex3f(-3,0,10);
						glVertex3f(3,0,10);
						glVertex3f(3,5,4);
						glVertex3f(-3,5,4);
				glEnd();
				glBegin(GL_TRIANGLES);
						glVertex3f(-3, 5, 4);
						glVertex3f(-8, 0, 4);
						glVertex3f(-3, 0, 10);
				
						glVertex3f(3, 5, 4);
						glVertex3f(8, 0, 4);
						glVertex3f(3, 0, -15);
						
					glColor3fv(ship1[iship->colorIndex]);
						glVertex3f(-3, 5, 4);
						glVertex3f(-3, 0, -15);
						glVertex3f(-8, 0, 4);

					glColor3fv(ship2[iship->colorIndex]);
						glVertex3f(3, 5, 4);
						glVertex3f(3, 0, 10);
						glVertex3f(8, 0, 4);
					// 
				glEnd();
		glPopMatrix();
		}
		else if(iship->custom<30)
		{	static float tmp;
			tmp = iship->custom*.5;
		
		
			glBegin(GL_TRIANGLES);
				glColor3fv(orange);
			// vertical
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y +3+tmp ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x  -1 ) , (iship->Ship.Center.y   +tmp ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x  +1 ) , (iship->Ship.Center.y   +tmp ) , (iship->Ship.Center.z    ) );

				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y +3+tmp ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y   +tmp ) , (iship->Ship.Center.z -1 ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y   +tmp ) , (iship->Ship.Center.z +1 ) );
			// horizontal
				glVertex3f( (iship->Ship.Center.x  +3+tmp ) , (iship->Ship.Center.y    ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x    +tmp ) , (iship->Ship.Center.y -1 ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x    +tmp ) , (iship->Ship.Center.y +1 ) , (iship->Ship.Center.z    ) );

				glVertex3f( (iship->Ship.Center.x  -3-tmp ) , (iship->Ship.Center.y    ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x    -tmp ) , (iship->Ship.Center.y -1 ) , (iship->Ship.Center.z    ) );
				glVertex3f( (iship->Ship.Center.x    -tmp ) , (iship->Ship.Center.y +1 ) , (iship->Ship.Center.z    ) );
			// depth
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y    ) , (iship->Ship.Center.z +3+tmp ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y -1 ) , (iship->Ship.Center.z   +tmp ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y +1 ) , (iship->Ship.Center.z   +tmp ) );

				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y    ) , (iship->Ship.Center.z -3-tmp ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y -1 ) , (iship->Ship.Center.z   -tmp ) );
				glVertex3f( (iship->Ship.Center.x     ) , (iship->Ship.Center.y +1 ) , (iship->Ship.Center.z   -tmp ) );
			// other
				glColor3fv(red);
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y +tmp	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x -tmp	) , (iship->Ship.Center.y	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y  ) , (iship->Ship.Center.z -tmp	) );

				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y +tmp	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x +tmp	) , (iship->Ship.Center.y	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y  ) , (iship->Ship.Center.z +tmp	) );
				
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y +tmp	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x +tmp	) , (iship->Ship.Center.y	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y  ) , (iship->Ship.Center.z -tmp	) );
				
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y +tmp	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x -tmp	) , (iship->Ship.Center.y	) , (iship->Ship.Center.z	) );
				glVertex3f( (iship->Ship.Center.x	) , (iship->Ship.Center.y  ) , (iship->Ship.Center.z +tmp	) );

			glEnd();
			++iship->custom;
		}
//	glPopMatrix();
	}
}
void es_draw::drawPickup()
{
	std::list<es_pickup>::const_iterator ipick;
	for( ipick=Pickup->PickupList.begin(); ipick!=Pickup->PickupList.end(); ipick++)
	{
		if(ipick->timer <=0)
		{
			glBegin(GL_QUADS);
				if(ipick->type == ENERGY)
				glColor3fv(lblue);
				else if(ipick->type == FIRE)
				glColor3fv(red);
				else if(ipick->type == BOMB)
				glColor3fv(maroon);
				else if(ipick->type == SLIME)
				glColor3fv(lgreen);
				else if(ipick->type == THROW)
				glColor3fv(maroon);
					glVertex3f( (ipick->location.x  -3 ) , (ipick->location.y -3 ) , (ipick->location.z) );
					glVertex3f( (ipick->location.x  +3 ) , (ipick->location.y -3 ) , (ipick->location.z) );
					glVertex3f( (ipick->location.x  +3 ) , (ipick->location.y +3 ) , (ipick->location.z) );
					glVertex3f( (ipick->location.x  -3 ) , (ipick->location.y +3 ) , (ipick->location.z) );

					glVertex3f( (ipick->location.x) , (ipick->location.y -3 ) , (ipick->location.z -3 ) );
					glVertex3f( (ipick->location.x) , (ipick->location.y +3 ) , (ipick->location.z -3 ) );
					glVertex3f( (ipick->location.x) , (ipick->location.y +3 ) , (ipick->location.z +3 ) );
					glVertex3f( (ipick->location.x) , (ipick->location.y -3 ) , (ipick->location.z +3 ) );
				glColor3fv(yellow);
					glVertex3f( (ipick->location.x  -3 ) , ipick->location.y , (ipick->location.z -3 ) );
					glVertex3f( (ipick->location.x  +3 ) , ipick->location.y , (ipick->location.z -3 ) );
					glVertex3f( (ipick->location.x  +3 ) , ipick->location.y , (ipick->location.z +3 ) );
					glVertex3f( (ipick->location.x  -3 ) , ipick->location.y , (ipick->location.z +3 ) );
				
			glEnd();
		}
	}
}
void es_draw::drawChasers()
{
	std::list<es_baseEnem>::iterator ichase;
	for( ichase=Enemies->Chasers->Units.begin(); ichase!=Enemies->Chasers->Units.end(); ichase++)
	{	float tmpx=(cos(ichase->Theta)*6)+ichase->feet.x;
		float tmpz=(sin(ichase->Theta)*6)+ichase->feet.z;
	
			glBegin(GL_QUAD_STRIP);
				glColor3fv(dgreen);
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y    ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y +3 ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x  -5 ) , (ichase->feet.y    ) , (ichase->feet.z +5 ) );
					glVertex3f( (ichase->feet.x  -5 ) , (ichase->feet.y +3 ) , (ichase->feet.z +5 ) );
					glVertex3f( (ichase->feet.x	 +5 ) , (ichase->feet.y    ) , (ichase->feet.z +5 ) );
					glVertex3f( (ichase->feet.x	 +5 ) , (ichase->feet.y +3 ) , (ichase->feet.z +5 ) );
				glColor3fv(black);
					glVertex3f( (ichase->feet.x  +5 ) , (ichase->feet.y    ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x  +5 ) , (ichase->feet.y +3 ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y    ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y +3 ) , (ichase->feet.z -5 ) );
			glEnd();
			glBegin(GL_QUADS);
				glColor3fv(yellow);
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y +3 ) , (ichase->feet.z -5 ) );
					glVertex3f( (ichase->feet.x	 -5 ) , (ichase->feet.y +3 ) , (ichase->feet.z +5 ) );
					glVertex3f( (ichase->feet.x  +5 ) , (ichase->feet.y +3 ) , (ichase->feet.z +5 ) );
					glVertex3f( (ichase->feet.x  +5 ) , (ichase->feet.y +3 ) , (ichase->feet.z -5 ) );
			glEnd();
			glBegin(GL_QUAD_STRIP);
				glColor3fv(mgreen);
					glVertex3f( (ichase->feet.x	 -2 ) , (ichase->feet.y +3 ) , (ichase->feet.z -2 ) );
					glVertex3f( (ichase->feet.x	 -2 ) , (ichase->feet.y +9 ) , (ichase->feet.z -2 ) );
					glVertex3f( (ichase->feet.x  -2 ) , (ichase->feet.y +3 ) , (ichase->feet.z +2 ) );
					glVertex3f( (ichase->feet.x  -2 ) , (ichase->feet.y +9 ) , (ichase->feet.z +2 ) );
					glVertex3f( (ichase->feet.x	 +2 ) , (ichase->feet.y +3 ) , (ichase->feet.z +2 ) );
					glVertex3f( (ichase->feet.x	 +2 ) , (ichase->feet.y +9 ) , (ichase->feet.z +2 ) );
				glColor3fv(orange);
					glVertex3f( (ichase->feet.x  +2 ) , (ichase->feet.y +3 ) , (ichase->feet.z -2 ) );
					glVertex3f( (ichase->feet.x  +2 ) , (ichase->feet.y +9 ) , (ichase->feet.z -2 ) );
					glVertex3f( (ichase->feet.x	 -2 ) , (ichase->feet.y +3 ) , (ichase->feet.z -2 ) );
					glVertex3f( (ichase->feet.x	 -2 ) , (ichase->feet.y +9 ) , (ichase->feet.z -2 ) );
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
				glColor3fv(red);
					glVertex3f( tmpx , (ichase->feet.y +9 ) , tmpz );
					glVertex3f( tmpx    , (ichase->feet.y +7 ) , tmpz-2   );
					glVertex3f( tmpx-1.7, (ichase->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx-2  , (ichase->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx-1.7, (ichase->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx    , (ichase->feet.y +7 ) , tmpz +2  );
					glVertex3f( tmpx+1.7 , (ichase->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx+2   , (ichase->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx+1.7 , (ichase->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx     , (ichase->feet.y +7 ) , tmpz-2   );
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
					glVertex3f( tmpx , (ichase->feet.y +5 ) , tmpz );
					glVertex3f( tmpx    , (ichase->feet.y +7 ) , tmpz-2   );
					glVertex3f( tmpx-1.7, (ichase->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx-2  , (ichase->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx-1.7, (ichase->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx    , (ichase->feet.y +7 ) , tmpz +2  );
					glVertex3f( tmpx+1.7 , (ichase->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx+2   , (ichase->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx+1.7 , (ichase->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx     , (ichase->feet.y +7 ) , tmpz-2   );
			glEnd();
	}
}
void es_draw::drawLookouts()
{
	std::list<es_baseEnem>::iterator ilook;
	for( ilook=Enemies->Lookouts->Units.begin(); ilook!=Enemies->Lookouts->Units.end(); ilook++)
	{	float tmpx=(cos(ilook->Theta)*6)+ilook->feet.x;
		float tmpz=(sin(ilook->Theta)*6)+ilook->feet.z;
	
			glBegin(GL_QUAD_STRIP);
				glColor3fv(red);
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y    ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y +3 ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x  -5 ) , (ilook->feet.y    ) , (ilook->feet.z +5 ) );
					glVertex3f( (ilook->feet.x  -5 ) , (ilook->feet.y +3 ) , (ilook->feet.z +5 ) );
					glVertex3f( (ilook->feet.x	 +5 ) , (ilook->feet.y    ) , (ilook->feet.z +5 ) );
					glVertex3f( (ilook->feet.x	 +5 ) , (ilook->feet.y +3 ) , (ilook->feet.z +5 ) );
				glColor3fv(dmaroon);
					glVertex3f( (ilook->feet.x  +5 ) , (ilook->feet.y    ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x  +5 ) , (ilook->feet.y +3 ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y    ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y +3 ) , (ilook->feet.z -5 ) );
			glEnd();
			glBegin(GL_QUADS);
				glColor3fv(maroon);
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y +3 ) , (ilook->feet.z -5 ) );
					glVertex3f( (ilook->feet.x	 -5 ) , (ilook->feet.y +3 ) , (ilook->feet.z +5 ) );
					glVertex3f( (ilook->feet.x  +5 ) , (ilook->feet.y +3 ) , (ilook->feet.z +5 ) );
					glVertex3f( (ilook->feet.x  +5 ) , (ilook->feet.y +3 ) , (ilook->feet.z -5 ) );
			glEnd();
			glBegin(GL_QUAD_STRIP);
				glColor3fv(blue);
					glVertex3f( (ilook->feet.x	 -2 ) , (ilook->feet.y +3 ) , (ilook->feet.z -2 ) );
					glVertex3f( (ilook->feet.x	 -2 ) , (ilook->feet.y +9 ) , (ilook->feet.z -2 ) );
					glVertex3f( (ilook->feet.x  -2 ) , (ilook->feet.y +3 ) , (ilook->feet.z +2 ) );
					glVertex3f( (ilook->feet.x  -2 ) , (ilook->feet.y +9 ) , (ilook->feet.z +2 ) );
					glVertex3f( (ilook->feet.x	 +2 ) , (ilook->feet.y +3 ) , (ilook->feet.z +2 ) );
					glVertex3f( (ilook->feet.x	 +2 ) , (ilook->feet.y +9 ) , (ilook->feet.z +2 ) );
				glColor3fv(white);
					glVertex3f( (ilook->feet.x  +2 ) , (ilook->feet.y +3 ) , (ilook->feet.z -2 ) );
					glVertex3f( (ilook->feet.x  +2 ) , (ilook->feet.y +9 ) , (ilook->feet.z -2 ) );
					glVertex3f( (ilook->feet.x	 -2 ) , (ilook->feet.y +3 ) , (ilook->feet.z -2 ) );
					glVertex3f( (ilook->feet.x	 -2 ) , (ilook->feet.y +9 ) , (ilook->feet.z -2 ) );
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
				glColor3fv(lblue);
					glVertex3f( tmpx , (ilook->feet.y +9 ) , tmpz );
					glVertex3f( tmpx    , (ilook->feet.y +7 ) , tmpz-2   );
					glVertex3f( tmpx-1.7, (ilook->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx-2  , (ilook->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx-1.7, (ilook->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx    , (ilook->feet.y +7 ) , tmpz +2  );
					glVertex3f( tmpx+1.7 , (ilook->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx+2   , (ilook->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx+1.7 , (ilook->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx     , (ilook->feet.y +7 ) , tmpz-2   );
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
					glVertex3f( tmpx , (ilook->feet.y +5 ) , tmpz );
					glVertex3f( tmpx    , (ilook->feet.y +7 ) , tmpz-2   );
					glVertex3f( tmpx-1.7, (ilook->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx-2  , (ilook->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx-1.7, (ilook->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx    , (ilook->feet.y +7 ) , tmpz +2  );
					glVertex3f( tmpx+1.7 , (ilook->feet.y +7 ) , tmpz+1.7 );
					glVertex3f( tmpx+2   , (ilook->feet.y +7 ) , tmpz     );
					glVertex3f( tmpx+1.7 , (ilook->feet.y +7 ) , tmpz-1.7 );
					glVertex3f( tmpx     , (ilook->feet.y +7 ) , tmpz-2   );
			glEnd();
	}
}

void es_draw::drawSlimeExplosions()
{
	loc_customf* iexplode = static_cast<phelColl*>(Weapons->Slime.Collision)->colList.front();
	while( iexplode != NULL)
	{
		if(iexplode->custom < 6)
		{
			glBegin(GL_TRIANGLES);
				glColor3fv(lgreen);
			// horizontal
				glVertex3f( (iexplode->location.x  +3+iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y -1 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y +1 ) , (iexplode->location.z    ) );

				glVertex3f( (iexplode->location.x  -3-iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y -1 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y +1 ) , (iexplode->location.z    ) );
			// depth
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z +3+iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -1 ) , (iexplode->location.z   +iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +1 ) , (iexplode->location.z   +iexplode->custom ) );

				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z -3-iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -1 ) , (iexplode->location.z   -iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +1 ) , (iexplode->location.z   -iexplode->custom ) );
			// other
				glColor3fv(mgreen);
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );

				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );

			glEnd();
			iexplode->custom += .3;
			iexplode = loc_customf::incr(iexplode);
		}
		else
		iexplode = static_cast<phelColl*>(Weapons->Slime.Collision)->colList.erase(iexplode);
	}
}


void es_draw::drawBombExplosions(clost &aclost)
{
loc_customf* iexplode = aclost.front();
	while( iexplode != NULL)
	{
		if(iexplode->custom < 25)//18
		{
			glBegin(GL_TRIANGLES);
				glColor3fv(orange);
			// vertical
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +3+iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x  -4 ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x  +4 ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z    ) );

				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +3+iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z -4 ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z +4 ) );
			// horizontal
				glVertex3f( (iexplode->location.x  +3+iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y -4 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y +4 ) , (iexplode->location.z    ) );

				glVertex3f( (iexplode->location.x  -3-iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y -4 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y +4 ) , (iexplode->location.z    ) );
			// depth
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z +3+iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -4 ) , (iexplode->location.z   +iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +4 ) , (iexplode->location.z   +iexplode->custom ) );

				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z -3-iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -4 ) , (iexplode->location.z   -iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +4 ) , (iexplode->location.z   -iexplode->custom ) );
			// other
				glColor3fv(yellow);
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );

				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );

			glEnd();
			iexplode->custom += 2;//1.2
			iexplode = loc_customf::incr(iexplode);
		}
		else
		iexplode = aclost.erase(iexplode);
	}
}
void es_draw::drawBombExplosions(phlist &alist)
{
	drawBombExplosions(static_cast<phelColl*>(alist.Collision)->colList);
}
/*
	loc_customf* iexplode = static_cast<phelColl*>(alist.Collision)->colList.front();
	while( iexplode != NULL)
	{
		if(iexplode->custom < 18)
		{
			glBegin(GL_TRIANGLES);
				glColor3fv(orange);
			// vertical
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +3+iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x  -4 ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x  +4 ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z    ) );

				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +3+iexplode->custom ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z -4 ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y   +iexplode->custom ) , (iexplode->location.z +4 ) );
			// horizontal
				glVertex3f( (iexplode->location.x  +3+iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y -4 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    +iexplode->custom ) , (iexplode->location.y +4 ) , (iexplode->location.z    ) );

				glVertex3f( (iexplode->location.x  -3-iexplode->custom ) , (iexplode->location.y    ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y -4 ) , (iexplode->location.z    ) );
				glVertex3f( (iexplode->location.x    -iexplode->custom ) , (iexplode->location.y +4 ) , (iexplode->location.z    ) );
			// depth
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z +3+iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -4 ) , (iexplode->location.z   +iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +4 ) , (iexplode->location.z   +iexplode->custom ) );

				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y    ) , (iexplode->location.z -3-iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y -4 ) , (iexplode->location.z   -iexplode->custom ) );
				glVertex3f( (iexplode->location.x     ) , (iexplode->location.y +4 ) , (iexplode->location.z   -iexplode->custom ) );
			// other
				glColor3fv(yellow);
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );

				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x +iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z -iexplode->custom	) );
				
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y +iexplode->custom	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x -iexplode->custom	) , (iexplode->location.y	) , (iexplode->location.z	) );
				glVertex3f( (iexplode->location.x	) , (iexplode->location.y  ) , (iexplode->location.z +iexplode->custom	) );

			glEnd();
			iexplode->custom += 1.2;
			iexplode = loc_customf::incr(iexplode);
		}
		else
		iexplode = static_cast<phelColl*>(alist.Collision)->colList.erase(iexplode);
	}
}
*/
void es_draw::drawEnergyExplosions(phlist &alist)
{loc_customf* iexplode = static_cast<phelColl*>(alist.Collision)->colList.front();
	while( iexplode != NULL)
	{
		if(iexplode->custom < 7)
		{
			glBegin(GL_QUADS);
				glColor3fv(white);
				if((int)iexplode->custom % 2)
				{
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 6  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 6  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 2.5  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 2.5  ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 6  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 6  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 2.5  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 2.5  ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 6  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 6  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 2.5  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  - 2.5  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -2  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 6  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 6  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 2.5  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  + 2.5  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +2  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  ) );
				//***********
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  +2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  + 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  + 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  +2 ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  +2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z + 2.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  + 6  ) , (iexplode->location.z + 2.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  + 6  ) , (iexplode->location.z   +2) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z  -2  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z - 6  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z - 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  + 2.5  ) , (iexplode->location.z  -2  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +2  ) , (iexplode->location.z -2  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +2  ) , (iexplode->location.z  - 2.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  - 2.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  + 6  ) , (iexplode->location.z  -2 ) );
					
					glVertex3f( (iexplode->location.x ) , (iexplode->location.y  -2  ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  - 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  - 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z -2 ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -2  ) , (iexplode->location.z-2  ) );
					glVertex3f( (iexplode->location.x ) , (iexplode->location.y  -2  ) , (iexplode->location.z  - 2.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  - 2.5  ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  -2) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  +2  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -2  ) , (iexplode->location.z  + 6  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  + 6  ) );
					glVertex3f( (iexplode->location.x ) , (iexplode->location.y  - 2.5  ) , (iexplode->location.z  +2  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -2  ) , (iexplode->location.z +2   ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  -2  ) , (iexplode->location.z  + 2.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  + 2.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  - 6  ) , (iexplode->location.z  +2  ) );					
				}
				else
				{
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4    ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4    ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  +4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +.5   ) , (iexplode->location.y  +4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +.5   ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4    ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4    ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  +4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -.5   ) , (iexplode->location.y  +4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -.5   ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z  ) );

					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4    ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4    ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  -4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -.5   ) , (iexplode->location.y  -4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -.5   ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  -4.5  ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4    ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4    ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  -4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +.5   ) , (iexplode->location.y  -4  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +.5   ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x  +4.5  ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  ) );

				//**********
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +.5  ) , (iexplode->location.z +4.5   ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  +4     ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z +4     ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z +4.5   ) );
					
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4  ) , (iexplode->location.z +4.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4  ) , (iexplode->location.z  +.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z  +.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z   +4.5 ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +.5  ) , (iexplode->location.z  -4.5  ) );
					glVertex3f( (iexplode->location.x ) , (iexplode->location.y  +.5  ) , (iexplode->location.z   -4    ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  -4     ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  +4.5 ) , (iexplode->location.z  -4.5  ) );
					
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4  ) , (iexplode->location.z  -4.5 ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4  ) , (iexplode->location.z -.5   ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z -.5   ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  +4.5  ) , (iexplode->location.z -4.5  ) );

					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  -4.5  ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  -4  ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z   -4 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  -4.5  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4  ) , (iexplode->location.z  -4.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4  ) , (iexplode->location.z -.5    ) );
					glVertex3f( (iexplode->location.x ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  -.5   ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z   -4.5 ) );
					
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  +4.5  ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y  -.5  ) , (iexplode->location.z  +4   ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z  +4   ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4.5 ) , (iexplode->location.z   +4.5 ) );
					
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  -4  ) , (iexplode->location.z +4.5  ) );
					glVertex3f( (iexplode->location.x   ) , (iexplode->location.y  -4  ) , (iexplode->location.z  +.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z  +.5  ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y  -4.5  ) , (iexplode->location.z +4.5  ) );
				}
			glEnd();
		iexplode->custom += .3;
		iexplode = loc_customf::incr(iexplode);
		}
		else
		iexplode = static_cast<phelColl*>(alist.Collision)->colList.erase(iexplode);
	}
}

void es_draw::drawFireExplosions()
{
	float tmpnum;
	loc_customf* iexplode = static_cast<phelColl*>(Weapons->Fire.Collision)->colList.front();
	while( iexplode != NULL)
	{
		if( iexplode->custom < 5 )
		{	tmpnum = 20-fabs(iexplode->custom);
				glBegin(GL_TRIANGLES);
				// top
					glColor3fv(red);
					glVertex3f( (iexplode->location.x -2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x    ) , (iexplode->location.y +tmpnum ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		 ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y +tmpnum ) , (iexplode->location.z    ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		 ) , (iexplode->location.z +2 ) );
				// second
					glColor3fv(yellow);
					glVertex3f( (iexplode->location.x -2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x -4 ) , (iexplode->location.y +tmpnum*.7 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x -2 ) , (iexplode->location.y		      ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +4 ) , (iexplode->location.y +tmpnum*.7 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +2 ) , (iexplode->location.y		      ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y +tmpnum*.7 ) , (iexplode->location.z -4 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z +2 ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y +tmpnum*.7 ) , (iexplode->location.z +4 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z +2 ) );
				// third
					glColor3fv(orange);
					glVertex3f( (iexplode->location.x -2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x -6 ) , (iexplode->location.y +tmpnum*.4 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +2 ) , (iexplode->location.y		   ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x -2 ) , (iexplode->location.y		      ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +6 ) , (iexplode->location.y +tmpnum*.4 ) , (iexplode->location.z  ) );
					glVertex3f( (iexplode->location.x +2 ) , (iexplode->location.y		      ) , (iexplode->location.z  ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y +tmpnum*.4 ) , (iexplode->location.z -6 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z +2 ) );
					
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z -2 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y +tmpnum*.4 ) , (iexplode->location.z +6 ) );
					glVertex3f( (iexplode->location.x  ) , (iexplode->location.y		    ) , (iexplode->location.z +2 ) );

				glEnd();
				iexplode->custom +=.8;
				iexplode = loc_customf::incr(iexplode);
		}
		else
		iexplode = static_cast<phelColl*>(Weapons->Fire.Collision)->colList.erase(iexplode);
	}
}


void es_draw::drawEnergy(phelit* ienergy)
{
//	phelit* ienergy;
	for( ienergy/*=Weapons->Energy.front()*/; ienergy!=NULL; ienergy = phelit::incr(ienergy))
	{
		glBegin(GL_QUADS);
			glColor3f(.9,.9,.9);
			glVertex3f( (ienergy->location.x  -3 ) , ienergy->location.y , (ienergy->location.z -3 ) );
			glVertex3f( (ienergy->location.x  +3 ) , ienergy->location.y , (ienergy->location.z -3 ) );
			glVertex3f( (ienergy->location.x  +3 ) , ienergy->location.y , (ienergy->location.z +3 ) );
			glVertex3f( (ienergy->location.x  -3 ) , ienergy->location.y , (ienergy->location.z +3 ) );
			glColor3f(.2,.2,.8);
			glVertex3f( (ienergy->location.x  -3 ) , (ienergy->location.y -3 ) , (ienergy->location.z) );
			glVertex3f( (ienergy->location.x  +3 ) , (ienergy->location.y -3 ) , (ienergy->location.z) );
			glVertex3f( (ienergy->location.x  +3 ) , (ienergy->location.y +3 ) , (ienergy->location.z) );
			glVertex3f( (ienergy->location.x  -3 ) , (ienergy->location.y +3 ) , (ienergy->location.z) );
			glColor3f(.2,.2,.8);
			glVertex3f( (ienergy->location.x) , (ienergy->location.y -3 ) , (ienergy->location.z -3 ) );
			glVertex3f( (ienergy->location.x) , (ienergy->location.y +3 ) , (ienergy->location.z -3 ) );
			glVertex3f( (ienergy->location.x) , (ienergy->location.y +3 ) , (ienergy->location.z +3 ) );
			glVertex3f( (ienergy->location.x) , (ienergy->location.y -3 ) , (ienergy->location.z +3 ) );
		glEnd();
	}
}


void es_draw::drawFire()
{float mult;
	phelcit* ifire;
	for (ifire=static_cast<phelcit*>(Weapons->Fire.front()); ifire!=NULL; ifire = static_cast<phelcit*>(phelcit::incr(ifire)))
	{ mult = 3-(ifire->custom*.1);
		glBegin(GL_QUADS);
			glColor3f(1,.8,0);
			glVertex3f( (ifire->location.x  -mult ) , ifire->location.y , (ifire->location.z -mult ) );
			glVertex3f( (ifire->location.x  +mult ) , ifire->location.y , (ifire->location.z -mult ) );
			glVertex3f( (ifire->location.x  +mult ) , ifire->location.y , (ifire->location.z +mult ) );
			glVertex3f( (ifire->location.x  -mult ) , ifire->location.y , (ifire->location.z +mult ) );
			glColor3f(1,.45,0);
			glVertex3f( (ifire->location.x  -mult ) , (ifire->location.y -mult ) , (ifire->location.z) );
			glVertex3f( (ifire->location.x  +mult ) , (ifire->location.y -mult ) , (ifire->location.z) );
			glVertex3f( (ifire->location.x  +mult ) , (ifire->location.y +mult ) , (ifire->location.z) );
			glVertex3f( (ifire->location.x  -mult ) , (ifire->location.y +mult ) , (ifire->location.z) );
			glColor3f(1,.2,0);
			glVertex3f( (ifire->location.x) , (ifire->location.y -mult ) , (ifire->location.z -mult ) );
			glVertex3f( (ifire->location.x) , (ifire->location.y +mult ) , (ifire->location.z -mult ) );
			glVertex3f( (ifire->location.x) , (ifire->location.y +mult ) , (ifire->location.z +mult ) );
			glVertex3f( (ifire->location.x) , (ifire->location.y -mult ) , (ifire->location.z +mult ) );
		glEnd();
	}
}

void es_draw::drawBombs()
{
	phelit* ibomb;
	for( ibomb=Weapons->Bombs.front(); ibomb!=NULL; ibomb=phelit::incr(ibomb))
	{
		glBegin(GL_QUADS);
			glColor3fv(black);
			glVertex3f( (ibomb->location.x  -3 ) , ibomb->location.y , (ibomb->location.z -3 ) );
			glVertex3f( (ibomb->location.x  +3 ) , ibomb->location.y , (ibomb->location.z -3 ) );
			glVertex3f( (ibomb->location.x  +3 ) , ibomb->location.y , (ibomb->location.z +3 ) );
			glVertex3f( (ibomb->location.x  -3 ) , ibomb->location.y , (ibomb->location.z +3 ) );
			glColor3fv(dmaroon);
			glVertex3f( (ibomb->location.x  -3 ) , (ibomb->location.y -3 ) , (ibomb->location.z) );
			glVertex3f( (ibomb->location.x  +3 ) , (ibomb->location.y -3 ) , (ibomb->location.z) );
			glVertex3f( (ibomb->location.x  +3 ) , (ibomb->location.y +3 ) , (ibomb->location.z) );
			glVertex3f( (ibomb->location.x  -3 ) , (ibomb->location.y +3 ) , (ibomb->location.z) );

			glVertex3f( (ibomb->location.x) , (ibomb->location.y -3 ) , (ibomb->location.z -3 ) );
			glVertex3f( (ibomb->location.x) , (ibomb->location.y +3 ) , (ibomb->location.z -3 ) );
			glVertex3f( (ibomb->location.x) , (ibomb->location.y +3 ) , (ibomb->location.z +3 ) );
			glVertex3f( (ibomb->location.x) , (ibomb->location.y -3 ) , (ibomb->location.z +3 ) );
		glEnd();
	}
}

void es_draw::drawThrow()
{
	phelit* ithrow;
	for( ithrow=Weapons->Throw.front(); ithrow!=NULL; ithrow=phelit::incr(ithrow))
	{
		glBegin(GL_QUADS);
			glColor3fv(black);
			glVertex3f( (ithrow->location.x  -3 ) , ithrow->location.y , (ithrow->location.z -3 ) );
			glVertex3f( (ithrow->location.x  +3 ) , ithrow->location.y , (ithrow->location.z -3 ) );
			glVertex3f( (ithrow->location.x  +3 ) , ithrow->location.y , (ithrow->location.z +3 ) );
			glVertex3f( (ithrow->location.x  -3 ) , ithrow->location.y , (ithrow->location.z +3 ) );
			glColor3fv(maroon);
			glVertex3f( (ithrow->location.x  -3 ) , (ithrow->location.y -3 ) , (ithrow->location.z) );
			glVertex3f( (ithrow->location.x  +3 ) , (ithrow->location.y -3 ) , (ithrow->location.z) );
			glVertex3f( (ithrow->location.x  +3 ) , (ithrow->location.y +3 ) , (ithrow->location.z) );
			glVertex3f( (ithrow->location.x  -3 ) , (ithrow->location.y +3 ) , (ithrow->location.z) );

			glVertex3f( (ithrow->location.x) , (ithrow->location.y -3 ) , (ithrow->location.z -3 ) );
			glVertex3f( (ithrow->location.x) , (ithrow->location.y +3 ) , (ithrow->location.z -3 ) );
			glVertex3f( (ithrow->location.x) , (ithrow->location.y +3 ) , (ithrow->location.z +3 ) );
			glVertex3f( (ithrow->location.x) , (ithrow->location.y -3 ) , (ithrow->location.z +3 ) );
		glEnd();
	}
}
void es_draw::drawSlime()
{
	phelit* islime;
	for( islime=Weapons->Slime.front(); islime!=NULL; islime=phelit::incr(islime))
	{
		glBegin(GL_QUADS);
			glColor3fv(lgreen);
			glVertex3f( (islime->location.x  -3 ) , islime->location.y , (islime->location.z -3 ) );
			glVertex3f( (islime->location.x  +3 ) , islime->location.y , (islime->location.z -3 ) );
			glVertex3f( (islime->location.x  +3 ) , islime->location.y , (islime->location.z +3 ) );
			glVertex3f( (islime->location.x  -3 ) , islime->location.y , (islime->location.z +3 ) );
			glColor3fv(mgreen);
			glVertex3f( (islime->location.x  -3 ) , (islime->location.y -3 ) , (islime->location.z) );
			glVertex3f( (islime->location.x  +3 ) , (islime->location.y -3 ) , (islime->location.z) );
			glVertex3f( (islime->location.x  +3 ) , (islime->location.y +3 ) , (islime->location.z) );
			glVertex3f( (islime->location.x  -3 ) , (islime->location.y +3 ) , (islime->location.z) );

			glVertex3f( (islime->location.x) , (islime->location.y -3 ) , (islime->location.z -3 ) );
			glVertex3f( (islime->location.x) , (islime->location.y +3 ) , (islime->location.z -3 ) );
			glVertex3f( (islime->location.x) , (islime->location.y +3 ) , (islime->location.z +3 ) );
			glVertex3f( (islime->location.x) , (islime->location.y -3 ) , (islime->location.z +3 ) );
		glEnd();
	}
}


void es_draw::drawBricks()
{
	std::vector<es_brick>::const_iterator ibrick;
	glBegin(GL_QUADS);
		for(ibrick=World->Bricks.begin(); ibrick<World->Bricks.end(); ibrick++)
		{
		// TOP
			glColor3fv(ibrick->topColor);
			glVertex3f(ibrick->cor1.x,  ibrick->cor2.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor2.x,  ibrick->cor2.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor2.x,  ibrick->cor2.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor1.x,  ibrick->cor2.y, ibrick->cor2.z);
		// FACE
			glColor3f(.4,.15,.15);
			glVertex3f(ibrick->cor1.x,   ibrick->cor1.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor2.x,   ibrick->cor1.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor2.x,   ibrick->cor2.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor1.x,   ibrick->cor2.y, ibrick->cor2.z);
		// LEFT
			//glColor3f(.4,.15,.15);
			glVertex3f(ibrick->cor1.x,  ibrick->cor1.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor1.x,  ibrick->cor2.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor1.x,  ibrick->cor2.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor1.x,  ibrick->cor1.y, ibrick->cor1.z);	
		// RIGHT
			glColor3f(.6,.225,.225);
			glVertex3f(ibrick->cor2.x,   ibrick->cor1.y, ibrick->cor2.z);
			glVertex3f(ibrick->cor2.x,   ibrick->cor1.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor2.x,   ibrick->cor2.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor2.x,   ibrick->cor2.y, ibrick->cor2.z);
		// BACK
			//glColor3f(.6,.225,.225);
			glVertex3f(ibrick->cor2.x,  ibrick->cor1.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor1.x,  ibrick->cor1.y, ibrick->cor1.z);			
			glVertex3f(ibrick->cor1.x,  ibrick->cor2.y, ibrick->cor1.z);
			glVertex3f(ibrick->cor2.x,  ibrick->cor2.y, ibrick->cor1.z);
		
		}
	glEnd();
}
