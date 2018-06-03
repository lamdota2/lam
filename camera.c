#include "server.h"

static int cam_flag;
static struct v4l2_capability cap;
static struct v4l2_fmtdesc fmtdesc;
static struct v4l2_frmsizeenum fmtsize;
static struct v4l2_requestbuffers req;
static struct v4l2_format fmt;
static struct v4l2_buffer buf;
char *img[1];

#define camfd server_info.cam.cam_fd	//相机设备

#define img_fd server_info.net.img_fd
#define cmd_fd server_info.net.cmd_fd
#define imgcfd server_info.net.img_cfd
#define cmdcfd server_info.net.cmd_cfd
int read_img(void)
{
  char temp[64];
  int ret;
  /*read()会把参数fd所指的文件传送nbyte个字节到buf指针所指的内存中
  	bytes=read(fd,buf,10);	*/
  ret=read(imgcfd,temp,64);
  if(ret>0)
	{
   //printf("%s\n",temp);
   server_info.net.img_rx+=ret-1;
   return ret;
  }
  if(ret<=0)
  {
   close(imgcfd);
   imgcfd=0;
   strcpy(server_info.net.img_socket,"disconnected");
   return -1;
  }
}


void *cam_work(void *arg)
{
  struct sockaddr_in img_peer;
  socklen_t len=sizeof(struct sockaddr_in);

  struct v4l2_buffer buf_temp;
  int on=1,dst_fd,ret,count,jpg_len;
  char temp[64];

  if(cam_flag<1) return;
  memset(&buf_temp,0,sizeof(buf_temp));
  buf_temp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  buf_temp.memory = V4L2_MEMORY_MMAP;
  
  //开启视频
  if(ioctl(camfd,VIDIOC_STREAMON,&on)<0)
  {
   perror("camera stream");
   return;
  }
  
   while(1)
  {
   //开始监听imgsock
   imgcfd=accept(img_fd,(struct sockaddr *)&img_peer,&len);  
   strcpy(server_info.net.img_socket,"connected");
   while(imgcfd)
   {
    if(ioctl(camfd,VIDIOC_DQBUF,&buf_temp)<0)
    {
     perror("DQBUF");
     cam_flag=0;
     exit(-1);
    }
   //测试将图像写入文件
   //dst_fd=open("./test.bmp",O_RDWR|O_CREAT|O_TRUNC,0777);
   //write(dst_fd,img[buf.index],buf.length);
   //close(dst_fd);
   //dst_fd=open("./test2.bmp",O_RDWR|O_CREAT|O_TRUNC,0777);
   //count =0;
   //while(count<buf.length)
   //{
   //count+=write(dst_fd,img[buf.index]+count,1024);
   //}
   //close(dst_fd);*/
   count=0;
   write(server_info.net.img_cfd,"img_start",9);
   ret=read_img(); 
   if(ret<=0)
   {
   ioctl(camfd,VIDIOC_QBUF,&buf_temp);
   continue;
   }

   int xx;
   printf("%d %d frame\n",xx++,buf_temp.bytesused);
   while(count<buf_temp.bytesused)
   {
    ret=write(server_info.net.img_cfd,img[buf.index]+count,1450);
    if(ret<=0)
    {
     close(imgcfd);
     imgcfd=0;
     break;
    }
    count+=ret;
    server_info.net.img_tx +=ret;
    ret=read_img();
    if(ret<=0)break;
   }
   ioctl(camfd,VIDIOC_QBUF,&buf_temp);
  }//end while
 }//end while
}


int init_camera(void)
{
  int ret=0,i;
  printf("Init camera %s...",server_info.cdev_cam);
  camfd=open(server_info.cdev_cam,O_RDWR);
  if(camfd<0)
  {
   printf("Open error...Ignore\n");
   cam_flag=0;
   return 1;
  }
  
   printf("...ok\n");

   //查询驱动信息
   ioctl(camfd,VIDIOC_QUERYCAP,&cap);
   printf("DriverName:%s\n",cap.driver);
   printf("Card Name:%s \n",cap.card);
   printf("Bus info:%s\n",cap.bus_info);
   printf("DriverVersion:%u.%u.%u\n",\
           (cap.version>>16)&0Xff,\
           (cap.version>>8)&0Xff,\
           cap.version & 0xff);  
     
   //显示当前支持的数据格式Mjpeg yuyv
   fmtdesc.index=0;
   fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   while(ioctl(camfd,VIDIOC_ENUM_FMT,&fmtdesc)!=-1)
   printf("Support:%d %s\n",fmtdesc.index++,fmtdesc.description);

   //显示支持的解析度
   for(i=0;;i++)
   {
     fmtsize.index=i;
     fmtsize.pixel_format = fmtdesc.pixelformat;
     if(ioctl(camfd,VIDIOC_ENUM_FRAMESIZES,&fmtsize)<0)
     break;
		 switch(fmtsize.type)
     {
			case V4L2_FRMSIZE_TYPE_DISCRETE:
      printf("Width = %d Height = %d\n",\
             fmtsize.discrete.width,fmtsize.discrete.height);
						  break;
     }

   }//end for
  
  //设置摄像头工作参数
  memset(&fmt,0,sizeof(fmt));
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width = server_info.cam.width;
  fmt.fmt.pix.height = server_info.cam.height;
  //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
  //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
  if(ioctl(camfd,VIDIOC_S_FMT,&fmt)<0)
  {
    perr("camera set format")
    return -1;
  }  

  //申请1个缓冲区
  req.count=1;
  req.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
  req.memory=V4L2_MEMORY_MMAP;
 if(ioctl(camfd,VIDIOC_REQBUFS,&req)<0)
 {
  perr("camera request buff")
  return -1;
 }

 memset(&buf,0,sizeof(buf));
 for(i=0;i<1;i++)
 {
  buf.index = i;
  buf.type =V4L2_BUF_TYPE_VIDEO_CAPTURE;
  
  //获得缓冲区首地址放入img[]里
  if(ioctl(camfd,VIDIOC_QUERYBUF,&buf)==0)
  {
   printf("buffer %d offset=%d len=%d\n",i,buf.m.offset,buf.length);
  img[i]=(char*) mmap(NULL,buf.length,PROT_READ,MAP_SHARED,\
                      camfd,buf.m.offset);
   if(img[i]==MAP_FAILED)
   {
    perr("mmap failed");
    return -1;
   }
   //加入缓冲区采集队列
   if(ioctl(camfd,VIDIOC_QBUF,&buf)<0)
   {
    perr("qbuf")
    return -1;
   }
  }//end if

 }//end for
  
   cam_flag=1;
}
