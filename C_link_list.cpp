#include "C_link_list.h"
#include "read_info.h"

C_read_info converterl;

void C_link_list::init()
{
begin=NULL;
tail=NULL;
curr=NULL;
}



int C_link_list::freetail()
{
     srvtype_ll *previousP=NULL;



          previousP=begin;

	  if(begin==NULL ||tail==NULL){/*number=0;*/ return 0;}

	  else if(begin==tail){

				      free(tail);
				      tail=NULL;
				      begin=NULL;


	                        }
	  else{
	        while(previousP->nextdoor!=tail){ previousP=previousP->nextdoor; }

                 free(tail);
		 tail=previousP;
                 tail->nextdoor=NULL;
              }

return 1;
}

int C_link_list::freeall()
{
 // oneline *previousP=NULL;
  //previousP=begin_line_P;

  while( begin!=NULL){

      freetail();
  }
return 0;
}










void C_link_list::reset_curr()
{
curr=begin;
}

char * C_link_list::get_all_curr_att()
{  
 //char tmp[MAX_A_SERVICE_ATT];
 //tmp=(char *)(char *)calloc(strlen(curr->service_attr)+1,sizeof(char));
  //strcpy(tmp,curr->service_attr);
 // printf("LLL\n");
 if(curr!=NULL){return  curr->service_attr;}
 else{return NULL;}
}

void C_link_list::add_new_service(char *srvurl)
{

if(begin==NULL ){begin=(srvtype_ll *)malloc(sizeof(srvtype_ll));
                  //begin->index=number;
                  sprintf(begin->service_url,"%s",srvurl);
                 // sprintf(begin->service_attr,"%s",srvatt);
		 begin->score=0;
		  begin->nextdoor=NULL;
		  tail=begin;
		}
else{
            tail->nextdoor=(srvtype_ll *)malloc(sizeof(srvtype_ll));
	    tail=tail->nextdoor;
	    sprintf(tail->service_url,"%s",srvurl);
	   // sprintf(tail->service_attr,"%s",srvatt);
           // tailP->index=number;
	    tail->score=0;
            tail->nextdoor=NULL;

       }

curr=begin;

}



int C_link_list::read_and_free_from_tail(char *outsrv,char*outatt)
{
/* this function will read infomation in tail of link-list and free them
   +-----------+    +------------    +-----------+    +--------------+
   |          -|--->|          -|--->|          -|--->|read this one-|--->NULL
   +-----------+    +-----------+    +-----------+    +--------------+

    +-----------+    +------------    +-----------+
   |          -|--->|          -|--->|          -|---> " free!"
   +-----------+    +-----------+    +-----------+
 */
   //char tmp[MAX_SERVICE_TYPE_ARRAY ];
   //char tmpatt[MAX_A_SERVICE_ATT];
   int tmp_index=0;


   srvtype_ll *previous=NULL;



          previous=begin;

	  if(begin==NULL || tail==NULL){ outsrv=NULL; outatt=NULL;  return 0;}

	  else if(begin==tail){
	                              sprintf(outsrv,"%s",tail->service_url);
				      sprintf(outatt,"%s",tail->service_attr);
				      //tmp_index=tailP->index;
				      free(tail);
				      tail=NULL;
				      begin=NULL;


	                        }
	  else{
	        while(previous->nextdoor!=tail){ previous=previous->nextdoor; }
                // sprintf(output,"%s",tailP->service_type);
		    sprintf(outsrv,"%s",tail->service_url);
	            sprintf(outatt,"%s",tail->service_attr);
                // tmp_index=tail->index;
                 free(tail);
		 tail=previous;
                 tail->nextdoor=NULL;
              }





  // if(previousP->nextdoor==tailP){ printf("\nokxxx\n");}



 // number--;

  return tmp_index;
}


void C_link_list::add_new_att(char *srvatt)
{

 sprintf(tail->service_attr,"%s",srvatt);
}



void C_link_list::printf_all()
{
// int i;
srvtype_ll *tmpP=NULL;

tmpP=begin;
         //if(tmpP==NULL){printf("NULLLLLLLLLLLLLLLLLL\n");}
       while(tmpP!=NULL){
          printf("\nsrv->%s <-> srv att%s <-%d\n",tmpP->service_url,tmpP->service_attr,tmpP->score);
	  tmpP=tmpP->nextdoor;
	  }


}


void C_link_list::get_curr_addr(char *out)
{
  char tmp[MAX_SERVICE_URL];
   char tmp_out[MAX_SERVICE_URL];
  int index=0,len=0,i=0,j=0;

  //printf(">>%s\n",curr->service_url);
if(curr!=NULL){
   strcpy(tmp,curr->service_url);

  index=converterl.indexOfs(curr->service_url,"://",1);

  len=strlen(tmp);
  i=index+2; j=0;
  while(i<len){
     tmp_out[j]=tmp[i];
  i++;
  j++;
  }

  tmp_out[j]='\0';
//indexOfs(char *text,char *cmptext,int rank)
  strcpy(out,tmp_out);
  }
  else{  strcpy(out,"\0"); }
}




void C_link_list::get_curr_svr_addr(char *out,char *attrwant)
{
  char *tmp=NULL;
  char *tmpout=NULL;
//int revalue=0;
//char *tmptoken1_1=NULL;
//printf("yyy1\n");

/*tmp=(char *)calloc(strlen(curr->service_attr)+1,sizeof(char));
tmpout=(char *)calloc(strlen(curr->service_attr)+1,sizeof(char));
*/
tmp=(char *)calloc(MAX_A_SERVICE_ATT+1,sizeof(char));
tmpout=(char *)calloc(MAX_A_SERVICE_ATT+1,sizeof(char));



//printf("yyy1\n");
if(curr!=NULL){
strcpy(tmp,curr->service_attr);
}
//printf("yyy2\n");


converterl.get_attrs(tmpout,attrwant,tmp);

strcpy(out,tmpout);
free(tmpout);
}



void C_link_list::next_curr()
{
if(curr->nextdoor!=NULL){
curr=curr->nextdoor;
}
}












