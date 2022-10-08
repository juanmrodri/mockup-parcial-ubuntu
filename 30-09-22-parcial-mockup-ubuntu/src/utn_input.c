/*
 * utn_input.c
 *
 *  Created on: 21 sept 2022
 *      Author: juanm
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "utn_input.h"


// static func. firma

static int getInt(int* pResultado);

static int getFloat(float* pResultado);

static int isNumeric(char* pResultado);

static int isFloat(char* pResultado);

static int myGets(char* cadena, int longitud);

// stactic func. desarrollo

/**
* \brief se encarga de llamar a myGets, en caso satisfactorio, pasa por referencia la conversion a entero del resultado
* \param pResultado guardara en la dir de memoria el resultado convertido a entero
* \return ret = [0] - error = [1]
*/
static int getInt(int* pResultado)
{
	int ret=-1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && isNumeric(buffer))
	{
		ret=0;
		*pResultado = atoi(buffer);
	}
	return ret;
}

/**
* \brief se encarga de llamar a myGets, en caso satisfactorio, pasa por referencia la conversion a flotante del resultado
* \param pResultado guardara en la dir de memoria el resultado convertido a flotante
* \return ret = [0] - error = [1]
*/
static int getFloat(float* pResultado)
{
	int ret=-1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && isFloat(buffer))
	{
		ret=0;
		*pResultado = atof(buffer);
	}
	return ret;
}

// el index = strlen(pResultado)-1; contempla el enter, y a eso el -1, justamente abajo, indicamos, que si existe un enter=\n, que lo reemplace por un \0
static int myGets(char* pResultado, int len)
{
	int ret=-1;
	int index;
	fflush(stdin);

	if(fgets(pResultado,len,stdin)!=NULL)
		{
			index = strlen(pResultado)-1;
				if(pResultado[index]=='\n')
					{
						pResultado[index]='\0';
					}
			ret=0;
		}
	return ret;
}

static int isNumeric(char* pResultado)
{
	int ret=-1;
	int i=0; // me tomo esta licencia aca

	if(pResultado!=NULL && strlen(pResultado) > 0)
	{
		if(pResultado[0] == '-') // negativos
			{
				i = 1;
			}
			while(pResultado[i] !='\0')
			{
				if(pResultado[i] < '0'  || pResultado[i] > '9')
				{
					ret = 0;
				}
				i++;
			}
	}

	return ret;
}

static int isFloat(char* pResultado)
{
	int ret=-1;
	int i=0; // me tomo esta licencia aca

	if(pResultado[0] == '-') // negativos
	{
		i = 1;
	}
	for( ; pResultado[i] !='\0'; i++)
	{
		if((pResultado[i] > '9' || pResultado[i] < '0') && pResultado[i]!='.')
		{
			ret = 0;
		}
	}

	return ret;
}

static int isLetter(char* pResultado, int len)
{
	int ret=-1;
	int i=0;
	while(pResultado[i]!='\0')
	{
		if((pResultado[i] < 'A' || pResultado[i] > 'Z') && (pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i]!=' '))
			{
				ret = 0;
			}
		i++;
	}
	return ret;
}

static int isDni(char* pResultado, int len)
{
	int ret=-1;
	int i;
	int dotCount=0;

		for(i=1; i<len;i++)
		{
		//printf("Esta llegando aca\n");
			if(pResultado[i]!= '\0')
			{
				//printf("Esta llegando aca 2\n");
				if(pResultado[i] == '.')
				{
					ret = 0;
				}
				printf("Esta llegando aca 3\n");
				if(pResultado[i] < '1' || pResultado[i] > '9')
					{
						ret = 0;
					}
				if(pResultado[i] == '.')
					{
						//printf("Hay un punto\n");
						dotCount++;
					}
				if(dotCount !=2)
				{
					ret = -1;
				}
			}
		}
	// por ahora existen estas variantes para gente de 80/90 anios (dnis 0.000.000) y los centennials has 99 millones (dnis 00.000.000)
	if(pResultado[1] =='.' && pResultado[5] =='.')
	{
		if(pResultado[9] != '\0')
		{
			ret = -1;
		}
		else
		{
			ret = 0;
		}

	}
	else
	{
		if(pResultado[2] =='.' && pResultado[6] =='.')
		{
			ret = 0;
		}
		else
		{
			// no fue un dni valido
			ret = -1;
		}
	}

	//printf("pResultado en pos[8] %c \n", pResultado[8]);
	//printf("pResultado en pos[9] %c \n", pResultado[9]);
	//printf("el strlen de pResultado al final de la func. isDni %d \n", strlen(pResultado));
	if(strlen(pResultado)==9 && pResultado[8]!='\0' && pResultado[9]=='\0')
	{
		printf("strlen 9 pos 8 0 \n");
		ret=0;

	}
	else
	{
		if(pResultado[2]=='.' && pResultado[9]!='\0' && pResultado[10]=='\0')
		{
			ret=0;
		}
		else
		{
			// no cumple con el formato
			ret=-1;
		}
	}


	return ret;
}

