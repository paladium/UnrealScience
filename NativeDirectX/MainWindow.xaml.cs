using System;
using System.Windows;
using System.Runtime.InteropServices;
using System.Windows.Input;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Globalization;
using WPFTextBoxAutoComplete;
using UnrealScienceLibrary;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Speech.Recognition;
using System.Windows.Media;

namespace NativeDirectX
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    enum COMMANDS
    {
        NONE = 0,
        EDITOR_MOVE_FORWARD = 1,
        EDITOR_MOVE_BACKWARD = 2,
        EDITOR_MOVE_LEFT = 3,
        EDITOR_MOVE_RIGHT = 4,

        EDITOR_ALT = 5,

        EDITOR_ROTATE_RIGHT = 6,

        EDITOR_ROTATE_LEFT = 7,

        EDITOR_ROTATE_UP = 8,
        EDITOR_ROTATE_DOWN = 9,

        EDITOR_ROTATE_TOP = 10,
        EDITOR_ROTATE_BOTTOM = 11
    };



    public partial class MainWindow : Window
    {

        System.Windows.Forms.Timer timer;

        UnrealScienceScripting Scripting;

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            UnrealScienceScripting.Cleanup();

            base.OnClosing(e);
        }

        #region Manipulate hierarchy
        void AddEntity(int index)
        {
            ListBoxItem item = new ListBoxItem();
            item.Content = new TextBlock() { Text = "entity #" + index };

            Hierarchy.Items.Add(item);

            Select_Entity(Hierarchy.Items.Count - 1);
        }

        void RemoveEntity(int index)
        {

            Hierarchy.Items.RemoveAt(index);
        }

        void Select_Entity(int index)
        {
            if (index < Hierarchy.Items.Count && index >= 0)
            {
                Hierarchy.SelectedIndex = index;

                SceneEntity s = UnrealScienceScripting.World.Entities[Scripting.current];

                PropertyGrid.Position.SetVector(s.Transform.Position);
                PropertyGrid.Rotation.SetVector(s.Transform.Rotation);
                PropertyGrid.Scale.SetVector(s.Transform.Scale);
                PropertyGrid.Texture.SetValue(s.Texture);
                PropertyGrid.SetColor(s.Color);
            }

        }

        void MoveEntity()
        {
            PropertyGrid.Position.GetVector();
            Vector3D v = PropertyGrid.Position.Value;
            Scripting.ScriptingManager.Parse(String.Format("move {0} {1} {2}", v.X, v.Y, v.Z));
        }

        void RotateEntity()
        {
            PropertyGrid.Rotation.GetVector();
            Vector3D v = PropertyGrid.Rotation.Value;
            Scripting.ScriptingManager.Parse(String.Format("rotate {0} {1} {2}", v.X, v.Y, v.Z));
        }

        void ScaleEntity()
        {
            PropertyGrid.Scale.GetVector();
            Vector3D v = PropertyGrid.Scale.Value;
            Scripting.ScriptingManager.Parse(String.Format("scale {0} {1} {2}", v.X, v.Y, v.Z));
        }

        void SetTexture()
        {
            string t = PropertyGrid.Texture.Value;
            Scripting.ScriptingManager.Parse("setTexture " + t);
        }

        void SetColor()
        {
            Vector3D v = PropertyGrid.Color;

            Scripting.ScriptingManager.Parse(String.Format("setColor {0} {1} {2}", v.X, v.Y, v.Z));
        }

        void ChangeColor(int index)
        {
            PropertyGrid.SetColor(UnrealScienceScripting.World.Entities[index].Color);
        }

        #endregion

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            unsafe
            {
                UnrealScienceScripting.InitD3D(panel.Handle.ToPointer(),
                    System.Windows.Forms.SystemInformation.VirtualScreen.Width,
                    System.Windows.Forms.SystemInformation.VirtualScreen.Height);
            }


            UnrealScienceScripting.InitWorld();

            timer = new System.Windows.Forms.Timer();

            //IntPtr hinstance = /*Marshal.GetHINSTANCE(typeof(MainWindow).Module)*/System.Diagnostics.Process.GetCurrentProcess().Handle;
            //IntPtr hInst = Marshal.GetHINSTANCE(this.GetType().Module);

            //unsafe
            //{
            //    bool t = InitInput(hInst.ToPointer());
            //}



            timer.Interval = 10;

            timer.Tick += timer_Tick;

            timer.Start();

            //InitScripting();

            Scripting = new UnrealScienceScripting();

            Scripting.InitScripting();

            Scripting.AddEntity = new Action<int>(AddEntity);
            Scripting.Select_Entity = new Action<int>(Select_Entity);
            Scripting.RemoveEntity = new Action<int>(RemoveEntity);
            Scripting.ChangeEntityColor = new Action<int>(ChangeColor);

            PropertyGrid.PositionChanged = new Action(MoveEntity);
            PropertyGrid.RotationChanged = new Action(RotateEntity);
            PropertyGrid.ScaleChanged = new Action(ScaleEntity);

            PropertyGrid.TextureChanged = new Action(SetTexture);

            PropertyGrid.ColorChanged = new Action(SetColor);

            PropertyGrid.InitGrid();



            //InitAnimationScripting();

            Scripting.InitAnimationScripting();

            Scripting.ScriptingManager.functions.Remove("startAnimation");
            Scripting.ScriptingManager.functions.Remove("next");
            Scripting.ScriptingManager.functions.Remove("prev");

            PropertyGrid.Visibility = System.Windows.Visibility.Collapsed;
        }

        COMMANDS c;

        Point p;

        bool isHold = false;

        Point difference;

        public static Point GetMousePositionWindowsForms()
        {
            System.Drawing.Point point = System.Windows.Forms.Control.MousePosition;
            return new Point(point.X, point.Y);
        }

        void timer_Tick(object sender, EventArgs e)
        {
            c = COMMANDS.NONE;


            if (isHold)
            {
                panel.Cursor = System.Windows.Forms.Cursors.Hand;
            }
            if (host.IsKeyboardFocused)
            {
                if (Keyboard.IsKeyDown(Key.W))
                {
                    c = COMMANDS.EDITOR_MOVE_FORWARD;
                }
                if (Keyboard.IsKeyDown(Key.S))
                {
                    c = COMMANDS.EDITOR_MOVE_BACKWARD;
                }

                if (Keyboard.IsKeyDown(Key.A))
                {
                    c = COMMANDS.EDITOR_MOVE_LEFT;
                }

                if (Keyboard.IsKeyDown(Key.D))
                {
                    c = COMMANDS.EDITOR_MOVE_RIGHT;
                }

                if (Keyboard.IsKeyDown(Key.LeftAlt))
                {
                    p = GetMousePositionWindowsForms();

                    c = COMMANDS.EDITOR_ALT;

                    //box.Text += 2 * p.X / (panel.Width) + " " + 2 * p.Y / (panel.Height)  + "\n";
                }

                if (Keyboard.IsKeyDown(Key.Q))
                {
                    c = COMMANDS.EDITOR_ROTATE_LEFT;
                }

                if (Keyboard.IsKeyDown(Key.E))
                {
                    c = COMMANDS.EDITOR_ROTATE_RIGHT;
                }

                if (Keyboard.IsKeyDown(Key.Z))
                {
                    c = COMMANDS.EDITOR_ROTATE_UP;
                }

                if (Keyboard.IsKeyDown(Key.X))
                {
                    c = COMMANDS.EDITOR_ROTATE_DOWN;
                }

                if (Keyboard.IsKeyDown(Key.LeftCtrl) && Keyboard.IsKeyToggled(Key.T))
                {
                    c = COMMANDS.EDITOR_ROTATE_TOP;
                }
            }





            if (host.IsFocused)
            {
                UnrealScienceScripting.TestUpdate((int)c, (float)difference.X, (float)difference.Y);
            }



            //Update();
            UnrealScienceScripting.Render();



            //Update();
        }

        private void field_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                string command = field.Text;

                Scripting.ScriptingManager.Parse(command);

                field.Text = "";

                box.Text += command + "\n";
            }
        }

        private void host_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            float aspectRatio = panel.Height / (panel.Width * 1.0f);

            UnrealScienceScripting.ResizeViewport(aspectRatio);
        }

        private void panel_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {

            host.Focus();

            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                isHold = true;

                p = GetMousePositionWindowsForms();
            }
        }

        private void panel_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                isHold = false;

                p = GetMousePositionWindowsForms();

                difference.X = 0;
                difference.Y = 0;

                //Mouse.OverrideCursor = Cursors.Arrow;

                panel.Cursor = System.Windows.Forms.Cursors.Arrow;
            }
        }

        private void panel_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {

            if (isHold)
            {
                if (host.IsFocused)
                {
                    Point curr = GetMousePositionWindowsForms();

                    difference = new Point();

                    difference.X = (curr.X - p.X) / 900;
                    difference.Y = -(curr.Y - p.Y) / 900;

                    //TestUpdate((int)c, (float)(difference.X), (float)(difference.Y));
                }
            }

        }

        private void CreateBox_Click(object sender, RoutedEventArgs e)
        {
            string query = "create box";

            Scripting.ScriptingManager.Parse(query);
        }

        private void SubmitAnimation_Click(object sender, RoutedEventArgs e)
        {
            string[] tokens = AnimationField.Text.Split('\n');

            Scripting.AnimationManager.Parse("reset");

            for (int i = 0; i < tokens.Length; i++)
            {
                Scripting.AnimationManager.Parse(tokens[i]);
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

            string fileName = System.Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) + "Temp" + ".usscene";

            //string fileName = @"C:\Users\Илькин\Desktop\test.usscene";

            SaveSceneTo(fileName);

            Process.Start("UnrealSciencePlayer.exe", fileName);
        }

        private void SaveSceneTo(string path)
        {
            Save save = new Save();

            save.Scene = UnrealScienceScripting.World;

            var task = new Task(() => save.Serialize(path));

            task.Start();

            task.Wait();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog d = new OpenFileDialog();

            d.Filter = "Unreal Science Scene files (*.usscene)|*.usscene";

            d.InitialDirectory = Environment.SpecialFolder.MyDocuments.ToString();



            if (d.ShowDialog() == System.Windows.Forms.DialogResult.OK && d.FileName.Length > 0)
            {

                if (System.Windows.MessageBox.Show("Do you want to save the scene?", "Save?", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    SaveFileDialog save = new SaveFileDialog();

                    save.Filter = "Unreal Science Scene files (*.usscene)|*.usscene";

                    save.InitialDirectory = Environment.SpecialFolder.MyDocuments.ToString();

                    if (save.ShowDialog() == System.Windows.Forms.DialogResult.OK && save.FileName.Length > 0)
                    {
                        SaveSceneTo(save.FileName);
                    }
                }

                SavedFilename = d.FileName;

                UnrealScienceScripting.Cleanup();
                UnrealScienceScripting.CleanUI();

                UnrealScienceScripting.World.Entities.Clear();
                Hierarchy.Items.Clear();

                Read r = new Read();

                Scripting.isPlaying = false;

                r.Deserialize(d.FileName);

                #region entities
                foreach (SceneEntity s in r.Scene.Entities)
                {
                    Scripting.ScriptingManager.Parse(s.CreationCommand);

                    Scripting.ScriptingManager.Parse(String.Format("move {0} {1} {2}",
                        s.Transform.Position.X,
                        s.Transform.Position.Y,
                        s.Transform.Position.Z));

                    Scripting.ScriptingManager.Parse(String.Format("rotate {0} {1} {2}",
                        s.Transform.Rotation.X,
                        s.Transform.Rotation.Y,
                        s.Transform.Rotation.Z));

                    Scripting.ScriptingManager.Parse(String.Format("scale {0} {1} {2}",
                        s.Transform.Scale.X,
                        s.Transform.Scale.Y,
                        s.Transform.Scale.Z));

                    Scripting.ScriptingManager.Parse("setTexture " + s.Texture);

                    Scripting.ScriptingManager.Parse(String.Format("setColor {0} {1} {2}", s.Color.X, s.Color.Y, s.Color.Z));

                    if (s.Animation.AnimationKeys.Count != 0)
                    {
                        foreach (AnimationKey key in s.Animation.AnimationKeys)
                        {
                            Vector3D v = new Vector3D();

                            if (key.KeyType == 1)
                            {
                                v = key.Destination.Position;
                            }
                            else if (key.KeyType == 2)
                            {
                                v = key.Destination.Rotation;
                            }
                            else if (key.KeyType == 3)
                            {
                                v = key.Destination.Scale;
                            }

                            string type = "";

                            if (key.KeyType == 1)
                            {
                                type = "position";
                            }
                            else if (key.KeyType == 2)
                            {
                                type = "rotation";
                            }
                            else if (key.KeyType == 3)
                            {
                                type = "scale";
                            }

                            Scripting.AnimationManager.Parse(String.Format("setKey {0} {1} {2} {3} {4} {5}",
                                type, key.StartOrder, key.Duration, v.X, v.Y, v.Z));
                        }
                    }
                }
                #endregion

                #region create_UI

                foreach (UnrealScienceLibrary.UIElement element in r.Scene.Elements)
                {
                    if (element is Text2D)
                    {
                        //Scripting.ScriptingManager.Parse("addText {0} {1} {2} {3} {4} {5}",
                        //    (element as Text2D).Text, );

                        Text2D t = element as Text2D;

                        UnrealScienceScripting.AddText2D(t.Text, t.FontName, (int)t.Position.X, (int)t.Position.Y, (int)t.Scale.X, (int)t.Scale.Y, (int)t.FontSize);
                    }
                }

                #endregion
            }
        }

        bool deleted = false;

        private void Hierarchy_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (!deleted)
            {
                Scripting.ScriptingManager.Parse("select " + (Hierarchy.SelectedIndex + 1));

                PropertyGrid.Visibility = System.Windows.Visibility.Visible;
            }

            if(Hierarchy.SelectedIndex == -1)
            {
                Scripting.ScriptingManager.Parse("select 0");

                PropertyGrid.Visibility = System.Windows.Visibility.Collapsed;
            }

            deleted = false;
        }

        private void ShowProperties_Click(object sender, RoutedEventArgs e)
        {
            if (Properties.IsHidden)
            {
                Properties.Show();
            }

        }

        private void ShowConsole_Click(object sender, RoutedEventArgs e)
        {
            if (Console.IsHidden)
            {
                Console.Show();
            }
        }

        private void ShowAnimation_Click(object sender, RoutedEventArgs e)
        {
            if (Animation.IsHidden)
            {
                Animation.Show();
            }
        }

        private void Say_Click(object sender, RoutedEventArgs e)
        {
            Say.IsEnabled = false;
            //Stop.IsEnabled = true;

            Choices c = new Choices();
            c.Add(new string[] { "create", "translate", "increase", "decrease", "delete" });

            Grammar gr = new Grammar(new GrammarBuilder(c));

            try
            {
                engine.RequestRecognizerUpdate();

                engine.LoadGrammar(gr);

                engine.SpeechRecognized += engine_SpeechRecognized;

                engine.SetInputToDefaultAudioDevice();

                engine.RecognizeAsync(RecognizeMode.Multiple);
            }
            catch
            {
                return;
            }
        }

        void engine_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            if (e.Result.Text == "create")
            {
                Scripting.ScriptingManager.Parse("create box");
            }

            if (e.Result.Text == "translate")
            {
                Scripting.ScriptingManager.Parse("translate 1 1 1");
            }

            if (e.Result.Text == "increase")
            {
                Scripting.ScriptingManager.Parse("incDec 1 1 1");
            }
            if (e.Result.Text == "decrease")
            {
                Scripting.ScriptingManager.Parse("incDec -1 -1 -1");
            }
            if (e.Result.Text == "delete")
            {
                deleted = true;
                Scripting.ScriptingManager.Parse("delete");
            }

        }


        SpeechRecognitionEngine engine = new SpeechRecognitionEngine();
        private string SavedFilename = "";

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            Say.IsEnabled = true;
            //Stop.IsEnabled = false;


        }

        private void CreateSphere_Click(object sender, RoutedEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/sphere.obj");
        }

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            UnrealScienceScripting.ChangeCameraSpeed((float)CameraSpeed.Value);

            if (host != null)
                host.Focus();
        }

        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/sphere.obj");
        }

        private void Image_MouseLeftButtonDown_1(object sender, MouseButtonEventArgs e)
        {
            Scripting.ScriptingManager.Parse("create box");
        }

        private void CreatePlane_Click(object sender, RoutedEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/plane.obj");
        }

        private void CreateCone_Click(object sender, RoutedEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/cone.obj");
        }

        private void Image_MouseLeftButtonDown_2(object sender, MouseButtonEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/cone.obj");
        }

        private void CreateCylinder_Click(object sender, RoutedEventArgs e)
        {
            Scripting.ScriptingManager.Parse("loadFromModel models/cylinder.obj");
        }

        private void Image_MouseLeftButtonDown_3(object sender, MouseButtonEventArgs e)
        {
            Scripting.ScriptingManager.Parse("clone");
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            Save();
        }

        public void Save()
        {
            if (SavedFilename != "")
            {
                SaveSceneTo(SavedFilename);
            }
            else
            {

                SaveFileDialog save = new SaveFileDialog();

                save.Filter = "Unreal Science Scene files (*.usscene)|*.usscene";

                save.InitialDirectory = Environment.SpecialFolder.MyDocuments.ToString();

                if (save.ShowDialog() == System.Windows.Forms.DialogResult.OK && save.FileName.Length > 0)
                {
                    SaveSceneTo(save.FileName);
                    SavedFilename = save.FileName;
                }
            }
        }

        private void MenuItem_Click_2(object sender, RoutedEventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();

            save.Filter = "Unreal Science Scene files (*.usscene)|*.usscene";

            save.InitialDirectory = Environment.SpecialFolder.MyDocuments.ToString();

            if (save.ShowDialog() == System.Windows.Forms.DialogResult.OK && save.FileName.Length > 0)
            {
                SaveSceneTo(save.FileName);
            }
        }

        private void MenuItem_Click_3(object sender, RoutedEventArgs e)
        {
            if (System.Windows.MessageBox.Show("Do you want to save the scene?", "Save?", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                Save();
            }
            Close();
        }

        private void Image_MouseLeftButtonDown_4(object sender, MouseButtonEventArgs e)
        {
            Save();
        }

        private void Image_MouseLeftButtonDown_5(object sender, MouseButtonEventArgs e)
        {
            OpenFileDialog d = new OpenFileDialog();

            d.Filter = "OBJ (*.obj)|*.obj";

            d.InitialDirectory = Environment.SpecialFolder.MyDocuments.ToString();

            if (d.ShowDialog() == System.Windows.Forms.DialogResult.OK && d.FileName.Length > 0)
            {
                Scripting.ScriptingManager.Parse("loadFromModel " + d.FileName);
            }
        }

        private void Hierarchy_MouseDown(object sender, MouseButtonEventArgs e)
        {
            HitTestResult r = VisualTreeHelper.HitTest(this, e.GetPosition(this));

            if (r.VisualHit.GetType() != typeof(System.Windows.Controls.ListBoxItem))
            {
                Hierarchy.UnselectAll();

                Scripting.ScriptingManager.Parse("select 0");

                PropertyGrid.Visibility = System.Windows.Visibility.Collapsed;
            }

        }

        private void HierarchyDelete_Click(object sender, RoutedEventArgs e)
        {
            if(Hierarchy.SelectedIndex != -1)
            {
                Hierarchy.Items.RemoveAt(Hierarchy.SelectedIndex);

                Scripting.ScriptingManager.Parse("delete");
            }
        }

        private string GetEntityName(int index)
        {
            return ((Hierarchy.Items[index] as ListBoxItem).Content as TextBlock).Text;
        }

        private void SetEntityName(int index, string text)
        {
            ((Hierarchy.Items[index] as ListBoxItem).Content as TextBlock).Text = text;
        }

        private void HierarchyRename_Click(object sender, RoutedEventArgs e)
        {
            string new_name = Prompt.ShowDialog(GetEntityName(Hierarchy.SelectedIndex), "Change Name");

            SetEntityName(Hierarchy.SelectedIndex, new_name);

            UnrealScienceScripting.ChangeName(new_name);
        }
    }
}
