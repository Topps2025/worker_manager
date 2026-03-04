#pragma once
#include <iostream>
#include <string>

class abs_worker{
public:
    virtual int get_ID() = 0;
    virtual int get_deptID() = 0;
    virtual std::string get_deptName() = 0;
    virtual void showInfo() = 0;

    int m_ID;//员工编号
    std::string m_name;//员工姓名
    int m_deptID;//所在部门编号
};


