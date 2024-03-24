RAM_SIZE_KB 	= 256
DP4C			= 0
ifeq (${DP4C}, 1)
	CONF_LOOP_WR= $(shell expr $(RAM_SIZE_KB) \* 4 )
else
	CONF_LOOP_WR= $(shell expr $(RAM_SIZE_KB) )
endif
CC_PARAM 		+= -DCONF_LOOP_WR=$(CONF_LOOP_WR)
CC_PARAM 		+= -DRAM_SIZE_KB=$(RAM_SIZE_KB)
CC_PARAM 		+= -DDP4C=$(DP4C)

all:
	gcc -o t_send sendPacket.c sender_test.c -lnet -lpcap $(CC_PARAM)
	gcc -o t_recv recvPacket.c receiver_test.c -lpcap

.PHONY: clean help
clean:
	rm t_send
	rm t_recv
help:
	@echo "--------------------------------------------------------------"
	@echo "You can use 'make RAM_SIZE_KB=256' to specify the RAM size."
	@echo "You can use 'make DP4C=1' to be compatiable with DP4C."
	@echo "--------------------------------------------------------------"
