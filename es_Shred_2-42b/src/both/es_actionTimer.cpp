

#include "es_actionTimer.h"
#include "es_avatar.h"
#include "es_weapons.h"
#include "es_pickupcon.h"
#include "es_world.h"
#include "es_collision.h"
#include "es_qtgl.h"
#include "es_enemies.h"
#include <QTimer>
#include <iostream>

es_actionTimer::es_actionTimer(bool ism){
isMulti=ism;
Status=0;
Timer = new QTimer(this);
connect(Timer, SIGNAL(timeout()), this, SLOT(doAction()));
}
void es_actionTimer::setVars(es_avatar* anav,es_weapons *aweap,es_pickupcon* apick,es_world* aworld,es_qtgl *aqt, es_collision* acol,es_enemies* enem)
{
Avatar=anav;
Weapons=aweap;
Pickup=apick;
World=aworld;
Es_qtgl=aqt;
Collision=acol;
Enemies=enem;
}

void es_actionTimer::doAction()
{
if(Status ==0)
	{
	Status=1;
	Avatar->action();
	Weapons->action();
	Pickup->action();
	Collision->action();
	if(isMulti==0)
	Enemies->action();
	Es_qtgl->updateGL();
	Status=0;
	}
else
std::cout<<"es_Warning: Actions did not complete within doAction before it was called again!!"<<std::endl;


}

void es_actionTimer::startTimer()
{
// SET doAction() TO BE CALLED ON A TIMER	
	Timer->start(12);
}
void es_actionTimer::stopTimer()
{
	Timer->stop();
}
