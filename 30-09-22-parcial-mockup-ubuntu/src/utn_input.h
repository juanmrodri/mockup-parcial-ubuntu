/*
 * utn_input.h
 *
 *  Created on: 21 sept 2022
 *      Author: juanm
 */

#ifndef UTN_INPUT_H_
#define UTN_INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
* \brief Solicita un numero entero a un usuario y se llama a la funcion getInt para recibirlo
* \param pResultado Se carga el numero ingresado
* \param mensaje Mensaje que solicita que se debe hacer
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param minimo Limite inferior a validar
* \param maximo Limite superior a validar
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

/**
* \brief Solicita un numero flotante a un usuario y se llama a la funcion getInt para recibirlo
* \param pResultado Se carga el numero ingresado
* \param mensaje Mensaje que solicita que se debe hacer
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param minimo Limite inferior a validar
* \param maximo Limite superior a validar
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);

/**
* \brief Solicita un solo caracter, luego, si pasa el filtro de isdigit(), llama a fgets
* \param pResultado Se carga el caracter ingreado
* \param mensaje Mensaje que solicita que se debe hacer
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param minimo Limite inferior a validar
* \param maximo Limite superior a validar
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);

/**
* \brief Solicita una cadena de caracteres al usuario y si pasa las validaciones, se guardara en el puntero pResultado
* \param pResultado Se carga la cadena validada
* \param mensaje Mensaje que solicita que se debe hacer
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param minimo Limite inferior a validar
* \param maximo Limite superior a validar
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getText(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);

/**
* \brief Solicita una cadena de caracteres, pero, con la condicion indicada en mensaje al usuario y si pasa las validaciones, se guardara en el puntero pResultado
* \param pResultado Se carga la cadena validada
* \param mensaje Mensaje que solicita que se debe hacer
* \param len tamanio total de la cadena de caracteres
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getPosition(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);

/**
* \brief Solicita una cadena de caracteres, pero, con la condicion indicada en mensaje al usuario y si pasa las validaciones, se guardara en el puntero pResultado
* \param pResultado Se carga la cadena validada
* \param mensaje Mensaje que solicita que se debe hacer
* \param len tamanio total de la cadena de caracteres
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getConfederation(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);

/**
* \brief toma una cadena de caracteres, y utiliza por cada posicion, la funcion toupper, convirtiendo a mayusculas todos los caracteres
* \param pResultado Se carga la cadena validada
* \param len tamanio total de la cadena de caracteres
* \return ret = [0] - error = [1]
*/
void utn_toUpper(char* pResultado, int len);

/**
* \brief Solicita una cadena de caracteres, pero, con la condicion de que esta represente un n de dni y si pasa las validaciones, se guardara en el puntero pResultado
* \param pResultado Se carga la cadena validada
* \param mensaje Mensaje que solicita que se debe hacer
* \param len tamanio total de la cadena de caracteres
* \param mensajeError Es el mensaje a ser mostrado en caso de error
* \param reintentos cantidad de intentos en caso de error
* \return ret = [0] - error = [1]
*/
int utn_getDni(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);



#endif /* UTN_INPUT_H_ */
