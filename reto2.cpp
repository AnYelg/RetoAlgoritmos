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

        ConexionesComputadora(string ip, string ag, string n){
            this ->IP = ip;
            this ->Nombre = n;
            this ->ipbuscada = ip+ag;
		}
            
		void ConexionesEntrantes(Record r){ //atras para delante
			cnxEntrantes.push(r.ipDestino);
		}
		void ConexionesSalientes(Record r){ //adelante para atras
			cnxSalientes.push(r.ipFuente);
		}
		void tipodeConexionE(){
            if(IP == cnxEntrantes.top().ipDestino.substr(0,10)){
                cout << "La red es interna"<< endl;
            }
			else{
				cout << "La red es externa" << endl;
			}
        }
		void tipodeConexionS(){
            if(IP == cnxSalientes.back().ipFuente.substr(0,10)){
                cout << "La red es interna"<< endl;
            }
			else{
				cout << "La red es externa" << endl;
			}
        }
        
};

int main(){

    int numeroinp;
    cout << "Ingrese un número entre el 1 y el 150: "; cin >> numeroinp; cout<< endl;	
	while (1 > numeroinp || numeroinp > 150){
		cout << "Su número esta fuera del rango, vuelva a insertar: "; cin >> numeroinp;
	}
	string ipagregado = to_string(numeroinp);
	string ipfinal = "172.21.65."+ ipagregado;
	string computadora;
	
	
    cargarDatos();
	
	cout << "***************** Pregunta 1 *****************" << endl;
	cout << "¿Qué dirección ip estas usando?" << endl;
	cout << ipfinal << endl;

	cout << "***************** Pregunta 2 *****************" << endl;
	cout << "¿Cuál fue la ip de la última conexión que recibió esta computadora? ¿Es interna o externa?" << endl;
	//Preguntarle como imprimir solo el ultimo
	ConexionesComputadora cocom("172.21.65.", ipagregado, computadora);
	
	for (int i = 0; i< data.size(); i++){
		if(data[i].ipDestino == cocom.ipbuscada){
			cocom.cnxEntrantes(data[i]);
		}
		else if(data[i].ipFuente == cocom.ipbuscada){
			cocom.cnxSalientes(data[i]);
		}
	}
	
	for (int i = 0; i< data.size(); i++){
		if(data[i].nombreFuente == computadora){
			data[i].imprimiripD();
		}

	}//Respuesta = INTERNA

	cout << "***************** Pregunta 3 *****************" << endl;
	cout << "¿Cuántas conexiones entrantes tiene esta computadora?" << endl;
	
	for(int i = 0; i< data.size(); i++){
		if(data[i].ipFuente == ipfinal){
			cocom.ConexionesEntrantes(data[i]);
		}
	}
	cout << cocom.cnxEntrantes.size()<< endl;

	cout << "***************** Pregunta 4 *****************" << endl;
	cout << "¿Cuántas conexiones salientes tiene esta computadora?" << endl;

	for(int i = 0; i< data.size(); i++){
		if(data[i].ipDestino == ipfinal){
			cocom.ConexionesSalientes(data[i]);
		}
	}
	cout << cocom.cnxSalientes.size()<< endl;

	cout << "***************** Pregunta Extra *****************" << endl;
	cout << "¿Tiene esta computadora 3 conexiones seguidas a un mismo sitio web?" << endl;

	for(int i = 0; i< data.size(); i++){
		if(data[i].puertoDestino == data[i+1].puertoDestino && data[i].puertoDestino == data[i+2].puertoDestino){
			int puertodes = data[i].puertoDestino;
			cout << "Sí sucede con el puerto: " << puertodes << endl;
		}
		
		
	}
	
}