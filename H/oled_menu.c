#include "oled_menu.h"

int8_t b01=0,k3[2]={0,0},oled_mode;
const char* value_name[selNUM]={"test0","test1","test2","test3","test4","test5","test6","test7","test8","test9"};
/*
 * k3 -> 0 ：选择第几个
 * k3 -> 1 ：虚线框的位置
 */

void oled_sel0(void){
	for (uint8_t i=0;i<3;i++){
		OLED_DrawBoxLine(0,22*i,127,19+22*i,1);
		if (i==k3[1])
			OLED_DrawBoxXuLine(0,22*i,127,19+22*i,2,b01);

		OLED_ShowString(2,1+22*i,(char*)value_name[k3[0]-k3[1]+i],16,1);
	}

	if (!ReadKEY1){
		k3[0]++;
		k3[1]++;
		if (k3[1]==3){
			k3[1]=2;
			if (k3[0]==selNUM)
				k3[0]--;
		}
	}
	if (!ReadKEY2){
		k3[0]--;
		k3[1]--;
		if (k3[1]==-1){
			k3[1]=0;
			if (k3[0]==-1)
				k3[0]++;
		}
	}
	if (!ReadKEY3){
		oled_mode=1;
		return;
	}
}

void* sel[selNUM]={&quan,&Kp,&Ki,&Kd};
uint8_t sel_info[selNUM][2]={{2,0},{2,2},{2,2},{2,2}};

void oled_sel1(void){
	if (sel_info[k3[0]][1]==0){
	}

	OLED_ShowNumNoLen(6,6,(int32_t)*sel[k3[0]],12,1);
	if (!ReadKEY4){
		oled_mode=0;
		return;
	}
}

void OLED_loop(void) {
	if (oled_mode==0)
		oled_sel0();
	else
		oled_sel1();

	/***************************/
	b01=1-b01;
	OLED_Refresh();
	OLED_ClearRF();
}


/*
 * 字体大小：16
 * 行间隔：15
 *
 * 字体大小：8
 * 行间隔：8
 */
