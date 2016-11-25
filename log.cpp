#include <cstdio>
#include <cstring>
#include <conio.h>
#include <ctime>
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
		strcpy(path, "record.bak");
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

		for (i=gang_pos>0?gang_pos:0; i<strlen(path); i++)
			if (path[i] == '.')
			{
				dot_pos = i;
			}
			else
				if (dot_pos == -1)
					filename[i-gang_pos-1] = path[i];
				else
					appendix[i-dot_pos-1] = path[i];
		//printf("path%s filename:%s, appendix:%s\n", path, filename,appendix);
		if (strstr(filename, "record")==NULL)
		{
			printf("Filename must be \"record\"\n");
			fclose(fin);
			_getch();
			return 0;			
		}
		if (strcmp(appendix, "bak")!=0)
		{
			printf("File appendix must be \"bak\"\n");
			fclose(fin);
			_getch();
			return 0;
		}
		printf("Log path:%s\n", path);
		int num=0;
		
		fout = fopen("log.txt", "w");

		while(true) 
		{
			num++;
			int filename_leng;
			rc = fread(&filename_leng,sizeof(int),1,fin);
			if (rc==0)
			{
				printf("\n1_Processing finished!\n");
				//_getch();
				//fclose(fin);
				//return 0;
				break;
			}	
			char ofilename[500]={'\0'};
			rc = fread(ofilename,sizeof(char),filename_leng,fin);
			if (rc==0)
			{
				printf("\n2_Processing finished!\n");
				fclose(fin);
				_getch();
				return 0;
			}
			for(int i=0; i<filename_leng; i++)
				ofilename[i] += ((i+1)%48);
			int newfilename_leng;
			rc = fread(&newfilename_leng,sizeof(int),1,fin);
			if (rc==0)
			{
				printf("\n3_Processing finished!\n");
				_getch();
				fclose(fin);
				return 0;
			}	

			//printf("%d\n", newfilename_leng);
			char nfilename[500]={'\0'};
			rc = fread(nfilename,sizeof(char),newfilename_leng,fin);
			if (rc==0)
			{
				printf("\n4_Processing finished!\n");
				fclose(fin);
				_getch();
				return 0;
			}

			time_t st;
			rc = fread(&st,sizeof(time_t),1,fin);
			if (rc==0)
			{
				printf("\n5_Processing finished!\n");
				_getch();
				fclose(fin);
				return 0;
			}
			//printf("%ld\n", st);
			int ver;
			rc = fread(&ver,sizeof(int),1,fin);
			if (rc==0)
			{
				printf("\n6_Processing finished!\n");
				_getch();
				fclose(fin);
				return 0;
			}
			int count_check; 
			rc = fread(&count_check,sizeof(int), 1, fin ); 
			if (rc==0)
			{
				printf("\n7_Processing finished!\n");
				_getch();
				fclose(fin);
				return 0;
			}	
			printf("-------record %d----------\n",num);
			printf("Encoding program version:V%d\n", ver);
			printf("Origin file name: %s\n", ofilename);
			printf("Encoded file name: %s\n", nfilename);
			printf("Encoding date: %s", ctime(&st));
			//printf("%d\n", count_check);
			if (count_check >= (1<<29))
				printf("Orgin file size: %lf GB\n", double(count_check)/(1<<29));
			else if (count_check >= (1<<19))
				printf("Orgin file size: %lf MB\n", double(count_check)/(1<<19));
			else if (count_check >= (1<<9))
				printf("Orgin file size: %lf KB\n", double(count_check)/(1<<9));
			else
				printf("Orgin file size: %d bytes\n", count_check*2);
			fprintf(fout, "-------record %d----------\n",num);
			fprintf(fout, "Encoding program version:V%d\n", ver);
			fprintf(fout, "Origin file name: %s\n", ofilename);
			fprintf(fout, "Encoded file name: %s\n", nfilename);
			fprintf(fout, "Encoding date: %s", ctime(&st));
			//printf("%d\n", count_check);
			if (count_check >= (1<<29))
				fprintf(fout, "Orgin file size: %lf GB\n", double(count_check)/(1<<29));
			else if (count_check >= (1<<19))
				fprintf(fout, "Orgin file size: %lf MB\n", double(count_check)/(1<<19));
			else if (count_check >= (1<<9))
				fprintf(fout, "Orgin file size: %lf KB\n", double(count_check)/(1<<9));
			else
				fprintf(fout, "Orgin file size: %d bytes\n", count_check*2);
		}	
	}
	fclose(fin);
	fclose(fout);
	printf("Remeber to delete the log file after reading!!!\nPress any key to continue.\n");
	_getch();
	return 0;
}