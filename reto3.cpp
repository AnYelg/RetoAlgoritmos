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
		vector <string> cnxEntrantes;
		vector <string> cnxSalientes;
        vector <string> cnxNombreF;
        vector <string> cnxNombreD;
        ConexionesComputadora(){
		    this->IP="";
            this ->Nombre = "";
	    }
        ConexionesComputadora(string ip){
		    this->IP=ip;
	    }
        ConexionesComputadora(string ip, string n){
            this ->IP = ip;
            this ->Nombre = n;
		}
            
		void ConexionesEntrantes(string r){ //atras para delante
			cnxEntrantes.push_back(r);
		}
		void ConexionesSalientes(string r){ //adelante para atras
			cnxSalientes.push_back(r);
		}
        // void ConexionesNombreF(string r){
        //     cnxNombreF.push_back(r);
        // }
        // void ConexionesNombreD(string r){
        //     cnxNombreD.push_back(r);
        // }
            
    void imprimir(){
		cout<<IP<<":";
		for(string ipDestino: cnxSalientes){
			cout<<ipDestino<<",";
		}
		cout<<endl;
	}
        
};


int main(){
    cargarDatos();
    // unordered_map<string, ConexionesComputadora> d;
    
    // int numeroinp;
    // cout << "Ingrese un número entre el 1 y el 150: "; cin >> numeroinp; cout<< endl;	
	// while (1 > numeroinp || numeroinp > 150){
	// 	cout << "Su número esta fuera del rango, vuelva a insertar: "; cin >> numeroinp;
	// }

	// string ipagregado = to_string(numeroinp);
	// string ipfinal = "172.21.65."+ ipagregado;
	// string computadora;

    // for (int i = 0; i< data.size(); i++){
	// 	if(data[i].ipFuente == ipfinal){
	// 		computadora = data[i].nombreFuente;
	// 		break;
    //     }
	// }
	// ConexionesComputadora concom("172.21.65.", ipagregado, computadora);
    unordered_map<string, ConexionesComputadora> cnx;
    for(Record r:data){
		if(cnx.find(r.ipFuente)==cnx.end()){
			ConexionesComputadora a(r.ipFuente);
			cnx[r.ipFuente]=a;
		}
		cnx[r.ipFuente].ConexionesSalientes(r.ipDestino);

        if(cnx.find(r.ipDestino)==cnx.end()){
			ConexionesComputadora a(r.ipDestino);
			cnx[r.ipDestino]=a;
		}
		cnx[r.ipDestino].ConexionesEntrantes(r.ipFuente);
	}

    for(Record r:data){
		if(cnx.find(r.ipDestino)==cnx.end()){
			ConexionesComputadora a(r.ipDestino);
			cnx[r.ipDestino]=a;
		}
		cnx[r.ipDestino].ConexionesEntrantes(r.ipFuente);
	}

    // for(Record r:data){
	// 	if(cnx.find(r.nombreFuente)==cnx.end()){
	// 		ConexionesComputadora a(r.nombreFuente);
	// 		cnx[r.nombreFuente]=a;
	// 	}
	// 	cnx[r.nombreFuente].ConexionesNombreF(r.ipFuente);
	// }

    // for(Record r:data){
	// 	if(cnx.find(r.nombreDestino)==cnx.end()){
	// 		ConexionesComputadora a(r.nombreDestino);
	// 		cnx[r.nombreDestino]=a;
	// 	}
	// 	cnx[r.nombreDestino].ConexionesNombreD(r.ipDestino);
	// }

	for(auto c:cnx){
		c.second.imprimir();
	}
    
    
}