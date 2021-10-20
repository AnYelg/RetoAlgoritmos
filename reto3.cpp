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
		void imprimiripD(){
			cout << ipDestino << endl;
		}
		void imprimirpD(){
			cout << puertoDestino << endl;
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
        string Nombre;
		string ipbuscada;
		stack<Record> cnxEntrantes;
		queue<Record> cnxSalientes;
        vector <string> cnxNombres;

        ConexionesComputadora(string ip){
		    this->ipbuscada = ip;
	    }

        ConexionesComputadora(string ip, string ag, string n){
            this ->IP = ip;
            this ->Nombre = n;
            this ->ipbuscada = ip+ag;
		}
            
		void ConexionesEntrantes(Record r){ //atras para delante
			cnxEntrantes.push(r);
		}
		void ConexionesSalientes(Record r){ //adelante para atras
			cnxSalientes.push(r);
		}
        void ConexionesNombre(string ipDestino){
            cnxNombres.push_back(ipDestino);
        }
            
		void tipodeConexion(){
            if(IP == cnxSalientes.back().ipFuente.substr(0,10)){
                cout << "La red es interna"<< endl;
            }
			else{
				cout << "La red es externa" << endl;
			}
        }
        void imprimir(){
		    cout<<ipbuscada<<":";
		for(string ipDestino: cnxNombres){
			cout<<ipDestino<<",";
		}
		cout<<endl;
	}

        // void meterdiccionario(){
        //     if(Nombre == cnxNombres )
        // }

        
};


int main(){
    cargarDatos();
    unordered_map<string, ConexionesComputadora> d;
    
    int numeroinp;
    cout << "Ingrese un número entre el 1 y el 150: "; cin >> numeroinp; cout<< endl;	
	while (1 > numeroinp || numeroinp > 150){
		cout << "Su número esta fuera del rango, vuelva a insertar: "; cin >> numeroinp;
	}

	string ipagregado = to_string(numeroinp);
	string ipfinal = "172.21.65."+ ipagregado;
	string computadora;

    for (int i = 0; i< data.size(); i++){
		if(data[i].ipFuente == ipfinal){
			computadora = data[i].nombreFuente;
			break;
	}
	ConexionesComputadora concom("172.21.65.", ipagregado, computadora);
    d.insert({"hola", concom});

    for(Record r:data){
		if(d.find(r.ipFuente)== d.end()){
			ConexionesComputadora a(r.ipFuente);
			d[r.ipFuente]=a;
		}
		d[r.ipFuente].ConexionesNombre(r.ipDestino);
	}
	for(auto c:d){
		c.second.imprimir();
	}
    
}