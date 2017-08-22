#include "systemc.h"
#define MEM_SIZE 512
SC_MODULE(Memory)
{
public:
	sc_in<bool> Port_CLK{"CLK"};
	sc_in<int> Port_Addr{"addr"};
	sc_inout<int> Port_Data{"data"};
	sc_inout<int> Fifo_Num{"fifo_Num"};
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
		Port_Data.write(m_data[m_curAddr]);
    	Fifo_Num.write(fifo_num);
    	m_curAddr = Port_Addr.read();
        m_curData = Port_Data.read();
        fifo_num = Fifo_Num.read();
	}

};