#include "manageSystem.hpp"

#ifdef _WIN32  // 仅在 Windows 系统下生效
#include <windows.h> // 或者使用 <cstdlib> 配合 system()
#endif

void test01(){
    abs_worker * ptr = nullptr;
    ptr = new manager_worker(1,55,"TOM");
    ptr->showInfo();
    delete ptr;
    
    ptr = new labor_worker(2,56,"JERRY");
    ptr->showInfo();
    delete ptr;
    
    ptr = new boss_worker(3,66,"TOPPS");
    ptr->showInfo();
    delete ptr;
}
int main(){

#ifdef _WIN32
    // 方式 A: 使用 system 命令 (简单直观)
    system("chcp 65001 > nul"); // > nul 是为了不显示切换成功的提示信息

    // 方式 B: 使用 Windows API (更底层，不弹出命令行窗口)
    // SetConsoleOutputCP(CP_UTF8);
#endif

    WorkerManager wm;
	int choice = 0;
	while(true){
	wm.Show_Menu();
	std::cin>>choice;
	switch(choice){
	case 0:
		std::cout<<"欢迎下次使用！\n";
		wm.Exit_system();
		break;
	case 1:
		wm.add_worker();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		system("cls");
		break;
		}
	}
    return 0;
}