// Copyright [2015] <Marcos Schead> [legal/copyright]

#ifndef NO_AVL_HPP
#define NO_AVL_HPP

#include <cstdio>
#include <vector>

#define ELEMENTONAOEXISTENTE -2
#define ELEMENTOEXISTE -3


template<typename T>
class NoAVL {
 private:
	int altura;
	T* dado;
	NoAVL<T>* esquerda;
	NoAVL<T>* direita;
	std::vector<NoAVL<T>*> elementos;

	/* METODOS PRIVADOS */

	//! Método para realizar uma rotação simples a esquerda
	/*!
	 * \param1 nodo é o qual se encontra desbalanceado
	 * \return a referência para o nodo que será substituido pelo argumento
	 */

	NoAVL<T>* rotacaoEsquerda(NoAVL<T>* nodo) {
		NoAVL<T>* a = nodo->direita;

		if (a->esquerda != 0)
			nodo->direita = a->esquerda;
		else
			nodo->direita = 0;

		a->esquerda = nodo;

		atualizarAltura(nodo);
		atualizarAltura(a);
		return a;
	}

	//! Método para realizar uma rotação simples a direita
	/*!
	 * \param1 nodo é o qual se encontra desbalanceado
	 * \return a referência para o nodo que será substituido pelo argumento
	 */

	NoAVL<T>* rotacaoDireita(NoAVL<T>* nodo) {
		NoAVL<T>* a = nodo->esquerda;

		if (a->direita != 0)
			nodo->esquerda = a->direita;
		else
			nodo->esquerda = 0;

		a->direita = nodo;

		atualizarAltura(nodo);
		atualizarAltura(a);
	    return a;
	}

	//! Método para verificar para qual lado um nodo está desbalanceado,
	//! caso ele esteja de fato.
	/*!
	 * \param1 nodo é o que queremos verificar se está desbalanceado
	 * \return um valor, indicando para qual lado tende o desbalanceamento
	 */

	int getBalance(NoAVL<T>* nodo) {
		if (nodo == 0)
			return 0;

		return nodo->esquerda->getAltura() - nodo->direita->getAltura();
	}

	//! Método para atualizar a altura do nodo
	/*!
	 * \param1 nodo é o objeto que queremos atualizar
	 */

	void atualizarAltura(NoAVL<T>* nodo) {
		nodo->altura = maximo(nodo->esquerda->getAltura(),
				nodo->direita->getAltura()) + 1;
	}

	//! Método para obter o maior inteiro
	/*!
	 * \param1 dado1 é um dos números
	 * \param2 dado2 é o outro número
	 * \return o maior dentre os parâmetros fornecidos
	 */

	int maximo(int dado1, int dado2) {
		if (dado1 > dado2)
			return dado1;
		else
			return dado2;
	}

 public:

 	//! Construtor
	/*!
	 * Faça-se a inicialização de todos os atributos da classe. Inicialmente, o nodo não
	 * possui filhos, logo os ponteiros recebem zero, o dado recebe a informação passada
	 * por parâmetro e a altura inicial é 0.
	 *
	 */

	explicit NoAVL<T>(const T& dado) :
			dado(new T(dado)), esquerda(NULL), direita(NULL) {
		altura = 0;
	}

	//! Destrutor
	/*!
	 * Deve destruir as informações do nodo específico
	 */

	virtual ~NoAVL() {}

	//! Método para obter altura de um nodo
	/*!
	 * \return a altura do nodo que chamou o método
	 */

	int getAltura() {
		if (this == 0)
			return -1;

		return altura;
	}

	//! Método para obter todos os nodos descendentes do nodo em questão
	/*!
	 * \return os nodos na forma de uma lista do tipo vector.
	 */

	std::vector<NoAVL<T>*> getElementos() {
		return elementos;
	}

	//! Método para obter o filho da esquerda do nodo em questão
	/*!
	 * \return o nodo filho da esquerda
	 */

	NoAVL<T>* getEsquerda() {
		return esquerda;
	}

	//! Método para obter o filho da direita do nodo em questão
	/*!
	 * \return o nodo filho da direita
	 */

	NoAVL<T>* getDireita() {
		return direita;
	}

	//! Método para inserir um dado na estrutura do nodo arv
	/*!
	 * \param1 dado é um tipo genérico que se deseja inserir na estrutura
	 * \param2 o nodo com a estrutura, na qual queremos inserir o dado
	 * \return a referência para o nodo inserido em arv
	 */

