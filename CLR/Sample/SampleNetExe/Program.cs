using SampleCLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SampleNetExe
{
    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            var result = SampleCLI.Math.SumFunction(5, 10);
            MessageBox.Show($"Sum = {result}");

            var result2 = SumFunction_PInvoke(3, 6);
            MessageBox.Show($"Sum2 = {result2}");
        }

        [DllImport("SampleDLL.dll", EntryPoint = "?SumFunction@SampleDLL@@YAHHH@Z")]
        public static extern int SumFunction_PInvoke(int a, int b);
    }
}
