/*
 * algorithm1.h
 *
 *  Created on: Jun 29, 2013
 *      Author: emanuel
 */

#ifndef ALGORITHM1_H_
#define ALGORITHM1_H_

#define KEY_NBITS 2048

int chaos_enc(char *filename_in, char *filename_out, char *filename_key);
int chaos_dec(char *filename_in, char *filename_out, char *filename_key);
int chaos_genkey(char *filename_key, int seed);

#endif /* ALGORITHM1_H_ */
