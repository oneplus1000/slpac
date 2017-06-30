#include "syntax.h"
#include "read_info.h"

C_read_info converter;


void C_syntax::init()
{
    begin_line_P=NULL;
    tail_line_P=NULL;
    IdleProcess=true;
    care_end=0;
    endloop=false;
    values.init();
    inloop.init();
    g_num=0;
    myfile.init();
    chkelseif=false;
    check_tag_value=false;
    myorder.init();
}



int C_syntax::freetail()
{
    oneline *previousP=NULL;



    previousP=begin_line_P;

    if(begin_line_P==NULL ||tail_line_P==NULL){/*number=0;*/ return 0;}

    else if(begin_line_P==tail_line_P){

        free(tail_line_P);
        tail_line_P=NULL;
        begin_line_P=NULL;


    }
    else{
        while( previousP->next!=tail_line_P ){ 
            previousP=previousP->next; 
        }

        free(tail_line_P);
        tail_line_P=previousP;
        tail_line_P->next=NULL;
    }

    return 0;
}

int C_syntax::freeall()
{
    // oneline *previousP=NULL;
    //previousP=begin_line_P;
    myorder.freeall();
    while( begin_line_P!=NULL){
        freetail();
    }
    begin_line_P=NULL;
    tail_line_P=NULL;
    return 0;
}



void C_syntax::printAll()
{

    int i=1,j=0;
    oneline *tmpP=NULL;
    tmpP=begin_line_P;

    while(tmpP!=NULL){
        j=0;
        while(j<strlen(tmpP->line)+5)
        {
            printf("%c",tmpP->line[j]);  j++;
            if(tmpP->line[j]=='\0'){printf("_");}
        }

        printf("\n");
        //printf("index-> %d srv->:%s: len= %d\n",i,tmpP->line,strlen(tmpP->line));
        tmpP=tmpP->next;
        i++;
    }


    //printf("\nnow_number %d\n", memo.check_mem("$tong"));
    //free(tmpP);

}


void C_syntax::add_struct_line(char *in)
{
    if(begin_line_P==NULL){ 
        begin_line_P=(oneline *)malloc(sizeof(oneline));
        sprintf(begin_line_P->line,"%s",in);
        begin_line_P->next=NULL;
        tail_line_P=begin_line_P;
    }
    else{  
        tail_line_P->next=(oneline *)malloc(sizeof(oneline));
        tail_line_P=tail_line_P->next;
        sprintf(tail_line_P->line,"%s",in);
        tail_line_P->next=NULL;
    }
    //printAll();
}



void C_syntax::add_line(char *in_line)
{
    char *tmp_line=NULL;
    char *tmp_line2=NULL;

    tmp_line=(char *)calloc(strlen(in_line)+30,sizeof(char));
    tmp_line2=(char *)calloc(strlen(in_line)+30,sizeof(char));

    int i=0,j=0;



    while(in_line[i]==' '||in_line[i]=='\t'){i++;}


    while(i<=strlen(in_line)){  
        tmp_line[j]=in_line[i]; i++; j++;  
    }
    tmp_line[j]='\0';
    i=strlen(tmp_line)-1;


    while(i>=0&&(tmp_line[i]==' '||tmp_line[i]=='\t'||tmp_line[i]=='\n' ) )
    { 
        /* printf("i--\n");*/i--; 
    }

    tmp_line2[i+1]='\0';
    while(i>=0)
    {  
        tmp_line2[i]=tmp_line[i]; 
        i--;
    }

    if(0<=strlen(tmp_line2)){  
        add_struct_line(tmp_line2);  
    }
    free(tmp_line);
    free(tmp_line2);

}





int C_syntax::file_to_lines(char *fname)
{
    char linetmp[MAX_LINE];
    FILE * fp=NULL;
    fp=fopen(fname,"rb");

    if(fp==NULL){
        return -1;
    }


    while( fgets(linetmp,MAX_LINE,fp)!=NULL )
    {
        add_line(linetmp);
    }

    fclose(fp);
    return 0;
}
//====================================
void  C_syntax::proc_commend()
{
    oneline *tmpP=NULL;



    tmpP=begin_line_P;

    bool enablenext=true;
    int i=0;



    while(tmpP!=NULL)
    {    enablenext=true;

        printf(";%s;\n",tmpP->line);

        if(g_num>0){
            if(check_tag(tmpP->line)==true){  /*in tag slps*/
                if(converter.startWith2(tmpP->line,"//")==true){  }

                else if(converter.startWith2(tmpP->line,"Dim")==true){  if(IdleProcess==true){ Dim(tmpP->line); } }

                else if(converter.startWith2(tmpP->line,"If")==true){   if(IdleProcess==true){   If(tmpP->line);   }
                    else{ care_end++; }
                }

                else if(converter.startWith2(tmpP->line,"Elseif")==true){   if(IdleProcess==false){ if(care_end<=0){ IdleProcess=true; }
                        //else{ care_end--; }
                    }

                    if(IdleProcess==true){  Elseif(tmpP->line);   }
                }

                else if(converter.startWith2(tmpP->line,"Else")==true){  if(IdleProcess==false){ if(care_end<=0){ IdleProcess=true;}
                        // else{ care_end--; }
                    }

                    if(IdleProcess==true){    Else();  }
                }

                else if(converter.startWith2(tmpP->line,"Println")==true){  if(IdleProcess==true){  printOut2(tmpP->line); /* printf("tmp-> %s\n",tmpP->line);*/} }
                else if(converter.startWith2(tmpP->line,"Printout")==true){  if(IdleProcess==true){  printOut3(tmpP->line); /* printf("tmp-> %s\n",tmpP->line);*/} }
                else if(converter.startWith2(tmpP->line,"Fprintln")==true){  if(IdleProcess==true){  FprintOut(tmpP->line,NEWLINE); /* printf("tmp-> %s\n",tmpP->line);*/} }
                else if(converter.startWith2(tmpP->line,"Fprintout")==true){  if(IdleProcess==true){  FprintOut(tmpP->line,SAMELINE); /* printf("tmp-> %s\n",tmpP->line);*/} }

                else if(converter.startWith2(tmpP->line,"Endif")==true){  if(IdleProcess==false){ if(care_end<=0){ IdleProcess=true; chkelseif=true;}
                        else{ care_end--; }
                    }
                }

                else if(converter.startWith2(tmpP->line,"Loop")==true){    if(IdleProcess==true){/* printf("x\n");*/ Loop(tmpP->line,tmpP);  }
                    else{/* printf("pluss %d\n",care_end);*/IdleProcess=false; care_end++; }

                }
                else if(converter.startWith2(tmpP->line,"Endloop")==true){  if(IdleProcess==true){ endloop=true; tmpP=inloop.return_P(); enablenext=false; }
                    else if(IdleProcess==false){  if(care_end<=0){ /*printf("new\n"); */IdleProcess=1;}else{ care_end--;} }

                }
                else if(converter.startWith2(tmpP->line,"Ordersrv_addstr(URL,")==true){  if(IdleProcess==true){  ordersrvs_addstr_url(tmpP->line); } }
                else if(converter.startWith2(tmpP->line,"Ordersrv_addstr(\"")==true){  if(IdleProcess==true){  ordersrvs_addstr(tmpP->line); } }
                else if(converter.startWith2(tmpP->line,"Ordersrv_addstring(")==true){  if(IdleProcess==true){  ordersrvs_addstring(tmpP->line); } }
                else if(converter.check_token_2rd(tmpP->line,"=")==true){   if(IdleProcess==true){  changeValue(tmpP->line);  } }
                else if(strcmp(tmpP->line,"Nextsrv()")==0){ if(IdleProcess==true){  if(g_num>0){ myll->next_curr();}  } }
                else if(strcmp(tmpP->line,"Resetsrv()")==0){ if(IdleProcess==true){ myll->reset_curr(); } }
                else if(strcmp(tmpP->line,"Ordersrv_ordernow()")==0){  if(IdleProcess==true){  ordersrvs_now(); } }
                else if(strcmp(tmpP->line,"Ordersrv_ordernow(URL)")==0){  if(IdleProcess==true){  ordersrvs_now_url(); } }
                else if(converter.startWith2(tmpP->line,"Ordersrv_ordernow(\"")==true){  if(IdleProcess==true){  ordersrvs_now_att(tmpP->line); } }
            }//end if(check_tag(tmpP->line)==true)
            else{   /*out side tag slps*/

                if(IdleProcess==true){  Fprint_outsidetag(tmpP->line); }
            }
        }

        if(enablenext==true){   tmpP=tmpP->next;    i++;}

    }//end proc_commend()



}


