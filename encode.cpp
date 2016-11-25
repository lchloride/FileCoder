#include <cstdio>
#include <cstring>
#include <conio.h>
#include <ctime>
using namespace std;
const int MAXLEN = 1;
const int VERSION = 1;
int main(int argc, char const *argv[])
{
	FILE *fin, *fout, *fout_name, *fin_num, *flog;
	char path[500]={'\0'};
	char filename[500]={'\0'};
	char appendix[100]={'\0'};
	char outfilename[50]={'\0'};
	char outfilename1[50]={'\0'};
	char inipath[500]={0};
	//char outappendix[100]={'\0'};
	// printf("%s\n", argv[0]);
	strcpy(inipath, argv[0]);
	if (argc == 1)
	{
		printf("Please input the path and filename:");
		scanf("%s", path);
		
	}
	else
	{
		strcpy(path, argv[1]);
	}
	time_t st = std::time(NULL), ed;
	printf("Processing %s\n", path);
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
		for (i=strlen(inipath); i>=0; i--)
			if (inipath[i]=='\\'||inipath[i]=='/')
			{
				break;
			}
			else
				inipath[i] = '\0';

				
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
		fin_num = fopen(strcat(inipath,"number.ini"), "r+");
		//printf("%s\n", inipath);
		if (fin_num == NULL)
		{
			printf("Missing number.ini\n");
			fclose(fin);
			_getch();
			return 0;
		}
		else
		{
			int last_num;
			fscanf(fin_num, "%d", &last_num);
			last_num++;
			sprintf(outfilename, "%d", last_num);
			printf("%d %s\n", last_num, outfilename);
			fseek(fin_num, 0, SEEK_SET);
			fprintf(fin_num, "%d\n", last_num);
		}
		fclose(fin_num);
		struct tm * timeinfo;
  		char fbuffer [80];
  		timeinfo = localtime (&st);

  		strftime (fbuffer,80,"_FILECODER%Y%m%d%H%M%S",timeinfo);
  		printf("%s\n", fbuffer);
		strcat(outfilename, fbuffer);
		char a1, a2;
		int count=0;
		fout = fopen(strcat(strcpy(outfilename1,outfilename), ".bak"), "wb");
		fout_name = fopen(strcat(outfilename, ".info"), "wb");

		for (i=strlen(inipath)-1; i>=0; i--)
			if (inipath[i] != '\\' && inipath[i] != '/')
				inipath[i] = '\0';
			else
				break;
		flog = fopen(strcat(inipath, "record.bak"), "ab");

		int filename_leng = strlen(path)-gang_pos-1;
		char* ful_filename = new char[filename_leng+1];
		for (int i=gang_pos+1; i<strlen(path); i++)
			ful_filename[i-gang_pos-1] = path[i];
		ful_filename[filename_leng] = '\0';
		//printf("%s\n", ful_filename);

		fwrite(&filename_leng,sizeof(int), 1, fout );
		fwrite(&VERSION,sizeof(int), 1, fout );
		fwrite(&count,sizeof(int), 1, fout ); 
		fwrite(ful_filename,sizeof(char), strlen(ful_filename), fout );

		fwrite(&filename_leng,sizeof(int), 1, fout_name );
		fwrite(&VERSION,sizeof(int), 1, fout_name );
		fwrite(&count,sizeof(int), 1, fout_name ); 
		fwrite(ful_filename,sizeof(char), strlen(ful_filename), fout_name );
		
		//fwrite(&count,sizeof(int), 1, flog );//大小
		int path_leng = strlen(path);//原文件名长度
		fwrite(&path_leng, sizeof(int), 1, flog);//原文件名
		for (i=0; i<path_leng; i++)
			path[i] -= ((i+1)%48);
		fwrite(path, sizeof(char), path_leng, flog);
		
		int outfilename_leng = strlen(outfilename1);//新文件名长度
		fwrite(&outfilename_leng, sizeof(int), 1, flog);//新文件名
		fwrite(outfilename1, sizeof(char), outfilename_leng, flog);		
		fwrite(&st,sizeof(time_t), 1, flog );//加入时间
 		fwrite(&VERSION,sizeof(int), 1, flog );//版本


		delete[] ful_filename;
		int rc1=1132,rc2=-96;
		bool set = true;
		/*fwrite( &rc1, sizeof( int ), 1, fout );
		fwrite( &rc2, sizeof( int ), 1, fout );*/
		char buffer[1025]={0};
		int l = 0;
		while( true )  
		{  
			rc1 = fread(&a1,sizeof(char),MAXLEN,fin);
			if (rc1==0)
			{set=true;break;}
			rc2 = fread(&a2,sizeof(char),MAXLEN,fin);
			//printf("%d %d\n", rc1, rc2);
			if (rc2==0)
			{set=false;break;}
			//l = strlen(buffer);
			buffer[l++] = a2;
			buffer[l++] = a1;
			if ((count+1) % 512==0)
			{fwrite(buffer,sizeof(char), 1024, fout );
			 memset(buffer, 0, 1025);
			 l=0;
			}
			if (count%(1<<19)==0)
				printf("Processing:%dMB Start!\n",count/(1<<19));
			count++;
			// if (count==1)
			// 	break;
		} 
		//printf("%d\n", set);
		printf("%d\n", l);
		for (int i=0; i<l; i++)
			printf("%x ", buffer[i]);
		if (l > 0) 
			fwrite(buffer,sizeof(char), l, fout );
		if (!set)
			fwrite(&a1,sizeof(char), rc1, fout ); 
		fseek(fout, 2L*sizeof(int), SEEK_SET);
		fwrite(&count,sizeof(int), 1, fout ); 
		fseek(fout_name, 2L*sizeof(int), SEEK_SET);
		fwrite(&count,sizeof(int), 1, fout_name );
		//fseek(flog, 0L, SEEK_SET);
		fwrite(&count,sizeof(int), 1, flog ); 
		printf("Encoding Finished!\n");
		fclose(fout);
		fclose(fout_name);
		fclose(flog);
	}
	ed = time(NULL);
	printf("Processing time:%lds\n",ed-st);
	printf("Press any key to exit.\n");
	_getch();
	fclose(fin);
	
	return 0;
}