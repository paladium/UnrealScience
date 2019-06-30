using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace UnrealScienceLibrary
{
    public class UnrealScienceScripting
    {
        #region Marschaling

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern unsafe void InitD3D(void* hwnd, int width, int height);


        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern unsafe bool InitInput(void* hInstance);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void Update();

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void InitWorld();

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void Render();

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void TestUpdate(int t, float x, float y);

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void Cleanup();



        #region console_functions
        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void CreateObject(int type);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void MoveObject(float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void ResizeObject(float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void SelectObject1(int index);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void DeleteEntity();

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void SetTexture(string t);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void Translate(float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void IncreaseDecrease(float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void ChangeName(string name);

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void StartAnimation();

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void CreateFromModel(string model);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void Rotate(float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void Next();

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void Prev();

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void ChangeColor(int r, int g, int b);

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void Clone();

        #endregion



        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void ResizeViewport(float to);
        

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static public extern void ChangeCameraSpeed(float to);


        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void AddKey(int type, int start, float duration, float x, float y, float z);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void SetProperty(int property, int value);

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void Reset();

        #region object`s data

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern int EntityNumber();

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern IntPtr GetPosition(int index);

        [DllImport("Engine.dll", SetLastError=true)]
        static public extern unsafe void ReleaseMemory(ref void* p);

        [DllImport("Engine.dll", SetLastError=true)]
        static public extern unsafe bool ChechPointerIsCorrect(void* ptr);

        #endregion

        #region UI Editor

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void ClearUI();

        [DllImport("Engine.dll", SetLastError = true)]
        static extern void InitUI();

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void SetPlaying();

        [DllImport("Engine.dll", SetLastError = true, CallingConvention=CallingConvention.Cdecl)]
        static extern void AddLabel([MarshalAs(UnmanagedType.LPWStr)]String text, [MarshalAs(UnmanagedType.LPStr)]String fontName, int posX, int posY, int sizeX, int sizeY, int fontSize);

        [DllImport("Engine.dll", SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void AddSprite([MarshalAs(UnmanagedType.LPStr)]String path, int posX, int posY, int sizeX, int sizeY);

        #endregion

        #region Graph3D
        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void IsDrawGraph(bool state);

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void SetType(int type);

        [DllImport("Engine.dll", SetLastError = true, ExactSpelling=true)]
        static public extern void AddGraph3DVertex(float x, float y, float z, float r, float g, float b);

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void InitializeGraph();

        [DllImport("Engine.dll", SetLastError = true)]
        static public extern void ResetGraph3D();


        [DllImport("Engine.dll", SetLastError=true)]
        static public extern void BuildGraph3D([MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.R4)]float[] x, 
            [MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.R4)]float[] y,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.R4)]float[] z, int size);
        #endregion

        #endregion


        public ScriptingManager ScriptingManager;
        public ScriptingManager AnimationManager;

        public Action<int> AddEntity;
        public Action<int> RemoveEntity;
        public Action<int> Select_Entity;
        public Action<int> RenameEntity;
        public Action CleanWorld;
        public Action<int> ChangeEntityColor;

        static public Scene World;

        public int current;

        public bool isPlaying = false;

        #region Ovveride c++ functions
        
        void CreateEntity(int type)
        {
            CreateObject(type);
            
            if(!isPlaying)
            {
                SceneEntity s = new SceneEntity();

                s.CreationCommand = "create " + ScriptingManager.EnumParam["create"].FirstOrDefault(x => x.Value == type).Key.ToLower();

                s.Color = new Vector3D(255, 255, 255);

                

                //s.Texture = "test.png";

                World.Entities.Add(s);

                current = World.Entities.Count - 1;

                AddEntity.Invoke(current);
            }
            
        }

        void LoadFromModel(string path)
        {
            CreateFromModel(path);

            if(!isPlaying)
            {
                SceneEntity s = new SceneEntity();

                s.CreationCommand = "loadFromModel " + path;

                //s.Texture = "test.png";

                World.Entities.Add(s);

                current = World.Entities.Count - 1;

                AddEntity.Invoke(current);
            }
            
        }

        void MoveEntity(float x, float y, float z)
        {
            MoveObject(x, y, z);

            if(!isPlaying)
            {
                World.Entities[current].Transform.Position = new Vector3D(x, y, z);
            }
            
        }

        void RotateEntity(float x, float y, float z)
        {
            Rotate(x, y, z);

            if(!isPlaying)
            {
                World.Entities[current].Transform.Rotation = new Vector3D(x, y, z);
            }
            
        }

        void ScaleEntity(float x, float y, float z)
        {
            ResizeObject(x, y, z);

            if(!isPlaying)
            {
                World.Entities[current].Transform.Scale = new Vector3D(x, y, z);
            }
            
        }

        void IncreaseDecreaseEntity(float x, float y, float z)
        {
            IncreaseDecrease(x, y, z);

            if(!isPlaying)
            {
                World.Entities[current].Transform.Scale.X += x;
                World.Entities[current].Transform.Scale.Y += y;
                World.Entities[current].Transform.Scale.Z += z;
            }
        }

        void SelectEntity(int s)
        {
            SelectObject1(s);
            if(!isPlaying)
            {
                current = s - 1;

                Select_Entity.Invoke(current);
            }
            
        }

        void TranslateEntity(float x, float y, float z)
        {
            Translate(x, y, z);

            if(!isPlaying)
            {
                World.Entities[current].Transform.Position.X += x;
                World.Entities[current].Transform.Position.Y += y;
                World.Entities[current].Transform.Position.Z += z;
            }
        }

        void SetEntityTexture(string path)
        {
            SetTexture(path);

            if(!isPlaying)
            {
                World.Entities[current].Texture = path;
            }
        }

        void DeleteEntity1()
        {
            

            DeleteEntity();

            if(!isPlaying)
            {
                if(current < World.Entities.Count && current >= 0)
                {
                    World.Entities.RemoveAt(current);

                    RemoveEntity.Invoke(current);

                    if(World.Entities.Count != 0)
                    {
                        current = World.Entities.Count;

                        SelectEntity(current);
                    }
                    
                }
                
            }
        }

        void ChangeEntity_Color(int r, int g, int b)
        {
            ChangeColor(r, g, b);

            if(!isPlaying)
            {
                World.Entities[current].Color = new Vector3D(r, g, b);
                ChangeEntityColor.Invoke(current);
            }
        }

        void Copy()
        {
            Clone();

            if(!isPlaying)
            {
                World.Entities.Add(World.Entities[current]);

                current = World.Entities.Count - 1;

                AddEntity.Invoke(current);
            }
        }

        void AddAnimationKey(int type, int start, float duration, float x, float y, float z)
        {
            AddKey(type, start, duration, x, y, z);

            if(!isPlaying)
            {
                AnimationKey key = new AnimationKey() { KeyType = type, StartOrder = start, Duration = duration};

                Transformation t = new Transformation();

                if(type == 1)
                {
                    t.Position = new Vector3D(x, y, z);
                }
                else if(type == 2)
                {
                    t.Rotation = new Vector3D(x, y, z);
                }
                else if(type == 3)
                {
                    t.Scale = new Vector3D(x, y, z);
                }

                key.Destination = t;

                key.OwnerID = current;

                World.Entities[current].Animation.AnimationKeys.Add(key);


            }
        }

        void ResetAnimator()
        {
            Reset();

            if(!isPlaying)
            {
                World.Entities[current].Animation.AnimationKeys.Clear();
            }
            
        }

        public static void CleanUI()
        {
            ClearUI();

            World.Elements.Clear();
           
        }

        public static void PushAnimationKeys(List<AnimationKey> keys)
        {
            foreach(AnimationKey k in keys)
            {
                SelectObject1(k.OwnerID);

                Reset();

                World.Entities[k.OwnerID].Animation.AnimationKeys.Clear();

                Vector3D v = new Vector3D();

                if (k.KeyType == 1)
                {
                    v = k.Destination.Position;
                }
                else if (k.KeyType == 2)
                {
                    v = k.Destination.Rotation;
                }
                else v = k.Destination.Scale;

                

                AddKey(k.KeyType, k.StartOrder, k.Duration, v.X, v.Y, v.Z);

                World.Entities[k.OwnerID].Animation.AnimationKeys.Add(k);
            }
        }

        public static void InitializeUI()
        {
            InitUI();
        }

        public static void AddText2D(String text, String fontName, int posX, int posY, int sizeX, int sizeY, int fontSize)
        {
            AddLabel(text, fontName, posX, posY, sizeX, sizeY, fontSize);

            Text2D t = new Text2D();

            t.Text = text;
            t.FontName = fontName;
            t.Position = new Vector2D(posX, posY);
            t.Scale = new Vector2D(sizeX, sizeY);

            World.Elements.Add(t);
        }

        public static void AddSprite2D(String path, int posX, int posY, int sizeX, int sizeY)
        {
            AddSprite(path, posX, posY, sizeX, sizeY);

            Sprite2D sprite = new Sprite2D();

            sprite.TexturePath = path;
            sprite.Position = new Vector2D(posX, posY);
            sprite.Scale = new Vector2D(sizeX, sizeY);

            World.Elements.Add(sprite);
        }

        #endregion

        public UnrealScienceScripting()
        {
            if(World != null)
            {
                World.Elements.Clear();
                World.Entities.Clear();
            }
            
            World = new Scene();
        }

        public void InitScripting()
        {
            ScriptingManager = new ScriptingManager();

            ScriptingManager.functions["create"] = new Action<int>(CreateEntity);
            ScriptingManager.EnumParam["create"] = new Dictionary<string, int>(StringComparer.InvariantCultureIgnoreCase) { 
                {
                    "None", 0
                },
                {
                    "Box", 1
                },
                {
                    "Cube", 1
                },
            };

            ScriptingManager.functions["loadFromModel"] = new Action<string>(LoadFromModel);

            //ScriptingManager.functions["создать"] = ScriptingManager.functions["create"];
            //ScriptingManager.EnumParam["создать"] = ScriptingManager.EnumParam["create"];

            ScriptingManager.functions["move"] = new Action<float, float, float>(MoveEntity);

            ScriptingManager.functions["select"] = new Action<int>(SelectEntity);

            ScriptingManager.functions["scale"] = new Action<float, float, float>(ScaleEntity);

            ScriptingManager.functions["rotate"] = new Action<float, float, float>(RotateEntity);

            ScriptingManager.functions["incDec"] = new Action<float, float, float>(IncreaseDecreaseEntity);

            ScriptingManager.functions["delete"] = new Action(DeleteEntity1);

            ScriptingManager.functions["setTexture"] = new Action<string>(SetEntityTexture);

            ScriptingManager.functions["translate"] = new Action<float, float, float>(TranslateEntity);

            ScriptingManager.functions["name"] = new Action<string>(ChangeName);

            ScriptingManager.functions["setColor"] = new Action<int, int, int>(ChangeEntity_Color);

            ScriptingManager.functions["startAnimation"] = new Action(StartAnimation);

            ScriptingManager.functions["clone"] = new Action(Copy);

            ScriptingManager.functions["next"] = new Action(Next);

            ScriptingManager.functions["prev"] = new Action(Prev);

            //UI language

            ScriptingManager.functions["clearUI"] = new Action(CleanUI);

            ScriptingManager.functions["initUI"] = new Action(InitializeUI);

            ScriptingManager.functions["addText"] = new Action<string, string, int, int, int, int, int>(AddText2D);

            ScriptingManager.ProcessSyntax();
        }

        public void InitAnimationScripting()
        {
            AnimationManager = new ScriptingManager();

            AnimationManager.functions["setKey"] = new Action<int, int, float, float, float, float>(AddAnimationKey);


            AnimationManager.EnumParam["setKey"] = new Dictionary<string, int>(StringComparer.InvariantCultureIgnoreCase)
            {
                {
                    "Position", 1
                },
                {
                    "Rotation", 2
                },
                {
                    "Scale", 3
                }
            };

            AnimationManager.functions["reset"] = new Action(ResetAnimator);

            AnimationManager.functions["setProperty"] = new Action<int, int>(SetProperty);

            AnimationManager.EnumParam["setProperty"] = new Dictionary<string, int>(StringComparer.InvariantCultureIgnoreCase) 
            { 
                {
                    "None", 0
                },
                {
                    "Endless", 1
                },
                {
                    "True", 1
                },
                {
                    "False", 0
                },
                {
                    "No", 0
                },
                {
                    "Yes", 1
                }
            };

            AnimationManager.ProcessSyntax();
        }

        [DllImport("kernel32.dll", SetLastError = false)]
        static extern void CopyMemory(IntPtr destination, IntPtr source, UIntPtr length);

        public static void Copy<T>(ref IntPtr source, T[] destination, int startIndex, int length)
            where T : struct
        {
            var gch = GCHandle.Alloc(destination, GCHandleType.Pinned);
            try
            {
                var targetPtr = Marshal.UnsafeAddrOfPinnedArrayElement(destination, startIndex);
                var bytesToCopy = Marshal.SizeOf(typeof(T)) * length;

                CopyMemory(targetPtr, source, (UIntPtr)bytesToCopy);
            }
            finally
            {
                gch.Free();
                //unsafe
                //{
                //    ReleaseMemory(source.ToPointer());
                //}
                
            }
        }

        
    }

    public static class Util
    {

        public static int ParseInt(string source)
        {
            int res = 0;

            int.TryParse(source, out res);

            return res;
        }

        public static float ParseFloat(string source)
        {
            float res = 0;

            float.TryParse(source, out res);

            return res;
        }

        public static T ParseEnum<T>(string value)
        {
            return (T)Enum.Parse(typeof(T), value, true);
        }

    }

    public class ScriptingManager
    {

        public Dictionary<string, Delegate> functions;

        public Dictionary<string, List<string>> FunctionSyntax;

        public Dictionary<string, Dictionary<string, int>> EnumParam;

        public ScriptingManager()
        {
            functions = new Dictionary<string, Delegate>();

            FunctionSyntax = new Dictionary<string, List<string>>();

            EnumParam = new Dictionary<string, Dictionary<string, int>>(StringComparer.InvariantCultureIgnoreCase);
        }

        public void ProcessSyntax()
        {
            foreach (string key in functions.Keys)
            {
                FunctionSyntax.Add(key, new List<string>());
                foreach (System.Reflection.ParameterInfo p in functions[key].Method.GetParameters())
                {
                    FunctionSyntax[key].Add(p.ParameterType.ToString());
                }


            }
        }

        public bool Parse(string command)
        {
            foreach (string key in functions.Keys)
            {
                if (command.StartsWith(key) && command.Length >= key.Length)
                {
                    string options = command.Substring(key.Length);

                    options = options.Trim();

                    string[] parts = options.Split(' ');

                    object[] parameters = null;

                    bool hasParameters = false;

                    if (FunctionSyntax[key].Count > 0)
                    {
                        parameters = new object[parts.Length];

                        for (int i = 0; i < parts.Length; i++)
                        {
                            parameters[i] = null;
                        }

                        hasParameters = true;
                    }




                    int k = 0;

                    if (hasParameters)
                    {
                        foreach (string t in parts)
                        {
                            //we have parameters
                            if (FunctionSyntax[key].Count > 0)
                            {
                                if (FunctionSyntax[key][k] == "System.Int32")
                                {
                                    int f = 0;

                                    if (EnumParam.ContainsKey(key))
                                    {
                                        if (EnumParam[key].ContainsKey(t))
                                        {
                                            f = EnumParam[key][t];
                                        }
                                        else
                                        {
                                            f = Util.ParseInt(t);
                                        }

                                    }
                                    else
                                    {
                                        f = Util.ParseInt(t);
                                    }

                                    parameters[k] = f;
                                }

                                else if (FunctionSyntax[key][k] == "System.Single")
                                {
                                    float f = 0;

                                    f = Util.ParseFloat(t);

                                    parameters[k] = f;
                                }

                                else if (FunctionSyntax[key][k] == "System.String")
                                {
                                    parameters[k] = t;
                                }

                                k++;
                            }


                        }
                    }



                    if (hasParameters)
                    {
                        if (parameters.Length == FunctionSyntax[key].Count)
                            functions[key].DynamicInvoke(parameters);
                    }
                    else
                    {
                        functions[key].DynamicInvoke();
                    }



                    return true;
                }
            }

            return false;
        }
    }

}
