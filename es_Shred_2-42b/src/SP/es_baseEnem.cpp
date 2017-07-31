// setVars (Energy)
// addEnergy()
// memory values, should be setable
// SightWithin and memory handling

#include "es_baseEnem.h"
#include <cmath>
#include <algorithm>
#include "defs.h"
#include "physDefs.h"
#include "es_world.h"
#include "angleFuncs.h"

#include <iostream>
//using namespace std;

es_baseEnem::es_baseEnem(float ax, float ay, float az,float atheta, float aspeed
                       , std::vector<int> alayers, es_idleGest agest) : Sight(-.7,.7,100,40){
    body.x = origSpot.x = ax;
    body.y = origSpot.y = ay+4;
    body.z = origSpot.z = az;
    feet.x = ax;
    feet.y = ay;
    feet.z = az;
	Health=20;
	Theta= origSpot.theta = atheta;
	mSpeed = aspeed;
	Layers=alayers;
	inSight=0;
	Gestures.push_back(es_idleGest(std::vector<es_idle>(),-1));
	Gestures.push_back(agest);
	if(Gestures.empty())
        gestState=-1;
	else
        gestState=1;
	memory=0;
}


void es_baseEnem::setVars(es_world *awor)
{
    World=awor;
}

void es_baseEnem::addSight(float aa, float bb, int dist, int adelay, std::vector<es_moving> amove)
{
    es_sight hsight(aa,bb,dist,adelay,amove);
    Sight=hsight;
}

void es_baseEnem::calcGestToOrig(es_orig &aspot)
{
    if(!World->isWallBetween(body,aspot,Layers))
    {
        float xxx,zzz,ccc,axx,azz,tang,att;
        xxx = aspot.x-body.x;
        zzz = aspot.z-body.z;
        ccc = sqrt((xxx*xxx)+(zzz*zzz));
        int tmpcount = ccc/mSpeed;
        tang=atan2(zzz,xxx);
        axx = cos(tang)*mSpeed;
        azz = sin(tang)*mSpeed;
        att = (ang::makeAngle(aspot.theta - Theta))/tmpcount;
        es_idle tmpidle(axx,azz,att,tmpcount);
        
        float tx = aspot.x-(body.x+(axx*tmpcount));
        float tz = aspot.z-(body.z+(azz*tmpcount));
        es_idle tmpidle2(tx,tz,0,1);
        
        std::vector<es_idle> agest;
        if(tmpcount>0)
        {
            agest.push_back(tmpidle);
            agest.push_back(tmpidle2);
        }
        else
        {
            agest.push_back(tmpidle2);
            float tatt = (ang::makeAngle(aspot.theta-Theta))/40;
            es_idle tmpidleatt(0,0,tatt,40);
            agest.push_back(tmpidleatt);
        }
        es_idleGest tmpgest(agest,1);
        Gestures[0] = tmpgest;
        gestState=0;
    }
    else
    {
        point2f tmp2f;
        point2f tmpbody = body;
        std::vector<es_idle> agest;
        while(World->isWallBetween(tmpbody,aspot,Layers))
        {
            tmp2f = World->bestPath(tmpbody,aspot);
            float xxx,zzz,ccc,axx,azz,tang;
            xxx = tmp2f.x-tmpbody.x;
            zzz = tmp2f.z-tmpbody.z;
            ccc = sqrt((xxx*xxx)+(zzz*zzz));
            int tmpcount = ccc/mSpeed;
            tang=atan2(zzz,xxx);
            axx = cos(tang)*mSpeed;
            azz = sin(tang)*mSpeed;
            //	att = (ang::makeAngle(aspot.theta - Theta))/tmpcount;
            es_idle tmpidle(axx,azz,0,tmpcount);
            
            float tx = tmp2f.x-(tmpbody.x+(axx*tmpcount));
            float tz = tmp2f.z-(tmpbody.z+(azz*tmpcount));
            es_idle tmpidle2(tx,tz,0,1);
            
            if(tmpcount>0)
            {
                agest.push_back(tmpidle);
                agest.push_back(tmpidle2);
            }
            else
            {
                agest.push_back(tmpidle2);
            }
            tmpbody=tmp2f;
        }
        float xxx,zzz,ccc,axx,azz,tang,att;
        xxx = aspot.x-tmpbody.x;
        zzz = aspot.z-tmpbody.z;
        ccc = sqrt((xxx*xxx)+(zzz*zzz));
        int tmpcount = ccc/mSpeed;
        tang=atan2(zzz,xxx);
        axx = cos(tang)*mSpeed;
        azz = sin(tang)*mSpeed;
        att = (ang::makeAngle(aspot.theta - Theta))/tmpcount;
        es_idle tmpidle(axx,azz,att,tmpcount);
        
        float tx = aspot.x-(tmpbody.x+(axx*tmpcount));
        float tz = aspot.z-(tmpbody.z+(azz*tmpcount));
        es_idle tmpidle2(tx,tz,0,1);
        
        if(tmpcount>0)
        {
            agest.push_back(tmpidle);
            agest.push_back(tmpidle2);
        }
        else
        {
            agest.push_back(tmpidle2);
            float tatt = (ang::makeAngle(aspot.theta-Theta))/40;
            es_idle tmpidleatt(0,0,tatt,40);
            agest.push_back(tmpidleatt);
        }
        
        es_idleGest tmpgest(agest,1);
        Gestures[0] = tmpgest;
        gestState=0;
    }
}

