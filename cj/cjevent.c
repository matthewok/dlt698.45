/*
 * cjevent.c
 *
 *  Created on: Jan 12, 2017
 *      Author: ava
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StdDataType.h"
#include "EventObject.h"
#include "AccessFun.h"
#include "ParaDef.h"
#include "cjevent.h"
#include "event.h"
//property


void printClass7(Class7_Object class7)
{
	int i=0;
	fprintf(stderr,"【Class7】逻辑名: %04x\n",class7.oi);
	fprintf(stderr,"当前记录数  最大记录数  上报标识  有效标识  关联对象属性【OAD】\n");
	fprintf(stderr,"%d           %d           %d           %d   ",class7.crrentnum,class7.maxnum,class7.reportflag,class7.enableflag);
	for(i=0;i<class7.class7_oad.num;i++) {
		fprintf(stderr,"%04X_%02X%02X ",class7.class7_oad.oadarr[i].OI,class7.class7_oad.oadarr[i].attflg,class7.class7_oad.oadarr[i].attrindex);
	}
	fprintf(stderr,"\n");
}

void printClass310d()
{
	Event310D_Object Event310d; //电能表飞走事件12
	int	readflg=0;
	int i=0;

	memset(&Event310d,0,sizeof(Event310D_Object));
	fprintf(stderr,"sizeof(Event310D_Object)=%d\n",sizeof(Event310D_Object));
	readflg = readCoverClass(0x310d,0,&Event310d,sizeof(Event310D_Object),event_para_save);
	if(readflg!=1)
	{
		fprintf(stderr,"无参数文件 readflg=%d\n",readflg);
		return;
	};
	fprintf(stderr,"【Event310D】电能表飞走事件: %04x\n",Event310d.event_obj.oi);
	fprintf(stderr,"当前记录数  最大记录数  上报标识  有效标识  关联对象属性【OAD】\n");
	fprintf(stderr,"%d           %d           %d           %d   ",
			Event310d.event_obj.crrentnum,Event310d.event_obj.maxnum,Event310d.event_obj.reportflag,Event310d.event_obj.enableflag);
	for(i=0;i<Event310d.event_obj.class7_oad.num;i++) {
		fprintf(stderr,"%04X_%02X%02X ",Event310d.event_obj.class7_oad.oadarr[i].OI,Event310d.event_obj.class7_oad.oadarr[i].attflg,Event310d.event_obj.class7_oad.oadarr[i].attrindex);
	}
	fprintf(stderr,"\n阈值=%d  关联采集任务号=%d\n",Event310d.poweroffset_obj.power_offset,Event310d.poweroffset_obj.task_no);
	fprintf(stderr,"\n");
}
/*
 *赋值class7-base
 */
void Class7_BaseInit(OI_698 oi,Class7_Object *obj){
	obj->oi=oi;
	obj->crrentnum=0;
	obj->maxnum=15;
	obj->enableflag=0;
	obj->reportflag=0;
}
/*
 *赋值class7
 */
void Class7_Init(OI_698 oi){
	Class7_Object obj;
	Class7_BaseInit(oi,&obj);
	saveCoverClass(oi,0,(void *)&obj,sizeof(Class7_Object),para_init_save);
}
/*
 * Event3105 初始化
 */
void Init_3105(){
	Event3105_Object obj;
	Class7_BaseInit(0x3105,&obj.event_obj);
	obj.mto_obj.over_threshold=240;
	saveCoverClass(0x3105,0,(void *)&obj,sizeof(Event3105_Object),para_init_save);
}
/*
 * Event3106 初始化
 */
void Init_3106(){
	Event3106_Object obj;
	Class7_BaseInit(0x3106,&obj.event_obj);
	//
	saveCoverClass(0x3106,0,(void *)&obj,sizeof(Event3106_Object),para_init_save);
}
/*
 * Event3107 初始化
 */
void Init_3107(){
	Event3107_Object obj;
	Class7_BaseInit(0x3107,&obj.event_obj);
	//
	saveCoverClass(0x3107,0,(void *)&obj,sizeof(Event3107_Object),para_init_save);
}
/*
 * Event3108 初始化
 */
void Init_3108(){
	Event3108_Object obj;
	Class7_BaseInit(0x3108,&obj.event_obj);
	//
	saveCoverClass(0x3108,0,(void *)&obj,sizeof(Event3108_Object),para_init_save);
}
/*
 * Event310B 初始化
 */
void Init_310B(){
	Event310B_Object obj;
	Class7_BaseInit(0x310B,&obj.event_obj);
	//
	saveCoverClass(0x310B,0,(void *)&obj,sizeof(Event310B_Object),para_init_save);
}
/*
 * Event310C 初始化
 */
void Init_310C(){
	Event310C_Object obj;
	Class7_BaseInit(0x310C,&obj.event_obj);
	//
	saveCoverClass(0x310C,0,(void *)&obj,sizeof(Event310C_Object),para_init_save);
}
/*
 * Event310D 初始化
 */
