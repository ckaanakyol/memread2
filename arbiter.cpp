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
	sc_inout<int> FifoNum{"FifoNum"};
	sc_inout<int> Port_Data{"Port_Data"};

	SC_CTOR(Arbiter)
    {
    	SC_METHOD(getAddrs);
        sensitive << Port_CLK;

        SC_METHOD(arbite);
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
			values0.pop();
		}
		else if(values1.size() > 0)
		{
			Sent_Addr.write(values1.front());
			values1.pop();
		}
		else if(values2.size() > 0)
		{
			Sent_Addr.write(values2.front());
			values2.pop();
		}
		else if(values3.size() > 0)
		{
			Sent_Addr.write(values3.front());
			values3.pop();
		}
	}
};
