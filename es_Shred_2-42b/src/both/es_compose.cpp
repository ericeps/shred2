#include "defs.h"
#include "es_compose.h"
#include <iostream>
#include "es_world.h"
#include "es_control.h"
#include "es_pickupcon.h"
#include "es_enemies.h"
#include "es_lookout.h"
#include "es_chaser.h"
#include <vector>
#include <list>
//#include <ctime>
#include <cstdlib>

typedef es_baseEnem es_chaser;
typedef es_baseEnem es_lookout;

es_compose::es_compose(bool ism)
{isMulti=ism;
}
void es_compose::setVars(es_world* aw,es_control* acon, es_pickupcon* apick, es_enemies* enem)
{
World =aw;
Control=acon;
Pickup=apick;
Enemies=enem;
}

void es_compose::makeMap(int aint)
	{
//		if(aint ==0)
//		aint = 1+ (rand() % 2);

		if(aint==1)
		{	int LayerHeight=8;
			map_1(LayerHeight);
			map_1_respawn(LayerHeight);
			map_1_pickup(LayerHeight);
			if(!isMulti)
			map_1_enemies(LayerHeight);
		}
		else if(aint==2)
		{	int LayerHeight=5;
			map_2(LayerHeight);
			map_2_respawn(LayerHeight);
			map_2_pickup(LayerHeight);
			if(!isMulti)
			map_2_enemies(LayerHeight);
		}
		else if(aint==3)
		{	int LayerHeight=8;
			map_3(LayerHeight);
			map_3_respawn(LayerHeight);
			map_3_pickup(LayerHeight);
			if(!isMulti)
			map_3_enemies(LayerHeight);
		}
                else if(aint==4)
                {	int LayerHeight=8;
                        map_4(LayerHeight);
                        map_4_respawn(LayerHeight);
                        map_4_pickup(LayerHeight);
                        if(!isMulti)
                        map_4_enemies(LayerHeight);
                }
		
	}

