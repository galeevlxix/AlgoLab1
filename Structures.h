#pragma once

struct Villagers
{
    int count = 0;                      //���������� �����
    int diedOfHunger = 0;               //���������� ������� �� ������ �� ���
    float diedOfHungerInPercent = 0;    //���������� ������� �� ������ �� ��� � ���������
    float sumOfDiedOfHunger = 0;        //����� ������� �� ������ � ���������, ����� �������� �� 10
    bool isPlague = false;              //���� �� ���� 
    int diedOfPlague = 0;               //���������� ������� �� ���� �� ���
    int arrived = 0;                    //���������� ���������� �� ���

    int bushelsToEatPerVillager = 0;    // = 20; CONST: ������� ����������� ������� ������ �������
    int maxAcresToSowPerVillager = 0;   // = 10; CONST: �������� �����, ������� ����� ���������� ���� ������ � ���
};

struct Bushels
{
    int count = 0;                      //���������� �������
    int harvested = 0;                  //������� ����� �� ���
    int destroyedByRats = 0;            //������� ������� �� ���
    int toEat = 0;                      //��� �������� �� ���
};

struct Acres
{
    int count = 0;                      //���������� �����
    int price = 0;                      //���� �� 1 ��� (�������/�������)
    int toBuy = 0;                      //������� ����� ������ 
    int toSell = 0;                     //������� ����� ������� 
    int toSow = 0;                      //������� ����� �������� 
    int bushelsHarvestPerAcre = 0;      //���������� �������, ������� ��������� � ������ ����

    float bushelsToSowPerAcre = 0;      // = 0.5f; CONST: ���������� ������� ��� ������ ������ ����
};