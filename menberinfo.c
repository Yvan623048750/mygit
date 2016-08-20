
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <dirent.h>	
#include "kernel_list.h"
	//1986990746 
char allName[20][30]={{"John"},{"Kim"},{"David"},{"James"},{"Michael"},{"Robert"},{"William"},{"Paul"},{"Peter"},{"George"},
			 {"Michelle"},{"Amy"},{"Mary"},{"Maria"},{"Lily"},{"Jessica"},{"Crystal"},{"Jennifer"},{"Rachel"},{"Elizabeth"}};	
char allTel[20][20]={{"4008869888"},{"8008468680"},{"8008468680"},{"4008006666"},{"4008838888"},
		    {"4008171888"},{"8008308899"},{"4008181188"},{"8008201111"},{"8009881200"},
			 {"8008108880"},{"8008205598"},{"4008879988"},{"8008809899"},{"8008201902"},
			 {"8008108168"},{"8008101100"},{"8008101210"},{"8008201912"},{"82253777"}};	
char allnumber[20][10]={{"1000"},{"1001"},{"1002"},{"1003"},{"1004"},
		    {"1005"},{"1006"},{"1007"},{"1008"},{"1009"},
			 {"1010"},{"1011"},{"1012"},{"1013"},{"1014"},
			 {"1015"},{"1016"},{"1017"},{"1018"},{"1019"}};
unsigned int crad[20];		 
			 
typedef struct User_Info{   //用户信息结构
	
	char Tel[20];
	char Name[30]; 
	char number[10];
	char image_way[60]; 
	char come_time[30];
	char leave_time[30];
	unsigned char Gender;
	unsigned char Age;
	unsigned short Id;
	unsigned char online;
	unsigned int Card_id;
	struct list_head list;	
 }UInfo,*pUInfo;
 
 char UsrName[30];
 

 
 int main (void)
 {
	 FILE *filp;
	 DIR *dir;
	 int ret;
	 UInfo test;
	 struct dirent *Dirent;
	 char dirway[50][50];	
	 char Buf[30];
	 char ReadUsrName[30][50];
	 int i=0,j=0,k=0;
	
	
	UInfo Users;
		//判断文件是否存在
		if (access("UserInfo",F_OK))
		{
			//创建用户目录
			ret = mkdir("UserInfo",0777);
			if(ret == -1)
			{
				perror(" Mkdir DIR");
			}	
		}
							
		while(1)
	{
		strcpy(Buf,(char *)allName[i]);
		strncpy(Users.Name,Buf,strlen(Buf)+1);  //将用户名写入用户信息结构
		
		strcpy(Buf,(char *)allTel[i]);
		strncpy(Users.Tel,Buf,strlen(Buf)+1);  //将电话写入用户信息结构

		strcpy(Buf,(char *)allnumber[i]);
		strncpy(Users.number,Buf,strlen(Buf)+1);  //

		crad[i]=1986990746+i;
		Users.Card_id=crad[i];
		
		
		if( i >=0 && i<=9)
		{
			Users.Gender=1;
		}
		else if( i >=10 && i<=19)
		{
			Users.Gender=0;
		}

		Users.Age=i+15;
		
		Users.Id=i+1;

		sprintf(Users.image_way,"./UserInfo/%s/%s.bmp",Users.Name,Users.Name);
		
		Users.online=1;
		
		sprintf(UsrName,"./UserInfo/%s",Users.Name,Users.Name);
		
		filp = fopen(UsrName,"w+");
		if(filp==NULL)
		{
			perror(" fopen");
			return 0;
		}
		
		printf("姓名：%s \n",Users.Name);
		printf("性别：%d \n",Users.Gender);
		printf("学号：%s \n",Users.number);
		printf("电话：%s \n",Users.Tel);
		printf("年龄：%d \n",Users.Age);
		printf("ID：%d \n",Users.Id); 
		printf("头像路径：%s \n",Users.image_way); 
		printf("离开时间：%s \n",Users.leave_time); 
		printf("上线时间：%s \n",Users.come_time); 
		
		printf("\n\n");
		fwrite(&Users,sizeof(UInfo),1,filp);
		
	
		fclose(filp);

		i++;
		if(i==20)
		{
			break;
		}
		//sleep(1);
	}
	
	i=0;
	dir = opendir("./UserInfo");
		if(dir == NULL)
		{
			perror(" Open DIR ");
		}
		while( Dirent =  readdir(dir))
		{
			if( !strcmp(Dirent->d_name,".") || !strcmp(Dirent->d_name,"..")  )
			{
				continue;
			}
			//printf(" d_name : %s \n",Dirent->d_name);
			stpcpy(dirway[i],Dirent->d_name);
			printf("  d_name : %s \n",(char *)dirway[i]);
			sprintf(ReadUsrName[i],"./UserInfo/%s",dirway[i]);
			printf("ReadUsrName[%d]=%s \n",i,ReadUsrName[i]);
			i++;

		}
		k=0;
		sleep(2);
	while(1)
	{
		printf("\n\n");
		printf("ReadUsrName[%d]=%s \n",k,ReadUsrName[k]);
		//pUInfo test2=(pUInfo)malloc(sizeof(UInfo));
		sleep(1);
		filp = fopen(ReadUsrName[k],"r+");
		if(filp==NULL)
		{
			perror(" fopen");
			return 0;
		}
		fseek(filp,0,0);
		fread(&test,sizeof(UInfo),1,filp);
	//	fseek(filp,0,0);
	//	fread(&test2,sizeof(UInfo),1,filp);
	/*	stpcpy(test2->Name,test.Name);
		test2->Gender=test.Gender;
		stpcpy(test2->number,test.number);
		stpcpy(test2->Tel,test.Tel);
		test2->Age=test.Age;
		test2->Id=test.Id;
		test2->online=test.online;
		stpcpy(test2->image_way,test.image_way);*/
		printf("read \n");
		printf("姓名：%s \n",test.Name);
		printf("性别：%d \n",test.Gender);
		printf("学号：%s \n",test.number);
		printf("电话：%s \n",test.Tel);
		printf("年龄：%d \n",test.Age);
		printf("ID：%d \n",test.Id);
		printf("Card_id ：%d \n",test.Card_id);
		printf("在线：%d \n",test.online);
		printf("头像路径：%s \n",test.image_way); 
		printf("离开时间：%s \n",test.leave_time); 
		printf("上线时间：%s \n",test.come_time); 
		/*printf("read \n");
		printf("姓名：%s \n",test2->Name);
		printf("性别：%d \n",test2->Gender);
		printf("学号：%s \n",test2->number);
		printf("电话：%s \n",test2->Tel);
		printf("年龄：%d \n",test2->Age);
		printf("ID：%d \n",test2->Id);
		printf("Card_id ：%d \n",test2->Card_id);
		printf("在线：%d \n",test2->online);
		printf("头像路径：%s \n",test2->image_way); 
		printf("离开时间：%s \n",test2->leave_time); 
		printf("上线时间：%s \n",test2->come_time); */
		printf("\n \n");
		fclose(filp);
		k++;
		if(k==20)
		{
			break;
		}
		//sleep(1);
	}	
	
	
	 return 0;
	 
 }
 