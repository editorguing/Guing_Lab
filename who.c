#include <stdlib.h>
#include <time.h>
#include <lastlog.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>

#define LASTLOG "/var/log/lastlog"
#define RECORD_LEN (sizeof(struct lastlog))

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
    	struct lastlog record;
    	struct lastlog null_record;
    	char *name = NULL;
    	char *time = NULL;
    	struct passwd *pw = NULL;
    	int uid = 0;

	if(argc > 2)
	{
		fprintf(stderr,"Usage: mywho [Option]\n");
		exit(1);
	}
	if(argc == 1)
	{
		if(NULL == (fp = fopen(LASTLOG, "r")))
		{
        		perror("lastlog");
        		return 2;
    		}

    		memset(&null_record, 0, RECORD_LEN);
    		while(1 == fread((void *)&record, RECORD_LEN, (size_t) 1, fp))
		{
        		if(memcmp((void *)&record, (void *)&null_record, RECORD_LEN))
			{
            			time = ctime(&record.ll_time);
            			//time[24] = '\n';
            			if((pw = getpwuid((uid_t) uid)))
				{
                			name = pw->pw_name;
                			name[8] = '\0'; /* Truncate to 8 characters */
            			}
				else
				{
                			name = "";
            			}
            			printf("%-8s    %-8s %s\n", name, record.ll_line, time);
        		}
        		uid++;
    		}

    		if(ferror(fp))
		{
        		fprintf(stderr, "lastlog: read error\n");
        		return 1;
    		}
		else
		{
        		(void) fclose(fp); /* Don't care */
        		return 0;
    		}
	}
	else
	{
		if(!strcmp(argv[1],"--help"))
		{
			printf("Usage: who [OPTION]... [ FILE | ARG1 ARG2 ]\n");
			printf("Print information about users who are currently logged in.\n\n");
			printf("  -a, --all         same as -b -l -r\n");
			printf("  -b, --boot        time of last system boot\n");
			printf("  -l, --login       print system login processes\n");
			printf("  -q, --count       all login names and number of users logged on\n");
			printf("  -r, --runlevel    print current runlevel\n");
			printf("      --help     display this help and exit\n");
			printf("      --version  output version information and exit\n\n");
			printf("If FILE is not specified, use /var/run/utmp.  /var/log/wtmp as FILE is common.\n");
			printf("If ARG1 ARG2 given, -m presumed: 'am i' or 'mom likes' are usual.\n\n");

			printf("GNU coreutils online help: <http://www.gnu.org/software/coreutils/>\n");
			printf("Full documentation at: <http://www.gnu.org/software/coreutils/who>\n");
			printf("or available locally via: info '(coreutils) who invocation'\n");
			printf("/run/utmp.  /var/log/wtmp as FILE is common.\n\n");
		}
		else if(!strcmp(argv[1], "--version"))
		{
                        printf("who (Guing coreutils) 1.01\n");
                        printf("Copyright (C) 2016 EditorGuing.\n");
                        printf("Mokpo Universary Computer Engineering 133322 Oh Jae-Hyeok\n");
			exit(1);
		}
		else
		{

			fprintf(stderr,"Usage: who [Option]\n");
			exit(1);
		}
	}
	return 0;
}