void C_syntax::ordersrvs_addstr_url(char *line)
{
    //printf("xxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    char tmp_att1[500];
    char tmp_att2[500];
    char tmp_att3[500];

    char arg1[200];
    char arg2[200];
    char arg3[200];
    //char tmp_attstr[200];
    //char tmp_attscore[200];
    int tmp_score=0;
    sscanf(line,"Ordersrv_addstr(URL,\"%s",tmp_att1);
    printf("=========<>%s\n",tmp_att1);
    int  i=0;
    while(tmp_att1[i]!='\"'){
        arg1[i]=tmp_att1[i];
        i++;
    }
    arg1[i]='\0';
    printf("arg1=%s<=\n",arg1);

    //sprintf(tmp_att2,"%s",index(tmp_att1,',')+2);
    /*i=0;
    while(tmp_att2[i]!=')'){
        arg2[i]=tmp_att2[i];
        i++;
    }
    arg2[i]='\0';*/


    sprintf(tmp_att2,"%s",index(tmp_att1,',')+1);
    i=0;
    while(tmp_att2[i]!=')'){
        arg3[i]=tmp_att2[i];
        i++;
    }
    arg3[i]='\0';
    printf("arg2=%s<=\n",arg3);

    // printf("--------->%s--%s=%s\n",arg1,arg2,arg3);
    myorder.add(arg1,atoi(arg3));

    ordersrvs_now_url();
    //ordersrvs_now_att(char *line);
    myorder.freeall();
}




void C_syntax::ordersrvs_addstr(char *line)
{
    //printf("xxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    char tmp_att1[500];
    char tmp_att2[500];
    char tmp_att3[500];

    char arg1[200];
    char arg2[200];
    char arg3[200];
    //char tmp_attstr[200];
    //char tmp_attscore[200];
    int tmp_score=0;
    sscanf(line,"Ordersrv_addstr(\"%s",tmp_att1);

    int  i=0;
    while(tmp_att1[i]!='\"'){
        arg1[i]=tmp_att1[i];
        i++;
    }
    arg1[i]='\0';

    sprintf(tmp_att2,"%s",index(tmp_att1,',')+2);
    i=0;
    while(tmp_att2[i]!='\"'){
        arg2[i]=tmp_att2[i];
        i++;
    }
    arg2[i]='\0';


    sprintf(tmp_att3,"%s",index(tmp_att2,',')+1);
    i=0;
    while(tmp_att3[i]!=')'){
        arg3[i]=tmp_att3[i];
        i++;
    }
    arg3[i]='\0';


    printf("--------->%s--%s=%s\n",arg1,arg2,arg3);
    myorder.add(arg2,atoi(arg3));

    C_link_list tmp;
    srvtype_ll *tmp_cur=NULL;
    tmp_cur=myll->curr;//,sizeof(*srvtype_ll));
    memcpy(&tmp,myll,sizeof(C_link_list));
    tmp.reset_curr();
    i=0;
    if(tmp.curr!=NULL){
        while(tmp.curr!=tmp.tail->nextdoor){
            //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
            char tmpout2[MAX_A_SERVICE_ATT];
            char tmpout[MAX_A_SERVICE_ATT];
            sprintf(tmpout2,"%s",tmp.curr->service_attr);
            converter.get_attrs(tmpout,arg1,tmpout2);  //��� att ���
            tmp.curr->score=tmp.curr->score+ordersrvs_now_check2(tmpout,myorder);
            //tmp.curr->score=(tmp.curr->score)+ordersrvs_now_check(tmp.curr->service_url,myorder);
            //printf("\n%d\n",i);
            i++;
            tmp.curr=tmp.curr->nextdoor;
        }
        bool chk=true;
        while(chk==true){
            chk=false;
            tmp.reset_curr();
            while(tmp.curr!=tmp.tail){
                if(tmp.curr->score < tmp.curr->nextdoor->score){
                    //printf("===========>before%d  %d",tmp.curr->score,tmp.curr->nextdoor->score);
                    ordersrvs_swap(tmp.curr,tmp.curr->nextdoor);
                    //printf("\n===========>after %d  %d\n",tmp.curr->score,tmp.curr->nextdoor->score);
                    chk=true;
                }
                tmp.curr=tmp.curr->nextdoor;
            }
            //tmp.curr=tmp.curr->nextdoor;
            //printf("\n====chk=%d\n",chk);
        }


    }
    //ordersrvs_now_att(char *line);
    myorder.freeall();
}

void C_syntax::ordersrvs_now_att(char *line){
    char *tmpline=NULL;
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    sprintf(tmpline,"%s",line);
    char *agv=NULL;
    agv=strchr(tmpline,'\"');
    agv++;
    //printf("->%s",agv);
    char *agvtmp=NULL;
    agvtmp=(char *)calloc(strlen(line)+1,sizeof(char));
    while((*agv)!='\0'&&(*agv)!='\"'){
        //agvtmp=strcat(agvtmp,agv,2);
        sprintf(agvtmp,"%s%c",agvtmp,*agv);
        agv++;
    }
    //printf("-8>%s<-\n",agvtmp);

    //char tmpout2[MAX_A_SERVICE_ATT];

    //printf("out-->%s<-%s<-",tmpout,tmpout2);

    C_link_list tmp;
    srvtype_ll *tmp_cur=NULL;
    tmp_cur=myll->curr;//,sizeof(*srvtype_ll));
    memcpy(&tmp,myll,sizeof(C_link_list));
    tmp.reset_curr();
    int i=0;
    if(tmp.curr!=NULL){
        while(tmp.curr!=tmp.tail->nextdoor){
            //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
            char tmpout2[MAX_A_SERVICE_ATT];
            char tmpout[MAX_A_SERVICE_ATT];
            sprintf(tmpout2,"%s",tmp.curr->service_attr);
            converter.get_attrs(tmpout,agvtmp,tmpout2);  //��� att ���
            tmp.curr->score=ordersrvs_now_check(tmpout,myorder);
            //tmp.curr->score=(tmp.curr->score)+ordersrvs_now_check(tmp.curr->service_url,myorder);
            //printf("\n%d\n",i);
            i++;
            tmp.curr=tmp.curr->nextdoor;
        }
        bool chk=true;
        while(chk==true){
            chk=false;
            tmp.reset_curr();
            while(tmp.curr!=tmp.tail){
                if(tmp.curr->score < tmp.curr->nextdoor->score){
                    //printf("===========>before%d  %d",tmp.curr->score,tmp.curr->nextdoor->score);
                    ordersrvs_swap(tmp.curr,tmp.curr->nextdoor);
                    //printf("\n===========>after %d  %d\n",tmp.curr->score,tmp.curr->nextdoor->score);
                    chk=true;
                }
                tmp.curr=tmp.curr->nextdoor;
            }
            //tmp.curr=tmp.curr->nextdoor;
            //printf("\n====chk=%d\n",chk);
        }


    }
    free(tmpline);
}

