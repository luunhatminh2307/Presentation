#pragma once
#ifdef SAMPLEDLL_EXPORTS
#define SAMPLEDLL_API __declspec(dllexport)
#else
#define SAMPLEDLL_API __declspec(dllimport)
#endif

namespace SampleDLL
{
	SAMPLEDLL_API int SumFunction(int a, int b);

	class SAMPLEDLL_API Calculator {
	public:
		static int SumMethod(int a, int b);
	};
}
