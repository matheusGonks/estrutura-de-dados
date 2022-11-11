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

class pilha{
	private:
		int tamanho;
		noh* topo;
	
	public:
		pilha();
		~pilha();
		void esvaziarPilha();
		void empilhar(int valor);
		int desempilhar();
		int getTamanho();
};

noh::noh(int valor){
	dado = valor;
	proximo = NULL; 
}

pilha::pilha(){
	tamanho = 0;
	topo = NULL;
}

void pilha::esvaziarPilha(){
	while(tamanho != 0){
		desempilhar();
	}
}

pilha::~pilha(){
	esvaziarPilha();	
}

void pilha::empilhar(int valor){
	noh* novo = new noh(valor);
	novo->proximo = topo;
	topo = novo;
	tamanho++;	
}

int pilha::desempilhar(){
	int valor = topo->dado;
	noh* aux = topo;
	topo = aux->proximo;
	delete aux; tamanho--;
	
	return valor;
}

int pilha::getTamanho(){
	return tamanho;
}

int buscarElemento(int numBuscado, pilha &pilhaPrincipal, pilha &pilhaAux){
	int pos = -1; int x = 1;
	int valorDescartado;
	while(pilhaPrincipal.getTamanho() != 0){
		valorDescartado = pilhaPrincipal.desempilhar(); 
		if(valorDescartado != numBuscado){
			pilhaAux.empilhar(valorDescartado);
			x++;
		}else{
			pos = x;						
		}
	}
	
	return pos;
}

void reempilhaPrincipal(pilha &pilhaPrincipal, pilha &pilhaAux){
	int valorDescartado;
	while(pilhaAux.getTamanho() != 0){
		valorDescartado = pilhaAux.desempilhar();
		pilhaPrincipal.empilhar(valorDescartado);
	}
}

int main()
{
	pilha minhaPilha, pilhaAuxiliar;
	int quantElementos; cin >> quantElementos; 
	while((minhaPilha.getTamanho()) < quantElementos){
		int num; cin >> num;
		minhaPilha.empilhar(num);
	}
	
	int numPesquisado;  
	cin >> numPesquisado; cout << endl;
	
	cout << buscarElemento(numPesquisado, minhaPilha, pilhaAuxiliar) << endl;	
	
	reempilhaPrincipal(minhaPilha, pilhaAuxiliar);
	while(minhaPilha.getTamanho() != 0){
		cout << minhaPilha.desempilhar() << " ";
	}
	
	cout << endl;
}