void Init_310D(){
	Event310D_Object obj;
	Class7_BaseInit(0x310D,&obj.event_obj);
	//
	saveCoverClass(0x310D,0,(void *)&obj,sizeof(Event310D_Object),para_init_save);
}
/*
 * Event310E 初始化
 */
void Init_310E(){
	Event310E_Object obj;
	Class7_BaseInit(0x310E,&obj.event_obj);
	//
	saveCoverClass(0x310E,0,(void *)&obj,sizeof(Event310E_Object),para_init_save);
}
/*
 * Event310F 初始化
 */
void Init_310F(){
	Event310F_Object obj;
	Class7_BaseInit(0x310F,&obj.event_obj);
	//
	saveCoverClass(0x310F,0,(void *)&obj,sizeof(Event310F_Object),para_init_save);
}
/*
 * Event3110 初始化
 */
void Init_3110(){
	Event3110_Object obj;
	Class7_BaseInit(0x3110,&obj.event_obj);
	//
	saveCoverClass(0x3110,0,(void *)&obj,sizeof(Event3110_Object),para_init_save);
}
/*
 * Event3116 初始化
 */
void Init_3116(){
	Event3116_Object obj;
	Class7_BaseInit(0x3116,&obj.event_obj);
	//
	saveCoverClass(0x3116,0,(void *)&obj,sizeof(Event3116_Object),para_init_save);
}
/*
 * Event311A 初始化
 */
void Init_311A(){
	Event311A_Object obj;
	Class7_BaseInit(0x311A,&obj.event_obj);
	//
	saveCoverClass(0x311A,0,(void *)&obj,sizeof(Event311A_Object),para_init_save);
}
/*
 * Event311C 初始化
 */
void Init_311C(){
	Event311C_Object obj;
	Class7_BaseInit(0x311C,&obj.event_obj);
	//
	saveCoverClass(0x311C,0,(void *)&obj,sizeof(Event311C_Object),para_init_save);
}

