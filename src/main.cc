#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void escriureArxiu(vector<int> resultat, string path) {
    ofstream arxiu(path);
    //Escriure al arxiu, no té cap misteri
    arxiu << resultat.size() << '\n';
    for(vector<int>::const_iterator i = resultat.begin(); i != resultat.end(); i++) {
        arxiu << *i << ' ';
    }
}

vector<int> solveProblem(int slices, vector<int> data) 
{
    if(data.size() == 0) return {};

    vector<int> ind;
    vector<int> val;
    vector<int> indexSol;
    vector<int> valueSol;

    int sum = 0;
    int maxsum = 0;
    int index = data.size() - 1;


    //Fins que no tinguem solució basically
    while(true) {
        for(int i = index; i > -1; i--) {

            int actual = data[i];
            int tempsum = sum + actual;
            
            if(tempsum == slices) {
                //Afegim els valors i ja tenim solució
                sum = tempsum;
                ind.push_back(i);
                val.push_back(actual);
                break;
            } else if (tempsum < slices) {
                //Afegim valors que hem d'actualitzar (possibilitat que hi hagi un millor solució)
                sum = tempsum;
                ind.push_back(i);
                val.push_back(actual);
                continue;
            } else if (tempsum > slices) {
                //Liada aixi que no guardem els valors
                continue;
            }
        }
         //Afegeixo els valors i els index als vectors de solució
        if(maxsum < sum) {
            //TODO: CAGADA?
            maxsum = sum;
            for (auto i : ind) indexSol.push_back(i);
            for (auto i : val) valueSol.push_back(i);
        }

        //Si el valor és el mateix sortim i tenim solució
        if(maxsum == slices) break;

        //Actualitzem l'últim valor i l'últim index
        if(ind.size() != 0) {
            //TODO: CAGADA?
            sum = sum - val.back();
            index = ind.back()-1;
            val.pop_back();
            ind.pop_back();
        } else {
            index--;
        }

        //Si ja no queda res a mirar ja tenim solució
        if(ind.size() == 0 && index == 0) break;
     }


    //Esta al revés així que ho girem i ja tenim la solució
    reverse(indexSol.begin(),indexSol.end());
    return indexSol;
}


void retallar(string const &str, const char delim, vector<int> &out) 
{
    //Split per cada espai, tampoc hi ha cap misteri
	size_t inici;
	size_t final = 0;

	while ((inici = str.find_first_not_of(delim, final)) != string::npos)
	{
		final = str.find(delim, inici);
		out.push_back(stoi(str.substr(inici, final - inici)));
	}
}

int main(int argc, char* argv[])
{

    vector<string> arxius = {
        "a_example",
        "b_small",
        "c_medium",
        "d_quite_big",
        "e_also_big",
    };

    //Automatitzacio per tots els datasets que em feia pal anar un a un
    for (auto p : arxius) {
        
        int slices;
        string linea;
        vector<int> info;
        vector<int> solucio;
        ifstream arxiu("../datasets/" + p + ".in");
        

        //Si arxiu no s'obre bé F
        if (!arxiu) { printf("Arxiu no trobat!"); return 0; }

        //Llegeixo primera linea i omplo variables.
        getline(arxiu, linea);
        retallar(linea, ' ', info);
        slices = info[0];
        info.clear();

        //Llegeixo segona linea i torno vector
        getline(arxiu, linea);
        retallar(linea, ' ', info);

        solucio = solveProblem(slices, info);
        escriureArxiu(solucio, "../output/" + p + ".out");
        arxiu.close();

        cout << "Processant: " << p << '\n'; 
    }
    
    cout << "\nCompletat =D\n";
    return 0;
}

