#include "send.h"

void send_packet(struct send_ctx *sendCtx)
{

	char err_buf[100] = "";
	libnet_t *lib_net = NULL;
	libnet_ptag_t lib_t = 0;
	unsigned char src_mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
	unsigned char dst_mac[6] = {0x88,0x88,0x88,0x88,0x89,0x88};
	    
      
//	lib_net = libnet_init(LIBNET_LINK_ADV, "enp0s3", err_buf);
	lib_net = libnet_init(LIBNET_LINK_ADV, "wlp0s20f3", err_buf);
	// lib_net = libnet_init(LIBNET_LINK_ADV, "enx00e04d6da7b3", err_buf);
	
	if(NULL == lib_net)  
	{  
	    perror("libnet_init");  
	    exit(-1);  
	}  


	// set sel = 1;
	lib_t = libnet_build_ethernet(
		(u_int8_t *)dst_mac,  
		(u_int8_t *)src_mac,  
		sendCtx->type,
		(u8 *) &(sendCtx->payload),	// payload 
		sendCtx->lens,  			// payload length
		lib_net,  
		0  
	);  
    
	int res = 0;  
	res = libnet_write(lib_net);
	if(-1 == res)  
	{  
	    perror("libnet_write");  
	    exit(-1);  
	}

	libnet_destroy(lib_net);     
	// printf("----ok-----\n");
} 

#if(DP4C==1)
	void read_tcm(int lineNum){
		struct send_ctx *sendCtx;
		sendCtx = (struct send_ctx *)malloc(sizeof(struct send_ctx));
		struct one_128b *one128b = &(sendCtx->payload.one128b[0]);
		one128b->pad            = htonl(0);
		one128b->tcm_data       = htonl(0);
		one128b->addr           = htonl(lineNum);
	    one128b->conf_type[0]   = htons(4);
	    one128b->conf_type[1]   = one128b->conf_type[0];
		sendCtx->type           = 0x9005;
		sendCtx->lens           = 50;
		send_packet(sendCtx);
	}

	void open_backPressure(int value){
	    struct send_ctx *sendCtx;
		sendCtx                     = (struct send_ctx *)malloc(sizeof(struct send_ctx));
	    sendCtx->type               = 0x9005;
		struct one_128b *one128b    = &(sendCtx->payload.one128b[0]);
		value                       = (value << 8) + 6;
	    one128b->conf_type[0]       = htons(value);
	    one128b->conf_type[1]       = one128b->conf_type[0];
		one128b->pad                = htonl(0);
		one128b->tcm_data           = htonl(0);
		one128b->addr               = htonl(0);
		sendCtx->lens               = 50;

		send_packet(sendCtx);
	}
	#else
	void set_read_sel(int read, u32 value){
		struct send_ctx *sendCtx;
		sendCtx                 = (struct send_ctx *)malloc(sizeof(struct send_ctx));
		struct context *payload;
		payload             	= &(sendCtx->payload);
		if(read == 1)
			payload->conf_type 	= htons(2);
		else
			payload->conf_type 	= htons(1);
		payload->check_sum		= 0;
		payload->pad[0]			= 0;
		payload->pad[1]			= 0;
		payload->tcm_addr 		= 0;
		sendCtx->type           = 0x9005;
		sendCtx->lens           = 50;
		send_packet(sendCtx);
	}

	void write_tcm(char *fileName, int lineNum){
		FILE * fp;
		if((fp = fopen(fileName,"r")) == NULL){
			perror("fail to read");
			exit (1) ;
		}

		u32	data;
		int i;
		for(i=0; i<lineNum; i++){
			fscanf(fp,"%08x\n", &data);
		}

		struct send_ctx *sendCtx;
		sendCtx = (struct send_ctx *)malloc(sizeof(struct send_ctx));
		struct context *payload;
		payload             	= &(sendCtx->payload);
		payload->conf_type   	= htons(3);
		payload->check_sum		= 0;
		payload->pad[0]			= 0;
		payload->pad[1]			= 0;
		payload->tcm_addr 		= htons(lineNum);
		for (i=0; i<256; i++){
			fscanf(fp,"%08x\n", &data);
			payload->tcm_data[i]= htonl(data);
		}
	    
		sendCtx->type           = 0x9005;
		sendCtx->lens           = 1024 + 16;
		send_packet(sendCtx);

		fclose(fp);
	}
#endif


