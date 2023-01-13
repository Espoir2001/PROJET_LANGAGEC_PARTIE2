/**
 * @brief Bibliothèque contenant les fonctions load et search
 * 
 */

/**
 * 
 * 
 * @param fname 
 * @return struct TreeNode* 
 */

struct TreeNode *load(const char *fname);

/**
 *
 * 
 * @param root 
 * @param entry 
 */
void search(struct TreeNode *root, char *entry);

/**
 * 
 * 
 * @param src 
 * @param v1 
 * @param v2 
 * @return int 
 */
int parse(const char *src, char *v1, char *v2);