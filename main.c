/*
 * main.c
 *
 *  Created on: Jun 12, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>

#include "handle_input.h"

//#include "algorithm1.h"
//#include "algorithm2.h"

int main(int argc, char *argv[])
{
	FILE *fp_in, *fp_out, *fp_key;
	int algorithm, seed;
	char operation;


	/*nao alocar nada antes desse ponto,
	 * pois handle input pode dar exit(1)
	 * ocasionado leak memory
	 */
	handleInput(argc, argv);


	//argc e argv estao ok nesse ponto!
	algorithm = atoi(argv[1]);
	operation = argv[2][0];


	//algoritmo 1
	if(algorithm == 1)
	{
		if(operation == 'K')
		{
			//gera chave
			fp_key = fopen(argv[3], "w");
			seed = atoi(argv[4]);


			fclose(fp_key);
		}


		//abre arquivos e entrada e saida

		if(operation == 'E')
		{
			//encripta

		}

		if(operation == 'D')
		{
			//desencripta

		}

		//nao esqueca de dar fclose
		//em todos arquivos qdo chegar aqui


	}

	//algoritmo 2
	if(algorithm == 2)
	{
		if(operation == 'K')
		{

			//gera chave
			fp_key = fopen(argv[3], "w");
			seed = atoi(argv[4]);


			fclose(fp_key);
		}


		//abre arquivos e entrada e saida
		if(operation == 'E')
		{
			//encripta

		}

		if(operation == 'D')
		{
			//desencripta

		}



	}


	return 0;
}

