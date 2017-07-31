/* Common Enemy classes.

 */
#ifndef ENEMYDEFS
#define ENEMYDEFS

#include <vector>
#include "defs.h"
#include <iostream>
using namespace std;

class es_idleGest;

struct es_orig : public point3f {
float theta;
};



struct es_moving{
	es_moving(float ax,float az,int acc){x=ax;z=az;constcount=acc;count=0;}
	float x;
	float z;
	int constcount;
	int count;
    };
struct es_idle{
        es_idle(float ax,float az,float atheta, int acc){x=ax;z=az;Theta=atheta,constcount=acc;count=0;}
	float x;
	float z;
	float Theta;
	int constcount;
	int count;
    };

struct gestBase{  //convenience class to make vectors of es_moving
    gestBase(){;}
    virtual void Fix(es_idleGest *AGest,float)=0;
    virtual ~gestBase(){;}
    };
struct PeekOut : public gestBase{
    PeekOut(float ax,float az, float at, float asp,float ad1,float ad2){x=ax;z=az;theta=at;speed=asp;delay01=ad1;delay02=ad2;}
	virtual void Fix(es_idleGest *AGest,float);
	float x,z,theta,speed;
    float delay01;
    float delay02;
    };
struct Spin : public gestBase{
    Spin(){;}
	virtual void Fix(es_idleGest *AGest,float);
    };
struct Stand : public gestBase{
    Stand(){;}
	virtual void Fix(es_idleGest *AGest,float);
    };

struct es_idleGest{
    es_idleGest(std::vector<es_idle> anidle,int anext){Idles=anidle;nextGest=anext;FixBase=NULL;}
    void fix(float amt);

    void setFixBase(gestBase *abase){if(FixBase!=NULL)
										delete FixBase;
										FixBase=abase;}
    std::vector<es_idle> Idles;
	int iiIdle;
    int nextGest;
    private:
        gestBase *FixBase;
    };



struct es_sight{
	es_sight(float aa,float bb, int adist, int AtkDelay=83, std::vector<es_moving> amov = std::vector<es_moving>())
			{A=aa; B=bb; dist=adist; attackDelay=0; CattackDelay=AtkDelay; Moves=amov;iimove=0;};
	float A;
	float B;
	int dist;
	std::vector< es_moving > Moves;
    int iimove;
	int CattackDelay;
	int attackDelay;
    };


struct mvt{  //convenience class to make vectors of es_moving
    mvt(){;}
    static es_idleGest mPeekOut(float x, float z, float theta, float speed, int delay1,int delay2);
	static std::vector<es_moving> BackAndForth(float x, float y, int count);
    static es_idleGest mSpin(float atheta, float aspeed);
    static es_idleGest mStand();
};


#endif
