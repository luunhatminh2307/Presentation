#pragma once

using namespace System;
using namespace System::Runtime::CompilerServices;

#include "../SampleDLL/SampleDLL.h"


namespace SampleCLI {
	//SampleDLL.dll内の関数を提供するためのマネージドクラス
	[Extension]
    public ref class Math
	{
	public:
		//SampleDLL.dllのSumFunction()のラッパー関数
		static int SumFunction_CLI(int a, int b)
		{
			return SampleDLL::SumFunction(a, b);
		}
	};

	//SampleDLL.dllのCalculatorクラスのマネージドラッパークラス
	public ref class Caculator_CLI
	{
		//ネイティブCalculatorクラスのポインタ
		SampleDLL::Calculator* m_calculator;

	public :
		// コンストラクター
		Caculator_CLI() {
			// ネイティブのCalculatorインスタンスの生成
			m_calculator = new SampleDLL::Calculator();
		}

		//デストラクター
		~Caculator_CLI() {
			//ここはマネージリソースを解放
			//（現在はマネージリソースがないため、何もしない）
			
			//次にアンマネージリソースの解放をファイナライザー呼び出し
			this->!Caculator_CLI();
		}

		//ファイナライザー
		!Caculator_CLI() {
			//アンマネージリソース(ネイティブ)を解放
			if (m_calculator != nullptr) {
				delete m_calculator;
				m_calculator = nullptr;
			}
		}

		//SumMethod()のラッパー関数
		int SumMethod(int a,int b)
		{
			return m_calculator->SumMethod(a, b);
		}
	};
}
