using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace ParticleTool
{
    class CParticle
    {
        protected Vector2 position;
        protected Vector2 scale;
        protected Vector4 color;
        protected float rotation;
        protected float life;

        public Vector2 Position{ get { return position; } set { position = value; } }
        public Vector2 Scale   { get { return scale; }    set { scale = value; } }
        public Vector4 Color   { get { return color; }    set { color = value; } }
        public float Rotation  { get { return rotation; } set { rotation = value; } }
        public float Life      { get { return life; }     set { life = value; } }
    }
}