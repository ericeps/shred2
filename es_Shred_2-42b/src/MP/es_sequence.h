/* Used by the reliUdp classes to keep track of packets.
    Used as a counter, increments by 1(with ++) from 0 to 65,535 then will loop back to 0.
    Overloads ++.  Uses two unsigned chars so it can loaded into a character array and sent as packet.
 */
#ifndef SEQ
#define SEQ

class es_sequence{
public:
	es_sequence(){high=0;low=0;}
	es_sequence(unsigned char hh,unsigned char ll){high=hh;low=ll;}
	static es_sequence imagine(unsigned char hh,unsigned char ll){es_sequence tmp(hh,ll);return tmp;}
void operator++(){
	if(low==255)
	{low=0;
		if(high==255)
		high=0;
		else
		++high;
	}
	else
	++low;
	}
bool operator==(const es_sequence &b){
	return ((low==b.low)&&(high==b.high));
	}

unsigned char low;
unsigned char high;
};

#endif
