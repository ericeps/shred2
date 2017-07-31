




#include "es_chaser.h"
#include <cmath>
#include <algorithm>
#include "defs.h"
#include "physDefs.h"
#include "es_world.h"
#include "angleFuncs.h"

#include <iostream>
using namespace std;

es_chaserList::es_chaserList() : es_baseEnemList()
{

}

void es_chaserList::justSpotted(std::list<es_baseEnem>::iterator apoint){

}
void es_chaserList::spottedInMem(std::list<es_baseEnem>::iterator apoint){

}
void es_chaserList::leftSight(std::list<es_baseEnem>::iterator apoint){

}
void es_chaserList::leftMem(std::list<es_baseEnem>::iterator apoint){

}

/*
void es_chaserList::SightWithin(point3f &apoint,int layer)
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
                && isSameLayer && 0== isWallBet )
            {	ift->inSight=1;
                ift->memory = 300;
                ift->Theta=avgle;
            }
            else
            ift->inSight=0;
    
			if(ift->memory != 0)//  Unit currently sees or has recently seen avatar
            {
                if(--ift->memory == 0)
				{	ift->Gestures.at(ift->idleState).Idles.at(ift->iiIdle).count = 0;
                    //ift->idleState=-2;
                    ift->calcGestToOrig(ift->origSpot);
                    ift->idleState=0;
                    ift->iiIdle=0;
				}
                else
                {
                    if(ift->inSight==1)
                    {
                        float nx,nz;
                        nx = cos(avgle)*ift->mSpeed;
                        nz = sin(avgle)*ift->mSpeed;
                        ift->body.x += nx;
                        ift->feet.x += nx;
                        ift->body.z += nz;
                        ift->feet.z += nz;
                    }
                    else if(isWallBet && isSameLayer)// Avatar not within sights, but recently was
                    {
                        point2f tmp = World->bestPath(ift->body,apoint);
                        float nx,nz;
                        float anZ,anX,nangle;
                        anZ = tmp.z - ift->body.z;
                        anX = tmp.x - ift->body.x;
                        if(anZ!=0&&anX!=0)
                        {
                            nangle = atan2(anZ,anX);
                            nx = cos(nangle)*ift->mSpeed;
                            nz = sin(nangle)*ift->mSpeed;
                        
                            ift->body.x += nx;
                            ift->feet.x += nx;
                            ift->body.z += nz;
                            ift->feet.z += nz;
                        }
                    }
                }

            }
			else// Do this when idle (avatar not in sights and not in unit's memory)
			{
			    ift->actIdle();
			}
}
}
*/
