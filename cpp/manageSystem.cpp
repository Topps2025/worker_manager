#include "manageSystem.hpp"
#include <iostream>
#include <string>


WorkerManager::WorkerManager(){
	std::ifstream ifs;
	ifs.open(FILENAME,std::ios::in);
// 文件不存在
	if (!ifs.is_open())
	{
		std::cout<<"文件不存在.\n";
		this->m_fileIsEmpty = true;
		this->m_empNum = 0;
		this->m_empArray= NULL;
		// 初始化成员属性
		ifs.close();
		return;
	}

// 文件为空的情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout<<"文件为空\n";
		this->m_fileIsEmpty = true;
		this->m_empNum = 0;
		this->m_empArray= NULL;
	// 初始化成员属性
		ifs.close();
		return;
	}
	
	this->m_empNum = this->get_empNum();
	this->m_fileIsEmpty = false;
	std::cout << "职工人数为:"<<m_empNum<<std::endl;
// 初始化职工，将硬盘里的职工数据读到内存中
	this->m_empArray = new abs_worker*[m_empNum];
	emp_init();
	for (int i = 0; i < m_empNum; i++)
	{
		if (m_empArray[i] == NULL)
		{
			std::cout<<"第"<<i+1<<"个职工信息初始化失败\n";
		}
		
		std::cout<<"职工编号："<<m_empArray[i]->m_ID
		<<"\t职工姓名："<<m_empArray[i]->m_name
		<<"\t部门编号："<<m_empArray[i]->m_deptID
		<<std::endl;
	}
	
}
WorkerManager::~WorkerManager(){
	if(m_empArray != NULL){
		delete[] m_empArray;
		m_empArray = NULL;
		//释放空间并将数组指针置空
	}
}
void WorkerManager::Show_Menu(){
    std::cout << "********************************************" << std::endl;
	std::cout << "*********  欢迎使用职工管理系统！ **********" << std::endl;
	std::cout << "*************  0.退出管理程序  *************" << std::endl;
	std::cout << "*************  1.增加职工信息  *************" << std::endl;
	std::cout << "*************  2.显示职工信息  *************" << std::endl;
	std::cout << "*************  3.删除离职职工  *************" << std::endl;
	std::cout << "*************  4.修改职工信息  *************" << std::endl;
	std::cout << "*************  5.查找职工信息  *************" << std::endl;
	std::cout << "*************  6.按照编号排序  *************" << std::endl;
	std::cout << "*************  7.清空所有文档  *************" << std::endl;
	std::cout << "********************************************" << std::endl;
	std::cout << std::endl;
}
void WorkerManager::Exit_system(){
	system("pause");
	exit(0);
}

// save()依次访问m_empArray中的元素，保存所有职工的信息到File中
void WorkerManager::save(){
	std::ofstream ofs;
	ofs.open(FILENAME,std::ios::out);

	for (int i = 0; i < this->m_empNum; i++)
	{
		ofs << this->m_empArray[i]->m_ID<<" "
		<<this->m_empArray[i]->m_name<<" "
		<<this->m_empArray[i]->m_deptID
		<<std::endl;
	}
	ofs.close();
}

