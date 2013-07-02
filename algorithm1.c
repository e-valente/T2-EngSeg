/*
 * algorithm1.c
 *
 *  Created on: Jun 29, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithm1.h"

int chaos_enc(char *filename_in, char *filename_out, char *filename_key)
{
	int i, j, nchars;
	double x0, x;
	FILE *fp_in, *fp_out, *fp_key;
	char ch, n;
	unsigned char keyvec[KEY_NBITS/8];
	unsigned char *kvec, *msg_vec, *enc_vec;

	fp_in = fopen(filename_in, "r");
	if(!fp_in){
		perror("Input error!\n");
		exit(1);

	}

	/*conta o numero de caracteres*/
	fseek(fp_in, 0L, SEEK_END);
	nchars = ftell(fp_in);




	kvec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);
	msg_vec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);
	enc_vec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);





	//gerado pela senha
	fp_key = fopen(filename_key, "r");
	if(!fp_in){
		perror("Input error!\n");
		exit(1);

	}

	for(i = 0; i < KEY_NBITS /8; i++)
	{
		fscanf(fp_key, "%c", &keyvec[i]);
	}


	//calculo de x0


	x = 0.0;
	for(i = 0; i < KEY_NBITS /8; i++)
	{
		x += (keyvec[i]/8);
	}

	//normaliza pra ficar perto de 0.01
	if(x > 0.01)
	{
		while(x > 0.01)x /= 10;
	}

	if(x < 0.1)
	{
		while(x < 0.1)x *= 10;
	}


	x0 = x;



	/*Gera vetor k
	 * Cada ki será calculado a partir
	 * do 100k + i elemento da série do mapa
	 * logistico.
	 * O Total de elementos é o numero de
	 * caracteres do arquivo de entrada
	 */
	for(i = 0; i < 100000; i++)
	{
		x = 4 * x0 * (1 - x0);
		x0 = x;

	}

	for(i = 100000, j = 0; i < 100000 + nchars; i++, j++)
	{
		x = 4 * x0 * (1 - x0);
		x0 = x;
		kvec[j] = ((int)(10000 * x)) % 256;

	}

	/*coloca arquivo de entrada na memoria
	 *
	 */

	fseek(fp_in, 0L, SEEK_SET);
	i = 0;
	while(!feof(fp_in) && i < nchars)
	{
		n = fgetc(fp_in);
		if(!feof(fp_in))
		{
			msg_vec[i] = n;
			i++;
		}
	}


	printf("encriptando....\n");
	for(i = 0; i < nchars; i++)
	{
		enc_vec[i] = msg_vec[i] ^ kvec[i];
	}


	/*gravando (em binario) no arquivo
	 * e saida
	 */

	fp_out = fopen(filename_out, "wb");
	if(!fp_out)
	{
		perror("Input error!\n");
		exit(1);


	}

	fwrite(enc_vec, sizeof(unsigned char), nchars, fp_out);



	free(kvec);
	free(enc_vec);
	free(msg_vec);
	fclose(fp_in);
	fclose(fp_out);
	fclose(fp_key);

	return 0;
}



int chaos_dec(char *filename_in, char *filename_out, char *filename_key)
{
	int i, j, nchars;
	double x0, x;
	FILE *fp_in, *fp_out, *fp_key;
	unsigned int n;
	unsigned char keyvec[KEY_NBITS/8];
	unsigned char *kvec, *msg_vec, *enc_vec;

	fp_in = fopen(filename_in, "rb");
	if(!fp_in){
		perror("Input error!\n");
		exit(1);

	}

	/*conta o numero de caracteres*/
	fseek(fp_in, 0L, SEEK_END);
	nchars = ftell(fp_in);


	kvec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);
	msg_vec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);
	enc_vec = (unsigned char*)malloc(sizeof(unsigned char) * nchars);


	//gerado pela senha
	//gerado pela senha
	fp_key = fopen(filename_key, "r");
	if(!fp_key){
		perror("Input error!");
		exit(1);

	}

	for(i = 0; i < KEY_NBITS /8; i++)
	{
		fscanf(fp_key, "%c", &keyvec[i]);
	}


	//calculo de x0


	x = 0.0;
	for(i = 0; i < KEY_NBITS /8; i++)
	{
		x += (keyvec[i]/8);
	}

	//normaliza pra ficar perto de 0.01
	if(x > 0.01)
	{
		while(x > 0.01)x /= 10;
	}

	if(x < 0.1)
	{
		while(x < 0.1)x *= 10;
	}
	//printf("x0 vale %lf\n", x);


	x0 = x;


	/*Gera vetor k
	 * Cada ki será calculado a partir
	 * do 100k + i elemento da série do mapa
	 * logistico.
	 * O Total de elementos é o numero de
	 * caracteres do arquivo de entrada
	 */
	for(i = 0; i < 100000; i++)
	{
		x = 4 * x0 * (1 - x0);
		x0 = x;

	}

	for(i = 100000, j = 0; i < 100000 + nchars; i++, j++)
	{
		x = 4 * x0 * (1 - x0);
		x0 = x;
		kvec[j] = ((int)(10000 * x)) % 256;

	}

	/*coloca arquivo de entrada na memoria
	 *
	 */

	fseek(fp_in, 0L, SEEK_SET);
	i = 0;

	for(i = 0; i < nchars; i++)
	{
		fread(&n, sizeof(unsigned char), 1, fp_in);
		enc_vec[i] = n;
		//printf("%d\n",n);
	}


	//printf("decriptando....\n");
	for(i = 0; i < nchars; i++)
	{
		msg_vec[i] =  enc_vec[i] ^ kvec[i];
	}


	/*gravando msg em text plano no arquivo
	 * de saida
	 */

	fp_out = fopen(filename_out, "w");

	for(i = 0; i < nchars; i++)
	{
		fprintf(fp_out, "%c", msg_vec[i]);
	}



	free(kvec);
	free(enc_vec);
	free(msg_vec);
	fclose(fp_in);
	fclose(fp_out);
	fclose(fp_key);

	return 0;
}


int chaos_genkey(char *filename_key, int seed)
{
	int i;
	float x0, x;
	FILE *fp_out;
	unsigned char keyvec[KEY_NBITS/8];

	//gerado pela senha
	srand (time(NULL) + seed);



	fp_out = fopen(filename_key, "w");
	if(!fp_out)
	{
		perror("Input error!");
		exit(1);


	}

	for(i = 0; i < KEY_NBITS /8; i++)
	{
		keyvec[i] = rand()%256;
		fprintf(fp_out, "%d ", keyvec[i]);
	}

	x = 0.0;
	for(i = 0; i < KEY_NBITS /8; i++)
	{
		x += (keyvec[i]/8);
	}


	fclose(fp_out);

	return 0;


}
