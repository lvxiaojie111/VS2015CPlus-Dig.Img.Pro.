#include "stdio.h"
#include "Windows.h"
//几个全局变量，存放读入图像的位图数据、宽、高、颜色表及每像素所占位数(比特) 
//此处定义全局变量主要为了后面的图像数据访问及图像存储作准备
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//图像类型

/***********************************************************************
* 函数名称：
* readBmp()
*
*函数参数：
*  char *bmpName -文件名字及路径
*
*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像文件名及其路径，读图像的位图数据、宽、高、颜色表及每像素
*      位数等数据进内存,存放在相应的全局变量中
***********************************************************************/
bool readBmp(char *bmpName)
{
	//二进制读方式打开指定的图像文件
    FILE *fp=fopen(bmpName,"rb");
	if(fp==0) return 0;
	
	
	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER),0);
	
	
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;  
	fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	
	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	
	//灰度图像有颜色表，且颜色表表项为256
	if(biBitCount==8){
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable=new RGBQUAD[256];
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf=new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
	
	//关闭文件
	fclose(fp);
	
	return 1;
}

/***********************************************************************
* 函数名称：
* saveBmp()
*
*函数参数：
*  char *bmpName -文件名字及路径
*  unsigned char *imgBuf  -待存盘的位图数据
*  int width   -像素为单位待存盘位图的宽
*  int  height  -像素为单位待存盘位图高
*  int biBitCount   -每像素所占位数
*  RGBQUAD *pColorTable  -颜色表指针

*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息，
*      将其写到指定文件中
***********************************************************************/
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, 
			 int biBitCount, RGBQUAD *pColorTable)
{
	//如果位图数据指针为0,则没有数据传入,函数返回
	if(!imgBuf)
		return 0;
	
	//颜色表大小,以字节为单位,灰度图像颜色表为1024字节,彩色图像颜色表大小为0
	int colorTablesize=0;
	if(biBitCount==8)
		colorTablesize=1024;

	//待存储图像数据每行字节数为4的倍数
	int lineByte=(width * biBitCount/8+3)/4*4;
	
	//以二进制写的方式打开文件
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;
	
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
	
	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	//bfOffBits是图像文件前三个部分所需空间之和
	fileHead.bfOffBits=54+colorTablesize;
	
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head; 
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
	
	//如果灰度图像,有颜色表,写入文件 
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
	
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
	
	//关闭文件
	fclose(fp);
	
	return 1;
}

/*
//文件存取函数调用的例子
void main()
{
	//读入指定BMP文件进内存
	char readPath[]="dog.BMP";
	readBmp(readPath);

	//输出图像的信息
	printf("width=%d,height=%d,biBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);

	//将图像数据存盘
	char writePath[]="dogcpy.BMP";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete []pBmpBuf;
	if(biBitCount==8)
		delete []pColorTable;
}
*/
/*
//文件数据进行修改的例子
void main()
{
	//读入指定BMP文件进内存
	char readPath[]="dog.BMP";
	readBmp(readPath);
	
	//输出图像的信息
	printf("width=%d,height=%d,biBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);
	
	
	//循环变量,图像的坐标
	int i,j;
	//每行字节数
	int lineByte=(bmpWidth*biBitCount/8+3)/4*4;

	//循环变量，针对彩色图像，遍历每像素的三个分量
	int k;
	
	//将图像左下角1/4部分置成黑色
	if(biBitCount==8){//对于灰度图像
		for(i=0;i<bmpHeight/2;i++){
			for(j=0;j<bmpWidth/2;j++){
				*(pBmpBuf+i*lineByte+j)=0;
			}
		}
	}
	else if(biBitCount==24){//彩色图像
		for(i=0;i<bmpHeight/2;i++){
			for(j=0;j<bmpWidth/2;j++){
				for(k=0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf+i*lineByte+j*3+k)=0;
			}
		}
	}
	
    //将图像数据存盘
	char writePath[]="dogcpy.BMP";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
		  
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete []pBmpBuf;
	if(biBitCount==8)
		delete []pColorTable;
}
 */

//调色板与灰度图像的关系
void main()
{
	//读入指定BMP文件进内存
	char readPath[]="dog.BMP";
	readBmp(readPath);

	//输出图像的信息
	printf("width=%d,height=%d,biBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);

	//改变灰度图像的颜色表蓝色分量的值,察看前后变化
	if(biBitCount==8){
		for(int i=0; i<256;i++){
			pColorTable[i].rgbBlue = 255-pColorTable[i].rgbBlue;
		}
	}


	//将图像数据存盘
	char writePath[]="dogcpy.BMP";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete []pBmpBuf;
	if(biBitCount==8)
		delete []pColorTable;
}

 