void es_compose::map_4(int LayerHeight){
        std::vector< std::vector<es_bound> > Bounds;
        std::vector<es_brick> brickAll;

                calcOuterBound(Bounds,300,3000,20);
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(0),0,LayerHeight*3));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(1),0,LayerHeight*3));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(2),0,LayerHeight*3));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(3),0,LayerHeight*3));

        es_bound abound;
        abound = es_compose::makeBound(0,2800,40,40,NL);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));
        abound = es_compose::makeBound(300,2800,40,40,NR);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));
        abound = es_compose::makeBound(0,2550,40,40,NL);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));
        abound = es_compose::makeBound(300,2550,40,40,NR);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));
        abound = es_compose::makeBound(0,2300,40,40,NL);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));
        abound = es_compose::makeBound(300,2300,40,40,NR);
                Bounds.at(0).push_back(abound);
                Bounds.at(1).push_back(abound);
                brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2));

        World->setupMap(Bounds,brickAll,LayerHeight);
}
void es_compose::map_4_respawn(int LayerHeight){
                std::vector<es_respawn> Respawn;
                es_respawn tmppoint;
                tmppoint.location.x = 150;
                tmppoint.location.z = 2950;
                tmppoint.location.y = 1;
                tmppoint.theta = 0;
                Respawn.push_back(tmppoint);
Control->setupRespawn(Respawn);
}
void es_compose::map_4_pickup(int LayerHeight){

}
void es_compose::map_4_enemies(int LayerHeight){
        std::vector<int> layers;
        layers.push_back(0);layers.push_back(1);layers.push_back(2);layers.push_back(3);
    {   es_lookout fig(30,0,2750,0,1,layers,mvt::mPeekOut(200,0,1.56,1,160,80));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(270,0,2750,3.1,1,layers,mvt::mPeekOut(-17,0,-1.56,1,160,40));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(30,0,2500,0,1,layers,mvt::mPeekOut(18,0,1.56,.8,160,55));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(270,0,2500,3.1,1,layers,mvt::mPeekOut(-20,0,-1.56,1,160,40));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    for(int icount=0;icount<1000;icount+=5)
    {
    es_chaser cha4(30,0,2250-icount,0,1,layers,mvt::mStand());
    cha4.addSight(-.7,.7,300,50);
    Enemies->Chasers->push_back(cha4);
    }

    for(int icount=0;icount<1000;icount+=5)
    {
    es_chaser cha4(270,0,2250-icount,3.1,1,layers,mvt::mStand());
    cha4.addSight(-.7,.7,300,50);
    Enemies->Chasers->push_back(cha4);
    }

}


void es_compose::map_3(int LayerHeight){
	std::vector< std::vector<es_bound> > Bounds;
	std::vector<es_brick> brickAll;

		calcOuterBound(Bounds,1000,1000,20);
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(0),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(1),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(2),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(3),0,LayerHeight*4));
			
	es_bound abound;
	abound = es_compose::makeBound(440,430,120,30,NL);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(430,440,30,120,FR);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(570,560,30,120,NL);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(560,570,120,30,FR);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));

	abound = es_compose::makeBound(440,840,80,80,FR);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(440,760,80,80,NR);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(560,840,80,80,FL);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));
	abound = es_compose::makeBound(560,760,80,80,NL);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));

	abound = es_compose::makeBound(400,200,200,30,NL);
		Bounds.at(0).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));

	World->setupMap(Bounds,brickAll,LayerHeight);
}
void es_compose::map_3_respawn(int LayerHeight){
		std::vector<es_respawn> Respawn;
		es_respawn tmppoint;
		tmppoint.location.x = 650;
		tmppoint.location.z = 500;
		tmppoint.location.y = 1;
		tmppoint.theta = 90;
		Respawn.push_back(tmppoint);
Control->setupRespawn(Respawn);	
}
void es_compose::map_3_pickup(int LayerHeight){

}
void es_compose::map_3_enemies(int LayerHeight){
std::vector<int> layers;
layers.push_back(0);layers.push_back(1);
es_lookout fig(500,0,500,1.5,1,layers,mvt::mSpin(.019,83));
fig.addSight(-.7,.7,300,50);//,mvt::BackAndForth(0,.3,50));
Enemies->Lookouts->push_back(fig);

std::vector<int> layers2;
layers2.push_back(0);layers2.push_back(1);
es_lookout fig2(500,0,800,1.5,1,layers2,mvt::mSpin(.019,83));
fig2.addSight(-.7,.7,300,50);
Enemies->Lookouts->push_back(fig2);

/*
es_chaser cha1(100,0,100,1.5,layers2,mvt::mSpin(.019,83));
cha1.addSight(-.7,.7,300,50);
Enemies->Chasers->push_back(cha1);

es_chaser cha2(200,0,100,1.5,layers2,mvt::mSpin(.019,83));
cha2.addSight(-.7,.7,300,50);
Enemies->Chasers->push_back(cha2);

es_chaser cha3(300,0,100,1.5,layers2,mvt::mSpin(.019,83));
cha3.addSight(-.7,.7,300,50);
Enemies->Chasers->push_back(cha3);

es_chaser cha4(400,0,100,1.5,layers2,mvt::mSpin(.019,83));
cha4.addSight(-.7,.7,300,50);
Enemies->Chasers->push_back(cha4);
*/
for(int ii=0;ii<3;++ii)
{
es_chaser cha4(100+(5*ii),0,100,1.5,1,layers2,mvt::mSpin(.019,83));
cha4.addSight(-.7,.7,300,50);
Enemies->Chasers->push_back(cha4);
}

}





