/* Common network classes/functions.

 */
#ifndef ES_NETDEFS
#define ES_NETDEFS

#include <QHostAddress>
#include <QNetworkInterface>
#include <QByteArray>
#include "es_sequence.h"

struct packet_info{
	int resendAttempt;
	QByteArray data;
	bool operator==(const es_sequence& aseq){
		return (es_sequence::imagine(data.at(4),data.at(5)) == aseq);
		}
	};


class es_ipcheck
{

public:
static bool isV4(const QHostAddress &v){return v.protocol() == QAbstractSocket::IPv4Protocol;}
static bool isV6(const QHostAddress &v){return v.protocol() == QAbstractSocket::IPv6Protocol;}
static bool isLocal(const QHostAddress &v){return v == QHostAddress::LocalHost;}

static QHostAddress getMyAddress(){
	QHostAddress tmp;
		QList<QHostAddress> hostadds = QNetworkInterface::allAddresses();
		for(int ii=0;ii<hostadds.size();ii++)
		{
		if(es_ipcheck::isV4(hostadds.at(ii)) && !es_ipcheck::isLocal(hostadds.at(ii)))
		tmp = hostadds.at(ii);
		}
	return tmp;
	}
};

#endif
