#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

//Orden kulz

class Record{
	public:
    string fecha;
    string hora;
    string ipFuente;
    int puertoFuente;
	string nombreFuente;
    string ipDestino;
    int puertoDestino;
	string nombreDestino;
	
	Record(string f, string h, string ipF, string pF, string nF,string ipD, string pD, string nD){
		this -> fecha = f;
        this -> hora = h;
        this -> ipFuente = ipF; 
        this -> nombreFuente = nF;
        this -> ipDestino = ipD;
        this -> nombreDestino = nD;

		if(pF == "-"){
			this -> puertoFuente = 0;
		}else{
			this -> puertoFuente = stoi(pF);
		}

        if(pD == "-"){
			this -> puertoDestino = 0;
		}else{
			this -> puertoDestino = stoi(pF);
		}

		
	}
	
	void imprimirRecord(){
		cout << fecha << "__" << hora << ":" << ipFuente << ":" << puertoFuente << ":" << nombreFuente <<":" << ipDestino << ":" << puertoDestino << ":" << nombreDestino << endl;
	}
};

template <class T>
class Sorter{
	public:
	virtual void Sort(vector<T> &data, int comparador(T a, T b))=0;
	
	void Imprimir(vector<T> &data){
		for(int i=0; i<data.size(); i++){
			cout<<data[i]<<",";
		}
		cout<<endl;
	}
	
	void Intercambiar(vector<T> &data, int posI, int posJ){
		T temp=data[posI];
		data[posI]=data[posJ];
		data[posJ]=temp;
	}
};

vector<Record> data;
void cargarDatos(){
	ifstream in;
	in.open("datosEquipo5.csv");
	string line, parte;
	vector<string> partes;
	while(getline(in, line)){
		if(line.find("\r")!=line.npos){
				line=line.substr(0, line.size()-1);
		}
		istringstream inString(line);
		while(getline(inString, parte, ',')){
			partes.push_back(parte);
		}
		Record r(partes[0], partes[1], partes[2], partes[3], partes[4], partes[5], partes[6], partes[7]);
		data.push_back(r);
		partes.clear();
	}
	in.close();
}

int compRF(Record r, string f){
	if(r.fecha < f){
		return -1;
	}
	else if (r.fecha == f){
		return 0;
	}
	else {
		return 1;
	}
}

int compRipF(Record r, string ipF){
	if(r.ipFuente < ipF){
		return -1;
	}
	else if (r.ipFuente == ipF){
		return 0;
	}
	else {
		return 1;
	}
}

int compRpF(Record r, int pF){
	if (r.puertoFuente < pF){
		return -1;
	}
	else if (r.puertoFuente == pF){
		return 0;
	}
	else {
		return 1;
	}
}

int compRNF(Record r, string nF){
	if(r.nombreFuente<nF){
		return -1;
	}else if (r.nombreFuente==nF){
		return 0;
	}else{
		return 1;
	}
}

int compIpDF(Record r, string ipD){
	if(r.ipDestino < ipD){
		return -1;	
	}
	else if (r.ipDestino == ipD){
		return 0;
	}else{
		return 1;
	}
}

int compPDF(Record r, int pD){
	if(r.puertoDestino < pD){
		return -1;
	}

	else if( r.puertoDestino == pD){
		return 0;
	}

	else{
		return 1;
	}
}

int compNDF(Record r, string nD){
	if(r.nombreDestino < nD){
		return -1;
	}

	else if( r.nombreDestino == nD){
		return 0;
	}

	else{
		return 1;
	}
}

template <class T, class B>
int busquedaBinaria (vector<T> a, B buscado, int comparador(T a, B b)){
    int inicio = 0;
    int fin = a.size()-1;
    while (inicio <=fin){
        int medio = (fin+inicio)/2;
        if(comparador(a[medio],buscado) == 0){
            return medio;
        }
		else if (comparador(a[medio], buscado) == -1){ 
            inicio = medio + 1;
        }
        else{
            fin = medio-1;
        }
    }
    return -1;
}

int compDRF(Record r1, Record r2){
	if(r1.fecha < r2.fecha){
		return -1;
	}else if (r1.fecha == r2.fecha){
		return 0;
	}else{
		return 1;
	}
}

int compDRipF(Record r1, Record r2){
	if(r1.ipFuente < r2.ipFuente){
		return -1;
	}else if (r1.ipFuente == r2.ipFuente){
		return 0;
	}else{
		return 1;
	}
}

int compDRpF(Record r1, Record r2){
	if(r1.puertoFuente < r2.puertoFuente){
		return -1;
	}else if (r1.puertoFuente == r2.puertoFuente){
		return 0;
	}else{
		return 1;
	}
}

int compDRNF(Record r1, Record r2){
	if(r1.nombreFuente < r2.nombreFuente){
		return -1;
	}else if (r1.nombreFuente == r2.nombreFuente){
		return 0;
	}else{
		return 1;
	}
}

