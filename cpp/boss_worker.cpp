#include "boss_worker.hpp"

int boss_worker::get_ID(){
	return m_ID;
}
int boss_worker::get_deptID(){
	return m_deptID;
}
std::string boss_worker::get_deptName(){
	return std::string("老板");
}
void boss_worker::showInfo(){
	std::cout<<"职工编号:"<<this->m_ID
	<<"\t姓名:"<<this->m_name
	<<"\t岗位:"<<this->get_deptName()
	<<std::endl;
}
boss_worker::boss_worker(int ID,int dID,std::string name){
	this->m_ID = ID;
	this->m_deptID = dID;
	this->m_name = name;
}