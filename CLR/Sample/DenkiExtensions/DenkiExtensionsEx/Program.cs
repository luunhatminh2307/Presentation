using DenkiExtensions.DENKIBOM;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace DenkiExtensionsEx
{
	namespace DENKIBOM
	{
		public static class BomMasterRecordExt
		{
            /// <summary>レコードを順に実行する</summary>
            public static void EachUntil(this BomMasterRecordSet rsData, Func<BomMasterRecord, bool> func)
            {
                if (rsData.IsEOF()) {
                    return;
                }
                rsData.MoveFirst();
                while (true) {
                    using var rec = rsData.GetRecord();
                    if (rec is not null) {
                        if (!func(rec)) {
                            return;
                        }
                    }
                    rsData.MoveNext();
                    if (rsData.IsEOF()) {
                        break;
                    }
                }
            }

            /// <summary>レコードを順に実行する</summary>
            public static void Each(this BomMasterRecordSet rsData, Action<BomMasterRecord> action)
            {
                EachUntil(rsData, rec => { action(rec); return true; });
            }
        }

        public static class BomMasterTableExt
        {
            static string toWhere(string primaryKeyName, string pattern) => $"{primaryKeyName}='{pattern}'";

            /// <summary>指定条件にあったデータを取得</summary>
            public static List<T>? Select<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : class
            {
                List<T>? res = new();
                using var rsData = tbl.Select(toWhere(primaryKeyName, pattern));                
                rsData?.Each(rec => {
                    var value = func(rec);
                    if (value is not null) {
                        res.Add(value);
                    }
                });
                return res;
            }

            /// <summary>指定条件にあったデータを取得</summary>
            public static List<T>? Select<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : struct
            {
                List<T>? res = new();
                using var rsData = tbl.Select(toWhere(primaryKeyName, pattern));
                rsData?.Each(rec => {
                    var value = func(rec);
                    if (value is not null) {
                        res.Add(value.Value);
                    }
                });
                return res;
            }

            /// <summary>指定条件にあった最初のデータを取得</summary>
            public static T? SelectFirst<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : class
			{
                T? res = null;
                using var rsData = tbl.Select($"{primaryKeyName}='{pattern}'");              
                rsData?.EachUntil(rec => {
                        var value = func(rec);
                        if (value is not null) {
                            res = value;
                            return false;
                        }
                        return true;
                    }
                );
                return res;
            }

            /// <summary>最初のデータを取得</summary>
            public static T? SelectFirst<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : struct
            {
                T? res = null;
                using var rsData = tbl.Select($"{primaryKeyName}='{pattern}'");
                rsData?.EachUntil(rec => {
                    var value = func(rec);
                    if (value is not null) {
                        res = value;
                        return false;
                    }
                    return true;
                }
                );
                return res;
            }

            /// <summary>最初のデータ一つだけが存在するデータを取得</summary>
            public static T? SelectOnlyOne<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : class
            {
                var res = tbl.Select<T>(primaryKeyName, pattern, func).Distinct();
                return res.Count() == 1 ? res.First() : null;
            }

            /// <summary>一つだけが存在するデータを取得</summary>
            public static T? SelectOnlyOne<T>(this BomMasterTable tbl,
                string primaryKeyName, string pattern, Func<BomMasterRecord, T?> func)
                where T : struct
            {
                var res = tbl.Select<T>(primaryKeyName, pattern, func).Distinct();
                return res.Count() == 1 ? res.First() : null;
            }
        }
    }
}
