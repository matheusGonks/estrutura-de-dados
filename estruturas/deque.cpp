#include <iostream>
using namespace std;

class noh{
	private:
		int dado;
		noh* anterior;
		noh* proximo;
		friend class deque;
	
	public:
		noh(int valor);
			
};

noh::noh(int valor){
	dado = valor;
	anterior = proximo = NULL;
}

class deque{
	private:
		noh* inicio;
		noh* fim;
		int elementosNoDeque;
	
	public:
		deque();
		void inserirInicio(int valor);
		void inserirFim(int valor);
		void inserirDequeVazio(int valor);
		int removerInicio();
		int removerFim();
		bool dequeVazio();	
};

deque::deque(){
	inicio = fim = NULL;
	elementosNoDeque = 0;
}

void deque::inserirDequeVazio(int valor){
	noh* novoNoh = new noh(valor);
	inicio = novoNoh;
	fim = novoNoh;
	elementosNoDeque++;
}

bool deque::dequeVazio(){
	return (elementosNoDeque == 0);
}

void deque::inserirInicio(int valor){
	if(dequeVazio()){
		inserirDequeVazio(valor);
	}else{
		noh* novoNoh = new noh(valor);
		novoNoh->proximo = inicio;
		inicio->anterior = novoNoh;
		inicio = novoNoh;		
		
		elementosNoDeque++;
	}
}

void deque::inserirFim(int valor){
	if(dequeVazio()){
		inserirDequeVazio(valor);
	}else{
		noh* novoNoh = new noh(valor);
		novoNoh->anterior = fim;
		fim->proximo = novoNoh;
		fim = novoNoh;
		
		elementosNoDeque++;
	}
}

int deque::removerInicio(){
	if(dequeVazio()) return -1;
	
	noh* nohAuxiliar = inicio;
	int valorDoNoh = nohAuxiliar->dado;
	inicio = nohAuxiliar->proximo;
	
	if(inicio == NULL){
		fim = NULL;
	}else{
		inicio->anterior = NULL;
	}
	
	delete nohAuxiliar;
	elementosNoDeque--;
	
	return valorDoNoh;
	
}

int deque::removerFim(){
	if(dequeVazio()) return -1;
	
	noh* nohAuxiliar = fim;
	int valorDoNoh = nohAuxiliar->dado;
	fim = fim->anterior;
	
	if(fim == NULL){
		inicio = NULL;
	}else{
		fim->proximo = NULL;
	}
	
	delete nohAuxiliar;
	elementosNoDeque--;	
	
	return valorDoNoh;
}



int main()
{
	deque meuDeque;
	char operacao;
	do{
		cout << "Qual operacao realizar?\n"
		 	 << "1-Enfileirar no fim       2-Enfileirar no inicio\n"
			 << "3-Desenfileirar no inicio 4-Desenfileirar no fim\n"
			 << "5-encerra\n"; 	
		
		cin >> operacao;
		int numero;
		
		if(operacao == '1'){
			cout << "Enfileirar no fim: ";
			cin >> numero;
			meuDeque.inserirFim(numero); cout << endl;
			
		}else if(operacao == '2'){
			cout << "Enfileirar no inicio: ";
			cin >> numero;
			meuDeque.inserirInicio(numero); cout << endl;
			
		}else if(operacao == '3'){
			cout << "O noh " <<  meuDeque.removerInicio() << " foi retirado;\n\n";
		
		}else if(operacao == '4'){
			cout << "O noh " <<  meuDeque.removerFim() << " foi retirado;\n\n";
			
		}
	
	}while(operacao != '5');
	
	return 0;
}
















