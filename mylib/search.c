#include <stdio.h>
#include <libgen.h>

#include "tree.h"
#include <string.h>

/**
 * @brief permet de chercher une entrée dans une structure de donnée et affiche les occurences trouvées.
*/


/**
 * @brief 
 * 
 * @param root structure de donnée dans laquelle on a chargé l'arborescence d'un répertoire dans laquelle on veut chercher
 * @param entry l'entrée dont on veut chercher les occurences
 */

void search(struct TreeNode *root, char *entry)
{

// verifier s'il s'agit d'un fichier ou d'un repertoire vide
	 if (root->contents == NULL )
	 { 
		if( strcmp( basename(root->fname),entry )==0 )
		{
          // printf(">>>%s/%s",dirname(root->fname),basename(root->fname));
		  printf(">>>%s",root->fname);
		   printf("\n");

		}
		
	}else 
	{ // Sinon, si c'est un repertoire non vide
		
        if( strcmp( basename(root->fname),entry  )==0 )
		{
           printf(">>>%s",root->fname);
		   printf("\n");
		}

		search(root->contents,entry);
		
	}
	
	if (root->next != NULL)
	{
		search(root->next,entry);	
	}



}