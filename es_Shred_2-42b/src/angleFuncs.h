/* Functions dealing with angles.

 */

#ifndef ANGLEFUNCS
#define ANGLEFUNCS

namespace ang
{
	const double WHOLEPI = 6.28318530718;
	const double PI = 3.1415926536;
	float makeAngle(float aan);
	bool angleWithin(float &angle ,float &aa, float &bb);
};
#endif
