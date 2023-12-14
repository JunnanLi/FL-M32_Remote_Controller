RAM_SIZE_KB 	= 128
CONF_LOOP_WR	= $(shell expr $(RAM_SIZE_KB) \* 4)
CC_PARAM 		+= -DCONF_LOOP_WR=$(CONF_LOOP_WR)

all:
	gcc -o t_send sendPacket.c sender_test.c -lnet -lpcap $(CC_PARAM)
	gcc -o t_recv recvPacket.c receiver_test.c -lpcap

.PHONY: clean help
clean:
	rm t_send
	rm t_recv
help:
	@echo "--------------------------------------------------------------"
	@echo "You can use 'make RAM_SIZE_KB=128' to specify the RAM size."
	@echo "--------------------------------------------------------------"
