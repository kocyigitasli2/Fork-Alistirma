// 171220028 �EYDA ASLI KO�Y���T
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void yaprak();
void ata(int,int);
void agacOlustur(int);

int main(int argc,char *argv[])
{
	int parametre = atoi(argv[1]);
	agacOlustur(parametre);

	return 0;
}



void yaprak()
{
	char file[20];
	sprintf(file,"%d.txt",getpid());//sprintf ile ekleme yap�yoruz
	FILE *fp=fopen(file,"w");
	srand(getpid());//time(NULL) olursa processler ayn� de�eri al�r
	fprintf(fp,"%d",(rand()%100));
	fclose(fp);
}


void ata(int pid1,int pid2)
{ 
	int eski,sol,sag;;
	wait(NULL);
	char file1[20];
        sprintf(file1,"%d.txt",pid1);
	char file2[20];
        sprintf(file2,"%d.txt",pid2);
	char file3[20];
        sprintf(file3,"%d.txt",getpid());

	FILE *fp1,*fp2,*fp3;
	fp1=fopen(file1,"r");
	fp2=fopen(file2,"r");
	fp3=fopen(file3,"r+");

	
	fscanf(fp1,"%d",&sol);
	fscanf(fp2,"%d",&sag);
	fscanf(fp3,"%d",&eski);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fp3=fopen(file3,"w");	
	fprintf(fp3,"%d",sol+sag+eski);
	fclose(fp3);



}

void agacOlustur(int h)
{

	if(h==0)
	{
		yaprak();
		return ;
	}

	int pid=fork();
	if(pid>0)
	{
		int pid2=fork();
		if(pid2>0) // Parent i�in i�lemler
		{
			yaprak();
			wait(NULL); //Child � bekle 
			printf("Parent: %d , c1:%d ,c2:%d\n",getpid(),pid,pid2);
			fflush(stdout); 
			ata(pid,pid2);
		}
		else if(pid2==0)
		{
			h--;
			agacOlustur(h);
		}
	}
	else if(pid==0) 
	{
		h--;
		agacOlustur(h);

 	}
}

