#include "manager_worker.hpp"

int manager_worker::get_ID(){
	return m_ID;
}
int manager_worker::get_deptID(){
	return m_deptID;
}
std::string manager_worker::get_deptName(){
	return std::string("经理");
}

void manager_worker::showInfo(){
	std::cout<<"职工编号:"<<this->m_ID
	<<"\t姓名:"<<this->m_name
	<<"\t岗位:"<<this->get_deptName()
	<<std::endl;
}

manager_worker::manager_worker(int ID,int dID,std::string name){
	this->m_ID = ID;
	this->m_deptID = dID;
	this->m_name = name;
}