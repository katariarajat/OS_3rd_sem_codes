#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
int main(int argc,char* argv[])
{

	if(argc<4)
	{
		write(1,"ERROR : 3 ARGUMENT EXPECTED",27);
		return 0;
	}
	int flag1=1;
	// checking if directory exist 
	
	DIR *dir=opendir(argv[3]);
	write(1,"Directory is created : ",23);
	if(dir)
	{	
		write(1,"Yes\n",4);
		closedir(dir);
	}
	else 
	{
		write(1,"No\n",3);
		flag1=0;
	}
	
	// opening new file and old file in read mode
	int fp = open(argv[1],O_RDONLY | O_EXCL);
	int fptr = open(argv[2],O_RDONLY | O_EXCL);

	long long int n1 = lseek(fp,0,SEEK_END);
	long long int n2 = lseek(fptr,0,SEEK_END);
	char ch1,ch2;
	write(1,"Whether file contents are reversed in newfile: \n",48);
	 write(1,"Checking files...                        \n",42);
	int flag=1;	
	// newfiles and old files are reverse or not is checked by character by character,extrating newfile from beginning and old file from end untill all the characters are checked 

	

	if(n1!=n2)
		flag=0;
	else
	{
		char *c,*h;
		int n = lseek(fp, 0, SEEK_END);
		int block=n/500;
		int block_read=(block==0)?1:block;
	
		int left_block=n-block*500;
	
		long long int i = 0;
		c=(char*)malloc(block_read);
		h=(char*)malloc(block_read);
		char *msg;
		msg=(char*)malloc(block_read);	

		while(i<left_block)
		{

			lseek(fptr,i*sizeof(char),SEEK_SET);
			i++;
			lseek(fp,-i*sizeof(char),SEEK_END);
			
			read(fp,c,sizeof(char));

			read(fptr,h,sizeof(char));
			if(c!=h)
			{
				flag=0;
				break;
			}
		}
		i=0;
		while(i<500 && block && flag)
		{
			lseek(fptr,i*sizeof(char)*block+left_block,SEEK_SET);
			i++;
			lseek(fp,-i*sizeof(char)*block-left_block,SEEK_END);
			read(fp,c,sizeof(char)*block);
			read(fptr,h,sizeof(char)*block);

			for(int begin=0,end=block-1;begin<block,end>=0;begin++,end--)
			{
				if(h[begin]!=c[end])
				{
					flag=0;
					break;
				}
			}
		}
	}
	if(flag==0)
		write(1,"No\n",3);
	else 
		write(1,"Yes\n",4);
	struct stat st;
	if(stat(argv[1],&st)==0)
	{
		mode_t perm = st.st_mode;
		 write(1,"User has read permissions on newfile : ",39);

		if(perm & S_IRUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		write(1,"User has write permissions on newfile : ",40);
		if(perm & S_IWUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		 write(1,"User has execute permissions on newfile : ",42);
		if(perm & S_IXUSR)
		{
			 write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"Group has read permissions on newfile : ",40);
		if(perm & S_IRGRP)
		{
			 write(1,"Yes\n",4);
		}
		else{
			 write(1,"No\n",3);
		}
		write(1,"Group has write permissions on newfile : ",41);
		if(perm & S_IWGRP)
		{
			write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"group has execute permissions on newfile : ",42);
		if(perm & S_IXGRP)
                {
                        write(1,"Yes\n",4);
                }
                else
                {
                        write(1,"No\n",3);
                }
		write(1,"Other has read permissions on newfile : ",40);
		 if(perm & S_IROTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has write permissions on newfile : ",41);
		 if(perm & S_IWOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has execute permissions on newfile : ",42);
		 if(perm & S_IXOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }



	}
	if(stat(argv[2],&st)==0)
	{
		mode_t perm = st.st_mode;
		 write(1,"User has read permissions on oldfile : ",39);

		if(perm & S_IRUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		write(1,"User has write permissions on oldfile : ",40);
		if(perm & S_IWUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		 write(1,"User has execute permissions on oldfile : ",42);
		if(perm & S_IXUSR)
		{
			 write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"Group has read permissions on oldfile : ",40);
		if(perm & S_IRGRP)
		{
			 write(1,"Yes\n",4);
		}
		else{
			 write(1,"No\n",3);
		}
		write(1,"Group has write permissions on oldfile : ",41);
		if(perm & S_IWGRP)
		{
			write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"group has execute permissions on oldfile : ",42);
		if(perm & S_IXGRP)
                {
                        write(1,"Yes\n",4);
                }
                else
                {
                        write(1,"No\n",3);
                }
		write(1,"Other has read permissions on oldfile : ",40);
		 if(perm & S_IROTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has write permissions on oldfile : ",41);
		 if(perm & S_IWOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has execute permissions on oldfile : ",42);
		 if(perm & S_IXOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }
	}
	if(stat(argv[3],&st)==0 && flag1)
	{
		mode_t perm = st.st_mode;
		 write(1,"User has read permissions on directory : ",41);

		if(perm & S_IRUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		write(1,"User has write permissions on directory : ",42);
		if(perm & S_IWUSR)
		{
			write(1,"Yes\n",4);
		}
		else{
			write(1,"No\n",3);
		}
		 write(1,"User has execute permissions on directory : ",44);
		if(perm & S_IXUSR)
		{
			 write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"Group has read permissions on directory : ",42);
		if(perm & S_IRGRP)
		{
			 write(1,"Yes\n",4);
		}
		else{
			 write(1,"No\n",3);
		}
		write(1,"Group has write permissions on directory : ",43);
		if(perm & S_IWGRP)
		{
			write(1,"Yes\n",4);
		}
		else
		{
			write(1,"No\n",3);
		}
		write(1,"group has execute permissions on directory : ",44);
		if(perm & S_IXGRP)
                {
                        write(1,"Yes\n",4);
                }
                else
                {
                        write(1,"No\n",3);
                }
		write(1,"Other has read permissions on directory : ",42);
		 if(perm & S_IROTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has write permissions on directory : ",43);
		 if(perm & S_IWOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }


		write(1,"Other has execute permissions on directory : ",44);
		 if(perm & S_IXOTH)
                {
                        write(1,"Yes\n",4);
                }
                else   
                {
                        write(1,"No\n",3);
                }
	}
	return 0;
}
