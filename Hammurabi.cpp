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
        cout << "Имеется сохраненный прогресс. Продолжить игру?" << endl;
        cout << "Клавиша [Y] - \"продолжить\". Чтобы начать новую игру, нажми на другую кнопку. Действие: ";
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
    cout << ((round == 0) ? "Добро пожаловать в игру!" : "С возвращением!") << endl;    

    while (round < 10 && !gameOver)    
    {       
        //если игра никогда не начиналась или игра продолжается в рамках игровой сессии
        if (round == 0 || gameStarted)
        {
            acres.price = GetRandomNumber(17, 26);
            BushelsHarvest(); //с предыдущего года
            GetReport();
            acres.bushelsHarvestPerAcre = GetRandomNumber(1, 6);
            villagers.isPlague = (GetRandomNumber(0, 20) <= 3);
            WriteFile(gamestateFile, &round, &gameOver, &villagers, &bushels, &acres);
            round++;
        }     
        //если игрок запустил сохраненную игру
        else
        {
            GetReport();
        }
        gameStarted = true;
        //ввод параметров, их проверка и прохождение игрового цикла
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
    cout << "Мой повелитель, соизволь поведать тебе" << endl;    

    if (round > 0)    
    {    
        cout << "   в году " << round << " твоего высочайшего правления" << endl;    
    }    

    if (villagers.diedOfHunger > 0)    
    {    
        cout << "   " << villagers.diedOfHunger << " людей умерло с голоду;" << endl;    
    }    

    if (gameOver)    
    {    
        cout << "Игра закончена, так как " << villagers.diedOfHungerInPercent << "% всего населения умерло с голоду;" << endl;    
        return;    
    }    

    if (villagers.arrived > 0)    
    {    
        cout << "   " << villagers.arrived << " людей приехало в город;" << endl;    
    }    

    if (villagers.isPlague)    
    {    
        cout << "   Чума уничтожила половину населения;" << endl;    
    }    

    cout << "   Население города сейчас составляет " << villagers.count << " человек; " << endl;    

    if (bushels.harvested > 0)    
    {    
        cout << "   Мы собрали " << bushels.harvested << " бушелей пшеницы, по " << acres.bushelsHarvestPerAcre << " бушелей с акра;" << endl;    
    }    

    if (bushels.destroyedByRats > 0)    
    {    
        cout << "   Крысы истребили " << bushels.destroyedByRats << " бушелей пшеницы;" << endl;    
    }    

    cout << "   Осталось " << bushels.count << " бушеля в амбарах;" << endl;    
    cout << "   Город сейчас занимает " << acres.count << " акров;" << endl;    
    cout << "   1 акр земли стоит сейчас " << acres.price << " бушелей." << endl;    
    cout << endl;    
}    

void Hammurabi::InputParameters()    
{    
    cout << "Что пожелаешь, повелитель?" << endl;    
    bool exit = false;    
    while (!exit)    
    {    
        cout << "Сколько акров земли повелеваешь купить? ";    
        cin >> acres.toBuy;    

        cout << "Сколько акров земли повелеваешь продать? ";    
        cin >> acres.toSell;    

        cout << "Сколько бушелей пшеницы повелеваешь съесть? ";    
        cin >> bushels.toEat;    

        cout << "Сколько акров земли повелеваешь засеять? ";    
        cin >> acres.toSow;    

        if (CheckInputParameters())    
        {    
            cout << "Подтверди введенные значения. Клавиша [Y] - \"подтверждаю\". Иначе нажми на другую кнопку. Действие: ";    
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
        cout << "О, повелитель, пощади нас! Вводимые значения не могут быть меньше 0!" << endl;    
        return false;    
    }    

    if (acres.toBuy * acres.toSell > 0)    
    {    
        cout << "О, повелитель, пощади нас! Нельзя продавать и покупать акры земли одновременно. Это бессмысленно. В этом же нет никакой выгоды!" << endl;    
        return false;    
    }    

    if (acres.toSow + acres.toSell > acres.count + acres.toBuy)    
    {    
        cout << "О, повелитель, пощади нас! Акров земли недостаточно, чтобы выполнить все ваши пожелания!" << endl;    
        return false;    
    }   

    if (acres.toSow * acres.bushelsToSowPerAcre + bushels.toEat + acres.toBuy * acres.price > bushels.count + acres.toSell * acres.price)
    {    
        cout << "О, повелитель, пощади нас! Бушелей пшеницы недостаточно, чтобы выполнить все ваши пожелания!" << endl;    
        return false;    
    }    

    if (villagers.count * villagers.maxAcresToSowPerVillager < acres.toSow)    
    {    
        cout << "О, повелитель, пощади нас! Людей недостаточно, чтобы обработать столько акров земли!" << endl;    
        return false;    
    }    

    return true;    
}    

void Hammurabi::OnGameOver()
{
    if (round == 10)
    {
        cout << "ВЫ ВЫИГРАЛИ" << endl;
        
        float diedOfHungerStat = villagers.sumOfDiedOfHunger / 10.0;
        float acresPerVillager = (float)acres.count / (float)villagers.count;
        
        cout << "Среднегодовой процент умерших от голода: " << roundf(diedOfHungerStat) << " %" << endl;
        cout << "Количество акров земли на одного жителя: " << roundf(acresPerVillager) << endl;

        //
        if (diedOfHungerStat > 33 && acresPerVillager < 7)
        {
            cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
        }
        else if (diedOfHungerStat > 10 && acresPerVillager < 9)
        {
            cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
        }
        else if (diedOfHungerStat > 3 && acresPerVillager < 10)
        {
            cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << endl;
        }
        else
        {
            cout << "Фантастика!Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
        }
    }
    else
    {
        cout << "ВЫ ПРОИГРАЛИ" << endl;
    }

    ClearFile(gamestateFile);
}

#pragma endregion

#pragma region Villagers

void Hammurabi::VillagersHungerMortality() //смертность населения от голода    
{    
    int wellFedVillagers = bushels.toEat / villagers.bushelsToEatPerVillager;    
    bushels.count -= bushels.toEat;     //спросить насчет недоеденной пшеницы    
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

void Hammurabi::VillagersPlagueMortality()  //смертность населения от чумы    
{    
    villagers.diedOfPlague = villagers.isPlague ? (villagers.count - villagers.count % 2) / 2 : 0;
    villagers.count -= villagers.diedOfPlague;    
}    

void Hammurabi::VillagersGrowth() //рост населения    
{    
    villagers.arrived = villagers.diedOfHunger / 2 + (5 - acres.bushelsHarvestPerAcre) * bushels.count / 600 + 1;    
    villagers.arrived = villagers.arrived < 0 ? 0 : villagers.arrived;    
    villagers.arrived = villagers.arrived > 50 ? 50 : villagers.arrived;    
    villagers.count += villagers.arrived;    
}    

#pragma endregion

#pragma region Bushels

void Hammurabi::BushelsHarvest() //сбор пшеницы    
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

void Hammurabi::SowAcres() //засев пшеницы на следующий год     
{    
    
    bushels.count -= (int)(acres.bushelsToSowPerAcre * acres.toSow);    
    bushels.harvested = acres.bushelsHarvestPerAcre * acres.toSow;    
}    
#pragma endregion
