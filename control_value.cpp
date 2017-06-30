#include "control_value.h"
#include "read_info.h"
C_read_info convert;
void C_control_value::init()
{
    begin_val_P=NULL;
    curr_val_P=NULL;
    tail_val_P=NULL;
    number_index=0;

}

bool C_control_value::add_new_val(char *val_name,int kind_of_val,int num)
{  /**/
    number_index++;

    if(begin_val_P==NULL){
        begin_val_P=(value *)malloc(sizeof(value));
        begin_val_P->index=number_index;
        strcpy(begin_val_P->name,val_name);
        begin_val_P->num=num;
        begin_val_P->int_or_str=1;
        begin_val_P->next=NULL;
        tail_val_P=begin_val_P;
    }
    else{
        tail_val_P->next=(value *)malloc(sizeof(value));
        tail_val_P=tail_val_P->next;
        tail_val_P->index=number_index;
        strcpy(tail_val_P->name,val_name);
        tail_val_P->num=num;
        tail_val_P->int_or_str=1;
        tail_val_P->next=NULL;

    }
    //printf("wdw\n");

    return true;
}

bool C_control_value::add_new_val(char *val_name,int kind_of_val,char *str)
{
    //printf("wdw\n");
    number_index++;

    if(begin_val_P==NULL){
        begin_val_P=(value *)malloc(sizeof(value));
        begin_val_P->index=number_index;
        strcpy(begin_val_P->name,val_name);
        //begin_val_P->num=num;
        strcpy(begin_val_P->stringv,str);
        begin_val_P->int_or_str=2;
        begin_val_P->next=NULL;
        tail_val_P=begin_val_P;
    }
    else{
        tail_val_P->next=(value *)malloc(sizeof(value));
        tail_val_P=tail_val_P->next;
        tail_val_P->index=number_index;
        strcpy(tail_val_P->name,val_name);
        //tail_val_P->num=num;
        strcpy(tail_val_P->stringv,str);
        tail_val_P->int_or_str=2;
        tail_val_P->next=NULL;

    }

    return true;
}

void C_control_value::printout_val()
{
    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if(tmpP->int_or_str==1){ printf("valname %s data_in %d  type int\n",tmpP->name,tmpP->num); }
        else if(tmpP->int_or_str==2){ printf("valname %s data_in :%s: type string\n",tmpP->name,tmpP->stringv); }
        tmpP= tmpP->next;
    }
}

int C_control_value::get_index(char *valname)
{
    //printf("val %s\n",valname);
    int index_tmp=-1;
    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if(0==strcmp(tmpP->name,valname)){ index_tmp=tmpP->index; }
        tmpP=tmpP->next;
    }

    //printf("val2 %s\n",valname);
    return index_tmp; //return index of value
}


int C_control_value::get_kind_by_index(int index)
{  int tmp_kind=-1;
    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if(tmpP->index==index){ tmp_kind=tmpP->int_or_str;  }
        tmpP=tmpP->next;
    }
    return tmp_kind;  /*return 1=int 2=string  0=not use  -1 = not have */
}

int  C_control_value::get_int_value(int index)
{
    int tmp_num=-1;
    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if((tmpP->index==index)&&(tmpP->int_or_str==1)){ tmp_num=tmpP->num;  }
        tmpP=tmpP->next;
    }
    return tmp_num;
}

void C_control_value::get_string_value(int index,char *out)
{
    //int tmp_num=-1;
    char tmp_str[MAX_VAL_STRING];
    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if((tmpP->index==index)&&(tmpP->int_or_str==2)){ strcpy(tmp_str,tmpP->stringv); }
        tmpP=tmpP->next;
    }
    strcpy(out,tmp_str);
    //return  &tmp_str[0];
}


void C_control_value::change_value(int index,int num)
{

    value *tmpP=NULL;
    tmpP=begin_val_P;

    while(tmpP!=NULL){
        if((tmpP->index==index)&&(tmpP->int_or_str==1)){ tmpP->num=num; }
        tmpP=tmpP->next;
    }
    // return tmp_num;

}

void C_control_value::change_value(int index,char *stringv)
{

    value *tmpP=NULL;
    tmpP=begin_val_P;

    char *tmptoken=NULL;
    char *linestr=NULL;
    //printf("change\n");
    //printf("stringv %s\n",stringv);
    tmptoken=(char *)calloc(strlen(stringv)+10,sizeof(char));
    linestr=(char *)calloc(strlen(stringv)+10,sizeof(char));
    sprintf(linestr,"%s",stringv);
    //printf("change2\n");
    int i=0,j=0;

    while(linestr[i]!='\"')
    {
        // printf(">%d %c;\n",i,linestr[i]);
        i++;
    }
    //printf("change3\n");
    i++; j=0;
    while(linestr[i]!='\"'&&linestr[i]!='\n')
    {  //printf(">%d %c; ",j,linestr);
        //printf("len(%d)\n",strlen(stringv)+10);
        tmptoken[j]=linestr[i];
        i++;  j++;
    }
    // printf("change3_0\n");
    tmptoken[j]='\0';
    //printf("change3_1\n");
    while(tmpP!=NULL){
        if((tmpP->index==index)&&(tmpP->int_or_str==2)){ sprintf(tmpP->stringv,"%s",tmptoken); }
        tmpP=tmpP->next;

    }
    //printf("change4\n");
    //printf("RR\n");
    free(tmptoken);
    free(linestr);
}