// funciones desarrollo

int utn_getInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int aux;
	int ret=-1;

		if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				printf("%s",mensaje);
				if(getInt(&aux) == 0 && aux >= minimo && aux <= maximo)
				{
					*pResultado = aux;
					ret=0; // salio bien
					break;
				}
				else
				{
					printf("%s",mensajeError);
					ret=-1;
				}
			}
		}
		else
		{
			printf("%s",mensaje);
			ret=-1; // salio mal
		}

	return ret;
}

int utn_getFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float aux;
	int ret=-1;

		if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				printf("%s",mensaje);
				if(getFloat(&aux) == 0 && aux >= minimo && aux <= maximo)
				{
					*pResultado = aux;
					ret=0; // salio bien
					break;
				}
				else
				{
					printf("%s",mensajeError);
					ret=-1;
				}
			}
		}
		else
		{
			printf("%s",mensaje);
			ret=-1; // salio mal
		}

	return ret;
}

int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos)
{
	char aux[2];
	int ret=-1;

		if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL && minimo<=maximo && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				if(isdigit(*pResultado)==0)
				{
					printf("%s",mensaje);
					fgets(aux,sizeof(aux),stdin);
					strcpy(pResultado, aux);
					ret=0;
					break;
				}
				else
				{
					printf("%s",mensaje);
					ret=-1; // salio mal
				}
			}
		}

	return ret;
}

int utn_getText(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	char aux[1024];
	int ret=-1;

		if(pResultado!=NULL && len>0 && mensaje!=NULL && mensajeError!=NULL && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				printf("%s",mensaje);
				fflush(stdin);
				fgets(aux,sizeof(aux),stdin);
				aux[strlen(aux)-1]='\0';
				if(isLetter(aux, len)==-1 && strlen(aux)<len) // que solo sean letras y no numeros
				{
					ret=0;
					strcpy(pResultado, aux);
					break;
				}
				else
				{
					ret=-1; // salio mal
					printf("%s",mensajeError);
				}
			}
		}

	return ret;
}

int utn_getPosition(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	char aux[1024];
	int ret=-1;

		if(pResultado!=NULL && len>0 && mensaje!=NULL && mensajeError!=NULL && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				printf("%s",mensaje);
				fflush(stdin);
				fgets(aux,sizeof(aux),stdin);
				aux[strlen(aux)-1]='\0';
				utn_toUpper(aux, len);
				if((isLetter(aux, len)==-1 && strlen(aux)<len) && (strncmp(aux,"ARQ",len)==0 || strncmp(aux,"DEF",len)==0 || strncmp(aux,"MED",len)==0 || strncmp(aux,"DEL",len)==0))
				{
					ret=0;
					strcpy(pResultado, aux);
					break;
				}
				else
				{
					ret=-1;
					printf("%s",mensajeError);
				}
			}
		}

	return ret;
}

int utn_getConfederation(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	char aux[1024];
	int ret=-1;

		if(pResultado!=NULL && len>0 && mensaje!=NULL && mensajeError!=NULL && reintentos>=0)
		{
			while(reintentos>0)
			{
				reintentos--;
				printf("%s",mensaje);
				fflush(stdin);
				fgets(aux,sizeof(aux),stdin);
				aux[strlen(aux)-1]='\0';
				utn_toUpper(aux, len);
				if((isLetter(aux, len)==-1 && strlen(aux)<len) && (strncmp(aux,"AFC",len)==0 || strncmp(aux,"CAF",len)==0 || strncmp(aux,"CONCACAF",len)==0 || strncmp(aux,"CONMEBOL",len)==0 || strncmp(aux,"UEFA",len)==0 || strncmp(aux,"OFC",len)==0))
				{
					ret=0;
					strcpy(pResultado, aux);
					break;
				}
				else
				{
					ret=-1;
					printf("%s",mensajeError);
				}
			}
		}

	return ret;
}

void utn_toUpper(char* pResultado, int len)
{
	for(int i=0; i<len-1;i++)
		{
		pResultado[i]=toupper(pResultado[i]);
		}
}

int utn_getDni(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	char aux[12];
	int i;
	int ret=-1;

		if(pResultado!=NULL && len>0 && len<=12 && mensaje!=NULL && mensajeError!=NULL && reintentos>=0)
		{
			for(i=0;i<reintentos;i++)
			{
				printf("%s",mensaje);
				fflush(stdin);
				fgets(aux,len,stdin);
				aux[strlen(aux)-1]='\0';
				if(isDni(aux, len)==0 && strlen(aux)<=10)
				{
					strcpy(pResultado, aux);
					ret=0;
					break;
				}
			}
		}
		else
		{
			printf("%s",mensaje);
			ret=-1; // salio mal
		}

	return ret;
}
