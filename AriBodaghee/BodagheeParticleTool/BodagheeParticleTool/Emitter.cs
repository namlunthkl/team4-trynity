using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;


namespace ParticleTool
{
    class Emitter
    {
        List<CParticle>   m_lEmitter = new List<CParticle>();
        protected Vector2 position;
        protected Vector2 life;
        protected Vector2 velocityX;
        protected Vector2 velocityY;
        protected short   particles;

        public Vector2 Position { get { return position; } set { position = value; } }
        public Vector2 Life     { get { return life; }     set { life = value; } }
        public Vector2 VelocityX{ get { return velocityX; }set { velocityX = value; } }
        public Vector2 VelocityY{ get { return velocityY; }set { velocityY = value; } }
        public short   Particles{ get { return particles; }set { particles = value; } }
    }
}
