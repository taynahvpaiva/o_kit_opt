#pragma once
#include "Localsearch.hpp"   
#include <algorithm> 
#include <cstdlib>     
#include <vector>

using namespace std;

bool bestImprovementSwap(Solution *s, Data &data){

    double bestDelta = 0;
    int best_i, best_j,currentNode_i,nextNode_i, previousNode_i,currentNode_j, nextNode_j, previousNode_j;
    double delta;

    for(int i = 1; i < s->sequence.size() - 1; i++){

        currentNode_i = s->sequence[i];
        nextNode_i = s->sequence[i + 1];
        previousNode_i = s->sequence[i - 1];

        for(int j = i + 1; j < s->sequence.size() - 1; j++){

            currentNode_j = s->sequence[j];
            nextNode_j = s->sequence[j + 1];
            previousNode_j = s->sequence[j - 1];

            if (j == i + 1){
                //(i and j adjacent) one pair always repeats on opposite sides, so we need to discard it
                delta = -data.getDistance(previousNode_i, currentNode_i) - data.getDistance(currentNode_j, nextNode_j)
                        + data.getDistance(previousNode_i, currentNode_j) + data.getDistance(currentNode_i, nextNode_j);
            }else{
                //kit's formula only works when i and j aren't adjacent
                delta = -data.getDistance(previousNode_i, currentNode_i) - data.getDistance(currentNode_i, nextNode_i) + data.getDistance(previousNode_i, currentNode_j)+ data.getDistance(currentNode_j, nextNode_i) - data.getDistance(previousNode_j, currentNode_j) - data.getDistance(currentNode_j, nextNode_j)+ data.getDistance(previousNode_j, currentNode_i) + data.getDistance(currentNode_i, nextNode_j);
            }

            if (delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0){
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->totalCost = s->totalCost + bestDelta;
        return true;
    }
    return false;
}



bool bestImprovement2Opt(Solution *s, Data &data){
    double bestDelta = 0;
    int best_i, best_j, currentNode_i, previousNode_i, currentNode_j, nextNode_j;
    double delta;

    for(int i = 1; i < s->sequence.size() - 1; i++){

        currentNode_i = s->sequence[i];
        previousNode_i = s->sequence[i - 1];

        for(int j = i + 1; j < s->sequence.size() - 1; j++){

            currentNode_j = s->sequence[j];
            nextNode_j = s->sequence[j + 1];

            
            delta = -data.getDistance(previousNode_i, currentNode_i) - data.getDistance(currentNode_j, nextNode_j)
                    + data.getDistance(previousNode_i, currentNode_j) + data.getDistance(currentNode_i, nextNode_j);
            

            if (delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0){
        reverse(s->sequence.begin() + best_i, s->sequence.begin() + best_j + 1);
        s->totalCost = s->totalCost + bestDelta;
        return true;
    }
    return false;
}

bool bestImprovementOrOpt(Solution *s, Data &data, int vertex123){
    
}

void BuscaLocal(Solution *s, Data &data){

    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false){

        int n = rand() % NL.size();
        switch (NL[n]){

            case 1:
                improved = bestImprovementSwap(s, data);
                break;
            case 2:
                improved = bestImprovement2Opt(s, data);
                break;
            case 3:
                improved = bestImprovementOrOpt(s, data, 1); // Reinsertion
                break;
            case 4:
                improved = bestImprovementOrOpt(s, data, 2); // Or-opt-2
                break;
            case 5:
                improved = bestImprovementOrOpt(s, data, 3); // Or-opt-3
                break;
        }

        if (improved){
            NL = {1, 2, 3, 4, 5};
        }else{
            NL.erase(NL.begin() + n);
        }
    }
}
