/*
 * sType.c
 *
 *  Created on: 1 oct 2022
 *      Author: juanm
 */

#include "sType.h"

#define EMPTY 1
#define OCCUPIED 0
#define LEN_DESCRIPTION

// static functions

static int newIdGenerator(void);

// static developing

static int newIdGenerator(void)
{
	static int cont=1000;
	return cont++;
}

int type_initArray(Type pArray[], int len)
{
	int ret=-1;

		if(pArray!=NULL && len>0)
		{
			for(int i=0;i<len;i++)
			{
				pArray[i].isEmpty = EMPTY;
			}
		}

	return ret;
}

int type_findEmptyArrayPosition(Type pArray[], int len)
{
	int index=-1;
		if(pArray!=NULL && len>0)
		{
			for(int i=0;i<len;i++)
			{
				if(pArray[i].isEmpty==EMPTY)
				{
					index = i;
					break;
				}
			}
		}
	return index;
}


int type_findIdByPos(Type pArray[], int len, int pos)
{
	int id;
	int auxIndex;

	if(pArray!=NULL && len>0)
	{
		auxIndex = pos-1; // como le hacemos elegir al usuario del 1 al 4, restando 1, tenemos la posicion en array
		id = pArray[auxIndex].idType;
	}

	return id;
}

int type_findPosById(Type pArray[], int len, int id)
{
	int auxPos;

	if(pArray!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].idType == id)
			{
				auxPos = i;
				break;
			}
		}
	}

	return auxPos;
}

void type_forceLoad(Type pArray[], int len, char description[])
{
	int indexFree;

	indexFree = type_findEmptyArrayPosition(pArray, len);
	pArray[indexFree].idType=newIdGenerator();
	strncpy(pArray[indexFree].description,description,sizeof(pArray[indexFree].description)); // con el sizeof tomamos el tamanio del lugar a donde lo guardamos
	pArray[indexFree].isEmpty=OCCUPIED;
}

void type_getDescriptionById(Type pArray[], int len, int id, char description[])
{
	int auxPos;
	int auxSize;

	if(pArray!=NULL && len>0 && id >999)
	{
		auxPos = type_findPosById(pArray, len, id); // buscamos la posicion por el id

		auxSize = sizeof(pArray[auxPos].description);

		strncpy(description,pArray[auxPos].description,auxSize);
	}

}

int type_printType(Type pArray[])
{
	int ret=-1;
		if(pArray!=NULL)
		{
			printf("id: %d\n"
						"Descripcion: %s\n\n", pArray->idType, pArray->description);
		}
	return ret;
}

int type_printTypes(Type pArray[], int len)
{
	int ret=-1;
		if(pArray!=NULL && len>0)
		{
			for(int i=0;i<len;i++)
			{
				if(pArray[i].isEmpty==OCCUPIED)
				{
					type_printType(&pArray[i]);
				}
			}
		}
	return ret;
}

