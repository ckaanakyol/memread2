#include "systemc.h"
#include "memory.cpp"
#include "arbiter.cpp"
#include "acc_unit.cpp"
int sc_main(int argc, char* argv[])
{
	cout << "\n\nCreating Modules............\n";
	/* Instantiate Modules */
	Memory mem("main_memory");
	Acc_Unit acc_unit0("acc0",0);
	Acc_Unit acc_unit1("acc1",1);
	Acc_Unit acc_unit2("acc2",2);
	Acc_Unit acc_unit3("acc3",3);

	Arbiter arbiter("arbiter");


	sc_start();
	return 0;
}