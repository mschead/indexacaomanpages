/*
 * TratadorIndiceSecundario.h
 *
 *  Created on: Jun 19, 2015
 *      Author: marcos
 */

#ifndef TRATADORINDICESECUNDARIO_H_
#define TRATADORINDICESECUNDARIO_H_

#include <string>
#include <string.h>
#include <set>
#include "RegistroIndiceSecundario.h"

#define QUANTIDADEREGISTROS 5700
#define QUANTIDADELISTAS 500

class TratadorIndiceSecundario {

private:
	FILE* listasPalavras[QUANTIDADELISTAS];
	int quantidadePalavras[QUANTIDADELISTAS];
	FILE* registrosPalavras;
	int quantidadeRegistrosPalavras;

	std::set<std::string> conectivos;

public:

	TratadorIndiceSecundario() {
		registrosPalavras = fopen("registrosPalavras.dat", "wb+"); //VERIFICAR PARTES DO CODIGO QUE USO
		for (int i = 0; i < QUANTIDADELISTAS; i++)
			quantidadePalavras[i] = 0;

		quantidadeRegistrosPalavras = 0;
		inserirConectivos();
	}

	void inserirConectivos() {
		conectivos.insert("The"); conectivos.insert("the");
		conectivos.insert("An"); conectivos.insert("an");
		conectivos.insert("Than"); conectivos.insert("than");
		conectivos.insert("Then"); conectivos.insert("then");
		conectivos.insert("Of"); conectivos.insert("of");
		conectivos.insert("As"); conectivos.insert("as");
		conectivos.insert("For"); conectivos.insert("for");
		conectivos.insert("From"); conectivos.insert("from");
		conectivos.insert("is"); conectivos.insert("Is");
		conectivos.insert("are"); conectivos.insert("Are");
		conectivos.insert("In"); conectivos.insert("in");
		conectivos.insert("On"); conectivos.insert("on");
		conectivos.insert("By"); conectivos.insert("by");
		conectivos.insert("Which"); conectivos.insert("which");
		conectivos.insert("What"); conectivos.insert("what");
		conectivos.insert("Where"); conectivos.insert("where");
		conectivos.insert("And"); conectivos.insert("and");
		conectivos.insert("These"); conectivos.insert("these");
		conectivos.insert("Those"); conectivos.insert("those");
		conectivos.insert("This"); conectivos.insert("this");
		conectivos.insert("That"); conectivos.insert("that");
		conectivos.insert("Can"); conectivos.insert("can");
		conectivos.insert("Be"); conectivos.insert("be");
		conectivos.insert("With"); conectivos.insert("with");
		conectivos.insert("Without"); conectivos.insert("without");
		conectivos.insert("To"); conectivos.insert("to");
		conectivos.insert("If"); conectivos.insert("if");
		conectivos.insert("Into"); conectivos.insert("into");
		conectivos.insert("Onto"); conectivos.insert("onto");
		conectivos.insert("Not"); conectivos.insert("not");
		conectivos.insert("More"); conectivos.insert("more");
		conectivos.insert("Must"); conectivos.insert("must");
		conectivos.insert("Otherwise"); conectivos.insert("otherwise");
		conectivos.insert("Until"); conectivos.insert("until");
		conectivos.insert("It"); conectivos.insert("it");
		conectivos.insert("You"); conectivos.insert("you");

		conectivos.insert("a");	conectivos.insert("b");
		conectivos.insert("c");	conectivos.insert("d");
		conectivos.insert("e");	conectivos.insert("f");
		conectivos.insert("g");	conectivos.insert("h");
		conectivos.insert("i");	conectivos.insert("j");
		conectivos.insert("k");	conectivos.insert("l");
		conectivos.insert("m");	conectivos.insert("n");
		conectivos.insert("o");	conectivos.insert("p");
		conectivos.insert("q");	conectivos.insert("r");
		conectivos.insert("s");	conectivos.insert("t");
		conectivos.insert("u");	conectivos.insert("v");
		conectivos.insert("w");	conectivos.insert("x");
		conectivos.insert("y");	conectivos.insert("z");
		conectivos.insert("A"); conectivos.insert("B");
		conectivos.insert("C"); conectivos.insert("D");
		conectivos.insert("E");	conectivos.insert("F");
		conectivos.insert("G");	conectivos.insert("H");
		conectivos.insert("I");	conectivos.insert("J");
		conectivos.insert("K");	conectivos.insert("L");
		conectivos.insert("M");	conectivos.insert("N");
		conectivos.insert("O");	conectivos.insert("P");
		conectivos.insert("Q");	conectivos.insert("R");
		conectivos.insert("S");	conectivos.insert("T");
		conectivos.insert("U");	conectivos.insert("V");
		conectivos.insert("W");	conectivos.insert("X");
		conectivos.insert("Y");	conectivos.insert("Z");

		conectivos.insert("0"); conectivos.insert("1");
		conectivos.insert("2"); conectivos.insert("3");
		conectivos.insert("4"); conectivos.insert("5");
		conectivos.insert("6"); conectivos.insert("7");
		conectivos.insert("8"); conectivos.insert("9");

		conectivos.insert("mlib"); conectivos.insert("hy");
		conectivos.insert("Or"); conectivos.insert("or");

		//conectivos.insert("File"); conectivos.insert("file");
		conectivos.insert("75i"); conectivos.insert("attributes");
		conectivos.insert("following"); conectivos.insert("function");
		conectivos.insert("name");

	}

