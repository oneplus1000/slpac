#include "dir.h"

int C_dir :: dirx(char *path)
{
    dirP=NULL;

    //if(opendir(dirP)){}
    printf(";%s;\n",path);
    dirP=opendir(path);
    //printf(";;\n");
    return 0;
    // if(dirP!=NULL){printf("not NULL\n");}
}


struct dirent  * C_dir ::readfromdir()
{

    //printf("XX\n");
    //return readdir(dirP);
    if(dirP!=NULL){return readdir(dirP);}
    else { return NULL;}
}

bool C_dir :: checkLastname(char *fullname,char *lastname)
{
    char funametmp[MAX_FNAME],lnametmp[MAX_FNAME];
    bool rev=true;
    strcpy(funametmp,fullname);
    strcpy(lnametmp,lastname);
    int lenf=0,i=0,j=0;
    lenf=strlen(funametmp);
    //printf("");
    while(i<lenf){

        if(funametmp[i]=='.'){
            j=0;
            while(j<strlen(lnametmp)){
                if(funametmp[i]!=lnametmp[j]){ rev=false; }
                j++; i++;
            }

        }//end if
        i++;
    }

    return rev;
}



void C_dir :: end_dir()
{
    closedir(dirP);

}




