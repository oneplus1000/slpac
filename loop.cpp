#include "loop.h"


void C_loop::push(int num,int i,oneline *tmpP)
{

    stackloop[index_a].i=i;
    stackloop[index_a].tmp_adrr_loop=tmpP;
    stackloop[index_a].num=num;

    if(index_a<MAX_LOOP){  index_a++; }
}


void C_loop::init()
{  int j=0;
    index_a=0;
    for(j=0;j<MAX_LOOP;j++)
    { stackloop[j].i=-1;
        stackloop[j].tmp_adrr_loop=NULL;
        stackloop[j].num=-1;
    }

}


void C_loop::pop_free()
{   stackloop[index_a-1].i=-1;
    stackloop[index_a-1].tmp_adrr_loop=NULL;
    stackloop[index_a-1].num=-1;
    if(index_a>0){index_a--;}

}


int  C_loop::return_num()
{
    return stackloop[index_a-1].num;
}

int  C_loop::return_i()
{
    return stackloop[index_a-1].i;
}

oneline *  C_loop::return_P()
{
    return stackloop[index_a-1].tmp_adrr_loop;
}



void C_loop::reduce_i()
{
    stackloop[index_a-1].i=stackloop[index_a-1].i-1;

}

void C_loop::reduce_num()
{
    stackloop[index_a-1].num=stackloop[index_a-1].num-1;

}





