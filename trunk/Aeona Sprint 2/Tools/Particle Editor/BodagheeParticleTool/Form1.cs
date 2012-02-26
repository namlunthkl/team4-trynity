using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;
using ParticleTool;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Threading;
using System.Xml.Linq;

namespace BodagheeParticleTool
{
    public partial class Form1 : Form
    {
        //Relative file path
        string m_szPath = "";

        public bool Looping = true;
        ManagedTextureManager TM = ManagedTextureManager.Instance;
        ManagedDirect3D D3D = ManagedDirect3D.Instance;
        Color BackGroundColor = Color.Black;
        System.DateTime PreviousTimeStamp = new System.DateTime();
        Emitter emitterObject = new Emitter();
        bool mouseMoveOK = false;

        public void Update(float deltaTime)
        {
            emitterObject.ColorStart = pictureBoxStartingColor.BackColor;
            emitterObject.ColorEnd = pictureBoxEndingColor.BackColor;

            emitterObject.Update(deltaTime);
        }
        public Form1()
        {
            InitializeComponent();
            D3D.InitManagedDirect3D(graphics_PanelViewer);
            TM.InitManagedTextureManager(ManagedDirect3D.Instance.Device, ManagedDirect3D.Instance.Sprite);

        }
        public void Render()
        {
            System.DateTime StartTimeStamp = System.DateTime.Now;
            System.TimeSpan CurrentTimeStamp = StartTimeStamp - PreviousTimeStamp;
            PreviousTimeStamp = StartTimeStamp;
            Update((float)(CurrentTimeStamp.Milliseconds / 1000.0f));

            D3D.Clear(BackGroundColor);

            D3D.DeviceBegin();
            D3D.SpriteBegin();

            emitterObject.Render();

            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();
        }

        private void changeBackgroundColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog ChangeBackGroundColor = new ColorDialog();
            ChangeBackGroundColor.Color = BackGroundColor;
            if (DialogResult.OK == ChangeBackGroundColor.ShowDialog())
            {
                BackGroundColor = ChangeBackGroundColor.Color;
            }
        }
        private void buttonCustomStartingColor_Click(object sender, EventArgs e)
        {
            ColorDialog drawColor = new ColorDialog();
            Color var = new Color();
            if (DialogResult.OK == drawColor.ShowDialog())
            {
                pictureBoxStartingColor.BackColor = drawColor.Color;
                var = drawColor.Color;
            }
            numericUpDownStartingAlpha.Value = var.A;
            numericUpDownStartingRed.Value = var.R;
            numericUpDownStartingGreen.Value = var.G;
            numericUpDownStartingBlue.Value = var.B;

            trackBarStartingAlpha.Value = var.A;
            trackBarStartingRed.Value = var.R;
            trackBarStartingGreen.Value = var.G;
            trackBarStartingBlue.Value = var.B;
        }
        private void buttonCustomEndingColor_Click(object sender, EventArgs e)
        {
            ColorDialog drawColor = new ColorDialog();
            Color var = new Color();
            drawColor.Color = pictureBoxEndingColor.BackColor;
            if (DialogResult.OK == drawColor.ShowDialog())
            {
                pictureBoxEndingColor.BackColor = drawColor.Color;
                var = drawColor.Color;
            }
            numericUpDownEndingAlpha.Value = var.A;
            numericUpDownEndingRed.Value = var.R;
            numericUpDownEndingGreen.Value = var.G;
            numericUpDownEndingBlue.Value = var.B;

            trackBarEndingAlpha.Value = var.A;
            trackBarEndingRed.Value = var.R;
            trackBarEndingGreen.Value = var.G;
            trackBarEndingBlue.Value = var.B;
        }

