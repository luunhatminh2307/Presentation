using DenkiExtensions.DENKIBOM;
using DenkiExtensionsEx.DENKIBOM;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BomDatabase
{
    public class ExportBomDb
    {
        static string ExportBomDatabasePath =>
            Path.Combine(Path.GetTempPath(), "BomDatabase.csv");
        
        public static Dictionary<string, string>? ReadCodeAndTypeFromBomDatabase()
        {
            using var db = BomMasterDatabase.Open();
            if (db is null) {
                return null;
            }
            using var tblBom = db.GetBomTable();
            if (tblBom is null) {
                return null;
            }
            using var rsData = tblBom.Select(null);
            if (rsData is null) {
                return null;
            }
            Dictionary<string, string> codeTypes = new();
            rsData.Each(rec => {
                try {
                    var code = rec.GetValueOrDefault("code", "");
                    var type = rec.GetValueOrDefault("type", "");
                    codeTypes[code] = type;
                }
                catch { }
            });
            return codeTypes;
        }

        static void Export(Dictionary<string,string> codeTypes)
        {
            List<string> lines = new() {
                $"部品コード,型式"
            };
            var contents = codeTypes.Select(kv => $"{kv.Key},{kv.Value}");
            lines.AddRange(contents);
            File.WriteAllLines(ExportBomDatabasePath, lines);
        }

        public static void Cmd()
        {
            var codeTypes = ReadCodeAndTypeFromBomDatabase();
            if (codeTypes is null) {
                return;
            }
            Export(codeTypes);
        }
    }
}
