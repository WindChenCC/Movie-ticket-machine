// Deal.h
// Created by cch on 2020/6/16.
#pragma once
#include <string>
#include <vector>

#include "Info.h"

class Deal {
   public:
    std::vector<FilmsInfo> finfo;

    // 构造函数读取电影信息
    Deal();
    // 析构函数保存电影信息
    ~Deal();

    // 重载<<
    friend std::ostream& operator<<(std::ostream& os, const FilmsInfo& film);
    // 电影排序
    static bool fcmp(const FilmsInfo& a, const FilmsInfo& b);
    // y/n判断
    bool yesOrNo();
    // 比较时间
    bool cmpTime(const FilmsInfo& film);
    // 等待
    void wait();
    // 输出电影信息
    void showFInfo(int n = 0);
    // 读取电影信息
    void filmRead();
    // 保存电影信息
    void filmSave();
};