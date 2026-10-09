#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include <vector>
#include "Data.h"

typedef struct Solution{
    std::vector<int> sequence;
    double totalCost;
} Solution;

typedef struct Insertion{
    int newNode;
    int node1Edge;
    double delta;//increase in cost with the new node
} Insertion;


Solution solutionRandom(Data &data, std::vector<int> &CL);

std::vector<Insertion> omegaInsertion(const Solution &s, Data &data, const std::vector<int> &CL);

Insertion selectCandidateAlpha(const std::vector<Insertion> &omega);

Solution newSolution(Data &data);
#endif