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
}