#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

class Record
{
	public:
		string fecha;
		string hora;
		string ipFuente;
		int puertoFuente;
		string nombreFuente;
		string ipDestino;
		int puertoDestino;
		string nombreDestino;
		
		Record(string f, string h, string ipF, string pF, string nF,string ipD, string pD, string nD)
        {
			this -> fecha = f;
			this -> hora = h;
			this -> ipFuente = ipF; 
			this -> nombreFuente = nF;
			this -> ipDestino = ipD;
			this -> nombreDestino = nD;

			if(pF == "-")
            {
				this -> puertoFuente = 0;
			}
            else
            {
				this -> puertoFuente = stoi(pF);
			}

			if(pD == "-")
            {
				this -> puertoDestino = 0;
			}
            else
            {
				this -> puertoDestino = stoi(pF);
			}

			
		}
		
};

vector<Record> data;
void cargarDatos()
{
	ifstream in;
	in.open("datosEquipo5.csv");
	string line, parte;
	vector<string> partes;
	while(getline(in, line))
    {
		if(line.find("\r")!=line.npos)
        {
				line=line.substr(0, line.size()-1);
		}
		istringstream inString(line);
		while(getline(inString, parte, ','))
        {
			partes.push_back(parte);
		}
		Record r(partes[0], partes[1], partes[2], partes[3], partes[4], partes[5], partes[6], partes[7]);
		data.push_back(r);
		partes.clear();
	}
	in.close();
}

template <class T>
class Nodo{
	public:
	T id;
	bool visitado;
	unordered_map<Nodo<T> *, int> siguientes;
	
	Nodo(T id)
	{
		this->id=id;
		visitado=false;
	}
	
	void agregarArcoConPeso(Nodo<T> *sig, int peso)
	{
		siguientes[sig]=peso;
	}
	
	void imprimirNodo()
	{
		cout<<this->id<<":";
		for(auto it=siguientes.begin(); it!=siguientes.end(); it++)
		{
			cout<<it->first->id<<","<<it->second<<";";
		}
		cout<<endl;
	}
};


template <class T>
class Grafo
{
	unordered_map<T,Nodo<T>*> nodos;
	
	public:

	
	void agregarNodo(T id)
	{
		Nodo<T> *nuevo=new Nodo<T>(id);
		nodos[id]=nuevo;
	}
	
	void agregarArcoDirigidoConPeso(T fuente, T destino){
		int nuevoPeso = calcularNuevoPeso(nodos[fuente], nodos[destino]);

		nodos[fuente]->agregarArcoConPeso(nodos[destino], nuevoPeso);
	}
	
	void imprimir()
	{
		for(auto it:nodos){
			it.second->imprimirNodo();
		}
	}

	int calcularNuevoPeso(Nodo<T> *fuente, Nodo<T> *destino){
		for(auto it = fuente->siguientes.begin(); it != fuente->siguientes.end(); it++){
			if(it->first->id == destino->id){
				int peso = it->second;
				peso++;
				
				return peso;
			}
		}

		return 1;
	}

	void numeroConexiones(T fuente){
		cout << nodos[fuente]->siguientes.size() << endl;
		int cantidad = 0;
		string direccion;

		for(auto it : nodos[fuente]->siguientes){
			if(it.second > cantidad){
				cantidad = it.second;
				direccion = it.first->id;
			}
		}

		cout << "Cantidad de conexiones a " << direccion << "unas " << cantidad << endl;
	}

	void conexion_B(T b){
		int counter = 0;

		for(auto nod : nodos){
			for(auto sig : nodos[nod.first]->siguientes){
				if(sig.first->id == b){
					counter++;
				}
			}
		}

		cout << "Cantidad de conexiones a B: " << counter << endl;
	}

	void conexion_C(T c){
		int counter = 0;

		for(auto nod : nodos){
			for(auto sig : nodos[nod.first]->siguientes){
				if(sig.first->id == c){
					counter++;
				}
			}
		}

		cout << "Cantidad de conexiones a C: " << counter << endl;
	}
};

int main()
{
	cargarDatos();

	string kevin = "172.21.65.54";
	string anomalo = "23.177.199.130";
	string sitio = "170.8.131.248";
	
	//Día a utilizar

	//string dia = "10-8-2020";
	//string dia = "11-8-2020";
	//string dia = "12-8-2020";
	//string dia = "13-8-2020";
	//string dia = "14-8-2020";
	string dia = "17-8-2020";
	//string dia = "18-8-2020";
	//string dia = "19-8-2020";
	//string dia = "20-8-2020";
	//string dia = "21-8-2020";

	Grafo<string> dirInt;

	Grafo<string> dirSitios;
	
	for(int i=0; i<data.size();i++){
    	if((data[i].nombreFuente.substr(data[i].nombreFuente.size() - 8,data[i].nombreFuente.size()) == "reto.com") && 
		(data[i].nombreDestino.size()>8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size() - 8,data[i].nombreDestino.size()) == "reto.com") && 
		(dia == data[i].fecha)){
	  		dirInt.agregarNodo(data[i].ipFuente);
      		dirInt.agregarNodo(data[i].ipDestino);
	  		dirInt.agregarArcoDirigidoConPeso(data[i].ipFuente, data[i].ipDestino);
    	}
    
    	if((data[i].nombreFuente.substr(data[i].nombreFuente.size() - 8,data[i].nombreFuente.size()) == "reto.com") && 
		(data[i].nombreDestino.size() > 8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size() - 8,data[i].nombreDestino.size()) != "reto.com") && 
		(data[i].nombreDestino.size() > 8) && (data[i].nombreDestino.substr(data[i].nombreDestino.size() - 8,data[i].nombreDestino.size()) != "-") &&
		(dia == data[i].fecha)){
		   dirSitios.agregarNodo(data[i].ipFuente);
    	   dirSitios.agregarNodo(data[i].ipDestino);
		   dirSitios.agregarArcoDirigidoConPeso(data[i].ipFuente, data[i].ipDestino);
    	}
    
  }


	

	cout << endl;
	cout << "******************************Cantidad de conexiones internas******************************" << endl;
	dirInt.numeroConexiones(kevin);
	dirInt.imprimir();

	cout << endl;
	cout << "******************************Cantidad de conexiones hacia B******************************" << endl;
	
	dirSitios.conexion_B(anomalo);

	cout << endl;
	cout << "******************************Cantidad de conexiones hacia C******************************" << endl;
	
	dirSitios.conexion_C(sitio);

	cout << endl;

	return 0;
}