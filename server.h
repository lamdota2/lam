#ifndef _server_h
#define _server_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

#define perr(x) {fflush(stdout);perror(x);return -1;}
pthread_mutex_t mutex;




struct net_info{
				char server_ip[20];
				int cmd_fd;
				int img_fd;
        int cmd_cfd;
        int img_cfd;
				int img_stat; //收发响应状态
				int cmd_stat;
				int net_signal;
				int net_delay;
				char cmd_socket[20];
				char img_socket[20];
				unsigned long long cmd_rx;
				unsigned long long cmd_tx;
				unsigned long long img_rx;
				unsigned long long img_tx;
};

struct cam_info{
				int cam_fd;
				int width;
				int height;
				int fps;
				char format[20];
};

struct info {
				char cdev_beep[20];
				char cdev_moto[20];
				char cdev_yuntai[20];
			        char cdev_cam[20];
                                int motoL_dir;
                                int motoL_min;
				int motoL_max;
                                int motoL_default;
				int motoR_dir;
				int motoR_min;
				int motoR_max;
                                int motoR_default;
				int yuntai_H_min;
				int yuntai_H_max;
				int yuntai_H_default;
				int yuntai_V_min;
				int yuntai_V_max;
				int yuntai_V_default;
				int beep_fd;
				int moto_fd;
				int yuntai_fd;
        char lastcmd[64];
				struct net_info net;
				struct cam_info cam;
}server_info;



//初始化设备函数
int init_dev(void);

//初始化摄像头
int init_camera(void);

//初始化网络
int init_network(void);

//摄像头采集线程
void *cam_work(void *arg);
//网络线程函数
void *net_cmd(void *arg); 
//显示参数
void *display_zz(void * arg);

//程序退出函数
void server_exit(int signo);

  
#endif
