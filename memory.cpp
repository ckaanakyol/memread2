#include "systemc.h"
#define MEM_SIZE 512
SC_MODULE(Memory)
{
public:
	sc_in<bool> Port_CLK{"CLK"};
	sc_in<int> Mem_Addr{"addr"};
	sc_out<int> Mem_Data{"data"};
	sc_in<int> Fifo_Num{"fifo_Num"};
	sc_out<int> Fifo_NumToAr{"Fifo_NumToAr"};
	SC_CTOR(Memory)
    {
        SC_METHOD(execute);
        sensitive << Port_CLK;
        m_data = new int[MEM_SIZE];
        m_curAddr = 0;
        m_curData = 0;
        fifo_num = -1;
    }

    ~Memory() {  }

private:

    int* m_data;
    int m_curAddr;
    int m_curData;
    int fifo_num;

	void execute()
	{
    	m_curAddr = Mem_Addr.read();
		Mem_Data.write(m_data[m_curAddr]);
    	Fifo_NumToAr.write(fifo_num);
        fifo_num = Fifo_Num.read();
	}

};