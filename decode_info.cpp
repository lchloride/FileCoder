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
	char appendix[100]={'\0'};
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
		int dot_pos = -1, gang_pos=-1;
		int i=0;
		for (i=strlen(path)-1; i>=0; i--)
			if (path[i]=='\\'||path[i]=='/')
			{
				gang_pos = i;
				break;
			}
		for (i=gang_pos; i<strlen(path); i++)
			if (path[i] == '.')
			{
				dot_pos = i;
			}
			else
				if (dot_pos == -1)
					filename[i-gang_pos-1] = path[i];
				else
					appendix[i-dot_pos-1] = path[i];
		printf("filename:%s, appendix:%s\n", filename,appendix);
		if (strcmp(appendix, "bak")!=0 && strcmp(appendix, "info")!=0)
		{
			printf("File appendix must be \"bak\" or \"info\"\n");
			fclose(fin);
			_getch();
			return 0;
		}

		int filename_leng;
		rc = fread(&filename_leng,sizeof(int),1,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			_getch();
			fclose(fin);
			return 0;
		}		
		int ver;
		rc = fread(&ver,sizeof(int),1,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			_getch();
			fclose(fin);
			return 0;
		}
		
		int count_check; 
		fread(&count_check,sizeof(int), 1, fin ); 

		char ofilename[500]={'\0'};
		rc = fread(ofilename,sizeof(char),filename_leng,fin);
		if (rc==0)
		{
			printf("Read file failed!\n");
			fclose(fin);
			_getch();
			return 0;
		}
		printf("Decode info of file:%s\n", path);
		printf("Encoding program version:V%d\n", ver);
		printf("Origin file name: %s\n", ofilename);
		//printf("%d\n", count_check);
		if (count_check >= (1<<29))
			printf("Orgin file size: %lf GB\n", double(count_check)/(1<<29));
		else if (count_check >= (1<<19))
			printf("Orgin file size: %lf MB\n", double(count_check)/(1<<19));
		else if (count_check >= (1<<9))
			printf("Orgin file size: %lf KB\n", double(count_check)/(1<<9));
		else
			printf("Orgin file size: %lf bytes\n", count_check*2);
	}
	fclose(fin);
	_getch();
	return 0;
}