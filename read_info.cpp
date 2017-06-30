#include "read_info.h"


int C_read_info::cmptext2(char *text,char*cmptext)
{

  if(strlen(text)<strlen(cmptext)){return 0;}
 int number=0,i=0,j=0,z=0;
 int  len=strlen(text);
 int len_cmp=strlen(cmptext);
 char *temp=NULL;
 char *temp2=NULL;
     temp=(char*)calloc(sizeof(char),strlen(text)+100);
     temp2=(char*)calloc(sizeof(char),strlen(text)+100);
  sprintf(temp,"%s",text);

  while(i<len){
    
       j=i; z=0;
      while(j<len_cmp){
           temp2[z]=temp[j];
	 j++; z++;
      }
      temp2[z]='\0';

   //printf("[%s]\n",temp2);
    i++;
  }


free(temp);
free(temp2);
return number;

}

int C_read_info::cmptext(char *text,char *cmptext)
{
   /*return number of how many text cmptext  in text*/
   /*eg. text="tongbasketbas"  cmptext="bas"  function will return  2 */
    int len_text=0,len_cmptext=0;
    int i=0,j=0,check=0;
    int returnvalue=0;
   len_text=strlen(text);
   len_cmptext=strlen(cmptext);


   while(i<len_text)
   {

      if(text[i]==cmptext[0]){

	     j=0; check=0;
	   while(j<len_cmptext){

	       if(text[i]==cmptext[j]){ check++; j++;  i++;}
               else{j=len_cmptext+100;/*exit form loop*/}
	    }
             i--;
	  if(check==len_cmptext){ returnvalue++; /*printf("X");*/}
      }

    i++;
   }



return returnvalue;
}//end C_read_info_config::cmptext(char *text,char *cmptext)





int C_read_info::indexOfs(char *text,char *cmptext,int rank)
{
/*
this function return index of text cmptext  with in text
eg. text="tongbasketbas"  cmptext="bas"  rank=1   function will return indexof  first "bas" (return 5)
    text="tongbasketbas"  cmptext="bas"  rank=2  function will return indexof  2rd "bas" (return 11)

*/

int len_text=0,len_cmptext=0;
    int i=0,j=0,check=0;
    int returnvalue=0,tmp=0;
    int rank_count=0;
   len_text=strlen(text);
   len_cmptext=strlen(cmptext);
   //printf("\n%d\n",len_cmptext);

   while(i<len_text)
   {

      if(text[i]==cmptext[0]){

	     j=0; check=0;

	   while(j<len_cmptext){
               if(j==0){tmp=i;}
	       if(text[i]==cmptext[j]){ check++; j++;  i++;}
               else{j=len_cmptext+100;/*exit form loop*/}
	    }
             i--;
	  if((check==len_cmptext)&&(rank_count<rank)){ rank_count++; returnvalue=tmp; }
      }

    i++;
   }


return returnvalue+1;
}


int C_read_info::indexOfs_end(char *text,char *cmptext,int rank)
{
/*
this function return index of text cmptext  with in text
eg. text="tongbasketbas"  cmptext="bas"  rank=1   function will return indexof  first "bas" but number returned is indexof last characther  (return 7)
    text="tongbasketbas"  cmptext="bas"  rank=2  function will return indexof  2rd "bas" but number returned is indexof last characther (return 13)

*/

int len_text=0,len_cmptext=0;
    int i=0,j=0,check=0;
    int returnvalue=0;
    int rank_count=0;
   len_text=strlen(text);
   len_cmptext=strlen(cmptext);
   //printf("\n%d\n",len_cmptext);

   while(i<len_text)
   {

      if(text[i]==cmptext[0]){

	     j=0; check=0;

	   while(j<len_cmptext){

	       if(text[i]==cmptext[j]){ check++; j++;  i++;}
               else{j=len_cmptext+100;/*exit form loop*/}
	    }
             i--;
	  if((check==len_cmptext)&&(rank_count<rank)){ rank_count++; returnvalue=i; }
      }

    i++;
   }


return returnvalue+1;
}



