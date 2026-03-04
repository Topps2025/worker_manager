#include "labor_worker.hpp"
int labor_worker::get_ID(){
	return m_ID;
}
int labor_worker::get_deptID(){
	return m_deptID;
}
std::string labor_worker::get_deptName(){
	return std::string("员工");
}   
void labor_worker::showInfo(){
	std::cout<<"职工编号:"<<this->m_ID
	<<"\t姓名:"<<this->m_name
	<<"\t岗位:"<<this->get_deptName()
	<<std::endl;
}

labor_worker::labor_worker(int ID,int dID,std::string name){
	this->m_ID = ID;
	this->m_deptID = dID;
	this->m_name = name;
}
