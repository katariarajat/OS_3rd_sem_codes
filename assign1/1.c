#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *fp=fopen("file1","r");
	char ch; 
	ch=getc(fp);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=getc(fp);
	}
	fclose(fp);
	
}
