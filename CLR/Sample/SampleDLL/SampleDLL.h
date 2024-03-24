#pragma once
#ifdef SAMPLEDLL_EXPORTS
#define SAMPLEDLL_API __declspec(dllexport)
#else
#define SAMPLEDLL_API __declspec(dllimport)
#endif

namespace SampleDLL
{
	//関数とクラスをエクスポート

	SAMPLEDLL_API int SumFunction(int a, int b);

	class SAMPLEDLL_API Calculator {
	public:
		int SumMethod(int a, int b);
	};
}