int C_read_info::insert_text(char *textoutput,char *text,char *inserter,int begin,int end)
{
/*
this function will insert "inserter"  in to "text"  and output to "textoutput"
eg.  text="ABCDEFGHIJ"    inserter="tong"  begin=2   end=5
1.   tmp1 <= "AB"   ,tmp2<="FGHIJ"
2.   textoutput <= tmp1+inserter+tmp2   ( "ABtongFGHIJ" )
*/
//printf("out %s; text |%s; inser %s; bggin %d; end %d;\n\n ",textoutput,text,inserter, begin, end);
char* tmp1=NULL;
char* tmp2=NULL;
//char* temp=NULL;
int i=0,j=0;
  if(strlen(text)<=begin||strlen(text)<end){ return -1;}
//printf("ttt1x\n");
   // tmp1=(char*)malloc(sizeof(text));
    //tmp2=(char*)malloc(sizeof(text));
tmp1=(char*)calloc(strlen(text)+1,sizeof(char));
tmp2=(char*)calloc(strlen(text)+1,sizeof(char));

    //stpncpy(tmp1,text,begin);
//printf("%s\n",text);
   i=0;
   j=0;
//if(tmp1!=NULL)printf("tmp1 not null\n");
//if(tmp2!=NULL)printf("tmp2 not null\n");
while(i<begin-1){
      //printf("%c\n",text[i]);
     tmp1[j]=text[i];
     i++;j++;


   }
    tmp1[j]='\0';
//printf("tmp1 =%s\n",tmp1);
   i=end;
   j=0;
   while(text[i]!='\0'){

     tmp2[j]=text[i];
     i++;j++;
    // printf("%c\n",text[i]);

   }
    tmp2[j]='\0';
  //  printf("tmp2 =%s\n",tmp2);
//printf("in4\n");
  //printf("\ntmp1=%s,tmp2->%s\n\n",tmp1,tmp2);
  //printf("%d %d %d\n",strlen(tmp1),strlen(tmp2),strlen(inserter));
   strcpy(textoutput,tmp1);
   //printf("2.tmp2 =%s\n",tmp2);
   //printf("in3\n");
   strcat(textoutput,inserter);
   //printf("2.inserter =%s\n",inserter);
   //printf("in2 %s  ;%s;\n",textoutput,tmp2);
   strcat(textoutput,tmp2);
  //printf("\nout=%s\n",textoutput);
   //printf("in1\n");
  free(tmp1);
  free(tmp2);
  //printf("in\n");
return 0;
}


int C_read_info::insert_text2(char *textoutput,int sizeoftextout,char *text,char *inserter,int begin,int end)
{
/*
this function will insert "inserter"  in to "text"  and output to "textoutput"
eg.  text="ABCDEFGHIJ"    inserter="tong"  begin=2   end=5
1.   tmp1 <= "AB"   ,tmp2<="FGHIJ"
2.   textoutput <= tmp1+inserter+tmp2   ( "ABtongFGHIJ" )
*/
printf("out %s; text |%s; inser %s; bggin %d; end %d;\n\n ",textoutput,text,inserter, begin, end);
char* tmp1=NULL;
char* tmp2=NULL;
char * out=NULL;
//char* temp=NULL;
int i=0,j=0;
  if(strlen(text)<=begin||strlen(text)<end){ return -1;}
//printf("ttt1x\n");
   // tmp1=(char*)malloc(sizeof(text));
    //tmp2=(char*)malloc(sizeof(text));
tmp1=(char*)calloc(strlen(text)+1,sizeof(char));
tmp2=(char*)calloc(strlen(text)+1,sizeof(char));
out=(char*)calloc(sizeoftextout,sizeof(char));

    //stpncpy(tmp1,text,begin);
//printf("%s\n",text);
   i=0;
   j=0;
//if(tmp1!=NULL)printf("tmp1 not null\n");
//if(tmp2!=NULL)printf("tmp2 not null\n");
while(i<begin-1){
      //printf("%c\n",text[i]);
     tmp1[j]=text[i];
     i++;j++;


   }
    tmp1[j]='\0';
//printf("tmp1 =%s\n",tmp1);
   i=end;
   j=0;
   while(text[i]!='\0'){

     tmp2[j]=text[i];
     i++;j++;
    // printf("%c\n",text[i]);

   }
    tmp2[j]='\0';
  //  printf("tmp2 =%s\n",tmp2);
//printf("in4\n");
  //printf("\ntmp1=%s,tmp2->%s\n\n",tmp1,tmp2);
              strcpy(out,tmp1);
   //printf("2.tmp2 =%s\n",tmp2);
   //printf("in3\n");
            strcat(out,inserter);
   //printf("2.inserter =%s\n",inserter);
   //printf("in2 %s  ;%s;\n",textoutput,tmp2);
             strcat(out,tmp2);
  printf("\nout=;%s; len =%d ==%d\n",out,strlen(out),sizeoftextout);
  //strcpy(textoutput,out);
  sprintf(textoutput,"%s",out);
   //printf("in1\n");
  free(tmp1);
  free(tmp2);
  free(out);
  //printf("in\n");
return 0;
}



