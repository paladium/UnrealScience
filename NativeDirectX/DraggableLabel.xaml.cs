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

namespace NativeDirectX
{
    /// <summary>
    /// Interaction logic for DraggableLabel.xaml
    /// </summary>
    public partial class DraggableLabel : UserControl
    {

        private bool isDragging = false;

        private Point position;

        public DraggableLabel()
        {
            InitializeComponent();

            MouseLeftButtonDown += new MouseButtonEventHandler(Control_MouseLeftButtonDown);
            MouseLeftButtonUp += new MouseButtonEventHandler(Control_MouseLeftButtonUp);
            MouseMove += new MouseEventHandler(Control_MouseMove);

            Text = "text";
        }

        private void Control_MouseMove(object sender, MouseEventArgs e)
        {
            //if(isDragging)
            //{
            //    var posWithinParent = e.GetPosition(Parent as UIElement);

            //    var parentSize = (Parent as Canvas).RenderSize;

                

            //    Canvas.SetLeft(this, Clamp((float)(posWithinParent.X - position.X), 0, (float)parentSize.Width));
            //    Canvas.SetTop(this, Clamp((float)(posWithinParent.Y - position.Y), 0, (float)parentSize.Height));
            //}
        }

        private void Control_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            isDragging = true;

            position = e.GetPosition(this);

            CaptureMouse();
        }

        private void Control_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            isDragging = false;

            ReleaseMouseCapture();
        }

        public static readonly DependencyProperty TextProperty =
           DependencyProperty.Register("Text", typeof(string), typeof(DraggableLabel), new PropertyMetadata(""));





        public static readonly DependencyProperty PositionXProperty =
            DependencyProperty.Register("PositionX", typeof(float), typeof(DraggableLabel), new PropertyMetadata(0.0f));

        public static readonly DependencyProperty PositionYProperty =
            DependencyProperty.Register("PositionY", typeof(float), typeof(DraggableLabel), new PropertyMetadata(0.0f));

        public static readonly DependencyProperty SizeXProperty =
            DependencyProperty.Register("SizeX", typeof(float), typeof(DraggableLabel), new PropertyMetadata(0.0f));

        public static readonly DependencyProperty SizeYProperty =
            DependencyProperty.Register("SizeY", typeof(float), typeof(DraggableLabel), new PropertyMetadata(0.0f));


        public string Text
        {
            get { return text; }
            set { text = value; label.Text = value; }
        }

        public float PositionX
        {
            get { return (float)pos.X; }
            set { pos.X = value; Canvas.SetLeft(this, value); }
        }
        public float PositionY
        {
            get { return (float)pos.Y; }
            set { pos.Y = value; Canvas.SetTop(this, value); }
        }

        public float SizeX
        {
            get { return (float)size.X;}
            set { size.X = value; Width = value; }
        }
        public float SizeY
        {
            get { return (float)size.Y; }
            set { size.Y = value; Height = value; }
        }

        public string FontName
        {
            get { return fontName; }
            set { fontName = value; label.FontFamily = new FontFamily(fontName); }
        }

        public int fontSize
        {
            get { return _fontSize; }
            set { _fontSize = value; label.FontSize = value; }
        }

        private Point size;
        private Point pos;
        private string text;
        private string fontName;
        private int _fontSize;
       

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e)
        {
            
            //if(e.Property == TextProperty)
            //{
            //    label.Content = Text;
            //}

            //if (e.Property == PositionXProperty)
            //{
            //    Canvas.SetLeft(this, PositionX);
            //}
            //if (e.Property == PositionYProperty)
            //{
            //    Canvas.SetTop(this, PositionY);
            //}

            //if(e.Property == SizeXProperty)
            //{
            //    this.Width = SizeX;
            //    label.Width = SizeX;
            //}

            //if(e.Property == SizeYProperty)
            //{
            //    this.Height = SizeY;
            //    label.Height = SizeY;
            //}

            base.OnPropertyChanged(e);
        }

        public static float Clamp(float value, float min, float max)
        {
            if (value > max)
                return Math.Max(value, max);

            if (value < min)
                return Math.Min(value, min);

            return value;
        }
    }
}
