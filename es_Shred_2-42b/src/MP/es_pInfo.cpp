
#include "es_pInfo.h"
#include "es_client.h"
#include <algorithm>
#include <iostream>

void es_pInfo::damage(float dam, unsigned char ID){
	std::list<es_pstats>::iterator ii = find(pStats.begin(),pStats.end(),ID);
	if(ii != pStats.end())
	ii->Damage += dam;
	}
void es_pInfo::killed(unsigned char ID){
	std::list<es_pstats>::iterator ii = find(pStats.begin(),pStats.end(),ID);
	if(ii != pStats.end())
	++ii->Kills;
	std::cout<<"killed by "<<(int)ID<<std::endl;
	}
void es_pInfo::slowed(unsigned char ID){
	std::list<es_pstats>::iterator ii = find(pStats.begin(),pStats.end(),ID);
	if(ii != pStats.end())
	++ii->Slows;
	}
	
void es_pInfo::setup(std::list<unsigned char> &oplist,unsigned char amyID){
pStats.clear();
	std::list<unsigned char>::iterator ii;
	for(ii=oplist.begin();ii!=oplist.end();ii++)
	{
	es_pstats tmp(*ii);
	pStats.push_back(tmp);
	}
	es_pstats tmp(amyID);
	pStats.push_back(tmp);
	}
void es_pInfo::setup(unsigned char amyID){
pStats.clear();
	es_pstats tmp(amyID);
	pStats.push_back(tmp);
	}
std::list<es_pstats> es_pInfo::getList(){
	return pStats;
	}

es_pInfo::es_pInfo(){

}