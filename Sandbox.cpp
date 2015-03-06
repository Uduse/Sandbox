// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class PureVirtual
{
public:
	PureVirtual();
	~PureVirtual();

	virtual void pureVirtualFunction( int x ) const = 0;
private:

};

PureVirtual::PureVirtual()
{
}

PureVirtual::~PureVirtual()
{
}

int _tmain( int argc, _TCHAR* argv[] )
{
	PureVirtual p;
	p.pureVirtualFunction();
	return 0;
}

