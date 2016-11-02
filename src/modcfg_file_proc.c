#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_file_proc.h"

int modcfg_create_str_tree(struct STR_TREE** strTreeRef, char* filePath)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	char tmpRead, preChar;

	int strBufLen = 1;
	char* strBuf = NULL;

	void* allocTmp = NULL;
	struct STR_TREE* strTree = NULL;
	struct STR_TREE* strTreeRoot = NULL;
	struct STR_TREE* strTreeParent = NULL;
	FILE* fileRead = NULL;

	// Open file
	fileRead = fopen(filePath, "r");
	if(fileRead == NULL)
	{
		retValue = MODCFG_FILE_FAILED;
		goto RET;
	}
	else
	{
		fseek(fileRead, 0, SEEK_END);
		rewind(fileRead);
	}

	// Create root string tree
	strTree = (struct STR_TREE*)malloc(sizeof(struct STR_TREE));
	if(strTree == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		// Clear memory
		strTree->strCount = 0;
		strTree->strList = NULL;
		strTree->childCount = 0;
		strTree->child = NULL;
		strTree->header = NULL;
		
		// Assign root address
		strTreeRoot = strTree;
	}

	// Read to significant character
	while(modcfg_get_char(fileRead, READ_SIG) < 0);
	fseek(fileRead, -1, SEEK_CUR);

	// Reading file to string tree
	while(!feof(fileRead))
	{
		tmpRead = modcfg_get_char(fileRead, READ_SIG);
		switch(tmpRead)
		{
		case '*':
			if(preChar == '/')
			{
				tmpRead = 0;
				preChar = 0;
				while(preChar != '*' && tmpRead != '/')
				{
					preChar = tmpRead;
					tmpRead = modcfg_get_char(fileRead, READ_SIG);
				}

				preChar = 0;
				tmpRead = 0;
			}
			else
			{
				// Append character to string buffer
//				strBufLen++;
//				allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
//				if(allocTmp == NULL)
//				{
//					retValue = MODCFG_MEM_FAILED;
//					goto ERR;
//				}
//				else
//				{
//					strBuf = (char*)allocTmp;
//					allocTmp = NULL;
//
//					strBuf[strBufLen - 2] = tmpRead;
//					strBuf[strBufLen - 1] = '\0';
//				}
				iResult = modcfg_str_append(&strBuf, &strBufLen, tmpRead);
				if(iResult != MODCFG_NO_ERROR)
				{
					retValue = iResult;
					goto ERR;
				}
			}
			break;

		case '/':
			if(preChar == '/')
			{
				// Remove previous '/' in buffer
				strBuf[strBufLen - 2] = '\0';
				strBufLen--;
				
				// Read to LF
				while(modcfg_get_char(fileRead, READ_ALL) != LF);

				preChar = 0;
				tmpRead = 0;
			}
			else
			{
				// Append character to string buffer
//				strBufLen++;
//				allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
//				if(allocTmp == NULL)
//				{
//					retValue = MODCFG_MEM_FAILED;
//					goto ERR;
//				}
//				else
//				{
//					strBuf = (char*)allocTmp;
//					allocTmp = NULL;
//
//					strBuf[strBufLen - 2] = tmpRead;
//					strBuf[strBufLen - 1] = '\0';
//				}
				iResult = modcfg_str_append(&strBuf, &strBufLen, tmpRead);
				if(iResult != MODCFG_NO_ERROR)
				{
					retValue = iResult;
					goto ERR;
				}

			}
			break;

		case '{':
			// Create a child tree
			strTree->childCount++;
			allocTmp = realloc(strTree->child, sizeof(struct STR_TREE) * strTree->childCount);
			if(allocTmp == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto ERR;
			}
			else
			{
				strTree->child = (struct STR_TREE*)allocTmp;
				allocTmp = NULL;

				strTree->child[strTree->childCount - 1].strCount = 0;
				strTree->child[strTree->childCount - 1].strList = NULL;
				strTree->child[strTree->childCount - 1].childCount = 0;
				strTree->child[strTree->childCount - 1].child = NULL;
				strTree->child[strTree->childCount - 1].header = NULL;
			}

			// Enter child tree
			strTreeParent = strTree;
			strTree = &(strTree->child[strTree->childCount - 1]);

			// Assign tree header
			strTree->header = strBuf;
			strBuf = NULL;
			strBufLen = 1;

			break;

		case '}':
			// Return to parent tree
			strTree = strTreeParent;
			
			break;

		case ';':
			// Append string to tree
			strTree->strCount++;
			allocTmp = realloc(strTree->strList, sizeof(char*) * strTree->strCount);
			if(allocTmp == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto ERR;
			}
			else
			{
				strTree->strList = (char**)allocTmp;
				allocTmp = NULL;
				
				strTree->strList[strTree->strCount - 1] = strBuf;
				strBuf = NULL;
				strBufLen = 1;
			}
			break;

		default:
			if(tmpRead > 0)
			{
				// Append character to string buffer
//				strBufLen++;
//				allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
//				if(allocTmp == NULL)
//				{
//					retValue = MODCFG_MEM_FAILED;
//					goto ERR;
//				}
//				else
//				{
//					strBuf = (char*)allocTmp;
//					allocTmp = NULL;
//
//					strBuf[strBufLen - 2] = tmpRead;
//					strBuf[strBufLen - 1] = '\0';
//				}
				iResult = modcfg_str_append(&strBuf, &strBufLen, tmpRead);
				if(iResult != MODCFG_NO_ERROR)
				{
					retValue = iResult;
					goto ERR;
				}

			}
			break;
		}
		preChar = tmpRead;	
	}

	// Checking
	if(strTree != strTreeRoot)
	{
		retValue = MODCFG_SYNTAX_ERROR;
		strTree = strTreeRoot;
		goto ERR;
	}

	// Assign string tree
	*strTreeRef = strTree;

	goto RET;

