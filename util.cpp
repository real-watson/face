
#include "engine.h"
extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
}

int rename_config_file(char *tmp, char *file)
{
	char cmd[64] = ""; 
	int res = 0;
	res = strcmp(tmp,file);
	if (res == 0)
		return -1;
	sprintf(cmd,"mv %s %s",tmp,file);
	system(cmd);
	return 0;
}

int file_moving_pointer(char *tmpbuff, char *token, char *string)
{
	FILE *tmp = NULL;
	FILE *file = NULL;
	char buff[256] = "";
	char new_value[256] = "";
	int offset = 0;
	int res = 0;
	tmp = fopen(CONFIG_TMP,"w");
	file = fopen(CONFIG_PATH,"ab+");

	if (NULL == file || NULL == tmp)
		return -1;

	offset = strlen(tmpbuff) - strlen(token);//get the len of front string xxx=

	while(fgets(buff,256,file) != NULL)//set up new file (tmp)
	{
		if (strncmp(buff,tmpbuff,strlen(tmpbuff)) == 0)
			continue;
		else
		{
			fwrite(buff,strlen(buff),sizeof(char),tmp);
				
		}

	}
	strncpy(new_value,tmpbuff,offset);
	strcat(new_value,string);
	strcat(new_value,"\n");
	/*Use sprintf commonly, but it is short of cutting string*/
	//sprintf(new_value,"%s%s",tmpbuff,string);
	fwrite(new_value,strlen(new_value),sizeof(char),tmp);
	res = rename_config_file(CONFIG_TMP,CONFIG_PATH);
	if (-1 == res)
		return -1;
	fclose(file);
	fclose(tmp);
	return 0;
}

int util_token_back(char *buff, char *key, char *string, char *flag)
{
	char *token = NULL;
	int res = 0;
	unsigned int len = 0;
	char tmp[32] = "";
	if (strcmp(flag,"set") == 0)
	{
		strncpy(tmp,buff,strlen(buff));
	}
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
					printf("set\n");
					file_moving_pointer(tmp,token,string);
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
	char last[128] = "";
	int sflag = 0;

	file = fopen(CONFIG_PATH,"ab+");
	if (NULL == file)
		return -1;
	
	while(fgets(buff,256,file) != NULL)
	{
		if (strstr(buff,key) != NULL)
		{	
			sflag = 1;
			res = util_token_back(buff,key,string,flag);	
			if (res != 0)
			{
				res = -1;
				break;
			}
		}
		else
		{
			memset(buff,0,256);
			continue;
		}
	}

	if (!sflag)// If the new key-value does not exsit, it shuold be zero.
	{
		/*
		* Set new key-value like ADDR "Earth"
		* key=string
		*/
		sprintf(last,"%s=%s\n",key,string);
		res = fwrite(last,strlen(last),sizeof(char),file);
		if (res == 0)
		{
			res = -1;
		}
	}

	if (res == -1)
	{
		fclose(file);
		return res;
	}
	fclose(file);
	return 0;
}

int check_string(char *str)
{
	if (str == NULL)
		return 0;
	if (strstr(str,"=") != NULL || strstr(str," ") != NULL)//check the input
		return -1;
	return 0;	
}

int util_get_string(char *key, char *string)
{
	int res = 0;
	char flag[12] = "get";
	res = check_string(string);
	if (!res)
		return (util_common_string(key,string,flag));
	else
		return -1;
}

int util_set_string(char *key, char *string)
{
	int res = 0;
	char flag[12] = "set";
	res = check_string(string);
	if (!res)
		return (util_common_string(key,string,flag));
	else
		return -1;
}

int util_match_string(char *key, char *string)
{
	int res = 0;
	char flag[12] = "match";
	res = check_string(string);
	if (!res)
		return (util_common_string(key,string,flag));
	else
		return -1;
}
