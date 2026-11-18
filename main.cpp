#include <iostream>
#include <vector>      
#include <cstdlib>
#include <ctime>

#include "Construction.hpp"
#include "Localsearch.hpp"
#include "Data.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));

    auto data = Data(argc, argv[1]);//get the problem informations
    data.read();
    
    int dimensionInstance = data.getDimension();

    cout << "Dimension: " << dimensionInstance << endl<< "DistanceMatrix: " << endl;
    data.printMatrixDist();
     
    Solution s0 = newSolution(data);

    cout << "\nSolucao construtor: ";//criado com o random
    for (int i = 0; i < s0.sequence.size(); i++) {
        cout << s0.sequence[i];
        if (i < s0.sequence.size() - 1) cout << " -> ";
    }
    
    cout << endl << "Custo construtor: " << s0.totalCost << endl;

    BuscaLocal(&s0, data);//melhora a solucao do construtor com estruturas de vizinhança

    cout << endl << "Solucao busca local: ";
    for (int i = 0; i < s0.sequence.size(); i++) {
        cout << s0.sequence[i];
        if (i < s0.sequence.size() - 1) cout << " -> ";
    }

    cout << endl << "Custo busca local: " << s0.totalCost << endl;

    return 0;
}