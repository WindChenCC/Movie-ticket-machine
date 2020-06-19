// Deal.h
// Created by cch on 2020/6/16.
#pragma once
#include <string>
#include <vector>

#include "Info.h"

class Deal {
   public:
    std::vector<FilmsInfo> finfo;

    // ���캯����ȡ��Ӱ��Ϣ
    Deal();
    // �������������Ӱ��Ϣ
    ~Deal();

    // ����<<
    friend std::ostream& operator<<(std::ostream& os, const FilmsInfo& film);
    // ��Ӱ����
    static bool fcmp(const FilmsInfo& a, const FilmsInfo& b);
    // y/n�ж�
    bool yesOrNo();
    // �Ƚ�ʱ��
    bool cmpTime(const FilmsInfo& film);
    // �ȴ�
    void wait();
    // �����Ӱ��Ϣ
    void showFInfo(int n = 0);
    // ��ȡ��Ӱ��Ϣ
    void filmRead();
    // �����Ӱ��Ϣ
    void filmSave();
};