void C_syntax::ordersrvs_now_url()
{
    C_link_list tmp;
    srvtype_ll *tmp_cur=NULL;
    tmp_cur=myll->curr;//,sizeof(*srvtype_ll));
    memcpy(&tmp,myll,sizeof(C_link_list));

    tmp.reset_curr();

    //tmp.curr->score=0;
    int i=0;
    //printf("\n%d\n",i);
    if(tmp.curr!=NULL){
        while(tmp.curr!=tmp.tail->nextdoor){
            //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
            tmp.curr->score=ordersrvs_now_check(tmp.curr->service_url,myorder);
            //tmp.curr->score=(tmp.curr->score)+ordersrvs_now_check(tmp.curr->service_url,myorder);
            //printf("\n%d\n",i);
            i++;
            tmp.curr=tmp.curr->nextdoor;
        }
        bool chk=true;

        while(chk==true){
            chk=false;
            tmp.reset_curr();
            while(tmp.curr!=tmp.tail){

                if(tmp.curr->score < tmp.curr->nextdoor->score){
                    //printf("===========>before%d  %d",tmp.curr->score,tmp.curr->nextdoor->score);
                    ordersrvs_swap(tmp.curr,tmp.curr->nextdoor);
                    //printf("\n===========>after %d  %d\n",tmp.curr->score,tmp.curr->nextdoor->score);
                    chk=true;
                }
                tmp.curr=tmp.curr->nextdoor;
            }
            //tmp.curr=tmp.curr->nextdoor;
            //printf("\n====chk=%d\n",chk);
        }
    }

}


void C_syntax::ordersrvs_now_url2()
{
    C_link_list tmp;
    srvtype_ll *tmp_cur=NULL;
    tmp_cur=myll->curr;//,sizeof(*srvtype_ll));
    memcpy(&tmp,myll,sizeof(C_link_list));

    tmp.reset_curr();

    //tmp.curr->score=0;
    int i=0;
    //printf("\n%d\n",i);
    if(tmp.curr!=NULL){
        while(tmp.curr!=tmp.tail->nextdoor){
            //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
            tmp.curr->score=tmp.curr->score+ordersrvs_now_check2(tmp.curr->service_url,myorder);
            //tmp.curr->score=(tmp.curr->score)+ordersrvs_now_check(tmp.curr->service_url,myorder);
            //printf("\n%d\n",i);
            i++;
            tmp.curr=tmp.curr->nextdoor;
        }
        bool chk=true;

        while(chk==true){
            chk=false;
            tmp.reset_curr();
            while(tmp.curr!=tmp.tail){

                if(tmp.curr->score < tmp.curr->nextdoor->score){
                    //printf("===========>before%d  %d",tmp.curr->score,tmp.curr->nextdoor->score);
                    ordersrvs_swap(tmp.curr,tmp.curr->nextdoor);
                    //printf("\n===========>after %d  %d\n",tmp.curr->score,tmp.curr->nextdoor->score);
                    chk=true;
                }
                tmp.curr=tmp.curr->nextdoor;
            }
            //tmp.curr=tmp.curr->nextdoor;
            //printf("\n====chk=%d\n",chk);
        }
    }

}

void C_syntax::ordersrvs_now(){

    C_link_list tmp;
    srvtype_ll *tmp_cur=NULL;
    tmp_cur=myll->curr;//,sizeof(*srvtype_ll));


    memcpy(&tmp,myll,sizeof(C_link_list));

    tmp.reset_curr();

    //tmp.curr->score=0;
    int i=0;
    //printf("\n%d\n",i);
    if(tmp.curr!=NULL){
        //printf("-------------------------------->0\n");
        while(tmp.curr!=tmp.tail->nextdoor){

            //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
            tmp.curr->score=ordersrvs_now_check(tmp.curr->service_attr,myorder);
            tmp.curr->score=(tmp.curr->score)+ordersrvs_now_check(tmp.curr->service_url,myorder);
            //printf("\n%d\n",i);
            i++;
            tmp.curr=tmp.curr->nextdoor;
        }

        //printf("=========:::::>%d\n",ordersrvs_now_check(tmp.curr->service_attr,myorder));
        //printf("\n%d\n",i);
        bool chk=true;
        //printf("-------------------------------->1\n");
        while(chk==true){
            chk=false;
            tmp.reset_curr();
            while(tmp.curr!=tmp.tail){

                if(tmp.curr->score < tmp.curr->nextdoor->score){
                    //printf("===========>before%d  %d",tmp.curr->score,tmp.curr->nextdoor->score);
                    ordersrvs_swap(tmp.curr,tmp.curr->nextdoor);
                    //printf("\n===========>after %d  %d\n",tmp.curr->score,tmp.curr->nextdoor->score);
                    chk=true;
                }
                tmp.curr=tmp.curr->nextdoor;
            }
            //tmp.curr=tmp.curr->nextdoor;
            //printf("\n====chk=%d\n",chk);
        }
    }
    //printf("-------------------------------->2\n");
}

void C_syntax::ordersrvs_swap(srvtype_ll *s1,srvtype_ll *s2){
    char tmp_service_url[MAX_SERVICE_TYPE_ARRAY ];
    char tmp_service_attr[MAX_A_SERVICE_ATT];
    int tmp_score=0;
    sprintf(tmp_service_url,"%s",s1->service_url);
    sprintf(tmp_service_attr,"%s",s1->service_attr);
    tmp_score=s1->score;

    sprintf(s1->service_url,"%s",s2->service_url);
    sprintf(s1->service_attr,"%s",s2->service_attr);
    s1->score=s2->score;

    sprintf(s2->service_url,"%s",tmp_service_url);
    sprintf(s2->service_attr,"%s",tmp_service_attr);
    s2->score=tmp_score;
}



int C_syntax::ordersrvs_now_check(char att[MAX_A_SERVICE_ATT],c_order od){
    //printf("\n-------------------------------------------->%d\n", converter.cmptext("ccaabbccddeeffcc","cc"));
    od.cur=NULL;
    int re=0;
    int i=0;

    //printf("\n---------------xx----------------------------->%d\n",od.g_num);

    while(i<od.g_num){
        //re=converter.cmptext(att,od.cur->text);
        char tmp[MAX_A_SERVICE_ATT];
        //strcpy(tmp,od.cur->text);
        order myorder=od.get();
        //printf("\n-------------------------------------------->%s\n",myorder.text);
        re=re+(converter.cmptext(att,myorder.text)*myorder.score);
        i++;
    }
    return re;
}


int C_syntax::ordersrvs_now_check2(char att[MAX_A_SERVICE_ATT],c_order od){
    //printf("\n-------------------------------------------->%d\n", converter.cmptext("ccaabbccddeeffcc","cc"));
    od.cur=NULL;
    int re=0;
    int i=0;

    //printf("\n---------------xx----------------------------->%d\n",od.g_num);

    while(i<od.g_num){
        //re=converter.cmptext(att,od.cur->text);
        char tmp[MAX_A_SERVICE_ATT];
        //strcpy(tmp,od.cur->text);
        order myorder=od.get();
        //printf("\n-------------------------------------------->%s\n",myorder.text);
        //re=re+(converter.cmptext(att,myorder.text)*myorder.score);
        re_comp(myorder.text);
        if(re_exec(att)==1){
            re=re+(1*myorder.score);
        }
        i++;
    }
    return re;
}



