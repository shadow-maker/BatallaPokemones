#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "ResourcePath.hpp"

using namespace std;
using json = nlohmann::json;

int getMatrixValue(int iDefend, int iAtack);

vector<string> getPokemones();

//Pokemon crearPokemon(string nombre);

vector<int> getDatosPokemon(string nombre);
