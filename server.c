#include "server.h"

//初始化全局结构体
struct info server_info={
				.cdev_beep = "/dev/qq_beep",
				.cdev_moto = "/dev/qq_moto",
				.cdev_yuntai = "/dev/qq_yuntai",
			  .cdev_cam = "/dev/video0",
        .motoL_dir = 0,
				.motoL_min = 0,
				.motoL_max = 20,
        .motoL_default=0,
				.motoR_dir =2,
				.motoR_min = 0,
				.motoR_max = 20,
        .motoR_default=0,
				.yuntai_H_min = 4,
				.yuntai_H_max = 23,
				.yuntai_H_default = 14,
				.yuntai_V_min = 4,
				.yuntai_V_max = 23,
				.yuntai_V_default = 14,
				.lastcmd="Init ok",
				.net={
						.server_ip="localhost",
						.cmd_cfd=0,
						.img_cfd=0,
						.net_signal=0,
						.net_delay=1000,
						.cmd_socket="Inited",
						.img_socket="Inited",
						.cmd_rx=0,
						.cmd_tx=0,
						.img_rx=0,
						.img_tx=0,
				},
				.cam={
						.width=320,
						.height=240,
						.fps=100,
						.format="MJPEG",
				},
};


int main(int argc,char * argv)
{
  int ret;
  pthread_t dis_id,cmd_id,img_id,cam_id;

  pthread_mutex_init(&mutex,NULL);
  //拦截ctrl+c退出消息
  signal(SIGINT,server_exit);
  signal(SIGPIPE,SIG_IGN);

  //打开所有设备文件,及对其初始化
  init_dev();
  ret=init_camera();
  ret=init_network();
  if(ret<0) return -1;  
  ret=pthread_create(&cmd_id,NULL,net_cmd,NULL); //启动cmd网络线程
  ret=pthread_create(&cam_id,NULL,cam_work,NULL); //启动摄像头采集线程
  
  sleep(2); 
  //显示车辆参数
  //ret=pthread_create(&dis_id,NULL,display_zz,NULL);
  
  pthread_join(cmd_id,0);
  return 0;
}

//初始化设备
int init_dev(void)
{
  int ret=0;

  //初始化beep
  printf("Init beep ...");
  server_info.beep_fd = open(server_info.cdev_beep,O_RDWR);
  if (server_info.beep_fd<0) 
  printf("...fail\n");
  else
  printf("...ok\n");

  //初始化马达
  printf("Init moto ...");
  server_info.moto_fd = open(server_info.cdev_moto,O_RDWR);
  if (server_info.moto_fd<0)
  printf("...fail\n");
  else
  printf("...ok\n");

  //初始化云台
  printf("Init yuntai ...");
  server_info.yuntai_fd = open(server_info.cdev_yuntai,O_RDWR);
  if (server_info.yuntai_fd<0)
  printf("...fail\n");
  else
  printf("...ok\n");
  return ret;
}

void server_exit(int signo)
{
  printf("server exit\n");
  close(server_info.cam.cam_fd);
  exit(0);
}
