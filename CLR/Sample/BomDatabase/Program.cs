using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace BomDatabase
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
            //DENKIBOMを有効にする。
            DenkiExtensionsEx.Utils.AddCommonFilesPath();
            ExportBomDb.Cmd();
        }
    }
}