int C_read_info::startWith(char *line,char* startwith)
{  /*return 1 when "startwith" value is start string on line
     if not return -1 */
//printf("line =:%s: startwith =:%s:\n",line,startwith);
/* char tmpl[MAX_VAL_STRING+200];
 char tmpw[MAX_VAL_STRING];*/
 char *tmpl=NULL;
 char *tmpw=NULL;
 int i=0,max=0,startbit=1,j=0;
 tmpl=(char*)calloc(strlen(line)+100,sizeof(char));
 tmpw=(char*)calloc(strlen(startwith)+100,sizeof(char));
   //printf("e3_2\n");
 strcpy(tmpl,line);
 strcpy(tmpw,startwith);

 if(strlen(tmpw)>strlen(tmpl)){  free(tmpl);  free(tmpw); return -1;}


  max=strlen(tmpl);
 while(tmpl[i]==' '&&(i<max)){ i++; }

 if(i>=max){  free(tmpl);  free(tmpw); return -1; }

 //check
  while(j<strlen(tmpw))
  {
     if(tmpl[i]!=tmpw[j]){startbit=-1;}
     j++; i++;
  }
 free(tmpl);  
 free(tmpw);
return startbit;
}




bool C_read_info::startWith2(char *line,char* startwith)
{ //printf("line= %s stratw= %s\n",line,startwith);
  int i=0;
 char tmpl2[MAX_VAL_STRING+10];
 char tmpw2[MAX_VAL_STRING+10];

 //tmpl2=(char*)calloc(strlen(line)+100,sizeof(char));
 //tmpw2=(char*)calloc(strlen(startwith)+100,sizeof(char));
// printf("before\n");
 strcpy(tmpl2,line);
 //sprintf(tmpl2,"%s",line);
 snprintf(tmpw2,sizeof(tmpw2),"%s",startwith);
// printf("after\n");
  bool revalue=true;

   while(i<strlen(startwith)){
      if(tmpl2[i]!=tmpw2[i]){  revalue=false; }
      i++;
   }

  //  printf("line=%s; re %d\n",line, revalue);
//free(tmpl2);
//free(tmpw2);
return revalue;
}



int C_read_info::getToken(char *outtoken,char *line,int index)
{

  int i=0,num=0,index_text=0,j=0,num2=0;

  int bit1=0,bit2=0;

  char *tmpw=NULL;
  char *out=NULL;

  tmpw=(char*)calloc(strlen(line)+1,sizeof(char));
  out=(char*)calloc(strlen(line)+1,sizeof(char));
  num=strlen(line);
  num2=num;
 strcpy(tmpw,line);
 //printf("test1\n");
i=0;
while(i<num-1){
   if(tmpw[i]==' '){ bit1=-1;  }
   else{  bit1=1;      }

   if(tmpw[i+1]==' '){ bit2=-1;  }
   else{  bit2=1;      }

   if(bit1!=bit2&&bit2==1){ /*printf("test2\n");*/
                   if(index_text==index){
		        while(tmpw[i+1]!=' ')
		        {
                           out[j]=tmpw[i+1];
			   i++;
			   j++;
			   num=-1;
		        }
			out[j]='\0';
                      }
		   else{j=0;}

		    index_text++;

		 }


i++;

}

strcpy(outtoken,out);
free(tmpw);
free(out);

if(num==-1){/*printf("\nwe have\n");*/return 1;}
return 0;  //end of token

}

