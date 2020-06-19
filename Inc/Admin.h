// Admin.h
// Created by cch on 2020/6/15.
#pragma once
#include <vector>

#include "Deal.h"

class Admin {
   private:
    Deal deal;
    // 获取string电影日期
    std::string strDate(const FilmsInfo& film);

   public:
    void menuChoice();
    // 添加
    void add();
    // 显示
    void showFInfo();
    // 修改
    void change();
    // 删除
    void del();
    // 统计
    void count();
};