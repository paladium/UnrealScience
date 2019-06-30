using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace UnrealScience.Controls
{
    /// <summary>
    /// Interaction logic for FieldString.xaml
    /// </summary>
    public partial class FieldString : UserControl
    {

        public Action ValueChanged;

        public FieldString()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty ValueProperty =
            DependencyProperty.Register("Value", typeof(string), typeof(FieldString));


        public static readonly DependencyProperty TextProperty =
            DependencyProperty.Register("Text", typeof(string), typeof(FieldString));


        public string Value
        {
            get { return (string)GetValue(ValueProperty); }
            set { SetValue(ValueProperty, value); }
        }


        public string Text
        {
            get { return (string)GetValue(TextProperty); }
            set { SetValue(TextProperty, value); }
        }

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e)
        {
            base.OnPropertyChanged(e);

            if (e.Property == TextProperty)
            {
                TextArea.Text = Text;
            }

            if(e.Property == ValueProperty)
            {
                Field.Text = Value;
            }
        }


        private void Field_TextChanged(object sender, TextChangedEventArgs e)
        {
            Value = Field.Text;   
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            ValueChanged.Invoke();
        }

        public void SetValue(string t)
        {
            Value = t;
        }
    }
}
