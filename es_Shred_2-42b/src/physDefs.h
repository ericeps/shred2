/* Container classes and classes related to the game 3D world.

 */

#ifndef PHYSDEFS
#define PHYSDEFS

#include "defs.h"

struct loc {
	point3f location;
	};

template <typename T>
class listEl{
	public:
		T* prev;
		T* next;
		public:
		static T* incr(T *aphys){
			//aphys= aphys->next;
			return aphys->next;
			};
		virtual ~listEl(){};
		listEl(){next=NULL;prev=NULL;}
	};
template <typename T>
class es_list{
	T* first;
	T* last;
	public:
	T* front(){return first;}
	T* back(){return last;}
	void push_back(T* anel){
			anel->next = NULL;
			if(last!=NULL)
			last->next=anel;
			anel->prev = last;
			last = anel;
			if(first==NULL)
			first=anel;
			}
	T* erase(T *aphys){
			if(aphys==last)
			last=aphys->prev;
			if(aphys==first)
			first=aphys->next;
			if(aphys->prev != NULL)
			aphys->prev->next = aphys->next;
			if(aphys->next != NULL)
			aphys->next->prev = aphys->prev;
			T *tmp = aphys->next;
			//aphys = aphys->next;
			delete aphys;
			return tmp;
			};
	es_list(){first=NULL;last=NULL;}
	virtual ~es_list(){};
};
struct loc_customf:public loc, public listEl<loc_customf> {  // location, list element, custom float....explosion
	float custom;
	};

class clost :public es_list<loc_customf>{
};


struct phelit :public loc,public listEl<phelit>{ //location, list element, Collidable, shiftable, pID....most weapons
	point3f shift;
	unsigned char pID;
	virtual ~phelit(){};
	};
struct phelcit : public phelit{ //location, list element, Collidable, shiftable, pID, custom integer.....fire weap
	int custom;
	};
class CollProc{
	public:
	virtual void Process(phelit *aph) = 0;
	virtual ~CollProc(){};
	};
class phelColl:public CollProc{
	public:
	virtual void Process(phelit *aph){
		loc_customf *tmpc = new loc_customf;
		tmpc->location = aph->location;
		tmpc->custom = defcust;
		colList.push_back(tmpc);
		}
	phelColl(float adef){defcust=adef;};
	clost colList;
	private:
	float defcust;
	};
class phlist: public es_list<phelit>{
public:
	CollProc *Collision;
};

#endif
