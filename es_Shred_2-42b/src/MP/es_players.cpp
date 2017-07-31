#include "es_players.h"
#include <list>
#include <iostream>
#include <cmath>
#include <iostream>

void es_players::addEnemies(std::list<unsigned char> &oplist)
{
	std::list<unsigned char>::iterator ii;
	for(ii=oplist.begin();ii!=oplist.end();ii++)
	{
	es_netship tmp;
	es_ship4 aShip;
	tmp.ID = *ii;
	tmp.Ship = aShip;
	tmp.colorIndex = tmp.ID % 10;
	PlayerShips.push_back(tmp);
	std::cout<<"Enemy"<<std::endl;
	}

}
/*void es_players::addIDShip(unsigned char anID, es_ship4 &aShip)
{
	es_netship tmp;
	tmp.ID = anID;
	tmp.Ship = aShip;
	PlayerShips.push_back(tmp);
	
std::cout<<"new ship ID == "<<anID<<std::endl;
}*/

void es_players::updateNetShip(unsigned char anID, es_ship4 &aShip, int atheta, float ahealth,int asidetilt,int aheadtilt)
{

	std::vector< es_netship >::iterator iid;
	for(iid=PlayerShips.begin(); iid!=PlayerShips.end(); iid++)
	{
		if (iid->ID == anID)
		{
		iid->Ship = aShip;
		iid->Theta = atheta;
		iid->Health = ahealth;
		iid->sideTilt = asidetilt;
		iid->headTilt = aheadtilt;
		if(ahealth >0)
			iid->custom = 0;
		break;
		}
	}
}


bool es_players::isWithin(point3f &apoint, int arad)
{
	float tmpx,tmpy,tmpz;
	std::vector< es_netship >::iterator iid;
	for(iid=PlayerShips.begin(); iid!=PlayerShips.end(); iid++)
	{
			tmpx = fabs(apoint.x - iid->Ship.Center.x);
			tmpz = fabs(apoint.z - iid->Ship.Center.z);
			tmpy = fabs(apoint.y - iid->Ship.Center.y);
		if(tmpx < 50 && tmpz < 50 && tmpy < 50)
		{
//			tmpx = fabs(apoint.x - iid->Ship.Center.x);
//			tmpz = fabs(apoint.z - iid->Ship.Center.z);
//			tmpy = fabs(apoint.y - iid->Ship.Center.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
			tmpx = fabs(apoint.x - iid->Ship.Front.x);
			tmpz = fabs(apoint.z - iid->Ship.Front.z);
			tmpy = fabs(apoint.y - iid->Ship.Front.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
			tmpx = fabs(apoint.x - iid->Ship.Back.x);
			tmpz = fabs(apoint.z - iid->Ship.Back.z);
			tmpy = fabs(apoint.y - iid->Ship.Back.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
			tmpx = fabs(apoint.x - iid->Ship.Left.x);
			tmpz = fabs(apoint.z - iid->Ship.Left.z);
			tmpy = fabs(apoint.y - iid->Ship.Left.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
			tmpx = fabs(apoint.x - iid->Ship.Right.x);
			tmpz = fabs(apoint.z - iid->Ship.Right.z);
			tmpy = fabs(apoint.y - iid->Ship.Right.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
			tmpx = fabs(apoint.x - iid->Ship.C2.x);
			tmpz = fabs(apoint.z - iid->Ship.C2.z);
			tmpy = fabs(apoint.y - iid->Ship.C2.y);
			if(tmpx < arad && tmpz < arad && tmpy < arad)
			return 1;
		}
	}

return 0;
}