#include <iostream>

using namespace std; 

class noh{
	private:
		int dado;
		noh* proximo;
		friend class pilha;

	public:
		noh(int valor);	
		
};

noh::noh(int valor){
	dado = valor;
	proximo = NULL;
}

class pilha{
	private:
		noh* topo;
		int tamanho;
	
	public:
		pilha();	
		~pilha();
		void criarNoh(int valor);
		void destruirNoh();
		void esvaziarPilha();
		
};

pilha::pilha(){
	topo = NULL;
	tamanho = 0;
}

void pilha::criarNoh(int valor){
	noh* novoNoh = new noh(valor);
	novoNoh->proximo = topo;
	topo = novoNoh;
	tamanho++;
}

void pilha::destruirNoh(){
	int dadoDoNoh; //utiliza o dado do noh removido pra qualquer coisa
	noh* nohAux = topo;
	dadoDoNoh = nohAux->dado;
	topo = nohAux->proximo;
	delete nohAux;
	
	tamanho--;	
}

void pilha::esvaziarPilha(){
	while(tamanho < 0) destruirNoh();
}

pilha::~pilha(){
	esvaziarPilha();
}

int main()
{
	
}










