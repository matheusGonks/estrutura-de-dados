//ESSE CARALHO NÃO FUNCIONA
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef int dado;

class Maxheap{
	private:
		dado* heap;
		int capacidade;
		int tamanho;
		inline int pai(int i);
		inline int esquerdo(int i);
		inline int direito(int i);
		void arruma(); // heapify
		void corrigeDescendo(int i);
		void corrigeSubindo(int i);
		
	public:
		Maxheap(int cap);
		Maxheap(dado vet[], int tam);
		~Maxheap();
		dado espiaRaiz();
		dado retiraRaiz();
		void insere(dado d);	
};

Maxheap::Maxheap(int cap){
	capacidade = cap;
	heap = new dado[cap];
	tamanho = 0;
}

Maxheap::Maxheap(dado vet[], int tam){
	capacidade = tam;
	
	heap = new dado[capacidade];
	
	
	memcpy(heap, vet, tam * sizeof(dado));
	/*for(int i = 0; i < tam; i++){ //possivel substituir mor memcpy da livraria cstring memcpy(heap, vet, tam * sizeof(dado))
		heap[i] = vet[i];
	}*/
	
	tamanho = tam;
	arruma();
}

Maxheap::~Maxheap(){
	delete[] heap;	
} 

void Maxheap::arruma() {
	for(int i = (tamanho/2 - 1); i >= 0; i--){ //heap começa em 0
		corrigeDescendo(i);
	}
}

int Maxheap::pai(int i){
	return (i - 1) / 2;
}

int Maxheap::direito(int i){
	return 2 * i + 2;
}

int Maxheap::esquerdo(int i){
	return 2 * i + 1;
}

void Maxheap::corrigeDescendo(int i ){
	int esq = esquerdo(i);
	int dir = direito(i);
	int maior = i;
	
	if((esq < tamanho) and (heap[esq] > heap[maior])){
		maior = esq;
	}	
	
	if((dir < tamanho) and (heap[dir] > heap[i])){
		maior = dir;
	}
	
	if(maior != i){
		swap(heap[i], heap[maior]);
		corrigeDescendo(maior);
	}
}

void Maxheap::corrigeSubindo(int i){
	int p = pai(i);
	if(heap[i] > heap[p]){
		swap(heap[i], heap[p]);
		corrigeSubindo(p);
	}
}

dado Maxheap::espiaRaiz(){
	return heap[0];
}

dado Maxheap::retiraRaiz(){
	if(tamanho == 0){
		cout << "Erro ao retirar raíz\n";
		//exit(EXIT_FAILURE) codigo do uchoa
	}
	
	dado aux = heap[0];
	swap(heap[0], heap[tamanho - 1]);
	tamanho--;
	corrigeDescendo(0);
	return aux;
}

void Maxheap::insere(dado d){
	if (tamanho == capacidade ){
		cout << "Erro ao retirar raíz\n";
		//exit(EXIT_FAILURE) codigo do uchoa
	}
	heap[tamanho] = d;
	corrigeSubindo(tamanho);
	tamanho++;
}

int main()
{
	int tam = 5;
	dado vet[] = {25, 2, 64, 41, 15};
	
	Maxheap *h = new Maxheap(vet, tam);
	
	for(int i = 0; i < tam; i++){
		cout << h->retiraRaiz() << " ";
	}
	cout << endl;
	
	for(int i = 0; i < tam; i++){
		h->insere(vet[i]);
	}
	cout << endl;
	
	for(int i = 0; i < tam; i++){
		cout << h->retiraRaiz() << " ";
	}
	cout << endl;
	
	delete h;
	return 0;
}
