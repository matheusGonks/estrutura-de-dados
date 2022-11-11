/* 
 * TAD conjunto
 */

#include <iostream>
#include <cmath>

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
		friend class conjunto;
	
	public:
		pilha();	
		~pilha();
		void criarNoh(int valor);
		int desempilha(); //funcao de desempilha permite tambem "ver" qual o noh 
		void esvaziarPilha();
		int getTamanho();
		
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

int pilha::desempilha(){
	int valor = topo->dado;
	noh* aux = topo;
	topo = aux->proximo;
	delete aux; tamanho--;
	
	return valor;
}

void pilha::esvaziarPilha(){
	while(tamanho < 0) desempilha();
}

int pilha::getTamanho(){
	return tamanho;
}

pilha::~pilha(){
	esvaziarPilha();
}

class conjunto {
    private:
		pilha elementosConjunto;


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
	elementosConjunto.criarNoh(elemento); 
}

void conjunto::remove(int elemento){ //metodo de desempilhar permite "ver" se o elemento da pilha eh o elemento que deve ser removido
	pilha pilhaAuxiliar;
	int valoresDaPilha;
	while(elementosConjunto.getTamanho() > 0){
		valoresDaPilha = elementosConjunto.desempilha();
		if(valoresDaPilha != elemento ) pilhaAuxiliar.criarNoh(valoresDaPilha);
	}
	
	//a pilha auxiliar eh agora a pilha principal ( de cabeça pra baixo ) sem o elemento a ser removido
	//resta agora desempilhar ela "direto" na pilha elementosConjunto
	
	while(pilhaAuxiliar.getTamanho() > 0 ){
		elementosConjunto.criarNoh(pilhaAuxiliar.desempilha());
	}
}

bool conjunto::membro(int elemento){
	pilha pilhaAuxiliar; 
	bool fazParte = false;
	int valoresDaPilha;
	
	while(elementosConjunto.getTamanho() > 0){
		valoresDaPilha = elementosConjunto.desempilha();
		if(valoresDaPilha == elemento){
			fazParte = true;
		}
		
		pilhaAuxiliar.criarNoh(valoresDaPilha);
	}
	
	while(pilhaAuxiliar.getTamanho() > 0){
		elementosConjunto.criarNoh(pilhaAuxiliar.desempilha());
	}
	
	return fazParte;
}

unsigned conjunto::tamanho(){
	return elementosConjunto.getTamanho();
}

void conjunto::uniao(conjunto& C1, conjunto& C2){
	pilha pilhaAux1, pilhaAux2;
	
	int i = 0; int tam = C1.tamanho();
	int* vetor = new int[tam];
	
	while(C1.tamanho() > 0){
		
		int valores = C1.elementosConjunto.desempilha();
		
		elementosConjunto.criarNoh(valores);	
		pilhaAux1.criarNoh(valores);
		vetor[i] = valores;
		
		i++;
	}
	
	while(C2.tamanho() > 0){
		
		int valores = C2.elementosConjunto.desempilha();
		int comparacao = 0;
		
		for(i = 0; i < tam; i++ ){
			if(valores == vetor[i]) comparacao++; 
		}
		
		if(comparacao == 0) elementosConjunto.criarNoh(valores);
		pilhaAux2.criarNoh(valores); 
	}
	
	while(pilhaAux1.getTamanho() > 0){
		C1.elementosConjunto.criarNoh(pilhaAux1.desempilha());
	}
	while(pilhaAux2.getTamanho() > 0){
		C2.elementosConjunto.criarNoh(pilhaAux2.desempilha());	
	}
	
	delete vetor;
	 
}

void conjunto::intersecao(conjunto& C1, conjunto& C2){
	pilha pilhaAux1, pilhaAux2;
	
	int i = 0; int tam = C1.tamanho();
	int* vetor = new int[tam];
	
	while(C1.tamanho() > 0){
		
		int valores = C1.elementosConjunto.desempilha();
		
		pilhaAux1.criarNoh(valores);
		vetor[i] = valores;
		
		i++;
	}
	
	while(C2.tamanho() > 0){
		
		int valores = C2.elementosConjunto.desempilha();
		int comparacao = 0;
		
		for(i = 0; i < tam; i++ ){
			if(valores == vetor[i]) comparacao++; 
		}
		
		if(comparacao != 0) elementosConjunto.criarNoh(valores);
		pilhaAux2.criarNoh(valores); 
	}
	
	while(pilhaAux1.getTamanho() > 0){
		C1.elementosConjunto.criarNoh(pilhaAux1.desempilha());
	}
	while(pilhaAux2.getTamanho() > 0){
		C2.elementosConjunto.criarNoh(pilhaAux2.desempilha());
	}
	
	delete vetor;
	
}

void conjunto::diferenca(conjunto& C1, conjunto& C2){
	pilha pilhaAux1, pilhaAux2;
	
	int i = 0; int tam = C2.tamanho();
	int* vetor = new int[tam];	
	
	while(C2.tamanho() > 0){
		
		int valores = C2.elementosConjunto.desempilha();	
		pilhaAux2.criarNoh(valores);
		vetor[i] = valores;
		
		i++;
	}
	
	while(C1.tamanho() > 0){
		
		int valores = C1.elementosConjunto.desempilha();
		int comparacao = 0;
		
		for(i = 0; i < tam; i++ ){
			if(valores == vetor[i]) comparacao++; 
		}
		
		if(comparacao == 0) elementosConjunto.criarNoh(valores);
		pilhaAux1.criarNoh(valores); 
	}
	
	while(pilhaAux1.getTamanho() > 0){
		C1.elementosConjunto.criarNoh(pilhaAux1.desempilha());
	}
	while(pilhaAux2.getTamanho() > 0){
		C2.elementosConjunto.criarNoh(pilhaAux2.desempilha());
	}
	
	delete vetor;
}

void conjunto::imprime(){
	pilha aux;
	while(elementosConjunto.getTamanho() > 0){
		int elemento = elementosConjunto.desempilha(); 
		cout << elemento  << " ";	
		aux.criarNoh(elemento);	
	}
	cout << endl;
	
	while(aux.getTamanho() > 0){
		elementosConjunto.criarNoh(aux.desempilha());
	}
	
}

void conjunto::depura(){
	pilha aux;
	cout << endl;
	cout << "TOPO\n";
	while(elementosConjunto.getTamanho() > 0){
		int elemento = elementosConjunto.desempilha(); 
		cout << elemento  << "\n";	
		aux.criarNoh(elemento);	
	}
	
	cout << endl;
	
	while(aux.getTamanho() > 0){
		elementosConjunto.criarNoh(aux.desempilha());
	}
	
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
