#pragma once

using namespace System;
using namespace System::Runtime::CompilerServices;

#include "../SampleDLL/SampleDLL.h"


namespace SampleCLI {
	[Extension]
    public ref class Math
	{
	public:
		//DLLのSumFunction()のラッパー関数
		static int SumFunction_CLI(int a, int b)
		{
			return SampleDLL::SumFunction(a, b);
		}
	};

	//Calculatorのラッパークラスの作成
	public ref class Caculator_CLI
	{
		SampleDLL::Calculator* m_calculator;
	public :
		Caculator_CLI() {
			m_calculator = new SampleDLL::Calculator();
		}
		~Caculator_CLI() {
			delete m_calculator;
		}

		int SumMethod(int a,int b)
		{
			return m_calculator->SumMethod(a, b);
		}
	};
}
