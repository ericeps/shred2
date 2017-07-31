
#include "es_collision.h"
#include "es_avatar.h"
#include "es_pickupcon.h"
#include "es_world.h"
#include "es_players.h"
#include "es_weapons.h"
#include "es_enemies.h"

#include <cmath>
#include <list>
#include <algorithm>

#include <iostream>

es_collision::es_collision(bool ism)
{isMulti=ism;
}
void es_collision::setVars(es_world* awor, es_avatar* anav, es_weapons* aweap, es_pickupcon* apick,es_players* aplay,es_enemies* anem){
World=awor;
Avatar=anav;
Weapons=aweap;
Pickup=apick;
Players=aplay;
Enemies=anem;
}

void es_collision::avDeath()
{
isAlive=0;
}
void es_collision::avLive()
{
isAlive=1;
}

void es_collision::action()
{
if(isAlive)
moveAvatar();
isPickup();

molim(Weapons->Energy.front());
molim(Weapons->Bombs.front());
molim(Weapons->Fire.front());
mogim(Weapons->Throw.front(),-.14);
mogim(Weapons->Slime.front(),-.002);

killsecond(Weapons->Energy,Weapons->Bombs,7);
killsecond(Weapons->Energy,Weapons->Throw,7);
killboth(Weapons->Fire,Weapons->Bombs,7);
killboth(Weapons->Throw,Weapons->Bombs,8);

worldstops(Weapons->Bombs,-3);
worldkills(Weapons->Energy);
worldkills(Weapons->Slime);
worldkills(Weapons->Fire);
changeCustom(Weapons->Fire,-1);

damage(Weapons->Energy,7,5);
damageProx(Weapons->Bombs,7,10,25,20);
damageProx(Weapons->Throw,8,10,25,20);
damage(Weapons->Fire,7,.4);
changeSpeed(Weapons->Slime,5,-.03,3.6);

if(isMulti){
	compPlr(Weapons->Energy,7);
	compPlr(Weapons->Bombs,7);
	compPlr(Weapons->Throw,8);
	compPlr(Weapons->Fire,7);
	compPlr(Weapons->Slime,5);
	worldkillsAvadax(Weapons->Throw,25,20);
}
else{
	molim(Enemies->Energy.front());
	killsecond(Enemies->Energy,Weapons->Bombs,7);
	worldkills(Enemies->Energy);
	worldkillsFiAvadax(Weapons->Throw,25,20);
	damage(Enemies->Energy,7,5);
	damageEnemies(Weapons->Energy,7,5);
	damageAllEnemies(Weapons->Bombs,7,10,25,20);
	damageAllEnemies(Weapons->Throw,8,10,25,20);
	damageEnemies(Weapons->Fire,7,.4);
	chaserWithin(Avatar->Ship.Center, 10,10);
        chaserSlow(Weapons->Slime,8,.7,3.6);
	Enemies->CheckSights(Avatar->Ship.Center, World->getLevel(Avatar->Ship.Center.y));
}
}

void es_collision::chaserWithin(point3f &apoint, int prox, float dmg)
{
if(Enemies->Chasers->Damage(apoint,prox,20))
{Avatar->dealDamage(dmg,12);
}
}

void es_collision::damageEnemies(phlist &alist,int prox, float dmg){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Enemies->Damage(item->location,prox,dmg))
		{	alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
		}
}
void es_collision::damageAllEnemies(phlist &alist,int prox, float dmg, int prox2, float dmg2){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Enemies->Damage(item->location,prox,dmg))
		{	Enemies->AllDamage(item->location,prox2,dmg2);
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
		}
}
void es_collision::damage(phlist &alist,int prox, float dmg){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Avatar->isWithin(item->location,prox))
		{	Avatar->dealDamage(dmg,item->pID);
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
		}
	}
void es_collision::damageProx(phlist &alist,int prox, float dmg,int prox2, float dmg2){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Avatar->isWithin(item->location,prox))
		{	Avatar->dealDamage(dmg,item->pID);
				if(Avatar->isWithin(item->location,prox2))
				Avatar->dealDamage(dmg2,item->pID);
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
		}
	}