bool C_syntax::ordersrvs_addstring(char *line)  
{	char *tmp=NULL;
    char *tmp_argv1=NULL;
    char *tmp_argv2=NULL;
    tmp=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp_argv1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp_argv2=(char *)calloc(strlen(line)+1,sizeof(char));
    strcpy(tmp,line);
    int i=0;
    while(i<strlen(line)){

        if(tmp[i]=='\"'){
            break;
        }
        i++;
    }
    int j=0;
    i++;
    while(i<strlen(line)){

        if(tmp[i]=='\"'){
            break;
        }
        else{
            tmp_argv1[j]=tmp[i];
            j++;
        }
        i++;
    }
    //printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s\n",tmp_argv1);

    //printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>len%d\n",strlen(line));
    while(i<strlen(line)){

        if(tmp[i]==','){
            break;
        }
        i++;
    }
    j=0;
    i++;
    while(i<strlen(line)){

        if(tmp[i]==')'){
            break;
        }
        else{
            tmp_argv2[j]=tmp[i];
            j++;
        }
        i++;
    }
    myorder.add(tmp_argv1,atoi(tmp_argv2));
    //printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s\n",tmp_argv2);
}


void C_syntax::Dim(char *line)
{
    char *tmp=NULL;
    char *tmp2=NULL;
    char *tmp3=NULL;
    tmp=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp2=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp3=(char *)calloc(strlen(line)+1,sizeof(char));
    //printf("dim =\n");
    strcpy(tmp,line);
    converter.getToken2(tmp2,tmp,1);
    converter.getToken2(tmp3,tmp,2);
    printf("add new value name=%s\n",tmp2);
    if(strcmp(tmp3,"integer")==0){/*printf("integer\n");*/ values.add_new_val(tmp2,1,00); }
    else if(strcmp(tmp3,"string")==0){/*printf("integer\n");*/ values.add_new_val(tmp2,1,""); }
    // converter.getToken(tmp3,tmp,2);

    // printf("tmp2 :%s: tmp3:%s:",tmp2,tmp3);
    free(tmp);
    free(tmp2);
    free(tmp3);

}

void C_syntax::changeValue(char *line)
{   char *tmp_line=NULL;
    char *tmp1=NULL;
    char *tmp2=NULL;
    char *tmp3=NULL;
    char *tmp4=NULL;

    tmp_line=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp2=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp3=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp4=(char *)calloc(strlen(line)+1,sizeof(char));

    sprintf(tmp_line,"%s",line);

    converter.getToken2(tmp1,line,0);
    converter.getToken2(tmp2,line,1);
    converter.getToken2(tmp3,line,2);
    converter.getToken2(tmp4,line,3);
    char tmp_val[MAX_VAL_STRING];

    if(converter.startWith(tmp1,"$")==1){
        if(values.get_kind_by_index(values.get_index(tmp1))==1){/*value is int */

            if(strcmp(tmp2,"=")==0&&( strcmp(tmp4,"+")==0||strcmp(tmp4,"/")==0||strcmp(tmp4,"*")==0||strcmp(tmp4,"-")==0 )){
                values.change_value(values.get_index(tmp1),operation(line));


            }

            else{
                if(converter.itIsInterger(tmp3)==1){ values.change_value(values.get_index(tmp1),atoi(tmp3)); }
                else if(strcmp(tmp3,"Numofsrv()")==0){      values.change_value(values.get_index(tmp1),g_num );  }
                else if(converter.startWith2(tmp3,"Chkatt(")==true){  values.change_value(values.get_index(tmp1),Checkatt(tmp_line));  printf("XX\n"); }
                else{}
            }

        }//End if(values.get_kind_by_index(values.get_index(tmp1))==1)

        else if(values.get_kind_by_index(values.get_index(tmp1))==2){/*value is string */

            if(converter.startWith(tmp3,"\"")==1){values.change_value(values.get_index(tmp1),tmp_line);  }

            else if(strcmp(tmp3,"Server-address()")==0){
                //myll->printf_all();
                printf("before---get-----------------------\n");
                myll->printf_all();
                myll->get_curr_addr(tmp_val);
                printf("after-----get---------------------\n");
                values.change_value_for_function(values.get_index(tmp1),tmp_val);

            }
            else if(converter.startWith2(tmp3,"Getatt(")==true){

                Get_att(tmp_val,tmp_line);

                values.change_value_for_function(values.get_index(tmp1),tmp_val);

            }

        }//End else if(values.get_kind_by_index(values.get_index(tmp1))==2)

    }//End if(converter.startWith(tmp1,"$")==1)

    free(tmp_line);

    free(tmp1);

    free(tmp2);

    free(tmp3);

    free(tmp4);

    //printf("wew2\n");
}



void C_syntax::Else()
{
    if(chkelseif==false){IdleProcess=false;}

}

void C_syntax::Elseif(char *line)
{   //printf("e1\n");

    //if(IdleProcess==false&&chkelseif=true ){}
    if(chkelseif==true){
        if(check(line)==true){ chkelseif=false; }
        else{ IdleProcess=false;  }
    }
    else if(chkelseif==false){IdleProcess=false;}
    //if(){}

}

void C_syntax::If(char *line)
{   //printf("e1\n");
    chkelseif=true;

    if(check(line)==true){ chkelseif=false; }
    else{ IdleProcess=false;  }



}






bool C_syntax::test_int_int(int num1,char *sym,int num2)
{
    if(strcmp(sym,"==")==0){ if(num1==num2){return true;}
        else{return false;}
    }
    else if(strcmp(sym,">=")==0){if(num1>=num2){return true;}
        else{return false;}
    }
    else if(strcmp(sym,"<=")==0){if(num1<=num2){return true;}
        else{return false;}
    }
    else if(strcmp(sym,"!=")==0){if(num1!=num2){return true;}
        else{return false;}
    }
    else if(strcmp(sym,"<")==0){if(num1<num2){return true;}
        else{return false;}
    }
    else if(strcmp(sym,">")==0){if(num1>num2){return true;}
        else{return false;}
    }
    else {return false; }

}

bool C_syntax::test_char_char(char *str1,char *sym,char *str2)
{
    if(strcmp(sym,"==")==0){
        if(strcmp(str1,str2)==0){return true;}
        else{return false; }
    }
    else if(strcmp(sym,"!=")==0){
        if(strcmp(str1,str2)!=0){return true;}
        else{return false; }
    }
    else{return false; }
}


