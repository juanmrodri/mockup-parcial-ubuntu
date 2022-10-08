/*
 * sResource.c
 *
 *  Created on: 1 oct 2022
 *      Author: juanm
 */

#include "sResource.h"
#include "utn_input.h"


#define EMPTY 1
#define OCCUPIED 0

// static functions

static int newIdGenerator(void);

// static developing

static int newIdGenerator(void)
{
	static int cont=1;
	return cont++;
}

int resource_initArray(Resource pArray[], int len)
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

int resource_findEmptyArrayPosition(Resource pArray[], int len)
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

int resource_findById(Resource pArray[], int len, int id)
{
	int ret=-1;

	if(pArray!=NULL && len>0 && id>0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].idResource==id)
			{
				ret=i;
				break;
			}
		}
	}
	return ret;
}

int resource_isResourceAdded(Resource pArray[], int len)
{
	int ret=-1;
	if(pArray!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==OCCUPIED)
			{
				// significa que hay un recurso dado de alta
				ret=0;
				break;
			}
		}
	}

	return ret;
}

int resource_load(Resource pArrayRes[], int lenRes, int TypeId)
{
	int ret=-1;
	char auxDescription[21];
	float auxPricePerHour;
	int indexFree;

	if(pArrayRes!=NULL && lenRes>0)
	{
		indexFree = resource_findEmptyArrayPosition(pArrayRes, lenRes);

		if(indexFree>-1 && pArrayRes[indexFree].isEmpty==EMPTY && TypeId>999)
		{
			if(utn_getText(auxDescription, 21, "\nPor favor ingrese la descripcion del recurso: ", "Error al ingresar la descripcion\n", 2)==0)
			{
				if(utn_getFloat(&auxPricePerHour, "\nPor favor ingrese el precio por hora ($100 - $1500000): ", "Error al ingresar el precio\n", 100, 1500000, 2)==0)
				{
							resource_add(pArrayRes, lenRes, auxDescription, auxPricePerHour, TypeId);
				}
				else
				{
					ret=-1;
					printf("Se produjo un error al ingresar el precio por hora!\n");
				}
			}
			else
			{
				ret=-1;
				printf("Se produjo un error al ingresar la descripcion!\n");
			}
		}
		else
		{
			ret=-1;
			printf("Se produjo un error al intentar cargar!\n");
		}
	}
	else
	{
		ret=-1;
		printf("Error al realizar la carga!\n");
	}

	return ret;
}

int resource_add(Resource pArray[], int len, char description[], float price, int idType)
{
	int ret=-1;
	int indexFree; // aca se guardara el primer index libre

	if(pArray!=NULL && len>0 && description!=NULL && price>0) // typeId>0
	{
		indexFree = resource_findEmptyArrayPosition(pArray, len);
		pArray[indexFree].idResource = newIdGenerator();
		strncpy(pArray[indexFree].description,description,sizeof(pArray[indexFree].description));
		pArray[indexFree].pricePerHour=price;
		pArray[indexFree].typeId=idType;
		pArray[indexFree].isEmpty=OCCUPIED; // importantisimo cambiar el estado
	}

	return ret;
}

int resource_modify(Resource pArray[], int len, int pos, int option)
{
	int ret=-1;
	int auxResponse;
	float auxPricePerHour;
	char auxDescription[21];

	if(pArray!=NULL && len>0 && option>0)
	{
		switch(option)
		{
			// precio por hora
			case 1:
				printf("\nEsta por modificar el precio: $%.2f\n",pArray[pos].pricePerHour);
				if(utn_getInt(&auxResponse, "\nDesea continuar? (1 si- 2 no): ", "\nPor favor elija una opcion correcta", 1, 2, 2)==0)
				{
					if(auxResponse==1)
					{
						// se modifica
						if(utn_getFloat(&auxPricePerHour, "\nPor favor ingrese el nuevo precio por hora ($100 - $1500000): ", "Error al ingresar el precio\n", 100, 1500000, 2)==0)
						{
							ret=0;
							pArray[pos].pricePerHour=auxPricePerHour;
							break;
						}
						else
						{
							// no se modifica
							ret=-1;
							printf("\nError al seleccionar\n\n");
						}
					}
					else
					{
						if(auxResponse==2)
						{
							// no se modifica
							ret=-1;
							printf("\nNo se modificara el precio!\n\n");
							break;
						}
					}
				}
				// no se modifica
				ret=-1;
				printf("\nError al seleccionar\n\n");
				break;
			// descripcion
			case 2:
				printf("\nEsta por modificar la descripcion: %s\n",pArray[pos].description);
				if(utn_getInt(&auxResponse, "\nDesea continuar? (1 si- 2 no): ", "\nPor favor elija una opcion correcta", 1, 2, 2)==0)
				{
					// se modifica
					if(auxResponse==1)
					{
						if(utn_getText(auxDescription, 21, "\nPor favor ingrese la nueva descripcion del recurso: ", "Error al ingresar la descripcion\n", 2)==0)
						{
							ret=0;
							strncpy(pArray[pos].description,auxDescription,sizeof(pArray[pos].description));
							break;
						}
						else
						{
							// no se modifica
							ret=-1;
							printf("\nError al ingresar descripcion\n\n");
						}
					}
					else
					{
						if(auxResponse==2)
						{
							// no se modifica
							ret=-1;
							printf("\nNo se modificara la descripcion!\n\n");
							break;
						}
					}
				}
				else
				{
					// no se modifica
					ret=-1;
					printf("\nError al seleccionar\n\n");
				}
				break;
		}
	}
	return ret;
}

int resource_remove(Resource pArray[], int len, int id)
{
	int ret=-1;
	int auxResponse;

	if(pArray!=NULL && len>0 && id>0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].idResource==id && pArray[i].isEmpty == OCCUPIED)
			{
				//es el id seleccionado
				printf("\nEsta por dar de baja: \n\n");
				resource_printResource(&pArray[i]);
				if(utn_getInt(&auxResponse, "\ndesea continuar? (1 si- 2 no): ", "\nPor favor elija una opcion correcta", 1, 2, 2)==0)
				{
					if(auxResponse==1)
					{
						ret=0;
						pArray[i].isEmpty=EMPTY;
						break;
					}
					else
					{
						if(auxResponse==2)
						{
							ret=-1;
							printf("\nNo se realizara la baja\n\n");
							break;
						}
					}
				}
				else
				{
					ret=-1;
					printf("\nError al elegir opcion\n\n");
				}
			}
			ret=-1;
			printf("\nError en el id\n\n");
		}
	}
	return ret;
}

int resource_printResource(Resource pArray[])
{
	int ret=-1;
	if(pArray!=NULL)
	{
		printf("\nid: %d\n"
					"Descripcion:%s\n"
					"Precio por hora: $%.2f\n"
					"IdType: %d\n\n", pArray->idResource,pArray->description,pArray->pricePerHour,pArray->typeId);
	}
	return ret;
}

int resource_printResources(Resource pArray[], int len)
{
	int ret=-1;
	if(pArray!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==OCCUPIED)
			{
				resource_printResource(&pArray[i]);
			}
		}
	}
	return ret;
}


