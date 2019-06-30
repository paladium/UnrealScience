using System;
using System.Collections.Generic;
using System.Linq;
using System.Speech.Recognition;
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

namespace UnrealSciencePlayer
{
    /// <summary>
    /// Interaction logic for Player.xaml
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

    public partial class Player : Window
    {

        Read Reader;

        public Player()
        {
            InitializeComponent();

            Reader = new Read();
        }

        System.Windows.Forms.Timer timer;

        UnrealScienceScripting Scripting;

        bool loaded = false;

        COMMANDS c;

        Point p;

        bool isHold = false;

        Point difference;

        bool isArray = false;
      
        public static Point GetMousePositionWindowsForms()
        {
            System.Drawing.Point point = System.Windows.Forms.Control.MousePosition;
            return new Point(point.X, point.Y);
        }

        SpeechRecognitionEngine engine = new SpeechRecognitionEngine();

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            UnrealScienceScripting.SetPlaying();

            unsafe
            {
                UnrealScienceScripting.InitD3D(panel.Handle.ToPointer(),
                    System.Windows.Forms.SystemInformation.VirtualScreen.Width,
                    System.Windows.Forms.SystemInformation.VirtualScreen.Height);

                loaded = true;
            }


            UnrealScienceScripting.InitWorld();

            timer = new System.Windows.Forms.Timer();

            timer.Interval = 10;

            timer.Tick += timer_Tick;

            timer.Start();

            Scripting = new UnrealScienceScripting();

            Scripting.InitScripting();

            Scripting.InitAnimationScripting();

            if(UnrealScienceScripting.World.Entities.Count != 0)
            {
                Scripting.isPlaying = true;
                CreateScene(UnrealScienceScripting.World);
                isArray = true;
            }
            else if (Reader.Scene != null)
            {
                Scripting.isPlaying = true;
                CreateScene(Reader.Scene);
            }

            Resize();

            InitSpeech();
        }

        public void InitSpeech()
        {

            Choices c = new Choices();
            c.Add(new string[] { "next" });

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

        private void engine_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            if (e.Result.Text == "next")
            {
                Scripting.ScriptingManager.Parse("next");
            }
        }

        public void CreateScene(Scene World)
        {
            #region generate_world
            foreach (SceneEntity s in World.Entities)
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

                if(s.Animation.AnimationKeys.Count != 0)
                {
                    foreach(AnimationKey key in s.Animation.AnimationKeys)
                    {
                        Vector3D v = new Vector3D();

                        if(key.KeyType == 1)
                        {
                            v = key.Destination.Position;
                        }
                        else if(key.KeyType == 2)
                        {
                            v = key.Destination.Rotation;
                        }
                        else if(key.KeyType == 3)
                        {
                            v = key.Destination.Scale;
                        }

                        string type = "";

                        if(key.KeyType == 1)
                        {
                            type = "position";
                        }
                        else if(key.KeyType == 2)
                        {
                            type = "rotation";
                        }
                        else if(key.KeyType == 3)
                        {
                            type = "scale";
                        }

                        Scripting.AnimationManager.Parse(String.Format("setKey {0} {1} {2} {3} {4} {5}",
                            type, key.StartOrder, key.Duration, v.X, v.Y, v.Z));
                    }
                }

                

                if(s.Animation.AnimationKeys.Count != 0)
                {
                    Scripting.ScriptingManager.Parse("startAnimation");
                    
                }
            }
            //Scripting.ScriptingManager.Parse("select 1");
            #endregion

            #region create_UI

            foreach(UnrealScienceLibrary.UIElement element in World.Elements)
            {
                if(element is Text2D)
                {
                    //Scripting.ScriptingManager.Parse("addText {0} {1} {2} {3} {4} {5}",
                    //    (element as Text2D).Text, );

                    Text2D t = element as Text2D;

                    //UnrealScienceScripting.AddSprite2D("back.jpg", (int)t.Position.X, (int)t.Position.Y, 1000, 500);

                    UnrealScienceScripting.AddText2D(t.Text, t.FontName, (int)t.Position.X, (int)t.Position.Y, (int)t.Scale.X, (int)t.Scale.Y, (int)t.FontSize);
                }
            }

            UnrealScienceScripting.InitializeUI();

            

            #endregion
        }

        public void StartReading(string from)
        {
            Reader.Deserialize(from);
        }

        void timer_Tick(object sender, EventArgs e)
        {
            c = COMMANDS.NONE;


            if (isHold)
            {
                panel.Cursor = System.Windows.Forms.Cursors.Hand;
            }

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

            UnrealScienceScripting.TestUpdate((int)c, (float)difference.X, (float)difference.Y);

            UnrealScienceScripting.Render();
        }

        private void host_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            Resize();
        }

        void Resize()
        {
            if (loaded)
            {
                float aspectRatio = panel.Height / (panel.Width * 1.0f);

                UnrealScienceScripting.ResizeViewport(aspectRatio);
            }
        }

        private void panel_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
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

        private void Next_Click(object sender, RoutedEventArgs e)
        {
            
            Scripting.ScriptingManager.Parse("next");
        }

       

    }
}
