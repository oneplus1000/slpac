#include "slpac.h"



struct valuex{
    int index;
    int int_or_str;  //1=int 2=string  0=not use
    char name[MAX_VAL_NAME];
    char stringv[MAX_VAL_STRING];
    int num;
    struct valuex* next;
};
typedef struct valuex value;


class C_control_value
{    value *begin_val_P,*curr_val_P,*tail_val_P;
     int number_index;
     int check_howmany_val();

 public:
    void change_value_for_function(int ,char *);
    void init();
    bool add_new_val(char *,int ,int );
    bool add_new_val(char *,int ,char *);
    void printout_val();
    int get_index(char *);  // find index of value by use name   return index of value  or -1 (if name not match)
    int get_kind_by_index(int);
    int get_int_value(int);
    int get_valname(char *,int );
    void change_value(int ,int);
    void change_value(int ,char *);
    void get_string_value(int,char *);
    int freetail();
    int freeall();
    int compare_value_with_string(char*,char *);
};