//void C_syntax::Loop(char *line,oneline *tmp)
int C_syntax::Loop(char *line,oneline *tmpP)
{ char *tmptoken1=NULL;

    char *tmptoken2=NULL;
    //char *tmptoken3=NULL;
    int tmp_re=0;

    //int check1=0,check2=0;   // check ==1 is integer     check ==2 is string    check==3 is ��า���ัว
    // int symbol=0;    //  symbol=1 "=="    2 symbol ">"  3 symbol ">="  4 symbol "!="  5 symbol "<"  6 symbol "<="

    tmptoken1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmptoken2=(char *)calloc(strlen(line)+1,sizeof(char));

    converter.getToken2(tmptoken1,line,1);
    converter.getToken2(tmptoken2,line,2);

    if( strcmp(tmptoken2,">")==0||strcmp(tmptoken2,"<")==0||strcmp(tmptoken2,"==")==0||strcmp(tmptoken2,">=")==0||strcmp(tmptoken2,"<=")==0||strcmp(tmptoken2,"!=")==0){
        if(endloop==false){
            inloop.push(0 ,0,tmpP);

        }
        else if(endloop==true){endloop=false;}


        if(check(line)!=true){  IdleProcess=false;  inloop.pop_free();}
        else{ IdleProcess=1;  inloop.reduce_num();}

    }

    else if(converter.startWith(tmptoken1,"$")==1){
        if(endloop==false){
            inloop.push(  values.get_int_value(values.get_index(tmptoken1)) ,0,tmpP);

        }
        else if(endloop==true){endloop=false;}


        if(inloop.return_num()<=0){/*printf("\ncxc1\n");*/ IdleProcess=0;  inloop.pop_free();}
        else{ /*printf("\ncxc\n");*/ IdleProcess=1;  inloop.reduce_num(); }
        // printf("->%d\n",inlloop.return_num());

    }
    else if(converter.startWith(tmptoken1,"Numofsrv()")==1){
        if(endloop==false){
            inloop.push( g_num ,0,tmpP);

        }
        else if(endloop==true){endloop=false;}


        if(inloop.return_num()<=0){/*printf("\ncxc1\n");*/ IdleProcess=0;  inloop.pop_free();}
        else{ /*printf("\ncxc\n");*/ IdleProcess=1;  inloop.reduce_num(); }
        // printf("->%d\n",inloop.return_num());

    }
    else if(converter.itIsInterger(tmptoken1)==1){
        if(endloop==false){ /*printf("tmp %d\n", atoi(tmptoken1) );*/ inloop.push( atoi(tmptoken1) ,0,tmpP);
        }
        else if(endloop==true){endloop=false;}

        if(inloop.return_num()<=0){/*printf("\ncxc1\n");*/ IdleProcess=0;  inloop.pop_free();}
        else{ /*printf("\ncxc\n");*/ IdleProcess=1;  inloop.reduce_num(); }
    }



    free(tmptoken1);

    free(tmptoken2);
    //free(tmptoken3);

    //tmp_re =1  loop  tmp_re=0 out
    return tmp_re;
}



bool C_syntax::check(char *line)
{
    char *tmptoken1=NULL;
    char *tmptoken2=NULL;
    char *tmptoken3=NULL;
    char outstring[MAX_VAL_STRING];
    char outstring2[MAX_VAL_STRING];
    bool returnvale=true;
    tmptoken1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmptoken2=(char *)calloc(strlen(line)+1,sizeof(char));
    tmptoken3=(char *)calloc(strlen(line)+1,sizeof(char));
    converter.getToken2(tmptoken1,line,1);
    converter.getToken2(tmptoken2,line,2);
    converter.getToken2(tmptoken3,line,3);


    if(converter.startWith(tmptoken1,"$")==1){
        // printf("e3\n");
        if(values.get_kind_by_index(values.get_index(tmptoken1))==1){
            if(converter.itIsInterger(tmptoken3)==1){
                if(true==test_int_int(values.get_int_value(values.get_index(tmptoken1)),tmptoken2,atoi(tmptoken3)) ){returnvale=true; }
                else{ returnvale=false; }
            }
            else if(converter.startWith(tmptoken3,"$")==1){
                if(true==test_int_int(values.get_int_value(values.get_index(tmptoken1)),tmptoken2,values.get_int_value(values.get_index(tmptoken3))) ){returnvale=true; }
                else{ returnvale=false; }
            }
            //else if(){}
            else{}

        }//end if(values.get_kind_by_index(values.get_index(tmptoken1))==1)
        else if(values.get_kind_by_index(values.get_index(tmptoken1))==2){
            if(converter.startWith(tmptoken3,"\"")==1){
                values.get_string_value(values.get_index(tmptoken1),outstring);
                if(test_char_char(outstring,tmptoken2,tmptoken3)==true){ returnvale=true; }
                else{ returnvale=false; }
            }
            else if(converter.startWith(tmptoken3,"$")==1){
                values.get_string_value(values.get_index(tmptoken1),outstring);
                values.get_string_value(values.get_index(tmptoken3),outstring2);
                if(test_char_char(outstring,tmptoken2,outstring2)==true){ returnvale=true; }
                else{ returnvale=false; }
            }
        }
    }//end if(converter.startWith(tmptoken1,"$")==1)

    else if(converter.startWith2(tmptoken3,"$")==true){

        if(values.get_kind_by_index(values.get_index(tmptoken3))==1){
            if(converter.itIsInterger(tmptoken1)==1){
                if(true==test_int_int(values.get_int_value(atoi(tmptoken1)),tmptoken2,values.get_index(tmptoken3)) ){IdleProcess=true; }
                else{ IdleProcess=false; }
            }
            else if(converter.startWith2(tmptoken1,"$")==true){
                if(true==test_int_int(values.get_int_value(values.get_index(tmptoken1)),tmptoken2,values.get_int_value(values.get_index(tmptoken3))) ){IdleProcess=true; }
                else{ IdleProcess=false; }
            }
            //else if(){}
            else{IdleProcess=false;}

        }//end if(values.get_kind_by_index(values.get_index(tmptoken1))==1)
        else if(values.get_kind_by_index(values.get_index(tmptoken3))==2){
            if(converter.startWith2(tmptoken1,"\"")==true){
                values.get_string_value(values.get_index(tmptoken3),outstring);
                if(test_char_char(tmptoken1,tmptoken2,outstring)==true){ IdleProcess=true; }
                else{ IdleProcess=false; }
            }
            else if(converter.startWith2(tmptoken3,"$")==true){
                values.get_string_value(values.get_index(tmptoken1),outstring);
                values.get_string_value(values.get_index(tmptoken3),outstring2);
                if(test_char_char(outstring,tmptoken2,outstring2)==true){ IdleProcess=true; }
                else{ IdleProcess=false; }
            }
        }



    }//end else if(converter.startWith2(tmptoken3,"$")==true)


    free(tmptoken1);
    free(tmptoken2);
    free(tmptoken3);
    return returnvale;
}

int  C_syntax::operation(char *line)
{
    char *tmptoken3=NULL;
    char *tmptoken4=NULL;
    char *tmptoken5=NULL;

    tmptoken3=(char *)calloc(strlen(line)+1,sizeof(char));
    tmptoken4=(char *)calloc(strlen(line)+1,sizeof(char));
    tmptoken5=(char *)calloc(strlen(line)+1,sizeof(char));

    converter.getToken2(tmptoken3,line,2);
    converter.getToken2(tmptoken4,line,3);
    converter.getToken2(tmptoken5,line,4);
    int tmp3=0,tmp5=0,revalue=0;

    if(converter.startWith(tmptoken3,"$")==1){
        tmp3=values.get_int_value(values.get_index(tmptoken3));
    }
    else if(converter.itIsInterger(tmptoken3)==1){ tmp3=atoi(tmptoken3);}

    if(converter.startWith(tmptoken5,"$")==1){
        tmp5=values.get_int_value(values.get_index(tmptoken5));
    }
    else if(converter.itIsInterger(tmptoken5)==1){ tmp5=atoi(tmptoken5);}


    if(strcmp(tmptoken4,"+")==0){
        revalue=tmp3+tmp5;
    }
    else if(strcmp(tmptoken4,"-")==0){
        revalue=tmp3-tmp5;
    }
    else if(strcmp(tmptoken4,"*")==0){
        revalue=tmp3*tmp5;
    }
    else if(strcmp(tmptoken4,"/")==0){
        if(tmp5!=0){revalue=tmp3/tmp5; }
        else{printf("number device by zero\n");  revalue=0; }
    }

    free(tmptoken3);
    free(tmptoken4);
    free(tmptoken5);
    return revalue;
}



