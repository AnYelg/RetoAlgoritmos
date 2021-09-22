#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
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



int main(){
	cargarDatos(); 

	cout << "***************************Pregunta 1***************************" << endl;
	cout << "Número de registros: " << data.size() << endl;
	
	cout << "***************************Pregunta 2***************************" << endl;
	QuickSort <Record> aj;
	aj.Sort(data, compDRF);
	int i = 0;
	while(i < data.size()){
		if(data[i].fecha != data[0].fecha){
			cout << "Información del segundo día, primer usuario: " << endl;
			data[i].imprimirRecord();
			int rec = 0; 
			while(data[i].fecha == data[i+1].fecha){
				rec++;
				i++;
			}
			cout << "Número de records con el segundo día: " << rec << endl;
			break;
		}
		else{
			i++;
		}
		
	}

	cout << "***************************Pregunta 3***************************" << endl;
	
	aj.Sort(data, compDRNF);

	cout << "Si como posición da -1, significa que no existe." << endl;

	int posj = busquedaBinaria<Record, string>(data, "jeffrey.reto.com", compRNF);
	cout<<"La computadora de Jeffrey esta en la posición: "<<posj<<endl;
	if (posj != -1){
		data[posj].imprimirRecord();
	}
	
	int posb = busquedaBinaria<Record, string>(data, "betty.reto.com", compRNF);
	cout<<"La computadora de Betty esta en la posición: "<<posb<<endl;
	if (posb != -1){
		data[posb].imprimirRecord();
	}
	
	int posk = busquedaBinaria<Record, string>(data, "katherine.reto.com", compRNF);
	cout<<"La computadora de Katherine esta en la posición: "<<posk<<endl;
	if (posk != -1){
		data[posk].imprimirRecord();
	}
	
	int poss = busquedaBinaria<Record, string>(data, "scott.reto.com", compRNF);
	cout<<"La computadora de Scott esta en la posición: "<<poss<<endl;
	if (poss != -1){
		data[poss].imprimirRecord();
	}
	
	int posbe = busquedaBinaria<Record, string>(data, "benjamin.reto.com", compRNF);
	cout<<"La computadora de Benjamin esta en la posición: "<<posbe<<endl;
	if (posbe != -1){
		data[posbe].imprimirRecord();
	}

	int possam = busquedaBinaria<Record, string>(data, "samuel.reto.com", compRNF);
	cout<<"La computadora de Samuel esta en la posición: "<<possam<<endl;
	if (possam != -1){
		data[possam].imprimirRecord();
	}

	int posr = busquedaBinaria<Record, string>(data, "raymond.reto.com", compRNF);
	cout<<"La computadora de Raymond esta en la posición: "<<posr<<endl;
	if (posr != -1){
		data[posr].imprimirRecord();
	}

	cout << "***************************Pregunta 4***************************" << endl;
	aj.Sort(data, compDRipF);
	int h = 0;
	while(h < data.size()){
		if(data[h].ipFuente != "-"){
			cout << " La dirección de la red interna de la compañía es: "<< data[h].ipFuente << endl;
			break;
		}
		else{
			h++;
		}
		
	}
	
	cout << "***************************Pregunta 5***************************" << endl;
	
	aj.Sort(data, compDRNF); 
	int posser = busquedaBinaria<Record, string>(data, "server.reto.com", compRNF);
	if (posser == -1){
		cout<<"La computadora server.reto.com no se encuentra "<<endl;	
	}
	else {
		cout << "Si se encuentra la computadora server.reto.com en la posición: "<< posser << endl;
	}

	cout << "***************************Pregunta 6***************************" << endl;
	
	aj.Sort(data, compDRNF);
	cout << "Si como posición da -1, significa que no existe." << endl;

	int gm = busquedaBinaria<Record, string>(data, "gmail.com", compNDF);
	cout << "El correo gmail.com se encuentra en la posición: "<<gm<<endl;

	int ou = busquedaBinaria<Record, string>(data, "outlook.com", compNDF);
	cout << "El correo outlook.com se encuentra en la posición: "<<ou<<endl;

	int prot = busquedaBinaria<Record, string>(data, "protonmail.com", compNDF);
	cout << "El correo protonmail.com se encuentra en la posición: "<<prot<<endl;

	int fre = busquedaBinaria<Record, string>(data, "freemailserver.com", compNDF);
	cout << "El correo freemailserver.com se encuentra en la posición: "<<fre<<endl;

	cout << "***************************Pregunta 7***************************" << endl;
	
	aj.Sort(data, compDRpD);
	
	int num = busquedaBinaria<Record, int>(data, 1000, compPDF);
	cout << "Existen " << num << " usuarios usando puertos abajo del 1000." << endl;
	
	 
	for(int i = num; i< data.size(); i--){
		if (data[i].puertoDestino <= 1000 && data[i+1].puertoDestino != data[i].puertoDestino){
			cout << "Número de Puerto Destino: " << data[i].puertoDestino << endl;	
		}
		
	}
	
}