#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <unordered_map>

using namespace std;

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

    bool DFS(T nodo_primero, T nodo_segundo){
        stack<Nodo<T>*> visitIn;
        visitIn.push(nodos[nodo_primero]);
        Nodo<T>* temp = visitIn.top();

        while((!visitIn.empty())){
            if(visitIn.top()->id == nodo_segundo){
                return true;
            }

            temp = visitIn.top();
            visitIn.pop();

            for(auto it : temp -> siguiente){
                if(it.first->visitIn == false){
                    visitIn.push(it.first);
                }
            }

            temp->visitIn = true;
        }

        return false;
    }

    bool BFS(T nodo_primero, T nodo_segundo){
        stack<Nodo<T>*> visitIn;
        visitIn.push(nodos[nodo_primero]);
        Nodo<T>* temp = visitIn.front();

        while((!visitIn.empty())){
            if(visitIn.front()->id == nodo_segundo){
                return true;
            }

            temp = visitIn.front();
            visitIn.pop();

            for(auto it : temp -> siguiente){
                if(it.first->visitIn == false){
                    visitIn.push(it.first);
                }
            }

            temp->visitIn = true;
        }

        return false;
    }

};

int main(){
    Grafo<string> g;

    g.agregarNodo("A");
    g.agregarNodo("T");
    g.agregarNodo("Y");
    g.agregarNodo("M");
    g.agregarNodo("D");
    g.agregarNodo("J");
    g.agregarNodo("X");
    g.agregarNodo("E");
    g.agregarNodo("S");
    g.agregarNodo("L");
    g.agregarNodo("K");
    g.agregarNodo("Z");
    g.agregarNodo("N");

    g.agregarArcoDirigidoConPeso("A", "T", 6);
    g.agregarArcoDirigidoConPeso("A", "Y", 5);
    g.agregarArcoDirigidoConPeso("T", "D", 2);
    g.agregarArcoDirigidoConPeso("T", "Y", 7);
    g.agregarArcoDirigidoConPeso("T", "X", 8);
    g.agregarArcoDirigidoConPeso("Y", "M", 9);
    g.agregarArcoDirigidoConPeso("Y", "J", 6);
    g.agregarArcoDirigidoConPeso("M", "J", 3);
    g.agregarArcoDirigidoConPeso("D", "M", 9);
    g.agregarArcoDirigidoConPeso("D", "E", 3);
    g.agregarArcoDirigidoConPeso("E", "J", 5);
    g.agregarArcoDirigidoConPeso("E", "S", 4);
    g.agregarArcoDirigidoConPeso("J", "S", 6);
    g.agregarArcoDirigidoConPeso("X", "L", 6);
    g.agregarArcoDirigidoConPeso("L", "E", 8);
    g.agregarArcoDirigidoConPeso("L", "K", 4);
    g.agregarArcoDirigidoConPeso("K", "Z", 8);
    g.agregarArcoDirigidoConPeso("Z", "S", 9);
    g.agregarArcoDirigidoConPeso("S", "N", 2);

    g.DFS("D", "N");

    g.imprimir();

    return 0;
}