void  C_syntax::change_for_printOut(char *out,char *line)
{

    char tmpline[MAX_VAL_STRING];
    char tmpout[MAX_VAL_STRING];
    char tmpword[MAX_VAL_STRING];
    char tmpword2[MAX_VAL_STRING];
    memset(tmpline,'\0',sizeof(tmpline));
    memset(tmpout,'\0',sizeof(tmpout));
    memset(tmpword,'\0',sizeof(tmpword));
    memset(tmpword2,'\0',sizeof(tmpword2));

    char outstring[MAX_VAL_STRING*2];
    int index=0,indexend=0,num=0;

    strcpy(tmpline,line);

    num=converter.cmptext(tmpline,"[$");

    int i=0,word=0,wordj=0;
    while(i<num){
        index=converter.indexOfs(tmpline,"[$",i+1);
        indexend=converter.indexOfs_end(tmpline,"[$",i+1);
        word=index;

        wordj=0;
        while(tmpline[word]!=']'&&word<strlen(tmpline)){
            //printf("h\n");
            tmpword[wordj]=tmpline[word];
            wordj++;
            word++;
        }
        tmpword[wordj]='\0';

        sprintf(tmpword2,"[%s]",tmpword);

        if(values.get_kind_by_index(values.get_index(tmpword))==2){
            //printf("test4\n");
            values.get_string_value(values.get_index(tmpword),outstring);

            converter.convert_syntax_srv_address(tmpout,tmpline,outstring,tmpword2);

        }
        else if(values.get_kind_by_index(values.get_index(tmpword))==1){
            int intvalue=values.get_int_value(values.get_index(tmpword));
            //printf("intvalue = %d\n",intvalue);
            sprintf(outstring,"%d",intvalue);
            converter.convert_syntax_srv_address(tmpout,tmpline,outstring,tmpword2);
        }

        sprintf(tmpline,"%s",tmpout);


        i++;
    }

    strcpy(out,tmpline);

}



void C_syntax::change_for_printOut2(char *out,char *in)
{
    char tmpline[MAX_VAL_STRING+100];

    sprintf(tmpline,"%s",in);


    sprintf(out,"%s",in);


    char sym[6];//sym_c[6];

    int i=0,index=0,indexend=0;

    int  num=converter.cmptext(out,"[\\");

    while(i<num){
        index=converter.indexOfs(tmpline,"[\\",i+1);
        indexend=converter.indexOfs_end(tmpline,"[\\",i+1);
        sym[0]='[';
        sym[1]='\\';
        sym[2]=tmpline[index+1];
        sym[3]=']';
        sym[4]='\0';





        if(tmpline[index+2]==']'){
            //printf("dss\n");
            if(tmpline[index+1]=='n'){converter.convert_syntax_char(out,tmpline,'\n',sym);  }
            else if(tmpline[index+1]=='t'){converter.convert_syntax_char(out,tmpline,'\t',sym);  }
            else if(tmpline[index+1]=='b'){converter.convert_syntax_char(out,tmpline,'\b',sym);  }
            else if(tmpline[index+1]=='\"'){converter.convert_syntax_char(out,tmpline,'\"',sym);  }
        }

        sprintf(tmpline,"%s",out);
        i++;
    }

}




void C_syntax::change_for_printOut3(char *out,char *in)
{
    char tmp_c1[MAX_VAL_STRING];
    char tmp_c2[MAX_VAL_STRING];
    char tmp_out[MAX_VAL_STRING];


    strcpy(tmp_c1,in);
    //printf("ccc%d\n",g_num);
    if(g_num>0){
        //printf("ccc\n");
        myll->get_curr_addr(tmp_c2);
        //printf("ccc2\n");
    }
    else{  sprintf(tmp_c2,""); }

    //printf("tmp_c2=%s;\n",tmp_c2);
    converter.convert_syntax_srv_address(tmp_out,tmp_c1,tmp_c2,"[Server-address()]");

    strcpy(out,tmp_out);

}







void C_syntax::input_clinklist(C_link_list *llp,int innum)
{
    //memcpy(&myll,llp);
    myll=llp;
    g_num=innum;

}



header_info C_syntax::read_from_ll_to_file_header()
{  header_info  info;
    oneline *tmp=NULL;
    tmp=begin_line_P;
    //int i=0;

    while(tmp!=NULL/*&&converter.startWith2(tmp->line,"#")==true*/){ // printf("%d",i); i++; printAll();
        // printf("before %s \n",tmp->line);
        if(check_tag(tmp->line)==true){
            if(converter.startWith2(tmp->line,"#enable")==true ){/*printf("11dd\n"); */info.enable=enable_header(tmp->line); }
            else if(converter.startWith(tmp->line,"#service")==1){srv_type_header(info.srv_type,tmp->line);}
            else if(converter.startWith2(tmp->line,"#config-file")==true){ /* printf("V %s \n",tmp->line);*/configfile_header(info.fname,tmp->line);}
            else if(converter.startWith2(tmp->line,"#maxwait")==true){info.timeout=timeout(tmp->line);}
            else if(converter.startWith2(tmp->line,"#run-type")==true){info.runtype=runtype(tmp->line);}
        }
        //printf("after %s \n",tmp->line);
        tmp=tmp->next;
    }


    return info;
}//end read_from_ll_to_file_harder()

int C_syntax::runtype(char *line)
{
    char *tmptoken1=NULL;
    int re=1;
    tmptoken1=(char *)calloc(strlen(line)+1,sizeof(char));
    converter.getToken2(tmptoken1,line,2);
    //printf("[%s]\n",tmptoken1);
    if(strcmp(tmptoken1,t_FIRSTTIMEONLY)==0){re=FIRSTTIMEONLY; }
    else if(strcmp(tmptoken1,t_SOMETIME_FAST)==0){ re=SOMETIME_FAST; }
    else if(strcmp(tmptoken1,t_SOMETIME_MEDIUM)==0){ re=SOMETIME_MEDIUM; }
    else if(strcmp(tmptoken1,t_SOMTIME_SLOW)==0){ re=SOMTIME_SLOW; }
    else if(strcmp(tmptoken1,t_EVERYTIME)==0){ re=EVERYTIME; }
    free(tmptoken1);
    return re;
}




bool C_syntax::enable_header(char *line)
{  /*return 1 is yes  return 0 is no or other*/
    //printf("11c %s\n",line);
    char *tmptoken1=NULL;
    int revalue=0;
    //char *tmptoken1_1=NULL;
    tmptoken1=(char *)calloc(strlen(line)+50,sizeof(char));

    converter.getToken2(tmptoken1,line,2);

    if(converter.startWith(tmptoken1,"yes")==1){/* printf("yessss\n");*/ revalue=1;}
    else if(converter.startWith(tmptoken1,"no")==1){/* printf("nooooo\n");*/ revalue=0;}
    else {/*printf("nooooo!\n"); */ revalue=0;}
    free(tmptoken1);
    if( revalue==1){return true;}
    else if(revalue==0){return false;}
}


