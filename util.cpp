
#include "engine.h"
extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}

int util_token_back(char *buff, char *key, char *string, char *flag)
{
	char *token = NULL;
	int res = 0;
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
				if (strcmp(flag,"get") == 0)
				{
					//get string
					strcpy(string,token);
				}
				else if (strcmp(flag,"match") == 0)
				{
					//match string
					return (strncmp(token,string,strlen(string)));
				}
				else if (strcmp(flag,"set") == 0)
				{
					//set string
				}
				else
					return -1;
			}
		}
	}
	return 0;
}

int util_common_string(char *key, char *string, char *flag)
{
	char buff[256] = "";
	FILE *file = NULL;
	int res = 0;

	file = fopen(CONFIG_PATH,"rw");
	if (NULL == file)
		return -1;
	
	while(fgets(buff,256,file) != NULL)
	{
		if (strstr(buff,key) != NULL)
		{	
			res = util_token_back(buff,key,string,flag);	
			if (res != 0)
				return -1;
		}
		else
			continue;
		memset(buff,0,256);
	}
	return 0;
}

int util_get_string(char *key, char *string)
{
	char flag[12] = "get";
	return (util_common_string(key,string,flag));
}

int util_set_string(char *key, char *string)
{
	char flag[12] = "set";
	return 0;
}

int util_match_string(char *key, char *string)
{
	char flag[12] = "match";
	return (util_common_string(key,string,flag));
}