	void tratarConteudoManpage(char* conteudo, int indice) {
		indice--;
		std::set<std::string> palavrasAdicionadas;
		int numeroArquivo = 0;
		RegistroIndiceSecundario reg = RegistroIndiceSecundario();

		char* palavra = strtok(conteudo, ", <->`[]{}@$&+-/!*/()'.\":#_=|;\n");
		while (palavra != NULL) {

			std::string aux = std::string(palavra);

			if (conectivos.find(aux) == conectivos.end() && palavrasAdicionadas.find(aux) == palavrasAdicionadas.end()) {

				numeroArquivo = funcaoHashing(palavra);
				char nomeArquivo[30];
				snprintf (nomeArquivo, sizeof(nomeArquivo), "Hash/listasPalavras%d.dat", numeroArquivo);

				if (quantidadePalavras[numeroArquivo] == 0)
					listasPalavras[numeroArquivo] = fopen(nomeArquivo, "wb+");
				else
					listasPalavras[numeroArquivo] = fopen(nomeArquivo, "rb+");

				if (!palavraExistente(palavra, numeroArquivo, indice)) {
					reg = RegistroIndiceSecundario(palavra, quantidadeRegistrosPalavras);

					// Escrever na lista calculada pelo hash
					// ESSA LINHA POSSO COMENTAR TALVEZ
					//fseek(listasPalavras[numeroArquivo], quantidadePalavras[numeroArquivo] * sizeof(RegistroIndiceSecundario), SEEK_SET);
					fwrite(&reg, 1, sizeof(RegistroIndiceSecundario), listasPalavras[numeroArquivo]);

					// Escreve no arquivo de registros geral
					fseek(registrosPalavras, quantidadeRegistrosPalavras * QUANTIDADEREGISTROS * sizeof(int), SEEK_SET);
					fwrite(&indice, 1, sizeof(int), registrosPalavras);

					quantidadePalavras[numeroArquivo]++;
					quantidadeRegistrosPalavras++;

				}

				fclose(listasPalavras[numeroArquivo]);
				palavrasAdicionadas.insert(palavra);

			}
			palavra = strtok(NULL, ", <->`[]{}@$&+-/!*/()'.\":#_=|;\n");
		}

	}
	void fecharArquivo() {
		fclose(registrosPalavras);
	}


	bool palavraExistente(char* palavra, int numeroArquivo, int indice) {
		RegistroIndiceSecundario reg = RegistroIndiceSecundario();
		int qtdPalavras = quantidadePalavras[numeroArquivo];

		int i = 0;
		while (i < qtdPalavras) {
			// ESSA AQUI POSSO COMENTAR
			//fseek(listasPalavras[numeroArquivo], i * sizeof(RegistroIndiceSecundario), SEEK_SET);
			fread(&reg, 1, sizeof(RegistroIndiceSecundario), listasPalavras[numeroArquivo]);

			if (strcmp(reg._palavra, palavra) == 0) {
				fseek(registrosPalavras, (QUANTIDADEREGISTROS * reg._indice * sizeof(int)) + (reg._quantidadePalavras * sizeof(int)), SEEK_SET);
				fwrite(&indice, 1, sizeof(int), registrosPalavras);

				reg._quantidadePalavras++;
				fseek(listasPalavras[numeroArquivo], i * sizeof(RegistroIndiceSecundario), SEEK_SET);
				fwrite(&reg, 1, sizeof(RegistroIndiceSecundario), listasPalavras[numeroArquivo]);

				return true;
			}

			i++;
			reg = RegistroIndiceSecundario();
		}

		return false;
	}



