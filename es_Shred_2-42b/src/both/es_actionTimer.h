/* Main game loop.

 */

#ifndef ES_ACTION_H
#define ES_ACTION_H
#include "defs.h"
#include <QObject>

class QTimer;
class es_avatar;
class es_weapons;
class es_world;
class es_pickupcon;
class es_collision;
class es_qtgl;
class es_enemies;

class es_actionTimer : public QObject
{
	Q_OBJECT
public:
es_actionTimer(bool);
void startTimer();
void stopTimer();

void setVars(es_avatar* anav,es_weapons *aweap,es_pickupcon* apick,es_world* aworld,es_qtgl *aqt, es_collision* acol,es_enemies *anem=0);

private:
	QTimer *Timer;
	es_avatar *Avatar;
	es_weapons *Weapons;
	es_pickupcon *Pickup;
	es_world *World;
	es_collision *Collision;
	es_enemies *Enemies;
	es_qtgl *Es_qtgl;
bool Status;
bool isMulti;
private slots:
void doAction();


};


#endif
