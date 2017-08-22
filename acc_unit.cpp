#include "systemc.h"
#define INDEX_ARRAY_SIZE 16
SC_MODULE(Acc_Unit)
{
public:
	sc_in<bool> Port_CLK{"Port_CLK"};
	sc_out<int> Port_MemAddr{"Port_MemAddr"};
    sc_in<int> Port_MemData{"Port_MemData"};
    sc_in<int> AU_num{"AU_num"};

    SC_HAS_PROCESS(Acc_Unit);
	Acc_Unit(sc_module_name name, int ord=-1):sc_module(name), order(ord)
    {
    	SC_METHOD(send);
    	sensitive << Port_CLK.neg();
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
		if(rand() % 4  == 0)
			return true;
		else false;
	}

    void send()
    {
    	if(decideToSend())
    	{
	    	int addr = index_array[cycle];
	    	Port_MemAddr.write(addr);
	    }
    }

    void receive()
    {
    	if(AU_num.read() == order)
    	{
    		cout<<"AU-"<<order << " read value: "<< Port_MemData.read()<<endl;
    	}
    }

    void fillIndexArray(int* index_array)
    {
    	for(int i = 0; i < INDEX_ARRAY_SIZE; i++)
    		index_array[i] = i;
    		//index_array[i] = rand() % MEM_SIZE;
    }

};