void es_compose::map_2_enemies(int LayerHeight){
        std::vector<int> layers;
 /*       layers.push_back(0);layers.push_back(1);layers.push_back(2);layers.push_back(3);
    {   es_lookout fig(30,0,2750,0,1,layers,mvt::mPeekOut(200,0,1.56,1,160,80));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(270,0,2750,3.1,1,layers,mvt::mPeekOut(-17,0,-1.56,1,160,40));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(30,0,2500,0,1,layers,mvt::mPeekOut(18,0,1.56,.8,160,55));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }
    {   es_lookout fig(270,0,2500,3.1,1,layers,mvt::mPeekOut(-20,0,-1.56,1,160,40));
        fig.addSight(-.7,.7,200,50);//,mvt::BackAndForth(0,.3,50));
        Enemies->Lookouts->push_back(fig);
    }

	{
    es_chaser cha4(30,0,2250-icount,0,1,layers,mvt::mStand());
    cha4.addSight(-.7,.7,300,50);
    Enemies->Chasers->push_back(cha4);
    }
*/
}
void es_compose::map_2(int LayerHeight)
{
	std::vector< std::vector<es_bound> > Bounds;
	std::vector<es_brick> brickAll;

		calcOuterBound(Bounds,1000,1000,20);
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(0),0,LayerHeight*7));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(1),0,LayerHeight*7));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(2),0,LayerHeight*7));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(3),0,LayerHeight*7));

	es_bound abound;
	abound = es_compose::makeBound(335,335,330,330,FL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight*2,.6,.6,.6));

	abound = es_compose::makeBound(335,335,50,50,FL);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*2,LayerHeight*6));

	abound = es_compose::makeBound(335,665,50,50,NL);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*2,LayerHeight*6));

	abound = es_compose::makeBound(665,665,50,50,NR);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*2,LayerHeight*6));

	abound = es_compose::makeBound(665,335,50,50,FR);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*2,LayerHeight*6));

	abound = es_compose::makeBound(440,440,120,120,FL);
		Bounds.at(2).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*2,LayerHeight*3));
	abound = es_compose::makeBound(80,345,40,40,FL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(200,345,40,40,FL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(80,655,40,40,NL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(200,655,40,40,NL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(920,345,40,40,FR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(800,345,40,40,FR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(920,655,40,40,NR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(800,655,40,40,NR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
		Bounds.at(5).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*6));

	abound = es_compose::makeBound(150,1000,300,150,NL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*5));

	abound = es_compose::makeBound(850,1000,300,150,NR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*5));

	abound = es_compose::makeBound(150,0,300,150,FL);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*5));

	abound = es_compose::makeBound(850,0,300,150,FR);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
		Bounds.at(3).push_back(abound);
		Bounds.at(4).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound,LayerHeight*0,LayerHeight*5));

	World->setupMap(Bounds,brickAll,LayerHeight);
}

void es_compose::map_2_respawn(int LayerHeight)
{
		std::vector<es_respawn> Respawn;
		es_respawn tmppoint;
		tmppoint.location.x = 170;
		tmppoint.location.z = 925;
		tmppoint.location.y = 26;
		tmppoint.theta = 0;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 170;
		tmppoint.location.z = 25;
		tmppoint.location.y = 26;
		tmppoint.theta = 180;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 830;
		tmppoint.location.z = 925;
		tmppoint.location.y = 26;
		tmppoint.theta = 0;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 830;
		tmppoint.location.z = 25;
		tmppoint.location.y = 26;
		tmppoint.theta = 180;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 50;
		tmppoint.location.z = 500;
		tmppoint.location.y = 1;
		tmppoint.theta = 270;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 950;
		tmppoint.location.z = 500;
		tmppoint.location.y = 1;
		tmppoint.theta = 90;
		Respawn.push_back(tmppoint);
Control->setupRespawn(Respawn);	
}
void es_compose::map_2_pickup(int LayerHeight)
{
	std::list<es_pickup> PickupList;

	es_pickup tmp;
	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 400;
	tmp.location.y = 28;
	tmp.location.z = 925;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 600;
	tmp.location.y = 28;
	tmp.location.z = 925;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 400;
	tmp.location.y = 28;
	tmp.location.z = 75;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 600;
	tmp.location.y = 28;
	tmp.location.z = 75;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 305;
	tmp.location.y = 3;
	tmp.location.z = 500;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 695;
	tmp.location.y = 3;
	tmp.location.z = 500;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 500;
	tmp.location.y = 3;
	tmp.location.z = 305;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 500;
	tmp.location.y = 3;
	tmp.location.z = 695;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 360;
	tmp.location.y = 33;
	tmp.location.z = 360;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 360;
	tmp.location.y = 33;
	tmp.location.z = 640;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 640;
	tmp.location.y = 33;
	tmp.location.z = 640;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 640;
	tmp.location.y = 33;
	tmp.location.z = 360;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 100;
	tmp.location.y = 33;
	tmp.location.z = 365;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 100;
	tmp.location.y = 33;
	tmp.location.z = 635;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 900;
	tmp.location.y = 33;
	tmp.location.z = 365;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 900;
	tmp.location.y = 33;
	tmp.location.z = 635;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 500;
	tmp.location.y = 18;
	tmp.location.z = 500;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 75;
	tmp.location.y = 1;
	tmp.location.z = 75;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 925;
	tmp.location.y = 1;
	tmp.location.z = 75;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 75;
	tmp.location.y = 1;
	tmp.location.z = 925;
	PickupList.push_back(tmp);
	
	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 925;
	tmp.location.y = 1;
	tmp.location.z = 925;
	PickupList.push_back(tmp);

Pickup->setupPickup(PickupList);
}

