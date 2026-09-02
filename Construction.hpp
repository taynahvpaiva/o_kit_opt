#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include <vector>
#include "Data.h"

typedef struct Solucao{
    std::vector<int> sequencia;
    double custoTotal;
} Solucao;

typedef struct InsertionInfo{
    int noInserido;
    int arestaRemovida;
    double delta;
} InsertionInfo;


Solucao solutionRandom(Data &data, std::vector<int> &CL);
std::vector<InsertionInfo> pareskOmega(const Solucao &s, Data &data, const std::vector<int> &CL);

#endif