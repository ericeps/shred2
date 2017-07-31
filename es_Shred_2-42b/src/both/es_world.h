/* Contains walls/items present in world,
    and code to test for collision with them.

 */

#ifndef ES_WORLD_H
#define ES_WORLD_H

#include "defs.h"
#include <vector>
#include <list>
//class es_avatar;

class es_world
{
friend class es_draw;

public:
// STARTUP CALIBRATION
	es_world();
//	void setAvatar(es_avatar *);
	void setupMap(std::vector< std::vector<es_bound> >&,std::vector<es_brick>&, int);

	int getQuad(point2f &p1);
	point2f bestPath(point2f &p1, point2f &p2);
	bool isWallBetween(point2f &p1,point2f &p2,std::vector<int> &slayers);
	bool isClear(point3f&) const;
	bool isClear_layer(point3f &apoint, float alayer) const;
	bool isClear(es_ship4&) const;
	bool isClear_layer(es_ship4&, float) const;
	bool isClear_Report( es_ship4&);
	int getLevel(float ay);
	es_collision_report CollisionReport;

	int Max_Height;
	int Layer_Height;

private:


	std::vector< std::vector<es_bound> > Bounds;
	std::vector<es_brick> Bricks;

	int tmpiibound;
	int tmpiilevel;

//	point3f camPos;

//	es_avatar *Avatar;
};

#endif
