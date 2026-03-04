#pragma once
#include <iostream>
#include <string>
#include "abs_worker.hpp"

class boss_worker:public abs_worker{
public:
    boss_worker(int ID,int dID,std::string name);
    int get_ID()override;
    void showInfo()override;
    std::string get_deptName()override;
    int get_deptID()override;
};
