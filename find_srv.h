#include "slpac.h"
#include "C_link_list.h"
//#include "C_link_list.h"

class find_srv{

 public:
   int re_number_of_service();
   void init();
   void FindSrvs_URL(char*);
   C_link_list* return_linklist();

 //void FindAttrs(char *);
};


