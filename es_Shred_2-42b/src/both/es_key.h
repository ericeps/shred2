/* Keypresses are processed in this class.
 */

#ifndef ES_KEY_H
#define ES_KEY_H

#include <QKeyEvent>

class es_weapons;
class es_avatar;

class es_key
{
public:
es_key();
void setVars(es_avatar* avat, es_weapons* aweap);
//void setWeapons(es_weapons*);
//void setAvatar(es_avatar*);

void enableMove(bool);
void press(QKeyEvent* keyevent);
void release(QKeyEvent* keyevent);

private:
	es_weapons *Weapons;
	es_avatar *Avatar;
	bool canMove;

};

#endif
