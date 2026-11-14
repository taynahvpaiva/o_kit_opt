#pragma once
#include "Data.h"
#include "Construction.hpp"

bool bestImprovementSwap(Solution *s, Data &data);
bool bestImprovement2Opt(Solution *s, Data &data);
bool bestImprovementOrOpt(Solution *s, Data &data, int vertex123); //Reinsertion , Or-opt-2, Or-opt-3

void BuscaLocal(Solution *s, Data &data);
