#include "slpac.h"

 struct od{
		char text[100];
		int score;
		struct od * next;

	 };
typedef  struct od order;


class c_order{
  public:
  	int g_num;
	 void init();
	 void add(char [],int);
	 order get();
	 void freeall();
	 	order * cur;

 private:	order * begin;
	order * tail;

	void freeone();



};

