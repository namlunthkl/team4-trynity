using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using BodagheeParticleTool;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace ParticleTool
{
    class Emitter
    {
        public List<Particle> Particle_List = new List<Particle>();
        public bool continuous;
        public bool reAnimate;
        public int image;
        public string imageFile;

        Color colorStart;
        Color colorEnd;
        private float fSize;
        private float maxLife;
        private float minVelX;
        private float maxVelX;
        private float minVelY;
        private float maxVelY;
        private float spwnAreaWidth;
        private float spwnAreaHeight;
        private float scaleStart;
        private float scaleEnd;
        private float rotation;
        private int spwnPattern;
        private int source;
        private int dest;
        private float emitterPosX;
        private float emitterPosY;
        private int maxParticles;
        private float emitterVelX;
        private float emitterVelY;

        public Color ColorStart { get { return colorStart; } set { colorStart = value; } }
        public Color ColorEnd { get { return colorEnd; } set { colorEnd = value; } }
        public float FSize { get { return fSize; } set { fSize = value; } }
        public float MaxLife { get { return maxLife; } set { maxLife = value; } }
        public float MinVelX { get { return minVelX; } set { minVelX = value; } }
        public float MaxVelX {get { return maxVelX; } set { maxVelX = value; } }
        public float MinVelY { get { return minVelY; } set { minVelY = value; } }
        public float MaxVelY { get { return maxVelY; } set { maxVelY = value; } }
        public float SpwnAreaWidth {get { return spwnAreaWidth; }set { spwnAreaWidth = value; }}
        public float SpwnAreaHeight{ get { return spwnAreaHeight; }set { spwnAreaHeight = value; }}
        public float ScaleStart{ get { return scaleStart; } set { scaleStart = value; } }
        public float ScaleEnd{ get { return scaleEnd; }set { scaleEnd = value; }}
        public float Rotation{ get { return rotation; } set { rotation = value; } }
        public int SpwnPattern {get { return spwnPattern; } set { spwnPattern = value; } }
        public int Source{get { return source; }set { source = value; } }
        public int Dest{get { return dest; } set { dest = value; } }
        public float EmitterPosX{get { return emitterPosX; }set { emitterPosX = value; }}
        public float EmitterPosY{ get { return emitterPosY; }set { emitterPosY = value; }}
        public int MaxParticles { get { return maxParticles; }set { maxParticles = value; } }
        public float EmitterVelX {get { return emitterVelX; } set { emitterVelX = value; } }
        public float EmitterVelY {get { return emitterVelY; }set { emitterVelY = value; }}

        public Emitter()
        {
            image = 0;
            colorStart = Color.White;
            colorEnd = Color.White;
            fSize = 1.0f;
            maxLife = 1.0f;
            minVelX = 0;
            maxVelX = 0;
            minVelY = 0;
            maxVelY = 0;
            spwnAreaWidth = 2;
            spwnAreaHeight = 2;
            scaleStart = 0.0f;
            scaleEnd = 0.0f;
            rotation = 0.0f;
            spwnPattern = 0;
            source = 2;
            dest = 3;
            emitterPosX = 0;
            emitterPosY = 0;
            maxParticles = 0;
            emitterVelX = 0;
            emitterVelY = 0;
            continuous = true;
            reAnimate = false;
        }

        public void Update(float deltaTime)
        {
            for (int i = 0; i < Particle_List.Count(); i++)
            {
                Particle_List[i].rotation += rotation * deltaTime;
                Particle_List[i].life -= 1000 * deltaTime;
                Particle_List[i].Color = ColorOperator.Lerp(ColorEnd, ColorStart, Particle_List[i].life / 1000);
                
                Particle_List[i].posX += Particle_List[i].velX * deltaTime;
                Particle_List[i].posY += Particle_List[i].velY * deltaTime;

                if (scaleStart <= scaleEnd )
                {
                    Particle_List[i].size_p += 0.5f * deltaTime;
                    if (Particle_List[i].size_p >= scaleEnd)
                    {
                        Particle_List[i].size_p += 0;
                    }
                }
                if (scaleStart >= scaleEnd )
                {
                    Particle_List[i].size_p -= 0.5f * deltaTime;
                    if (Particle_List[i].size_p <= scaleStart)
                    {
                        Particle_List[i].size_p += 0;
                    }
                }

                EmitterPosX += EmitterVelX * deltaTime;
                EmitterPosY += EmitterVelY * deltaTime;

                if (Particle_List[i].Life < 0 && continuous)
                {
                    Respawn(Particle_List[i]);
                }
                //else if (reAnimate)
                //{
                // Respawn(Particle_List[i]);

                // if (i >= Particle_List.Count() - 1)
                // {
                //     reAnimate = false;
                // }
                // }
            }
        }
        public void Respawn(Particle p)
        {
            Random rand = new Random();
            p.Life = (float)(rand.Next(0, (int)MaxLife * 1000));
            p.Size_p = FSize;

            p.VelX = rand.Next((int)(MinVelX), (int)(MaxVelX));
            p.VelY = rand.Next((int)(MinVelY), (int)(MaxVelY));

            p.PosX = EmitterPosX - (rand.Next(0, (int)SpwnAreaWidth * 2 + 1) - SpwnAreaWidth) / 2;
            p.PosY = EmitterPosY - (rand.Next(0, (int)SpwnAreaHeight * 2 + 1) - SpwnAreaHeight) / 2;
        }
        public void Render()
        {
            int tempBlend1 = 0;
            int tempBlend2 = 0;

            tempBlend1 = (int)SGP.ManagedDirect3D.Instance.Device.RenderState.SourceBlend;
            tempBlend2 = (int)SGP.ManagedDirect3D.Instance.Device.RenderState.DestinationBlend;

            SGP.ManagedDirect3D.Instance.Sprite.Flush();

            SGP.ManagedDirect3D.Instance.Device.SetRenderState(Microsoft.DirectX.Direct3D.RenderStates.SourceBlend, this.Source);
            SGP.ManagedDirect3D.Instance.Device.SetRenderState(Microsoft.DirectX.Direct3D.RenderStates.DestinationBlend, this.Dest);

            for (int i = 0; i < this.Particle_List.Count; i++)
            {
                if (this.Particle_List[i].Life > 0)
                {
                    int OffSetX = (int)((int)(SGP.ManagedTextureManager.Instance.GetTextureWidth(image) >> 1) * this.Particle_List[i].Size_p);
                    int OffSetY = (int)((int)(SGP.ManagedTextureManager.Instance.GetTextureHeight(image) >> 1) * this.Particle_List[i].Size_p);

                    SGP.ManagedTextureManager.Instance.Draw(image, (int)this.Particle_List[i].PosX,
                        (int)this.Particle_List[i].PosY, this.Particle_List[i].Size_p, this.Particle_List[i].Size_p, Rectangle.Empty, OffSetX, OffSetY,
                        this.Particle_List[i].rotation, this.Particle_List[i].Color.ToArgb());
                }
            }
            SGP.ManagedDirect3D.Instance.Sprite.Flush();
            tempBlend1 = (int)SGP.ManagedDirect3D.Instance.Device.RenderState.SourceBlend;
            tempBlend2 = (int)SGP.ManagedDirect3D.Instance.Device.RenderState.DestinationBlend;
        }
    }
}
