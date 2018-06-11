/* Auther: ChuJK
 * Date: 2011.8.13
 * 主函数文件
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include "device.h"
#include "server.h"


//信号处理函数
void sig_handler(int signo)
{
	if(signo == SIGINT)
	{
		if(on_off)
			cam_off();//关闭摄像头
		uninit_socket();//卸载服务器
		uninit_dev();//卸载设备
		exit(0);
	}
	if(signo == SIGPIPE)
	{
		printf("SIGPIPE!\n");
	}
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"-usage: %s [dev] [port]\n",argv[0]);
		exit(1);
	}

	//设置信号
	//当收到CTRL+C的信号时候停止捕获图像
	if(signal(SIGINT,sig_handler) == SIG_ERR)
	{
		fprintf(stderr,"signal: %s\n",strerror(errno));
		exit(1);
	}
	if(signal(SIGPIPE,sig_handler) == SIG_ERR)
	{
		fprintf(stderr,"signal: %s\n",strerror(errno));
		exit(1);
	}

	//清屏
	printf("\033[1H\033[2J");
	fflush(stdout);

	camera_fd = open(argv[1],O_RDWR|O_NONBLOCK,0);
	get_dev_info();
	init_dev();//初始化设备
	get_dev_info();

	int port = atoi(argv[2]);
	init_socket(port);//初始化服务器socket

	lis_acc(20);//监听并处理请求

	return 0;
}
