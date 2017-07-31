/* Stores data related to a player's score.

 */
#ifndef PINFO
#define PINFO

#include <list>

struct es_pstats{
unsigned char ID;
float Damage;
int Kills;
int Slows;
bool operator==(const unsigned char achar){return achar==ID;}
es_pstats(unsigned char achar){ID=achar;Damage=0;Kills=0;Slows=0;}
//es_pstats(unsigned char achar,float dmg,int kil,int slo){ID=achar;Damage=dmg;Kills=kil;Slows=slo;}
};

class es_pInfo{
public:
es_pInfo();
void setup(std::list<unsigned char>&,unsigned char);
void setup(unsigned char amyID);
std::list<es_pstats> getList();
void damage(float,unsigned char);
void killed(unsigned char);
void slowed(unsigned char);

private:
std::list<es_pstats> pStats;
};
#endif
