#include "slpac.h"
#include "loop.h"
#include "control_value.h"
#include "c_file.h"
#include "order.h"
#include "find_srv.h"

#define NEWLINE 1
#define SAMELINE 2
#define OPENTAG "<slps>"
#define CLOSETAG "</slps>"



struct headerinfo{
      bool enable;  // true =yes, false= no
      char srv_type[MAX_SERVICE_TYPE_ARRAY ];
      char fname[MAX_FNAME];
       int timeout;
      int runtype;
  };
typedef struct  headerinfo  header_info;



class C_syntax
{    
	bool endloop;  // endloop==true mean it back from end loop    endloop==false mean it not back from end loop
	int care_end;  // 0 care End    >0  skip End
	oneline *begin_line_P;
	oneline *tail_line_P;
	void add_struct_line(char *);
	bool IdleProcess;
	void Dim(char *);
	void changeValue(char *);
	void If(char *);
	void Elseif(char *);
	void Else();
	int str_in_str(char*,char*);
	bool chkelseif;
	bool test_int_int(int ,char *,int);
	bool test_char_char(char *,char *,char *);

	void printOut2(char *);
	void printOut3(char *);
	void FprintOut(char *,int);

	void Fprint_outsidetag(char *);


	void change_for_printOut(char *,char *);
	void change_for_printOut2(char *,char *);
	void change_for_printOut3(char *,char *);
	int Loop(char *,oneline *);
	C_loop  inloop;
	bool check(char *);
	int operation(char*);

	C_link_list* myll;
	c_order myorder;
	void ordersrvs_now();
	int g_num;
	bool enable_header(char *);
	void  srv_type_header(char*,char * );
	void configfile_header(char * ,char *);
	long int timeout(char *);
	int Checkatt(char *);
	void Get_att(char*,char *);
	C_file myfile;
	bool check_tag(char *);
	bool check_tag_value;
	void ordersrvs_now_url();
	void ordersrvs_now_url2();
	bool ordersrvs_addstring(char *);  //��Ѻ�����	
	int ordersrvs_now_check(char[],c_order);
	int ordersrvs_now_check2(char[],c_order);
	void ordersrvs_addstr(char *);
	void ordersrvs_now_att(char *); 

	public:
	int runtype(char *);
	void openorclrF(char *);
	void cpto();
	int freetail();
	int freeall();
	header_info read_from_ll_to_file_header();
	C_control_value values;
	void input_clinklist(C_link_list *,int );
	void init();

	void add_line(char *);
	int file_to_lines(char *);
	void printAll();

	void proc_commend();  //not do

	void ordersrvs_swap(srvtype_ll *,srvtype_ll *);
	void ordersrvs_addstr_url(char *);

};




