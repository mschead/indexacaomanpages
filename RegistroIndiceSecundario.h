/*
 * RegistroIndiceSecundario.h
 *
 *  Created on: Jun 18, 2015
 *      Author: marcos
 */

#ifndef REGISTROINDICESECUNDARIO_H_
#define REGISTROINDICESECUNDARIO_H_

class RegistroIndiceSecundario {

public:
	int _indice;
	int _quantidadePalavras;
	char _palavra[70];

public:
	RegistroIndiceSecundario() {
		_indice = -1;
		_quantidadePalavras = 0;
	}

	RegistroIndiceSecundario(const char* palavra, int indice, int quantidadePalavras = 1) {
		_indice = indice;
		_quantidadePalavras = quantidadePalavras;
		strncpy(_palavra, palavra, sizeof(_palavra));
	}



};

#endif /* REGISTROINDICESECUNDARIO_H_ */
