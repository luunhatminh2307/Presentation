#include "StdAfx.h"
#include "SampleDLL.h"

namespace SampleDLL
{
    int SumFunction(int a, int b) {
        return a + b;
    }

    int Calculator::SumMethod(int a, int b) {
        return a + b;
    }


    //クラスの場合、P/Invokeのための方法
    //案1；C#側は、直接メモリ管理を行う必要の場合、オブジェクトの作成、使用、破棄の関数の作成
    //オブジェクト作成関数
    SAMPLEDLL_API Calculator* CreateCalculator()
    {
        return new Calculator();
    }
    //使用関数
    SAMPLEDLL_API int CalculatorSum(Calculator* calculator, int a, int b)
    {
        return calculator->SumMethod(a, b);
    }
    //破棄関数
    SAMPLEDLL_API void DeleteCalculator(Calculator* calculator)
    {
        delete calculator;
    }

    //案2；C#側は、直接メモリ管理を行う必要がない場合、オブジェクトの作成と破棄の手順を省略できる。
    SAMPLEDLL_API int CalculatorSum(int a, int b)
    {
        auto calculator = new Calculator();
        auto res = calculator->SumMethod(a, b);
        delete calculator;
        return res;
    }
}