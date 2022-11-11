/* 
 * TAD conjunto
 */

#include <iostream>
#include <cmath>

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
		int getTamanho();
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

int deque::getTamanho(){
	return elementosNoDeque;
}

class conjunto {
    private:
    	deque elementosConjunto;

    public: 
        // sugestão de métodos públicos para sua classe conjunto
        void insere(int elemento);
        void remove(int elemento);
        bool membro(int elemento);

        void uniao(conjunto& C1, conjunto& C2);
        void intersecao(conjunto& C1, conjunto& C2);    
        void diferenca(conjunto& C1, conjunto& C2);
        
        unsigned tamanho();

        void imprime();
        void depura();     
};

// função que retorna uma posição no vetor para um dado caracter maiúsculo
inline unsigned char2pos(char c) {
    return unsigned(c)- 65;
}

void conjunto::insere(int elemento){
	if(membro(elemento) == false)elementosConjunto.inserirFim(elemento);
}

void conjunto::remove(int elemento){
	int repeticao = elementosConjunto.getTamanho();
	int valorDoNoh;
	
	for(int i = ; i < repeticao; i++){
		valorDoNoh = elementosConjunto.removerFim();
		if(valorDoNoh != elemento) elementosConjunto.inserirInicio(valorDoNoh);	
	}
}

bool conjunto::membro(int elemento){
	int repeticao = elementosConjunto.getTamanho();
	int valorDoNoh; 
	bool fazParte = false;
	
	for(int i = ; i < repeticao; i++){
		valorDoNoh = elementosConjunto.removerFim();
		if(valorDoNoh == elemento) fazParte = true;
		elementosConjunto.inserirInicio(valorDoNoh);	
	}
	
	return fazParte;
}


// *** não altere a função principal sem antes consultar os professores ***
int main( ) {
    conjunto meusConjuntos[26];
    char operacao;
    // conjuntos são representados por letras maiúsculas
    char conjunto1, conjunto2, conjunto3;
    int elemento;
    unsigned pos1, pos2, pos3;

    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // inserir
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].insere(elemento);
                break;
            case 'r': // remover
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].remove(elemento);
                break;
            case 'm': // checa pertinência
                cin >> conjunto1 >> elemento;
                pos1 = char2pos(conjunto1);
                cout << meusConjuntos[pos1].membro(elemento) << endl;
                break;
            case '+': // efetua união
                // conjunto1 terá o resultado da união de conjunto2 com conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].uniao(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case '*': // efetua interseção
                // conjunto1 terá o resultado da interseção de conjunto2 com conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].intersecao(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case '-': // efetua diferença
                // conjunto1 terá o resultado da diferença de conjunto2 para o conjunto3
                cin >> conjunto1 >> conjunto2 >> conjunto3;
                pos1 = char2pos(conjunto1);
                pos2 = char2pos(conjunto2);
                pos3 = char2pos(conjunto3);
                meusConjuntos[pos1].diferenca(meusConjuntos[pos2],meusConjuntos[pos3]);
                break;
            case 't': // tamanho
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                cout << meusConjuntos[pos1].tamanho() << endl;
                break;
            case 'd': // mostrar estrutura
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].depura();
                break;
            case 'p': // imprimir dados
                cin >> conjunto1;
                pos1 = char2pos(conjunto1);
                meusConjuntos[pos1].imprime();
                break;
            case 's': // sair
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } while (operacao != 's');

    return 0; 
}
