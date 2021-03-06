/*
 * cjdev.c
 *
 *  Created on: Feb 9, 2017
 *      Author: ava
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StdDataType.h"
#include "Shmem.h"
#include "EventObject.h"
#include "PublicFunction.h"
#include "AccessFun.h"
#include "Objectdef.h"
#include "ParaDef.h"
#include "Shmem.h"
#include "main.h"
#include "Esam.h"

extern ProgramInfo *JProgramInfo;

void printF203() {
    CLASS_f203 oif203 = {};
    readCoverClass(0xf203, 0, &oif203, sizeof(CLASS_f203), para_vari_save);
    fprintf(stderr, "[F203]开关量输入\n");
    fprintf(stderr, "逻辑名 %s\n", oif203.class22.logic_name);
    fprintf(stderr, "设备对象数量：%d\n", oif203.class22.device_num);
    fprintf(stderr, "属性2：ST=%d_%d_%d_%d %d_%d_%d_%d\n", oif203.statearri.stateunit[0].ST,
            oif203.statearri.stateunit[1].ST, oif203.statearri.stateunit[2].ST,
            oif203.statearri.stateunit[3].ST, oif203.statearri.stateunit[4].ST, oif203.statearri.stateunit[5].ST,
            oif203.statearri.stateunit[6].ST,
            oif203.statearri.stateunit[7].ST);
    fprintf(stderr, "属性2：CD=%d_%d_%d_%d %d_%d_%d_%d\n\n", oif203.statearri.stateunit[0].CD,
            oif203.statearri.stateunit[1].CD,
            oif203.statearri.stateunit[2].CD, oif203.statearri.stateunit[3].CD, oif203.statearri.stateunit[4].CD,
            oif203.statearri.stateunit[5].CD,
            oif203.statearri.stateunit[6].CD, oif203.statearri.stateunit[7].CD);
    fprintf(stderr, "属性4：接入标志=%02x\n", oif203.state4.StateAcessFlag);
    fprintf(stderr, "属性4：属性标志=%02x\n", oif203.state4.StatePropFlag);
}

void printF101() {
    CLASS_F101 f101 = {};
    int i = 0;
    readCoverClass(0xf101, 0, &f101, sizeof(CLASS_F101), para_vari_save);
    fprintf(stderr, "[F101]安全模式参数\n");
    if (f101.active == 0) {
        fprintf(stderr, "属性2:安全模式选择：不启用安全模式参数\n");
    } else if (f101.active == 1) {
        fprintf(stderr, "属性2:安全模式选择：启用安全模式参数\n");
    } else {
        fprintf(stderr, "属性2:安全模式选择[0,1]：读取无效值：%d\n", f101.active);
    }
    fprintf(stderr, "安全模式参数个数：%d\n", f101.modelnum);
    for (i = 0; i < f101.modelnum; i++) {
        fprintf(stderr, "OI=%04x 安全模式=%d\n", f101.modelpara[i].oi, f101.modelpara[i].model);
    }
}

void printF205() {
    CLASS_F205 f205 = {};
    int i = 0;
    readCoverClass(0xf205, 0, &f205, sizeof(CLASS_F205), para_vari_save);
    fprintf(stderr, "[F205]继电器输出\n");
    for(i=0;i<3;i++) {
    	fprintf(stderr,"--%d--\n",i);
		fprintf(stderr,"当前状态  = %d\n",f205.unit[i].currentState);
		fprintf(stderr,"开关属性  = %d\n",f205.unit[i].switchAttr);
		fprintf(stderr,"接线状态  = %d\n",f205.unit[i].wiredState);
    }
}

void printF209() {
	CLASS_f209 f209 = {};
    readCoverClass(0xf209, 0, &f209, sizeof(CLASS_f209), para_vari_save);
    fprintf(stderr, "[F209]载波接口[鼎信：TCR3　　东软：ESRT　　力合微：LH9C　　芯珑：SLE2 　瑞斯康　0101]\n");
	fprintf(stderr,"厂商信息  = %c%c%c%c\n",f209.para.version.factoryCode[1],f209.para.version.factoryCode[0],
			f209.para.version.chipCode[1],f209.para.version.chipCode[0]);
	fprintf(stderr,"版本日期  = %d-%d-%d-%d\n",f209.para.version.softDate[0],f209.para.version.softDate[1],
											 f209.para.version.softDate[2],f209.para.version.softDate[3]);
	fprintf(stderr,"软件版本  = %d\n",f209.para.version.softVer);
}

void SetF101(int argc, char *argv[]) {
    CLASS_F101 f101 = {};
    int tmp = 0;
    if (strcmp(argv[2], "init") == 0) {
        memset(&f101, 0, sizeof(CLASS_F101));
        f101.active = 1; //初始化启用
        saveCoverClass(0xf101, 0, &f101, sizeof(CLASS_F101), para_init_save);
        setOIChange_CJ(0xf101);
    }
    if (strcmp(argv[2], "set") == 0) {
        memset(&f101, 0, sizeof(CLASS_F101));
        readCoverClass(0xf101, 0, &f101, sizeof(CLASS_F101), para_vari_save);
        sscanf(argv[4], "%d", &tmp);
        f101.active = tmp;
        saveCoverClass(0xf101, 0, &f101, sizeof(CLASS_F101), para_vari_save);
        setOIChange_CJ(0xf101);
    }
}

void getipnum(MASTER_STATION_INFO *info, char *argv) {
    int ipnum1 = 0, ipnum2 = 0, ipnum3 = 0, ipnum4 = 0, port1;
    sscanf((const char *) argv, "%d.%d.%d.%d:%d", &ipnum1, &ipnum2, &ipnum3, &ipnum4, &port1);
    info[0].port = port1;
    info[0].ip[1] = (INT8U) ipnum1;
    info[0].ip[2] = (INT8U) ipnum2;
    info[0].ip[3] = (INT8U) ipnum3;
    info[0].ip[4] = (INT8U) ipnum4;
}

void SetUsrPwd(int argc, char *argv[]) {
    CLASS25 class4500;
    memset(&class4500, 0x00, sizeof(class4500));

    if (argc == 5) {
        write_userpwd(argv[2], argv[3], argv[4]);
        readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
        memset(class4500.commconfig.userName,0,sizeof(class4500.commconfig.userName));
        memset(class4500.commconfig.passWord,0,sizeof(class4500.commconfig.passWord));
        class4500.commconfig.userName[0] = strlen(argv[2]);
        memcpy(&class4500.commconfig.userName[1], argv[2], strlen(argv[2]));
        class4500.commconfig.passWord[0] = strlen(argv[3]);
        memcpy(&class4500.commconfig.passWord[1], argv[3], strlen(argv[3]));
        saveCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
        setOIChange_CJ(0x4500);
    } else {
        readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
        fprintf(stderr, "用户名：%s\t密码：%s\n", &class4500.commconfig.userName[1], &class4500.commconfig.passWord[1]);
        fprintf(stderr, "说明:【cdma电信用户名密码设置】cj usr-pwd 参数:　user  password	apn \n");
    }
}

void showStatus()
{
    JProgramInfo = OpenShMem("ProgramInfo", sizeof(ProgramInfo), NULL);
    fprintf(stderr, "集中器登陆(0:没有登陆 1:GPRS登陆 2:以太网登陆 3:串口登陆)[%d]\n", JProgramInfo->dev_info.jzq_login);
    fprintf(stderr, "1:AT检测成功 2:获取GPRS模块信息 3:检测SIM卡 4:注册网络成功[%d]\n", JProgramInfo->dev_info.gprs_status);
    fprintf(stderr, "信号强度[%d]\n", JProgramInfo->dev_info.Gprs_csq);
    fprintf(stderr, "在线类型0:GPRS  1:CDMA2000  2:TD_LTE  3:FDD_LTE[%d]\n", JProgramInfo->dev_info.wirelessType);
    fprintf(stderr, "拨号成功(0:拨号未成功 1:拨号成功)[%d]\n", JProgramInfo->dev_info.pppd_status);
    fprintf(stderr, "主站连接状态(0:尚未连接 1:已经连接)[%d]\n", JProgramInfo->dev_info.connect_ok);
    shmm_unregister("ProgramInfo", sizeof(ProgramInfo));
}


//TODO: 字符串第一个字节是否要保存长度，规约读取
void SetIPort(int argc, char *argv[]) {
    CLASS25 class4500;
    MASTER_STATION_INFO_LIST master;

    memset(&master, 0, sizeof(MASTER_STATION_INFO_LIST));
    memset(&class4500, 0, sizeof(CLASS25));
    readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
    fprintf(stderr, "\n无线公网 主IP %d.%d.%d.%d:%d\n", class4500.master.master[0].ip[1], class4500.master.master[0].ip[2],
            class4500.master.master[0].ip[3],
            class4500.master.master[0].ip[4], class4500.master.master[0].port);
    fprintf(stderr, "\n无线公网 备IP %d.%d.%d.%d:%d\n", class4500.master.master[1].ip[1], class4500.master.master[1].ip[2],
            class4500.master.master[1].ip[3],
            class4500.master.master[1].ip[4], class4500.master.master[1].port);
    int i = 0;
    int num = argc - 2;
    if (num > 0 && num < 4) {
        master.masternum = num;
        for (i = 0; i < num; i++) {
            getipnum(&master.master[i], argv[2 + i]);
        }
        memcpy(&class4500.master, &master, sizeof(MASTER_STATION_INFO_LIST));
        class4500.master.master[0].ip[0] = 4;	//ｉｐ长度
        class4500.master.master[1].ip[0] = 4;	//ｉｐ长度
        fprintf(stderr, "\n存储前 主IP %d.%d.%d.%d:%d\n", class4500.master.master[0].ip[1],
                class4500.master.master[0].ip[2], class4500.master.master[0].ip[3],
                class4500.master.master[0].ip[4], class4500.master.master[0].port);
        fprintf(stderr, "\n存储前 备IP %d.%d.%d.%d:%d\n", class4500.master.master[1].ip[1],
                class4500.master.master[1].ip[2], class4500.master.master[1].ip[3],
                class4500.master.master[1].ip[4], class4500.master.master[1].port);
        saveCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
        setOIChange_CJ(0x4500);
    }
}

void SetNetIPort(int argc, char *argv[]) {
    CLASS26 class4510;
    MASTER_STATION_INFO_LIST master;

    memset(&master, 0, sizeof(MASTER_STATION_INFO_LIST));
    memset(&class4510, 0, sizeof(CLASS26));
    readCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);
    fprintf(stderr, "\n以太网接口 主IP %d.%d.%d.%d:%d\n", class4510.master.master[0].ip[1], class4510.master.master[0].ip[2],
            class4510.master.master[0].ip[3],
            class4510.master.master[0].ip[4], class4510.master.master[0].port);
    fprintf(stderr, "\n以太网接口 备IP %d.%d.%d.%d:%d\n", class4510.master.master[1].ip[1], class4510.master.master[1].ip[2],
            class4510.master.master[1].ip[3],
            class4510.master.master[1].ip[4], class4510.master.master[1].port);
    int i = 0;
    int num = argc - 2;
    if (num > 0 && num < 4) {
        master.masternum = num;
        for (i = 0; i < num; i++) {
            getipnum(&master.master[i], argv[2 + i]);
        }
        memcpy(&class4510.master, &master, sizeof(MASTER_STATION_INFO_LIST));
        class4510.master.master[0].ip[0] = 4;	//ｉｐ长度
        class4510.master.master[1].ip[0] = 4;	//ｉｐ长度
        fprintf(stderr, "\n存储前 主IP %d.%d.%d.%d:%d\n", class4510.master.master[0].ip[1],
                class4510.master.master[0].ip[2], class4510.master.master[0].ip[3],
                class4510.master.master[0].ip[4], class4510.master.master[0].port);
        fprintf(stderr, "\n存储前 备IP %d.%d.%d.%d:%d\n", class4510.master.master[1].ip[1],
                class4510.master.master[1].ip[2], class4510.master.master[1].ip[3],
                class4510.master.master[1].ip[4], class4510.master.master[1].port);
        saveCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);
        setOIChange_CJ(0x4510);
    }
}

void setOnlineMode(int argc, char *argv[]) {
    CLASS25 class4500;
    CLASS26 class4510;

    memset(&class4500, 0, sizeof(CLASS25));
    readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
    memset(&class4510, 0, sizeof(CLASS26));
    readCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);
    if (argc != 4) {
        fprintf(stderr, "说明:gprs和以太网的工作模式(0:混合模式 1:客户端模式 2:服务器模式)\n");
        fprintf(stderr, " 	gprs工作模式:%d\n", class4500.commconfig.workModel);
        fprintf(stderr, " 	以太网工作模式:%d\n", class4510.commconfig.workModel);
        return;
    }

    memset(&class4500, 0, sizeof(CLASS25));
    readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
    class4500.commconfig.workModel = atoi(argv[2]);
    saveCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);

    class4510.commconfig.workModel = atoi(argv[3]);
    saveCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);
    setOIChange_CJ(0x4500);
    setOIChange_CJ(0x4510);
    fprintf(stderr, "在线模式设置完成\n");

}

void SetID(int argc, char *argv[]) {
    CLASS_4001_4002_4003 classtmp = {};
    char idbuf[VISIBLE_STRING_LEN - 1];
    long int len = 0, id = 0, i = 0;
    char a;
    int tmpval = 0;

    memset(&classtmp, 0, sizeof(CLASS_4001_4002_4003));
    //
    if (argc > 2) {
        memset(idbuf, 0, sizeof(idbuf));
        len = argc - 2;
        classtmp.curstom_num[0] = len;
        for (i = 0; i < len; i++) {
            sscanf(argv[2 + i], "%02x", &tmpval);
            classtmp.curstom_num[i + 1] = tmpval;
        }
        for (i = 0; i < 16; i++) {
            fprintf(stderr, "%02x ", classtmp.curstom_num[i]);
        }
        saveCoverClass(0x4001, 0, &classtmp, sizeof(CLASS_4001_4002_4003), para_vari_save);
        saveCoverClass(0x4001, 0, &classtmp, sizeof(CLASS_4001_4002_4003), para_init_save);
        writeIdFile(classtmp);
        setOIChange_CJ(0x4001);
    } else {
        readCoverClass(0x4001, 0, &classtmp, sizeof(CLASS_4001_4002_4003), para_vari_save);
        fprintf(stderr, "\nCommAddr[%d]:", classtmp.curstom_num[0]);
        for (i = 0; i < classtmp.curstom_num[0]; i++) {
            fprintf(stderr, "%02x ", classtmp.curstom_num[i + 1]);
        }
    }
}

void SetHEART(int argc, char *argv[]) {
    CLASS25 class4500 = {};
    CLASS26 class4510 = {};
    memset(&class4500, 0, sizeof(CLASS25));
    memset(&class4510, 0, sizeof(CLASS26));
    readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
    readCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);

    int tmpval = 0;//分钟
    if (argc > 2) {
        sscanf(argv[2], "%d", &tmpval);
        class4500.commconfig.heartBeat = tmpval;
        class4510.commconfig.heartBeat = tmpval;
        saveCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
        saveCoverClass(0x4510, 0, &class4510, sizeof(CLASS26), para_vari_save);
        setOIChange_CJ(0x4500);
        setOIChange_CJ(0x4510);
    } else {
        fprintf(stderr, "\n心跳周期:%d s \n", class4500.commconfig.heartBeat);
    }
}

void SetApn(int argc, char *argv[]) {
    CLASS25 class4500;
    COMM_CONFIG_1 config1;
    char apnbuf[VISIBLE_STRING_LEN - 1];
    memset(&config1, 0, sizeof(COMM_CONFIG_1));
    memset(&class4500, 0, sizeof(CLASS25));
    readCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
    fprintf(stderr, "\n读出 APN : %s\n", &class4500.commconfig.apn[1]);
    if (argc > 2) {
        memset(apnbuf, 0, sizeof(apnbuf));
        if (sscanf(argv[2], "%s", apnbuf)) {
        	fprintf(stderr,"apnlen = %d\n",strlen(apnbuf));
            class4500.commconfig.apn[0] = strlen(apnbuf);
            memcpy(&class4500.commconfig.apn[1], apnbuf, sizeof(apnbuf));
            fprintf(stderr, "\n存储前 APN : %s\n", &class4500.commconfig.apn[1]);
            saveCoverClass(0x4500, 0, &class4500, sizeof(CLASS25), para_vari_save);
            write_apn((char *) &class4500.commconfig.apn[1]);
            setOIChange_CJ(0x4500);
        }
    }
}

void Init_4500() {
    CLASS25 obj;
    memset(&obj, 0, sizeof(obj));
    obj.commconfig.workModel = 1;
    obj.commconfig.onlineType = 0;
    obj.commconfig.connectType = 0;
    obj.commconfig.appConnectType = 0;
    memcpy(&obj.commconfig.apn[1], "cmcc", 4);
    memcpy(&obj.commconfig.userName[1], "user", 4);
    memcpy(&obj.commconfig.passWord[1], "user", 4);
    memcpy(&obj.commconfig.proxyIp[1], "0.0.0.0", 7);
    obj.commconfig.proxyPort = 0;
    obj.commconfig.timeoutRtry = 3;
    obj.commconfig.heartBeat = 60;
    memcpy(&obj.master.master[0].ip[1], "192.168.0.97", sizeof("192.168.0.97"));
    obj.master.master[0].port = 5022;

    saveCoverClass(0x4500, 0, (void *) &obj, sizeof(CLASS25), para_vari_save);
    setOIChange_CJ(0x4500);
}

void inoutdev_process(int argc, char *argv[]) {
    int tmp = 0;
    OI_698 oi = 0;

    if (argc >= 2) { // dev pro
        if (strcmp(argv[1], "dev") == 0) {
            sscanf(argv[3], "%04x", &tmp);
            oi = tmp;
            if (strcmp(argv[2], "pro") == 0) {
                switch (oi) {
                    case 0xf203:
                        printF203();
                        break;
                    case 0xf101:
                        printF101();
                        break;
                    case 0xf205:
                        printF205();
                        break;
                    case 0xf209:
                        printF209();
                        break;
                }
            } else {
                switch (oi) {
                    case 0xf101:
                        SetF101(argc, argv);
                        break;
                }
            }
            if (strcmp(argv[2], "init") == 0) {
                sscanf(argv[3], "%04x", &tmp);
                oi = tmp;
                switch (oi) {
                    case 0x4500:
                        Init_4500();
                        break;
                }
            }
        }
    }
}


void SetF201(int argc, char *argv[])
{
    CLASS_f201 oif201[3] = {};
    int serno = 0;
    INT8U	i=0;
    if (argc != 8 || (atoi(argv[2])<0 && atoi(argv[2])>2) ||
    	(atoi(argv[3]) < 0 && atoi(argv[3]) > 255) || (atoi(argv[4]) < 0 && atoi(argv[4]) > 2) ||
        (atoi(argv[5]) > 5 && atoi(argv[5]) > 8) ||  (atoi(argv[6]) < 0 && atoi(argv[6]) > 2) ||
        (atoi(argv[7]) < 0 && atoi(argv[7]) > 3)) {
        fprintf(stderr, "使用方法，括号内的数字是需要设置的参数\n");

        fprintf(stderr,"参数配置说明\n");
        fprintf(stderr,"参数1:485_I(0),485_II(1),485_III(2)\n");
        fprintf(stderr,
                "参数2：波特率：bps300(0),bps600(1),bps1200(2),bps2400(3),bps4800(4),bps7200(5),\n"\
                "             bps9600(6),bps19200(7),bps38400(8),bps57600(9),bps115200(10)"\
                        ",auto(255)\n");
        fprintf(stderr, "参数3：校验方式：none(0), odd(1), even(2)\n");
        fprintf(stderr, "参数4：数据位：d5(5), d6(6), d7(7),d8(8)\n");
        fprintf(stderr, "参数5：停止位：stop0(0), stop1(1), stop2(2)\n");
        fprintf(stderr, "参数6：端口功能：上行通信(0), 抄表(1), 级联(2)，停用(3)\n");

        if (readCoverClass(0xf201, 0, oif201, sizeof(CLASS_f201)*3, para_vari_save) > 0) {
        	for(i=0;i<3;i++) {
				fprintf(stderr,"\n\n读取485_[%d]参数如下:",i+1);
				fprintf(stderr, "\n当前描述符(%s)：波特率(%d)，校验方式(%d)，数据位(%d)，停止位(%d)，端口功能(%d)\n", oif201[i].devdesc,
						oif201[i].devpara.baud,oif201[i].devpara.verify,oif201[i].devpara.databits,oif201[i].devpara.stopbits,
						oif201[i].devfunc);
        	}
        }
        return;
    }
    readCoverClass(0xf201, 0, oif201, sizeof(CLASS_f201)*3, para_vari_save);
    serno = atoi(argv[2]);
    fprintf(stderr,"当前设置485_(%d)口设置\n",(serno+1));
    if(serno>2) return;
    oif201[serno].devpara.baud = atoi(argv[3]);
    oif201[serno].devpara.verify = atoi(argv[4]);
    oif201[serno].devpara.databits = atoi(argv[5]);
    oif201[serno].devpara.stopbits = atoi(argv[6]);
    oif201[serno].devfunc = atoi(argv[7]);
    switch(oif201[serno].devfunc) {
    case 0:memcpy(oif201[serno].devdesc,"698",3);break;
    case 1:memcpy(oif201[serno].devdesc,"645",3);break;
    case 2:memcpy(oif201[serno].devdesc,"uplink",6);break;
    case 3:memcpy(oif201[serno].devdesc,"stop",4);break;
    }
    saveCoverClass(0xf201, 0, &oif201, sizeof(CLASS_f201)*3, para_vari_save);
    setOIChange_CJ(0xf201);
}

void SetF202(int argc, char *argv[]) {
    CLASS_f202 oif202 = {};

    if (argc != 6 || (atoi(argv[2]) < 0 && atoi(argv[2]) > 255) || (atoi(argv[3]) < 0 && atoi(argv[3]) > 2) ||
        (atoi(argv[4]) > 5 && atoi(argv[4]) > 8) ||
        (atoi(argv[5]) < 0 && atoi(argv[5]) > 2)) {
        fprintf(stderr, "使用方法，括号内的数字是需要设置的参数\n");

        fprintf(stderr,
                "波特率：bps300(0),bps600(1),bps1200(2),bps2400(3),bps4800(4),bps7200(5),\nbps9600(6),bps19200(7),bps38400(8),bps57600(9),bps115200(10)"
                        ",auto(255)\n");
        fprintf(stderr, "校验方式：none(0), odd(1), even(2)\n");
        fprintf(stderr, "数据位：d5(5), d6(6), d7(7),d8(8)\n");
        fprintf(stderr, "停止位:stop0(0), stop1(1), stop2(2)\n");

        if (readCoverClass(0xf202, 0, &oif202, sizeof(CLASS_f202), para_vari_save) > 0) {
            fprintf(stderr, "\n\n当前配置：波特率(%d)，校验方式(%d)，数据位(%d)，停止位(%d)\n", oif202.devpara.baud, oif202.devpara.verify,
                    oif202.devpara.databits,
                    oif202.devpara.stopbits);
        }
        return;
    }

    oif202.devpara.baud = atoi(argv[2]);
    oif202.devpara.verify = atoi(argv[3]);
    oif202.devpara.databits = atoi(argv[4]);
    oif202.devpara.stopbits = atoi(argv[5]);
    saveCoverClass(0xf202, 0, &oif202, sizeof(CLASS_f202), para_vari_save);
    setOIChange_CJ(0xf202);
}
