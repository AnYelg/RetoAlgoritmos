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
	unordered_map<Nodo<T> *, int> siguientes;
	
	Nodo(T id)
	{
		this->id=id;
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

	//int leerSiguiente(T d){

	//}

	
	void agregarNodo(T id)
	{
		Nodo<T> *nuevo=new Nodo<T>(id);
		nodos[id]=nuevo;
	}
	
	void agregarArcoDirigidoConPeso(T fuente, T destino, int peso)
	{
		if(nodos.find(fuente)!=nodos.end() && nodos.find(destino)!=nodos.end())
		{
			nodos[fuente]->agregarArcoConPeso(nodos[destino], peso);
		}
	}
	
	void agregarArcoNoDirigidoConPeso(T fuente, T destino, int peso)
	{
		agregarArcoDirigidoConPeso(fuente, destino, peso);
		agregarArcoDirigidoConPeso(destino, fuente, peso);
	}
	
	void imprimir()
	{
		for(auto it:nodos){
			it.second->imprimirNodo();
		}
	}
	
	
};

int main()
{
	cargarDatos();

	Grafo<string> ConexionesUno;
	int peso=0;
	
	
	
	string dia= "10-8-2020";


	for(auto it : data){
		if(it.fecha == dia){
			if(it.ipDestino.find("172.21.65.") != string::npos){
				ConexionesUno.agregarNodo(it.ipDestino);
			}

			if(it.ipFuente.find("172.21.65.") != string::npos){
				ConexionesUno.agregarNodo(it.ipFuente);
			}

		ConexionesUno.agregarArcoNoDirigidoConPeso(it.ipFuente, it.ipDestino, peso);
		}
	}

	ConexionesUno.imprimir();

}