        private void numericUpDownStartingAlpha_ValueChanged(object sender, EventArgs e)
        {
            trackBarStartingAlpha.Value = (int)numericUpDownStartingAlpha.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb((int)numericUpDownStartingAlpha.Value, (int)numericUpDownStartingRed.Value, (int)numericUpDownStartingGreen.Value, (int)numericUpDownStartingBlue.Value);
        }
        private void numericUpDownStartingRed_ValueChanged(object sender, EventArgs e)
        {
            trackBarStartingRed.Value = (int)numericUpDownStartingRed.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb((int)numericUpDownStartingAlpha.Value, (int)numericUpDownStartingRed.Value, (int)numericUpDownStartingGreen.Value, (int)numericUpDownStartingBlue.Value);
        }
        private void numericUpDownStartingGreen_ValueChanged(object sender, EventArgs e)
        {
            trackBarStartingGreen.Value = (int)numericUpDownStartingGreen.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb((int)numericUpDownStartingAlpha.Value, (int)numericUpDownStartingRed.Value, (int)numericUpDownStartingGreen.Value, (int)numericUpDownStartingBlue.Value);
        }
        private void numericUpDownStartingBlue_ValueChanged(object sender, EventArgs e)
        {
            trackBarStartingBlue.Value = (int)numericUpDownStartingBlue.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb((int)numericUpDownStartingAlpha.Value, (int)numericUpDownStartingRed.Value, (int)numericUpDownStartingGreen.Value, (int)numericUpDownStartingBlue.Value);

        }

        private void trackBarStartingAlpha_Scroll(object sender, EventArgs e)
        {
            numericUpDownStartingAlpha.Value = (int)trackBarStartingAlpha.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb(trackBarStartingAlpha.Value, trackBarStartingRed.Value, trackBarStartingGreen.Value, trackBarStartingBlue.Value);

        }
        private void trackBarStartingRed_Scroll(object sender, EventArgs e)
        {
            numericUpDownStartingRed.Value = (int)trackBarStartingRed.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb(trackBarStartingAlpha.Value, trackBarStartingRed.Value, trackBarStartingGreen.Value, trackBarStartingBlue.Value);

        }
        private void trackBarStartingGreen_Scroll(object sender, EventArgs e)
        {
            numericUpDownStartingGreen.Value = (int)trackBarStartingGreen.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb(trackBarStartingAlpha.Value, trackBarStartingRed.Value, trackBarStartingGreen.Value, trackBarStartingBlue.Value);

        }
        private void trackBarStartingBlue_Scroll(object sender, EventArgs e)
        {
            numericUpDownStartingBlue.Value = (int)trackBarStartingBlue.Value;
            pictureBoxStartingColor.BackColor = Color.FromArgb(trackBarStartingAlpha.Value, trackBarStartingRed.Value, trackBarStartingGreen.Value, trackBarStartingBlue.Value);

        }

        private void numericUpDownEndingAlpha_ValueChanged(object sender, EventArgs e)
        {
            trackBarEndingAlpha.Value = (int)numericUpDownEndingAlpha.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb((int)numericUpDownEndingAlpha.Value, (int)numericUpDownEndingRed.Value, (int)numericUpDownEndingGreen.Value, (int)numericUpDownEndingBlue.Value);

        }
        private void numericUpDownEndingRed_ValueChanged(object sender, EventArgs e)
        {
            trackBarEndingRed.Value = (int)numericUpDownEndingRed.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb((int)numericUpDownEndingAlpha.Value, (int)numericUpDownEndingRed.Value, (int)numericUpDownEndingGreen.Value, (int)numericUpDownEndingBlue.Value);

        }
        private void numericUpDownEndingGreen_ValueChanged(object sender, EventArgs e)
        {
            trackBarEndingGreen.Value = (int)numericUpDownEndingGreen.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb((int)numericUpDownEndingAlpha.Value, (int)numericUpDownEndingRed.Value, (int)numericUpDownEndingGreen.Value, (int)numericUpDownEndingBlue.Value);

        }
        private void numericUpDownEndingBlue_ValueChanged(object sender, EventArgs e)
        {
            trackBarEndingBlue.Value = (int)numericUpDownEndingBlue.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb((int)numericUpDownEndingAlpha.Value, (int)numericUpDownEndingRed.Value, (int)numericUpDownEndingGreen.Value, (int)numericUpDownEndingBlue.Value);

        }

