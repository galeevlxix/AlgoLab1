#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <string>
#include "Structures.h"

using namespace std;

void ReadFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres);
void WriteFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres);
void ClearFile(string fileName);