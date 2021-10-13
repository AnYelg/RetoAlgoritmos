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
}


class ConexionesComputadora{
    public:
        string IP;
        string Nombre;
    
        ConexionesComputadora(string ip, string n){
            this ->IP = "172.21.65." + ip;
            this ->Nombre;

            stack<string> cnxEntrantes;
            queue<string> cnxSalientes;

            void ConexionesEntrantes(Record r){ //atras para delante
                cnxEntrantes.push(r.ipFuente);
            }
            void ConexionesSalientes(Record r){ //adelante para atras
                cnxSalientes.push(r.ipDestino);
            }
        }

        
        
};

int main(){
    string ipagregado;
    int numeroinp;
    cout << "Ingrese un número entre el 1 y el 150"; cin >> numeroinp; cout<< endl;
    ipagregado = to_string(numeroinp);

    cargarDatos();

    string nombre = "primer nombre";

    ConexionesComputadora concom(ipagregado, nombre);
}