#include "slpac.h"
//
struct srvlink
             {    int index;
                  char service_url[MAX_SERVICE_TYPE_ARRAY ];
                  char service_attr[MAX_A_SERVICE_ATT];
				 int  score;
                  struct srvlink * nextdoor;

              };

typedef struct srvlink srvtype_ll;


class C_link_list{



  public:
   srvtype_ll *begin;
       srvtype_ll *tail;
   int  freetail();
    int freeall();
    srvtype_ll *curr;
      void init();
      void add_new_service(char *);
      void add_new_att(char *);
      int read_and_free_from_tail(char *,char*);
      void printf_all();
       void get_curr_svr_addr(char *,char *);
       char* get_all_curr_att();
       void next_curr();
       void get_curr_addr(char *);
       void reset_curr();

};






