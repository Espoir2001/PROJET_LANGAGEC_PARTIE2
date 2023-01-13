#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib/mylib.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv)
{


struct config
{
    char rootdir[BUFSIZ];
    char datafile[BUFSIZ];
    char pidfile[BUFSIZ];
};

    struct  config conf;
      FILE *fp;
    char s[BUFSIZ];
    char buffer[BUFSIZ];
    char v1[BUFSIZ];
    char v2[BUFSIZ];

 fp = fopen("tree.conf", "r");
    if (fp == NULL)
        {
            perror("tree.conf");
            return 1;
        }


    while (fgets(s, BUFSIZ, fp) != NULL)
    {
        s[strlen(s)] = '\0'; // supprime le \n final
        char *ptr = strchr(s, '#');
       
        

        if (ptr != NULL)
        {
            *ptr = '\0'; // pour ne pas tenir compte des lignes de commentaire
        }
        else
        {
            parse(s,v1,v2);
          

            if(strcmp(v1,"rootdir")==0)
            {
                strcpy(conf.rootdir,v2);
            }
            else if(strcmp(v1,"datafile")==0)
            {
                strcpy(conf.datafile,v2);
            }
             else if(strcmp(v1,"pidfile")==0)
            {
                strcpy(conf.pidfile,v2);
            }
            continue;
        }
    }

    fclose(fp);

       printf("rootdir: %s\n", conf.rootdir);
       printf("datafile: %s\n", conf.datafile);
       printf("pidfile: %s\n", conf.pidfile);

    FILE* data_file = fopen(conf.datafile, "w");
    if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
    }


    int num_written = fprintf(data_file,argv[1]);
    if (num_written < 0) {
        printf("Error writing to file\n");
        fclose(data_file);
        return 1;
    }

    FILE* pid_file = fopen(conf.pidfile, "r");
    int pid;
   
    if (pid_file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    fscanf(pid_file, "%d", &pid);

    fclose(pid_file);

    printf("PID: %d\n", pid);

   pid =(pid_t) pid;
   kill(pid, SIGHUP);

   return 0;
}