//#include "slpac.h"
#include "syntax.h"
#include "dir.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

//#include "read_info.h"
//#include "slpac.h"


//C_control_value  myval;

int work(char *);

int mymain();
int g_count;
bool check_runtype(int ,int);

/*
int main()
{
  pid_t  pid,sid;

  int len;
  time_t timebuf;
  pid=fork();

  if(pid<0){
            //perror("fork");
            exit(EXIT_FAILURE);
  }

  if(pid>0){
           exit(EXIT_SUCCESS);
  }

  if((sid=setsid())<0){
        perror("setsid");
       exit(EXIT_FAILURE);
  }
  if(chdir("/")<0){
             perror("chdir");
             exit(EXIT_FAILURE);


  }

   umask(0);

      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);
        printf("\nPID=%d\n",pid);
      len=strlen(ctime(&timebuf));
        g_count=0;
      while(1){

         mymain();
         sleep(5);

     if(g_count>=100){g_count=1;}
     else{g_count++;}

       }//end while(1)
     exit(0);
}//end main

*/

int main()
{  int i=1;
    g_count=0;
    while(1){ mymain() ;
        if(g_count>=100){g_count=1;}
        else{g_count++;}
        //printf("end %d=============================\n\n",g_count);
    }

}

int mymain()
{
    C_dir dd;
    char *tmp=NULL;
    char *path="/slps/";

    //printf("<<<<<<<A\n");
    dd.dirx(path);
    //printf("<<<<<<<B\n");

    struct dirent *fileinfo;

    while(( fileinfo=dd.readfromdir() )!=NULL){
        //printf("dd.readfromdir()\n");
        tmp=(char*)calloc(150,sizeof(char));

        if(dd.checkLastname(fileinfo->d_name,".slps")==true&&(strcmp(fileinfo->d_name,"..")!=0&&strcmp(fileinfo->d_name,".")!=0)){
            sprintf(tmp,"%s/%s",path,fileinfo->d_name);
            work(tmp);
        }
        free(tmp);
        tmp=NULL;

    }
    //printf("B3\n");
    dd.end_dir();
    //printf("RR=%d\n",1%20);
    return 0;
}

int work(char *fname)
{
    C_syntax   mysyn;

    find_srv  find;
    header_info h_info;
    h_info.enable=false;
    C_link_list *srv_ll=NULL;
    int number_of_service=0;

    mysyn.init();
    find.init();


    mysyn.file_to_lines(fname); //read script code
    //printf("file_to_lines(fname);\n");


    h_info=mysyn.read_from_ll_to_file_header();  //get header of script file.
    // printf("mysyn.read_from_ll_to_file_header();\n");
    if(h_info.enable==1&&(check_runtype(h_info.runtype,g_count)==true)){
        mysyn.openorclrF(h_info.fname);  //open file tmp for write
        char waittime[100];
        sprintf(waittime,"%d",h_info.timeout);
        SLPSetProperty("net.slp.multicastMaximumWait",waittime);  //set slp config(net.slp.multicastMaximumWait)
        SLPGetRefreshInterval() ;
        printf("---> %s\n",SLPGetProperty("net.slp.multicastMaximumWait"));
        find.FindSrvs_URL(h_info.srv_type);  //find srv
        //find.FindSrvs_URL("service:printer");
        //printf("find.FindSrvs_URL(h_info.srv_type);\n");
        //  printf("find.FindSrvs_URL(h_info.srv_type);\n");
        srv_ll=find.return_linklist();  // get info of srv
        number_of_service=find.re_number_of_service(); //get number of srv.
        //    printf("find.re_number_of_service();\n");
        // srv_ll->printf_all();  //print srv that we found.
        mysyn.input_clinklist(srv_ll,number_of_service); //put info of srv to mysyn
        // printf("timeout= %d\n",h_info.timeout);
        //printf("-----------------------\n");

        mysyn.proc_commend();  //execute script code

        //printf("-----------------------\n");

        mysyn.cpto();  //copy result from tmp file to real conf file.

    }
    else{printf("This file don't enable.\n");}

    mysyn.freeall();  //free mysyn

    if(srv_ll!=NULL){ srv_ll->freeall(); /*free  srv_ll*/}
    return 0;

}


bool check_runtype(int type,int count)
{
    if(type==FIRSTTIMEONLY){
        if(count==0){return true;}
        else{return false;}
    }
    else if(type==SOMETIME_FAST){
        if(count%10==0){ return true;}
        else{ return false; }
    }
    else if(type==SOMETIME_MEDIUM){
        if(count%25==0){ return true;}
        else{ return false; }
    }
    else if(type==SOMTIME_SLOW){
        if(count==100||count==0){ return true;}
        else{ return false; }
    }
    else if(type==EVERYTIME){
        return true;
    }
    else{ return false; }

}




