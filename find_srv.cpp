#include "find_srv.h"
//#include <slp.h>

C_link_list mylist;
int 	number_of_service=0;
void FindAttrs(char *);
SLPBoolean mySrvUrlCallback( SLPHandle ,const char* ,unsigned short ,SLPError ,void* );
SLPBoolean myAttrCallback(SLPHandle ,const char*,SLPError ,void* );

void find_srv::init()
{
    number_of_service=0;
    mylist.init();
}


SLPBoolean mySrvUrlCallback( SLPHandle hslp,const char* srvurl,unsigned short lifetime,SLPError errcode,void* cookie )
{  //int tmp;
    //char tmp_url[MAX_SERVICE_URL],tmp_addr[MAX_SERVICE_URL];


    if(errcode == SLP_OK)
    {
        //printf("URL%s,%i\n",srvurl,lifetime);
        //srv_stru.add_new_service_URL((char *)srvurl,(int)lifetime);
        //FindAttrs((char *)srvurl);
        number_of_service++;
        //printf("xxx]\n");
        mylist.add_new_service((char *)srvurl);
        //printf("xxx]2\n");
        FindAttrs((char*)srvurl);
        //printf("xxx]3\n");
    }

    return SLP_TRUE;
}



void find_srv::FindSrvs_URL(char* Asrvtype)

{
    SLPError    result;
    SLPHandle   hslp;
    SLPError callbackerr;

    if(SLPOpen("en",SLP_FALSE,&hslp) == SLP_OK)
    {    //printf("\ntest\n");


        result = SLPFindSrvs(hslp,
                             Asrvtype,
                             0,
                             0,
                             mySrvUrlCallback,
                             &callbackerr);
        //printf("\ntest2\n");


        if(result != SLP_OK)
        {
            printf("errorcode: %i\n",result);
        }
        SLPClose(hslp);
    }
}



SLPBoolean myAttrCallback(SLPHandle hslp,const char* attrlist,SLPError errcode,void* cookie )

{  //printf("+++++\n");
    if(errcode == SLP_OK)
    {
        //printf("att->%s\n",attrlist);
        mylist.add_new_att((char *)attrlist );
        //printf("==========\n");
    }
    //printf("==========2\n");
    return SLP_TRUE;
}




void FindAttrs(char *srv_url)

{
    SLPError    result;
    SLPHandle   hslp;

    if(SLPOpen("en",SLP_FALSE,&hslp) == SLP_OK)
    {
        //printf("xxx\n");
        result = SLPFindAttrs(hslp,
                              srv_url,
                              0,
                              0,
                              myAttrCallback,
                              0);
        //printf("xxx2\n");
        if(result != SLP_OK)
        {
            printf("errorcode: %i\n",result);
        }
        SLPClose(hslp);
    }
}



C_link_list* find_srv::return_linklist()
{

    return &mylist;

}


int find_srv::re_number_of_service()
{
    return number_of_service;
}


