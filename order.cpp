#include "order.h"


void c_order::init(){
    begin=NULL;
    tail=NULL;
    cur=NULL;
    g_num=0;
}


void c_order::add(char text[50],int num){
    if(begin==NULL ){
        begin=(order *)malloc(sizeof(order));
        sprintf(begin->text,"%s",text);
        begin->next=NULL;
        begin->score=num;
        tail=begin;
        g_num++;
    }
    else{
        tail->next=(order *)malloc(sizeof(order));
        tail=tail->next;
        sprintf(tail->text,"%s",text);
        tail->next=NULL;
        tail->score=num;
        g_num++;
    }

}

order c_order::get(){
    order re;
    if(cur==NULL){
        cur=begin;
    }

    if(cur!=NULL){
        sprintf(re.text,"%s",cur->text);
        re.score=cur->score;
        cur=cur->next;
        //return true;
    }
    return re;
}


void c_order::freeone(){

    order *previous=NULL;
    previous=begin;

    if(begin==NULL || tail==NULL){ return;  }

    else if(begin==tail){
        free(tail);
        tail=NULL;
        begin=NULL;
    }
    else{
        while(previous->next!=tail){ previous=previous->next; }
        free(tail);
        tail=previous;
        tail->next=NULL;
    }



}

void c_order::freeall()
{	g_num=0;
    while( begin!=NULL){

        freeone();
    }
    return;
}



