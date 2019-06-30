using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using UnrealScienceLibrary;

namespace UnrealScience.Controls
{
    /// <summary>
    /// Interaction logic for PropertyGrid.xaml
    /// </summary>
    public partial class PropertyGrid : System.Windows.Controls.UserControl
    {
        public PropertyGrid()
        {
            InitializeComponent();

            Color = new Vector3D();
        }

        public void InitGrid()
        {
            Position.ValueChanged = PositionChanged;
            Rotation.ValueChanged = RotationChanged;
            Scale.ValueChanged = ScaleChanged;

            Position.InitField();
            Rotation.InitField();
            Scale.InitField();
            Scale.X.Interval = 0.1f;
            Scale.Y.Interval = 0.1f;
            Scale.Z.Interval = 0.1f;

            Texture.ValueChanged = TextureChanged;
        }

        public Action PositionChanged;

        public Action RotationChanged;

        public Action ScaleChanged;

        public Action TextureChanged;

        public Action ColorChanged;

        public Vector3D Color;

        private void ColorPicker_Click(object sender, RoutedEventArgs e)
        {
            ColorDialog d = new ColorDialog();

            

            d.Color = System.Drawing.Color.FromArgb(255, (int)Color.X, (int)Color.Y, (int)Color.Z);

            if(d.ShowDialog() == DialogResult.OK)
            {
                Color.X = d.Color.R;
                Color.Y = d.Color.G;
                Color.Z = d.Color.B;

                color.Background = new SolidColorBrush(new Color() { R = (byte)Color.X, G = (byte)Color.Y, B = (byte)Color.Z, A = 255 });

                ColorChanged.Invoke();
            }
        }

        public void SetColor(Vector3D c)
        {
            Color.X = c.X;
            Color.Y = c.Y;
            Color.Z = c.Z;

            color.Background = new SolidColorBrush(new Color() { R = (byte)Color.X, G = (byte)Color.Y, B = (byte)Color.Z, A = 255 });
        }
    }
}
