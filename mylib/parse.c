#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/**
 * @brief permet de parser une ligne de fichier config de forme variable = valeur . Ainsi v1 gardera la variable et v2 sa valeur
 * 
 * @param src 
 * @param v1 
 * @param v2 
 * @return int 
 */

int parse(const char *src, char *v1, char *v2)
{
  return sscanf(src,"%s = %s",v1,v2)==2 ;
}