void es_collision::changeSpeed(phlist &alist,int prox,float amt,float ttimer){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Avatar->isWithin(item->location,prox))
		{Avatar->changeSpeed(amt,ttimer,item->pID);
		alist.Collision->Process(item);
		item = alist.erase(item);
		continue;
		}
		item = phelit::incr(item);
		}
	}
void es_collision::chaserSlow(phlist &alist,int prox,float amt,float ttimer){
    phelit *item = alist.front();
            while(item !=NULL)
            {
            if(Enemies->CheckSlow(item->location,prox,amt,ttimer))
            {
            alist.Collision->Process(item);
            item = alist.erase(item);
            continue;
            }
            item = phelit::incr(item);
            }
    }

void es_collision::compPlr(phlist &alist,int prox){
	phelit *item = alist.front();
		while(item !=NULL)
		{
		if(Players->isWithin(item->location,prox))
		{
		alist.Collision->Process(item);
		item = alist.erase(item);
		continue;
		}
		item = phelit::incr(item);
		}
	}

void es_collision::changeCustom(phlist &alist, int ch){
	phelcit *item = static_cast<phelcit*>(alist.front());
	while(item !=NULL)
	{
		if(item->custom <= 0)
		{item = static_cast<phelcit*>(alist.erase(item));
		continue;
		}
		item->custom+=ch;
		item = static_cast<phelcit*>(phelcit::incr(item));
	}
	}


void es_collision::isPickup()
{
	std::list<es_pickup>::iterator ipickup;
	ipickup = Pickup->PickupList.begin(); 
	while( ipickup != Pickup->PickupList.end())
	{	
		if(ipickup->timer <= 0)
		{
			if (Avatar->isWithin(ipickup->location, 5))
			{
			Avatar->refillWeapon(ipickup->type,ipickup->amount);
			ipickup->timer=1000;
			++ipickup;
			}
			else if(isMulti && Players->isWithin(ipickup->location,5))
			{
			ipickup->timer=1000;
			++ipickup;
			}
			else
			++ipickup;
		}
		else
		++ipickup;
	}
}
void es_collision::killsecond(phlist &first, phlist &second, int prox)
{
point3f tmp;
phelit* ifirst=first.front();
phelit* isecond=second.front();
	while(ifirst != NULL)
	{	isecond=second.front();
		while (isecond != NULL)
		{
			tmp.x = fabs( isecond->location.x - ifirst->location.x );
			tmp.z = fabs( isecond->location.z - ifirst->location.z );
			tmp.y = fabs( isecond->location.y - ifirst->location.y );
			if(tmp.x < prox && tmp.z < prox && tmp.y < prox)
			{
			second.Collision->Process(isecond);
			isecond=second.erase(isecond);
			continue;
			}
			isecond=phelit::incr(isecond);
		}
		ifirst = phelit::incr(ifirst);
	}
}

void es_collision::killboth(phlist &first, phlist &second, int prox)
{
point3f tmp;
phelit* ifirst=first.front();
phelit* isecond=second.front();
bool tmpkill = 0;
	while(ifirst != NULL)
	{	isecond=second.front();
		while (isecond != NULL)
		{
			tmp.x = fabs( isecond->location.x - ifirst->location.x );
			tmp.z = fabs( isecond->location.z - ifirst->location.z );
			tmp.y = fabs( isecond->location.y - ifirst->location.y );
			if(tmp.x < prox && tmp.z < prox && tmp.y < prox)
			{
			second.Collision->Process(isecond);
			isecond=second.erase(isecond);
			tmpkill = 1;
			break;
			}
			isecond = phelit::incr(isecond);
		}
		if(tmpkill==1)
		{	tmpkill=0;
			first.Collision->Process(ifirst);
			ifirst=first.erase(ifirst);
		}
		else
		ifirst = phelit::incr(ifirst);
	}
}

