/*
 * TratadorDisco.h
 *
 *  Created on: Jun 18, 2015
 *      Author: marcos
 */

#ifndef TRATADORINDICEPRIMARIO_H_
#define TRATADORINDICEPRIMARIO_H_
#include <queue>
#include <stdio.h>
#include "NoAVL.h"

template <typename T>
class TratadorIndicePrimario {

private:
	NoAVL<RegistroIndicePrimario>* indicePrimarioMemoria;
	FILE* indicePrimario;

public:

	TratadorIndicePrimario<T>(){
		indicePrimario = 0;
		indicePrimarioMemoria = 0;
	}

	void adicionarManPage(const char* nome, int indice) {

		RegistroIndicePrimario m = RegistroIndicePrimario(indice - 1, nome);

		if (indice == 0)
			indicePrimarioMemoria = new NoAVL<RegistroIndicePrimario>(m);

		indicePrimarioMemoria = indicePrimarioMemoria->inserir(m, indicePrimarioMemoria);

	}

	void salvarArvoreEmDisco() {
		NoAVL<RegistroIndicePrimario>* nodoVazio = new NoAVL<RegistroIndicePrimario>(RegistroIndicePrimario(-1, "##"));

		// 0 - há somente nodos nulos
		// 1 - transicao
		// 2 - não há somente nodos nulos
		int nivelFinal = 2;

		RegistroIndicePrimario m;
		indicePrimario = fopen("indicePrimario.dat", "wb+");
		int pecorrer = 1;

		if (!indicePrimarioMemoria)
			return;

		std::queue<NoAVL<T>*> nivelAtual, proximoNivel;
		nivelAtual.push(indicePrimarioMemoria);

		while ( /*!nivelAtual.empty() ||*/nivelFinal != 0) {
			NoAVL<T>* nodoAtual = nivelAtual.front();
			nivelAtual.pop();

			if (nodoAtual) {

				if (nodoAtual == nodoVazio) {
					proximoNivel.push(nodoVazio);
					proximoNivel.push(nodoVazio);

				} else {
					m = *(nodoAtual->getDado());
					fseek(indicePrimario, pecorrer * sizeof(RegistroIndicePrimario), SEEK_SET);
					fwrite(&m, 1, sizeof(RegistroIndicePrimario), indicePrimario);

					proximoNivel.push(nodoAtual->getEsquerda());
					proximoNivel.push(nodoAtual->getDireita());

					nivelFinal = 1;
				}

			} else {
				m = RegistroIndicePrimario(-1, "#");
				fseek(indicePrimario, pecorrer * sizeof(RegistroIndicePrimario), SEEK_SET);
				fwrite(&m, 1, sizeof(RegistroIndicePrimario), indicePrimario);

				proximoNivel.push(nodoVazio);
				proximoNivel.push(nodoVazio);
			}

			pecorrer++;

			if (nivelAtual.empty()) {

				if (nivelFinal == 1)
					nivelFinal = 2;
				else
					nivelFinal = 0;

				std::swap(nivelAtual, proximoNivel);
			}
		}

		fclose(indicePrimario);

	}


	void lerArvoreDisco(int argc) {
		indicePrimario = fopen("indicePrimario.dat", "rb");
		RegistroIndicePrimario m = RegistroIndicePrimario();

		for (int i = 0; i < argc; i++) {
			fseek(indicePrimario, i * sizeof(RegistroIndicePrimario), SEEK_SET);
			fread(&m, 1, sizeof(RegistroIndicePrimario), indicePrimario);
			printf("%s\n", m._nome);
			m = RegistroIndicePrimario();
		}

	}

	int buscarNoDisco(char* nome) {
		int registro = 1;
		indicePrimario = fopen("indicePrimario.dat", "rb");

		RegistroIndicePrimario m = RegistroIndicePrimario();
		fseek(indicePrimario, sizeof(RegistroIndicePrimario), SEEK_SET);
		fread(&m, 1, sizeof(RegistroIndicePrimario), indicePrimario);

		while (strcmp(nome, m._nome) != 0) {

			if (strcmp(m._nome, "#") == 0)
				return -1;

			if (strcmp(nome, m._nome) > 0)
				registro = 2 * (registro) + 1;
			else
				registro = (2 * (registro));


			m = RegistroIndicePrimario();
			fseek(indicePrimario, registro * sizeof(RegistroIndicePrimario), SEEK_SET);
			fread(&m, 1, sizeof(RegistroIndicePrimario), indicePrimario);

		}

		return m._indice;
	}


};

#endif /* TRATADORINDICEPRIMARIO_H_ */
