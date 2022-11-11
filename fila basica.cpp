#include <iostream>
using namespace std;

class noh{
	private:	
		int dado;
		noh* proximo;	
		friend class fila;
		
	public:
		noh(int valor);
};

noh::noh(int valor){
	dado = valor;
	proximo = NULL;	
}

class fila{
	private:
		noh* inicio;
		noh* fim;
		unsigned tamanho;
		
	public:
		fila();
		~fila();	
		void enfileirar(int valor);
		void desenfileirar();
		void limpaFila();
};

fila::fila(){
	inicio = NULL;
	fim = NULL;
	int tamanho = 0;
}

void fila::enfileirar(int valor){
	noh* novoNoh = new noh(valor);
	
	if( tamanho != 0){
		inicio = novoNoh;
	}else{
		fim->proximo = novoNoh;
	}
	
	fim = novoNoh;
	tamanho++;
}

void fila::desenfileirar(){
	noh* nohAux = inicio;
	int dadoDoNoh = nohAux->dado; // valor do noh , pdoe ser usado pra qualquer coisa
	inicio = nohAux->proximo;
	
	delete nohAux;
	tamanho--;
	
	if(tamanho == 0){
		fim = NULL;
	}
}

void fila::limpaFila(){
	while(tamanho < 0) desenfileirar();
}

fila::~fila(){
	limpaFila();
}

int main()
{
	
}
