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
    bool play = false;            // 放映情况
    int playNum;                  // 场次
    double sumSales = 0;          // 累计销售额

    int year;
    int month;
    int day;
    int hour;
    int minute;
};

// 用户信息
class UserInfo {
   public:
    char idName[30];    // 用户名
    char password[30];  // 密码
    bool vip = false;   // vip
};

// 票信息
class Ticket {
   public:
    char name[30];        // 电影名
    int seat[2] = {0};    // 座位坐标
    double price;         // 票价
    int playNum;          // 场次
    bool isBest = false;  // 是否最佳区
    bool play = false;    // 放映情况

    int year;
    int month;
    int day;
    int hour;
    int minute;
};