	std::vector<int> registrosComPalavra(char* palavra) {
		RegistroIndiceSecundario reg = RegistroIndiceSecundario();

		int aux = 0;
		std::vector<int> retorno;

		int numeroArquivo = funcaoHashing(palavra);
		char nomeArquivo[30];
		snprintf (nomeArquivo, sizeof(nomeArquivo), "Hash/listasPalavras%d.dat", numeroArquivo);

		listasPalavras[numeroArquivo] = fopen(nomeArquivo, "rb+");
		registrosPalavras = fopen("registrosPalavras.dat", "rb+");


		int i = 0;
		while (i < quantidadePalavras[numeroArquivo]) {
			fseek(listasPalavras[numeroArquivo], i * sizeof(RegistroIndiceSecundario), SEEK_SET);
			fread(&reg, 1, sizeof(RegistroIndiceSecundario), listasPalavras[numeroArquivo]);

			if (strcmp(reg._palavra, palavra) == 0) {

				int deslocamento = (reg._indice * QUANTIDADEREGISTROS * sizeof(int)) + (0 * sizeof(int));
				fseek(registrosPalavras, deslocamento, SEEK_SET);

				for (int j = 0; j < reg._quantidadePalavras; j++) {
					fread(&aux, 1, sizeof(int), registrosPalavras);
					retorno.push_back(aux);
				}

				fclose(listasPalavras[numeroArquivo]);
				fclose(registrosPalavras);
				return retorno;

			}

			i++;
		}

		fclose(listasPalavras[numeroArquivo]);
		fclose(registrosPalavras);
		return retorno;
	}


	void imprimirListas() {

		char nomeArquivo[30];
		int maiorIndice = 0;
		int maiorQuantidade = 0;
		char palavraQueMaisAparece[60];

		FILE *arquivo;
		RegistroIndiceSecundario reg = RegistroIndiceSecundario();

		for (int i = 0; i < QUANTIDADELISTAS; i++) {
			snprintf (nomeArquivo, sizeof(nomeArquivo), "Hash/listasPalavras%d.dat", i);
			arquivo = fopen(nomeArquivo, "rb+");

			printf("%s\n", "------------------------------------");
			printf("Lista %d: %s\n", i, nomeArquivo);

			for (int j = 0; j < quantidadePalavras[i]; j++) {
				fseek(arquivo, j * sizeof(RegistroIndiceSecundario), SEEK_SET);
				fread(&reg, 1, sizeof(RegistroIndiceSecundario), arquivo);

				printf("Quantidade de palavras dessa lista : %d\n", quantidadePalavras[i]);
				printf("Palavra: %s\n", reg._palavra);
				printf("Quantidade: %d\n", reg._quantidadePalavras);
				printf("Indice: %d\n\n", reg._indice);

				if (reg._indice > maiorIndice)
					maiorIndice = reg._indice;

				if (reg._quantidadePalavras > maiorQuantidade) {
					maiorQuantidade = reg._quantidadePalavras;
					strcpy(palavraQueMaisAparece, reg._palavra);
				}

				reg = RegistroIndiceSecundario();

			}
			//printf("%s\n", "------------------------------------");

		}

		printf("Quantidade de palavras: %d\n", maiorQuantidade);
		//printf("Maior Quantidade de palavras de todas: %d\n", maiorQuantidade);
		printf("Palavra que mais aparece: %s\n", palavraQueMaisAparece);

	}





	int funcaoHashing(char* chave) {
		int soma = 0;
		for (unsigned int i = 0; i < strlen(chave); i++)
			soma = soma + chave[i];

		return soma % QUANTIDADELISTAS;
	}






};


#endif /* TRATADORINDICESECUNDARIO_H_ */
