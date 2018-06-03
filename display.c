#include "server.h"
//显示参数界面

//方向数值到字符串转换
void cdir2char(char * motoL_dir,char * motoR_dir,int l,int r)
{
  if(l==0) strcpy(motoL_dir,"Front");
  if(l==1) strcpy(motoL_dir,"Back");
  if(r==2) strcpy(motoR_dir,"Front");
  if(r==3) strcpy(motoR_dir,"Back");
}

void *display_zz(void * arg)
{
  char motoL_dir[6],motoR_dir[6];
  //打印flag
 while(1)
 {
  usleep(200*1000);  
  system("clear");
  printf("\033[1;0H ********************************************************\n\033[0m");
  printf("\033[2;0H *                  QinQi wifi car Ver 1.0              *\n\033[0m");
  printf("\033[3;0H ********************************************************\n\033[0m");
 
  //打印cammer信息
  printf("\033[4;0H ------------------------ Camera ------------------------\n \033[0m");
  printf("\033[5;0H Camera device: %s Format: Mjpeg\n\033[0m",server_info.cdev_cam);
  printf("\033[6;0H Width: 800 Height: 600 Fps: 120\n \033[0m");
  //printf("\033[8;0H ----------------------------------------\n \033[0m"); 
  printf("\033[7;0H ------------------------- Moto -------------------------\n \033[0m");
  printf("\033[8;0H Moto device: %s\n \033[0m",server_info.cdev_moto);
  cdir2char(motoL_dir,motoR_dir,server_info.motoL_dir,server_info.motoR_dir);
  printf("\033[8;30H Direct L: %s R: %s \033[0m",motoL_dir,motoR_dir);
  printf("\033[9;0H L:>>>>>>>>>>>>>>>>>>>> 100%\033[0m");
  printf("\033[9;30H R:>>>>>>>>>>>>>>>>>>>> 100%\033[0m");
  printf("\033[10;0H L Arg: Min=%d Max=%d Def=%d \n \033[0m",\
							server_info.motoL_min,server_info.motoL_max,\
              server_info.motoL_default);
  printf("\033[10;30H R Arg: Min=%d Max=%d Def=%d \n \033[0m",\
							server_info.motoR_min,server_info.motoR_max,\
              server_info.motoR_default);
  //printf("\033[16;0H ----------------------------------------\n \033[0m");
  
  printf("\033[11;0H ------------------------ YunTai ------------------------\n \033[0m");
  printf("\033[12;0H YunTai device: %s\n \033[0m",server_info.cdev_yuntai);
  printf("\033[13;0H H:>>>>>>>>>>>>>>>>>>>> 100%\033[0m");
  printf("\033[13;30H V:>>>>>>>>>>>>>>>>>>>> 100%\033[0m");
  printf("\033[14;0H H: Min=%d Max=%d Def=%d \n \033[0m",\
							server_info.yuntai_H_min,server_info.yuntai_H_max,\
              server_info.yuntai_H_default);
  printf("\033[14;30H V: Min=%d Max=%d Default=%d \n \033[0m",\
							server_info.yuntai_V_min,server_info.yuntai_V_max,\
              server_info.yuntai_V_default);
  
  printf("\033[15;0H -------------------------- NET -------------------------\n \033[0m");
  printf("\033[16;0H IP:%s",server_info.net.server_ip); 
  printf("\033[16;24H Signal:%dDB",server_info.net.net_signal);
  printf("\033[16;42H Delay:%dms\n \033[0m",server_info.net.net_delay);

  printf("\033[17;0H Cmd_socket:%s",server_info.net.cmd_socket);
  printf("\033[17;30H Img_socket:%s \n \033[0m",server_info.net.img_socket);
  printf("\033[18;30H IMG RX:%lld",\
          server_info.net.img_rx>1000*1000?server_info.net.img_rx/\
          (1000*1000):server_info.net.img_rx); 
  printf("\033[18;45H TX:%lld \033[0m",server_info.net.img_tx/1000);
  printf("\033[18;0H CMD RX:%lld",server_info.net.cmd_rx);
  printf("\033[18;17H TX:%lld \033[0m",server_info.net.cmd_tx/1000);
  printf("\033[19;0H CMD:%s",server_info.lastcmd);
  printf("\033[20;0H --------------------------------------------------------\n \033[0m");
 }//end while
 return 0;
}