int C_read_info::cmp_Atoken(char *text1x,char*text2x)
{
 	int n1=0,n2=0,i=0,j=0,bit=0;
	char *text1;
	char *text2;
 	n1=strlen(text1x);
 	n2=strlen(text2x);

text1=(char*)calloc(strlen(text1x)+1,sizeof(char));
text2=(char*)calloc(strlen(text2x)+1,sizeof(char));

strcpy(text1,text1x);
strcpy(text2,text2x);


  while(text1[i]==' '&&i<=n1){ i++; }
  while(text2[j]==' '&&j<=n2){ j++; }

  while((text1[i]!=' '||text2[j]!=' ')&&i<=n1&&j<=n2){
                                        if(text1[i]!=text2[j]){ bit=1; }

					i++; j++;
                                      }

free(text1);
free(text2);

  return bit;
}


int C_read_info::itIsInterger(char *text)
{
int len=0,i=0,step1=0,step2=0,re=1;
//printf("ttt2e\n");
char *tmp=(char*)calloc(strlen(text)+1,sizeof(char));

strcpy(tmp,text);
len=strlen(tmp);
//printf("ttt2e%s\n",text);
//bitemtpy=0;

//bitmatchAll=1;

for(i=0;i<len;i++){ if(tmp[i]!=' '){ step1=1; /*not emtpy*/}  }


if(step1==1 ){   for(i=0;i<len;i++){ if(tmp[i]==' '||tmp[i]=='0'){   }
                                     else {  step2=1; }

				      }

                      if( step2==1 ){
		                        if(atoi(tmp)==0){ re=0; }
					else{ re=1; }
		                     }
	              else{   re=1;   }


                }
else{
          re=0;
    }



//printf("bitmatchAll=%d \n",re);
//return 1 is integer  0 is not
//printf("int %d\n",re);
free(tmp);
return re;
}




int C_read_info::plusplus(char *out,char *line)
{
char *text1=NULL;
char *text2=NULL;
int i=0;

text1=(char*)calloc(strlen(line)+1,sizeof(char));
text2=(char*)calloc(strlen(line)+1,sizeof(char));

while(i<strlen(line)){
                       
                     }

free(text1);
free(text2);
return 0;

}



