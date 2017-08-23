#include "systemc.h"
using namespace std;
#include <queue>
SC_MODULE(Arbiter)
{
public:
	sc_in<bool> Port_CLK{"Port_CLK"};
	sc_in<int> Port_Addr1{"addr1"};
	sc_in<int> Port_Addr2{"addr2"};
	sc_in<int> Port_Addr3{"addr3"};
	sc_in<int> Port_Addr0{"addr0"};
	sc_out<int> Sent_Addr{"sent_addr"};
	sc_out<int> Ar_FifoNumToMem{"Ar_FifoNumToMem"};
	sc_out<int> Ar_FifoNumToAU{"Ar_FifoNumToAU"};
	sc_in<int> Ar_InData{"Ar_InData"};
	sc_in<int> Ar_InFifoNum{"Ar_InFifoNum"};
	sc_out<int> Ar_OutData{"Ar_InData"};

	SC_CTOR(Arbiter)
    {
    	SC_METHOD(getAddrs);
        sensitive << Port_CLK;

        SC_METHOD(arbite);
        sensitive << Port_CLK;

        SC_METHOD(getData);
        sensitive << Port_CLK;
    }
    ~Arbiter() {  }

private:
	std::queue <int> values0;
	std::queue <int> values1;
	std::queue <int> values2;
	std::queue <int> values3;

	void getAddrs()
	{
		if(Port_Addr0.read() != INT_MIN) { values0.push(Port_Addr0.read()) ;} 
		if(Port_Addr1.read() != INT_MIN) { values1.push(Port_Addr1.read()) ;} 
		if(Port_Addr2.read() != INT_MIN) { values2.push(Port_Addr2.read()) ;} 
		if(Port_Addr3.read() != INT_MIN) { values3.push(Port_Addr3.read()) ;}
	}

	void arbite()
	{
		if(values0.size() > 0)
		{
			Sent_Addr.write(values0.front());
			cout<< "Arbite-0 addr: " << values0.front() << endl;
			values0.pop();
			Ar_FifoNumToMem.write(0);

		}
		else if(values1.size() > 0)
		{
			Sent_Addr.write(values1.front());
			cout<< "Arbite-1 addr: " << values1.front() << endl;
			values1.pop();
			Ar_FifoNumToMem.write(1);
		}
		else if(values2.size() > 0)
		{
			Sent_Addr.write(values2.front());
			cout<< "Arbite-2 addr: " << values2.front() << endl;
			values2.pop();
			Ar_FifoNumToMem.write(2);
		}
		else if(values3.size() > 0)
		{
			Sent_Addr.write(values3.front());
			cout<< "Arbite-3 addr: " << values3.front() << endl;
			values3.pop();
			Ar_FifoNumToMem.write(3);
		}
	}

	void getData()
	{	
		int data = Ar_OutData.read();
		int fifo_order = Ar_InFifoNum.read();
		Ar_FifoNumToAU.write(fifo_order);
		Ar_OutData.write(data);
		//cout<< "Arbiter fifo_order: " << fifo_order << endl; 
	}
};
