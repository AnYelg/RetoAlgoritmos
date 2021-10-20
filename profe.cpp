#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

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
	
	Record(string f, string h, string iF, string pF, string nF, string iD, string pD, string nD){
		fecha=f;
		hora=h;
		ipFuente=iF;
		if(pF=="-"){
			puertoFuente=0;
		}else{
			
			try{
				puertoFuente=stoi(pF);
			}catch (const std::invalid_argument& ia){
				puertoFuente=0;
				cout<<"error"<<pD<<endl;
			}
		}
		nombreFuente=nF;
		ipDestino=iD;
		if(pD=="-"){
			puertoDestino=0;
		}else{
			try{
				puertoDestino=stoi(pD);
			}catch (const std::invalid_argument& ia){
				puertoDestino=0;
				cout<<"error"<<pD<<endl;
			}
		}
		nombreDestino=nD;
	}
	
	void imprimirRecord(){
		cout<<nombreFuente<<endl;
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
	string ip;
	vector<string> conexionesSalida;
	
	ConexionesComputadora(){
		this->ip="";
	}
	
	ConexionesComputadora(string ip){
		this->ip=ip;
	}
	
	void agregarSaliente(string ipDestino){
		conexionesSalida.push_back(ipDestino);
	}
	
	void imprimir(){
		cout<<ip<<":";
		for(string ipDestino: conexionesSalida){
			cout<<ipDestino<<",";
		}
		cout<<endl;
	}
};

int main(){
	cargarDatos();
	cout<<"Datos leidos"<<endl;
	unordered_map<string, ConexionesComputadora> cnx;
	for(Record r:data){
		if(cnx.find(r.ipFuente)==cnx.end()){
			ConexionesComputadora a(r.ipFuente);
			cnx[r.ipFuente]=a;
		}
		cnx[r.ipFuente].agregarSaliente(r.ipDestino);
	}
	for(auto c:cnx){
		c.second.imprimir();
	}
}