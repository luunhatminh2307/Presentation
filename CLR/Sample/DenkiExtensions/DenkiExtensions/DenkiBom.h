#pragma once
#include "stdafx.h"
#include <DENKIBOM.h>
#include <DENKIPM.h>
#include "AppCommon.h"

namespace DenkiExtensions {

	namespace DENKIBOM
	{
		/// <summary>レコードの構成要素を表すクラス</summary>
		public ref class BomMasterField
		{
		public:
			DenkiBomMasterField *m_fld;

			BomMasterField(DenkiBomMasterField *fld) :m_fld(fld) {}
			~BomMasterField() {
				if (m_fld != nullptr) {
					delete m_fld;
					m_fld = nullptr;
				}
			}

			/// <summary>値を設定</summary>
			bool SetValue(System::String ^value) {
				return m_fld->SetValue(toWStr(value).c_str());
			}

			/// <summary>主キー名を取得</summary>
			System::String^ GetPrimaryKeyColumnName()
			{
				LPCWSTR	schema;
				m_fld->GetSchema(schema);
				return schema ? gcnew System::String(schema) : nullptr;
			}
			/// <summary>割り付け属性名を取得</summary>
			System::String^ GetAttributeName()
			{
				LPCWSTR	name;
				m_fld->GetAttributeName(name);
				return name ? gcnew System::String(name) : nullptr;
			}
			/// <summary>値を取得</summary>
			long GetValueLong() { long v; m_fld->GetValue(v); return v;};
			double GetValueDouble() { double v; m_fld->GetValue(v); return v; };
			System::String^ GetValueStr() { 
				LPSTR v = nullptr; 
				m_fld->GetValue(v); 
				if (v) {
					auto str = gcnew System::String(v);
					m_fld->FreeString(v);
					return str;
				}
				return nullptr;
			};
		};


		/// <summary>各表の構成要素郡を表すクラス</summary>
		public ref class BomMasterRecord
		{
			DenkiBomMasterRecord *m_rec;

		public:
			BomMasterRecord(DenkiBomMasterRecord *rec) : m_rec(rec) {}
			~BomMasterRecord() {
				if (m_rec != nullptr) {
					delete m_rec;
					m_rec = nullptr;
				}
			}

			/// <summary>フィールドを取得</summary>
			BomMasterField^ GetField(System::String ^name) {
				auto fld = new DenkiBomMasterField();
				auto ok = m_rec->GetField(*fld, toStr(name).c_str());
				return ok ? gcnew BomMasterField(fld) : nullptr;
			}
			/// <summary>フィールドを取得</summary>
			BomMasterField^ GetField(int index)
			{
				auto fld = new DenkiBomMasterField();
				auto ok = m_rec->GetField(*fld, index);
				return ok ? gcnew BomMasterField(fld) : nullptr;
			}
			/// <summary>フィールド数を取得</summary>
			int GetFieldCount() { return m_rec->GetFieldCount(); };

			/// <summary>レコードの内容をクリア</summary>
			void ClearValue() { m_rec->ClearValue(); }
			/// <summary>レコードの内容を登録</summary>
			int Entry() { return m_rec->Entry(); }
			/// <summary>レコードの内容のデータを削除</summary>
			int Delete() { return m_rec->Delete(); }
		};

		/// <summary>検索処理で返されるデータ(レコード)の集合体を表すクラス</summary>
		public ref class BomMasterRecordSet
		{
			DenkiBomMasterRecordset *m_rsData;

		public:
			BomMasterRecordSet(DenkiBomMasterRecordset *rsData) : m_rsData(rsData) {}
			~BomMasterRecordSet() {

			}
			/// <summary>カーソルが既に最後行になっているか？</summary>
			bool IsEOF() { return m_rsData->IsEOF(); }
			/// <summary>カーソルが既に先頭になっているか？</summary>
			bool IsBOF() { return m_rsData->IsBOF(); }
			/// <summary>カーソルを先頭に移す</summary>
			bool MoveFirst() { return m_rsData->MoveFirst(); }
			/// <summary>カーソルを次に移す</summary>
			bool MoveLast() { return m_rsData->MoveLast(); }
			/// <summary>カーソルを前に戻す</summary>
			bool MoveNext() { return m_rsData->MoveNext(); }
			/// <summary>カーソルを末尾に移す</summary>
			bool MovePrevious() { return m_rsData->MovePrevious(); }
			/// <summary>カーソルを指定行に移す。但し、レコードセットを前方スクロールで開いた場合は使えない。</summary>
			bool MoveTo(long recordIndex) { return m_rsData->MoveTo(recordIndex); }

			/// <summary>カレントカーソルのレコードを返す</summary>
			BomMasterRecord^ GetRecord() {
				auto rec = new DenkiBomMasterRecord();
				return m_rsData->GetRecord(*rec) ? gcnew BomMasterRecord(rec) : nullptr;
			}
		};

		/// <summary>部品マスタデータベースの各表を表すクラス</summary>
		public ref class BomMasterTable
		{
			DenkiBomMasterTable *m_tbl;
		public:
			BomMasterTable(DenkiBomMasterTable *tbl) : m_tbl(tbl) {}
			~BomMasterTable() {
				if (m_tbl != nullptr) {
					m_tbl->Close();
					delete m_tbl;
					m_tbl = nullptr;
				}
			}

			/// <summary>レコードを取得</summary>
			BomMasterRecord ^GetRecord() { 
				return gcnew BomMasterRecord(new DenkiBomMasterRecord(m_tbl));
			}

			/// <summary>指定条件にあったデータを取得</summary>
			BomMasterRecordSet^ Select(System::String^ whereStr) {
				auto rsData = new DenkiBomMasterRecordset();
				if (!m_tbl->Select(*rsData, 
						isNull(whereStr) ? nullptr : toWStr(whereStr).c_str())) {
					return nullptr;
				}
				return gcnew BomMasterRecordSet(rsData);
			}
		};

		/// <summary>部品マスタデータベースの本体を表すクラス </summary>
		public ref class BomMasterDatabase
		{
		private:
			DenkiBomMasterDatabase *m_db;

		public:
			BomMasterDatabase(DenkiBomMasterDatabase *db) : m_db(db) {}
			~BomMasterDatabase() {
				if (m_db != nullptr) {
					m_db->Close();
					delete m_db;
					m_db = nullptr;
				}
			}

			/// <summary>部品マスタデータベースを開く</summary>
			static BomMasterDatabase ^Open()
			{
				auto db = new DenkiBomMasterDatabase();
				if (!db->Open())
				{
					delete db;
					return nullptr;
				}
				return gcnew BomMasterDatabase(db);
			}

			/// <summary>部品表を取得く</summary>
			BomMasterTable^ GetBomTable() {
				auto tbl = new DenkiBomMasterTable();
				if (m_db->GetBomTable(*tbl)) {
					return gcnew BomMasterTable(tbl);
				}
				else {
					delete tbl;
					return nullptr;
				}
			}
			/// <summary>端子表を取得く</summary>
			BomMasterTable ^GetPinTable() {
				auto tbl = new DenkiBomMasterTable();
				if (m_db->GetPinTable(*tbl)) {
					return gcnew BomMasterTable(tbl);
				}
				else {
					delete tbl;
					return nullptr;
				}
			}
			/// <summary>付属品表を取得く</summary>
			BomMasterTable ^GetAcsryTable() {
				auto tbl = new DenkiBomMasterTable();
				if (m_db->GetAcsryTable(*tbl)) {
					return gcnew BomMasterTable(tbl);
				}
				else {
					delete tbl;
					return nullptr;
				}
			}
		};
	}
}
