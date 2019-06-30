using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace UnrealScienceLibrary
{
    [Serializable]
    
    public class Vector3D
    {
        public float X { get; set; }

        public float Y { get; set; }

        public float Z { get; set; }

        public Vector3D() { }

        public Vector3D(float _x, float _y, float _z)
        {
            X = _x;
            Y = _y;
            Z = _z;
        }
    }

    [Serializable]
    public class Vector2D
    {
        public float X { get; set; }

        public float Y { get; set; }

        public Vector2D(){}

        public Vector2D(float _x, float _y)
        {
            X = _x;
            Y = _y;
        }
    }

    public class Transformation
    {
        
        public Vector3D Position { get; set; }

        public Vector3D Rotation { get; set; }

        public Vector3D Scale { get; set; }

        public Transformation()
        {
            Position = new Vector3D();
            Rotation = new Vector3D();
            Scale = new Vector3D(1, 1, 1);
        }
    }

    [Serializable]
    public class AnimationKey
    {
        [XmlIgnore]
        public int OwnerID;

        public Transformation Start;

        public Transformation Destination;

        public int KeyType;

        public float Duration { get; set; }

        public int StartOrder { get; set; }

        public AnimationKey()
        {
            Start = new Transformation();

            Destination = new Transformation();
        }
    }

    [Serializable]
    public class Animation
    {
        public List<AnimationKey> AnimationKeys { get; set; } 

        public Animation()
        {
            AnimationKeys = new List<AnimationKey>();
        }
    }

    [Serializable]
    
    public class SceneEntity
    {
        
        public Transformation Transform { get; set; }

        public string Texture { get; set; }
        
        public Animation Animation { get; set; }

        public string CreationCommand { get; set; }

        public Vector3D Color { get; set; }

        public SceneEntity()
        {
            Transform = new Transformation();

            Animation = new Animation();

            Color = new Vector3D();
        }
    }


    [Serializable]
    public class Scene
    {
        public List<SceneEntity> Entities { get; set; }

        
        public List<UIElement> Elements { get; set; }

        public Scene()
        {
            Entities = new List<SceneEntity>();

            Elements = new List<UIElement>();
        }
    }

    public class Save
    {
        public Scene Scene { get; set; }

        
        public void Serialize(string to)
        {
            XmlSerializer formatter = new XmlSerializer(typeof(Scene));

            using(FileStream fs = new FileStream(to, FileMode.Create))
            {
                formatter.Serialize(fs, Scene);
            }
        }
    }

    public class Read
    {
        public Scene Scene { get; set; }

        public void Deserialize(string from)
        {

            XmlSerializer formatter = new XmlSerializer(typeof(Scene));

            //using(StreamReader s = new StreamReader(from))
            //{
            //    Scene = (Scene)formatter.Deserialize(s);
            //}

            using (FileStream fs = new FileStream(from, FileMode.Open))
            {
                Scene = (Scene)formatter.Deserialize(fs);
            }
        }

        
    }

    #region UI

    [XmlInclude(typeof(Text2D))]
    [XmlInclude(typeof(Sprite2D))]
    public class UIElement
    {
        public Vector2D Position { get; set; }

        public Vector2D Scale { get; set; }
    }

    [Serializable]
    public class Text2D : UIElement
    {
        public string Text { get; set; }

        public string FontName { get; set; }

        public float FontSize { get; set; }
    }

    [Serializable]
    public class Sprite2D : UIElement
    {
        public string TexturePath { get; set; }
    }


    #endregion


}
