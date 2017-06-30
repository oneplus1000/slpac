#include "slpac.h"

class C_dir
{
 DIR *dirP;
public:
int dirx(char *);
struct dirent *readfromdir();
void end_dir();
bool checkLastname(char *,char *);

};



