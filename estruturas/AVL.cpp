#include <iostream>
using namespace std;

class noh{
	private:
		int dado;
		int altura;
		noh* pai;
		noh* esquerdo;
		noh* direito;	
		friend class arvore;

	public:
		noh(int valor);	
		
};

noh::noh(int valor){
	pai = NULL;
	esquerdo = NULL;
	direito = NULL;
	altura = 1;
	dado = valor;
}

class arvore{
	private:
		noh* raiz;
	
		noh* inserirAuxRecursivo(noh* umNoh, int valor);
		noh*buscaAux(int umValor);
		noh* minimoAux(noh* raizSubarvore);
		noh* maximoAux(noh* raizSubarvore);
				
	public:
		arvore();
		void inserir(int valor);
		void buscar(int umValor);
		
		void remover(int valor);
		void transplanta(noh* antigo, noh* novo);	
		
		int minimo();
		int maximo();
		
		int informaAltura(noh* umNoh);
		int maiorAltura(int alturaArvoreEsquerda, int alturaArvoreDireita);
		void atualizaAltura(noh* umNoh);
		int fatorBalanceamento(noh* umNoh);
			
		void rotacaoSimplesEsquerda(noh* umNoh);
		void rotacaoSimplesDireita(noh* umNoh);
		void rotacaoEsquerdaDireita(noh* umNoh);
		void rotacaoDireitaEsquerda(noh* umNoh);
};

arvore::arvore(){
	raiz = NULL;
}

noh* arvore::inserirAuxRecursivo(noh* umNoh, int valor){
	if(umNoh == NULL){
		noh* novoNoh = new noh(valor);
		return novoNoh; 
	
	} else {
		
		if(valor < umNoh->dado){
			umNoh->esquerdo = inserirAuxRecursivo(umNoh->esquerdo, valor);
			umNoh->esquerdo->pai = umNoh;
		}else{
			umNoh->direito = inserirAuxRecursivo(umNoh->direito, valor);
			umNoh->direito->pai = umNoh;
		}	
		
	}
	
	return umNoh;
}

void arvore::inserir(int valor){
		raiz = inserirAuxRecursivo(raiz, valor);
}

int arvore::minimo(){
	if(raiz == NULL){
		cout << "arvore vazia";
		
	} else {
		noh* menorNoh = minimoAux(raiz);
		return menorNoh->dado;
	}
}

noh* arvore::minimoAux(noh* raizSubarvore){
	//tem que ir pra esquerda ate acabar a arvore, ou seja, ate achar um noh em que o ponteiro esquerdo aponta pra null
	while(raizSubarvore->esquerdo != NULL){
		raizSubarvore = raizSubarvore->esquerdo; 
	}
	
	return raizSubarvore;
}


int arvore::maximo(){
	if(raiz == NULL){
		cout << "arvore vazia\n";
	
	}else {
		noh* maiorNoh = maximoAux(raiz);
		return maiorNoh->dado;
	}
}

noh* arvore::maximoAux(noh* raizSubarvore){
	//tem que ir pra direita enquanto o noh nn apontar pra NULL
	while(raizSubarvore->direito != NULL){
		raizSubarvore = raizSubarvore->direito;
	}
	
	return raizSubarvore;
}

void arvore::buscar(int umValor){
	noh* nohBuscado = buscaAux(umValor);
	
	if(nohBuscado == NULL){
		cout << "O noh buscado nao esta na arvore\n";
	}else{
		cout << "O numero " 
			 << nohBuscado->dado
			 << " foi encontrado!\n"; 			 
	}
}

noh* arvore::buscaAux(int umValor){
	noh* nohParaBusca = raiz;
	while(nohParaBusca != NULL){
		if(nohParaBusca->dado == umValor){
			return nohParaBusca;
		}else if(nohParaBusca->dado > umValor){
			nohParaBusca = nohParaBusca->esquerdo;
		}else{
			nohParaBusca = nohParaBusca->direito;
		} 
	}
	
	return nohParaBusca;
}