int C_read_info::convert_syntax_replase(char *textoutput,char *text,char *svr_add_to_repaste,char *svr_addre)
{
  /* à¸?à¸±à¸?à¸?à¸±à¸? à¸?à¸µà¹?à¸?à¸°à¸?à¸³à¸?à¸²à¸£ à¸«à¸²à¸?à¸³à¸?à¸µà¹?à¸­à¸¢à¸¹à¹?à¹?à¸? svr_addre à¸?à¸µà¹?à¸­à¸¢à¸¹à¹?à¹?à¸? text à¹?à¸¥à¹?à¸§à¹?à¸?à¸?à¸?à¸µà¹?à¸?à¹?à¸§à¸¢  svr_add_to_repaste  à¹?à¸¥à¹?à¸§ return à¸?à¸¥à¸±à¸?à¹?à¸?à¸?à¸²à¸? textoutput

  */
     char *temp=NULL;
     char *temp2=NULL;
     //char temp[100];
     //char temp2[100];
     int howmanytime=0,i=1,index=0,index_e=0;
     //char svr_addre[20]="[service-address]";

  //int tong[50];
  //memset(tong,'a',sizeof(tong));
  //printf("tong \n");
     int len=strlen(text)+strlen(svr_add_to_repaste)+strlen(svr_addre)+1;
     temp=(char*)calloc(strlen(text)+strlen(svr_add_to_repaste)+strlen(svr_addre)+1,sizeof(char));
    temp2=(char*)calloc(strlen(text)+strlen(svr_add_to_repaste)+strlen(svr_addre)+1,sizeof(char));
   
   

   //memset(temp,'\0',sizeof(temp));
   //memset(temp2,'\0',sizeof(temp2));
   //printf("ssss-> %d\n",sizeof(*temp2));
//printf("test1_1\n");
     strcpy(temp,text);
     //printf("sizeof = %d; len =%d\n",sizeof(*temp),len);
  //sizeof()
      howmanytime=cmptext(temp,svr_addre);
      //printf("=====>%d\n",howmanytime);
//printf("test1_3\n");
       while(i<=howmanytime){
       // printf("test > %d\n",howmanytime);
        //  printf("loop1=%d\n",i);
	 index=indexOfs(temp,svr_addre,1);
	  //printf("loop2=%d\n",i);

         index_e=indexOfs_end(temp,svr_addre,1);
	  //printf("loop3=%d\n",i);
         // printf("be-->%s\n",temp);
	  //memset(temp2,'a',sizeof(temp2));
	 printf("len =%d\n",len);
	 insert_text2(temp2,len,temp,svr_add_to_repaste,index,index_e);

	  //printf("trerr2\n");
	 //printf("loop4=%d\n",i);
          //printf("af-->%s\n\n",temp);

	 strcpy(temp,temp2);

	 //printf("loop5=%d\n",i);
	 // printf("%s,%s,%d,%d\n----------\n",temp,temp2,index,index_e);
	i++;
      }


      //printf("out =%d  text=%s\n",strlen(temp),temp);
      strcpy(textoutput,temp);
 //printf("trerr1\n");
 //printf("test2\n");
//printf(">>%s\n",temp);
      free(temp);
     // printf("test3\n");
      free(temp2);
     // printf("test4\n");

  return howmanytime;
}

int C_read_info::convert_syntax_srv_address(char *textoutput,char *text,char *svr_add_to_repaste,char *svr_addre)
{
  /* à¸?à¸±à¸?à¸?à¸±à¸? à¸?à¸µà¹?à¸?à¸°à¸?à¸³à¸?à¸²à¸£ à¸«à¸²à¸?à¸³à¸?à¸µà¹?à¸­à¸¢à¸¹à¹?à¹?à¸? svr_addre à¸?à¸µà¹?à¸­à¸¢à¸¹à¹?à¹?à¸? text à¹?à¸¥à¹?à¸§à¹?à¸?à¸?à¸?à¸µà¹?à¸?à¹?à¸§à¸¢  svr_add_to_repaste  à¹?à¸¥à¹?à¸§ return à¸?à¸¥à¸±à¸?à¹?à¸?à¸?à¸²à¸? textoutput

  */
     char *temp=NULL;
     char *temp2=NULL;
     int howmanytime=0,i=1,index=0,index_e=0;
     //char svr_addre[20]="[service-address]";
 //printf("test1\n");

     temp=(char*)calloc(strlen(text)+strlen(svr_addre)+100,sizeof(char));
    temp2=(char*)calloc(strlen(text)+strlen(svr_addre)+100,sizeof(char));
//printf("test1_1\n");
     strcpy(temp,text);
//printf("test1_2\n");
//printf("temp=%s\n",temp);
      howmanytime=cmptext(temp,svr_addre);
//printf("test1_3\n");
       while(i<=howmanytime){
        //  printf("loop1=%d\n",i);
	 index=indexOfs(temp,svr_addre,1);
	  //printf("loop2=%d\n",i);
         index_e=indexOfs_end(temp,svr_addre,1);
	  //printf("loop3=%d\n",i);
         // printf("be-->%s\n",temp);
	 //printf("%"sizeof()
	 //memset(temp2,'a',siz
	 insert_text(temp2,temp,svr_add_to_repaste,index,index_e);
	 //printf("loop4=%d\n",i);
          //printf("af-->%s\n\n",temp);
	 strcpy(temp,temp2);
	 //printf("loop5=%d\n",i);
	 // printf("%s,%s,%d,%d\n----------\n",temp,temp2,index,index_e);
	i++;
      }


      strcpy(textoutput,temp);
 //printf("trerr1\n");
 //printf("test2\n");
      free(temp);
     // printf("test3\n");
      free(temp2);
     // printf("test4\n");
 //printf("trerr\n");
  return 0;
}


