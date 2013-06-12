/*
 * handle_input.c
 *
 *  Created on: Jun 12, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>

#include "handle_input.h"

void handleInput(int argc, char **argv)
{
	int algorithm;
	char operation;


	if(argc != 6 && argc != 5) printOutputAndExit(argv);

	//Encripta ou decripta:
	if(argc == 6)
	{
		//algoritmo 1 ou 2
		algorithm = atoi(argv[1]);
		if(algorithm != 1 && algorithm != 2)printOutputAndExit(argv);

		//D ou E
		operation = argv[2][0];
		if(operation != 'E' && operation != 'D')printOutputAndExit(argv);

	}

	//Gera chave
	if(argc == 5)
	{
		//algoritmo 1 ou 2
		algorithm = atoi(argv[1]);
		if(algorithm != 1 && algorithm != 2)printOutputAndExit(argv);

		//operacao 'K' (key)
		operation = argv[2][0];
		if(operation != 'K')printOutputAndExit(argv);

	}

}


void printOutputAndExit(char **argv)
{

	fprintf(stderr, "Invalid output!\n");
	fprintf(stderr, "usage: \n%s <1 or 2> <D or E>"
			" <key file> <input file> <output file>\nor\n", argv[0]);
	fprintf(stderr, "%s <1 or 2> K <key file> <seed>\n", argv[0]);
	exit(1);

}
