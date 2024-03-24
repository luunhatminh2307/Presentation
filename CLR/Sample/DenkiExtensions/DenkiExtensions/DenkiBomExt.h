#include "DenkiBom.h"

using namespace System::Runtime::CompilerServices;
namespace DenkiExtensions {

	namespace DENKIBOM
	{
		/// <summary>BomMasterRecord�N���X�̊g�����\�b�h</summary>
		[Extension]
		public ref class BomMasterRecordExt
		{
		public:
			/// <summary>�t�B�[���h�̒l���擾</summary>
			[Extension]
			static System::String^ GetValueOrDefault(BomMasterRecord^ rec, System::String^ fieldName,
				System::String^ def)
			{
				auto fld = rec->GetField(fieldName);
				return fld == nullptr ? def : fld->GetValueStr();
			}

			/// <summary>�t�B�[���h�̒l���擾</summary>
			[Extension]
			static long  GetValueOrDefault(BomMasterRecord ^rec, System::String ^fieldName,
				long def)
			{
				auto fld = rec->GetField(fieldName);
				return fld == nullptr ? def : fld->GetValueLong();
			}

			/// <summary>�t�B�[���h�̒l���擾</summary>
			[Extension]
			static double GetValueOrDefault(BomMasterRecord ^rec, System::String ^fieldName,
				double def)
			{
				auto fld = rec->GetField(fieldName);
				return fld == nullptr ? def : fld->GetValueDouble();
			}
		};

		[Extension]
		public ref class BomMasterTableExt
		{
		public:
			/// <summary>��L�[�����擾</summary>
			[Extension]
			static System::String ^GetPrimaryKeyColumnName(BomMasterTable ^tbl, System::String ^fieldName)
			{
				auto rec = tbl->GetRecord();
				if (rec == nullptr) {
					return nullptr;
				}
				auto fld = rec->GetField(fieldName);
				if (fld == nullptr) {
					return nullptr;
				}
				return fld->GetPrimaryKeyColumnName();
			}

			/// <summary>code ��L�[�����擾</summary>
			[Extension]
			static System::String ^GetPrimaryKeyCodeColumnName(BomMasterTable ^tbl)
			{
				auto schema = GetPrimaryKeyColumnName(tbl, L"code");
				return schema == nullptr ? L"denkiowner.code" : schema;
			}
		};
	}
}