bool C_read_info::chaek_attrs(char *attrwant,char* in_all_attr)
{   //printf("");
  if(in_all_attr==NULL){ return false;}
    char *tmp_att=NULL;
    char *tmp_all=NULL;
      tmp_att=(char *)calloc(strlen(in_all_attr)+1,sizeof(char));
      tmp_all=(char *)calloc(strlen(in_all_attr)+1,sizeof(char));
    snprintf(tmp_att,sizeof(tmp_att),"(%s=",attrwant);
    strcpy(tmp_all,in_all_attr);
    int index=0,index_end=0;
      index=indexOfs(tmp_all,tmp_att,1);
      index_end=indexOfs_end(tmp_all,tmp_att,1);
      free(tmp_att);
      free(tmp_all);
     if(index_end<=0||index==index_end){ return false;  }
     else{return true;}

   // free(tmp_att);
    //free(tmp_all);
}




int C_read_info::get_attrs(char *out,char *attrwant,char* in_all_attr)
{   /*attrwant must have length more than 2*/
  char *tmp_in=NULL;
  char *tmp_att=NULL;
  char *tmp_out=NULL;

  int index=0,index_end=0,i=0,j=0;

  if( strlen(in_all_attr)<= strlen(attrwant) ){return -1;}
 tmp_in=(char *)calloc(strlen(in_all_attr)+1,sizeof(char));
 tmp_att=(char *)calloc(strlen(in_all_attr)+1,sizeof(char));
 tmp_out=(char *)calloc(strlen(in_all_attr)+1,sizeof(char));
 // printf("\nede\n");
 //printf("xxxxxxxx1\n");
 //printf("----------------------------------------------------------1>%s\n",in_all_attr);
  strcpy(tmp_in,in_all_attr);
  sprintf(tmp_att,"(%s=",attrwant);
  //printf("\nede2\n");
  index=indexOfs(tmp_in,tmp_att,1);
  index_end=indexOfs_end(tmp_in,tmp_att,1);
 //if(index<=1){ return -1;}
//if(index_end>strlen(tmp_in)){printf("\nxx\n");}
//printf("xxxxxxxx2\n");
  // printf("\nindex-> %d  len %d \n",index_end,strlen(tmp_in));
  // printf("\ntmp_in %s\n",tmp_in);
 //printf("----------------------------------------------------------2>%s\n",in_all_attr);
 i=index_end;
 j=0;
  while(tmp_in[i]!=')')
  {
    tmp_out[j]=tmp_in[i];
     j++;
     i++;
  }
 tmp_out[j]='\0';
//printf("xxxxxxxx3\n");
   if(index_end<=1){ sprintf(tmp_out,'\0'); }
 strcpy(out,tmp_out);
 //printf("\ntmp_out=%s\n",tmp_out);

 //printf("----------------------------------------------------------3>%s\n",in_all_attr);
  free(tmp_out);
  free(tmp_in);
  free(tmp_att);
   //printf("----------------------------------------------------------4>%s\n",in_all_attr);
//printf("xxxxxxxx4\n");
 //free(tmp_in);
 //tmp_in=NULL;
// printf("\nede4\n");
if(index==index_end||(index==0&&index_end==0)){   return 0;}
//printf("xxxxxxxx5_2\n");
return 1;
}

