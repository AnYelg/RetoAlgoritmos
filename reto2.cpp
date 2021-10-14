#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;

//Andrea Yela González A01025250
//Joshua Rúben Amaya Camilo A01025258

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
	Record(){

	}

	Record(string ipF,  string nF,string ipD){
        this -> ipFuente = ipF; 
        this -> nombreFuente = nF;
        this -> ipDestino = ipD;	
	}
	
	void imprimirRecord(){
		cout << fecha << "__" << hora << ":" << ipFuente << ":" << puertoFuente << ":" << nombreFuente <<":" << ipDestino << ":" << puertoDestino << ":" << nombreDestino << endl;
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

	Record r2(partes[3], partes[5], partes[6]);
}

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
			while(comparador(data[j], data[p]) == 1 &&j>lo){
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

int compRNF(Record r, string nF){
	if(r.nombreFuente<nF){
		return -1;
	}else if (r.nombreFuente==nF){
		return 0;
	}else{
		return 1;
	}
}


class ConexionesComputadora{
    public:
        string IP;
        string Nombre;
    	stack<string> cnxEntrantes;
        queue<string> cnxSalientes;

        ConexionesComputadora(string ip, string n){
            this ->IP = "172.21.65." + ip;
            this ->Nombre = n;
		}
            
		void ConexionesEntrantes(Record r){ //atras para delante
			cnxEntrantes.push(r.ipFuente);
		}
		void ConexionesSalientes(Record r){ //adelante para atras
			cnxSalientes.push(r.ipDestino);
		}              
        
};

int compDRNF(Record r1, Record r2){
	if(r1.nombreFuente < r2.nombreFuente){
		return -1;
	}else if (r1.nombreFuente == r2.nombreFuente){
		return 0;
	}else{
		return 1;
	}
}

int main(){
    string ipagregado;
    int numeroinp;
	QuickSort <Record> r;
	r.Sort(data, compDRNF);
    cout << "Ingrese un número entre el 1 y el 150: "; cin >> numeroinp; cout<< endl;
    ipagregado = to_string(numeroinp);

    cargarDatos();

    string computadora = "jacob.reto.com";

    ConexionesComputadora concom(ipagregado, computadora);

	
	cout << "***************** Pregunta 1 *****************" << endl;
	cout << "¿Qué dirección ip estas usando?" << endl;
	cout << "172.21.65" << endl;

	cout << "***************** Pregunta 2 *****************" << endl;
	cout << "¿Cuál fue la ip de la última conexión que recibió esta computadora? ¿Es interna o externa?" << endl;
	
	//int posj = busquedaBinaria<Record, string>(data, "william.reto.com", compRNF);
	//data[posj].imprimirRecord();
	
	
	cout << "***************** Pregunta 3 *****************" << endl;
	cout << "¿Cuántas conexiones entrantes tiene esta computadora?" << endl;
	

	cout << "***************** Pregunta 4 *****************" << endl;
	cout << "¿Cuántas conexiones salientes tiene esta computadora?" << endl;

	cout << "***************** Pregunta Extra *****************" << endl;
	cout << "¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?" << endl;
	
}