void es_compose::map_1_enemies(int LayerHeight){

std::vector<int> layers;
layers.push_back(3);

es_lookout tmp1fighter(500,3*LayerHeight,540,0,1,layers,mvt::mSpin(.019,83));
tmp1fighter.addSight(-.7,.7,400,83);
Enemies->Lookouts->push_back(tmp1fighter);

es_lookout tmp2fighter(540,3*LayerHeight,500,1.5,1,layers,mvt::mSpin(-.019,83));
tmp2fighter.addSight(-.7,.7,400,83);
Enemies->Lookouts->push_back(tmp2fighter);

es_lookout tmp3fighter(460,3*LayerHeight,500,-1.5,1,layers,mvt::mSpin(-.019,83));
tmp3fighter.addSight(-.7,.7,400,83);
Enemies->Lookouts->push_back(tmp3fighter);

es_lookout tmp4fighter(500,3*LayerHeight,460,3.1,1,layers,mvt::mSpin(.019,83));
tmp4fighter.addSight(-.7,.7,400,83);
Enemies->Lookouts->push_back(tmp4fighter);


std::vector<int> layers2;
layers2.push_back(0);layers2.push_back(1);layers2.push_back(2);
es_lookout tmp5fighter(220,0,780,0,1,layers2,mvt::mSpin(-.019,83));
tmp5fighter.addSight(-.7,.7,300,50,mvt::BackAndForth(0,.3,50));
Enemies->Lookouts->push_back(tmp5fighter);


std::vector<int> layers3;
layers3.push_back(0);layers2.push_back(1);layers2.push_back(2);
es_lookout tmp6fighter(100,0,500,0,1,layers2,mvt::mSpin(.019,83));
tmp6fighter.addSight(-.7,.7,300,50,mvt::BackAndForth(0,.3,50));
Enemies->Lookouts->push_back(tmp6fighter);
}

void es_compose::map_1(int LayerHeight)
{
	std::vector< std::vector<es_bound> > Bounds;
	std::vector<es_brick> brickAll;

                calcOuterBound(Bounds,1000,1000,20);
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(0),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(1),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(2),0,LayerHeight*4));
			brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(3),0,LayerHeight*4));

		// maze pieces
		Bounds.at(0).push_back(es_compose::makeBound(250, 750, 125, 20,FL));
		Bounds.at(0).push_back(es_compose::makeBound(250, 750,  20,125,FL));
		Bounds.at(0).push_back(es_compose::makeBound(750, 750, 125, 20,FR));
		Bounds.at(0).push_back(es_compose::makeBound(750, 750,  20,125,FR));
			brickAll.push_back(es_compose::makeBrick(250, 750, 125, 20,0,LayerHeight,FL));
			brickAll.push_back(es_compose::makeBrick(250, 750,  20,125,0,LayerHeight, FL));
			brickAll.push_back(es_compose::makeBrick(750, 750,125, 20,0,LayerHeight,  FR));
			brickAll.push_back(es_compose::makeBrick(750, 750, 20,125,0,LayerHeight,  FR));

		// bridges
		Bounds.at(1).push_back(es_compose::makeBound(450, 750,  100, 20,FL));
		Bounds.at(2).push_back(es_compose::makeBound(450, 750,  100, 20,FL));
		Bounds.at(0).push_back(es_compose::makeBound(450, 750,  30, 20,FL));
		Bounds.at(0).push_back(es_compose::makeBound(550, 750,  30, 20,FR));
		Bounds.at(1).push_back(es_compose::makeBound(450, 250, 100, 20,NL));
		Bounds.at(2).push_back(es_compose::makeBound(450, 250, 100, 20,NL));
		Bounds.at(0).push_back(es_compose::makeBound(450, 250,  30, 20,NL));
		Bounds.at(0).push_back(es_compose::makeBound(550, 250,  30, 20,NR));
			brickAll.push_back(es_compose::makeBrick(450, 750,100, 20, LayerHeight, LayerHeight*3,FL));
			brickAll.push_back(es_compose::makeBrick(450, 750,  30, 20, 0, LayerHeight,  FL));
			brickAll.push_back(es_compose::makeBrick(550, 750,  30, 20, 0, LayerHeight,  FR));
			brickAll.push_back(es_compose::makeBrick(450, 250, 100, 20, LayerHeight, LayerHeight*3,NL));
			brickAll.push_back(es_compose::makeBrick(450, 250,  30, 20, 0, LayerHeight,  NL));
			brickAll.push_back(es_compose::makeBrick(550, 250,  30, 20, 0, LayerHeight,  NR));
		
	// center block
	es_bound abound;
	abound = es_compose::makeBound(375,625,250,250);
		Bounds.at(0).push_back(abound);
		Bounds.at(1).push_back(abound);
		Bounds.at(2).push_back(abound);
			brickAll.push_back(es_compose::makeBrick(abound, 0,LayerHeight*3));

	World->setupMap(Bounds,brickAll,LayerHeight);
}



