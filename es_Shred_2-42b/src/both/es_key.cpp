

#include "es_key.h"
#include "es_avatar.h"
#include "es_weapons.h"
#include <iostream>

es_key::es_key()
{
canMove=1;
}

void es_key::setVars(es_avatar* avat, es_weapons* aweap){
Avatar=avat;
Weapons=aweap;
}
/*
void es_key::setWeapons(es_weapons *aweap){
Weapons = aweap;
}
void es_key::setAvatar(es_avatar *anav){
Avatar = anav;
}*/


void es_key::enableMove(bool abool){
		canMove=abool;
		Avatar->move.left = 0;
		Avatar->move.right = 0;
		Avatar->move.up = 0;
		Avatar->move.down = 0;
		Avatar->move.jump = 0;
		Avatar->move.crouch = 0;
		Avatar->move.turnleft = 0;
		Avatar->move.turnright = 0;
		Weapons->offFire();
	//	Weapons->throwDone();
}
void es_key::press(QKeyEvent* keyevent)
{

if(canMove ==1)
{
	switch(keyevent->key())
	{
	case Qt::Key_W:
		Avatar->move.left = 1;
		break;
	case Qt::Key_R:
		Avatar->move.right = 1;
		break;
	case Qt::Key_E:
		Avatar->move.up = 1;
		break;
	case Qt::Key_D:
		Avatar->move.down = 1;
		break;
	case Qt::Key_Space:
		Avatar->move.jump = 1;
		break;
	case Qt::Key_I:
		Avatar->onBoost();
		break;
		
	case Qt::Key_S:
		Avatar->move.turnleft = 1;
		break;
	case Qt::Key_F:
		Avatar->move.turnright = 1;
		break;

	case Qt::Key_N:
		Weapons->onFire();
		break;
	case Qt::Key_J:
		if(! keyevent->isAutoRepeat())
		Weapons->addEnergy();
		break;
	case Qt::Key_H:
		if(! keyevent->isAutoRepeat())
		Weapons->addSlime();
		break;
	case Qt::Key_L:
		Weapons->addBomb();
		break;
	case Qt::Key_K:
		Weapons->startThrow();
		break;
		
		
	case Qt::Key_Right:
		Avatar->move.turnright = 1;
		break;
	case Qt::Key_Left:
		Avatar->move.turnleft = 1;
		break;
	case Qt::Key_Up:
		Avatar->move.up = 1;
		break;
	case Qt::Key_Down:
		Avatar->move.down = 1;
		break;
	}
}
}

void es_key::release(QKeyEvent* keyevent)
{
if(canMove==1)
{	if(! keyevent->isAutoRepeat())
	{
		switch(keyevent->key())
		{
		
		case Qt::Key_W:
			Avatar->move.left = 0;
			break;
		case Qt::Key_R:
			Avatar->move.right = 0;
			break;
		case Qt::Key_E:
			Avatar->move.up = 0;
			break;
		case Qt::Key_D:
			Avatar->move.down = 0;
			break;
		case Qt::Key_Space:
			Avatar->move.jump = 0;
			break;
	//	case Qt::Key_J:
	//		Avatar->move.crouch = 0;
	//		break;
		case Qt::Key_I:
			Avatar->offBoost();
			break;
		case Qt::Key_S:
			Avatar->move.turnleft = 0;
			break;
		
		case Qt::Key_F:
			Avatar->move.turnright = 0;
			break;
			
		case Qt::Key_N:
			Weapons->offFire();
			break;
		case Qt::Key_K:
			Weapons->finishThrow();
			break;

		case Qt::Key_Right:
			Avatar->move.turnright = 0;
			break;
		case Qt::Key_Left:
			Avatar->move.turnleft = 0;
			break;
		case Qt::Key_Up:
			Avatar->move.up = 0;
			break;
		case Qt::Key_Down:
			Avatar->move.down = 0;
			break;
		}
	}
}
}
