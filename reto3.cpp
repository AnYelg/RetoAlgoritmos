#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <vector>
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
        void ConexionesNombreF(string r){
            cnxNombreF.push_back(r);
        }
        void ConexionesNombreD(string r){
            cnxNombreD.push_back(r);
        }

            
        void imprimirDestino(){
            cout<<IP<<":";
            for(string ipDestino: cnxSalientes){
                cout<<ipDestino<<",";
            }
            cout<<endl;
        }

        void imprimirFuente(){
            cout<<IP<<":";
            for(string ipFuente: cnxEntrantes){
                cout<<ipFuente<<",";
            }
            cout<<endl;
        }

        
};


int main(){
    cargarDatos();
   
    unordered_map<string, ConexionesComputadora> cnx; //Creación del diccionario

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

        if(cnx.find(r.nombreFuente)==cnx.end()){
			ConexionesComputadora a(r.nombreFuente);
			cnx[r.nombreFuente]=a;
		}
		cnx[r.nombreFuente].ConexionesNombreF(r.ipFuente);
        
        if(cnx.find(r.nombreDestino)==cnx.end()){
			ConexionesComputadora a(r.nombreDestino);
			cnx[r.nombreDestino]=a;
		}
		cnx[r.nombreDestino].ConexionesNombreD(r.ipDestino);
    
	}

    unordered_set<string> anomalo;
    unordered_set<string> preg2;
    unordered_set<string> preg3;
    unordered_set<string> preg4;
    unordered_set<string> preg6;
    unordered_set<string> preg7;
	unordered_set<int> preg71;

    for(int i = 0; i< data.size(); i++){
        if(data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size()) != "reto.com" || data[i].ipFuente.substr(0,10) != "172.21.65." || data[i].nombreDestino != "-"){
            anomalo.insert(data[i].nombreDestino);
        }

        if(data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size()) != "reto.com" || data[i].ipFuente.substr(0,10) != "172.21.65." || data[i].nombreDestino != "-"){
            preg2.insert(data[i].ipDestino);
        }

        if(data[i].ipDestino.substr(0,10) == "172.21.65."){
            preg3.insert(data[i].nombreDestino);
        }

        if(data[i].ipFuente == "172.21.65.35"){
            preg4.insert(data[i].ipDestino);
        }

        if((data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size()) != "reto.com" || data[i].ipDestino.substr(0,10) != "172.21.65." || data[i].nombreDestino != "-") && (data[i].ipFuente == "172.21.65.35")){
            preg6.insert(data[i].nombreDestino);
        }

        if((data[i].nombreFuente.substr(data[i].nombreFuente.size()-8,data[i].nombreFuente.size()) != "reto.com" || data[i].ipDestino.substr(0,10) != "172.21.65." || data[i].nombreDestino != "-") && (data[i].ipFuente == "172.21.65.35")){
            preg7.insert(data[i].fecha);
			preg71.insert(data[i].puertoFuente);
        }

    }
    cout << "***************** Pregunta 1 *****************" << endl;
    cout << "Sí, hay: " << anomalo.size() << endl;

    for (string it: anomalo){ //Pregunta 1
        cout << it << endl;
    }

    cout << "***************** Pregunta 2 *****************" << endl;
    for(auto it: preg2){
        cout << it << endl;
    }

    cout << "***************** Pregunta 3 *****************" << endl;
    cout << preg3.size() << endl;

    cout << "***************** Pregunta 4 *****************" << endl;
    for (auto it: preg4){ //Pregunta 1
        cout << it << endl;
    }
    cout << "***************** Pregunta 6 *****************" << endl;
    cout << preg6.size() << endl;

    cout << "***************** Pregunta 7 *****************" << endl;
    for (auto it: preg7){
        cout << it << endl;
        break;
    }
	for (auto it: preg71){
        cout << it << endl;
        break;
    }
    
}