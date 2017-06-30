#include "slpac.h"


class C_read_info
{
   private:
//public:
   protected:



     int insert_text(char*,char*,char*,int,int);
     /*-----------*/
   public:
     bool chaek_attrs(char *,char*);
     void  insert_char(char *,char *,char ,int,int);
     int convert_syntax_char(char *,char *,char ,char *);
     int indexOfs_end(char *,char *,int );
     int indexOfs(char *,char *,int );
     int startWith(char *,char *);
     bool startWith2(char *,char *);
     int getToken(char* ,char *,int);
     int getToken2(char*,char *,int);
     int cmptext(char *,char*);
     int cmptext2(char *,char*);
     int cmp_Atoken(char *,char*);
     int itIsInterger(char *);
     int plusplus(char *,char *);
     int convert_syntax_srv_address(char *,char *,char *,char *);
     int convert_syntax_replase(char *,char *,char *,char *);
     int get_attrs(char *,char *,char* );
     bool check_token_2rd(char *,char *);
     int insert_text2(char *,int,char *,char *,int,int);
    //void cut_empty_char();
};



