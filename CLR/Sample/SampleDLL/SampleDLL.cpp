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


    //�N���X�̏ꍇ�AP/Invoke�̂��߂̕��@
    //��1�GC#���́A���ڃ������Ǘ����s���K�v�̏ꍇ�A�I�u�W�F�N�g�̍쐬�A�g�p�A�j���̊֐��̍쐬
    //�I�u�W�F�N�g�쐬�֐�
    SAMPLEDLL_API Calculator* CreateCalculator()
    {
        return new Calculator();
    }
    //�g�p�֐�
    SAMPLEDLL_API int CalculatorSum(Calculator* calculator, int a, int b)
    {
        return calculator->SumMethod(a, b);
    }
    //�j���֐�
    SAMPLEDLL_API void DeleteCalculator(Calculator* calculator)
    {
        delete calculator;
    }

    //��2�GC#���́A���ڃ������Ǘ����s���K�v���Ȃ��ꍇ�A�I�u�W�F�N�g�̍쐬�Ɣj���̎菇���ȗ��ł���B
    SAMPLEDLL_API int CalculatorSum(int a, int b)
    {
        auto calculator = new Calculator();
        auto res = calculator->SumMethod(a, b);
        delete calculator;
        return res;
    }
}