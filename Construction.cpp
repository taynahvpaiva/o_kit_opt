#include "Construction.hpp"

#include <algorithm>//ordenar omega
#include <cmath>
#include <vector>
#include <cstdlib>//biblioteca que contem o random

using namespace std;

//1. Construir uma solução parcial s' de forma aleatória
Solucao solutionRandom(Data &data, std::vector<int> &CL) {
    Solucao s = {{1}, 0};
    //sorteando 3 nós aleatorios para formar uma solucao parcial(s') aleatoria
    for (int i = 0; i < 3; i++) {
        int primeiroNos = rand() % CL.size();//rand() gera um numero inteiro aleatorio e depois acha o resto da divisao pelo tamanho da solucao
        //esse numero que for encontrado vai ser o indice escolhido e isso repete 3 vezes
        s.sequencia.push_back(CL[primeiroNos]);
        CL.erase(CL.begin() + primeiroNos);
    }
    s.sequencia.push_back(1);

    //calcular o custo(distancia) total da solucao parcial
    for (int a = 0, b = 1; b < s.sequencia.size(); a++, b++) {
        s.custoTotal+= data.getDistance(s.sequencia[a], s.sequencia[b]);
    }

    return s;
}

//2. Computar os pares (k, {i, j}) para todo k ∈ CL, {i, j} ∈ s e armazená-los em uma lista Ω
std::vector<InsertionInfo> pairskOmega(const Solucao &s, Data &data, const std::vector<int> &CL) {
      std::vector<InsertionInfo> omega;
    for (int t = 0; t < CL.size(); t++) {
        int k = CL[t];
      
        //percorre as arestas (i, j) do subtour atual s
        for (int aresta = 0; aresta < s.sequencia.size() - 1; aresta++) {
            int i = s.sequencia[aresta];
            int j = s.sequencia[aresta + 1];

            //delta = d(i,k) + d(k,j) - d(i,j)
            double dik = data.getDistance(i, k);//nova aresta1
            double dkj = data.getDistance(k, j);//nova aresta2
            double dij = data.getDistance(i, j);//aresta antiga removida

            double delta = dik + dkj - dij;

            InsertionInfo novidade;
            novidade.noInserido = k;
            novidade.arestaRemovida = i;
            novidade.delta = delta;

           omega.push_back(novidade);
        }
    }

    //4. Ordenar os pares em Ω em ordem crescente de ∆
    std::sort(omega.begin(), omega.end(),
    [](const InsertionInfo &a, const InsertionInfo &b) {
        return a.delta < b.delta;
    }
    );

    return omega;
}

//6. Selecionar aleatoriamente um dos [α × |Ω|] primeiros pares em Ω
InsertionInfo selectCandidateAlpha(
    const std::vector<InsertionInfo> &omega
) {
    //divide o numero aleatorio gerado por rand() pelo seu valor máximo (RAND_MAX da biblioteca), gerando um valor entre 0 e 1
    double alpha = (double) rand() / RAND_MAX;

    //quantos elementos de Omega participarão da seleção
    int alphaomega = (int)(alpha * omega.size());

    // Escolhe aleatoriamente um dos primeiros elementos
    // Gera um índice aleatório entre 0 e alphaomega - 1 para escolher um dos primeiros elementos de omega.
    int escolhido = rand() % alphaomega;


    return omega[escolhido];
}