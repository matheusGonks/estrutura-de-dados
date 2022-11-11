#include <iostream>
using namespace std;

class noh{
	private:
		friend class fila;
		string placa;
		noh* proximo;
	
	public:
		noh(string placa);	
};

class fila{
	private:
		noh* inicio;
		noh* final;
		unsigned tamanho;
	
	public:
		fila();	
		~fila();
		void enfileira(string placa);
		string desenfileira();
		void limpaFila();
		int tamanhoFila();
};

fila::fila(){
	inicio = NULL;
	final = NULL;
	tamanho = 0;
}

string fila::desenfileira(){
	string plac = inicio->placa;
	noh* temp = inicio;
	inicio = inicio->proximo;
	delete temp; tamanho--;
	
	return plac;
}

fila::~fila(){
	limpaFila();	
}

void fila::limpaFila(){
	while(tamanho > 0){
		desenfileira();
	}
}

void fila::enfileira(string placa){
	noh* novo = new noh(placa);	
	final->proximo = novo;
	final = novo;
	tamanho++; 
}

int fila::tamanhoFila(){
	return tamanho;
}

int buscaCarro(string busca, fila &filaCarros, fila &filaAuxiliar ){
	string carroNaFila; 
	int x = filaCarros.tamanhoFila();
	int carrosMovidos = 0;
	
	while(x > 0){
		carroNaFila = filaCarros.desenfileira();
		if(carroNaFila == busca){
			x = 0;			
		}else{
			filaAuxiliar.enfileira(carroNaFila);
			carrosMovidos++;
		} 
		
	}
	
	if(carrosMovidos = filaCarros.tamanhoFila()){
		return -1;
	}else{
		return carrosMovidos;
	}
}

void restaurarFila(fila &filaCarros, fila &filaAuxiliar){
	string carrosNaFila;
	while( filaAuxiliar.tamanhoFila() > 0 ){
		carrosNaFila = filaAuxiliar.desenfileira();
		filaCarros.enfileira(carrosNaFila);
	}
}

int main(){
	
	fila estacionamento, filaCarrosMovidos;
	char processo;	cin >> processo;
	string placaCarro; int movidos;
	
	while(processo != 'S'){
		if( processo == 'E' ){
			cin >> placaCarro;
			estacionamento.enfileira(placaCarro);
		}
		
		if( processo == 'D'){
			cin >> placaCarro;
			movidos = buscaCarro(placaCarro, estacionamento, filaCarrosMovidos);
			if( movidos = -1){
				cout << "NAO ENCONTRADO";
			}else{
				restaurarFila(estacionamento, filaCarrosMovidos);
			}
		}
		
		cout << endl;
		cin >> processo;		
	}	
}
