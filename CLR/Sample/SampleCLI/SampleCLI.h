#pragma once

using namespace System;
using namespace System::Runtime::CompilerServices;

#include "../SampleDLL/SampleDLL.h"


namespace SampleCLI {
	int SumFunction2(int a, int b)
	{
		return SampleDLL::SumFunction(a, b);
	}

	[Extension]
    public ref class Math
	{
	public:
		static int SumFunction(int a, int b)
		{
			return SampleDLL::SumFunction(a, b);
		}
	};

	public ref class Caculator
	{
	public :
		static int SumMethod(int a,int b)
		{
			return SampleDLL::SumFunction(a, b);
		}
	};
}
