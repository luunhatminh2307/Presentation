#pragma once
#ifdef SAMPLEDLL_EXPORTS
#define SAMPLEDLL_API __declspec(dllexport)
#else
#define SAMPLEDLL_API __declspec(dllimport)
#endif

namespace SampleDLL
{
	//�֐��ƃN���X���G�N�X�|�[�g

	SAMPLEDLL_API int SumFunction(int a, int b);

	class SAMPLEDLL_API Calculator {
	public:
		int SumMethod(int a, int b);
	};
}
