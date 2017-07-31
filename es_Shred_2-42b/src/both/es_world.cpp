

#include "defs.h"
#include "es_world.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "es_avatar.h"
//#include "es_compose.h"
#include <algorithm>
#include <cmath>
#include <iostream>

es_world::es_world()
{
//camPos.x = 0;
//camPos.y = 50;
//camPos.z = 100;
}


//void es_world::setAvatar(es_avatar *anav){
//Avatar = anav;
//}
int es_world::getQuad(point2f &p1)
{

		if( p1.x < Bounds[tmpiilevel].at(tmpiibound).cor1.x)
		{
			if( p1.z < Bounds[tmpiilevel].at(tmpiibound).cor1.z )
			{
				// 1
				return 1;
			}
			else if( p1.z < Bounds[tmpiilevel].at(tmpiibound).cor2.z )
			{
				// 2
				return 2;
			}
			else
			{
				// 3
				return 3;
			}
		}
		else
		if( p1.x < Bounds[tmpiilevel].at(tmpiibound).cor2.x )
		{	if( p1.z > Bounds[tmpiilevel].at(tmpiibound).cor2.z )
			{
				// 4
				return 4;
			}
			else// if( p1.z < Bounds[tmpiilevel].at(tmpiibound).cor1.z )
			{
				// 5
				return 5;
			}
		}
		else
		{	if(p1.z > Bounds[tmpiilevel].at(tmpiibound).cor2.z )
			{		
				// 6
				return 6;
			}
			else if(p1.z > Bounds[tmpiilevel].at(tmpiibound).cor1.z)
			{
				// 7
				return 7;
			}
			else
			{
				// 8
				return 8;
			}
		}
}

point2f es_world::bestPath(point2f &p1, point2f &p2)
{
	int q1=getQuad(p1);
	int q2=getQuad(p2);
	point2f tmp;
	// if p2 is on a brick, within its x and z coordinates.
	if(p2.x > Bounds[tmpiilevel].at(tmpiibound).cor1.x && p2.x < Bounds[tmpiilevel].at(tmpiibound).cor2.x && p2.z > Bounds[tmpiilevel].at(tmpiibound).cor1.z && p2.z < Bounds[tmpiilevel].at(tmpiibound).cor2.z)
	{
	tmp.x = p1.x;
	tmp.z = p1.z;
	return tmp;
	}
	else
	if(q1==1)
	{
		if(q2==4)
		{

			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==7)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==6)
		{
		// more calc needed
			float bratio = (((Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x)/2)-p1.x)/(((Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z)/2)-p1.z);
			float pratio = (p2.x-p1.x)/(p2.z-p1.z);
			if(pratio>bratio)
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
			else
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
		}
	}
	else if(q1==2)
	{
		if(q2==4 || q2==6)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==5 || q2==8)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==7)
		{
		// more calc needed
			if( 1 > ((p2.z - Bounds[tmpiilevel].at(tmpiibound).cor1.z) + (p1.z - Bounds[tmpiilevel].at(tmpiibound).cor1.z))/(Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z))
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
			else
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
		}
	}
	else if(q1==3)
	{
		if(q2==7)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==5)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==8)
		{
		// more calc needed
			float bratio = (((Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x)/2)-p1.x)/(p1.z-((Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z)/2));
			float pratio = (p2.x-p1.x)/(p1.z-p2.z);
			if(pratio>bratio)
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
			else
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
		}
	}
	else if(q1==4)
	{
		if(q2==7 || q2==8)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==2 || q2==1)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==5)
		{
		// more calc needed
			if( 1 > ((p2.x - Bounds[tmpiilevel].at(tmpiibound).cor1.x) + (p1.x - Bounds[tmpiilevel].at(tmpiibound).cor1.x))/(Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x))
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
			else
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
		}
	}
	else if(q1==5)
	{
		if(q2==2 || q2==3)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==7 || q2==6)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==4)
		{
		// more calc needed
			if( 1 > ((p2.x - Bounds[tmpiilevel].at(tmpiibound).cor1.x) + (p1.x - Bounds[tmpiilevel].at(tmpiibound).cor1.x))/(Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x))
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
			else
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
		}
	}
	else if(q1==6)
	{
		if(q2==5)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==2)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==1)
		{
		// more calc needed
			float bratio = (p1.x-((Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x)/2))/(p1.z-((Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z)/2));
			float pratio = (p1.x-p2.x)/(p1.z-p2.z);
			if(pratio>bratio)
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
			else
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
		}
	}
	else if(q1==7)
	{
		if(q2==5 || q2==1)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==4 || q2==3)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==2)
		{
		// more calc needed
			if( 1 > ((p2.z - Bounds[tmpiilevel].at(tmpiibound).cor1.z) + (p1.z - Bounds[tmpiilevel].at(tmpiibound).cor1.z))/(Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z))
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
			else
			{	tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
		}
	}
	else if(q1==8)
	{
		if(q2==2)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
		}
		else if(q2==4)
		{
			tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
			tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
		}
		else if(q2==3)
		{
		// more calc needed
			float bratio = (p1.x-((Bounds[tmpiilevel].at(tmpiibound).cor2.x-Bounds[tmpiilevel].at(tmpiibound).cor1.x)/2))/(((Bounds[tmpiilevel].at(tmpiibound).cor2.z-Bounds[tmpiilevel].at(tmpiibound).cor1.z)/2)-p1.z);
			float pratio = (p1.x-p2.x)/(p2.z-p1.z);
			if(pratio>bratio)
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor1.x-2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor1.z-2;
			}
			else
			{
				tmp.x = Bounds[tmpiilevel].at(tmpiibound).cor2.x+2;
				tmp.z = Bounds[tmpiilevel].at(tmpiibound).cor2.z+2;
			}
		}
	}
