/*
 * TratadorArquivoDados.h
 *
 *  Created on: Jun 19, 2015
 *      Author: marcos
 */

#ifndef TRATADORARQUIVODADOS_H_
#define TRATADORARQUIVODADOS_H_

#define TAMANHOREGISTRO 139800
#define TAMANHOCONTEUDO 139730
#define TAMANHONOME 70

#include <stdio.h>

class TratadorArquivoDados {

private:
	FILE* arquivoRegistros;

public:

	TratadorArquivoDados() {
		arquivoRegistros = fopen("manpages.dat", "wb+");
	}

	void inserirManpage(const char* nome, char* conteudo, int indice) {
		RegistroArquivoDados reg = RegistroArquivoDados();
		reg.setNome(nome);
		reg.setConteudo(conteudo);

		//fseek(arquivoRegistros, (indice - 1) * sizeof(RegistroArquivoDados), SEEK_SET);
		fwrite(&reg, 1, sizeof(RegistroArquivoDados), arquivoRegistros);
	}

	void fecharArquivo() {
		fclose(arquivoRegistros);
	}

	void imprimirNomeManpage(int indice) {
		RegistroArquivoDados reg = RegistroArquivoDados();
		arquivoRegistros = fopen("manpages.dat", "rb");

		fseek(arquivoRegistros, indice * sizeof(RegistroArquivoDados), SEEK_SET);
		fread(&reg, 1, sizeof(RegistroArquivoDados), arquivoRegistros);

		printf("%s\n", " ");
		printf("%s", reg._nome);
		printf("%s\n", " ");

		fclose(arquivoRegistros);

	}

	void imprimirConteudoManpage(int indice) {
		RegistroArquivoDados reg = RegistroArquivoDados();
		arquivoRegistros = fopen("manpages.dat", "rb");

		fseek(arquivoRegistros, indice * sizeof(RegistroArquivoDados), SEEK_SET);
		fread(&reg, 1, sizeof(RegistroArquivoDados), arquivoRegistros);

		printf("%s\n", " ");
		printf("%s", reg._conteudo);
		printf("%s\n", " ");

		fclose(arquivoRegistros);

	}



	void imprimirArquivoDados(int argc) {
		RegistroArquivoDados reg = RegistroArquivoDados();
		arquivoRegistros = fopen("manpages.dat", "rb");

		for (int i = 1; i < argc; i++) {
			fseek(arquivoRegistros, (i - 1) * TAMANHOREGISTRO, SEEK_SET);
			fread(&reg, 1, sizeof(RegistroArquivoDados), arquivoRegistros);
			printf("Numero: %d Arquivo: %s\n", i, reg._nome);
			//printf("%s\n\n", reg._conteudo);
		}

		fclose(arquivoRegistros);

	}

};

#endif /* TRATADORARQUIVODADOS_H_ */
