#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
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

}