#include "Hammurabi.h"

int GetRandomNumber(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

Hammurabi::Hammurabi()    
{   
    srand(time(0));
    ReadFile(constFile, &round, &gameOver, &villagers, &bushels, &acres);
    ReadFile(gamestateFile, &round, &gameOver, &villagers, &bushels, &acres);
    if (round >= 1)
    {
        cout << "������� ����������� ��������. ���������� ����?" << endl;
        cout << "������� [Y] - \"����������\". ����� ������ ����� ����, ����� �� ������ ������. ��������: ";
        int key = _getch();
        switch (key)
        {
        case 121:
        case 89:
            cout << "Y" << endl;
            break;
        default:
            cout << (char)key << endl;
            Villagers temp;
            villagers = temp;
            Acres temp2;
            acres = temp2;
            Bushels temp3;
            bushels = temp3;
            ReadFile(constFile, &round, &gameOver, &villagers, &bushels, &acres); 
            break;
        }
    }
    gameStarted = false;
}    

void Hammurabi::BeginGameplayLoop()    
{    
    cout << ((round == 0) ? "����� ���������� � ����!" : "� ������������!") << endl;    

    while (round < 10 && !gameOver)    
    {       
        //���� ���� ������� �� ���������� ��� ���� ������������ � ������ ������� ������
        if (round == 0 || gameStarted)
        {
            acres.price = GetRandomNumber(17, 26);
            BushelsHarvest(); //� ����������� ����
            GetReport();
            acres.bushelsHarvestPerAcre = GetRandomNumber(1, 6);
            villagers.isPlague = (GetRandomNumber(0, 20) <= 3);
            WriteFile(gamestateFile, &round, &gameOver, &villagers, &bushels, &acres);
            round++;
        }     
        //���� ����� �������� ����������� ����
        else
        {
            GetReport();
        }
        gameStarted = true;
        //���� ����������, �� �������� � ����������� �������� �����
        InputParameters();
        VillagersHungerMortality();    
        VillagersPlagueMortality();    
        VillagersGrowth();    
        SellAcres();    
        BuyAcres();    
        SowAcres();    
        BusehlsDestructionByRats();   
    }    
    GetReport();
    OnGameOver();
}    

#pragma region InputOutput

void Hammurabi::GetReport()    
{    
    cout << "��� ����������, �������� �������� ����" << endl;    

    if (round > 0)    
    {    
        cout << "   � ���� " << round << " ������ ����������� ���������" << endl;    
    }    

    if (villagers.diedOfHunger > 0)    
    {    
        cout << "   " << villagers.diedOfHunger << " ����� ������ � ������;" << endl;    
    }    

    if (gameOver)    
    {    
        cout << "���� ���������, ��� ��� " << villagers.diedOfHungerInPercent << "% ����� ��������� ������ � ������;" << endl;    
        return;    
    }    

    if (villagers.arrived > 0)    
    {    
        cout << "   " << villagers.arrived << " ����� �������� � �����;" << endl;    
    }    

    if (villagers.isPlague)    
    {    
        cout << "   ���� ���������� �������� ���������;" << endl;    
    }    

    cout << "   ��������� ������ ������ ���������� " << villagers.count << " �������; " << endl;    

    if (bushels.harvested > 0)    
    {    
        cout << "   �� ������� " << bushels.harvested << " ������� �������, �� " << acres.bushelsHarvestPerAcre << " ������� � ����;" << endl;    
    }    

    if (bushels.destroyedByRats > 0)    
    {    
        cout << "   ����� ��������� " << bushels.destroyedByRats << " ������� �������;" << endl;    
    }    

    cout << "   �������� " << bushels.count << " ������ � �������;" << endl;    
    cout << "   ����� ������ �������� " << acres.count << " �����;" << endl;    
    cout << "   1 ��� ����� ����� ������ " << acres.price << " �������." << endl;    
    cout << endl;    
}    

void Hammurabi::InputParameters()    
{    
    cout << "��� ���������, ����������?" << endl;    
    bool exit = false;    
    while (!exit)    
    {    
        cout << "������� ����� ����� ����������� ������? ";    
        cin >> acres.toBuy;    

        cout << "������� ����� ����� ����������� �������? ";    
        cin >> acres.toSell;    

        cout << "������� ������� ������� ����������� ������? ";    
        cin >> bushels.toEat;    

        cout << "������� ����� ����� ����������� �������? ";    
        cin >> acres.toSow;    

        if (CheckInputParameters())    
        {    
            cout << "��������� ��������� ��������. ������� [Y] - \"�����������\". ����� ����� �� ������ ������. ��������: ";    
            int key = _getch();    

            switch(key)
            {
            case 121:
            case 89:
                cout << "Y" << endl;
                exit = true;
                break;
            default:
                cout << (char)key << endl;
                break;
            }  
        }    

        cout << endl;    
    }    
}    

bool Hammurabi::CheckInputParameters()    
{    
    if (acres.toSow < 0 || acres.toBuy < 0 || acres.toSell < 0 || bushels.toEat < 0)    
    {    
        cout << "�, ����������, ������ ���! �������� �������� �� ����� ���� ������ 0!" << endl;    
        return false;    
    }    

    if (acres.toBuy * acres.toSell > 0)    
    {    
        cout << "�, ����������, ������ ���! ������ ��������� � �������� ���� ����� ������������. ��� ������������. � ���� �� ��� ������� ������!" << endl;    
        return false;    
    }    

    if (acres.toSow + acres.toSell > acres.count + acres.toBuy)    
    {    
        cout << "�, ����������, ������ ���! ����� ����� ������������, ����� ��������� ��� ���� ���������!" << endl;    
        return false;    
    }   

    if (acres.toSow * acres.bushelsToSowPerAcre + bushels.toEat + acres.toBuy * acres.price > bushels.count + acres.toSell * acres.price)
    {    
        cout << "�, ����������, ������ ���! ������� ������� ������������, ����� ��������� ��� ���� ���������!" << endl;    
        return false;    
    }    

    if (villagers.count * villagers.maxAcresToSowPerVillager < acres.toSow)    
    {    
        cout << "�, ����������, ������ ���! ����� ������������, ����� ���������� ������� ����� �����!" << endl;    
        return false;    
    }    

    return true;    
}    

void Hammurabi::OnGameOver()
{
    if (round == 10)
    {
        cout << "�� ��������" << endl;
        
        float diedOfHungerStat = villagers.sumOfDiedOfHunger / 10.0;
        float acresPerVillager = (float)acres.count / (float)villagers.count;
        
        cout << "������������� ������� ������� �� ������: " << roundf(diedOfHungerStat) << " %" << endl;
        cout << "���������� ����� ����� �� ������ ������: " << roundf(acresPerVillager) << endl;

        //
        if (diedOfHungerStat > 33 && acresPerVillager < 7)
        {
            cout << "��-�� ����� ���������������� � ����������, ����� ������� ����, � ������ ��� �� ������.������ �� ��������� ������� ������ ������������� � ��������" << endl;
        }
        else if (diedOfHungerStat > 10 && acresPerVillager < 9)
        {
            cout << "�� ������� �������� �����, ������� ������ � ����� ��������.����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������" << endl;
        }
        else if (diedOfHungerStat > 3 && acresPerVillager < 10)
        {
            cout << "�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����" << endl;
        }
        else
        {
            cout << "����������!���� �������, �������� � ���������� ������ �� ���������� �� �����" << endl;
        }
    }
    else
    {
        cout << "�� ���������" << endl;
    }

    ClearFile(gamestateFile);
}

#pragma endregion

#pragma region Villagers

void Hammurabi::VillagersHungerMortality() //���������� ��������� �� ������    
{    
    int wellFedVillagers = bushels.toEat / villagers.bushelsToEatPerVillager;    
    bushels.count -= bushels.toEat;     //�������� ������ ����������� �������    
    villagers.diedOfHunger = villagers.count - wellFedVillagers;    
    villagers.diedOfHunger = villagers.diedOfHunger < 0 ? 0 : villagers.diedOfHunger;    
    villagers.diedOfHungerInPercent = ((float)villagers.diedOfHunger / (float)villagers.count) * 100;
    villagers.sumOfDiedOfHunger += villagers.diedOfHungerInPercent;
    villagers.count -= villagers.diedOfHunger;
    if (villagers.diedOfHungerInPercent > 45.0f)
    {    
        gameOver = true;    
    }    
}    

void Hammurabi::VillagersPlagueMortality()  //���������� ��������� �� ����    
{    
    villagers.diedOfPlague = villagers.isPlague ? (villagers.count - villagers.count % 2) / 2 : 0;
    villagers.count -= villagers.diedOfPlague;    
}    

void Hammurabi::VillagersGrowth() //���� ���������    
{    
    villagers.arrived = villagers.diedOfHunger / 2 + (5 - acres.bushelsHarvestPerAcre) * bushels.count / 600 + 1;    
    villagers.arrived = villagers.arrived < 0 ? 0 : villagers.arrived;    
    villagers.arrived = villagers.arrived > 50 ? 50 : villagers.arrived;    
    villagers.count += villagers.arrived;    
}    

#pragma endregion

#pragma region Bushels

void Hammurabi::BushelsHarvest() //���� �������    
{    
    bushels.count += bushels.harvested;    
}    

void Hammurabi::BusehlsDestructionByRats()    
{    
    bushels.destroyedByRats = (int)(GetRandomNumber(0, 700) * 0.0001f * bushels.count);    
    bushels.count -= bushels.destroyedByRats;    
}    

#pragma endregion

#pragma region Acres

void Hammurabi::BuyAcres()    
{    
    bushels.count -= acres.toBuy * acres.price;    
    acres.count += acres.toBuy;    
}    

void Hammurabi::SellAcres()    
{    
    bushels.count += acres.toSell * acres.price;    
    acres.count -= acres.toSell;    
}    

void Hammurabi::SowAcres() //����� ������� �� ��������� ���     
{    
    
    bushels.count -= (int)(acres.bushelsToSowPerAcre * acres.toSow);    
    bushels.harvested = acres.bushelsHarvestPerAcre * acres.toSow;    
}    
#pragma endregion