void es_compose::map_1_respawn(int LayerHeight)
{
		std::vector<es_respawn> Respawn;
		es_respawn tmppoint;
		tmppoint.location.x = 125;
		tmppoint.location.z = 500;
		tmppoint.location.y = 1;
		tmppoint.theta = 270;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 500;
		tmppoint.location.z = 875;
		tmppoint.location.y = 1;
		tmppoint.theta = 0;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 500;
		tmppoint.location.z = 125;
		tmppoint.location.y = 1;
		tmppoint.theta = 180;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 875;
		tmppoint.location.z = 500;
		tmppoint.location.y = 1;
		tmppoint.theta = 90;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 380;
		tmppoint.location.z = 560;
		tmppoint.location.y = 25;
		tmppoint.theta = 215;
		Respawn.push_back(tmppoint);
		tmppoint.location.x = 610;
		tmppoint.location.z = 560;
		tmppoint.location.y = 25;
		tmppoint.theta = 45;
		Respawn.push_back(tmppoint);
Control->setupRespawn(Respawn);
}

void es_compose::map_1_pickup(int LayerHeight)
{
	std::list<es_pickup> PickupList;

	es_pickup tmp;
	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 100;
	tmp.location.y = 4;
	tmp.location.z = 900;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = SLIME;
	tmp.amount = 10;
	tmp.location.x = 900;
	tmp.location.y = 4;
	tmp.location.z = 100;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 900;
	tmp.location.y = 4;
	tmp.location.z = 900;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = ENERGY;
	tmp.amount = 40;
	tmp.location.x = 100;
	tmp.location.y = 4;
	tmp.location.z = 100;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = FIRE;
	tmp.amount = 150;
	tmp.location.x = 500;
	tmp.location.y = 28;
	tmp.location.z = 500;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 500;
	tmp.location.y = 28;
	tmp.location.z = 760;
	PickupList.push_back(tmp);

	tmp.timer=0;
	tmp.type = BOMB;
	tmp.amount = 10;
	tmp.location.x = 500;
	tmp.location.y = 28;
	tmp.location.z = 240;
	PickupList.push_back(tmp);

Pickup->setupPickup(PickupList);
}

void es_compose::calcOuterBound(std::vector< std::vector <es_bound> > &boundList, unsigned int ax, unsigned int az, unsigned int aLevels)
{
	es_bound west,east,north,south;
        west.cor1.x = -20-2;
        west.cor2.x = 2;
        west.cor1.z = -2;
        west.cor2.z = az+2;
        east.cor1.x = ax-2;
        east.cor2.x = ax+20+2;
        east.cor1.z = 0-2;
        east.cor2.z = az+2;

        north.cor1.x = 0-2;
        north.cor2.x = ax+2;
        north.cor1.z = -20-2;
        north.cor2.z = 0+2;
        south.cor1.x = 0-2;
        south.cor2.x = ax+2;
        south.cor1.z = az-2;
        south.cor2.z = az+20+2;

	for(unsigned int ii=0;ii<aLevels;ii++)
	{
	std::vector<es_bound> tmpbound;
	tmpbound.push_back(north);
	tmpbound.push_back(east);
	tmpbound.push_back(south);
	tmpbound.push_back(west);
	boundList.push_back(tmpbound);
	}
}

