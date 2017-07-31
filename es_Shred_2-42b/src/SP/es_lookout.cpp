// setVars (Energy)
// addEnergy()

#include "es_lookout.h"
#include <cmath>
#include <algorithm>
#include "defs.h"
#include "physDefs.h"
#include "es_world.h"
#include "angleFuncs.h"

es_lookoutList::es_lookoutList() : es_baseEnemList()
{
    
}
void es_lookoutList::setVars(es_world* awor,phlist *aenergy)
{
World=awor;
Energy = aenergy;
}

void es_lookoutList::justSpotted(std::list<es_baseEnem>::iterator apoint){

}
void es_lookoutList::spottedInMem(std::list<es_baseEnem>::iterator apoint){

}
void es_lookoutList::leftSight(std::list<es_baseEnem>::iterator apoint){

}
void es_lookoutList::leftMem(std::list<es_baseEnem>::iterator apoint){

}

/*
void es_lookoutList::SightWithin(point3f &apoint,int layer)
{
std::list<es_baseEnem>::iterator ift = Units.begin();
for(ift;ift!=Units.end();ift++)
{
			float avZ,avX,avgle,avist;
			avZ = apoint.z - ift->body.z;
			avX = apoint.x - ift->body.x;
			avgle = atan2(avZ,avX);
			avist = avZ/sin(avgle);
            float A1,B1;
            bool isWallBet =  World->isWallBetween(ift->body, apoint,ift->Layers);;
            bool isSameLayer = (ift->Layers.end() != std::find(ift->Layers.begin(),ift->Layers.end(),layer));
            A1=ang::makeAngle(ift->Theta+ift->Sight.A);
            B1=ang::makeAngle(ift->Theta+ift->Sight.B);
            // See if avatar is within this sight
            if( ang::angleWithin(avgle,A1,B1) && avist <= ift->Sight.dist
                && isSameLayer && 0==isWallBet )
            {
				ift->inSight=1;
				ift->memory = 100;
				if(seeState==0)
				seeState=1;//spotted for first time
				else if(seeState==1)
				seeState=2;//is in sight, not first spot
				else if(seeState==4)
				seeState=5;//spotted while in memory
				else if(seeState==7)
				seeState=1;//spotted again, not in memory
            }
            else
            {
				ift->inSight=0;
				if(seeState==1 || seeState==2)
				seeState=3;//leaving sight, still in memory
				else if(seeState==3)
				seeState=4;//in memory, not in sight
            }

            if(ift->memory!=0)
			{
                if(--ift->memory == 0)
				{
					seeState=6;//leaving memory

				   //ift->Gestures.at(ift->idleState).Idles.at(ift->iiIdle).count = 0;
                    ift->idleState=1;
                    //ift->iiIdle=0;
                    ift->Theta = lastTheta;
				}
                else
                {
                    if(++(ift->Sight.attackDelay) == ift->Sight.CattackDelay)
                    {	
                        addEnergy(ift->body,avgle);
                        ift->Sight.attackDelay=0;
                    }
                    if(ift->inSight==1)
                    {
						ift->Theta=avgle;
                    }
                }
            }
            else // Do this if avatar is not in sight
			{
				seeState=7;
			   ift->actIdle();

			}
}
}
*/

void es_lookoutList::addEnergy(point3f &abod,float theta){
	phelit *tmpenergy = new phelit;
	tmpenergy->shift.x = cos(theta)*6;
	tmpenergy->shift.z = sin(theta)*6;
	tmpenergy->shift.y = 0;
	tmpenergy->location.x = abod.x + tmpenergy->shift.x;
	tmpenergy->location.z = abod.z + tmpenergy->shift.z;
	tmpenergy->location.y = abod.y;
	tmpenergy->pID = 11;
	Energy->push_back(tmpenergy);
}





