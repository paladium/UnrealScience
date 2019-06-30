using Microsoft.CSharp;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using UnrealScienceLibrary;

namespace UnrealScience.Controls
{
    /// <summary>
    /// Interaction logic for Graph3D.xaml
    /// </summary>
    public partial class Graph3D : UserControl
    {
        public Func<float, float, float> Z;

        public Graph3D()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string formula = ProcessFormula(Function.Text);

            float xMin = XMin.Value;
            float xMax = XMax.Value;

            float yMin = YMin.Value;
            float yMax = YMax.Value;

            float step = Step.Value;

            int type = GraphType.SelectedIndex;

            UnrealScienceScripting.SetType(type + 1);

            UnrealScienceScripting.ResetGraph3D();

            BuildGraph(xMin, xMax, yMin, yMax, step, formula);

            UnrealScienceScripting.InitializeGraph();
        }

        private void BuildGraph(float xMin, float xMax, float yMin, float yMax, float step, string formula)
        {
            SetZFunction(this, formula);

            List<Vector3D> v = new List<Vector3D>();

            for (float x = xMin; x <= xMax; x += step)
            {
                for (float y = yMin; y <= yMax; y += step)
                {
                    float z = Z.Invoke(x, y);

                    Vector3D vector = new Vector3D(x, y, z);

                    v.Add(vector);

                    //UnrealScienceScripting.AddGraph3DVertex(x, y, z, 50, 50, 50);
                }
            }

            float[] xArr = new float[v.Count];
            float[] yArr = new float[v.Count];
            float[] zArr = new float[v.Count];

            for (int i = 0; i < v.Count; i++)
            {
                xArr[i] = v[i].X;
                yArr[i] = v[i].Y;
                zArr[i] = v[i].Z;
            }

            UnrealScienceScripting.BuildGraph3D(xArr, yArr, zArr, v.Count);

            //for (int i = 0; i < 10; i++)
            //{
            //    UnrealScienceScripting.AddGraph3DVertex(i, i, i, i, i, i);
            //}

        }

        private string ProcessFormula(string s)
        {
            string res = s;
            res = res.Replace("sin", "Math.Sin");
            res = res.Replace("cos", "Math.Cos");
            res = res.Replace("abs", "Math.Abs");
            res = res.Replace("tan", "Math.Tan");
            res = res.Replace("sqrt", "Math.Sqrt");
            res = res.Replace("pow", "Math.Pow");
            res = res.Replace("pi", "Math.PI");

            res = "-(float)(" + res + ")";

            return res;
        }

        public static void SetZFunction(Graph3D g, string f)
        {
            MethodInfo function = CreateFunction(f);
            var betterFunction = (Func<float, float, float>)Delegate.CreateDelegate
                (typeof(Func<float, float, float>), function);

            g.Z = betterFunction;
        }

        public static MethodInfo CreateFunction(string function)
        {
            string code = @"
            using System;
            
            namespace UserFunctions
            {                
                public class BinaryFunction
                {                
                    public static float Function(float x, float y)
                    {
                        return func_xy;
                    }
                }
            }
        ";

            string finalCode = code.Replace("func_xy", function);

            CSharpCodeProvider provider = new CSharpCodeProvider();
            CompilerResults results = provider.CompileAssemblyFromSource(new CompilerParameters(), finalCode);

            // Check the compiler results for errors
            StringWriter sw = new StringWriter();
            foreach (CompilerError ce in results.Errors)
            {
                if (ce.IsWarning) continue;
                sw.WriteLine("{0}({1},{2}: error {3}: {4}", ce.FileName, ce.Line, ce.Column, ce.ErrorNumber, ce.ErrorText);
            }
            // If there were errors, raise an exception...
            string errorText = sw.ToString();
            if (errorText.Length > 0)
                throw new ApplicationException(errorText);

            Type binaryFunction = results.CompiledAssembly.GetType("UserFunctions.BinaryFunction");
            return binaryFunction.GetMethod("Function");
        }
    }
}
