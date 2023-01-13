#include<strings.h>

/*! 
   \brief Structure de données pour stocker des informations sur un seul fichier

Pour les répertoires , contents est la liste chainée des fichiers dans le répertoire

Pour les fichiers , contents est NULL

next est le fichier suivant dans le répertoire (ou NULL) .
    \author Espoir HOUEDJI    
*/

/**
 *@param fname nom du fichier
 * @param contents liste chainée de fichier dans un répertoire
 * @param next fichier suivant
 */

struct TreeNode {
    char *fname;
    struct TreeNode *contents;   // Pour Repertoire
    struct TreeNode *next;
};

