#include "FileIO.h"

void ReadFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres)
{
    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open())
    {
        cout << "Файл " << fileName << " не может быть открыт для записи" << endl;
        return;
    }
    string parameter = "";
    string value = "";
    int rowCount = count(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), '\n');
    if (rowCount == 0) return;
    fin.close();
    fin.open(fileName);
    while (rowCount >= 0)
    {
        fin >> parameter;
        fin >> value;
        rowCount--;
        
        //GameState
        if (parameter == "round") *round = atoi(value.c_str());
        else if (parameter == "gameOver")
            *gameOver = value == "0" ? false : true;

        else if (parameter == "villagers_count")
            (*villagers).count = atoi(value.c_str());
        else if (parameter == "villagers_diedOfHunger")
            (*villagers).diedOfHunger = atoi(value.c_str());
        else if (parameter == "villagers_diedOfHungerInPercent")
            (*villagers).diedOfHungerInPercent = stof(value.c_str());
        else if (parameter == "villagers_sumOfDiedOfHunger")
            (*villagers).sumOfDiedOfHunger = stof(value.c_str());
        else if (parameter == "villagers_isPlague")
            (*villagers).isPlague = value == "0" ? false : true;
        else if (parameter == "villagers_diedOfPlague")
            (*villagers).diedOfPlague = atoi(value.c_str());
        else if (parameter == "villagers_arrived")
            (*villagers).arrived = atoi(value.c_str());

        else if (parameter == "bushels_count")
            (*bushels).count = atoi(value.c_str());
        else if (parameter == "bushels_harvested")
            (*bushels).harvested = atoi(value.c_str());
        else if (parameter == "bushels_destroyedByRats")
            (*bushels).destroyedByRats = atoi(value.c_str());
        else if (parameter == "bushels_toEat")
            (*bushels).toEat = atoi(value.c_str());

        else if (parameter == "acres_count")
            (*acres).count = atoi(value.c_str());
        else if (parameter == "acres_price")
            (*acres).price = atoi(value.c_str());
        else if (parameter == "acres_toBuy")
            (*acres).toBuy = atoi(value.c_str());
        else if (parameter == "acres_toSell")
            (*acres).toSell = atoi(value.c_str());
        else if (parameter == "acres_toSow")
            (*acres).toSow = atoi(value.c_str());
        else if (parameter == "acres_bushelsHarvestPerAcre")
            (*acres).bushelsHarvestPerAcre = atoi(value.c_str());
        //ConstFile
        else if (parameter == "bushelsToEatPerVillager")
            (*villagers).bushelsToEatPerVillager = atoi(value.c_str());
        else if (parameter == "maxAcresToSowPerVillager")
            (*villagers).maxAcresToSowPerVillager = atoi(value.c_str());
        else if (parameter == "bushelsToSowPerAcre")
            (*acres).bushelsToSowPerAcre = atof(value.c_str());
        else
        {
            cout << "Файл игры поврежден! \n    Параметр: " << parameter << endl;
            break;
        }
    }
    fin.close();
}

void WriteFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres)
{
    ofstream fout;
    fout.open(fileName);
    if (!fout.is_open())
    {
        cout << "Файл состояния игры не может быть открыт" << endl;
        return;
    }

    fout << "round " << *round << endl;
    fout << "gameOver " << *gameOver << endl;

    fout << "villagers_count " << (*villagers).count << endl;
    fout << "villagers_diedOfHunger " << (*villagers).diedOfHunger << endl;
    fout << "villagers_diedOfHungerInPercent " << (*villagers).diedOfHungerInPercent << endl;
    fout << "villagers_sumOfDiedOfHunger " << (*villagers).sumOfDiedOfHunger << endl;
    fout << "villagers_isPlague " << (*villagers).isPlague << endl;
    fout << "villagers_diedOfPlague " << (*villagers).diedOfPlague << endl;
    fout << "villagers_arrived " << (*villagers).arrived << endl;

    fout << "bushels_count " << (*bushels).count << endl;
    fout << "bushels_harvested " << (*bushels).harvested << endl;
    fout << "bushels_destroyedByRats " << (*bushels).destroyedByRats << endl;
    fout << "bushels_toEat " << (*bushels).toEat << endl;

    fout << "acres_count " << (*acres).count << endl;
    fout << "acres_price " << (*acres).price << endl;
    fout << "acres_toBuy " << (*acres).toBuy << endl;
    fout << "acres_toSell " << (*acres).toSell << endl;
    fout << "acres_toSow " << (*acres).toSow << endl;
    fout << "acres_bushelsHarvestPerAcre " << (*acres).bushelsHarvestPerAcre << endl;

    fout.close();
}

void ClearFile(string fileName)
{
    ofstream file;
    file.open(fileName);
    file.close();
}