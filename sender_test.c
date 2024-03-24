#include "send_recv.h"
#include "unistd.h"

// #define MULTI_CORE 1

int main(int argc, char *argv[])
{
	int opt;
	int i;
	while(1){
		system("clear");
		printf("//======================================================//\n");
		printf("\tPlease chose your option:\n");
		printf("\t0:\tstart the 1st PE, single-core running mode\n");
		printf("\t1:\tset sel to f, i.e., configuring mode\n");
		printf("\t2:\tread sel\n");
		printf("\t3:\tconfigure instruction\n");
		printf("\t4:\tread instruction\n");
		printf("\t5:\topen/close black pressure\n");
		printf("\t6:\tstart abcd PEs, multi-core running mode\n");
		printf("\tNote:\tcurrent RAM size: %d KB, DP4C_TAG:%d\n",RAM_SIZE_KB, DP4C);
		printf("//======================================================//\n");
		printf("opt is: ");
		scanf("%d", &opt);

		if(opt == 0){
			//* start PE_0;
			set_read_sel(0, 14);
			//* start all PEs;
			// set_read_sel(0, 0);
			//* start 2 PEs;
			// set_read_sel(0, 12);
		}
		else if(opt == 1){
			set_read_sel(0, 15);
		}

		else if(opt == 2)
			set_read_sel(1, 0);
		else if(opt == 3){
			char fileName[30] = "firmware.hex";
			int lineNum = 0;
			for (i = 0; i < CONF_LOOP_WR; i++){
				#if(DP4C==1)
					lineNum = 64*i;
				#else
					lineNum = 256*i;
				#endif
				write_tcm(fileName, lineNum);
			}
		}
	#if(DP4C==1)
		else if(opt == 4){
			for (i = 0; i < (CONF_LOOP_WR*50); i++){
				read_tcm(i);
			}
		}
		else if(opt == 5){
			system("clear");
			printf("//======================================================//\n");
			printf("\tPlease chose your option:\n");
			printf("\t0:\tclose black pressure\n");
			printf("\t1:\topen black pressure\n");
			printf("//======================================================//\n");
			printf("opt is: ");
			int value;
			scanf("%d", &value);
			open_backPressure(value);
		}
	#endif
		if(opt == 6){
			int bitmap;
			printf("status of pe in bitmap is: (0 is running) ");
			scanf("%d", &bitmap);
			set_read_sel(0, bitmap);
		}
	}

    return 0;
} 
