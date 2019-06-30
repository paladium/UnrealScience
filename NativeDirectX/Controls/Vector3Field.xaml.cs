using System;
using System.Windows;
using System.Windows.Controls;
using UnrealScienceLibrary;

namespace UnrealScience.Controls
{
    /// <summary>
    /// Interaction logic for Vector3Field.xaml
    /// </summary>
    public partial class Vector3Field : UserControl
    {

        public Vector3D Value;

        public Action ValueChanged;

        public Vector3Field()
        {
            InitializeComponent();

            Value = new Vector3D();
        }

        public void InitField()
        {
            X.ValueChanged = ValueChanged;
            Y.ValueChanged = ValueChanged;
            Z.ValueChanged = ValueChanged;
        }

        public static readonly DependencyProperty XProperty = 
            DependencyProperty.Register("XField", typeof(float), typeof(Vector3Field),
            new PropertyMetadata(0.0f));


        public static readonly DependencyProperty YProperty =
            DependencyProperty.Register("YField", typeof(float), typeof(Vector3Field),
            new PropertyMetadata(0.0f));

        public static readonly DependencyProperty ZProperty =
            DependencyProperty.Register("ZField", typeof(float), typeof(Vector3Field),
            new PropertyMetadata(0.0f));

        public float XField
        {
            get { return (float)GetValue(XProperty); }
            set { SetValue(XProperty, value); X.Value = value; X.Field.Text = value.ToString(); }
        }

        public float YField
        {
            get { return (float)GetValue(YProperty); }
            set { SetValue(YProperty, value); Y.Value = value; Y.Field.Text = value.ToString(); }
        }

        public float ZField
        {
            get { return (float)GetValue(ZProperty); }
            set { SetValue(ZProperty, value); Z.Value = value; Z.Field.Text = value.ToString(); }
        }
        

        public void GetVector()
        {
            //GetFloatValue(X.Text, ref Value.X);
            //GetFloatValue(Y.Text, ref Value.Y);
            //GetFloatValue(Z.Text, ref Value.Z);

            Value.X = X.Value;
            Value.Y = Y.Value;
            Value.Z = Z.Value;
        }

        public void SetVector(Vector3D v)
        {
            XField = v.X;
            YField = v.Y;
            ZField = v.Z;
            GetVector();
        }

        public void Clear()
        {
            XField = 0;
            YField = 0;
            ZField = 0;
        }
    }
}
