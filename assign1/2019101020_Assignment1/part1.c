#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	// checking if directory exists ,
	// if not then create it with mkdir
	struct stat stats;
	stat("ASSIGNMENT", &stats);
	if ((S_ISDIR(stats.st_mode)) == 0)
	{

		int dir = mkdir("ASSIGNMENT", 0700);
		//dir check
		if (dir == -1)
		{
			perror("mkdir");
			return 0;
		}
	}

	char *fullpath = malloc(10 + strlen(argv[1]));
	if (fullpath == NULL)
	{
		perror("memory not allocated");
		return 0;
	}

	// creating relative path for new file to be created in
	// fullpath char array using sprintf()

	char *g;
	g=(char*)malloc(sizeof(char)*500);
	int begin=0;
	for(int i=0;i<strlen(argv[1]);i++)
	{
		if(argv[1][i]=='/')
		{
			begin=0;
			continue;
		}
		g[begin++]=argv[1][i];
	}
	g[begin]='\0';
	// printf("%s\n",g);
	// return 0;
	sprintf(fullpath, "ASSIGNMENT/%s", g);

	int fp = open(argv[1], O_RDONLY | O_EXCL);
	//returning error if the file given does not opens
	if (fp == -1)
	{
		perror("ERROR OPENING GIVE FILE");
		return 0;
	}
	
	// checking if the file already exist in ASSIGNMENT folder and changing its method of opening from O_CREAT
	// if file doesnot exist 
	struct stat st;
	stat(fullpath, &st);
	int fptr;
	if (S_ISREG(st.st_mode))
	{
		fptr = open(fullpath, O_EXCL | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	else
	{
		fptr = open(fullpath, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
		// reporting error if file does not created
		if (fptr == -1)
		{
			perror("ERROR CREATING NEW FILE IN ASSIGNMENT");
			return 0;
		}
	}

	
	// using lseek to find number of characters
	int n = lseek(fp, 0, SEEK_END);
	int block=n/500;
	int block_read=(block==0)?1:block;
	
	int left_block=n-block*500;
	
	long long int i = 0;
	char msg[100];
	char *c,*h;
	c=(char*)malloc(block_read);
	h=(char*)malloc(block_read);
	//printf("%d %d",left_block,n);
	while(i<left_block)
	{
	//	system("clear");
		i++;
		lseek(fp,-i*sizeof(char),SEEK_END);
		read(fp,c,sizeof(char));
//		printf("%s",c);
		write(fptr,c,sizeof(char));
		
		float per=((float)i/n)*100;
		sprintf(msg,"%0.2f%%\r",per);
		write(1,msg,8);
	}
	i=0;
	while(i<500 && block)
	{

		i++;

		lseek(fp,-i*sizeof(char)*block-left_block,SEEK_END);
		read(fp,c,sizeof(char)*block);

		for(int begin=0,end=block-1;begin<block,end>=0;begin++,end--)
		{
			h[begin]=c[end];
		}
		write(fptr,h,sizeof(char)*block);

		float per=((float)(i*block+left_block)/n)*100;
		sprintf(msg,"%0.2f%%\r",per);
		write(1,msg,8);

	}

	
	write(1, "COMPLETED\n", 10);
	// closing opened file
	close(fp);
	close(fptr);
	return 0;
}