return tmp;
}




bool es_world::isWallBetween(point2f &p1,point2f &p2,std::vector<int> &slayers)
{
	int ibound;
point2f c1,c2;
bool canBe;
float a1,a2,a3;
int ilay=0;
for(ilay; ilay!=slayers.size(); ilay++)
{
	ibound = 0;
	while(ibound != Bounds[ilay].size())
	{	canBe=0;
		if( p1.x < Bounds[ilay].at(ibound).cor1.x)
		{
			if( p1.z < Bounds[ilay].at(ibound).cor1.z )
			{
				c1.x=Bounds[ilay].at(ibound).cor2.x;		// 1
				c1.z=Bounds[ilay].at(ibound).cor1.z;
				c2.x=Bounds[ilay].at(ibound).cor1.x;
				c2.z=Bounds[ilay].at(ibound).cor2.z;
				
				if(p2.x > Bounds[ilay].at(ibound).cor1.x && p2.z > Bounds[ilay].at(ibound).cor1.z)
				canBe=1;
			}
			else if( p1.z < Bounds[ilay].at(ibound).cor2.z )
			{
				c1.x=Bounds[ilay].at(ibound).cor1.x;		// 2
				c1.z=Bounds[ilay].at(ibound).cor1.z;
				c2.x=Bounds[ilay].at(ibound).cor1.x;
				c2.z=Bounds[ilay].at(ibound).cor2.z;
				
				if(p2.x > Bounds[ilay].at(ibound).cor1.x)
				canBe=1;
			}
			else
			{
				c1.x=Bounds[ilay].at(ibound).cor1.x;		// 3
				c1.z=Bounds[ilay].at(ibound).cor1.z;
				c2.x=Bounds[ilay].at(ibound).cor2.x;
				c2.z=Bounds[ilay].at(ibound).cor2.z;
				
				if(p2.x > Bounds[ilay].at(ibound).cor1.x && p2.z < Bounds[ilay].at(ibound).cor2.z)
				canBe=1;
			}
		}
		else
		if( p1.x < Bounds[ilay].at(ibound).cor2.x )
		{	if( p1.z > Bounds[ilay].at(ibound).cor2.z )
			{
				c1.x=Bounds[ilay].at(ibound).cor1.x;		// 4
				c1.z=Bounds[ilay].at(ibound).cor2.z;
				c2.x=Bounds[ilay].at(ibound).cor2.x;
				c2.z=Bounds[ilay].at(ibound).cor2.z;
				
				if(p2.z < Bounds[ilay].at(ibound).cor2.z)
				canBe=1;
			}
			else
			{
				c1.x=Bounds[ilay].at(ibound).cor2.x;		// 5
				c1.z=Bounds[ilay].at(ibound).cor1.z;
				c2.x=Bounds[ilay].at(ibound).cor1.x;
				c2.z=Bounds[ilay].at(ibound).cor1.z;
				
				if(p2.z > Bounds[ilay].at(ibound).cor1.z)
				canBe=1;
			}
		}
		else
		{	if(p1.z > Bounds[ilay].at(ibound).cor2.z )
			{		
				c1.x=Bounds[ilay].at(ibound).cor1.x;		// 6
				c1.z=Bounds[ilay].at(ibound).cor2.z;
				c2.x=Bounds[ilay].at(ibound).cor2.x;
				c2.z=Bounds[ilay].at(ibound).cor1.z;
				
				if(p2.x < Bounds[ilay].at(ibound).cor2.x && p2.z < Bounds[ilay].at(ibound).cor2.z)
				canBe=1;
			}
			else if(p1.z > Bounds[ilay].at(ibound).cor1.z)
			{
				c1.x=Bounds[ilay].at(ibound).cor2.x;		// 7
				c1.z=Bounds[ilay].at(ibound).cor2.z;
				c2.x=Bounds[ilay].at(ibound).cor2.x;
				c2.z=Bounds[ilay].at(ibound).cor1.z;
				
				if(p2.x < Bounds[ilay].at(ibound).cor2.x)
				canBe=1;
			}
			else
			{
				c1.x=Bounds[ilay].at(ibound).cor2.x;		// 8
				c1.z=Bounds[ilay].at(ibound).cor2.z;
				c2.x=Bounds[ilay].at(ibound).cor1.x;
				c2.z=Bounds[ilay].at(ibound).cor1.z;
				
				if(p2.x < Bounds[ilay].at(ibound).cor2.x && p2.z > Bounds[ilay].at(ibound).cor1.z)
				canBe=1;
			}
		}
		c1.x-=p1.x;
		c1.z-=p1.z;
		c2.x-=p1.x;
		c2.z-=p1.z;
		
		a1 = atan2(c1.z,c1.x);
		a2 = atan2(c2.z,c2.x);
		a3 = atan2((p2.z-p1.z),(p2.x-p1.x));
		if(a1 < a2)
		{	if( a3>a1 && a3<a2 && canBe )
			{tmpiibound=ibound;
			tmpiilevel=ilay;
			return 1;
			}
		}
		else
		{	if((a3>a1 || a3<a2) && canBe)
			{tmpiibound=ibound;
			tmpiilevel=ilay;
			return 1;
			}
		}
	++ibound;
	}	//while
}
return 0;
}
bool es_world::isClear(point3f &apoint) const
{
	if(apoint.y <0)
	return 0;
	else if(apoint.y >Max_Height)		// if "apoint" is greater than max_height, will always return true
	return 1;
//	if( apoint.x<0 || apoint.x > Width || apoint.z < 0 || apoint >Depth )
//	return 0;
	
	int Level = apoint.y/Layer_Height;
	std::vector<es_bound>::const_iterator ibound;
	ibound = Bounds[Level].begin();

	while(ibound != Bounds[Level].end())
	{
		if(	(ibound->cor1.x <=apoint.x && apoint.x <=ibound->cor2.x)
		&&	(ibound->cor1.z <=apoint.z && apoint.z <=ibound->cor2.z))
			return 0;
		else
		++ibound;
	}
	return 1;
}

