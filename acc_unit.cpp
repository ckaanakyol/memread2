#include "systemc.h"
#define INDEX_ARRAY_SIZE 16
SC_MODULE(Acc_Unit)
{
public:
	sc_in<bool> Port_CLK{"Port_CLK"};
	sc_out<int> AU_Addr{"AU_Addr"};
    sc_in<int> AU_InData{"AU_InData"};
    sc_in<int> AU_num{"AU_num"};

    SC_HAS_PROCESS(Acc_Unit);
	Acc_Unit(sc_module_name name, int ord=-1):sc_module(name), order(ord)
    {
    	SC_METHOD(send);
    	sensitive << Port_CLK;
    	SC_METHOD(receive);
    	sensitive << Port_CLK;
    	index_array = new int[INDEX_ARRAY_SIZE];
    	cycle = 0;
    	fillIndexArray(index_array);
    	cout<<"Order: " << order << endl;
    }
    ~Acc_Unit() {  }

private:
    int* index_array;
	int cycle;
	int order;

	bool decideToSend()
	{
		if(rand() % 2== 0)
			return true;
		else false;
	}

    void send()
    {
    	if(decideToSend() && cycle < INDEX_ARRAY_SIZE)
    	{
	    	int addr = index_array[cycle];
	    	AU_Addr.write(addr);
	    	cout<<"AU-" <<order<< " sent address: " <<addr <<endl;
	    	cycle++;
	    }
	    else
	    {
	    	cout<<"AU-" <<order<< " not sent address." <<endl;
	    	AU_Addr.write(INT_MIN);
	    }
    }

    void receive()
    {
    	if(AU_num.read() == order)
    	{
    		//cout<<"AU-"<<order << " read value: "<< AU_InData.read()<<endl;
    	}
    }

    void fillIndexArray(int* index_array)
    {
    	for(int i = 0; i < INDEX_ARRAY_SIZE; i++)
    		index_array[i] = i + order * 16;
    		//index_array[i] = rand() % MEM_SIZE;
    }

};