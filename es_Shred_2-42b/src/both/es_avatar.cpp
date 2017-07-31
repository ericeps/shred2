
#include <iostream>
#include "defs.h"
#include "es_avatar.h"
#include "es_world.h"
#include <cmath>
#include "es_net.h"
#include "es_control.h"
#include "es_pInfo.h"
#include <utility>


es_avatar::es_avatar(bool ismul)
{
colorIndex=0;
isMulti = ismul;
move.left=0;
move.right=0;
move.up=0;
move.down=0;
move.jump=0;
move.crouch=0;
move.turnleft=0;
move.turnright=0;

Momentum.vert=0;
Momentum.head=0;
Momentum.strafe=0;
Momentum.spin=0;
Speed = .06;
chSpeed=0.0;
sBoost=0.0;
sideTilt=0;
headTilt=0;
Health = 20;
Deaths=0;
JumpFluid = 100;
boostStatus=0;
regenCount=0;
respawnCount=0;
stock_energy = 1000;
stock_fire = 20000;
stock_bombs = 1000;
stock_slime = 1000;
}

void es_avatar::reset()
{
move.left=0;
move.right=0;
move.up=0;
move.down=0;
move.jump=0;
move.crouch=0;
move.turnleft=0;
move.turnright=0;

Momentum.vert=0;
Momentum.head=0;
Momentum.strafe=0;
Momentum.spin=0;
sideTilt=0;
headTilt=0;
Health = 20;
Speed = .06;
chSpeed=0.0;
sBoost=0.0;
JumpFluid = 100;
boostStatus=0;
stock_energy = 1000;
stock_fire = 20000;
stock_bombs = 1000;
stock_slime = 1000;
regenCount=0;
respawnCount=0;
}

void es_avatar::setVars(es_world* awor,es_control *acon, es_pInfo* ap){
World=awor;
Control=acon;
pInfo=ap;
}

void es_avatar::setNet(es_net *anet){
Net = anet;
}
void es_avatar::setColorIndex(unsigned char anint){
colorIndex=anint;
}

void es_avatar::action()
{
	calcMomentum();

	calcHealth();
	if(isMulti)
	Net->sendShip(Ship, Theta, Health, sideTilt, headTilt);
}

void es_avatar::calcHealth()
{
	if(Health < 20 && Health > 0)
	{	if(++regenCount > 400)
		Health+=.07;
	}
	else if(Health <=0 && respawnCount<200)
	{	//if(respawnCount ==0)
		//Control->death();
		++respawnCount;
		Health=0;
		this->shiftVert(1);
	}
	else if(respawnCount==200)
	{
		++Deaths;
		Control->live();
		respawnCount=0;
	}
}

