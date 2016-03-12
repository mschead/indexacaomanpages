/*
 * RegistroIndicePrimario.h
 *
 *  Created on: Jun 18, 2015
 *      Author: marcos
 */

#ifndef REGISTROINDICEPRIMARIO_H_
#define REGISTROINDICEPRIMARIO_H_

#include <string.h>

class RegistroIndicePrimario {

//private:
public:
	int _indice;
	char _nome[70];

public:
	RegistroIndicePrimario() {
		_indice = -1;
	}

	RegistroIndicePrimario(int indice, const char* nome) {
		_indice = indice;
		strncpy(_nome, nome, sizeof(_nome));
	}

	bool operator<(RegistroIndicePrimario& n) {
		return strcmp(_nome, n._nome) < 0;
	}

	bool operator>(RegistroIndicePrimario& n) {
		return strcmp(_nome, n._nome) > 0;
	}

	bool operator==(RegistroIndicePrimario& n) {
			return strcmp(_nome, n._nome) == 0;
	}

};


#endif /* REGISTROINDICEPRIMARIO_H_ */
