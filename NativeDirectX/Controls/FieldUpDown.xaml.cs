using System;
using System.Windows;
using System.Windows.Controls;
using UnrealScienceLibrary;

namespace UnrealScience.Controls
{
    /// <summary>
    /// Interaction logic for FieldUpDown.xaml
    /// </summary>
    public partial class FieldUpDown : UserControl
    {

        private float _interval = 1;
        private float _min = -float.MaxValue;
        private float _max = float.MaxValue;

        public Action ValueChanged;

        public FieldUpDown()
        {
            InitializeComponent();

        }


        public static readonly DependencyProperty ValueProperty =
            DependencyProperty.Register("Value", typeof(float), typeof(FieldUpDown),
            new PropertyMetadata(0.0f));


        public static readonly DependencyProperty IntervalProperty =
            DependencyProperty.Register("Interval", typeof(float), typeof(FieldUpDown),
            new PropertyMetadata(1.0f));

        public static DependencyProperty MaxProperty =
            DependencyProperty.Register("Max", typeof(float), typeof(FieldUpDown),
            new PropertyMetadata(float.MaxValue));

        public static readonly DependencyProperty MinProperty =
            DependencyProperty.Register("Min", typeof(float), typeof(FieldUpDown),
            new PropertyMetadata(-float.MaxValue));

        public static readonly DependencyProperty TextProperty =
            DependencyProperty.Register("Text", typeof(string), typeof(FieldUpDown));

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e)
        {
            base.OnPropertyChanged(e);

            if (e.Property == TextProperty)
            {
                TextArea.Text = Text;
            }
        }

        public float Value
        {
            get { return (float)GetValue(ValueProperty); }
            set { SetValue(ValueProperty, value); }
        }

        public float Interval
        {
            get { return (float)GetValue(IntervalProperty); }
            set { SetValue(IntervalProperty, value); _interval = value; }
        }

        public float Max
        {
            get { return (float)GetValue(MaxProperty); }
            set { SetValue(MaxProperty, value); _max = value; }
        }

        public float Min
        {
            get { return (float)GetValue(MinProperty); }
            set { SetValue(MinProperty, value); _min = value; }
        }

        public string Text
        {
            get { return (string)GetValue(TextProperty); }
            set { SetValue(TextProperty, value); }
        }

        private void Increase_Click(object sender, RoutedEventArgs e)
        {
            Value += Interval;
            Value = Clamp(Value, Min, Max);

            if (ValueChanged != null)
                ValueChanged.Invoke();

            Field.Text = Value.ToString();
        }

        private void Decrease_Click(object sender, RoutedEventArgs e)
        {
            Value -= Interval;
            Value = Clamp(Value, Min, Max);
            if (ValueChanged != null)
                ValueChanged.Invoke();

            Field.Text = Value.ToString();
        }

        public static float Clamp(float v, float min, float max)
        {
            if (v < min)
                return min;
            if (v > max)
                return max;
            return v;
        }



        private void Field_TextChanged(object sender, TextChangedEventArgs e)
        {
            //Value = Util.ParseFloat(Field.Text);

            float temp = 0;

            if(float.TryParse(Field.Text, out temp))
            {
                Value = temp;

                Value = Clamp(Value, Min, Max);
                if (ValueChanged != null)
                    ValueChanged.Invoke();
            }
            else
            {
                Value = 0;
            }
            
        }

        private void Field_LostFocus(object sender, RoutedEventArgs e)
        {
            GetValue();
        }

        private void GetValue()
        {
            Value = Util.ParseFloat(Field.Text);
            Value = Clamp(Value, Min, Max);
            if (ValueChanged != null)
                ValueChanged.Invoke();
            Field.Text = Value.ToString();
        }

        private void Field_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if(e.Key == System.Windows.Input.Key.Enter)
            {
                GetValue();
            }
        }
    }
}
