#include "server.h"

#define cmd_port 1110
#define img_port 1111

#define cmdcfd server_info.net.cmd_cfd
#define imgcfd server_info.net.img_cfd
#define cmd_fd server_info.net.cmd_fd
#define img_fd server_info.net.img_fd
static struct sockaddr_in cmd_addr,img_addr,cmd_peer,img_peer;
static socklen_t len=sizeof(struct sockaddr_in);

void *net_cmd(void *arg)
{
  int ret;
  if(listen(cmd_fd,2)==-1)
  {
  perror("listen");
  pthread_exit((void *)-1);
  }
  while(1)
  {
    cmdcfd=accept(cmd_fd,(struct sockaddr *)&cmd_peer,&len);

    strcpy(server_info.net.cmd_socket ,"connected");

    while(cmdcfd)
    {
     ret=read(cmdcfd,server_info.lastcmd,64);
     if(ret>0)
      {
       server_info.lastcmd[ret]=0;
       check_cmd(server_info.lastcmd);
       server_info.net.cmd_rx+=ret-1;
      }
     if(ret <=0)
     {
      strcpy(server_info.net.cmd_socket ,"disconnected");
      close(cmdcfd);
      cmdcfd=0;
     }
    }
  }
}

int init_network(void)
{
  int ret=0;
  int opt=1;
  int opt_len= sizeof(opt);
  printf("Createing network socket...");

  cmd_fd=socket(AF_INET,SOCK_STREAM,0);
  img_fd=socket(AF_INET,SOCK_STREAM,0);  
  if(cmd_fd==-1||img_fd==-1)
  {
    perr("socket")
		return -1;
  }

  setsockopt(cmd_fd,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,opt_len);
  setsockopt(img_fd,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,opt_len);

  cmd_addr.sin_family=AF_INET;
  img_addr.sin_family=AF_INET;

  cmd_addr.sin_port = htons(cmd_port);
  img_addr.sin_port = htons(img_port);
  
  cmd_addr.sin_addr.s_addr=INADDR_ANY;
  img_addr.sin_addr.s_addr=INADDR_ANY;
  
  ret=bind(cmd_fd,(struct sockaddr *)&cmd_addr,sizeof(cmd_addr));
  if(ret==-1)
  {
   perr("bind")
   return -1;
  }

  ret=bind(img_fd,(struct sockaddr *)&img_addr,sizeof(img_addr));
  if(ret==-1)
  {
   perr("bind")
   return -1;
  } 

  
  if(listen(img_fd,2)==-1)
  {
  perror("listen");
  pthread_exit((void *)-1);
  printf("...ok\n");
 }
  return ret;
}
