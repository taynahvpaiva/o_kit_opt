#include <iostream>
#include <vector>      
#include <cstdlib>
#include <ctime>

#include "Construction.hpp" 
#include "Data.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));

    auto data = Data(argc, argv[1]);//objeto chamado data da classe Data usando argc(2) e argv[1](a instancia)
    data.read();
    
    int n = data.getDimension();//variavel n para receber a dimensao da instancia

    cout << "Dimension: " << n << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist();

   vector<int> CL;//vetor para guardar os nós disponiveis
    for (int i = 2; i <= n; i++) {
        CL.push_back(i);
    }

    Solucao s0 = solutionRandom(data, CL);

    cout << "\nSubtour inicial: ";//criado com o random
    for (int i = 0; i < s0.sequencia.size(); i++) {
        cout << s0.sequencia[i];
        if (i < s0.sequencia.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "Custo do subtour inicial: " << s0.custoTotal << endl;
    cout << "Resto de nos no CL(pos criação do subtor inicial): " << CL.size() << endl;


//2. Computar os pares (k, {i, j}) para todo k ∈ CL, {i, j} ∈ s e armazená-los em uma lista Ω
    std::vector<InsertionInfo> omega = pairskOmega(s0, data, CL);
    std::cout << "Total de candidatos em omega: " << omega.size() << std::endl << std::endl;
    for (int i = 0; i < (int)omega.size(); i++) {
        std::cout << "Opcao " << i + 1 << ": "
                  << "Inserir No " << omega[i].noInserido
                  << " apos o No " << omega[i].arestaRemovida
                  << " | Delta: " << omega[i].delta << std::endl;
    }

    
    

    return 0;
}