// InfoDeal.h
// Created by cch on 2020/5/31.
#pragma once
#include <vector>

#include "FilmsInfo.h"
class InfoDeal : public FilmsInfo {
   protected:
    std::vector<FilmsInfo> finfo;
    // FilmsInfo类比较函数
    static bool cmp(const FilmsInfo& a, const FilmsInfo& b);

   public:
    // 构造函数 读取信息
    InfoDeal();
    // 析构函数 保存信息
    ~InfoDeal();

    // 读取
    void fileRead();
    // 保存
    void fileSave();
    // 显示座位
    void showSeat(int n);
    // 获取当前时间
    long long get_time();
};