#include "es_net.h"
#include "defs.h"
#include "es_weapons.h"
#include <iostream>
#include "es_client.h"
#include "es_weapons.h"
#include "es_players.h"
#include "es_MPgame.h"


#define DELIM 1

es_net::es_net(es_MPgame *agame)
	{GameInfo = agame;
	}

void es_net::setClient(es_client *aclient){
	Client = aclient;
	}

void es_net::setWeapons(es_weapons* aweap){
	Weapons = aweap;
	}
//void es_net::setAvatar(es_client *anav){
//	Avatar = anav;
//	}

void es_net::setPlayers(es_players* aplay){
	Players = aplay;
	}

//void es_net::action(){
//sendShip(Avatar->Ship, Avatar->Theta, Avatar->Health, Avatar->sideTilt, Avatar->headTilt);
//}

void es_net::processDatagram(QByteArray &datagram)
	{
		if('a' == datagram.at(1) )
			readWeapon(datagram);
		else if('z' == datagram.at(1))
			readShip(datagram);
		else
			std::cout<<"Unrecognized datagram!"<<std::endl;
	}


void es_net::readShip(QByteArray &datagram)
	{	QList<QByteArray> dataList = datagram.split(',');
		es_ship4 tmpShip;
		int aID,atheta,sideTilt,headTilt;
		float ahealth;
		aID = dataList.at(1).toInt();
//std::cout<<"recID "<<aID<<std::endl;
		tmpShip.Center.x = dataList.at(2).toFloat();
		tmpShip.Center.y = dataList.at(3).toFloat();
		tmpShip.Center.z = dataList.at(4).toFloat();
		tmpShip.Front.x = dataList.at(5).toFloat();
		tmpShip.Front.y = dataList.at(6).toFloat();
		tmpShip.Front.z = dataList.at(7).toFloat();
		tmpShip.Back.x = dataList.at(8).toFloat();
		tmpShip.Back.y = dataList.at(9).toFloat();
		tmpShip.Back.z = dataList.at(10).toFloat();
		tmpShip.Left.x = dataList.at(11).toFloat();
		tmpShip.Left.y = dataList.at(12).toFloat();
		tmpShip.Left.z = dataList.at(13).toFloat();
		tmpShip.Right.x = dataList.at(14).toFloat();
		tmpShip.Right.y = dataList.at(15).toFloat();
		tmpShip.Right.z = dataList.at(16).toFloat();
		tmpShip.C2.x = dataList.at(17).toFloat();
		tmpShip.C2.y = dataList.at(18).toFloat();
		tmpShip.C2.z = dataList.at(19).toFloat();
		atheta = dataList.at(20).toInt();
		ahealth = dataList.at(21).toFloat();
		sideTilt = dataList.at(22).toInt();
		headTilt = dataList.at(23).toInt();
		Players->updateNetShip(aID, tmpShip, atheta, ahealth, sideTilt,headTilt);
	}

void es_net::readWeapon(QByteArray &datagram)
	{	QList<QByteArray> dataList = datagram.split(',');

		if('a' == datagram.at(2))
		{
		phelit *tmpData = new phelit;
		tmpData->pID = dataList.at(1).toFloat();
		tmpData->location.x = dataList.at(2).toFloat();
		tmpData->location.y = dataList.at(3).toFloat();
		tmpData->location.z = dataList.at(4).toFloat();
		tmpData->shift.x = dataList.at(5).toFloat();
		tmpData->shift.y = dataList.at(6).toFloat();
		tmpData->shift.z = dataList.at(7).toFloat();
		Weapons->netEnergy(tmpData);
		}
		else if('b' == datagram.at(2))
		{
		phelcit *tmpData = new phelcit;
		tmpData->pID = dataList.at(1).toFloat();
		tmpData->location.x = dataList.at(2).toFloat();
		tmpData->location.y = dataList.at(3).toFloat();
		tmpData->location.z = dataList.at(4).toFloat();
		tmpData->shift.x = dataList.at(5).toFloat();
		tmpData->shift.y = dataList.at(6).toFloat();
		tmpData->shift.z = dataList.at(7).toFloat();
		tmpData->custom = dataList.at(8).toFloat();
		Weapons->netFire(tmpData);
		}
		else if('c' == datagram.at(2))
		{
		phelit *tmpData = new phelit;
		tmpData->pID = dataList.at(1).toFloat();
		tmpData->location.x = dataList.at(2).toFloat();
		tmpData->location.y = dataList.at(3).toFloat();
		tmpData->location.z = dataList.at(4).toFloat();
		tmpData->shift.x = dataList.at(5).toFloat();
		tmpData->shift.y = dataList.at(6).toFloat();
		tmpData->shift.z = dataList.at(7).toFloat();
		Weapons->netBomb(tmpData);
		}
		else if('d' == datagram.at(2))
		{
		phelit *tmpData = new phelit;
		tmpData->pID = dataList.at(1).toFloat();
		tmpData->location.x = dataList.at(2).toFloat();
		tmpData->location.y = dataList.at(3).toFloat();
		tmpData->location.z = dataList.at(4).toFloat();
		tmpData->shift.x = dataList.at(5).toFloat();
		tmpData->shift.y = dataList.at(6).toFloat();
		tmpData->shift.z = dataList.at(7).toFloat();
		Weapons->netThrow(tmpData);
		}
		else if('e' == datagram.at(2))
		{
		phelit *tmpData = new phelit;
		tmpData->pID = dataList.at(1).toFloat();
		tmpData->location.x = dataList.at(2).toFloat();
		tmpData->location.y = dataList.at(3).toFloat();
		tmpData->location.z = dataList.at(4).toFloat();
		tmpData->shift.x = dataList.at(5).toFloat();
		tmpData->shift.y = dataList.at(6).toFloat();
		tmpData->shift.z = dataList.at(7).toFloat();
		Weapons->netSlime(tmpData);
		}
	}
	