void  C_syntax::srv_type_header(char*out,char * line)
{
    char tmptoken1[MAX_VAL_STRING];
    //int revalue=0;
    char tmptoken1line[MAX_VAL_STRING];



    strcpy(tmptoken1line,line);
    converter.getToken2(tmptoken1,tmptoken1line,2);
    int i=0;
    while(tmptoken1[i]!='\n'&&tmptoken1[i]!=' ')
    {
        //printf("+%d\n",i);
        i++;
    }
    tmptoken1[i]='\0';
    //printf("+++>%s<++\n",tmptoken1);
    sprintf(out,"%s",tmptoken1);

}



void C_syntax::configfile_header(char *out ,char *line)
{
    char tmptoken1[MAX_VAL_STRING];
    char tmpline[MAX_VAL_STRING];

    strcpy(tmpline,line);
    converter.getToken2(tmptoken1,tmpline,2);
    int i=0;
    while(tmptoken1[i]!='\n'&&tmptoken1[i]!=' ')
    {
        //printf("+%d\n",i);
        i++;
    }
    tmptoken1[i]='\0';

    sprintf(out,"%s",tmptoken1);


}




long int C_syntax::timeout(char *line)
{
    char *tmptoken1=NULL;
    long int revalue=0;
    tmptoken1=(char *)calloc(strlen(line)+1,sizeof(char));

    converter.getToken2(tmptoken1,line,2);

    //printf("B %s B\n",tmptoken1);

    revalue=atol(tmptoken1);

    free(tmptoken1);
    return revalue;
}




int C_syntax::Checkatt(char *line)
{
    /*if have att you want in att list function return 1
  else return 0
  ->value *line is value of att you want
  */

    char tmpline[MAX_VAL_STRING];
    char tmp1[MAX_VAL_STRING];
    char tmpout2[MAX_VAL_STRING];
    char tmptokenOUT[MAX_VAL_STRING];

    char tmpout[MAX_A_SERVICE_ATT];
    //int len_cmdatt=strlen("Chkatt(")+1;
    strcpy(tmpline,line);
    int len_cmdatt=converter.indexOfs_end(tmpline,"Chkatt(\"",1);


    int i=0,j=0;

    //printf("MM %d\n",len_cmdatt);
    while(len_cmdatt<strlen(line)){
        // printf("%d %c\n",len_cmdatt,tmpline[len_cmdatt]);
        tmp1[j]=tmpline[len_cmdatt];
        len_cmdatt++; j++;
    }
    tmp1[j]='\0';
    //printf("\n>>%s\n",tmp1);
    i=1;
    len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    // printf("before_len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    if(len_cmdatt>=2){
        while(tmp1[len_cmdatt+1]==']'&&tmp1[len_cmdatt-1]=='\\'&&tmp1[len_cmdatt-2]=='['){
            //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
            i++;
            len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
            // printf("AF_len_cmdatt=%d ",len_cmdatt); printf(">>%s =%c %c %c\n",tmp1,tmp1[len_cmdatt+1],tmp1[len_cmdatt-1],tmp1[len_cmdatt-2]);
        }
    }
    tmp1[len_cmdatt]='\0';
    //len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;

    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s;\n",tmp1);
    //if(myll!=NULL){
    sprintf(tmpout2,"%s",myll->get_all_curr_att());
    //}
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s;\n",tmp1);
    if(g_num>0){
        converter.get_attrs(tmpout,tmp1,tmpout2);
        //printf("M %s\n",myll->get_all_curr_att());
    }

    //if(0==strcmp();
    //printf("2len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);

    change_for_printOut2(tmptokenOUT,tmp1);
    //printf("3len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmptokenOUT);
    int revalue=0;
    if(true==converter.chaek_attrs(tmptokenOUT,myll->get_all_curr_att())){ revalue=1; }
    else{ revalue=0;}

    return revalue;
}






void C_syntax::printOut2(char *line)
{

    char tmptokenOUT[MAX_VAL_STRING];
    char tmptokenOUT_2[MAX_VAL_STRING];
    char tmptokenOUT_3[MAX_VAL_STRING];


    char *tmpline=NULL;
    //char *tmp0=NULL;
    char *tmp1=NULL;
    tmp1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    int len_cmdatt=0;
    int ix=0,i=0,jx=0;
    strcpy(tmpline,line);





    while(tmpline[ix]!='\"'){  ix++;   }

    ix++; jx=0;
    while(tmpline[ix]!='\0'&&tmpline[ix]!='\n')
    {  //printf("\ncheck2\n");
        tmp1[jx]=tmpline[ix];
        ix++;  jx++;
    }
    tmp1[jx]='\0';

    //printf("c>>%s\n",tmp1);

    i=1;
    len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    // printf("before_len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    if(len_cmdatt>=2){
        while(tmp1[len_cmdatt+1]==']'&&tmp1[len_cmdatt-1]=='\\'&&tmp1[len_cmdatt-2]=='['){
            //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
            i++;
            len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
            // printf("AF_len_cmdatt=%d ",len_cmdatt); printf(">>%s =%c %c %c\n",tmp1,tmp1[len_cmdatt+1],tmp1[len_cmdatt-1],tmp1[len_cmdatt-2]);
        }
    }

    tmp1[len_cmdatt]='\0';
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);


    change_for_printOut(tmptokenOUT,tmp1);
    //printf("TEST2\n");
    //printf("O:%s:O\n",tmptokenOUT);
    change_for_printOut2(tmptokenOUT_2,tmptokenOUT);
    change_for_printOut3(tmptokenOUT_3,tmptokenOUT_2);

    //printf("\"%s\";\n",tmptokenOUT_3);


    free(tmp1);
    free(tmpline);
}











void C_syntax::printOut3(char *line)
{

    char tmptokenOUT[MAX_VAL_STRING];
    char tmptokenOUT_2[MAX_VAL_STRING];
    char tmptokenOUT_3[MAX_VAL_STRING];


    char *tmpline=NULL;
    //char *tmp0=NULL;
    char *tmp1=NULL;
    tmp1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    int len_cmdatt=0;
    int ix=0,i=0,jx=0;
    strcpy(tmpline,line);





    while(tmpline[ix]!='\"'){  ix++;   }

    ix++; jx=0;
    while(tmpline[ix]!='\0'&&tmpline[ix]!='\n')
    {  //printf("\ncheck2\n");
        tmp1[jx]=tmpline[ix];
        ix++;  jx++;
    }
    tmp1[jx]='\0';

    //printf("c>>%s\n",tmp1);

    i=1;
    len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    // printf("before_len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    if(len_cmdatt>=2){
        while(tmp1[len_cmdatt+1]==']'&&tmp1[len_cmdatt-1]=='\\'&&tmp1[len_cmdatt-2]=='['){
            //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
            i++;
            len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
            // printf("AF_len_cmdatt=%d ",len_cmdatt); printf(">>%s =%c %c %c\n",tmp1,tmp1[len_cmdatt+1],tmp1[len_cmdatt-1],tmp1[len_cmdatt-2]);
        }
    }
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    //len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    tmp1[len_cmdatt]='\0';
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);


    change_for_printOut(tmptokenOUT,tmp1);

    change_for_printOut2(tmptokenOUT_2,tmptokenOUT);
    change_for_printOut3(tmptokenOUT_3,tmptokenOUT_2);

    //printf(";%s;",tmptokenOUT_3);


    free(tmp1);
    free(tmpline);
}



