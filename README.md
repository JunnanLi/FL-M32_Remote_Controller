# Controller
## Files
There are 5 files in this folder:

|---------------|--------------------------------------------------|
| File name     | Function description                             |
|---------------|--------------------------------------------------|
| send_recv.h   | Header file                                      |
|---------------|--------------------------------------------------|
| sendPacket.c  | Used to send Ethernet packet (0x9005) to         |
|               |  configure Core leveraging libpcap, 0x00 is      |
|               |  used to start program; 0x01 is used to start    |
|               |  configuration; 0x02 is used to read cpu state   |
|               |  (pause or start); 0x03 is used to load program; |
|               |  0x04 is used to read program loaded in CPU      |
|---------------|--------------------------------------------------|
|sender_test.c  | Has a main function used to configure Core       |
|---------------|--------------------------------------------------|
|recvPacket.c   | Used to receive Ehternet packet returned from    |
|               |  CPU, 0x02 is state; 0x04 is program loade       |
|               |  in CPU; 0x05 is "printf" in running progra      |
|receive_test.c |  Has a main function used to print information   |
|               |  returned from CPU                               |
|---------------|--------------------------------------------------|

## Usage
1) Run Makefile (i.e., `make` ) to generate two binary program, i.e., t_send & t_recv
2) Run t_send (i.e., `./t_send`) to configure CPU, you will see a simplied UI, And you can chose any option by inputing the corresponding digit：
    //======================================================//  
	Please chose your option:  
	0:	   set sel to 0, i.e., running mode
	1:	   set sel to 1, i.e., configuring mode
	2:	   read sel
	3:	   configure instruction
	4:	   read instruction
	5:	   open/close black pressure
	6:	   set sel to f, i.e., configuring mode
	Note:  current RAM size is 128 KB  
	//======================================================//  
	opt is:  

    For example,  we run the example program by inputing `3` to configure intstuction, and then `0` to run the program  
3) You can use 'make RAM_SIZE_KB=128' to specify the RAM size.
4) You can run 'make help' for help;