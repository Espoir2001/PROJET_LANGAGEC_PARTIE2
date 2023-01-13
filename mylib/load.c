#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <dirent.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief build_path permet de construire le chemin absolu
 * 
 */


/**
 * @brief 
 * 
 * @param root 
 * @param filename 
 * @return char* 
 */
char *build_path(const char *root, char *filename)
{
    char *path = malloc(strlen(root) + strlen(filename) + 2);
	strcpy(path, root);
	strcat(path, "/");
	strcat(path, filename);
	strcat(path, "\0");
	return path;
}


/**
 * @brief load qui charge l'arborescence d'un repertoire dans une structure de donnée
 * 
 */

/**
 * @brief 
 * 
 * @param fname répertoire dont on veut charger l'arborescence
 * @return struct TreeNode* 
 */


struct TreeNode *load(const char *fname)
{
     struct TreeNode *root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
     struct stat s;
	if (lstat(fname, &s) < 0){
		perror("lstat");
		exit(EXIT_FAILURE);
	}

    if (S_ISREG(s.st_mode) || S_ISLNK(s.st_mode)) {
		root->fname = (char *) fname;
		root->contents = NULL;
		root->next = NULL;
		
	}
    else if(S_ISDIR(s.st_mode)){
        DIR *dir;
		struct dirent *direntry;
		// Le noeud précédent (le premier appel n'a pas de précédent)
		struct TreeNode *prev = NULL;
		root->fname = (char *)fname;
		root->contents = NULL;
		root->next = NULL;
		dir = opendir(fname);

        if (dir == NULL){
			perror("Impossibilité d'ouvir le repertoire");
		}
		else
		{

while ( (direntry = readdir(dir)) != NULL){
			if ((*direntry).d_name[0]!='.'){
				// Entrée de répertoire courant
				struct TreeNode *curr = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				
				/* 
				Utilisation de la fonction build_path pour créer le chemin
				des sous-répertoires et des fichiers
				*/

				char *path = build_path(fname, (*direntry).d_name);
				curr = load(path);
				// Au premier appel , il n'y a pas de précédent donc j'en défini un.
				if (prev == NULL){
					prev = curr;
				} else {
				// Après le premier appel ,on déplace le pointeur pour creer une liste chainée	
					prev->next = curr;
					prev = prev->next;
				}
				// Dans le premier appel , contents de root est à NULL , donc on pointe la première entrée du repertoire
				if (root->contents == NULL){
					root->contents = prev;
				}
			}
		}
		closedir(dir);

		}
        
    }
return root;
}