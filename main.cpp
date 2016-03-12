/*
 * main.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: marcos
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "RegistroIndicePrimario.h"
#include "RegistroArquivoDados.h"
#include "TratadorIndicePrimario.h"
#include "TratadorIndiceSecundario.h"
#include "TratadorArquivoDados.h"
#include <iostream>
#include <sys/time.h>



double timeit(struct timeval &start, struct timeval &end) {
	double delta = ((end.tv_sec - start.tv_sec) * 1000000u + end.tv_usec
			- start.tv_usec) / 1.e6;
	return delta;
}


int main(int argc, char* argv[]) {

	TratadorIndicePrimario<RegistroIndicePrimario>* t1 = new TratadorIndicePrimario<RegistroIndicePrimario>();
	TratadorIndiceSecundario* t2 = new TratadorIndiceSecundario();
	TratadorArquivoDados* t3 = new TratadorArquivoDados();

	char conteudo[139730];
	struct stat st;

	struct timeval start, end;
	gettimeofday(&start, NULL);


	//argc = 1000;
	for (int i = 1; i < argc; i++) {
		printf("Indice Primário(%d): %s\n", i - 1, argv[i]);

		FILE* arquivo = fopen(argv[i], "r");
		stat(argv[i], &st);

		std::string s = std::string(argv[i]);
		int size = s.size();
		s = s.substr(0, size - 4);
		s = s.substr(9);

		t1->adicionarManPage(s.c_str(), i);

		fclose(arquivo);
	}

	t1->salvarArvoreEmDisco();

	for (int i = 1; i < argc; i++) {
		printf("Arquivo de Dados(%d): %s\n", i - 1, argv[i]);

		FILE* arquivo = fopen(argv[i], "r");
		stat(argv[i], &st);

		std::string s = std::string(argv[i]);
		int size = s.size();
		s = s.substr(0, size - 4);
		s = s.substr(9);

		fread(conteudo, 1, st.st_size, arquivo);

		t3->inserirManpage(s.c_str(), conteudo, i);

		fclose(arquivo);
		memset(conteudo, 0, sizeof(conteudo));
	}

	t3->fecharArquivo();

	for (int i = 1; i < argc; i++) {
		printf("Indice Secundário(%d): %s\n", i - 1, argv[i]);

		FILE* arquivo = fopen(argv[i], "r");
		stat(argv[i], &st);
		fread(conteudo, 1, st.st_size, arquivo);

		t2->tratarConteudoManpage(conteudo, i);

		fclose(arquivo);
		memset(conteudo, 0, sizeof(conteudo));
	}

	t2->fecharArquivo();


	gettimeofday(&end, NULL);
	double timeTaken = timeit(start,end);
	std::cout << "Tempo de indexação: " << timeTaken << " segundos" << std::endl;


	char i[20];
	int indice = -1;
	std::vector<int> registros1, registros2;

	do {
		printf("\n%s\n", "*********************************");
		printf("%s\n", "[1] Pesquisar pelo nome");
		printf("%s\n", "[2] Pesquisar por palavra");
		printf("%s\n", "[3] Pesquisar por duas palavras");
		printf("%s\n", "[4] Sair");
		printf("%s\n", "*********************************");
		printf("%s", "Opção: ");
		std::cin >> i;


		if (strcmp("1", i) == 0) {
			printf("%s", "Digite o nome da manpage: ");
			std::cin >> i;

			indice = t1->buscarNoDisco(i);
			if (indice != -1)
				t3->imprimirConteudoManpage(indice);
		}

		if (strcmp("2", i) == 0) {
			printf("%s", "Digite a palavra: ");
			std::cin >> i;

			registros1 = t2->registrosComPalavra(i);

			for (std::vector<int>::iterator it = registros1.begin(); it != registros1.end(); ++it)
				t3->imprimirNomeManpage(*it);

		}

		if (strcmp("3", i) == 0) {

			printf("%s", "Digite a primeira palavra: ");
			std::cin >> i;
			registros1 = t2->registrosComPalavra(i);

			printf("%s", "Digite a segunda palavra: ");
			std::cin >> i;
			registros2 = t2->registrosComPalavra(i);


			if (registros1.size() < registros2.size()) {
				for (std::vector<int>::iterator it1 = registros1.begin(); it1 != registros1.end(); ++it1) {
					for (std::vector<int>::iterator it2 = registros2.begin(); it2 != registros2.end(); ++it2) {
						if (*it1 == *it2)
							t3->imprimirNomeManpage(*it1);
					}
				}
			} else {
				for (std::vector<int>::iterator it2 = registros2.begin(); it2 != registros2.end(); ++it2) {
					for (std::vector<int>::iterator it1 = registros1.begin(); it1 != registros1.end(); ++it1) {
						if (*it1 == *it2)
							t3->imprimirNomeManpage(*it1);
					}
				}
			}
		}

	} while (strcmp(i, "4") != 0);


	return 0;
}


#endif /* MAIN_CPP_ */



