#pragma once
#include <iostream>
#include <string>
#include "abs_worker.hpp"

class labor_worker:public abs_worker{
public:
    labor_worker(int ID,int dID,std::string name);
    int get_ID()override;
    std::string get_deptName()override;
    int get_deptID()override;
    void showInfo()override;
};