es_bound es_compose::makeBound(es_brick& abrick)
{
es_bound Bound;

Bound.cor1.x = abrick.cor1.x-2;
Bound.cor2.x = abrick.cor2.x+2;
Bound.cor1.z = abrick.cor1.z-2;
Bound.cor2.z = abrick.cor2.z+2;
return Bound;
}
es_brick es_compose::makeBrick(es_bound& abound,int y1, int y2,float ar,float ag,float ab)
{
es_brick Brick;

Brick.cor1.x = abound.cor1.x+2;
Brick.cor2.x = abound.cor2.x-2;
Brick.cor1.z = abound.cor1.z+2;
Brick.cor2.z = abound.cor2.z-2;
Brick.cor1.y = y1;
Brick.cor2.y = y2;
Brick.topColor[0] = ar;
Brick.topColor[1] = ag;
Brick.topColor[2] = ab;
return Brick;
}
es_bound es_compose::makeBound(int x, int z, unsigned int xl, unsigned int zl, CORNER Corner)
{

// Boundary for Collision Detection
es_bound Bound;
if(Corner == NL)
{	Bound.cor1.x = x;
        Bound.cor2.x = x+xl;
        Bound.cor1.z = z-zl;
        Bound.cor2.z = z;
}else if(Corner == NR)
{	Bound.cor1.x = x-xl;
        Bound.cor2.x = x;
        Bound.cor1.z = z-zl;
        Bound.cor2.z = z;
}else if(Corner == FR)
{	Bound.cor1.x = x-xl;
        Bound.cor2.x = x;
        Bound.cor1.z = z;
        Bound.cor2.z = z+zl;
}else if(Corner == FL)
{	Bound.cor1.x = x;
        Bound.cor2.x = x+xl;
        Bound.cor1.z = z;
        Bound.cor2.z = z+zl;
}
Bound.cor1.x += -2;
Bound.cor2.x += +2;
Bound.cor1.z += -2;
Bound.cor2.z += +2;

return Bound;
}

es_brick es_compose::makeBrick(int x, int z, unsigned int xl, unsigned int zl, int y1, int y2 , CORNER Corner,float ar,float ag,float ab)
{

// HOW IT LOOKS
es_brick Brick;
if(Corner == NL)
{	Brick.cor1.x = x;
        Brick.cor2.x = x+xl;
        Brick.cor1.z = z-zl;
        Brick.cor2.z = z;
}else if(Corner == NR)
{	Brick.cor1.x = x-xl;
        Brick.cor2.x = x;
        Brick.cor1.z = z-zl;
        Brick.cor2.z = z;
}else if(Corner == FR)
{	Brick.cor1.x = x-xl;
        Brick.cor2.x = x;
        Brick.cor1.z = z;
        Brick.cor2.z = z+zl;
}else if(Corner == FL)
{	Brick.cor1.x = x;
        Brick.cor2.x = x+xl;
        Brick.cor1.z = z;
        Brick.cor2.z = z+zl;
}
        Brick.cor1.x += 2;
        Brick.cor2.x += -2;
        Brick.cor1.z += 2;
        Brick.cor2.z += -2;
Brick.cor1.y = y1;
Brick.cor2.y = y2;

Brick.topColor[0] = ar;
Brick.topColor[1] = ag;
Brick.topColor[2] = ab;
return Brick;
}

/*
void es_compose::map_3(int LayerHeight){
        std::vector< std::vector<es_bound> > Bounds;
        std::vector<es_brick> brickAll;

                calcOuterBound(Bounds,1000,1000,20);
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(0),0,LayerHeight*4));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(1),0,LayerHeight*4));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(2),0,LayerHeight*4));
                        brickAll.push_back(es_compose::makeBrick(Bounds.at(0).at(3),0,LayerHeight*4));

        es_bound abound;
        abound = es_compose::makeBound(440,430,120,30,NL);
                Bounds.at(0).push_back(abound);
                        brickAll.push_back(es_compose::makeBrick(abound,0,LayerHeight));

        World->setupMap(Bounds,brickAll,LayerHeight);
}
void es_compose::map_3_respawn(int LayerHeight){
                std::vector<es_respawn> Respawn;
                es_respawn tmppoint;
                tmppoint.location.x = 650;
                tmppoint.location.z = 500;
                tmppoint.location.y = 1;
                tmppoint.theta = 90;
                Respawn.push_back(tmppoint);
Control->setupRespawn(Respawn);
}
void es_compose::map_3_pickup(int LayerHeight){

}
void es_compose::map_3_enemies(int LayerHeight){


}

*/
//
