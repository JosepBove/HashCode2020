#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void retallar(string const &str, const char delim, vector<int> &out) 
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(stoi(str.substr(start, end - start)));
	}
}


void solveProblem(int slices, int types, vector<int> data) 
{

}

int main()
{
    string linea;
    ifstream arxiu( "../datasets/a_example.in" );
    vector<int> info;

    int slices;
    int types;

    //Si arxiu no s'obre bé F
    if (!arxiu) return 0;

    
    //Llegeixo primera linea i omplo variables.
    getline(arxiu, linea);
    retallar(linea, ' ', info);
    slices = info[0];
    types = info[1];
    info.clear();

    //Llegeixo segona linea i torno vector
    getline(arxiu, linea);
    retallar(linea, ' ', info);

    /*
    //Test per veure si la info està ben carregada
    cout << "Slices: " << slices << " Types: " << types << '\n' << "Data: ";
    for (auto i = info.begin(); i != info.end(); ++i) std::cout << *i << ' ';
    */

    solveProblem(slices, types, info);

    arxiu.close(); 
    return 0;
}

