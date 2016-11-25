#include <cstdio>
#include <cstring>
#include <conio.h>
using namespace std;
const int MAXLEN = 1;
const int VERSION = 1;
int main(int argc, char const *argv[])
{
	FILE *fin, *fout;
	char path[500]={'\0'};
	char filename[500]={'\0'};
	int rc;
	if (argc == 1)
	{
		printf("Please input the path and filename:");
		scanf("%s", path);
		
	}
	else
	{
		strcpy(path, argv[1]);
	}
	fin = fopen(path, "rb");
	if (fin == NULL)
	{
		printf("The file does not exist!\n");
	}
	else
	{
		int filename_leng;
		rc = fread(&filename_leng,sizeof(int),1,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			fclose(fin);
			return 0;
		}		
		int ver;
		rc = fread(&ver,sizeof(int),1,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			fclose(fin);
			return 0;
		}
		
		int count_check; 
		fread(&count_check,sizeof(int), 1, fin ); 

		char filename[500]={'\0'};
		rc = fread(filename,sizeof(char),filename_leng,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			fclose(fin);
			return 0;
		}
		printf("Processing:%s, target file:%s\n", path,filename);

		fout = fopen(filename, "wb");
		char a1, a2;
		int count=0;
		int rc1=1132,rc2=-96;
		bool set = true;
		/*fwrite( &rc1, sizeof( int ), 1, fout );
		fwrite( &rc2, sizeof( int ), 1, fout );*/
		while( true )  
		{  
			a1 = 0;
			a2 = 0;
			rc1 = fread(&a1,sizeof(char),MAXLEN,fin);
			if (rc1==0)
			{set=true;break;}
			rc2 = fread(&a2,sizeof(char),MAXLEN,fin);
			//printf("%d %d\n", rc1, rc2);
			if (rc2==0)
			{set=false;break;}
			fwrite(&a2,sizeof(char), rc2, fout );
			fwrite(&a1,sizeof(char), rc1, fout );  
			if (count%(1<<19)==0)
				printf("Processing:%dMB Start!\n",count/(1<<19));
			count++;
			// if (count==1)
			// 	break;
		} 
		//printf("%d\n", set);
		if (!set)
			fwrite(&a1,sizeof(char), rc1, fout );

		if (count_check == count)
			printf("Decode Successfully Finished!\n");
		else
			printf("There are something wrong with decoding file!\n");
		fclose(fout);
	}
	printf("Press any key to exit.\n");
	_getch();
	fclose(fin);
	return 0;
}