int C_read_info::getToken2(char* out,char *in,int index_token)
{
 char *tmp_in=NULL;
  //char *tmp_att=NULL;
  char *tmp_out=NULL;

 // int index_end=0,i=0,j=0;
 // printf("X%sX\n",in);
    //if( strlen(in_all_attr)<= strlen(attrwant) ){return -1;}
 tmp_in=(char *)calloc(strlen(in)+1,sizeof(char));
// tmp_att=(char *)calloc(strlen(in)+1,sizeof(char));
 tmp_out=(char *)calloc(strlen(in)+1,sizeof(char));

  strcpy(tmp_in,in);
   
  int i=0,j=0;
  int token=0;
  bool tokenplus=false;
 //printf(";%s;\n",tmp_in);
    while(i<strlen(in)&&token<=index_token){
         /*  printf("test =%c\n",tmp_in[i]);*/
      while(i<strlen(in)&&(tmp_in[i]==' '||tmp_in[i]=='\t')){ /*printf("test1\n");*/  j=0; i++;}
      while(i<strlen(in)&&(tmp_in[i]!=' '&&tmp_in[i]!='\t')){ tokenplus=true;/*printf("test2\n");*/tmp_out[j]=tmp_in[i];   j++; i++;  }
       tmp_out[j]='\0';
        if(tokenplus==true){ token++;tokenplus=false;}
       //i++;
    }
   // printf("Y%sY\n",out);
//   printf("index %d tmp_out ;%s;\n",index_token,tmp_out);
    strcpy(out,tmp_out);
    free(tmp_out);
    free(tmp_in);

return 0;
}



bool C_read_info::check_token_2rd(char *line,char *check)
{ char tmp_token[MAX_VAL_STRING];
 char tmp_line[MAX_VAL_STRING];
   strcpy(tmp_line,line);

    if(strcmp(tmp_line,"")==0){ return false;}
  //tmp_token=(char *)calloc(strlen(line)+MAX_VAL_STRING,sizeof(char));

     getToken2(tmp_token,tmp_line,1);
    if(strcmp(tmp_token,"=")==0){ return true; }
    else{ return false;}
}





int C_read_info::convert_syntax_char(char *textoutput,char *text,char charecter,char *svr_addre)
{

     char *temp;
     char *temp2;
     int howmanytime=0,i=1,index=0,index_e=0;
     //char svr_addre[20]="[service-address]";


     temp=(char*)calloc(sizeof(char),strlen(text)+strlen(svr_addre)+100);
    temp2=(char*)calloc(sizeof(char),strlen(text)+strlen(svr_addre)+100);

     strcpy(temp,text);


      howmanytime=cmptext(temp,svr_addre);

       while(i<=howmanytime){

	 index=indexOfs(temp,svr_addre,1);
         index_e=indexOfs_end(temp,svr_addre,1);
         // printf("be-->%s\n",temp);
	 //+++insert_text(temp2,temp,svr_add_to_repaste,index,index_e);
	 insert_char(temp2,temp,charecter,index,index_e);
          //printf("af-->%s\n\n",temp);
	 strcpy(temp,temp2);
	 // printf("%s,%s,%d,%d\n----------\n",temp,temp2,index,index_e);
	i++;
      }
    // printf("%s\n",temp);
      strcpy(textoutput,temp);
 //printf("trerr1\n");
      free(temp);
      free(temp2);
 //printf("trerr\n");
  return 0;
}

void  C_read_info::insert_char(char *out,char *in,char in_char,int index,int index_e)
{
     char *temp;
     char *temp2;



     temp=(char*)calloc(sizeof(char),strlen(in)+100);
     temp2=(char*)calloc(sizeof(char),strlen(in)+100);

    int i=0,j=0;
    while(i<index-1){
       temp[i]=in[i];
    i++;
    }
    temp[i]='\0';
    i=index_e;
    j=0;
    while(i<strlen(in)){
         temp2[j]=in[i];
    i++; j++;
    }
    temp2[j]='\0';
 // printf("\ntmp1 =%s tmp2 =%s\n",temp,temp2);
   sprintf(out,"%s%c%s",temp,in_char,temp2);
   
   free(temp);
   free(temp2);
}






