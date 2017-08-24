#include "systemc.h"
#include "memory.cpp"
#include "arbiter.cpp"
#include "acc_unit.cpp"
int sc_main(int argc, char* argv[])
{
	cout << "\n\nCreating Modules............\n";
	/* Instantiate Modules */
	Memory mem("main_memory");

	Arbiter arbiter("arbiter");

	Acc_Unit acc0("acc0",0);
	Acc_Unit acc1("acc1",1);
	Acc_Unit acc2("acc2",2);
	Acc_Unit acc3("acc3",3);

	sc_signal<int> addr0{"addr0"};
	sc_signal<int> addr1{"addr1"};
	sc_signal<int> addr2{"addr2"};
	sc_signal<int> addr3{"addr3"};

	sc_signal<int> sentAddr{"sentAddr"};
	sc_signal<int, SC_MANY_WRITERS> portdata{"portdata"};
	sc_signal<int> datatoau{"datatoau"};
	sc_signal<int> fifonumtomem{"fifonumtomem"};
	sc_signal<int> fifonumtoau{"fifonumtoau"};
	sc_signal<int> fifonumtoar{"fifonumtoar"};
	sc_clock clk;

	acc0.AU_Addr(addr0);
	acc1.AU_Addr(addr1);
	acc2.AU_Addr(addr2);
	acc3.AU_Addr(addr3);

	acc0.AU_InData(datatoau);
	acc1.AU_InData(datatoau);
	acc2.AU_InData(datatoau);
	acc3.AU_InData(datatoau);

	acc0.AU_num(fifonumtoau);
	acc1.AU_num(fifonumtoau);
	acc2.AU_num(fifonumtoau);
	acc3.AU_num(fifonumtoau);

	acc0.Port_CLK(clk);
	acc1.Port_CLK(clk);
	acc2.Port_CLK(clk);
	acc3.Port_CLK(clk);

	arbiter.Port_Addr0(addr0);
	arbiter.Port_Addr1(addr1);
	arbiter.Port_Addr2(addr2);
	arbiter.Port_Addr3(addr3);

	arbiter.Sent_Addr(sentAddr);

	arbiter.Ar_FifoNumToMem(fifonumtomem);
	arbiter.Ar_FifoNumToAU(fifonumtoau);
	arbiter.Ar_InData(portdata);
	arbiter.Ar_OutData(datatoau);
	arbiter.Ar_InFifoNum(fifonumtoar);

	arbiter.Port_CLK(clk);

	mem.Mem_Addr(sentAddr);
	mem.Mem_Data(portdata);
	mem.Fifo_Num(fifonumtomem);
	mem.Fifo_NumToAr(fifonumtoar);
	mem.Port_CLK(clk);

	sc_start(50000, SC_PS);
	return 0;
}