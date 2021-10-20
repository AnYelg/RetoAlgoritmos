#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>

using namespace std;
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

class ConexionesComputadora : public Record{
    public:
        string IP;
        string ipbuscada;
        string Nombre;
		stack<Record> cnxEntrantes;
		queue<Record> cnxSalientes;

        ConexionesComputadora(string ip, string ag, string n){
            this ->IP = ip;
            this ->Nombre = n;
            this ->ipbuscada = ip+ag;
		}
            
		void ConexionesEntrantes(Record r){ //atras para delante
			cnxEntrantes.push(r.ipFuente);
		}
		void ConexionesSalientes(Record r){ //adelante para atras
			cnxSalientes.push(r.ipDestino);
		}
        void tipodeConexionE(){
            if(IP == cnxEntrantes.top().ipFuente.substr(0,10)){
                
            }
        }
        
};


int main(){
    cargarDatos();
    unordered_map<string, ConexionesComputadora> d;

    for (int i = 0; i< data.size(); i++){
		
	}
    
}