bool es_world::isClear_layer(point3f &apoint, float alayer) const
{
	if(alayer <0 )
	return 0;
	else if(apoint.y >Max_Height)		// if "apoint" is greater than max_height, will always return true
	return 1;
//	if( apoint.x<0 || apoint.x > Width || apoint.z < 0 || apoint >Depth )
//	return 0;
	
	int Level = alayer/Layer_Height;
	std::vector<es_bound>::const_iterator ibound;
	ibound = Bounds[Level].begin();

	while(ibound != Bounds[Level].end())
	{
					if(		(ibound->cor1.x <=apoint.x  &&  apoint.x <=ibound->cor2.x)
						&&	(ibound->cor1.z <=apoint.z  &&  apoint.z <=ibound->cor2.z))
					{	return 0;
					}
					else
					++ibound;
	}
	return 1;
}

int es_world::getLevel(float ay){
return ay/Layer_Height;
}

bool es_world::isClear(es_ship4 &aship) const
{
	if(aship.Center.y <0 || aship.Center.y > Max_Height)
	return 0;
	int Level = aship.Center.y/Layer_Height;
	std::vector<es_bound>::const_iterator ibound;
	ibound = Bounds[Level].begin();
//	if( apoint.x<0 || apoint.x > Width || apoint.z < 0 || apoint >Depth )
//	return 0;
	
	while(ibound != Bounds[Level].end())
	{
				if(		(ibound->cor1.x <=aship.Front.x  &&  aship.Front.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Front.z  &&  aship.Front.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Back.x  &&  aship.Back.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Back.z  &&  aship.Back.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Left.x  &&  aship.Left.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Left.z  &&  aship.Left.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Right.x  &&  aship.Right.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Right.z  &&  aship.Right.z <=ibound->cor2.z))
				{	return 0;
				}
				else
				++ibound;
	}
	return 1;
}

bool es_world::isClear_layer(es_ship4 &aship, float alayer) const
{
	if(alayer <0 || alayer > Max_Height)
	return 0;
	int Level = alayer/Layer_Height;
	std::vector<es_bound>::const_iterator ibound;
	ibound = Bounds[Level].begin();
//	if( apoint.x<0 || apoint.x > Width || apoint.z < 0 || apoint >Depth )
//	return 0;
	
	while(ibound != Bounds[Level].end())
	{
				if(		(ibound->cor1.x <=aship.Front.x  &&  aship.Front.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Front.z  &&  aship.Front.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Back.x  &&  aship.Back.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Back.z  &&  aship.Back.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Left.x  &&  aship.Left.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Left.z  &&  aship.Left.z <=ibound->cor2.z))
				{	return 0;
				}
				else if((ibound->cor1.x <=aship.Right.x  &&  aship.Right.x <=ibound->cor2.x)
					&&	(ibound->cor1.z <=aship.Right.z  &&  aship.Right.z <=ibound->cor2.z))
				{	return 0;
				}
				else
				++ibound;
	}
	return 1;
}


