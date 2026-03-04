#pragma once
#include <iostream>
#include <string>
#include "boss_worker.hpp"
#include "labor_worker.hpp"
#include "manager_worker.hpp"
#include <fstream>
#define FILENAME "empfile.txt"


class WorkerManager{
public:
    WorkerManager();
    void Show_Menu();
    void Exit_system();
    void add_worker();
    void save();
    int get_empNum();
    void emp_init();
    void Show_Emp();
    int emp_Isexist(int id);
    void Del_emp();
    void Mod_emp();
    void Find_emp();
    ~WorkerManager();

    bool m_fileIsEmpty;
    abs_worker ** m_empArray;
    int  m_empNum;
};
