using SampleCLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;
using static SampleCLI.Math;

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
            //�֐��̏ꍇ�ASumFunction()�̌��ʂ��擾
            //1. PInvoke��
            var res_sumF_PInvoke = SumFunction_PInvoke(5, 10);
            //2. CLI��
            var res_sumF_CLI = SumFunction_CLI(5, 10);

            MessageBox.Show($"res_sumF_PInvoke = {res_sumF_PInvoke}" + Environment.NewLine
                          + $"res_sumF_CLI = {res_sumF_CLI}");


            //�N���X�̏ꍇ�ASumMethod()�̌��ʂ��擾
            //1. P/Invoke��
            //���ڃ������Ǘ����s���ꍇ
            var caculator = CreateCalculator_PInvoke();
            var res_sumMethod_PInvoke = CalculatorSum_PInvoke(caculator, 1, 2);
            DeleteCalculator_PInvoke(caculator);
            //���ڃ������Ǘ����s��Ȃ��ꍇ
            var res_sumMethod_PInvoke2 = CalculatorSum_PInvoke(1, 2);

            //2. CLI��
            using var caculatorCLI = new Caculator_CLI();
            var res_sumMethod_CLI = caculatorCLI.SumMethod(1,2);

            MessageBox.Show($"res_sumMethod_PInvoke = {res_sumMethod_PInvoke}" + Environment.NewLine
                          + $"res_sumMethod_PInvoke2 = {res_sumMethod_PInvoke2}" + Environment.NewLine
                          + $"res_sumMethod_CLI = {res_sumMethod_CLI}");
        }

        [DllImport("SampleDLL.dll", EntryPoint = "?SumFunction@SampleDLL@@YAHHH@Z")]
        public static extern int SumFunction_PInvoke(int a, int b);


        //Calculator�N���X�̒��ڃ������Ǘ����s���ꍇ
        [DllImport("SampleDLL.dll", EntryPoint = "?CreateCalculator@SampleDLL@@YAPEAVCalculator@1@XZ")]
        public static extern IntPtr CreateCalculator_PInvoke();
        [DllImport("SampleDLL.dll", EntryPoint = "?CalculatorSum@SampleDLL@@YAHPEAVCalculator@1@HH@Z")]
        public static extern int CalculatorSum_PInvoke(IntPtr calculator,int a, int b);
        [DllImport("SampleDLL.dll", EntryPoint = "?DeleteCalculator@SampleDLL@@YAXPEAVCalculator@1@@Z")]
        public static extern void DeleteCalculator_PInvoke(IntPtr calculator);

        //Calculator�N���X�̒��ڃ������Ǘ����s��Ȃ��ꍇ
        [DllImport("SampleDLL.dll", EntryPoint = "?CalculatorSum@SampleDLL@@YAHHH@Z")]
        public static extern int CalculatorSum_PInvoke(int a, int b);
    }
}
