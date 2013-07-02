==Compilar==
*deps: compilador C, compilador java e VM java

Para compilar, digite:
make

==Gerar chaves==
./t2-engseg 1 K chave.txt 7
./t2-engseg 2 K chave.txt 7
O primeiro exemplo gera a chave para o algoritmo 1 (crypto chaos) e o
segundo para o algoritmo 2 (RC4 modificado). Ambas chaves são de 2048 bits.
 
==Encriptar==

./t2-engseg 1 E chave.txt arquivoentrada.txt arquivosaida.enc
ou 
./t2-engseg 2 E chave.txt arquivoentrada.txt arquivosaida.enc

==Decriptar==

./t2-engseg 1 D chave.txt arquivosaida.enc arquivosaida.txt
ou 
./t2-engseg 2 D chave.txt arquivosaida.enc arquivosaida.txt
