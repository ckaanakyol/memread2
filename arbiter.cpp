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
    	SC_METHOD(arbite);
        sensitive << Port_CLK;
    }
    ~Arbiter() {  }

private:
	std::queue <int> values0;
	std::queue <int> values1;
	std::queue <int> values2;
	std::queue <int> values3;

	void arbite()
	{
		
	}
};
