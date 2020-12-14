#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "ResourcePath.hpp"

using namespace std;
using json = nlohmann::json;

int getMatrixValue(int iDefend, int iAtack);

vector<string> getDictKeys(string relPath);

vector<int> getDatosPokemon(string nombre);

vector<int> getDatosMovimiento(string nombre);