void arvore::transplanta(noh* antigo, noh* novo){
	
	if(raiz == antigo){
		raiz = novo;
	}else if(antigo == antigo->pai->esquerdo){
		antigo->pai->esquerdo = novo;
	}else{
		antigo->pai->direito = novo;
	}
	
	if(novo != NULL){
		novo->pai = antigo->pai;
	}
}

void arvore::remover(int valor){
	noh* nohRemover = buscaAux(valor);
	
	if(nohRemover == NULL){
		cout << "Noh nao encontrado \n";
	}else {
		if(nohRemover->esquerdo == NULL){
			transplanta(nohRemover, nohRemover->direito);
		}else if(nohRemover->direito == NULL){
			transplanta(nohRemover, nohRemover->esquerdo);
		}else{
			noh* sucessor = minimoAux(nohRemover->direito);
			if(sucessor->pai != nohRemover){
				transplanta(sucessor, sucessor->direito);
				sucessor->direito = nohRemover->direito;
				sucessor->direito->pai = sucessor;
			}
						
			transplanta(nohRemover, sucessor);
			sucessor->esquerdo = nohRemover->esquerdo;
			sucessor->esquerdo->pai = sucessor;         

		}
		
		delete[] nohRemover;
	}
}

int arvore::informaAltura(noh* umNoh){
	if(umNoh = NULL){
		return 0;
	}else{
		return umNoh->altura;
	}
}

int arvore::maiorAltura(int alturaArvoreEsquerda, int alturaArvoreDireita){
	if(alturaArvoreEsquerda > alturaArvoreDireita){
		return alturaArvoreEsquerda;
	}else{
		return alturaArvoreDireita;
	}
}

void arvore::atualizaAltura(noh* umNoh){
	int alturaArvoreEsquerda = informaAltura(umNoh->esquerdo);
	int alturaArvoreDireita = informaAltura(umNoh->direito);
	umNoh->altura = 1 + maiorAltura(alturaArvoreEsquerda, alturaArvoreDireita);
}

int arvore::fatorBalanceamento(noh* umNoh){
	int alturaArvoreEsquerda = informaAltura(umNoh->esquerdo);
	int alturaArvoreDireita = informaAltura(umNoh->direito);
	return alturaArvoreEsquerda - alturaArvoreDireita;
}

void arvore::rotacaoSimplesEsquerda(noh* umNoh){
	noh* nohAuxiliar = umNoh->direito;
	umNoh->direito = nohAuxiliar->esquerdo;
	
}

 

int main(){
	
	int opcao;
	arvore minhaAVL;
	
	do{
		cout << "Qual Operacao deve ser realizada?\n" 
			 <<	"Digite 1 para inserir\n"
			 << "Digite 2 para buscar\n"
			 << "Digite 3 para deletar\n"
			 << "Digite 4 para achar o menor noh\n"
			 << "Digite 5 para achar o maior noh\n";	
	
		cin >> opcao;
	
		if(opcao == 1){
			int inserirValor ; 
			cout << "INSERIR "; cin >> inserirValor;			 
			minhaAVL.inserir(inserirValor);	
			
		}else if(opcao == 2){
			int buscarValor;
			cout << "BUSCAR "; cin >> buscarValor;
			minhaAVL.buscar(buscarValor);
		
		}else if(opcao == 3){
			int removerValor;
			cout << "REMOVER "; cin >> removerValor;
			minhaAVL.remover(removerValor);
			
		}else if(opcao == 4){
			cout << "O menor noh na arvore eh "
				 << minhaAVL.minimo() << endl;
		}else if(opcao == 5){
			cout << "O maior noh na arvore eh "
				 << minhaAVL.maximo() << endl;
		}
		
		cout << endl;
	
	}while(opcao != 0);
}
