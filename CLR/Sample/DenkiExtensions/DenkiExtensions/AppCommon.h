#pragma once
#include "stdafx.h"

namespace DenkiExtensions
{
	inline std::wstring toWStr(System::String ^str)
	{
		msclr::interop::marshal_context context;
		return context.marshal_as<const TCHAR *>(str);
	}

    inline std::string toStr(System::String ^str)
    {
        auto wstr = toWStr(str);
        size_t len = wstr.size() + 1;
        char *charStr = new char[len];
        wcstombs_s(nullptr, charStr, len, wstr.c_str(), len);
        return charStr;
    }

    inline bool isNull(System::String ^str)
    {
        // == nullptrで nullチェックできないため
        return System::Object::ReferenceEquals(str, nullptr);
    }
}

