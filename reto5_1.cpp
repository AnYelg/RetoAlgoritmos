#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <unordered_map>
#include <queue>
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

    bool DFS(T nodo1, T nodo2){
        stack<Nodo<T>*> visitar;
        visitar.push(nodos[nodo1]);
        Nodo<T>* temp = visitar.top();

        while(!visitar.empty()){
            if(visitar.top()->id == nodo2){
                return true;
            }

            temp = visitar.top();
            visitar.pop();

            for(auto it : temp->siguientes){
                if(it.first->visitado == false){
                    visitar.push(it.first);
                }
            }

            temp->visitado = true;
        }

        return false;
    }

    bool BFS(T nodo_primero, T nodo_segundo){
        queue<Nodo<T>*> visitar;
        visitar.push(nodos[nodo_primero]);
        Nodo<T>* temp = visitar.front();

        while(!visitar.empty()){
            if(visitar.front()->id == nodo_segundo){
                return true;
            }

            temp = visitar.front();
            visitar.pop();

            for(auto it : temp -> siguientes){
                if(it.first->visitado == false){
                    visitar.push(it.first);
                }
            }

            temp->visitado = true;
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

    bool solucion = g.DFS("A", "J");
    if(solucion == true){
        cout << "Existe solución" << endl;
    }
    else{
        cout << "No existe solución" << endl;
    }


    bool solucion2 = g.BFS("A", "J");
    if(solucion2 == true){
        cout << "Existe solución" << endl;
    }

    else{
        cout << "No existe solución" << endl;
    }

    return 0;
}