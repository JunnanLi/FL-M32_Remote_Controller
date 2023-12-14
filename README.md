# 程序配置软件
## 功能简介
通过网络报文远程配置RISCV待执行程序

## 文件描述
包含四个文件，功能如下：

| 文件名        | 功能描述                                         |
|---------------|--------------------------------------------------|
| send.h        | 头文件                                           |
| sendPacket.c  | 通过libnet库构造和发送以太网报文，以配置RISCV程序。报文以太网协议字段为0x9005，后续8b功能字段包含：1）0x00用于启动程序（RISCV进入启动模式）; 2）0x01用于停止程序（RISCV进入配置模式）；3）0x02用于读RISCV核模式；4）0x03用于加载程序；5）0x04用于读已加载的程序      |
|sender_test.c  | 包含main函数，通过接收用户的配置命令，构造相应的配置报文       |
|firmware.hex   | RISCV核待运行的二进制程序（可运行Firmware_Runtime脚本获得）    |

## 使用说明
1) 修改sender_test.c 13行的网口接口名，如`enp0s3`。可以通过在终端输入`ifconfig`获得
2) 运行Makefile (即**make**)用于生成可执行程序，即t_send
3) 运行t_send (即./t_send)以发送配置RISCV核。终端会显示如下简易界面，可以输入相应数字以执行配置功能：

~~~    
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
~~~

    例如，输入`3`，可以将本文件夹内firmware.hex配置到RISCV的存储单元中，接着输入`0`以启动程序  
4) 可以在make后增加参数RAM_SIZE_KB制定RISCV存储单元的大小，如'make RAM_SIZE_KB=128'，目前FL-M32支持64,128,256KB三种.
5) 你还可以运行'make help'查询make支持的参数.
