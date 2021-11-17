#include <iostream>
#include <unordered_map>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

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
		Record(string ipF,  string nF,string ipD)
        {
			this -> ipFuente = ipF; 
			this -> nombreFuente = nF;
			this -> ipDestino = ipD;	
		}
		
		void imprimirRecord()
        {
			cout << fecha << "__" << hora << ":" << ipFuente << ":" << puertoFuente << ":" << nombreFuente <<":" << ipDestino << ":" << puertoDestino << ":" << nombreDestino << endl;
		}

		void imprimiripD()
        {
			cout << ipDestino << endl;
		}

		void imprimirpD()
        {
			cout << puertoDestino << endl;
		}

        
	
};
vector<Record> data;

unordered_map <string, int> conexionesPorDia(string f)
{
    unordered_map <string, int> d;

    for(Record r: data)
    {
        if(f == r.fecha)
        {  
            if(r.nombreDestino != "-" && r.nombreFuente.substr(r.nombreFuente.size(),r.nombreFuente.size()-8) != "reto.com")
            {
				//Checar si ya existe
				if(d.find(r.nombreDestino) == d.end())
				{
					d[r.nombreDestino] = 0;
				}
                d[r.nombreDestino]++;
            }
		
        }
    }
    
    
	// for(auto it: d)
	// {
	// 	cout << it.first << "," << it.second << endl;
	// }
	return d;
    
}

void top(int n, string f)
{
	unordered_map <string, int> a = conexionesPorDia(f);
	map <int, vector <string> > m;
	
	for(auto it : a)
	{
		m[it.second].push_back(it.first);
	}

	for (auto it1 : m)
	{
		cout << it1.first << ":" << endl;
		// for(string it2 : it1.first.begin())
		// {
		// 	cout << it2 << endl;
		// }
		// for (string it2 : it1.first)
		// {
		// 	cout << it2.first;
		// }
		for(auto it2 : it1.first)
		{
			cout << it2 << endl;
		}
	}
}

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

int main()
{
    cargarDatos();
	//conexionesPorDia("14-8-2020");
	top(5, "14-8-2020");

}
