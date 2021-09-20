#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
 
//Busqueda kulz 
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
        this -> ipFuente = ipF; //CHECAAAAA
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

int compDRNF(Record r1, Record r2){
	if(r1.nombreFuente < r2.nombreFuente){
		return -1;
	}else if (r1.nombreFuente == r2.nombreFuente){
		return 0;
	}else{
		return 1;
	}
}
/*
template <class T>
class QuickSort: public Sorter<T>{
	public:
	void Sort(vector<T> &data, int comparador(T a, T b)){
		SortAux(data, 0, data.size()-1);
	}
	
	private:
	void SortAux(vector<T> &data, int lo, int hi){
		if(lo>=hi){
			return;
		}
		int posOrdenado=Partition(data, lo, hi);
		SortAux(data, lo, posOrdenado-1);
		SortAux(data, posOrdenado+1, hi);
	}
	
	int Partition(vector<T> &data, int lo, int hi){
		int p=lo;
		int i=lo+1;
		int j=hi;
		while (true){
			while((compDRNF(data[i],data[p]) == -1 or compDRNF(data[i],data[p]) == 0) && i < hi){
				i++;
			}
			while(compDRNF(data[i],data[p]) == 1 &&j>lo){
				j--;
			}
			if(i<j){
				this->Intercambiar(data, i,j);
			}
			else{
				this->Intercambiar(data, p, j);
				break;
			}
		}
		return j;
	}
};*/

template <class T>
class InsertSort: public Sorter<T>{
    public:
        void Sort(vector<T> &data, int comparador(T a, T b)){
            for(int i=1; i < data.size(); i++){
                for(int j=i; j > 0; j--){
                    if(compDRNF(data[j-1], data[j]) == -1){
                        this->Intercambiar(data, j-1, j);  
                    }
					else{
                        break;
                    }
                    
                }
                
            }
            
        }
};


int main(){
	cargarDatos(); 

	int pos = busquedaBinaria<Record, string>(data, "samuel.reto.com", compRNF);
	cout<<"samuel.reto.com se encuentra en la posicion: "<<pos<<endl;
	InsertSort <Record> s;
	s.Sort(data, compDRNF);

	
	//data[0].imprimirRecord();
}