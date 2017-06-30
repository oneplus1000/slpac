#include "slpac.h"
//#include <
class C_file{
    //FILE *fileP;
    char g_fname[MAX_FNAME];
    char g_fname_tmp[MAX_FNAME];
public:
    void init();
    void inputfname(char *);
    int openorclear(); /*open new file if don't have this file name or open file(if we have that file name)then clear data of that file */
    int writef(char *); /*write data to file(tmp file)*/
    int writef_sameline(char *);
    int cpyto();

};