void es_collision::molim(phelit *item){ //linear item
	while(item !=NULL)
	{
		item->location.x += item->shift.x;
		item->location.y += item->shift.y;
		item->location.z += item->shift.z;
		item = phelit::incr(item);
	}
}
void es_collision::mogim(phelit *item, float wgt){ //gravity item{
	while(item !=NULL)
	{
		item->location.x += item->shift.x;
		item->location.y += item->shift.y;
		item->location.z += item->shift.z;
		item->shift.y += wgt;
		item = phelit::incr(item);
	}
}


void es_collision::worldkills(phlist &alist){
	phelit *item = alist.front();
	while(item !=NULL)
	{
		if(!World->isClear(item->location))
		{
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
	}
}
void es_collision::worldkillsFiAvadax(phlist &alist,int prox,int dmg){
	phelit *item = alist.front();
	while(item !=NULL)
	{
		if(!World->isClear(item->location))
		{	Enemies->AllDamage(item->location,prox,dmg);
			if(Avatar->isWithin(item->location,prox))
			Avatar->dealDamage(dmg,item->pID);
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
	}
}
//worldkillsAvadax processes Throw collision w/ world, and dmges avatar if avatar is within prox
void es_collision::worldkillsAvadax(phlist &alist,int prox,int dmg){
	phelit *item = alist.front();
	while(item !=NULL)
	{
		if(!World->isClear(item->location))
		{	if(Avatar->isWithin(item->location,prox))
			Avatar->dealDamage(dmg,item->pID);
			alist.Collision->Process(item);
			item = alist.erase(item);
			continue;
		}
		item = phelit::incr(item);
	}
}
void es_collision::worldstops(phlist &alist){
	phelit *item = alist.front();
	while(item !=NULL)
	{
		if(!World->isClear(item->location))
		{
			item->shift.x=0;
			item->shift.y=0;
			item->shift.z=0;
		}
		item = phelit::incr(item);
	}
}
void es_collision::worldstops(phlist &alist,int tbelow){
	phelit *item = alist.front();
	while(item !=NULL)
	{
                if(!World->isClear_layer(item->location, item->location.y+tbelow))
		{
			item->shift.x=0;
			item->shift.y=0;
			item->shift.z=0;
		}
		item = phelit::incr(item);
	}
}

void es_collision::moveAvatar()
{
		if ( ! Check_Move() )
		{
		Collision_Process();
		}
}

bool es_collision::Check_Move()
{

float headx,headz,strafx,strafz,vert,boostx,boostz;
headx=0;
headz=0;
strafx=0;
strafz=0;
boostx=0;
boostz=0;
vert=0;

		// CALCULATE X, Z, & LAYER POSITIONS *******************
			// TURN LEFT/RIGHT
				if(Avatar->Momentum.spin)
				{
					int tmptheta = Avatar->Theta;
						if(Avatar->Momentum.spin>0)
						tmptheta++;
						else if(Avatar->Momentum.spin<0)
						tmptheta--;
					if(tmptheta==360)
					tmptheta=0;
					else if(tmptheta==-1)
					tmptheta=359;
					es_ship4 tmpship = Avatar->imagineTheta(tmptheta);
					if ( World->isClear( tmpship ) )
					{Avatar->Theta = tmptheta;
					Avatar->Ship = tmpship;
					}
				}

			// FORWARD/BACKWARD
                                if(Avatar->Momentum.head)
                                {

                                headx  = sin(Avatar->Theta*3.14159/180)*Avatar->Momentum.head*Avatar->Speed;
                                headz  = cos(Avatar->Theta*3.14159/180)*Avatar->Momentum.head*Avatar->Speed;
                                }
			// STRAFE LEFT/RIGHT
				if(Avatar->Momentum.strafe)
				{
				strafx  = cos(Avatar->Theta*3.14159/180)*Avatar->Momentum.strafe*Avatar->Speed;
				strafz  = sin(Avatar->Theta*3.14159/180)*Avatar->Momentum.strafe*-Avatar->Speed;
				}
			// FLY/SINK
				if(Avatar->Momentum.vert)
				{	vert = Avatar->Momentum.vert*Avatar->Speed;
				}
                       // Boost
                               if(Avatar->boostStatus){
                                     headx  += sin(Avatar->Theta*3.14159/180)*-(Avatar->sBoost);
                                     headz  += cos(Avatar->Theta*3.14159/180)*-(Avatar->sBoost);
                               }


        es_ship4 TmpShip = Avatar->imagineMove(headx+strafx, headz+strafz, vert);

	if (World->isClear_Report( TmpShip ))
	{Avatar->Ship = TmpShip;
	return 1;
	}
	else
	{
	collisionDetail(TmpShip);
	return 0;
	}
}

void es_collision::collisionDetail(es_ship4 &aship)
{
	int ghostLevel,avatarLevel;
	ghostLevel = aship.Center.y / World->Layer_Height;
	avatarLevel = Avatar->Ship.Center.y / World->Layer_Height;
	point3f *shipSidePtr;

	if(World->CollisionReport.Avatar_Side == FRONT)
		shipSidePtr = &aship.Front;
	else if(World->CollisionReport.Avatar_Side == BACK)
		shipSidePtr = &aship.Back;
	else if(World->CollisionReport.Avatar_Side == LEFT)
		shipSidePtr = &aship.Left;
	else if(World->CollisionReport.Avatar_Side == RIGHT)
		shipSidePtr = &aship.Right;


		if(World->isClear_layer(aship, Avatar->Ship.Center.y))
		{										
			if(ghostLevel > avatarLevel)
			World->CollisionReport.Wall_Side=Y1;
			else
			World->CollisionReport.Wall_Side=Y2;
		}
		else

		{
			// Calculate distances to x and z boundaries
					float x1dist,x2dist,z1dist,z2dist;
				x1dist = shipSidePtr->x - World->CollisionReport.BoundPtr->cor1.x;
				x2dist = World->CollisionReport.BoundPtr->cor2.x - shipSidePtr->x;
				z1dist = shipSidePtr->z - World->CollisionReport.BoundPtr->cor1.z;
				z2dist = World->CollisionReport.BoundPtr->cor2.z - shipSidePtr->z;

				float dists[] = {x1dist,x2dist,z1dist,z2dist};
				std::vector<float> distvector (dists,dists+4);
				std::sort(distvector.begin(),distvector.begin()+4);

			// WHICH AXIS IS CLOSER, TO DETECT WHICH COLLIDED
				// CHECKS TO SEE IF IN A CORNER
				if( (distvector[1] - distvector[0]) < 1)
				{
						COLLIDE tmpCollide0,tmpCollide1;
						if (distvector[0] == x1dist)
						{tmpCollide0=X1;
						}
						else if (distvector[0] == x2dist)
						{tmpCollide0=X2;
						}
						else if (distvector[0] == z1dist)
						{tmpCollide0=Z1;
						}
						else if (distvector[0] == z2dist)
						{tmpCollide0=Z2;
						}
						
						if (distvector[1] == x1dist)
						{tmpCollide1=X1;
						}
						else if (distvector[1] == x2dist)
						{tmpCollide1=X2;
						}
						else if (distvector[1] == z1dist)
						{tmpCollide1=Z1;
						}
						else if (distvector[1] == z2dist)
						{tmpCollide1=Z2;
						}
					Avatar->punchME(tmpCollide0,tmpCollide1);
				}
				// CALCULATES WHICH FACET WAS HIT
				else
				if (distvector[0] == x1dist)
				{World->CollisionReport.Wall_Side=X1;
				}
				else if (distvector[0] == x2dist)
				{World->CollisionReport.Wall_Side=X2;
				}
				else if (distvector[0] == z1dist)
				{World->CollisionReport.Wall_Side=Z1;
				}
				else if (distvector[0] == z2dist)
				{World->CollisionReport.Wall_Side=Z2;
				}
		}
//std::cout<<"\nCollide..."<<World->CollisionReport.Wall_Side<<std::endl;
}


void es_collision::Collision_Process()
{


				// TURN LEFT/RIGHT
						// DOES THIS DO ANYTHING??
						if(Avatar->Momentum.spin)
						{		int tmptheta = Avatar->Theta;
							if(Avatar->Momentum.spin>0)
							tmptheta++;
							else if(Avatar->Momentum.spin<0)
							tmptheta--;
									if(tmptheta==360)
									tmptheta=0;
									else if(tmptheta==-1)
									tmptheta=359;
						
							es_ship4 tmpship = Avatar->imagineTheta(tmptheta);
							if ( World->isClear( tmpship ) )
							{Avatar->Theta = tmptheta;
							Avatar->Ship = tmpship;
							}
						}

				// VERTICAL, FLY & SINK
						if(Avatar->Momentum.vert && (World->CollisionReport.Wall_Side==Y1 || World->CollisionReport.Wall_Side==Y2))
						{	float tmpvert;
							if(World->CollisionReport.Wall_Side == Y1)
								tmpvert = Avatar->Ship.Center.y - Avatar->Momentum.vert *Avatar->Speed;
							else if(World->CollisionReport.Wall_Side == Y2)
								tmpvert = Avatar->Ship.Center.y - Avatar->Momentum.vert *Avatar->Speed;

							if(tmpvert <0)
							tmpvert=0;
							else if(tmpvert > World->Max_Height)
							tmpvert=World->Max_Height;
						Avatar->setVert(tmpvert);
						}



				// FORWARD & BACKWARD
						if(Avatar->Momentum.head && (World->CollisionReport.Wall_Side==X1 || World->CollisionReport.Wall_Side==X2))
						{
								float tmpx = sin(Avatar->Theta*3.14159/180) *  -Avatar->Speed *Avatar->Momentum.head;
								float tmpz = cos(Avatar->Theta*3.14159/180) *   Avatar->Speed *Avatar->Momentum.head;
								es_ship4 tmpShip = Avatar->imagineShift(tmpx,tmpz);

							if( World->isClear(tmpShip))
							{
							Avatar->Ship = tmpShip;
							}
						}
						else if(Avatar->Momentum.head && (World->CollisionReport.Wall_Side==Z2 || World->CollisionReport.Wall_Side==Z1))
						{
								float tmpx = sin(Avatar->Theta*3.14159/180) *   Avatar->Speed *Avatar->Momentum.head;
								float tmpz = cos(Avatar->Theta*3.14159/180) *  -Avatar->Speed *Avatar->Momentum.head;
								es_ship4 tmpShip = Avatar->imagineShift(tmpx,tmpz);

							if( World->isClear(tmpShip))
							{
							Avatar->Ship = tmpShip;
							}
						}

						
				// STRAFE LEFT & RIGHT
						if(Avatar->Momentum.strafe && (World->CollisionReport.Wall_Side==Z1 || World->CollisionReport.Wall_Side==Z2))
						{
								float tmpx = cos(Avatar->Theta*3.14159/180) *  Avatar->Speed *Avatar->Momentum.strafe;
								float tmpz = sin(Avatar->Theta*3.14159/180) *  Avatar->Speed *Avatar->Momentum.strafe;
								es_ship4 tmpShip = Avatar->imagineShift(tmpx,tmpz);

							if( World->isClear(tmpShip))
							{
							Avatar->Ship = tmpShip;
							}
						}
						else if(Avatar->Momentum.strafe && (World->CollisionReport.Wall_Side==X1 || World->CollisionReport.Wall_Side==X2))
						{
								float tmpx = cos(Avatar->Theta*3.14159/180) * -Avatar->Speed *Avatar->Momentum.strafe;
								float tmpz = sin(Avatar->Theta*3.14159/180) * -Avatar->Speed *Avatar->Momentum.strafe;
								es_ship4 tmpShip = Avatar->imagineShift(tmpx,tmpz);

							if( World->isClear(tmpShip))
							{
							Avatar->Ship = tmpShip;
							}
						}
}