void C_syntax::Get_att(char*out ,char *line)
{
    //printf(">>%s\n",line);
    /*char *tmpline=NULL;
 char *tmp1=NULL;
 char *tmpout2=NULL;
*/
    char tmpline[MAX_VAL_STRING];
    char tmp1[MAX_VAL_STRING];
    char tmpout2[MAX_A_SERVICE_ATT];

    char tmptokenOUT[MAX_VAL_STRING];
    char tmpatt[MAX_VAL_STRING];
    /* tmp1=(char *)calloc(strlen(line)+1,sizeof(char));
 tmpout2=(char *)calloc(strlen(line)+1,sizeof(char));;
 tmpline=(char *)calloc(strlen(line)+1,sizeof(char));*/
    char tmpout[MAX_A_SERVICE_ATT];
    //int len_cmdatt=strlen("Chkatt(")+1;
    strcpy(tmpline,line);
    int len_cmdatt=converter.indexOfs_end(tmpline,"Getatt(\"",1);


    int i=0,j=0;

    // printf("MM %d\n",len_cmdatt);
    while(len_cmdatt<strlen(tmpline)){
        // printf("%d %c\n",len_cmdatt,tmpline[len_cmdatt]);
        tmp1[j]=tmpline[len_cmdatt];
        len_cmdatt++; j++;
    }
    tmp1[j]='\0';
    //printf("\n>>%s\n",tmp1);tmpout2
    i=1;
    len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    // printf("before_len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    if(len_cmdatt>=2){
        while(tmp1[len_cmdatt+1]==']'&&tmp1[len_cmdatt-1]=='\\'&&tmp1[len_cmdatt-2]=='['){
            //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
            i++;
            len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
            // printf("AF_len_cmdatt=%d ",len_cmdatt); printf(">>%s =%c %c %c\n",tmp1,tmp1[len_cmdatt+1],tmp1[len_cmdatt-1],tmp1[len_cmdatt-2]);
        }
    }
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    //len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    tmp1[len_cmdatt]='\0';
    // printf("tmp1=%s=\n",tmp1);
    //printf("myll->get_all_curr_att=%s\n",myll->get_all_curr_att());
    sprintf(tmpout2,"%s\0",myll->get_all_curr_att());
    //printf("myll->get_all_curr_att2=%s\n",myll->get_all_curr_att());
    if(g_num>0){
        converter.get_attrs(tmpout,tmp1,tmpout2);
    }
    //sprintf(myll->curr->service_attr,"%s",tmpout2);
    //printf("\nmyll->get_all_curr_att3=%s   |||%s \n",myll->get_all_curr_att(),tmpout2);


    change_for_printOut2(tmptokenOUT,tmp1);
    //	printf("tesrt--------2\n");
    //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmptokenOUT);
    //printf("\nmyll->get_all_curr_att4=%s\n",myll->get_all_curr_att());
    int revalue=0;
    if(true==converter.chaek_attrs(tmptokenOUT,myll->get_all_curr_att())){ revalue=1; }
    else{ revalue=0;}
    //printf("TTT %d\n",revalue);
    // printf("tesrt--------2-1\n");
    if(revalue==1){  /*printf("CCC\n");*/
        converter.get_attrs(tmpatt,tmptokenOUT,myll->get_all_curr_att());
        strcpy(out,tmpatt);
    }
    else{ sprintf(tmpatt,"\0"); }
    //printf("tesrt--------3\n");
    //printf("XCCC\n");
    //printf("1XCCC\n");
    //free(tmp1);
    //printf("2XCCC\n");
    //free(tmpout2);
    //printf("3XCCC\n");
    //free(tmpline);
    //printf("4XCCC\n");
    //return revalue;


}






void C_syntax::openorclrF(char *fname)
{  /*if we have file */
    myfile.inputfname(fname);
    if(-1==myfile.openorclear()){printf("Can not open file!"); }
}

void C_syntax::cpto()
{  /*copy data from tmp file to real file config*/
    myfile.cpyto();
}






void C_syntax::FprintOut(char *line,int cmd)
{

    //converter.get_attrs(NULL,char *attrwant,char* in_all_attr)
    //Nextsrv

    //char tmptoken[MAX_VAL_STRING];
    char tmptokenOUT[MAX_VAL_STRING];
    char tmptokenOUT_2[MAX_VAL_STRING];
    char tmptokenOUT_3[MAX_VAL_STRING];


    char *tmpline=NULL;
    //char *tmp0=NULL;
    char *tmp1=NULL;
    tmp1=(char *)calloc(strlen(line)+1,sizeof(char));
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    int len_cmdatt=0;
    int ix=0,i=0,jx=0;
    strcpy(tmpline,line);





    while(tmpline[ix]!='\"'){  ix++;   }

    ix++; jx=0;
    while(tmpline[ix]!='\0'&&tmpline[ix]!='\n')
    {  //printf("\ncheck2\n");
        tmp1[jx]=tmpline[ix];
        ix++;  jx++;
    }
    tmp1[jx]='\0';

    //printf("c>>%s\n",tmp1);

    i=1;
    len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
    // printf("before_len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
    if(len_cmdatt>=2){
        while(tmp1[len_cmdatt+1]==']'&&tmp1[len_cmdatt-1]=='\\'&&tmp1[len_cmdatt-2]=='['){
            //printf("len_cmdatt=%d ",len_cmdatt); printf(">>%s\n",tmp1);
            i++;
            len_cmdatt=converter.indexOfs_end(tmp1,"\"",i)-1;
            // printf("AF_len_cmdatt=%d ",len_cmdatt); printf(">>%s =%c %c %c\n",tmp1,tmp1[len_cmdatt+1],tmp1[len_cmdatt-1],tmp1[len_cmdatt-2]);
        }
    }

    tmp1[len_cmdatt]='\0';

    change_for_printOut(tmptokenOUT,tmp1);
    //printf("TEST2\n");
    // printf("O:%s:O\n",tmptokenOUT);
    change_for_printOut2(tmptokenOUT_2,tmptokenOUT);
    //printf("O:%s:O\n",tmptokenOUT);
    change_for_printOut3(tmptokenOUT_3,tmptokenOUT_2);


    if(cmd==NEWLINE){myfile.writef(tmptokenOUT_3);}
    else if(cmd==SAMELINE){myfile.writef_sameline(tmptokenOUT_3);}
    //printf()
    free(tmp1);
    free(tmpline);
}


bool C_syntax::check_tag(char *line)
{
    char *tmpline=NULL;
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    strcpy(tmpline,line);
    if(true==converter.startWith2(tmpline,OPENTAG)){
        check_tag_value=true;
    }
    else if(true==converter.startWith2(tmpline,CLOSETAG)){
        check_tag_value=false;
    }
    free(tmpline);
    return check_tag_value;
}


void C_syntax::Fprint_outsidetag(char *line)
{
    char *tmpline=NULL;
    char *tmp1=NULL;
    tmpline=(char *)calloc(strlen(line)+1,sizeof(char));
    tmp1=(char *)calloc(strlen(line)+MAX_VAL_STRING,sizeof(char));
    strcpy(tmpline,line);
    memset((char *)tmp1,'\0',sizeof(tmp1));


    //printf("-->%s\n",tmpline);

    if(false==converter.startWith2(tmpline,CLOSETAG)){

        //chang_val_outsidetag(tmp1,tmpline);
        //printf("test1 ->%s , %s\n",tmp1,tmpline);
        values.compare_value_with_string(tmp1,tmpline);
        //printf("test2 ->;%s; , ;%s;\n",tmp1,tmpline);
        myfile.writef(tmp1);
        //printf("test3 ->%s , %s\n",tmp1,tmpline);
    }
    //printf("1-->%s\n",tmpline);
    free(tmpline);
    //printf("2-->%s\n",tmpline);
    free(tmp1);

    return ;
}