        private void trackBarEndingAlpha_Scroll(object sender, EventArgs e)
        {
            numericUpDownEndingAlpha.Value = (int)trackBarEndingAlpha.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb(trackBarEndingAlpha.Value, trackBarEndingRed.Value, trackBarEndingGreen.Value, trackBarEndingBlue.Value);

        }
        private void trackBarEndingRed_Scroll(object sender, EventArgs e)
        {
            numericUpDownEndingRed.Value = (int)trackBarEndingRed.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb(trackBarEndingAlpha.Value, trackBarEndingRed.Value, trackBarEndingGreen.Value, trackBarEndingBlue.Value);

        }
        private void trackBarEndingGreen_Scroll(object sender, EventArgs e)
        {
            numericUpDownEndingGreen.Value = (int)trackBarEndingGreen.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb(trackBarEndingAlpha.Value, trackBarEndingRed.Value, trackBarEndingGreen.Value, trackBarEndingBlue.Value);

        }
        private void trackBarEndingBlue_Scroll(object sender, EventArgs e)
        {
            numericUpDownEndingBlue.Value = (int)trackBarEndingBlue.Value;
            pictureBoxEndingColor.BackColor = Color.FromArgb(trackBarEndingAlpha.Value, trackBarEndingRed.Value, trackBarEndingGreen.Value, trackBarEndingBlue.Value);

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Looping = false;
            if (TM != null)
            {
                TM.ShutdownManagedTextureManager();
                TM = null;
            }
            if (D3D != null)
            {
                D3D.Shutdown();
                D3D = null;
            }
        }
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Looping = false;
            if (TM != null)
            {
                TM.ShutdownManagedTextureManager();
                TM = null;
            }
            if (D3D != null)
            {
                D3D.Shutdown();
                D3D = null;
            }
            this.Close();
        }

        private void importImageStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            if (DialogResult.OK == ofd.ShowDialog())
            {
                emitterObject.imageFile = ofd.FileName;
            }
            emitterObject.image = TM.LoadTexture(emitterObject.imageFile, Color.Black.ToArgb());
        }

        private void numericUpDownEmitterAmount_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MaxParticles = (int)numericUpDownEmitterAmount.Value;
            int diff = Math.Abs(emitterObject.MaxParticles - emitterObject.Particle_List.Count);

            if (emitterObject.MaxParticles < emitterObject.Particle_List.Count)
            {
                for (int i = 0; i < diff; i++)
                {
                    emitterObject.Particle_List.RemoveAt(0);
                }
            }
            else
            {
                for (int i = 0; i < diff; i++)
                {
                    Particle tempParticle = new Particle();
                    emitterObject.Particle_List.Add(tempParticle);
                }
            }

        }
        private void numericUpDownEmitterLife_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MaxLife = (float)numericUpDownEmitterLife.Value;
        }

        private void numericUpDownMinVelocityX_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MinVelX = (float)numericUpDownMinVelocityX.Value;
        }
        private void numericUpDownMinVelocityY_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MinVelY = (float)numericUpDownMinVelocityY.Value;
        }
        private void numericUpDownMaxVelocityX_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MaxVelX = (float)numericUpDownMaxVelocityX.Value;
        }
        private void numericUpDownMaxVelocityY_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MaxVelY = (float)numericUpDownMaxVelocityY.Value;
        }
        private void numericUpDownStartingScale_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.ScaleStart = (float)numericUpDownStartingScale.Value;
        }
        private void numericUpDownEndingScale_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.ScaleEnd = (float)numericUpDownEndingScale.Value;
        }


        private void numericUpDownEmitterShapeWidth_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.SpwnAreaWidth = (float)numericUpDownEmitterShapeWidth.Value;
        }
        private void numericUpDownEmitterShapeHeight_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.SpwnAreaHeight = (float)numericUpDownEmitterShapeHeight.Value;
        }

        private void numericUpDownEmitterPositionX_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.EmitterPosX = (float)numericUpDownEmitterPositionX.Value;
        }
        private void numericUpDownEmitterPositionY_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.EmitterPosY = (float)numericUpDownEmitterPositionY.Value;
        }

        private void checkBoxEmitterBurst_CheckedChanged(object sender, EventArgs e)
        {
            emitterObject.continuous = checkBoxEmitterBurst.Checked;
        }
        private void buttonREANIMATEPARTICLES_Click(object sender, EventArgs e)
        {
            emitterObject.reAnimate = true;
        }

        private void comboBoxSourceBlend_SelectedIndexChanged(object sender, EventArgs e)
        {
            emitterObject.Source = comboBoxSourceBlend.SelectedIndex;
            emitterObject.Dest = comboBoxDestinationBlend.SelectedIndex;
        }
        private void comboBoxDestinationBlend_SelectedIndexChanged(object sender, EventArgs e)
        {
            emitterObject.Source = comboBoxSourceBlend.SelectedIndex;
            emitterObject.Dest = comboBoxDestinationBlend.SelectedIndex;
        }

        private void numericUpDownRotation_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.Rotation = (float)numericUpDownRotation.Value;
        }

        private void buttonRandomizeAll_Click(object sender, EventArgs e)
        {
            checkBoxRandomStartColor.Checked = true;
            checkBoxRandomEndColor.Checked = true;
            checkBoxRandomMinVelX.Checked = true;
            checkBoxRandomMinVelY.Checked = true;
            checkBoxRandomMaxVelX.Checked = true;
            checkBoxRandomMaxVelY.Checked = true;
            checkBoxRandomScaleStart.Checked = true;
            checkBoxRandomScaleEnd.Checked = true;
            checkBoxRandomAmount.Checked = true;
            checkBoxRandomLife.Checked = true;
            checkBoxRandomShapeHeight.Checked = true;
            checkBoxRandomShapeWidth.Checked = true;
            checkBoxRandomSource.Checked = true;
            checkBoxRandomDestination.Checked = true;
            checkBoxRandomRotation.Checked = true;
        }
        private void buttonRandomizeSelected_Click(object sender, EventArgs e)
        {
            Random rand = new Random((int)DateTime.Now.Ticks & 0x0000FFFF);
            if (checkBoxRandomStartColor.Checked == true)
            {
                Thread.Sleep(1);
                byte a1 = (byte)rand.Next(0, 255);
                byte r1 = (byte)rand.Next(0, 255);
                byte g1 = (byte)rand.Next(0, 255);
                byte b1 = (byte)rand.Next(0, 255);

                Color color1 = Color.FromArgb(a1, r1, g1, b1);
                pictureBoxStartingColor.BackColor = color1;

                numericUpDownStartingAlpha.Value = a1;
                numericUpDownStartingRed.Value = r1;
                numericUpDownStartingGreen.Value = g1;
                numericUpDownStartingBlue.Value = b1;

                trackBarStartingAlpha.Value = a1;
                trackBarStartingRed.Value = r1;
                trackBarStartingGreen.Value = g1;
                trackBarStartingBlue.Value = b1;
            }
            if (checkBoxRandomEndColor.Checked == true)
            {
                Thread.Sleep(1);
                byte a2 = (byte)rand.Next(0, 255);
                byte r2 = (byte)rand.Next(0, 255);
                byte g2 = (byte)rand.Next(0, 255);
                byte b2 = (byte)rand.Next(0, 255);

                Color color2 = Color.FromArgb(a2, r2, g2, b2);
                pictureBoxEndingColor.BackColor = color2;

                numericUpDownEndingAlpha.Value = a2;
                numericUpDownEndingRed.Value = r2;
                numericUpDownEndingGreen.Value = g2;
                numericUpDownEndingBlue.Value = b2;

                trackBarEndingAlpha.Value = a2;
                trackBarEndingRed.Value = r2;
                trackBarEndingGreen.Value = g2;
                trackBarEndingBlue.Value = b2;
            }
            if (checkBoxRandomMinVelX.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMinVelocityX.Value = rand.Next(-200, 0);
                emitterObject.MinVelX = (float)numericUpDownMinVelocityX.Value;
            }
            if (checkBoxRandomMinVelY.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMinVelocityY.Value = rand.Next(-200, 0);
                emitterObject.MinVelY = (float)numericUpDownMinVelocityY.Value;
            }
            if (checkBoxRandomMaxVelX.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMaxVelocityX.Value = rand.Next(0, 200);
                emitterObject.MaxVelX = (float)numericUpDownMaxVelocityX.Value;
            }
            if (checkBoxRandomMaxVelY.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMaxVelocityY.Value = rand.Next(0, 200);
                emitterObject.MaxVelY = (float)numericUpDownMaxVelocityY.Value;
            }
            if (checkBoxRandomScaleStart.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownStartingScale.Value = rand.Next(0, 5);
                emitterObject.ScaleStart = (float)numericUpDownStartingScale.Value;
            }
            if (checkBoxRandomScaleEnd.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEndingScale.Value = rand.Next(0, 5);
                emitterObject.ScaleEnd = (float)numericUpDownEndingScale.Value;
            }
            if (checkBoxRandomAmount.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterAmount.Value = rand.Next(0, 2000);
                emitterObject.MaxParticles = (int)numericUpDownEmitterAmount.Value;
            }
            if (checkBoxRandomLife.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterLife.Value = rand.Next(1, 20);
                emitterObject.MaxLife = (int)numericUpDownEmitterLife.Value;
            }
            if (checkBoxRandomShapeHeight.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterShapeHeight.Value = rand.Next(1, 100);
                emitterObject.SpwnAreaHeight = (float)numericUpDownEmitterShapeHeight.Value;
            }
            if (checkBoxRandomShapeWidth.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterShapeWidth.Value = rand.Next(1, 100);
                emitterObject.SpwnAreaWidth = (float)numericUpDownEmitterShapeWidth.Value;
            }
            if (checkBoxRandomSource.Checked == true)
            {
                Thread.Sleep(1);
                emitterObject.Source = rand.Next(0, 14);
                comboBoxSourceBlend.SelectedIndex = emitterObject.Source;
            }
            if (checkBoxRandomDestination.Checked == true)
            {
                Thread.Sleep(1);
                emitterObject.Dest = rand.Next(0, 14);
                comboBoxDestinationBlend.SelectedIndex = emitterObject.Dest;
            }
            if (checkBoxRandomRotation.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownRotation.Value = rand.Next(-10, 10);
                emitterObject.Rotation = (float)numericUpDownRotation.Value;
            }
        }

        private void graphics_PanelViewer_MouseMove(object sender, MouseEventArgs e)
        {
            if (mouseMoveOK)
            {
                if (emitterObject.image != -1)
                {
                    if (e.X >= 0 && e.X <= graphics_PanelViewer.Width)
                    {
                        emitterObject.EmitterPosX = e.X - (TM.GetTextureWidth(emitterObject.image) >> 1);
                        numericUpDownEmitterPositionX.Value = (decimal)emitterObject.EmitterPosX;
                    }
                    if (e.Y >= 0 && e.Y <= graphics_PanelViewer.Height)
                    {
                        emitterObject.EmitterPosY = e.Y - (TM.GetTextureHeight(emitterObject.image) >> 1);
                        numericUpDownEmitterPositionY.Value = (decimal)emitterObject.EmitterPosY;
                    }
                }    
            }
        }

        private void saveXMLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSaveFile = new SaveFileDialog();
            dlgSaveFile.Filter = "All File|*.*|XML Files|*.xml";
            dlgSaveFile.FilterIndex = 2;
            dlgSaveFile.DefaultExt = "xml";
            dlgSaveFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgSaveFile.ShowDialog())
            {
                // ROOT
                XElement xRoot = new XElement("Particle");
                
                // IMAGEFILE
                XAttribute xImageFile = new XAttribute("ImageFile", emitterObject.imageFile );
                xRoot.Add(xImageFile);
                
                XElement xEmitter = new XElement("Emitter");
                xRoot.Add(xEmitter);

                // CONTINUOUS
                XAttribute xContinuous = new XAttribute("Continuous", (emitterObject.continuous == true) ? 1: 0);
                xEmitter.Add(xContinuous);
                // RE-ANIMATE
                XAttribute xReAnimate = new XAttribute("Reanimate", (emitterObject.reAnimate == true) ? 1: 0);
                xEmitter.Add(xReAnimate);
                // EMITTER POS X
                XAttribute xEmitterPosX = new XAttribute("EmitterPosX", emitterObject.EmitterPosX);
                xEmitter.Add(xEmitterPosX);
                // EMITTER POS Y
                XAttribute xEmitterPosY = new XAttribute("EmitterPosY", emitterObject.EmitterPosY);
                xEmitter.Add(xEmitterPosY);
                // MAX PARTICLES
                XAttribute xMaxParticles = new XAttribute("MaxParticles", emitterObject.MaxParticles);
                xEmitter.Add(xMaxParticles);
                // SIZE
                XAttribute xSize = new XAttribute("Size", emitterObject.FSize);
                xEmitter.Add(xSize);
                // MAX LIFE
                XAttribute xMaxLife = new XAttribute("MaxLife", emitterObject.MaxLife);
                xEmitter.Add(xMaxLife);
                // SPAWN WIDTH
                XAttribute xSpawnWidth = new XAttribute("SpawnWidth", emitterObject.SpwnAreaWidth);
                xEmitter.Add(xSpawnWidth);
                // SPAWN HEIGHT
                XAttribute xSpawnHeight = new XAttribute("SpawnHeight", emitterObject.SpwnAreaHeight);
                xEmitter.Add(xSpawnHeight);
                // SCALE START
                XAttribute xScaleStart = new XAttribute("ScaleStart", emitterObject.ScaleStart);
                xEmitter.Add(xScaleStart);
                // SCALE END
                XAttribute xScaleEnd = new XAttribute("ScaleEnd", emitterObject.ScaleEnd);
                xEmitter.Add(xScaleEnd);
                // ROTATION
                XAttribute xRotation = new XAttribute("Rotation", emitterObject.Rotation);
                xEmitter.Add(xRotation);
                // MIN VEL X
                XAttribute xMinVelX = new XAttribute("MinVelX", emitterObject.MinVelX);
                xEmitter.Add(xMinVelX);
                // MAX VEL X
                XAttribute xMaxVelX = new XAttribute("MaxVelX", emitterObject.MaxVelX);
                xEmitter.Add(xMaxVelX);
                // MIN VEL Y
                XAttribute xMinVelY = new XAttribute("MinVelY", emitterObject.MinVelY);
                xEmitter.Add(xMinVelY);
                // MAX VEL Y
                XAttribute xMaxVelY = new XAttribute("MaxVelY", emitterObject.MaxVelY);
                xEmitter.Add(xMaxVelY);
                // COLOR START
                XAttribute xStartColorA = new XAttribute("StartColorA", emitterObject.ColorStart.A);
                xEmitter.Add(xStartColorA);
                XAttribute xStartColorR = new XAttribute("StartColorR", emitterObject.ColorStart.R);
                xEmitter.Add(xStartColorR);
                XAttribute xStartColorG = new XAttribute("StartColorG", emitterObject.ColorStart.G);
                xEmitter.Add(xStartColorG);
                XAttribute xStartColorB = new XAttribute("StartColorB", emitterObject.ColorStart.B);
                xEmitter.Add(xStartColorB);
                // COLOR END
                XAttribute xEndColorA = new XAttribute("EndColorA", emitterObject.ColorEnd.A);
                xEmitter.Add(xEndColorA);
                XAttribute xEndColorR = new XAttribute("EndColorR", emitterObject.ColorEnd.R);
                xEmitter.Add(xEndColorR);
                XAttribute xEndColorG = new XAttribute("EndColorG", emitterObject.ColorEnd.G);
                xEmitter.Add(xEndColorG);
                XAttribute xEndColorB = new XAttribute("EndColorB", emitterObject.ColorEnd.B);
                xEmitter.Add(xEndColorB);
                // SOURCE
                XAttribute xSource = new XAttribute("Source", emitterObject.Source);
                xEmitter.Add(xSource);
                // DEST
                XAttribute xDest = new XAttribute("Dest", emitterObject.Dest);
                xEmitter.Add(xDest);

                xRoot.Save(dlgSaveFile.FileName);
            }
        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgOpenFile.FilterIndex = 2;
            dlgOpenFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgOpenFile.ShowDialog())
            {
                XElement xRoot = XElement.Load(dlgOpenFile.FileName);

                XAttribute xImageName = xRoot.Attribute("ImageFile");
                emitterObject.imageFile = xImageName.Value;

                emitterObject.image =TM.LoadTexture(xImageName.Value, 0);
                XElement xEmitter = xRoot.Element("Emitter");

                XAttribute xContinuous = xEmitter.Attribute("Continuous");
                checkBoxEmitterBurst.Checked = (int.Parse(xContinuous.Value) == 1) ? true : false;

                XAttribute xReAnimate = xEmitter.Attribute("Reanimate");
                emitterObject.reAnimate = (int.Parse(xReAnimate.Value) == 1) ? true : false;

                XAttribute xEmitterPosX = xEmitter.Attribute( "EmitterPosX" );
                numericUpDownEmitterPositionX.Value = decimal.Parse(xEmitterPosX.Value);

                XAttribute xEmitterPosY = xEmitter.Attribute("EmitterPosY");
                numericUpDownEmitterPositionY.Value = decimal.Parse(xEmitterPosY.Value);

                XAttribute xMaxParticles = xEmitter.Attribute("MaxParticles");
                numericUpDownEmitterAmount.Value = int.Parse(xMaxParticles.Value);

                XAttribute xSize = xEmitter.Attribute("Size");
                emitterObject.FSize = float.Parse(xSize.Value);
                //WTF IS MISSING HERE

                XAttribute xMaxLife = xEmitter.Attribute("MaxLife");
                numericUpDownEmitterLife.Value= decimal.Parse(xMaxLife.Value);

                XAttribute xSpawnWidth = xEmitter.Attribute("SpawnWidth"); 
                numericUpDownEmitterShapeWidth.Value = decimal.Parse(xSpawnWidth.Value);

                XAttribute xSpawnHeight = xEmitter.Attribute("SpawnHeight");
                numericUpDownEmitterShapeHeight.Value = decimal.Parse(xSpawnHeight.Value);

                XAttribute xScaleStart = xEmitter.Attribute("ScaleStart");
                numericUpDownStartingScale.Value = decimal.Parse(xScaleStart.Value);

                XAttribute xScaleEnd = xEmitter.Attribute("ScaleEnd");
                numericUpDownEndingScale.Value = decimal.Parse(xScaleEnd.Value);

                XAttribute xRotation = xEmitter.Attribute("Rotation");
                numericUpDownRotation.Value = decimal.Parse(xRotation.Value);

                XAttribute xMinVelX = xEmitter.Attribute("MinVelX");
                numericUpDownMinVelocityX.Value = decimal.Parse(xMinVelX.Value);

                XAttribute xMaxVelX = xEmitter.Attribute("MaxVelX");
                numericUpDownMaxVelocityX.Value = decimal.Parse(xMaxVelX.Value);

                XAttribute xMinVelY = xEmitter.Attribute("MinVelY");
                numericUpDownMinVelocityY.Value = decimal.Parse(xMinVelY.Value);

                XAttribute xMaxVelY = xEmitter.Attribute("MaxVelY");
                numericUpDownMaxVelocityY.Value = decimal.Parse(xMaxVelY.Value);

                XAttribute xStartColorA = xEmitter.Attribute("StartColorA");
                byte tempSA = byte.Parse(xStartColorA.Value);
                XAttribute xStartColorR = xEmitter.Attribute("StartColorR");
                byte tempSR = byte.Parse(xStartColorR.Value);
                XAttribute xStartColorG = xEmitter.Attribute("StartColorG");
                byte tempSG = byte.Parse(xStartColorG.Value);
                XAttribute xStartColorB = xEmitter.Attribute("StartColorB");
                byte tempSB = byte.Parse(xStartColorB.Value);
                numericUpDownStartingAlpha.Value = (decimal)tempSA;
                numericUpDownStartingRed.Value = (decimal)tempSR;
                numericUpDownStartingGreen.Value = (decimal)tempSG;
                numericUpDownStartingBlue.Value = (decimal)tempSB;
                
                XAttribute xEndColorA = xEmitter.Attribute("EndColorA");
                byte tempEA = byte.Parse(xEndColorA.Value);
                XAttribute xEndColorR = xEmitter.Attribute("EndColorR");
                byte tempER = byte.Parse(xEndColorR.Value);
                XAttribute xEndColorG = xEmitter.Attribute("EndColorG");
                byte tempEG = byte.Parse(xEndColorG.Value);
                XAttribute xEndColorB = xEmitter.Attribute("EndColorB");
                byte tempEB = byte.Parse(xEndColorB.Value);
                numericUpDownEndingAlpha.Value = (decimal)tempEA;
                numericUpDownEndingRed.Value = (decimal)tempER;
                numericUpDownEndingGreen.Value = (decimal)tempEG;
                numericUpDownEndingBlue.Value = (decimal)tempEB;

                XAttribute xSource = xEmitter.Attribute("Source");
                comboBoxSourceBlend.SelectedIndex = int.Parse(xSource.Value);

                XAttribute xDest = xEmitter.Attribute("Dest");
                comboBoxDestinationBlend.SelectedIndex = int.Parse(xDest.Value);
            }
        }
        private void graphics_PanelViewer_MouseDown(object sender, MouseEventArgs e)
        {
            mouseMoveOK = true;
        }
        private void graphics_PanelViewer_MouseUp(object sender, MouseEventArgs e)
        {
            mouseMoveOK = false;
        }
    }
}
