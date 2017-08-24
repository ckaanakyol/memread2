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
        fill(m_data);
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

    void fill(int* m_data)
    {
    	for(int i = 0 ; i < MEM_SIZE; i++)
    		m_data[i]=i;
    }

	void execute()
	{
    	m_curAddr = Mem_Addr.read();
        fifo_num = Fifo_Num.read();

        if(m_curAddr == INT_MIN && fifo_num == -1)
        {
        	Mem_Data.write(INT_MIN);
	        Fifo_NumToAr.write(-1);
        }
        else
        {
			Mem_Data.write(m_data[m_curAddr]);
	        Fifo_NumToAr.write(fifo_num);
        	cout<< "Mem - Addr: " << m_curAddr << " fifo_num: " << fifo_num << endl;
        }

	}

};