ERR:
	// Delete string tree
	modcfg_delete_str_tree(strTree);

RET:
	if(allocTmp != NULL)
		free(allocTmp);
	
	if(fileRead != NULL)
		fclose(fileRead);

	return retValue;
}

char modcfg_get_char(FILE* fileRead, int readAction)
{	
	int iResult;
	int readCount;
	char tmpRead;
	
	// Read a character
	readCount = 1;
	iResult = fread((void*)&tmpRead, sizeof(char), readCount, fileRead);
	if(iResult != readCount)
		goto ERR;

	if(readAction == READ_ALL)
		goto RET;

	// Determint if character is signaficant
	if(tmpRead >= ASCII_MIN_SIG && tmpRead <= ASCII_MAX_SIG)
		goto RET;

ERR:
	return -1;

RET:
	return tmpRead;
}

void modcfg_delete_str_tree_recursive(struct STR_TREE* strTree)
{
	int i;

	// Free header
	if(strTree->header != NULL)
		free(strTree->header);

	// Free string
	for(i = 0; i < strTree->strCount; i++)
	{
		if(strTree->strList[i] != NULL)
			free(strTree->strList[i]);
	}
	if(strTree->strList != NULL)
		free(strTree->strList);

	// Free child
	for(i = 0; i < strTree->childCount; i++)
	{
		modcfg_delete_str_tree_recursive(&(strTree->child[i]));
	}
	if(strTree->child != NULL)
		free(strTree->child);
}

void modcfg_delete_str_tree(struct STR_TREE* strTree)
{
	// Delete child tree
	modcfg_delete_str_tree_recursive(strTree);
	
	// Free self
	if(strTree != NULL)
		free(strTree);
}

void print_str_tree(struct STR_TREE* strTree)
{
	int i;

	// Print header
	printf("Header: %s\n", strTree->header);

	// Print string
	for(i = 0; i < strTree->strCount; i++)
	{
		printf("String %d: %s\n", i, strTree->strList[i]);
	}

	// Print child tree
	printf("\n");
	for(i = 0; i < strTree->childCount; i++)
	{
		print_str_tree(&(strTree->child[i]));
	}
}

