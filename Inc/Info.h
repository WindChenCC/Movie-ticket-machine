// Info.h
// Created by cch on 2020/6/15.
#pragma once

// 电影信息
class FilmsInfo {
   public:
    char name[30];
    bool seat[10][10] = {false};  // 座位情况 0空1满
    double price;                 // 价格
    double discount;              // 折扣
    int rest = 100;               // 剩余座位
    bool play = false;
    int playNum;  // 场次
    double sumSales = 0;

    int year;
    int month;
    int day;
    int hour;
    int minute;
};

// 用户信息
class UserInfo {
   public:
    char idName[30];
    char password[30];
    bool vip = false;
};

// 票信息
class Ticket {
   public:
    char name[30];
    int seat[2] = {0};
    double price;
    int playNum;
    bool isBest = false;
    bool play = false;

    int year;
    int month;
    int day;
    int hour;
    int minute;
};