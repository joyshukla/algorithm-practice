#include<iostream>
#include<bitset>
using namespace std;

int main()
{
	enum Flag {CF, PF, ZF, SD, IF, numFlags};
	// store processor flags
	bitset<numFlags> procFlags;
	procFlags.set(CF);
	procFlags.set(ZF);
	procFlags.set(IF);
	cout << "flags are : " << procFlags << endl;
	cout << "flipping the bits : " << procFlags.flip() << endl;
	cout << "shifted left by 1 : " << (procFlags << 1) << endl;
	cout << "shifted right by 2 : " << (procFlags >> 2) << endl;
	
	return 1;
}
