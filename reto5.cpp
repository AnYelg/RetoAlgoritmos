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
	unordered_map<string, unordered_map<string, int>> conexInt;

	Grafo<string> ConexionesDos;
	unordered_map<string, unordered_map<string, int>> conexSit;
	
	int peso=0;
	
	//Día a utilizar

	//string dia = "10-8-2020";
	//tring dia = "11-8-2020";
	//string dia = "12-8-2020";
	//string dia = "13-8-2020";
	//string dia = "14-8-2020";
	//string dia = "17-8-2020";
	//string dia = "18-8-2020";
	//string dia = "19-8-2020";
	//string dia = "20-8-2020";
	string dia = "21-8-2020";

	//Grafo de conexiones de red interna
	for(auto it : data){
		if(it.fecha == dia){
			if(it.ipDestino.find("172.21.65.") != string::npos){
				ConexionesUno.agregarNodo(it.ipDestino);
				//Generar la matriz
				conexInt[it.ipFuente][it.ipDestino] +=1;
			}

			if(it.ipFuente.find("172.21.65.") != string::npos){
				ConexionesUno.agregarNodo(it.ipFuente);
			}

		ConexionesUno.agregarArcoNoDirigidoConPeso(it.ipFuente, it.ipDestino, peso);
		}
	}

	for(auto it : conexInt){
		for(auto numConexiones : it.second){
			ConexionesUno.agregarArcoDirigidoConPeso(it.first, numConexiones.first, numConexiones.second);
		}
	}


	//Grafo de conexiones de sitios web
	for(auto elem : data){
		if(elem.fecha == dia){
			if(!elem.ipDestino.find("172.21.65.") != string::npos){
				ConexionesDos.agregarNodo(elem.ipFuente);
				//Generar la matriz
				conexSit[elem.ipFuente][elem.ipDestino] +=1;

				ConexionesDos.agregarNodo(elem.ipDestino);
			}

		ConexionesDos.agregarArcoNoDirigidoConPeso(elem.ipFuente, elem.ipDestino, peso);
		}
	}

	for(auto elem : conexSit){
		for(auto numConexiones : elem.second){
			ConexionesDos.agregarArcoDirigidoConPeso(elem.first, numConexiones.first, numConexiones.second);
		}
	}

	cout << endl;
	/*cout << "***********************Impresión de grafo de conexiones internas realizado***********************" << endl;

	ConexionesUno.imprimir();

	cout << endl;
	cout << "***********************Impresión de grafo de conexiones a sitio web realizado***********************" << endl;

	ConexionesDos.imprimir();

	cout << endl;*/

	cout << "***********************Cantidad de conexiones internas por día***********************" << endl;
	cout << "Día de búsqueda: " << dia << endl;
	
	int contador = 0;
	for(auto j : conexInt){
		cout << j.first << "; ";
		contador += 1;
	}
	
	cout << endl;
	cout << "Cantidad de conexiones en el día: " << contador << endl;

	
	cout << endl;
	cout << "***********************Cantidad de conexiones internas hacia A por día***********************" << endl;

	int conexion_a = 0;

	for(auto it : conexInt){
		for(auto it2 : it.second){
			if(it2.first == "172.21.65.54"){
				conexion_a += 1;
			}
		}
	}

	cout << "Conexion de computadoras internas hacia kevin.reto.com: " << conexion_a << endl;

	cout << endl;
	cout << "***********************Cantidad de conexiones internas hacia B por día***********************" << endl;

	int conexion_b_1 = 0;

	for(auto it : conexSit){
		for(auto it2 : it.second){
			if(it2.first == "38.237.12.77"){
				conexion_b_1 += 1;
			}
		}
	}

	int conexion_b_2 = 0;

	for(auto it : conexSit){
		for(auto it2 : it.second){
			if(it2.first == "23.177.199.130"){
				conexion_b_2 += 1;
			}
		}
	}

	cout << "Conexion de computadoras internas hacia bofgd2egwezcd8n3kplv.org (ip -> 38.237.12.77): " << conexion_b_1 << endl;
	cout << "Conexion de computadoras internas hacia cmpxaw7lxdyhb63ocpgb.xxx (ip -> 23.177.199.130): " << conexion_b_2 << endl;

	cout << endl;
	cout << "***********************Cantidad de conexiones internas hacia C por día***********************" << endl;

	int conexion_c = 0;

	for(auto it : conexSit){
		for(auto it2 : it.second){
			if(it2.first == "172.21.65.54"){
				conexion_c += 1;
			}
		}
	}

	cout << "Conexion de computadoras internas hacia irs.gov (ip -> 170.8.131.248): " << conexion_c << endl;


}