bool es_world::isClear_Report( es_ship4 &aship)
{
	if(aship.Center.y < 0)
	{	CollisionReport.Wall_Side = Y1;
		return 0;
	}
	else if(aship.Center.y > Max_Height)
	{	CollisionReport.Wall_Side = Y2;
		return 0;
	}
	
	int Level = aship.Center.y/Layer_Height;
	std::vector<es_bound>::const_iterator ibound;
	ibound = Bounds[Level].begin();

	while(ibound != Bounds[Level].end())
	{
				if(			(ibound->cor1.x <=aship.Front.x  &&  aship.Front.x <=ibound->cor2.x)
					&&		(ibound->cor1.z <=aship.Front.z  &&  aship.Front.z <=ibound->cor2.z))
				{//	collisionDetail(ibound, aship, FRONT);
					CollisionReport.Avatar_Side = FRONT;
					CollisionReport.BoundPtr = ibound;
					return 0;
				}
				else if(	(ibound->cor1.x <=aship.Back.x  &&  aship.Back.x <=ibound->cor2.x)
					&&		(ibound->cor1.z <=aship.Back.z  &&  aship.Back.z <=ibound->cor2.z))
				{//	collisionDetail(ibound, aship, BACK);
					CollisionReport.Avatar_Side = BACK;
					CollisionReport.BoundPtr = ibound;
					return 0;
				}
				else if(	(ibound->cor1.x <=aship.Left.x  &&  aship.Left.x <=ibound->cor2.x)
					&&		(ibound->cor1.z <=aship.Left.z  &&  aship.Left.z <=ibound->cor2.z))
				{//	collisionDetail(ibound, aship, LEFT);
					CollisionReport.Avatar_Side = LEFT;
					CollisionReport.BoundPtr = ibound;
					return 0;
				}
				else if(	(ibound->cor1.x <=aship.Right.x  &&  aship.Right.x <=ibound->cor2.x)
					&&		(ibound->cor1.z <=aship.Right.z  &&  aship.Right.z <=ibound->cor2.z))
				{//	collisionDetail(ibound, aship, RIGHT);
					CollisionReport.Avatar_Side = RIGHT;
					CollisionReport.BoundPtr = ibound;
					return 0;
				}
				else
				++ibound;
	}
	return 1;
}

/*
void es_world::collisionDetail(std::vector<es_bound>::const_iterator ibound, es_ship4 &aship, ES_SHIP_SIDE sidehit)
{
	int ghostLevel,avatarLevel;
	ghostLevel = aship.Center.y / Layer_Height;
	avatarLevel= Avatar->Center().y / Layer_Height;
	point3f *shipSidePtr;


	CollisionReport.Avatar_Side = sidehit;

	if(sidehit == FRONT)
		shipSidePtr = &aship.Front;
	else if(sidehit == BACK)
		shipSidePtr = &aship.Back;
	else if(sidehit == LEFT)
		shipSidePtr = &aship.Left;
	else if(sidehit == RIGHT)
		shipSidePtr = &aship.Right;


		if(isClear_layer(aship, Avatar->Center().y))
		{										
			if(ghostLevel > avatarLevel)
			CollisionReport.Wall_Side=Y1;
			else
			CollisionReport.Wall_Side=Y2;
		}
		else

		{
			// Calculate distances to x and z boundaries
					float x1dist,x2dist,z1dist,z2dist;
				x1dist = shipSidePtr->x - ibound->cor1.x;
				x2dist = ibound->cor2.x - shipSidePtr->x;
				z1dist = shipSidePtr->z - ibound->cor1.z;
				z2dist = ibound->cor2.z - shipSidePtr->z;

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
				{CollisionReport.Wall_Side=X1;
				}
				else if (distvector[0] == x2dist)
				{CollisionReport.Wall_Side=X2;
				}
				else if (distvector[0] == z1dist)
				{CollisionReport.Wall_Side=Z1;
				}
				else if (distvector[0] == z2dist)
				{CollisionReport.Wall_Side=Z2;
				}
		}
//std::cout<<"\nCollide..."<<CollisionReport.Wall_Side<<std::endl;
}
*/


void es_world::setupMap(std::vector< std::vector<es_bound> > &abound, std::vector<es_brick> &abrick, int aLayerHeight)
{
	Bounds = abound;
	Bricks = abrick;
	Layer_Height = aLayerHeight;
	Max_Height = (aLayerHeight* Bounds.size()) - 1;
}
