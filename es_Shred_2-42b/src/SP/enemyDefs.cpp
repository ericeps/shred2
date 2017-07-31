#include "enemyDefs.h"
#include "angleFuncs.h"
#include <cmath>
#include <iostream>
using namespace std;

es_idleGest mvt::mSpin(float atheta, float aspeed)
{
es_idle anidle(0.0,0.0,atheta,aspeed);
std::vector<es_idle> tmpidle;
tmpidle.push_back(anidle);
es_idleGest agest(tmpidle,1);
agest.setFixBase(new Spin());
return agest;
}
es_idleGest mvt::mStand()
{
es_idle anidle(0.0,0.0,0,1);
std::vector<es_idle> tmpidle;
tmpidle.push_back(anidle);
es_idleGest agest(tmpidle,1);
agest.setFixBase(new Stand());
return agest;
}

void es_idleGest::fix(float amt)
{
//speed*=amt;
FixBase->Fix(this,amt);
}

std::vector<es_moving> mvt::BackAndForth(float x, float y, int count)
{
es_moving m1(x,y,count);
es_moving m2(-x,-y,count*2);
es_moving m3(x,y,count);
std::vector<es_moving> hovec;
hovec.push_back(m1);
hovec.push_back(m2);
hovec.push_back(m3);
return hovec;
}

es_idleGest mvt::mPeekOut(float xxx, float zzz, float theta, float aspeed, int delay1, int delay2)
{
		es_idle m0(0,0,0,delay1);
		es_idle m1(0,0,0,delay2);
        float ccc,axx,azz,tang,att;
        ccc = sqrt((xxx*xxx)+(zzz*zzz));
        int tmpcount = ccc/aspeed;
        tang=atan2(zzz,xxx);
        axx = cos(tang)*aspeed;
        azz = sin(tang)*aspeed;
        att = (ang::makeAngle(theta))/tmpcount;
        es_idle tmpidle(axx,azz,att,tmpcount);
        es_idle tmpidlerev(-axx,-azz,-att,tmpcount);

        float tx = xxx-(axx*tmpcount);
        float tz = zzz-(azz*tmpcount);
        es_idle tmpidle2(tx,tz,0,1);
        es_idle tmpidle2rev(-tx,-tz,0,1);

        std::vector<es_idle> agest;
        if(tmpcount>0)
        {	agest.push_back(m0);
            agest.push_back(tmpidle);
            agest.push_back(tmpidle2);
            agest.push_back(m1);
            agest.push_back(tmpidle2rev);
            agest.push_back(tmpidlerev);
        }
        else
        {
            float tatt = (ang::makeAngle(theta))/40;
            es_idle tmpidleatt(0,0,tatt,40);
            es_idle tmpidleattrev(0,0,-tatt,40);
            agest.push_back(m0);
            agest.push_back(tmpidle2);
            agest.push_back(tmpidleatt);
            agest.push_back(m1);
            agest.push_back(tmpidleattrev);
            agest.push_back(tmpidle2rev);
        }
        es_idleGest tmpgest(agest,1);
		tmpgest.setFixBase(new PeekOut(xxx,zzz,theta,aspeed,delay1,delay2));
		//tmpgest.x=xxx;tmpgest.z=zzz;tmpgest.theta=theta;tmpgest.speed=aspeed;tmpgest.delay01=delay1;tmpgest.delay02=delay2;
		return tmpgest;
}
void PeekOut::Fix(es_idleGest *AGest,float amt)
{std::cout<<"peekoutFix"<<std::endl;
	speed*=amt;
		es_idle m0(0,0,0,delay01);
		es_idle m1(0,0,0,delay02);
        float ccc,axx,azz,tang,att;
        ccc = sqrt((x*x)+(z*z));
        int tmpcount = ccc/speed;
        tang=atan2(z,x);
        axx = cos(tang)*speed;
        azz = sin(tang)*speed;
        att = (ang::makeAngle(theta))/tmpcount;
        es_idle tmpidle(axx,azz,att,tmpcount);
        es_idle tmpidlerev(-axx,-azz,-att,tmpcount);

        float tx = x-(axx*tmpcount);
        float tz = z-(azz*tmpcount);
        es_idle tmpidle2(tx,tz,0,1);
        es_idle tmpidle2rev(-tx,-tz,0,1);

        std::vector<es_idle> agest;
        if(tmpcount>0)
        {	agest.push_back(m0);
            agest.push_back(tmpidle);
            agest.push_back(tmpidle2);
            agest.push_back(m1);
            agest.push_back(tmpidle2rev);
            agest.push_back(tmpidlerev);
        }
        else
        {
            float tatt = (ang::makeAngle(theta))/40;
            es_idle tmpidleatt(0,0,tatt,40);
            es_idle tmpidleattrev(0,0,-tatt,40);
            agest.push_back(m0);
            agest.push_back(tmpidle2);
            agest.push_back(tmpidleatt);
            agest.push_back(m1);
            agest.push_back(tmpidleattrev);
            agest.push_back(tmpidle2rev);
        }
        AGest->Idles=agest;
}

void Spin::Fix(es_idleGest *AGest,float amt)
{

}
void Stand::Fix(es_idleGest *AGest,float amt)
{

}