	NoAVL<T>* inserir(T& dado, NoAVL<T>* arv) {
		if (arv == 0)
			return new NoAVL<T>(dado);

		if (dado < *(arv->dado))
			arv->esquerda = inserir(dado, arv->esquerda);
		else
			arv->direita = inserir(dado, arv->direita);


		atualizarAltura(arv);
		int balance = getBalance(arv);

		if (balance > 1 && dado < *(arv->esquerda->dado)) {
			return rotacaoDireita(arv);
		}

		if (balance < -1 && dado > *(arv->direita->dado)) {
			return rotacaoEsquerda(arv);
		}

		if (balance > 1 && dado > *(arv->esquerda->dado)) {
			arv->esquerda = rotacaoEsquerda(arv->esquerda);
			return rotacaoDireita(arv);
		}

		if (balance < -1 && dado < *(arv->direita->dado)) {
			arv->direita = rotacaoDireita(arv->direita);
			return rotacaoEsquerda(arv);
		}

		return arv;
	}

	//! Método para remover um dado na estrutura do nodo arv
	/*!
	 * \param1 o nodo com a estrutura, na qual queremos inserir o dado
	 * \param2 dado é um tipo genérico que se deseja inserir na estrutura
	 * \return a referência para o nodo removido em arv
	 */

	NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		NoAVL<T> *aux;

		if (arv == 0)
			return arv;

		if (dado < *(arv->getDado())) {
			arv->esquerda = remover(arv->esquerda, dado);
		} else {
			if (dado > *(arv->getDado())) {
				arv->direita = remover(arv->direita, dado);
			} else {
				if (arv->direita != 0 && arv->esquerda != 0) {
					aux = minimo(arv->direita);
					arv->dado = aux->dado;
					arv->direita = remover(arv->direita, *(aux->dado));
				} else {
					if (arv->direita != 0)
						aux = arv->direita;
					else
						aux = arv->esquerda;

					if (aux == 0) {
						aux = arv;
						arv = 0;
					} else {
						*arv = *aux;
					}

					 delete aux;
				}
			}
		}

		if (arv == 0)
			return arv;

		atualizarAltura(arv);
		int balance = getBalance(arv);

		if (balance > 1 && getBalance(arv->esquerda) >= 0) {
			return rotacaoDireita(arv);
		}

		if (balance < -1 && getBalance(arv->direita) <= 0) {
			return rotacaoEsquerda(arv);
		}

		if (balance > 1 && getBalance(arv->esquerda) < 0) {
			arv->esquerda = rotacaoEsquerda(arv->esquerda);
			return rotacaoDireita(arv);
		}

		if (balance < -1 && getBalance(arv->direita) > 0) {
			arv->direita = rotacaoDireita(arv->direita);
			return rotacaoEsquerda(arv);
		}

		return arv;
	}

	//! Método para obter o menor dado da estrutura nodo passada por parâmetro
	/*!
	 * \param1 o nodo com a estrutura, na qual queremos procura o menor dado
	 * \return a referência para o menor nodo
	 */

	NoAVL<T>* minimo(NoAVL<T>* nodo) {
		NoAVL<T>* aux = nodo;
		while (aux->esquerda != 0)
			aux = aux->esquerda;

		return aux;
	}

	//! Método para obter o dado do nodo em questão
	/*!
	 * \return a informação guardada pelo nodo.
	 */

	T* getDado() {
		return dado;
	}

	//! Método para buscar um dado na estrutura do nodo arv
	/*!
	 * \param1 dado é um tipo genérico que se deseja inserir na estrutura
	 * \param2 o nodo que se começa a busca pelo dado
	 * \return a referência para o dado procurado
	 */

	T* busca(const T& dado, NoAVL<T>* arv) {
		while (arv != 0 && *(arv->dado) != dado) {
			if (*(arv->dado) < dado)
				arv = arv->direita;
			else
				arv = arv->esquerda;
		}

		if (arv == 0)
			throw ELEMENTONAOEXISTENTE;

		return arv->getDado();
	}

	//! Método para organizar em preOrdem os descendentes de nodo,
	//! no vetor elementos
	/*!
	 * \param1 o nodo com os descendentes, os quais queremos organizar
	 */

	void preOrdem(NoAVL<T>* nodo) {
		if (nodo != 0) {
			elementos.push_back(nodo);
			preOrdem(nodo->esquerda);
			preOrdem(nodo->direita);
		}
	}

	//! Método para organizar emOrdem os descendentes de nodo, no vetor elementos
	/*!
	 * \param1 o nodo com os descendentes, os quais queremos organizar
	 */

	void emOrdem(NoAVL<T>* nodo) {
		if (nodo != 0) {
			emOrdem(nodo->esquerda);
			elementos.push_back(nodo);
			emOrdem(nodo->direita);
		}
	}

	//! Método para organizar em posOrdem os descendentes de nodo,
	//! no vetor elementos
	/*!
	 * \param1 o nodo com os descendentes, os quais queremos organizar
	 */

	void posOrdem(NoAVL<T>* nodo) {
		if (nodo != 0) {
			posOrdem(nodo->esquerda);
			posOrdem(nodo->direita);
			elementos.push_back(nodo);
		}
	}

};

#endif /* NO_AVL_HPP */