bool es_avatar::isWithin(point3f &apoint, int arad)
{
	float tmpx,tmpy,tmpz;
	tmpx = fabs(apoint.x - Ship.Center.x);
	tmpz = fabs(apoint.z - Ship.Center.z);
	tmpy = fabs(apoint.y - Ship.Center.y);
if(tmpx < 50 && tmpz < 50 && tmpy < 50)
{
//	tmpx = fabs(apoint.x - Ship.Center.x);
//	tmpz = fabs(apoint.z - Ship.Center.z);
//	tmpy = fabs(apoint.y - Ship.Center.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
	tmpx = fabs(apoint.x - Ship.Front.x);
	tmpz = fabs(apoint.z - Ship.Front.z);
	tmpy = fabs(apoint.y - Ship.Front.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
	tmpx = fabs(apoint.x - Ship.Back.x);
	tmpz = fabs(apoint.z - Ship.Back.z);
	tmpy = fabs(apoint.y - Ship.Back.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
	tmpx = fabs(apoint.x - Ship.Left.x);
	tmpz = fabs(apoint.z - Ship.Left.z);
	tmpy = fabs(apoint.y - Ship.Left.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
	tmpx = fabs(apoint.x - Ship.Right.x);
	tmpz = fabs(apoint.z - Ship.Right.z);
	tmpy = fabs(apoint.y - Ship.Right.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
	tmpx = fabs(apoint.x - Ship.C2.x);
	tmpz = fabs(apoint.z - Ship.C2.z);
	tmpy = fabs(apoint.y - Ship.C2.y);
	if(tmpx < arad && tmpz < arad && tmpy < arad)
	return 1;
}
return 0;
}

void es_avatar::dealDamage(float anum,unsigned char pID)
{
Health -= anum;
regenCount=0;
if(Control->isAlive())
{	if(Health>0)
	{	if(isMulti)
		pInfo->damage(anum,pID);
	}
	else
	{	if(isMulti==1)
		{	pInfo->damage(anum+Health,pID);
			pInfo->killed(pID);
		}
		Control->death();
	}
}
}

point3f es_avatar::Center(){
return Ship.Center;
}
point3f es_avatar::Front(){
return Ship.Front;
}
point3f es_avatar::Back(){
return Ship.Back;
}
point3f es_avatar::Left(){
return Ship.Left;
}
point3f es_avatar::Right(){
return Ship.Right;
}
int es_avatar::getTheta(){
return Theta;
}

int es_avatar::stockEnergy(){
	return stock_energy;
	}
int es_avatar::stockFire(){
	return stock_fire;
	}
int es_avatar::stockBombs(){
	return stock_bombs;
	}
int es_avatar::stockThrow(){
	//return stock_throw;
	return stock_bombs;
	}
int es_avatar::stockSlime(){
	return stock_slime;
	}

void es_avatar::takeEnergy(){
	--stock_energy;
	}
void es_avatar::takeFire(){
	--stock_fire;
	}
void es_avatar::takeBomb(){
	--stock_bombs;
	}
void es_avatar::takeThrow(){
	//stock_throw--;
	--stock_bombs;
	}
void es_avatar::takeSlime(){
	--stock_slime;
	}

void es_avatar::refillWeapon(WEAPON_LIST weap, int amount){
	if(weap == ENERGY)
	stock_energy += amount;
	else if(weap == FIRE)
	stock_fire += amount;
	else if(weap == BOMB)
	stock_bombs += amount;
	else if(weap == THROW)
	stock_bombs += amount;
	else if(weap == SLIME)
	stock_slime += amount;
}

void es_avatar::Placement(point3f apoint, int atheta)
{
point2f tmpDepth,tmpSide;
Theta = atheta;
		tmpDepth.x = ( sin(atheta*3.14159/180) *1 );
		tmpDepth.z = ( cos(atheta*3.14159/180) *1 );
		tmpSide.x = ( cos(atheta*3.14159/180) *1 );
		tmpSide.z = ( sin(atheta*3.14159/180) *-1 );

Ship.Center.x = apoint.x;
Ship.Center.z = apoint.z;
Ship.Center.y = apoint.y;

Ship.Front.x = apoint.x + (tmpDepth.x* -12);
Ship.Front.z = apoint.z + (tmpDepth.z* -12);
Ship.Front.y = apoint.y;

Ship.Back.x = apoint.x + (tmpDepth.x* 7);
Ship.Back.z = apoint.z + (tmpDepth.z* 7);
Ship.Back.y = apoint.y;

Ship.Left.x = apoint.x + (tmpSide.x* -2);
Ship.Left.z = apoint.z + (tmpSide.z* -2);
Ship.Left.y = apoint.y;

Ship.Right.x = apoint.x + (tmpSide.x* 2);
Ship.Right.z = apoint.z + (tmpSide.z* 2);
Ship.Right.y = apoint.y;

Ship.C2.x = apoint.x + (tmpDepth.x* -6);
Ship.C2.z = apoint.z + (tmpDepth.z* -6);
Ship.C2.y = apoint.y;
}



es_ship4 es_avatar::imagineTheta(int atheta)
{
	point2f tmpDepth,tmpSide;
		tmpDepth.x = ( sin(atheta*3.14159/180) *1 );
		tmpDepth.z = ( cos(atheta*3.14159/180) *1 );
		tmpSide.x = ( cos(atheta*3.14159/180) *1 );
		tmpSide.z = ( sin(atheta*3.14159/180) *-1 );
es_ship4 tmpcoll;

tmpcoll.Center.x = Ship.Center.x;
tmpcoll.Center.z = Ship.Center.z;
tmpcoll.Center.y = Ship.Center.y;

tmpcoll.Front.x = Ship.Center.x + (tmpDepth.x* -15);
tmpcoll.Front.z = Ship.Center.z + (tmpDepth.z* -15);
tmpcoll.Front.y = Ship.Center.y;

tmpcoll.Back.x = Ship.Center.x + (tmpDepth.x* 10);
tmpcoll.Back.z = Ship.Center.z + (tmpDepth.z* 10);
tmpcoll.Back.y = Ship.Center.y;

tmpcoll.Left.x = Ship.Center.x + (tmpSide.x* -5);
tmpcoll.Left.z = Ship.Center.z + (tmpSide.z* -5);
tmpcoll.Left.y = Ship.Center.y;

tmpcoll.Right.x = Ship.Center.x + (tmpSide.x* 5);
tmpcoll.Right.z = Ship.Center.z + (tmpSide.z* 5);
tmpcoll.Right.y = Ship.Center.y;

tmpcoll.C2.x = Ship.Center.x + (tmpDepth.x* -7.5);
tmpcoll.C2.z = Ship.Center.z + (tmpDepth.z* -7.5);
tmpcoll.C2.y = Ship.Center.y;

return tmpcoll;
}

es_ship4 es_avatar::imagineMove(float ax,float az,float ay)
{
es_ship4 tmpship;
tmpship.Center.x = Ship.Center.x + ax;
tmpship.Center.z = Ship.Center.z + az;
tmpship.Front.x = Ship.Front.x + ax;
tmpship.Front.z = Ship.Front.z + az;
tmpship.Back.x = Ship.Back.x + ax;
tmpship.Back.z = Ship.Back.z + az;
tmpship.Left.x = Ship.Left.x + ax;
tmpship.Left.z = Ship.Left.z + az;
tmpship.Right.x = Ship.Right.x + ax;
tmpship.Right.z = Ship.Right.z + az;
tmpship.C2.x = Ship.C2.x + ax;
tmpship.C2.z = Ship.C2.z + az;

tmpship.Center.y = Ship.Center.y + ay;
tmpship.Front.y = Ship.Front.y + ay;
tmpship.Back.y = Ship.Back.y + ay;
tmpship.Left.y = Ship.Left.y + ay;
tmpship.Right.y = Ship.Right.y + ay;
tmpship.C2.y = Ship.C2.y + ay;

return tmpship;
}
es_ship4 es_avatar::imagineShift(float ax,float az)
{
es_ship4 tmpship;
tmpship.Center.x = Ship.Center.x + ax;
tmpship.Center.z = Ship.Center.z + az;
tmpship.Front.x = Ship.Front.x + ax;
tmpship.Front.z = Ship.Front.z + az;
tmpship.Back.x = Ship.Back.x + ax;
tmpship.Back.z = Ship.Back.z + az;
tmpship.Left.x = Ship.Left.x + ax;
tmpship.Left.z = Ship.Left.z + az;
tmpship.Right.x = Ship.Right.x + ax;
tmpship.Right.z = Ship.Right.z + az;
tmpship.C2.x = Ship.C2.x + ax;
tmpship.C2.z = Ship.C2.z + az;

tmpship.Center.y = Ship.Center.y;
tmpship.Front.y = Ship.Center.y;
tmpship.Back.y = Ship.Center.y;
tmpship.Left.y = Ship.Center.y;
tmpship.Right.y = Ship.Center.y;
tmpship.C2.y = Ship.Center.y;

return tmpship;
}

void es_avatar::shiftVert(float ay)
{
Ship.Center.y += ay;
Ship.Front.y += ay;
Ship.Back.y += ay;
Ship.Left.y += ay;
Ship.Right.y += ay;
Ship.C2.y += ay;
}
void es_avatar::setVert(float ay)
{
Ship.Center.y = ay;
Ship.Front.y = ay;
Ship.Back.y = ay;
Ship.Left.y = ay;
Ship.Right.y = ay;
Ship.C2.y = ay;
}

void es_avatar::calcMomentum()
{
		// CALCULATE MOMENTUM *******************
				// TURN LEFT & RIGHT
					if(move.turnright)
					{	--Momentum.spin;
						if(Momentum.spin<-12)
						Momentum.spin=-12;
					}
					else if(move.turnleft)
					{	++Momentum.spin;
						if(Momentum.spin >12)
						Momentum.spin=12;
					}
					else
					{
						if(Momentum.spin<0)
						++Momentum.spin;
						else if(Momentum.spin>0)
						--Momentum.spin;
					}
				// FORWARD & BACKWARD
					if(move.up)
					{	--Momentum.head;
						if(Momentum.head <-20)
						Momentum.head =-20;
					}
					else if(move.down)
					{	++Momentum.head;
						if(Momentum.head >10)
						Momentum.head =10;
					}
					else
					{
						if(Momentum.head<0)
						++Momentum.head;
						else if(Momentum.head>0)
						--Momentum.head;
					}
				// STRAFE LEFT & RIGHT
					if(move.left)
					{	--Momentum.strafe;
						if(Momentum.strafe <-15)
						Momentum.strafe=-15;
					}
					else if(move.right)
					{	++Momentum.strafe;
						if(Momentum.strafe >15)
						Momentum.strafe=15;
					}
					else
					{
						if(Momentum.strafe<0)
						++Momentum.strafe;
						else if(Momentum.strafe>0)
						--Momentum.strafe;
					}

					if(move.jump && JumpFluid > 0)
					{	if(++Momentum.vert>10)
						Momentum.vert=10;
						--JumpFluid;
					}
					else if(!World->isClear_layer(Ship, Ship.Center.y-1))
					{
						if((JumpFluid+=.2) > 100)
						JumpFluid = 100;
					Momentum.vert=0;
					}
					else
					{
						if(--Momentum.vert <-15)
						Momentum.vert=-15;
					}
		std::vector<std::pair<float,float> >::iterator ii;
		for(ii=chSpeedList.begin();ii!=chSpeedList.end();ii++)
		{
			if(ii->second > 0)
			{	if(--ii->second <=0)
					chSpeed -= ii->first;
				ii=chSpeedList.erase(ii);
			}
		}
		if(boostStatus==1 && JumpFluid > 0)
                {	sBoost = 2;
                        JumpFluid--;
		}
		else
		sBoost = 0.0;
        Speed = chSpeed + .06;//+sBoost;

		sideTilt = -Momentum.strafe + Momentum.spin;
		headTilt = (Momentum.head<0 ? (Momentum.head/4)+Momentum.vert : (Momentum.head/4)+(Momentum.vert/3));
}

void es_avatar::onBoost()
	{
	boostStatus=1;
	}
void es_avatar::offBoost()
	{
	boostStatus = 0;
	}
void es_avatar::changeSpeed(float amt, float ttimer,unsigned char pID)
{
ttimer*=83; // 12 millisecond loop * 83 == 996 milliseconds, or about 1 second
std::pair<float,float> tmpslow;
tmpslow.first=amt;
tmpslow.second=ttimer;
chSpeedList.push_back(tmpslow);
if(isMulti==1 && Control->isAlive())
pInfo->slowed(pID);
chSpeed += amt;
}
int es_avatar::getHeadMomentum(){
	return Momentum.head;
}
void es_avatar::shiftXZ(float ax, float az)
{
Ship.Center.x += ax;
Ship.Center.z += az;
Ship.Front.x += ax;
Ship.Front.z += az;
Ship.Back.x += ax;
Ship.Back.z += az;
Ship.Left.x += ax;
Ship.Left.z += az;
Ship.Right.x += ax;
Ship.Right.z += az;
Ship.C2.x += ax;
Ship.C2.z += az;
}

void es_avatar::punchME(COLLIDE acol0, COLLIDE acol1)
{
	if( acol0 == X1)
	{		if(acol1 == Z1)
			{
			shiftXZ(-.5,-.5);
			}
			else if(acol1 == Z2)
			{
			shiftXZ(-.5,.5);
			}
	}
	else if( acol0 == X2)
	{		if(acol1 == Z1)
			{
			shiftXZ(.5,-.5);
			}
			else if(acol1 == Z2)
			{
			shiftXZ(.5,.5);
			}
	}
	else if( acol0 == Z1)
	{		if(acol1 == X1)
			{
			shiftXZ(-.5,-.5);
			}
			else if(acol1 == X2)
			{
			shiftXZ(.5,-.5);
			}
	}
	else if( acol0 == Z2)
	{		if(acol1 == X1)
			{
			shiftXZ(-.5,.5);
			}
			else if(acol1 == X2)
			{
			shiftXZ(.5,.5);
			}
	}
}


