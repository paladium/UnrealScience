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
    /// Interaction logic for UIEditor.xaml
    /// </summary>
    public partial class UIEditor : UserControl
    {
        public UIEditor()
        {
            InitializeComponent();
        }

        

        List<DraggableLabel> elements = new List<DraggableLabel>();

        int selected = 0;

        private void Add_Text_Click(object sender, RoutedEventArgs e)
        {
            DraggableLabel block = new DraggableLabel();

            block.Text = "TEXT";

            block.FontName = "Arial";

            block.Cursor = Cursors.Hand;

            block.MouseLeftButtonDown += block_MouseLeftButtonDown;

            elements.Add(block);

            selected = elements.Count - 1;

            UI.Children.Add(block);
        }

        void block_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DraggableLabel t = sender as DraggableLabel;
            ActualText.Text = (t).Text;

            PosX.Text = t.PositionX.ToString();
            PosY.Text = t.PositionY.ToString();

            SizeX.Text = t.SizeX.ToString();
            SizeY.Text = t.SizeY.ToString();

            FontName.Text = t.FontName;

            selected = elements.FindIndex(x => x == t);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            
        }

        private void Apply_Click(object sender, RoutedEventArgs e)
        {
            elements[selected].Text = ActualText.Text;

            elements[selected].PositionX = Util.ParseFloat(PosX.Text);
            elements[selected].PositionY = Util.ParseFloat(PosY.Text);

            //Canvas.SetLeft(elements[selected], elements[selected].PositionX);
            //Canvas.SetTop(elements[selected], elements[selected].PositionY);

            elements[selected].SizeX = Util.ParseFloat(SizeX.Text);
            elements[selected].SizeY = Util.ParseFloat(SizeY.Text);

            elements[selected].FontName = FontName.Text;
            
            elements[selected].fontSize = Util.ParseInt(FontSize.Text);

            //elements[selected].Width = elements[selected].SizeX;
            //elements[selected].Height = elements[selected].SizeY;
        }

        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            UnrealScienceScripting.CleanUI();

            foreach(DraggableLabel l in elements)
            {

                UnrealScienceScripting.AddText2D(l.Text, l.FontName, (int)l.PositionX, (int)l.PositionY, (int)l.SizeX, (int)l.SizeY, (int)l.fontSize);
            }
        }


    }
}