void C_control_value::change_value_for_function(int index,char *stringv)
{
    value *tmpP=NULL;
    tmpP=begin_val_P;
    //char *tmpin=NULL;
    //char *linestr=NULL;
    //printf("change\n");
    //printf("stringv %s\n",stringv);
    //tmpin=(char *)calloc(strlen(stringv)+10,sizeof(char));

    while(tmpP!=NULL){
        if((tmpP->index==index)&&(tmpP->int_or_str==2)){ sprintf(tmpP->stringv,"%s",stringv); }
        tmpP=tmpP->next;

    }

}



int C_control_value::freetail()
{
    value * previousP=NULL;



    previousP=begin_val_P;

    if(begin_val_P==NULL ||tail_val_P==NULL){/*number=0;*/ return 0;}

    else if(begin_val_P==tail_val_P){

        free(tail_val_P);
        tail_val_P=NULL;
        begin_val_P=NULL;


    }
    else{
        while(previousP->next!=tail_val_P){ previousP=previousP->next; }

        free(tail_val_P);
        tail_val_P=previousP;
        tail_val_P->next=NULL;
    }

    return 0;
}



int C_control_value::compare_value_with_string(char *reline,char *line)
{   /*check string if thai string is value name then replase it by data in val*/
    int i=0,j=0,len=strlen(line);
    char valname[MAX_VAL_NAME],valname2[MAX_VAL_NAME],replase_val[MAX_VAL_STRING];

    bool exitloopj=false;

    char *tmpline=NULL;
    tmpline=(char *)calloc(strlen(line)+MAX_VAL_STRING,sizeof(char));



    char *tmpline2=NULL;
    int lenstr=strlen(line)+MAX_VAL_STRING;
    tmpline2=(char *)calloc(strlen(line)+MAX_VAL_STRING,sizeof(char));
    strcpy(tmpline,line);
    strcpy(tmpline2,line);

    //printf("xxxxx-->%d %d\n",strlen(line)+1,strlen(tmpline ));
    //printf("test1\n");
    memset(valname,'\0',sizeof(valname));
    memset(valname2,'\0',sizeof(valname2));
    memset(replase_val,'\0',sizeof(replase_val));
    //printf("\n\ni have $ iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii len=%d\n\n",len);

    //printf("test2\n");
    while(i<len){
        if(tmpline[i]=='$'){


            j=1;
            exitloopj=false;
            //printf("==munber all of value =%d==\n",check_howmany_val());
            /*exitloopj dose not use*/
            while(j<=check_howmany_val()&&(exitloopj==false)){
                get_valname(valname,j);
                //printf("loop j=%d\n",j);
                //printf("numval=%d\n",check_howmany_val());
                int replase=-1;
                if(get_kind_by_index(j)==1){ sprintf(replase_val,"%d",get_int_value(j) );}
                else if(get_kind_by_index(j)==2){    get_string_value(j,replase_val); }
                sprintf(valname2,"[%s]",valname);
                //printf("%s -- %s\n",line,tmpline);
                //printf("len of tmpline2 =%d\n",lenstr);
                //printf("valuename=%s replased=%s by=%s\n",valname2,tmpline,replase_val);
                replase=convert.convert_syntax_replase(tmpline2,tmpline,replase_val,valname2);
                //printf("2 %s -- %s\n",line,tmpline);
                //printf("2numval=%d\n",check_howmany_val());
                strcpy(tmpline,tmpline2);
                //printf("3numval=%d\n",check_howmany_val());
                // printf("===============================tmpline2=%s->%d  %s\n",tmpline2,replase,valname2);
                memset(valname,'\0',sizeof(valname));
                memset(valname2,'\0',sizeof(valname2));
                memset(replase_val,'\0',sizeof(replase_val));
                //if(replase>0){/*printf("true\n");*/ exitloopj=true; }
                j++;
            }


        }
        i++;
    }

    //printf("===============================tmpline2=%s-\n",tmpline);
    //printf("test3\n");

    strcpy(reline,tmpline);
    //printf("%d %d->%s\n",strlen(reline),strlen(tmpline),tmpline);
    //printf("test4\n");
    free(tmpline);
    //printf("test5\n");
    free(tmpline2);
    //printf("test6\n");
    return 0;
}




int C_control_value::check_howmany_val()
{
    value *tmpP=NULL;
    tmpP=begin_val_P;
    int i=0;
    while(tmpP!=NULL){

        i++;
        tmpP=tmpP->next;
    }
    return i;
}

int  C_control_value::get_valname(char *re,int index)
{
    value *tmpP=NULL;
    tmpP=begin_val_P;
    int len=0;
    bool exitloop=false;
    while(tmpP!=NULL&&(exitloop==false)){
        //if(0==strcmp(tmpP->name,valname)){ index_tmp=tmpP->index; }
        if(tmpP->index==index){ sprintf(re,"%s",tmpP->name); len=strlen(tmpP->name);  exitloop=true; }
        tmpP=tmpP->next;
    }
    return len;
    //printf("val2 %s\n",valname);
    //return index_tmp; //return index of value
}