void es_net::sendShip(es_ship4 &aShip, int atheta, float ahealth, int sideTilt, int headTilt)
	{
QByteArray tmpData;
	tmpData
	.append("pz")
	.append(',').append( QByteArray::number(GameInfo->getmyID()))
	.append(',').append( QByteArray::number(aShip.Center.x,'g') )
	.append(',').append( QByteArray::number(aShip.Center.y,'g') )
	.append(',').append( QByteArray::number(aShip.Center.z,'g') )
	.append(',').append( QByteArray::number(aShip.Front.x,'g') )
	.append(',').append( QByteArray::number(aShip.Front.y,'g') )
	.append(',').append( QByteArray::number(aShip.Front.z,'g') )
	.append(',').append( QByteArray::number(aShip.Back.x,'g') )
	.append(',').append( QByteArray::number(aShip.Back.y,'g') )
	.append(',').append( QByteArray::number(aShip.Back.z,'g') )
	.append(',').append( QByteArray::number(aShip.Left.x,'g') )
	.append(',').append( QByteArray::number(aShip.Left.y,'g') )
	.append(',').append( QByteArray::number(aShip.Left.z,'g') )
	.append(',').append( QByteArray::number(aShip.Right.x,'g') )
	.append(',').append( QByteArray::number(aShip.Right.y,'g') )
	.append(',').append( QByteArray::number(aShip.Right.z,'g') )
	.append(',').append( QByteArray::number(aShip.C2.x,'g') )
	.append(',').append( QByteArray::number(aShip.C2.y,'g') )
	.append(',').append( QByteArray::number(aShip.C2.z,'g') )
	.append(',').append( QByteArray::number(atheta))
	.append(',').append( QByteArray::number(ahealth,'g') )
	.append(',').append( QByteArray::number(sideTilt))
	.append(',').append( QByteArray::number(headTilt));
	Client->sendNoverify(tmpData);
	}

void es_net::sendEnergy(phelit *aData)
	{
	QByteArray tmpData;
	tmpData.append("paa")
	.append(',').append( QByteArray::number( aData->pID))
	.append(',').append( QByteArray::number( aData->location.x,'g' ))
	.append(',').append( QByteArray::number( aData->location.y,'g' ))
	.append(',').append( QByteArray::number( aData->location.z,'g' ))
	.append(',').append( QByteArray::number( aData->shift.x,'g' ))
	.append(',').append( QByteArray::number( aData->shift.y,'g' ))
	.append(',').append( QByteArray::number( aData->shift.z,'g' ));
	Client->sendVerify(tmpData);
	}
void es_net::sendFire(phelcit *aData)
	{
	QByteArray tmpData;
	tmpData.append("pab")
	.append(',').append( QByteArray::number( aData->pID))
	.append(',').append( QByteArray::number( aData->location.x,'g' ))
	.append(',').append( QByteArray::number( aData->location.y,'g' ))
	.append(',').append( QByteArray::number( aData->location.z,'g' ))
	.append(',').append( QByteArray::number( aData->shift.x,'g' ))
	.append(',').append( QByteArray::number( aData->shift.y,'g' ))
	.append(',').append( QByteArray::number( aData->shift.z,'g' ))
	.append(',').append( QByteArray::number( aData->custom));
	Client->sendVerify(tmpData);
	}
void es_net::sendBomb(phelit *aData)
	{
	QByteArray tmpData;
	tmpData.append("pac")
	.append(',').append( QByteArray::number( aData->pID))
	.append(',').append( QByteArray::number( aData->location.x,'g' ))
	.append(',').append( QByteArray::number( aData->location.y,'g' ))
	.append(',').append( QByteArray::number( aData->location.z,'g' ))
	.append(',').append( QByteArray::number( aData->shift.x,'g' ))
	.append(',').append( QByteArray::number( aData->shift.y,'g' ))
	.append(',').append( QByteArray::number( aData->shift.z,'g' ));
	Client->sendVerify(tmpData);
	}
void es_net::sendThrow(phelit *aData)
	{
	QByteArray tmpData;
	tmpData.append("pad")
	.append(',').append( QByteArray::number( aData->pID))
	.append(',').append( QByteArray::number( aData->location.x,'g' ))
	.append(',').append( QByteArray::number( aData->location.y,'g' ))
	.append(',').append( QByteArray::number( aData->location.z,'g' ))
	.append(',').append( QByteArray::number( aData->shift.x,'g' ))
	.append(',').append( QByteArray::number( aData->shift.y,'g' ))
	.append(',').append( QByteArray::number( aData->shift.z,'g' ));
	Client->sendVerify(tmpData);
	}
void es_net::sendSlime(phelit *aData)
	{
	QByteArray tmpData;
	tmpData.append("pae")
	.append(',').append( QByteArray::number( aData->pID))
	.append(',').append( QByteArray::number( aData->location.x,'g' ))
	.append(',').append( QByteArray::number( aData->location.y,'g' ))
	.append(',').append( QByteArray::number( aData->location.z,'g' ))
	.append(',').append( QByteArray::number( aData->shift.x,'g' ))
	.append(',').append( QByteArray::number( aData->shift.y,'g' ))
	.append(',').append( QByteArray::number( aData->shift.z,'g' ));
	Client->sendVerify(tmpData);
	}