void es_baseEnem::actIdle()
{
	if(gestState==-1)//Gestures is empty
        return;
	else if (gestState==0 || gestState==1)
	{
        body.x += Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).x;
        feet.x += Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).x;
        body.z += Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).z;
        feet.z += Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).z;
        Theta =  ang::makeAngle(Theta + Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).Theta);
        if(++(Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).count) == Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).constcount)
        {
            Gestures[gestState].Idles.at(Gestures[gestState].iiIdle).count=0;
            if(++(Gestures[gestState].iiIdle) == Gestures.at(gestState).Idles.size())
            {   Gestures[gestState].iiIdle=0;
                gestState=Gestures.at(gestState).nextGest;
            }
        }
 	}
 	else
 	cout<<"gestState does not equal zero or one!!!!"<<endl;
}

void es_baseEnem::fixSpeed(float amt)
{
    float tmpcountratio = (float)Gestures.at(gestState).Idles.at(Gestures[gestState].iiIdle).count
						 / (float)Gestures.at(gestState).Idles.at(Gestures[gestState].iiIdle).constcount;
    std::vector<es_idleGest>::iterator gi;
	for(gi=Gestures.begin();gi!=Gestures.end();gi++)
	{
		gi->fix(amt);
	}
    // calculate new count (as of this writing a the end spot will be off by up to 1)
    Gestures.at(gestState).Idles.at(Gestures[gestState].iiIdle).count
		 = tmpcountratio * Gestures.at(gestState).Idles.at(Gestures[gestState].iiIdle).constcount;
}

void es_baseEnemList::justSpotted(std::list<es_baseEnem>::iterator apoint){

}
void es_baseEnemList::spottedInMem(std::list<es_baseEnem>::iterator apoint){

}
void es_baseEnemList::leftSight(std::list<es_baseEnem>::iterator apoint){

}
void es_baseEnemList::leftMem(std::list<es_baseEnem>::iterator apoint){

}

void es_baseEnemList::action()
{
	std::list<es_baseEnem>::iterator ii=Units.begin();
	while(ii!=Units.end())
	{
		if(ii->Health<=0)
		{
            loc_customf *tmpexp = new loc_customf;
            tmpexp->location = ii->feet;
            tmpexp->custom = 0;
            colList.push_back(tmpexp);
            ii=Units.erase(ii);
		}
		else
            ++ii;
	}
}

es_baseEnemList::es_baseEnemList()
{
    
}

es_baseEnemList::~es_baseEnemList()
{

}
void es_baseEnemList::setVars(es_world *awor)
{
    World=awor;
}


void es_baseEnemList::push_back(es_baseEnem abaseEnem)
{// add a unit to this container
    abaseEnem.setVars(World);
    Units.push_back(abaseEnem);
}
bool es_baseEnemList::Damage(point3f &apoint,int prox,float dmg)
{// Damage first unit within proximity
    std::list<es_baseEnem>::iterator ii=Units.begin();
    for(ii;ii!=Units.end();ii++)
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
void es_baseEnemList::AllDamage(point3f &apoint,int prox,float dmg)
{// Damage all Units within proximity
    std::list<es_baseEnem>::iterator ii=Units.begin();
    for(ii;ii!=Units.end();ii++)
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

bool es_baseEnemList::Slow(point3f &apoint, int prox,float amt,float ttimer){
    std::list<es_baseEnem>::iterator ii=Units.begin();
    for(ii;ii!=Units.end();ii++)
    {
        float tmpx,tmpy,tmpz;
        tmpx = fabs(apoint.x - ii->body.x);
        tmpz = fabs(apoint.z - ii->body.z);
        tmpy = fabs(apoint.y - ii->body.y);
        if(tmpx < 50 && tmpz < 50 && tmpy < 50)
        {
            if(tmpx < prox && tmpz < prox && tmpy < prox)
            {	ii->mSpeed*=amt;
				ii->fixSpeed(amt);
                return 1;
            }
            tmpx = fabs(apoint.x - ii->feet.x);
            tmpz = fabs(apoint.z - ii->feet.z);
            tmpy = fabs(apoint.y - ii->feet.y);
            if(tmpx < prox && tmpz < prox && tmpy < prox)
            {	ii->mSpeed*=amt;
				ii->fixSpeed(amt);
                return 1;
            }
        }
    }
    return 0;
}

void es_baseEnemList::SightWithin(point3f &apoint,int layer)
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
            {//in sight
				ift->inSight=1;
				ift->memory = 100;
				if(ift->seeState==0)
				{	ift->seeState=1;//spotted for first time
					//std::list<es_baseEnem>::pointer(*ift)
					justSpotted(ift);
				}
				else if(ift->seeState==1)
				{	ift->seeState=2;//is in sight, not first spot

				}
				else if(ift->seeState==4)
				{	ift->seeState=5;//spotted while in memory
					spottedInMem(ift);
				}
            }
            else
            {//not in sight
				ift->inSight=0;
				if(ift->seeState==1 || ift->seeState==2)
				{	ift->seeState=3;//leaving sight, still in memory
					leftSight(ift);
				}
				else if(ift->seeState==3)
				ift->seeState=4;//in memory, not in sight
            }

            if(ift->memory!=0)
			{//in memory
                if(--ift->memory == 0)
				{//just left memory
					ift->seeState=6;//leaving memory
					leftMem(ift);
				}
            }
            else // Do this if avatar is not in sight
			{//not in memory
				ift->seeState=0;
				ift->actIdle();
			}
}
}
