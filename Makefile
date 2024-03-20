# Compatiable with DP4C
DP4C			= 0
RAM_SIZE_KB 	= 256
ifeq (${DP4C}, 1)
	CONF_LOOP_WR= $(shell expr $(RAM_SIZE_KB) \* 4 )
else
	CONF_LOOP_WR= $(shell expr $(RAM_SIZE_KB) )
endif
CC_PARAM 		+= -DCONF_LOOP_WR=$(CONF_LOOP_WR)

all:
	gcc -o t_send sendPacket.c sender_test.c -lnet -lpcap $(CC_PARAM)

.PHONY: clean help
clean:
	rm t_send
help:
	@echo "--------------------------------------------------------------"
	@echo "You can use 'make RAM_SIZE_KB=128' to specify the RAM size."
	@echo "You can use 'make DP4C=1' to be compatiable with DP4C."
	@echo "--------------------------------------------------------------"
