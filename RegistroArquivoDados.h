/*
 * RegistroArquivoDados.h
 *
 *  Created on: Jun 18, 2015
 *      Author: marcos
 */

#ifndef REGISTROARQUIVODADOS_H_
#define REGISTROARQUIVODADOS_H_

#include <string>

class RegistroArquivoDados {
public:
	char _nome[70];
	char _conteudo[139730];

	RegistroArquivoDados() {

	}

	void setNome(const char* nome) {
		strncpy(_nome, nome, sizeof(_nome));
	}

	void setConteudo(char* conteudo) {
		strncpy(_conteudo, conteudo, sizeof(_conteudo));
	}


};

#endif /* REGISTROARQUIVODADOS_H_ */