int compDRipD(Record r1, Record r2){
	if(r1.ipDestino < r2.ipDestino){
		return -1;
	}

	else if(r1.ipDestino == r2.ipDestino){
		return 0;
	}

	else{
		return 1;
	}
}

int compDRnD(Record r1, Record r2){
	if(r1.nombreDestino < r2.nombreDestino){
		return -1;
	}

	else if(r1.nombreDestino == r2.nombreDestino){
		return 0;
	}

	else{
		return 1;
	}
}

int compDRpD(Record r1, Record r2){
	if(r1.puertoDestino < r2.puertoDestino){
		return -1;
	}

	else if(r1.puertoDestino == r2.puertoDestino){
		return 0;
	}

	else{
		return 1;
	}
}

template <class T>
class QuickSort: public Sorter<T>{
	public:
	void Sort(vector<T> &data, int comparador(T a, T b)){

		SortAux(data, 0, data.size()-1, comparador);
	}
	
	private:
	void SortAux(vector<T> &data, int lo, int hi, int comparador(T a, T b)){
		if(lo>=hi){
			return;
		}
		int posOrdenado=Partition(data, lo, hi, comparador);
		SortAux(data, lo, posOrdenado-1, comparador);
		SortAux(data, posOrdenado+1, hi, comparador);
	}
	
	int Partition(vector<T> &data, int lo, int hi, int comparador(T a, T b)){
		int p=lo;
		int i=lo+1;
		int j=hi;
		while (true){
			while(comparador(data[i], data[p]) < 1 &&i<hi){
				i++;
			}
			while(comparador(data[j], data[p]) == -1 &&j>lo){
				j--;
			}
			if(i<j){
				this->Intercambiar(data, i,j);
			}else{
				this->Intercambiar(data, p, j);
				break;
			}
		}
		return j;
	}
};



int main(){
	cargarDatos(); 

	//Pregunta 1
	cout << "Número de registros: " << data.size() << endl;
	//Pregunta 2
	QuickSort <Record> s;
	s.Sort(data, compDRF);

	for(int i = 0; i < 20; i++){
		data[i].imprimirRecord();
	}

	//Pregunta 3
	QuickSort <Record> s;
	s.Sort(data, compDRNF);

	int pos = busquedaBinaria<Record, string>(data, "jeffrey.reto.com", compRNF);
	cout<<"La computadora de Jeffrey esta en la posición: "<<pos<<endl;
	
	int pos = busquedaBinaria<Record, string>(data, "betty.reto.com", compRNF);
	cout<<"La computadora de Betty esta en la posición: "<<pos<<endl;

	int pos = busquedaBinaria<Record, string>(data, "katherine.reto.com", compRNF);
	cout<<"La computadora de Katherine esta en la posición: "<<pos<<endl;

	int pos = busquedaBinaria<Record, string>(data, "scott.reto.com", compRNF);
	cout<<"La computadora de Scott esta en la posición: "<<pos<<endl;

	int pos = busquedaBinaria<Record, string>(data, "benjamin.reto.com", compRNF);
	cout<<"La computadora de Benjamin esta en la posición: "<<pos<<endl;

	int pos = busquedaBinaria<Record, string>(data, "samuel.reto.com", compRNF);
	cout<<"La computadora de Samuel esta en la posición: "<<pos<<endl;

	int pos = busquedaBinaria<Record, string>(data, "raymond.reto.com", compRNF);
	cout<<"La computadora de Raymond esta en la posición: "<<pos<<endl;
	
	//Pregunta 4
	QuickSort <Record> s;
	s.Sort(data, compDRNF);

	for(int i = 0; i < 20; i++){
		data[i].imprimirRecord();
	}
	
	//Pregunta 5
	QuickSort <Record> s;
	s.Sort(data, compDRNF); 
	int pos = busquedaBinaria<Record, string>(data, "server.reto.com", compRNF);
	cout<<"La computadora server.reto.com esta en la posición: "<<pos<<endl;

	//Pregunta 6
	QuickSort <Record> s;
	s.Sort(data, compDRNF);

	int num = busquedaBinaria<Record, string>(data, "gmail.com", compNDF);
	cout << "El correo gmail.com se encuentra en la posición: "<<num<<endl;

	int num = busquedaBinaria<Record, string>(data, "outlook.com", compNDF);
	cout << "El correo outlook.com se encuentra en la posición: "<<num<<endl;

	int num = busquedaBinaria<Record, string>(data, "protonmail.com", compNDF);
	cout << "El correo protonmail.com se encuentra en la posición: "<<num<<endl;

	int num = busquedaBinaria<Record, string>(data, "freemailserver.com", compNDF);
	cout << "El correo freemailserver.com se encuentra en la posición: "<<num<<endl;

	//Pregunta 7
	QuickSort <Record> s;
	s.Sort(data, compDRpD);
	
	int num = busquedaBinaria<Record, int>(data, 1000, compPDF);
	cout << "Hay: " << data.size()-num << "puertos abajo del 1000 que  se están usando" << endl;
	
	
	
	
	
	
	//data[0].imprimirRecord();
}