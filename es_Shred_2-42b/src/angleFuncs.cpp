#include "angleFuncs.h"

	float ang::makeAngle(float aan)
	{
	if(aan<-PI)
	return aan+=WHOLEPI;
	else if(aan>PI)
	return aan-=WHOLEPI;
	return aan;
	}

	bool ang::angleWithin(float &angle ,float &aa, float &bb){
	if(aa<bb)
	return (angle > aa && angle < bb);
	else
	return (angle > aa || angle < bb);
	}