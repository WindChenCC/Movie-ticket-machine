// Admin.h
// Created by cch on 2020/6/15.
#pragma once
#include <vector>

#include "Deal.h"

class Admin {
   private:
    Deal deal;
    // ��ȡstring��Ӱ����
    std::string strDate(const FilmsInfo& film);

   public:
    void menuChoice();
    // ���
    void add();
    // ��ʾ
    void showFInfo();
    // �޸�
    void change();
    // ɾ��
    void del();
    // ͳ��
    void count();
};