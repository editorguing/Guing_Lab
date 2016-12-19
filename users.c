#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define STR_SIZE 1024

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char c;
	int i=0;
	char str[STR_SIZE];
	int num[STR_SIZE];
	int a=0, b=0;

	if(argc > 2)
	{
		fprintf(stderr,"Usage: users [Option]\n");
		exit(1);
	}

	if(argc == 1)
	{
		fp = fopen("/var/run/utmp", "r");
		c = getc(fp);
		while ( c != EOF)			//파일 끝이 아닐때까지
		{
			//putc(c,stdout);		//읽은 문자를 표준출력에 출력
			c = getc(fp);			//파일로부터 문자 읽기
			str[i] = c;
			if(str[i] == ':')
			{
				num[i] = i;
				if(a == 0)
					a = num[i];
				else if(a != 0 && b == 0)
					b = num[i];
				else if(a != 0 && b != 0)
				{
					a = 0;
					b = 0;
					a = num[i];
					str[a-1] = 32;
					printf("%c", str[a-1]);
				}
			}
			for(a;a<b;a++)
			{
				if((str[a] >= 65 && str[a] <= 90) || (str[a] >= 97 && str[a] <= 122) || str[a] == 32)
				{
					printf("%c", str[a]);
				}
			}
			i++;
		}
		printf("\n");
		fclose(fp);
		exit(2);
	}
	else
	{
		if(!strcmp(argv[1],"--help"))
		{
			printf("Usage: users [Options]... [FILE]\n");
			printf("Output who is currently logged in according to FILE.\n");
			printf("If FILE is not specified, use /var/run/utmp.  /var/log/wtmp as FILE is common.\n\n");
			printf("      --help     display this help and exit\n");
			printf("      --version  output version information and exit\n\n");
			printf("GNU coreutils online help: <http://www.gnu.org/software/coreutils/>\n");
			printf("Report users translation bugs to <http://translationproject.org/team/>\n");
			printf("Full documentation at: <http://www.gnu.org/software/coreutils/users>\n");
			printf("For available locally via: info '(coreutils) users invocation'\n");
			exit(1);
		}
		else if(!strcmp(argv[1],"--version"))
		{
			printf("users (Guing coreutils) 1.01\n");
			printf("Copyright (C) 2016 EditorGuing.\n");
			printf("Mokpo Universary Computer Engineering 133322 Oh Jae-Hyeok\n");
			exit(1);
		}
		else
		{
			fprintf(stderr,"Usage: %s [Option]\n", argv[0]);
			exit(1);
		}
	}
	return 0;
}