void event_process(int argc, char *argv[])
{
	OI_698	oi=0;
	int 	tmp[20]={};
	Class7_Object	class7={};
	int		i = 0,ret = 0;

	if(argc>=4) {	//event att 3100
//		fprintf(stderr,"argv=%s",argv[3]);
		sscanf(argv[3],"%04x",&tmp[0]);
		oi = tmp[0];
		if(strcmp("reset",argv[2])==0) {
			ret = clearClass(oi);
			fprintf(stderr,"复位出错=%d",ret);
		}
		if(strcmp("pro",argv[2])==0) {
			if(argc==4) {
				switch(oi) {
				case 0x310d:
					fprintf(stderr,"class310d\n");
					printClass310d();
					break;
				case 0x3100:
				case 0x3104:
					fprintf(stderr,"class-%04x\n",oi);
					memset(&class7,0,sizeof(Class7_Object));
					readCoverClass(oi,0,&class7,sizeof(Class7_Object),event_para_save);
					printClass7(class7);
					break;
				}
			}else {
				switch(oi) {
				case 0x3100:	//终端初始化事件1
				case 0x3104:	//终端状态量变位事件3
					memset(&class7,0,sizeof(Class7_Object));
					class7.oi = oi;
					sscanf(argv[4],"%d",&tmp[1]);
					class7.crrentnum = tmp[1];
					sscanf(argv[5],"%d",&tmp[1]);
					class7.maxnum = tmp[1];
					sscanf(argv[6],"%d",&tmp[1]);
					class7.reportflag = tmp[1];
					sscanf(argv[7],"%d",&tmp[1]);
					class7.enableflag = tmp[1];
					sscanf(argv[8],"%d",&tmp[0]);
					for(i=0;i<tmp[0];i++) {
						fprintf(stderr,"argv[%d]=%s",i+9,argv[9+i]);
						sscanf(argv[i+9],"%04X-%02X%02X",&tmp[1],&tmp[2],&tmp[3]);
						class7.class7_oad.oadarr[i].OI = tmp[1];
						class7.class7_oad.oadarr[i].attflg = tmp[2];
						class7.class7_oad.oadarr[i].attrindex = tmp[3];
						fprintf(stderr," %04X-%02X%02X\n",class7.class7_oad.oadarr[i].OI,class7.class7_oad.oadarr[i].attflg,class7.class7_oad.oadarr[i].attrindex);
					}
//					fprintf(stderr," crrentnum=%d maxnum=%d reportflag=%d enableflag=%d\n",class7.crrentnum,class7.maxnum,class7.reportflag,class7.enableflag);
//					fprintf(stderr,"class7size=%d\n",sizeof(Class7_Object));
					saveCoverClass(class7.oi,0,&class7,sizeof(Class7_Object),event_para_save);
					break;
				}
			}
		}
		if(strcmp("record",argv[2])==0) {
			sscanf(argv[4],"%d",&tmp[1]);
			INT8U record_n = tmp[1];      //事件记录参数0/n
			INT8U *Getbuf=NULL;//因为记录为变长，只能采用二级指针，动态分配
			INT8U Getlen=0;//记录长度
			if(record_n!=0){
				ProgramInfo* prginfo_event;
				prginfo_event=OpenShMem("ProgramInfo",sizeof(ProgramInfo),NULL);
				Get_Event(oi,record_n,(INT8U**)&Getbuf,&Getlen,prginfo_event);
				if(Getbuf!=NULL){
                    INT8U index=0,h2=0,h1=0,l2=0,l1=0;
                    index++;//0:结构体
                    index++;//1:结构体元素个数
                    index++;//3:事件序号unsigned-long
                    h2=Getbuf[index++];
                    h1=Getbuf[index++];
                    l2=Getbuf[index++];
                    l1=Getbuf[index++];
                    INT32U event_order=((h2<<24)+(h1<<16)+(l2<<8)+l1);
                    fprintf(stderr,"事件%04x：\n",oi);
                    fprintf(stderr,"事件序号：%d\n",event_order);
                    index++;//0x1c date-s 发生时间
                    l2=Getbuf[index++];
                    l1=Getbuf[index++];
                    fprintf(stderr,"发生时间：%d-%d-%d %d:%d:%d\n",((l2<<8)+l1),
                    		Getbuf[index++],Getbuf[index++],Getbuf[index++],Getbuf[index++],Getbuf[index++]);
                    index++;//0x1c date-s 结束时间
                    if(oi==0x311C){
                    	fprintf(stderr,"该事件无结束时间!\n");
                    }else{
                    	l2=Getbuf[index++];
                    	l1=Getbuf[index++];
                    	fprintf(stderr,"结束时间：%d-%d-%d %d:%d:%d\n",((l2<<8)+l1),
                    	                            Getbuf[index++],Getbuf[index++],Getbuf[index++],Getbuf[index++],Getbuf[index++]);
                    }
                    INT8U Len=0;
                    fprintf(stderr,"事件源类型：");
                    switch(Getbuf[index++]){
						case s_null:
							fprintf(stderr,"NULL ");
							Len=0;
							break;
						case s_tsa:
							fprintf(stderr,"TSA ");
							Len=(Getbuf[index+1]+1);
							break;
						case s_oad:
							fprintf(stderr,"OAD ");
							Len=4;
							break;
						case s_usigned:
							fprintf(stderr,"USIGNED ");
							Len=1;
							break;
						case s_enum:
							fprintf(stderr,"ENUM ");
							Len=1;
							break;
						case s_oi:
							fprintf(stderr,"OI ");
							Len=2;
							break;
                    }
                    INT8U i=0;
                    for(i=0;i<Len;i++)
                    	fprintf(stderr,"%02x",Getbuf[index++]);
                    fprintf(stderr,"\n");

				}
			}
		}
		if(strcmp("init",argv[2])==0) {
			if(oi == 0){
				Class7_Init(0x3100);
				Class7_Init(0x3101);
				Class7_Init(0x3104);
				Class7_Init(0x3109);
				Class7_Init(0x310A);
				Class7_Init(0x3111);
				Class7_Init(0x3112);
				Class7_Init(0x3114);
				Class7_Init(0x3115);
				Class7_Init(0x3117);
				Class7_Init(0x3118);
				Class7_Init(0x3119);
				Class7_Init(0x311B);
				Class7_Init(0x3200);
				Class7_Init(0x3201);
				Class7_Init(0x3202);
				Class7_Init(0x3203);
				Init_3105();
				Init_3106();
				Init_3107();
				Init_3108();
				Init_310B();
				Init_310C();
				Init_310D();
				Init_310E();
				Init_310F();
				Init_3110();
				Init_3116();
				Init_311A();
				Init_311C();
			}else{
               switch(oi){
               case 0x3100:
			   case 0x3101:
			   case 0x3104:
			   case 0x3109:
			   case 0x310A:
			   case 0x3111:
			   case 0x3112:
			   case 0x3114:
			   case 0x3115:
			   case 0x3117:
			   case 0x3118:
			   case 0x3119:
			   case 0x311B:
			   case 0x3200:
			   case 0x3201:
			   case 0x3202:
			   case 0x3203:
				   Class7_Init(oi);
				   break;
			   case 0x3105:
				   Init_3105();
				   break;
			   case 0x3106:
				   Init_3106();
				   break;
			   case 0x3107:
				   Init_3107();
				   break;
			   case 0x3108:
				   Init_3108();
				   break;
			   case 0x310B:
				   Init_310B();
				   break;
			   case 0x310C:
				   Init_310C();
				   break;
			   case 0x310D:
				   Init_310D();
				   break;
			   case 0x310E:
				   Init_310E();
				   break;
			   case 0x310F:
				   Init_310F();
				   break;
			   case 0x3110:
				   Init_3110();
				   break;
			   case 0x3116:
				   Init_3116();
			   	   break;
			   case 0x311A:
				   Init_311A();
				   break;
			   case 0x311C:
				   Init_311C();
				   break;
               }
			}
		}
	}
}