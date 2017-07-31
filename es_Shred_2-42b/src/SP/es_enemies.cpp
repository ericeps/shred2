#include "es_enemies.h"
#include "defs.h"
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include "es_lookout.h"
#include "es_world.h"
#include "angleFuncs.h"
#include <iostream>

es_enemies::es_enemies()
{
Energy.Collision = new phelColl(0);
Lookouts = new es_lookoutList;
Chasers = new es_chaserList;
}
void es_enemies::setVars(es_world* awor)
{
World=awor;
Lookouts->setVars(World, &Energy);
Chasers->setVars(World);
}

void es_enemies::killMemory()
{/**/
std::list<es_baseEnem>::iterator iic;
for(iic=Chasers->Units.begin();iic!=Chasers->Units.end();iic++)
{
iic->memory=1;
}
std::list<es_baseEnem>::iterator iil;
for(iil=Lookouts->Units.begin();iil!=Lookouts->Units.end();iil++)
{
iil->memory=1;
}

}

void es_enemies::action()
{
Lookouts->action();
Chasers->action();
}

bool es_enemies::Damage(point3f &apoint,int prox,float dmg)
{
if(Lookouts->Damage(apoint,prox,dmg))
	return 1;
if(Chasers->Damage(apoint,prox,dmg))
	return 1;
return  0;
}

void es_enemies::AllDamage(point3f &apoint,int prox,float dmg)
{
Lookouts->AllDamage(apoint,prox,dmg);
Chasers->AllDamage(apoint,prox,dmg);
}

void es_enemies::CheckSights(point3f &aship, int shipLevel)
{
Lookouts->SightWithin(aship, shipLevel);
Chasers->SightWithin(aship, shipLevel);
}
bool es_enemies::CheckSlow(point3f &aslow, int prox,float amt,float ttimer){
    if(Chasers->Slow(aslow,prox,amt,ttimer))
            return 1;
    if(Lookouts->Slow(aslow,prox,amt,ttimer))
            return 1;
    return  0;
}

/*
void es_enemies::push_backLookout(es_lookout alookout)
{
Lookouts->push_back(alookout);
Lookouts->back().iiIdle = Lookouts->back().Idle.begin();
}
bool es_enemies::LookoutDamage(point3f &apoint,int prox,float dmg)
{
std::list<es_lookout>::iterator ii=Lookouts->begin();
for(ii;ii!=Lookouts->end();ii++)
{
	float tmpx,tmpy,tmpz;
	tmpx = fabs(apoint.x - ii->body.x);
	tmpz = fabs(apoint.z - ii->body.z);
	tmpy = fabs(apoint.y - ii->body.y);
	if(tmpx < 50 && tmpz < 50 && tmpy < 50)
	{
		if(tmpx < prox && tmpz < prox && tmpy < prox)
		{	ii->Health-=dmg;
			return 1;
		}
		tmpx = fabs(apoint.x - ii->feet.x);
		tmpz = fabs(apoint.z - ii->feet.z);
		tmpy = fabs(apoint.y - ii->feet.y);
		if(tmpx < prox && tmpz < prox && tmpy < prox)
		{	ii->Health-=dmg;
			return 1;
		}
	}
}
return 0;
}
void es_enemies::AllLookoutDamage(point3f &apoint,int prox,float dmg)
{
std::list<es_lookout>::iterator ii=Lookouts->begin();
for(ii;ii!=Lookouts->end();ii++)
{
	float tmpx,tmpy,tmpz;
	tmpx = fabs(apoint.x - ii->body.x);
	tmpz = fabs(apoint.z - ii->body.z);
	tmpy = fabs(apoint.y - ii->body.y);
	if(tmpx < 50 && tmpz < 50 && tmpy < 50)
	{
		if(tmpx < prox && tmpz < prox && tmpy < prox)
		{	ii->Health-=dmg;
			continue;
		}
		tmpx = fabs(apoint.x - ii->feet.x);
		tmpz = fabs(apoint.z - ii->feet.z);
		tmpy = fabs(apoint.y - ii->feet.y);
		if(tmpx < prox && tmpz < prox && tmpy < prox)
		{	ii->Health-=dmg;
			continue;
		}
	}
}
}

void es_enemies::addEnergy(point3f &abod,float theta){
	phelit *tmpenergy = new phelit;
	tmpenergy->shift.x = cos(theta)*6;
	tmpenergy->shift.z = sin(theta)*6;
	tmpenergy->shift.y = 0;
	tmpenergy->location.x = abod.x + tmpenergy->shift.x;
	tmpenergy->location.z = abod.z + tmpenergy->shift.z;
	tmpenergy->location.y = abod.y;
	tmpenergy->pID = 11;
	Energy.push_back(tmpenergy);
}


void es_enemies::LookoutSightWithin(point3f &apoint,int layer)
{
std::list<es_lookout>::iterator ift = Lookouts->begin();
for(ift;ift!=Lookouts->end();ift++)
{
			float avZ,avX,avgle,avist;
			avZ = apoint.z - ift->body.z;
			avX = apoint.x - ift->body.x;
			avgle = atan2(avZ,avX);
			avist = avZ/sin(avgle);
		float A1,B1;
			std::vector<es_sight>::iterator ii;
			for(ii=ift->SightList.begin();ii!=ift->SightList.end();ii++)
			{	A1=makeAngle(ift->Theta+ii->A);
				B1=makeAngle(ift->Theta+ii->B);
					if( angleWithin(avgle,A1,B1) && avist <= ii->dist
						&& ift->Layers.end()!=std::find(ift->Layers.begin(),ift->Layers.end(),layer) 
						&& 0 == World->isWallBetween(ift->body, apoint,ift->Layers) )
					{	ift->inSight=1;
						ift->Theta=avgle;
						if(!ift->isSighted)
						{	//ii->iimove=ii->movement.begin();
							ift->Sighted=ii;
							ift->isSighted=1;
						}
						break;
					}
					else
					ift->inSight=0;
			}
			if(ift->isSighted)
			{
					if(++(ift->Sighted->attackDelay) == ift->Sighted->CattackDelay)
					{	if(ift->inSight==1)
						addEnergy(ift->body,avgle);
						ift->Sighted->attackDelay=0;
					}
//					if( ! ift->Sighted->movement.empty())
//					{
//							ift->body.x += ift->Sighted->iimove->x;
//							ift->feet.x += ift->Sighted->iimove->x;
//							ift->body.z += ift->Sighted->iimove->z;
//							ift->feet.z += ift->Sighted->iimove->z;
//							if(++(ift->Sighted->iimove->count)==ift->Sighted->iimove->constcount)
//							{	ift->Sighted->iimove->count=0;
//								if(++(ift->Sighted->iimove)==ift->Sighted->movement.end())
//								ift->isSighted=0;
//							}
//					}
//					else
//
					ift->isSighted=0;
			}
			else if( ! ift->Idle.empty())
			{
				ift->body.x += ift->iiIdle->x;
				ift->feet.x += ift->iiIdle->x;
				ift->body.z += ift->iiIdle->z;
				ift->feet.z += ift->iiIdle->z;
				ift->Theta =  makeAngle(ift->Theta + ift->iiIdle->Theta);
				if(++(ift->iiIdle->count) == ift->iiIdle->constcount)
				{	ift->iiIdle->count=0;
					if(++(ift->iiIdle) == ift->Idle.end())
					ift->iiIdle=ift->Idle.begin();
				}
			}
}
}
*/
