#include "send_recv.h"


void get_packet(unsigned char *argument, const struct pcap_pkthdr *p_pkthdr, const unsigned char *packet_content){
	
	// if(packet_content[13]!=0x00)
	//	printf("type is %02x%02x\n", packet_content[12], packet_content[13]);
	if((packet_content[12] == 0x90)&&(packet_content[13] == 0x05)){
		// uint8_t length = packet_content[15];
		// int i;
		// for (i = 0; i < length; ++i){
		// 	printf("%c", packet_content[16+i]);
		// 	// printf("%02x\n", packet_content[16+i]);
		// }
		if(packet_content[15] == 0x02){
			printf("dtcm_sel is %d\n", packet_content[29]);
		}
		else if(packet_content[15] == 0x04){
			// printf("itcm data is %02x%02x%02x%02x\n", packet_content[18],packet_content[19],packet_content[20],packet_content[21]);
			printf("tcm data is %02x%02x%02x%02x\n", packet_content[22],packet_content[23],packet_content[24],packet_content[25]);
			printf("addr is %02x%02x%02x%02x\n", packet_content[26],packet_content[27],packet_content[28],packet_content[29]);
		}
	}
}


void recv_print_value(){
	int recvPktPID=0;


	pcap_t * pcap_h = NULL;  
	char error_content[100] = "";
	const unsigned char *packet = NULL;
	char *p_net_interface_name = NULL;
	struct pcap_pkthdr p_pkthdr;

	p_net_interface_name = pcap_lookupdev(error_content);  
	if(NULL == p_net_interface_name) {  
		perror("pcap_lookupdev");  
		exit(-1);  
	}  
	// printf("interface: %s\n", p_net_interface_name); 

	pcap_h = pcap_open_live("enp0s3",BUFSIZE,1,10,error_content);
	// pcap_h = pcap_open_live(p_net_interface_name,BUFSIZE,0,0,error_content);
	if(pcap_h == NULL){
		printf("error_pcap_handle\n");
		exit(0);
	}

	//BPF filter;
	// struct bpf_program filter;
	// pcap_compile(pcap_h, &filter, "ehter dst 00:01:02:03:04:05", 1, 0);
	
	// pcap_setfilter(pcap_h, &filter);

	if(pcap_loop(pcap_h,-1,get_packet,NULL)<0){
		
		perror("pcap_loop");
		exit(-1);
	}
  
    pcap_close(pcap_h);
	
} 


// #include <pcap.h>  
// #include <time.h>  
// #include <stdlib.h>  
// #include <stdio.h>  
  
// void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)  
// {  
//   int * id = (int *)arg;  
    
//   printf("id: %d\n", ++(*id));  
//   printf("Packet length: %d\n", pkthdr->len);  
//   printf("Number of bytes: %d\n", pkthdr->caplen);  
//   printf("Recieved time: %s", ctime((const time_t *)&pkthdr->ts.tv_sec));   
    
//   int i;  
//   for(i=0; i<pkthdr->len; ++i)  
//   {  
//     printf(" %02x", packet[i]);  
//     if( (i + 1) % 16 == 0 )  
//     {  
//       printf("\n");  
//     }  
//   }  
    
//   printf("\n\n");  
// }  
  
// int main()  
// {  
//   char errBuf[PCAP_ERRBUF_SIZE], * devStr;  
    
//   /* get a device */  
//   devStr = pcap_lookupdev(errBuf);  
    
//   if(devStr)  
//   {  
//     printf("success: device: %s\n", devStr);  
//   }  
//   else  
//   {  
//     printf("error: %s\n", errBuf);  
//     exit(1);  
//   }  
    
//   /* open a device, wait until a packet arrives */  
//   pcap_t * device = pcap_open_live(devStr, 65535, 1, 0, errBuf);  
    
//   if(!device)  
//   {  
//     printf("error: pcap_open_live(): %s\n", errBuf);  
//     exit(1);  
//   }  
    
//   /* wait loop forever */  
//   int id = 0;  
//   if(pcap_loop(device, -1, getPacket, (u_char*)&id)<0){
//   	printf("%s\n", "pcap_loop error");
//   }
    
//   pcap_close(device);  
  
//   return 0;  
// }


