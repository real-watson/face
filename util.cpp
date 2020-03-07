
#include "engine.h"
extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}

int util_token_back(char *buff, char *key, char *string)
{
	char *token = NULL;
	unsigned int len = 0;
	token = strtok(buff,"=");
	len = strlen(token);
	if (token != NULL)
	{
		if (0 == strncmp(token,key,len))
		{
			token = strtok(NULL,"=");
			if (token != NULL)
			{
				strcpy(string,token);
			}
		}
	}
	return 0;
}

int util_get_string(char *key,char *string)
{
	char buff[256] = "";
	FILE *file = NULL;
	file = fopen(CONFIG_PATH,"rw");
	if (NULL == file)
		return -1;
	
	while(fgets(buff,256,file) != NULL)
	{
		if (strstr(buff,key) != NULL)
		{	
			util_token_back(buff,key,string);	
		}
		else
		{
			continue;
		}

		memset(buff,0,256);
	}
	return 0;
}
