#include "server.h"
int ioctl_cmd(int fd,int arg1,int arg2)
{
  printf("ioctl %d\n",fd);
  ioctl(fd,arg1,arg2);
 
  return 0;
}


int check_cmd(char *cmd)
{
  int ret=0;
   printf("first debug %s\n",cmd);
  //分离命令
  //停车命令 原型 stop:0 需设置motoL和motoR motoL的pwm输出0
   if(strncmp(cmd,"stop:",5)==0)
    {
     printf("debug stop\n");
     server_info.motoL_default=0;
     server_info.motoR_default=0;
     ioctl_cmd(server_info.moto_fd,0,server_info.motoL_default);     
     ioctl_cmd(server_info.moto_fd,2,server_info.motoR_default);     
     return 0;
    }
 
  //前进命令 原型 front:25  需设置motoL和motoR的dir为0和2,pwm输出:后的值
  if(strncmp(cmd,"front:",6)==0)
  {
   strsep(&cmd,":");
   server_info.motoL_default=atoi(strsep(&cmd,":"));
   server_info.motoR_default=server_info.motoL_default; 

   printf("debug front %d\n",server_info.motoL_default);
   ioctl_cmd(server_info.moto_fd,0,server_info.motoL_default);     
   ioctl_cmd(server_info.moto_fd,2,server_info.motoR_default);     
   return 0;
  }

  //后退命令 原型 back:25  需设置motoL和motoR的dir为1和3,pwm输出:后的值
  if(strncmp(cmd,"back:",5)==0)
  {
   strsep(&cmd,":");
   printf("debug back\n");
   server_info.motoL_default=atoi(strsep(&cmd,":"));
   server_info.motoR_default=server_info.motoL_default; 
   ioctl_cmd(server_info.moto_fd,1,server_info.motoL_default);     
   ioctl_cmd(server_info.moto_fd,3,server_info.motoR_default);     
   return 0;
  }

  //左右转命令 原型 left:25:25  需设置motoL和motoR的dir为0和2,pwm输出:后L的值和R的值
  if(strncmp(cmd,"left:",5)==0 || strncmp(cmd,"right:",6)==0)
  {
   printf("debug l or r\n");
   strsep(&cmd,":");
   server_info.motoL_default=atoi(strsep(&cmd,":"));
   server_info.motoR_default=atoi(strsep(&cmd,":"));
   ioctl_cmd(server_info.moto_fd,0,server_info.motoL_default);     
   ioctl_cmd(server_info.moto_fd,2,server_info.motoR_default);     
   return 0;
  }
// turnleft  
if(strncmp(cmd,"turnl:",6)==0)
  {
   printf("debug trun left\n");
   server_info.motoL_default=20000000;
   server_info.motoR_default=20000000;
   ioctl_cmd(server_info.moto_fd,1,server_info.motoL_default);     
   ioctl_cmd(server_info.moto_fd,2,server_info.motoR_default);     
   return 0;
  }
  
// turnright  
if(strncmp(cmd,"turnr:",6)==0)
  {
   printf("debug trun right\n");
   server_info.motoL_default=20000000;
   server_info.motoR_default=20000000;
   ioctl_cmd(server_info.moto_fd,0,server_info.motoL_default);     
   ioctl_cmd(server_info.moto_fd,3,server_info.motoR_default);     
   return 0;
  }
 // if(strncmp(cmd,"motoL:",6))index_cmd=0; //控制motoL的命令
  
 // if(strncmp(cmd,"motoR:",6))index_cmd=0; //控制motoR的命令
  
  //云台水平移动命令 原型 yuntaiH:25  需设置,pwm输出:后的值和步进时的值,编号0
  if(strncmp(cmd,"yuntaiH:",8)==0) //控制云台水平的命令
  {
   strsep(&cmd,":");
   server_info.yuntai_H_default=atoi(strsep(&cmd,":"));
   ioctl_cmd(server_info.yuntai_fd,0,server_info.yuntai_H_default);     
   return 0;
  }
  
  //云台垂直移动命令 原型 yuntaiV:25  需设置,pwm输出:后的值和步进时的值，编号1
  if(strncmp(cmd,"yuntaiV:",8)==0) //控制云台垂直的命令
  {
   strsep(&cmd,":");
   server_info.yuntai_V_default=atoi(strsep(&cmd,":"));
   ioctl_cmd(server_info.yuntai_fd,1,server_info.yuntai_V_default);     
   return 0;
  } 
 
  if(strncmp(cmd,"beep:",5)==0); //控制喇叭的命令
 
  //执行命令

}
