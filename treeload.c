#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib/mylib.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

// #define L 50

/*!
   \brief Programme treetest, on charge une arborescence  et on cherche un fichier dans l'arborescence.

   \author Espoir HOUEDJI
*/

void catcher(int signum)
{
    puts("signal recu \n");
    
}

int main(int argc, char **argv)
{
struct config
{
    char rootdir[BUFSIZ];
    char datafile[BUFSIZ];
    char pidfile[BUFSIZ];
};

    struct  config conf;
    struct sigaction sigact;

    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_handler = catcher;
    sigaction(SIGHUP, &sigact, NULL);

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


   struct TreeNode *root = load((const char *) conf.rootdir );

   

       FILE* f_pid = fopen(conf.pidfile, "w");

        if( f_pid== NULL) {
            printf("Error opening file\n");
            return 1;
            }
            pid_t pid = getpid();
            char pid_str[16];  
            sprintf(pid_str, "%d", pid); 

            int written = fprintf(f_pid,pid_str);
            if (written < 0) {
                printf("Error writing to file\n");
                fclose(f_pid);
                return 1;
            }

            printf("%s : \n",pid_str);

        fclose(f_pid);    

pause();
   FILE* data_file = fopen(conf.datafile, "r");
   
     while (fgets(buffer, BUFSIZ, data_file) != NULL)
    {
             buffer[strlen(buffer)] = '\0'; // supprime le \n final
    }
    
    char* newline = strchr(buffer, '\n');
    if (newline) {
        *newline = '\0';
    }

   search(root, buffer);


   return 0;
}