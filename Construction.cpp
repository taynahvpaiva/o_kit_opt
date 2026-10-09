#include "Construction.hpp"

#include <algorithm>//sort omega
#include <cmath>
#include <vector>
#include <cstdlib>//random library

using namespace std;

//1. Construir uma solução parcial s' de forma aleatória
Solution solutionRandom(Data &data, std::vector<int> &CL) {
    Solution s = {{1}, 0};//initialize struct solution

    //selecting 3 random nodes for the initial solution
    for (int i = 0; i < 3; i++) {
        int firstNode = rand() % CL.size();//rand() gera um numero inteiro aleatorio e depois acha o resto da divisao pelo tamanho da solucao
        //esse numero que for encontrado vai ser o indice do array escolhido e isso repete 3 vezes
        s.sequence.push_back(CL[firstNode]);
        CL.erase(CL.begin() + firstNode);
    }
    s.sequence.push_back(1);

    //calcular o custo(distancia) total da solucao parcial
    for (int a = 0, b = 1; b < s.sequence.size(); a++, b++) {
        s.totalCost+= data.getDistance(s.sequence[a], s.sequence[b]);
    }

    return s;
}

//2. Computar os pares (k, {i, j}) para todo k pertecente CL, {i, j} pertecente s e armazená-los em uma lista Ω
std::vector<Insertion> omegaInsertion(const Solution &s, Data &data, const std::vector<int> &CL) {
      std::vector<Insertion> omega;//possibility of insertion
    for (int i = 0; i < CL.size(); i++) {
        int node = CL[i];
      
        //percorre as arestas (i, j) do subtour atual s
        for (int edge=0; edge<s.sequence.size() - 1; edge++) {

            int row = s.sequence[edge];
            int column = s.sequence[edge+1];

            double edge1 = data.getDistance(row, node);//nova aresta1
            double edge2 = data.getDistance(node, column);//nova aresta2
            double removedEdge = data.getDistance(row, column);//aresta antiga removida

            double delta = edge1 + edge2 - removedEdge;

            Insertion update;
            update.newNode = node;
            update.node1Edge = row;
            update.delta = delta;

           omega.push_back(update);
        }
    }

    //4. Ordenar os pares em Ω em ordem crescente de ∆
    std::sort(omega.begin(), omega.end(), [](const Insertion &node1, const Insertion &node2) {return node1.delta < node2.delta;});
    return omega;
}

//6. Selecionar aleatoriamente um dos [α × |Ω|] primeiros pares em Ω
//a função escolhe uma possibilidade de inserção, que envolve tanto um nó quanto o lugar onde ele será inserido
Insertion selectCandidateAlpha(const std::vector<Insertion> &omega){
    //5. divide o numero aleatorio gerado por rand() pelo seu valor máximo (RAND_MAX da biblioteca), gerando um valor entre 0 e 1
    double alpha = (double) rand() / RAND_MAX;

    //quantos elementos de Omega participarão da seleção
    int omegatoalpha = (int)(alpha * omega.size());

    // Escolhe aleatoriamente um dos primeiros elementos
    // Gera um índice aleatório entre 0 e omegatoalpha - 1 para escolher um dos primeiros elementos de omega.
    int selected = rand() % omegatoalpha;

    return omega[selected];
}

Solution newSolution(Data &data) {
    vector<int> CL;//vetor para guardar os nós disponiveis
    for (int i = 2; i <= data.getDimension(); i++) {
        CL.push_back(i);
    }

    Solution s0 = solutionRandom(data, CL);

    while (!CL.empty()) {
        // 3. Calcular os candidatos
        vector<Insertion> omega = omegaInsertion(s0, data, CL);

        // 6. Selecionar um candidato
        Insertion selected = selectCandidateAlpha(omega);

        //new node in the solution
        for (int i = 0; i < (int)s0.sequence.size(); i++) {
            if (s0.sequence[i] == selected.node1Edge) {
                s0.sequence.insert(s0.sequence.begin() + i + 1, selected.newNode);//begin() inicio do vetor; + i + 1  posicao logo depois do indice i; selected.newNode no que sera inserido 
                break;
            }
        }

        s0.totalCost += selected.delta;

        for (int i = 0; i < (int)CL.size(); i++) {
            if (CL[i] == selected.newNode) {
                CL.erase(CL.begin() + i);
                break;
            }
        }

    }

    return s0;
}