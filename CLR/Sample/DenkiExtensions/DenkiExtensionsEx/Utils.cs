using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DenkiExtensionsEx
{
    public static class Utils
    {
        /// <summary>
        /// PATHに "C:\Program Files\Common Files\Alfatech"を追加
        /// 目的：DENKIBOM.dllなどロードできるため
        /// </summary>
        /// <remarks>ACAD-DENKIで起動した場合、この関数を呼び出すのが不要</remarks>
        public static bool AddCommonFilesPath()
        {
            try {
                using var regKey = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion", false);
                if (regKey is null) {
                    return false;
                }
                var dir = (string)regKey.GetValue("CommonFilesDir");
                if (dir is null) {
                    return false;
                }
                var commonFilePath = Path.Combine(dir, "Alfatech");
                var envPaths = Environment.GetEnvironmentVariable("Path")?.Split(';') ?? Array.Empty<string>();
                var isExist = envPaths.Any(
                    path => !string.IsNullOrEmpty(path) && Directory.Exists(path)
                            && (string.Compare(Path.GetFullPath(path), commonFilePath, true) == 0));
                if (!isExist)
                {
                    var newEnvPath = string.Join(";", envPaths.Append(commonFilePath));
                    Environment.SetEnvironmentVariable("Path", newEnvPath);
                }
                return true;
            }
            catch { return false; };
        }
    }
}