void WorkerManager::add_worker(){
	// 要添加多少人————即数组中有多少元素
	int add_num = 0;
	std::cout<<"请输入要添加的人数\n";
	std::cin >>add_num;

	if (add_num > 0)
	{
		// 计算新空间的大小
		int new_size = this->m_empNum + add_num;
		
		// 在堆区开辟 元素数量为new_num的 父类指针数组，用 父类指针的指针 newspace 来维护这个指针的数组
		abs_worker ** newspace = new abs_worker*[new_size];

		// 将旧空间的原内容放入新空间
		if(m_empArray != NULL){
			for (int i = 0; i < m_empNum; i++)
			{
				newspace[i] = m_empArray[i];
			}
			
		}

		// 释放旧空间，更新 m_emparray 指针，使其指向新空间;
		delete[] m_empArray;
		m_empArray = newspace;

		//添加员工
		for(int i = 0;i < add_num; i++){
			int id;
			std::string name;
			// REMEMBER: newspace 是指向 元素为指针的数组 的指针
			abs_worker * worker = NULL;
			
			//利用多态，我们可以 用父类指针 指向 子类对象
			//该指针暂时置为空，因为我们还不知道 添加的员工 是哪一个 子类
			std::cout<<"请输入第"<<i+1<<"名员工的姓名\n";
			std::cin>>name;
			// 添加输入检查，防止编号重复
			while (1)
			{
				std::cout<<"请输入第"<<i+1<<"名员工的编号\n";
				std::cin>>id;
				if (emp_Isexist(id) != -1)
				{
					std::cout<<"该编号的员工已存在,请重新输入\n";
				}
				else break;
			} 
			
			int dselect;
			do
			{
				system("cls");
				std::cout<<"请输入第"<<i+1<<"名员工的工种\n";
				std::cout<<"1,工人\n";
				std::cout<<"2,经理\n";
				std::cout<<"3,老板\n";

				std::cin>>dselect;
				switch (dselect)
				{
				case 1:
					worker = new labor_worker(id,1,name);
					break;
				case 2:
					worker = new manager_worker(id,2,name);
					break;
				case 3:
					worker = new boss_worker(id,3,name);
					break;
				
				default:
					std::cout<<"工种输入有错误，请重新输入\n";
					break;
				}
			} while (dselect!=1&&dselect!=2&&dselect!=3);
		// while循环保证输入的数字符合要求
		// 将worker指针的副本 拷入 newspace指向的 指针数组
		newspace[m_empNum+i] = worker;
		}

		// 更新 m_empNum
		m_empNum = new_size;

		// 更新m_fileIsEmpty状态
		m_fileIsEmpty = false;

		std::cout<<"成功添加 "<<add_num<<" 名员工\n"<<std::endl;

		// 将数据存入硬盘中
		this->save();
	}
	else{
		std::cout<<"输入有误\n";
	}
	
	system("pause");
	system("cls");

}
int WorkerManager::get_empNum(){
	std::ifstream ifs;
	ifs.open(FILENAME,std::ios::in);
	int id,d_id,empNum = 0;
	std::string name;
	while (ifs >> id && ifs >> name && ifs >> d_id)
	{
		empNum++;
	}
	ifs.close();
	return empNum;
}
// 根据File内容初始化职工信息
void WorkerManager::emp_init(){

	int id,did;
	std::string name;
	std::ifstream ifs;
	ifs.open(FILENAME,std::ios::in);
	int index = 0;// 在循环外部将index初始化
	while (ifs >> id && ifs >> name && ifs >>did)
	{
		// int index = 0;
		// 错误：每次都将index初始化为0，导致只有m_empArray[i]被赋值
		// m_empArray[1..m_empNum-1] 都是未初始化野指针。
		// 构造函数里随后用 for (i=0; i<m_empNum; i++) 去访问 m_empArray[i]->...，一旦访问到未初始化元素就会段错误（Segmentation fault）
		abs_worker* worker =NULL;
		switch (did)
		{
		case 1:
			worker = new labor_worker(id,did,name);
			break;
		case 2:
			worker = new manager_worker(id,did,name);
			break;
		case 3:
			worker = new boss_worker(id,did,name);
			break;					
		default:
			break;
		}
		m_empArray[index] = worker;
		index++;
	}
	
	ifs.close();
}
void WorkerManager::Show_Emp(){
	if (m_fileIsEmpty == true)
	{
		std::cout<<"文件为空或不存在\n";
		return;
	}
	for (int i = 0; i < m_empNum; i++)
	{
		m_empArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}
int WorkerManager::emp_Isexist(int id){
	for (int i = 0; i < m_empNum; i++)
	{
		if (m_empArray[i]->m_ID == id)
		{
			return i;
		}
	}
	return -1;
}

void WorkerManager::Del_emp(){
	if (m_empNum == 0)
	{
		std::cout<<"员工名单为空,删除失败\n";
		return;
	}
	std::cout<<"请输入要删除的员工的编号\n";
	int index,id;
	std::cin>>id;
	index = emp_Isexist(id);
	if (index == -1)
	{
		std::cout<<"输入有误,删除的员工不存在，删除失败\n";
		return;
	}
	delete m_empArray[index];
	for (int i = index; i < m_empNum - 1; i++)
	{
		m_empArray[i] = m_empArray[i+1];
		// 取缔被删除的元素，后面的元素依次往前排.
	}
	m_empNum--;
	this->save();
	if (m_empNum == 0)
	{
		m_fileIsEmpty = true;
	}
	
	std::cout<<"删除成功\n";
	system("cls");
}

void WorkerManager::Mod_emp(){
	if (m_fileIsEmpty == true)
	{
		std::cout<<"员工名单为空,修改失败\n";
		return;
	}
	int new_id,dselect,id,index;
	std::string new_name;

	// 判断编号是否存在，若存在，找到index下标
	while (1)
	{
		std::cout<<"请输入要修改员工的编号:\n";
		std::cin>>id;
		index = this->emp_Isexist(id);
		if (index == -1)
		{
			std::cout<<"该编号不存在,请重新输入\n";
			continue;// 直到index的下标正常为止
		}
		else break;			
	}
	std::cout<<"原信息如下:\n";
	m_empArray[index]->showInfo();
	
	// 创建临时指针，以待其副本被存入数组
	abs_worker * worker = NULL;//暂时置空，因为还不知道修改后的职工指针类型

	//
	std::cout<<"请输入修改后的姓名\n";
	std::cin>>new_name;
	
	// 添加输入检查，防止编号重复
	while (1)
	{
		std::cout<<"请输入修改后的编号\n";
		std::cin>>new_id;
		if (emp_Isexist(new_id) != -1 && new_id != id)// 如果输入的新ID已经存在，且不是与旧ID重复，则重新输入
		{
			std::cout<<"该编号的员工已存在,请重新输入\n";
		}
		else break;
	} 
			
	do
	{
		std::cout<<"请输入修改后的工种\n";
		std::cout<<"1,工人\n";
		std::cout<<"2,经理\n";
		std::cout<<"3,老板\n";
		std::cin>>dselect;
		switch (dselect)
		{
		case 1:
			worker = new labor_worker(new_id,1,new_name);
			break;
		case 2:
			worker = new manager_worker(new_id,2,new_name);
			break;
		case 3:
			worker = new boss_worker(new_id,3,new_name);
			break;
		default:
			std::cout<<"工种输入有错误，请重新输入\n";
			break;
		}
	} while (dselect!=1&&dselect!=2&&dselect!=3);


	// 先释放原来指针指向的空间
	delete m_empArray[index];
	// 替换数组元素，使其为新指针
	m_empArray[index] = worker;
	// 将修改后的数据保存
	this->save();
}