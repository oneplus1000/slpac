#include "slpac.h"

struct one_line{  //int lineindex;
                  char line[MAX_LINE];
                  struct one_line *next;

};
typedef struct one_line oneline;


struct loopinfo{    int num;
                    int i;
		    oneline *tmp_adrr_loop;

		};
typedef struct  loopinfo loop_info;


class C_loop
{   loop_info stackloop[MAX_LOOP];
    int index_a;
public:
  void init();
  void push(int,int ,oneline *);
  void pop_free();
  int return_num();
  int return_i();
  oneline * return_P();
  void reduce_i();
  void reduce_num();

};


