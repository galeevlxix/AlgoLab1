#pragma once

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