# Лабораторная работа 1
Игра Hammurabi  
[Правила](https://github.com/user-attachments/files/17792554/P21_1_Hammurabi.pdf)
## Структуры игры
В файле `Structures.h` определим основные структуры: жители, бушели пшеницы и акры земли.
```c++
struct Villagers
{
    int count = 0;                      //количество людей
    int diedOfHunger = 0;               //количество умерших от голода за год
    float diedOfHungerInPercent = 0;    //количество умерших от голода за год в процентах
    float sumOfDiedOfHunger = 0;        //сумма умерших от голода в процентах, чтобы поделить на 10
    bool isPlague = false;              //была ли чума 
    int diedOfPlague = 0;               //количество умерших от чумы за год
    int arrived = 0;                    //количество приехавших за год

    int bushelsToEatPerVillager = 0;    // = 20; CONST: годовое потребление бушелей каждым жителем
    int maxAcresToSowPerVillager = 0;   // = 10; CONST: максимум акров, который может обработать один житель в год
};

struct Bushels
{
    int count = 0;                      //количество бушелей
    int harvested = 0;                  //собрано всего за год
    int destroyedByRats = 0;            //съедено крысами за год
    int toEat = 0;                      //для поедания за год
};

struct Acres
{
    int count = 0;                      //количество акров
    int price = 0;                      //цена за 1 акр (продажа/покупка)
    int toBuy = 0;                      //сколько акров купить 
    int toSell = 0;                     //сколько акров продать 
    int toSow = 0;                      //сколько акров засадить 
    int bushelsHarvestPerAcre = 0;      //количество бушелей, которое соберется с одного акра

    float bushelsToSowPerAcre = 0;      // = 0.5f; CONST: количество бушелей для посева одного акра
};
```
## Файловый ввод/вывод через `fstream`
Функция `ReadFile` необходима для чтения файлов _GameState.txt_, хранящего состояние игры после каждого раунда, и _Const.txt_, хранящего начальные и константные значения. Вывод текщего состояния в _GameState.txt_ осуществляется с помощью функции `WriteFile`. Функция `ClearFile` необходима для обнуления файла _GameState.txt_, когда игра закончена.
```c++
void ReadFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres);
void WriteFile(string fileName, int* round, bool* gameOver, Villagers* villagers, Bushels* bushels, Acres* acres);
void ClearFile(string fileName);
```
```c++
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
```
## Класс игры 
Основные поля класса `Hammurabi` - это объекты _villagers, bushels и acres_. Они меняются под влиянием различных методов. `round` - это счетчик раундов игры. `gameOver` и `gameStarted` означают соответсвенно конец и начало игры . 
```c++
class Hammurabi
{
public:
	Hammurabi();
	void BeginGameplayLoop();

private:
    Villagers villagers;
    Bushels bushels;
    Acres acres;

    bool gameOver;
    bool gameStarted; //для проверки
    int round;

    string gamestateFile = "..\\AlgoLab1\\GameState.txt";
    string constFile = "..\\AlgoLab1\\Const.txt";

    void GetReport();
    void InputParameters();
    bool CheckInputParameters();
    void OnGameOver();

    void VillagersHungerMortality();
    void VillagersPlagueMortality();
    void VillagersGrowth();

    void BushelsHarvest();
    void BusehlsDestructionByRats();

    void BuyAcres();
    void SellAcres();
    void SowAcres();
};
```
### Инициализация и рандом
Функция `GetRandomNumber` возвращает случайное число в заданном диапазоне.  
```c++
int GetRandomNumber(int start, int end)
{
    return rand() % (end - start + 1) + start;
}
```
В начале каждой игровой сессии мы задаем для рандома сид, завязанный на текущем времени. Иначе каждую сессию `GetRandomNumber` будет выдавать один и тот же набор случайных чисел.  
Затем мы сначала читаем constFile, а потом gamestateFile, чтобы существующие значения из gamestateFile перекрыли значения из constFile. Если сохранений игры не было, то значения constFile останутся.  
Далее, если есть сохраненная игра, пользователь может выбрать, продолжить игру или начать новую.   
```c++
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
```
###  Ввод и вывод
Перед игрой и после каждого раунда игрок частично видит текущее состояние игры. 
```c++
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
        cout << "   Мы собрали " << bushels.harvested << " бушелей пшеницы, по " << acres.bushelsHarvestPerAcre << " бушелей с акра;" << endl;       }    

    if (bushels.destroyedByRats > 0)    
    {    
        cout << "   Крысы истребили " << bushels.destroyedByRats << " бушелей пшеницы;" << endl;    
    }    

    cout << "   Осталось " << bushels.count << " бушеля в амбарах;" << endl;    
    cout << "   Город сейчас занимает " << acres.count << " акров;" << endl;    
    cout << "   1 акр земли стоит сейчас " << acres.price << " бушелей." << endl;    
    cout << endl;    
}
```
Далее игрок вводит параметры игры. Если они прошли проверку, а игрок подвердил введённые значения, начинается очередной раунд.
```c++
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
```
За проверку введенных значений отвечает функция `CheckInputParameters`. Правила проверки:
- Игрок не может вводить отрицательные числа.
- Нельзя и покупать, и продавать акры земли в рамках одного раунда.
- Количество акров земли должно быть достаточно для посева и продажи.
- Количество бушелей пшеницы должно быть достаточно для покупки акров и поедания.
- Количество жителей должно быть достаточно для посева акров.
```c++
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
```
В конце игры файл состояния gamestateFile должен быть очищен. Если игрок дошел до 10 раунда, по его игре выводится оценка.
```c++
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
```
### Villagers
- VillagersHungerMortality - сколько человек умерло от голода
- VillagersPlagueMortality - сколько человек умерло от чумы
- VillagersGrowth - сколько человек приехало в город
```c++
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
```
### Bushels
- BushelsHarvest - сбор пшеницы с прошлого года
- BusehlsDestructionByRats - сколько пшеницы уничтожено крысами
```c++
void Hammurabi::BushelsHarvest() //сбор пшеницы    
{    
    bushels.count += bushels.harvested;    
}    

void Hammurabi::BusehlsDestructionByRats()    
{    
    bushels.destroyedByRats = (int)(GetRandomNumber(0, 700) * 0.0001f * bushels.count);    
    bushels.count -= bushels.destroyedByRats;    
}
```
### Acres
- BuyAcres - покупка акров земли
- SellAcres - продажа акров земли
- SowAcres - засев акров земли пшеницей 
```c++
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
```
### Игровой цикл
Игровой цикл состоит из следующей цепочки методов:
1. Если новая игра (`round` равен 0) или игра продолжается в рамках одной сессии (`gameStarted` равен true), игра
   - генерирует случайные параметры.
   - сохраняет их в файл.
   - увеличивает количество пшеницы на количество собранных бушелей.
   - выводит отчет.
   - увеличивает номер раунда.  
Иначе, если игрок запустил сохраненную игру, она просто выводит отчет. Сделано это для того, чтобы игрок между раундами не мог бесконечно перезаходить в игру, генерируя благоприятные для себя значения параметров.
2. Ввод параметров и их проверка.
3. Смертность населения от голода.
4. Смертность населения от чумы.
5. Прирост населения.
6. Продажа акров земли.
7. Покупка акров земли.
8. Засев пшеницы на следующий раунд.  
Если игрок прошёл все 10 раундов или больше 45% населения умерло от голода в прошлом раунде (`gameOver` равен true), игра заканчивается. После окончания игры игрок получает отчет за последний раунд и оценку всей игры.
```c++
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
```
