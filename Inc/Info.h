// Info.h
// Created by cch on 2020/6/15.
#pragma once

// ��Ӱ��Ϣ
class FilmsInfo {
   public:
    char name[30];
    bool seat[10][10] = {false};  // ��λ��� 0��1��
    double price;                 // �۸�
    double discount;              // �ۿ�
    int rest = 100;               // ʣ����λ
    bool play = false;            // ��ӳ���
    int playNum;                  // ����
    double sumSales = 0;          // �ۼ����۶�

    int year;
    int month;
    int day;
    int hour;
    int minute;
};

// �û���Ϣ
class UserInfo {
   public:
    char idName[30];    // �û���
    char password[30];  // ����
    bool vip = false;   // vip
};

// Ʊ��Ϣ
class Ticket {
   public:
    char name[30];        // ��Ӱ��
    int seat[2] = {0};    // ��λ����
    double price;         // Ʊ��
    int playNum;          // ����
    bool isBest = false;  // �Ƿ������
    bool play = false;    // ��ӳ���

    int year;
    int month;
    int day;
    int hour;
    int minute;
};