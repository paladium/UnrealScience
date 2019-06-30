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
    /// Interaction logic for AnimationManager.xaml
    /// </summary>
    public partial class AnimationManager : UserControl
    {
        public AnimationManager()
        {
            InitializeComponent();
        }

        private void Load_Click(object sender, RoutedEventArgs e)
        {
            Keys.Items.Clear();

            int t = 0;

            foreach (SceneEntity s in UnrealScienceScripting.World.Entities)
            {
                t++;
                foreach (AnimationKey k in s.Animation.AnimationKeys)
                {
                    ListBoxItem item = new ListBoxItem();

                    item.Tag = k;

                    
                    

                    item.ToolTip = GetToolTip(k);

                    item.Content = "Key of entity#" + (t);

                    Keys.Items.Add(item);
                }
            }

        }

        Vector3D GetDestValue(AnimationKey k)
        {
            Vector3D v;

            if (k.KeyType == 1)
            {
                v = k.Destination.Position;
            }
            else if (k.KeyType == 2)
            {
                v = k.Destination.Rotation;
            }
            else v = k.Destination.Scale;

            return v;
        }

        void SetDestValue(ref AnimationKey k, Vector3D value)
        {
            if (k.KeyType == 1)
            {
                k.Destination.Position = value;
            }
            else if (k.KeyType == 2)
            {
                k.Destination.Rotation = value;
            }
            else k.Destination.Scale = value;


        }

        string GetToolTip(AnimationKey k)
        {
            string type = "";

            if (k.KeyType == 1)
                type = "Position";
            else if (k.KeyType == 2)
                type = "Rotation";
            else type = "Scale";

            return string.Format("It is a key with following parameters: \n Type: {0}, StartSlide: {1}, Duration: {2} seconds, Destination Value: {3} {4} {5}",
                        type, k.StartOrder, k.Duration, GetDestValue(k).X, GetDestValue(k).Y, GetDestValue(k).Z);
        }

        private void Keys_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
            ListBoxItem item = Keys.SelectedItem as ListBoxItem;

            if(item != null)
            {
                AnimationKey k = item.Tag as AnimationKey;

                Type.SelectedIndex = k.KeyType - 1;

                Duration.Text = k.Duration.ToString();

                KeyOrder.Text = k.StartOrder.ToString();

                

                Value.SetVector(GetDestValue(k));
            }

            


        }

        private void Apply_Click(object sender, RoutedEventArgs e)
        {
            AnimationKey k = new AnimationKey();

            k.KeyType = Type.SelectedIndex + 1;


            Value.GetVector();

            SetDestValue(ref k, Value.Value);

            k.StartOrder = Util.ParseInt(KeyOrder.Text);

            k.Duration = Util.ParseFloat(Duration.Text);

            k.OwnerID = ((Keys.SelectedItem as ListBoxItem).Tag
                as AnimationKey).OwnerID;

            (Keys.SelectedItem as ListBoxItem).Tag = k;

            (Keys.SelectedItem as ListBoxItem).ToolTip = GetToolTip(k);

            //Sort();
        }



        public void Sort()
        {


            for (int i = 0; i < Keys.Items.Count; i++)
            {
                int orderA = ((Keys.Items[i] as ListBoxItem).Tag
                    as AnimationKey).StartOrder;

                for (int j = i; j < Keys.Items.Count; j++)
                {
                    if (i != j)
                    {
                        int orderB = ((Keys.Items[j] as ListBoxItem).Tag
                        as AnimationKey).StartOrder;

                        if (orderA > orderB)
                        {
                            ListBoxItem A = Keys.Items[i] as ListBoxItem;
                            ListBoxItem B = Keys.Items[j] as ListBoxItem;

                            Keys.Items.Insert(i - 1, B);
                            Keys.Items.RemoveAt(i);

                            Keys.Items.Insert(j - 1, A);
                            Keys.Items.RemoveAt(j);
                        }
                    }
                }
            }
        }
        public void Swap(ref object a, ref object b)
        {
            object c = a;
            a = b;
            b = a;
        }

        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            List<AnimationKey> SceneKeys = new List<AnimationKey>();
            for (int i = 0; i < Keys.Items.Count; i++)
            {
                AnimationKey key = (Keys.Items[i] as ListBoxItem).Tag as AnimationKey;

                SceneKeys.Add(key);
            }

            UnrealScienceScripting.PushAnimationKeys(SceneKeys);
        }
    }
}
