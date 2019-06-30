using System;
using System.Collections.Generic;
using System.Linq;
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

namespace NativeDirectX
{
    /// <summary>
    /// Interaction logic for KeyControl.xaml
    /// </summary>
    public partial class KeyControl : UserControl
    {
        public KeyControl()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty DurationProperty = 
            DependencyProperty.Register("Duration", typeof(float), typeof(KeyControl), new PropertyMetadata(1.0f));


        public float Duration
        {
            get { return duration; }
            set { duration = value; }
        }

        private float duration;

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e)
        {
            if(e.Property == DurationProperty)
            {
                SetWidth();
            }

            base.OnPropertyChanged(e);
        }

        public void SetWidth()
        {
            line.Width = duration * 100;
        }
    }
}
