using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ParticleTool
{
    class Particle
    {
        public Color color;
        public float posX;
        public float posY;
        public float velX;
        public float velY;
        public float size_p;
        public float rotation;
        public float life;
        public float curLife;
        
        public Color Color{ get { return color; } set { color = value; } }
        public float PosX { get { return posX; } set { posX = value; } }
        public float PosY { get { return posY; } set { posY = value; } }
        public float VelX { get { return velX; } set { velX = value; } }
        public float VelY { get { return velY; } set { velY = value; } }
        public float Size_p { get { return size_p; } set { size_p = value; } }
        public float Rotation { get { return rotation; } set { rotation = value; } }
        public float Life { get { return life; } set { life = value; } }

        public Particle()
        {
            curLife = 0.0f;
            color = Color.White;
            posX = 0.0f;
            posY = 0.0f;
            velX = 0.0f;
            velY = 0.0f;
            size_p = 0.0f;
            rotation = 0.0f;
            life = 1.0f;
        }
    }
}