#include <stdlib.h>
#include <time.h>
#include <lastlog.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>

#define LASTLOG "/var/log/wtmp"
#define RECORD_LEN (sizeof(struct lastlog))

int main(int argc, char *argv[])
{
	char *nope = "**Never logged in**";
	FILE *fp = NULL;
    	struct lastlog record;
    	struct lastlog null_record;
    	char *name = NULL;
    	char *time = NULL;
    	struct passwd *pw = NULL;
    	int uid = 0;

	if(argc > 2)
	{
		fprintf(stderr,"Usage: mylastlog [Option]\n");
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
		printf("Username\tPort\tFrom\t\t   Latest\n");
    		while(1 == fread((void *)&record, RECORD_LEN, (size_t) 1, fp))
		{
        		if(memcmp((void *)&record, (void *)&null_record, RECORD_LEN))
			{
            			time = ctime(&record.ll_time);
            			time[24] = '\n';
            			if((pw = getpwuid((uid_t) uid)))
				{
                			name = pw->pw_name;
                			name[8] = '\0';
            			}
				else
				{
                			name = "";
            			}
					printf("%-8s\t%-8s\t\t   %d\n", name, record.ll_line, record.ll_time);
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

		/*
		printf("Username\tPort\tFrom\t\tLastest\n");
		printf("root\t\t\t\t\t%s\n",nope);
		printf("daemon\t\t\t\t\t%s\n",nope);
		printf("bin\n");
		printf("sys\n");
		printf("sync\n");
		printf("games\n");
		printf("man\n");
		printf("lp\n");
		printf("mail\n");
		printf("news\n");
		printf("uucp\n");
		printf("proxy\n");
		printf("www-data\n");
		printf("backup\n");
		printf("list\n");
		printf("irc\n");
		printf("gnats\n");
		printf("nobody\n");
		printf("systemd-timesync\n");
		printf("systemd-network\n");
		printf("systemd-resolve\n");
		printf("systemd-bus-proxy\n");
		printf("syslog\n");
		printf("_apt\n");
		printf("messagebus\n");
		printf("uuidd\n");
		printf("lightdm\n");
		printf("whoopsie\n");
		printf("avahi-autoipd\n");
		printf("avahi\n");
		printf("dnsmasq\n");
		printf("colord\n");
		printf("speech-dispatcher\n");
		printf("hplip\n");
		printf("kernoops\n");
		printf("pulse\n");
		printf("rtkit\n");
		printf("saned\n");
		printf("usbmux\n");
		*/
	}
	else if(argc == 2)
	{
		if(!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h"))
		{
			printf("Usage: mylastlog [options]\n\n");
			printf("Options:\n");
			printf("  -b, --before DAYS             print only lastlog records older than DAYS\n");
			printf("  -h, --help                    display this help message and exit\n");
			printf("  -t, --time DAYS               print only lastlog records more recent than DAYS\n");
			printf("  -u, --user LOGIN              print lastlog record of the specified LOGIN\n\n");
			printf("      --version			display this version and exit\n");
			exit(1);
		}
		else if(!strcmp(argv[1], "--version"))
		{
                        printf("lastlog (Guing coreutils) 1.01\n");
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
