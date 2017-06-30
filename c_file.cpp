#include "c_file.h"


void C_file::init()
{
    //fileP=NULL;
    sprintf(g_fname_tmp,"/tmp/slptmp.tmp");
}

void C_file::inputfname(char *fname)
{
    strcpy(g_fname,fname);
}


int C_file::writef(char *line)
{
    FILE *fp=NULL;
    fp=fopen(g_fname_tmp,"a");
    if(fp==NULL){return -1;}
    fprintf(fp,"%s\n",line);
    fclose(fp);
    return 1;
}

int C_file::writef_sameline(char *line)
{
    FILE *fp=NULL;
    fp=fopen(g_fname_tmp,"a");
    if(fp==NULL){return -1;}
    fprintf(fp,"%s\n",line);
    fclose(fp);
    return 1;
}


int C_file::openorclear()
{  FILE *fp=NULL;
    fp=fopen(g_fname_tmp,"w");
    if(fp==NULL){return -1;}
    fprintf(fp,"");
    fclose(fp);
    return 1;
}

int C_file::cpyto()
{  char linetmp[MAX_LINE];
    FILE *fp_sorce=NULL;
    FILE *fp_des=NULL;
    fp_sorce=fopen(g_fname_tmp,"r");
    fp_des=fopen(g_fname,"w");
    if(fp_sorce==NULL||fp_des==NULL){return -1;}

    while( fgets(linetmp,MAX_LINE,fp_sorce)!=NULL )
    {
        //add_line(linetmp);
        //printf("%s\n",linetmp);
        fprintf(fp_des,"%s",linetmp);
    }
    fclose(fp_des);
    fclose(fp_sorce);
    return 1;
}







