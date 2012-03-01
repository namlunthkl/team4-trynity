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
        private String FilePath = Properties.Settings.Default.Path;

        public bool Looping = true;
        ManagedTextureManager TM = ManagedTextureManager.Instance;
        ManagedDirect3D D3D = ManagedDirect3D.Instance;
        Color BackGroundColor = Color.Black;
        System.DateTime PreviousTimeStamp = new System.DateTime();
        Emitter emitterObject = new Emitter();
        bool mouseMoveOK = false;
        bool gravityMoveOK = false;

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
            //FolderBrowserDialog fbd = new FolderBrowserDialog();

            //if (fbd.ShowDialog() == DialogResult.OK)
            //{
            //    Properties.Settings.Default.RelativePath = fbd.SelectedPath;
            //}
        }
        public void Render()
        {
            System.DateTime StartTimeStamp = System.DateTime.Now;
            System.TimeSpan CurrentTimeStamp = StartTimeStamp - PreviousTimeStamp;
            PreviousTimeStamp = StartTimeStamp;
            Update((float)(CurrentTimeStamp.TotalSeconds));

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
            ofd.Filter = "JPG Files|*.jpg|PNG Files|*.png|BMP Files|*.bmp";
            if (DialogResult.OK == ofd.ShowDialog())
            {
                emitterObject.imageFile = ofd.FileName;
            }
            emitterObject.image = TM.LoadTexture(emitterObject.imageFile, Color.Black.ToArgb());
        }

        private void numericUpDownEmitterAmount_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.MaxParticles = (int)numericUpDownEmitterAmount.Value;
            trackBarEmitterAmount.Value = (int)numericUpDownEmitterAmount.Value;
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
            trackBarEmitterLife.Value = (int)numericUpDownEmitterLife.Value;
        }

        private void trackBarEmitterAmount_Scroll(object sender, EventArgs e)
        {
            emitterObject.MaxParticles = (int)trackBarEmitterAmount.Value;
            numericUpDownEmitterAmount.Value = trackBarEmitterAmount.Value;
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
        private void trackBarEmitterLife_Scroll(object sender, EventArgs e)
        {
            emitterObject.MaxLife = (float)trackBarEmitterLife.Value;
            numericUpDownEmitterLife.Value = trackBarEmitterLife.Value;
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
            emitterObject.Source = comboBoxSourceBlend.SelectedIndex + 1;
            emitterObject.Dest = comboBoxDestinationBlend.SelectedIndex + 1;
        }
        private void comboBoxDestinationBlend_SelectedIndexChanged(object sender, EventArgs e)
        {
            emitterObject.Source = comboBoxSourceBlend.SelectedIndex + 1;
            emitterObject.Dest = comboBoxDestinationBlend.SelectedIndex + 1;
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
                numericUpDownMinVelocityX.Value = rand.Next(-500, 0);
                emitterObject.MinVelX = (float)numericUpDownMinVelocityX.Value;
            }
            if (checkBoxRandomMinVelY.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMinVelocityY.Value = rand.Next(-500, 0);
                emitterObject.MinVelY = (float)numericUpDownMinVelocityY.Value;
            }
            if (checkBoxRandomMaxVelX.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMaxVelocityX.Value = rand.Next(0, 500);
                emitterObject.MaxVelX = (float)numericUpDownMaxVelocityX.Value;
            }
            if (checkBoxRandomMaxVelY.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownMaxVelocityY.Value = rand.Next(0, 500);
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
                //Thread.Sleep(1);
                numericUpDownEmitterAmount.Value = rand.Next(0, 5000);
                emitterObject.MaxParticles = (int)numericUpDownEmitterAmount.Value;
            }
            if (checkBoxRandomLife.Checked == true)
            {
                //Thread.Sleep(1);
                numericUpDownEmitterLife.Value = rand.Next(1, 50);
                emitterObject.MaxLife = (int)numericUpDownEmitterLife.Value;
            }
            if (checkBoxRandomShapeHeight.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterShapeHeight.Value = rand.Next(1, 600);
                emitterObject.SpwnAreaHeight = (float)numericUpDownEmitterShapeHeight.Value;
            }
            if (checkBoxRandomShapeWidth.Checked == true)
            {
                Thread.Sleep(1);
                numericUpDownEmitterShapeWidth.Value = rand.Next(1, 800);
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

        private void saveXMLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSaveFile = new SaveFileDialog();
            dlgSaveFile.Filter = "All File|*.*|XML Files|*.xml";
            dlgSaveFile.FilterIndex = 2;
            dlgSaveFile.DefaultExt = "xml";
            dlgSaveFile.InitialDirectory = FilePath;

            if (DialogResult.OK == dlgSaveFile.ShowDialog())
            {

                String tempstring = String.Empty;
                String forwardString = String.Empty;
                String tempFilename = String.Empty;
                String destFile = FilePath;

                for (int i = emitterObject.imageFile.Length - 1; i >= 0; i--)
                {
                    if (emitterObject.imageFile[i].Equals('\\'))
                        break;
                    else
                        tempstring += emitterObject.imageFile[i];
                }
                destFile += "\\";

                for (int i = tempstring.Length - 1; i >= 0; i--)
                {
                    destFile += tempstring[i];
                    forwardString += tempstring[i];
                }


                // ROOT
                XElement xRoot = new XElement("Particle");
                
                // IMAGEFILE
                XElement xImageFile = new XElement("ImageFile", forwardString );
                xRoot.Add(xImageFile);
                
               // XElement xEmitter = new XElement("Emitter");
                //xRoot.Add(xEmitter);

                // CONTINUOUS
                XElement xContinuous = new XElement("Continuous", (emitterObject.continuous == true) ? 1 : 0);
                xRoot.Add(xContinuous);
                // RE-ANIMATE
                XElement xReAnimate = new XElement("Reanimate", (emitterObject.reAnimate == true) ? 1 : 0);
                xRoot.Add(xReAnimate);
                // EMITTER POS X
                XElement xEmitterPosX = new XElement("EmitterPosX", emitterObject.EmitterPosX);
                xRoot.Add(xEmitterPosX);
                // EMITTER POS Y
                XElement xEmitterPosY = new XElement("EmitterPosY", emitterObject.EmitterPosY);
                xRoot.Add(xEmitterPosY);
                // MAX PARTICLES
                XElement xMaxParticles = new XElement("MaxParticles", emitterObject.MaxParticles);
                xRoot.Add(xMaxParticles);
                // SIZE
                XElement xSize = new XElement("Size", emitterObject.FSize);
                xRoot.Add(xSize);
                // MAX LIFE
                XElement xMaxLife = new XElement("MaxLife", emitterObject.MaxLife);
                xRoot.Add(xMaxLife);
                // SPAWN WIDTH
                XElement xSpawnWidth = new XElement("SpawnWidth", emitterObject.SpwnAreaWidth);
                xRoot.Add(xSpawnWidth);
                // SPAWN HEIGHT
                XElement xSpawnHeight = new XElement("SpawnHeight", emitterObject.SpwnAreaHeight);
                xRoot.Add(xSpawnHeight);
                // SCALE START
                XElement xScaleStart = new XElement("ScaleStart", emitterObject.ScaleStart);
                xRoot.Add(xScaleStart);
                // SCALE END
                XElement xScaleEnd = new XElement("ScaleEnd", emitterObject.ScaleEnd);
                xRoot.Add(xScaleEnd);
                // ROTATION
                XElement xRotation = new XElement("Rotation", emitterObject.Rotation);
                xRoot.Add(xRotation);
                // MIN VEL X
                XElement xMinVelX = new XElement("MinVelX", emitterObject.MinVelX);
                xRoot.Add(xMinVelX);
                // MAX VEL X
                XElement xMaxVelX = new XElement("MaxVelX", emitterObject.MaxVelX);
                xRoot.Add(xMaxVelX);
                // MIN VEL Y
                XElement xMinVelY = new XElement("MinVelY", emitterObject.MinVelY);
                xRoot.Add(xMinVelY);
                // MAX VEL Y
                XElement xMaxVelY = new XElement("MaxVelY", emitterObject.MaxVelY);
                xRoot.Add(xMaxVelY);
                // COLOR START
                XElement xStartColorA = new XElement("StartColorA", emitterObject.ColorStart.A);
                xRoot.Add(xStartColorA);
                XElement xStartColorR = new XElement("StartColorR", emitterObject.ColorStart.R);
                xRoot.Add(xStartColorR);
                XElement xStartColorG = new XElement("StartColorG", emitterObject.ColorStart.G);
                xRoot.Add(xStartColorG);
                XElement xStartColorB = new XElement("StartColorB", emitterObject.ColorStart.B);
                xRoot.Add(xStartColorB);
                // COLOR END
                XElement xEndColorA = new XElement("EndColorA", emitterObject.ColorEnd.A);
                xRoot.Add(xEndColorA);
                XElement xEndColorR = new XElement("EndColorR", emitterObject.ColorEnd.R);
                xRoot.Add(xEndColorR);
                XElement xEndColorG = new XElement("EndColorG", emitterObject.ColorEnd.G);
                xRoot.Add(xEndColorG);
                XElement xEndColorB = new XElement("EndColorB", emitterObject.ColorEnd.B);
                xRoot.Add(xEndColorB);
                // SOURCE
                XElement xSource = new XElement("Source", emitterObject.Source);
                xRoot.Add(xSource);
                // DEST
                XElement xDest = new XElement("Dest", emitterObject.Dest);
                xRoot.Add(xDest);
                // GRAVITY POSITION X
                XElement xGravPosX = new XElement("GravPosX", emitterObject.GravityPosX);
                xRoot.Add(xGravPosX);
                // GRAVITY POSITION Y
                XElement xGravPosY = new XElement("GravPosY", emitterObject.GravityPosY);
                xRoot.Add(xGravPosY);
                // GRAVITY POWER
                XElement xGravPower = new XElement("GravPower", emitterObject.GravityPower);
                xRoot.Add(xGravPower);
                // GRAVITY DISTANCE X
                XElement xGravDistX = new XElement("GravDistX", emitterObject.GravityDistX);
                xRoot.Add(xGravDistX);
                // GRAVITY DISTANCE Y
                XElement xGravDistY = new XElement("GravDistY", emitterObject.GravityDistY);
                xRoot.Add(xGravDistY);

                // SAVE
                xRoot.Save(dlgSaveFile.FileName);
            }
        }
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgOpenFile.FilterIndex = 2;
            dlgOpenFile.InitialDirectory = FilePath;

            if (DialogResult.OK == dlgOpenFile.ShowDialog())
            {
                XElement xRoot = XElement.Load(dlgOpenFile.FileName);

                XElement xImageName = xRoot.Element("ImageFile");
                string tempF = FilePath;
                tempF += "\\";
                tempF += xImageName.Value;
                emitterObject.imageFile = tempF;
                emitterObject.image =TM.LoadTexture(tempF, 0);

                XElement xContinuous = xRoot.Element("Continuous");
                checkBoxEmitterBurst.Checked = (int.Parse(xContinuous.Value) == 1) ? true : false;

                XElement xReAnimate = xRoot.Element("Reanimate");
                emitterObject.reAnimate = (int.Parse(xReAnimate.Value) == 1) ? true : false;

                XElement xEmitterPosX = xRoot.Element("EmitterPosX");
                numericUpDownEmitterPositionX.Value = decimal.Parse(xEmitterPosX.Value);

                XElement xEmitterPosY = xRoot.Element("EmitterPosY");
                numericUpDownEmitterPositionY.Value = decimal.Parse(xEmitterPosY.Value);

                XElement xMaxParticles = xRoot.Element("MaxParticles");
                numericUpDownEmitterAmount.Value = int.Parse(xMaxParticles.Value);

                XElement xSize = xRoot.Element("Size");
                emitterObject.FSize = float.Parse(xSize.Value);
                //WTF IS MISSING HERE

                XElement xMaxLife = xRoot.Element("MaxLife");
                numericUpDownEmitterLife.Value= decimal.Parse(xMaxLife.Value);

                XElement xSpawnWidth = xRoot.Element("SpawnWidth"); 
                numericUpDownEmitterShapeWidth.Value = decimal.Parse(xSpawnWidth.Value);

                XElement xSpawnHeight = xRoot.Element("SpawnHeight");
                numericUpDownEmitterShapeHeight.Value = decimal.Parse(xSpawnHeight.Value);

                XElement xScaleStart = xRoot.Element("ScaleStart");
                numericUpDownStartingScale.Value = decimal.Parse(xScaleStart.Value);

                XElement xScaleEnd = xRoot.Element("ScaleEnd");
                numericUpDownEndingScale.Value = decimal.Parse(xScaleEnd.Value);

                XElement xRotation = xRoot.Element("Rotation");
                numericUpDownRotation.Value = decimal.Parse(xRotation.Value);

                XElement xMinVelX = xRoot.Element("MinVelX");
                numericUpDownMinVelocityX.Value = decimal.Parse(xMinVelX.Value);

                XElement xMaxVelX = xRoot.Element("MaxVelX");
                numericUpDownMaxVelocityX.Value = decimal.Parse(xMaxVelX.Value);

                XElement xMinVelY = xRoot.Element("MinVelY");
                numericUpDownMinVelocityY.Value = decimal.Parse(xMinVelY.Value);

                XElement xMaxVelY = xRoot.Element("MaxVelY");
                numericUpDownMaxVelocityY.Value = decimal.Parse(xMaxVelY.Value);

                XElement xStartColorA = xRoot.Element("StartColorA");
                byte tempSA = byte.Parse(xStartColorA.Value);
                XElement xStartColorR = xRoot.Element("StartColorR");
                byte tempSR = byte.Parse(xStartColorR.Value);
                XElement xStartColorG = xRoot.Element("StartColorG");
                byte tempSG = byte.Parse(xStartColorG.Value);
                XElement xStartColorB = xRoot.Element("StartColorB");
                byte tempSB = byte.Parse(xStartColorB.Value);
                numericUpDownStartingAlpha.Value = (decimal)tempSA;
                numericUpDownStartingRed.Value = (decimal)tempSR;
                numericUpDownStartingGreen.Value = (decimal)tempSG;
                numericUpDownStartingBlue.Value = (decimal)tempSB;

                XElement xEndColorA = xRoot.Element("EndColorA");
                byte tempEA = byte.Parse(xEndColorA.Value);
                XElement xEndColorR = xRoot.Element("EndColorR");
                byte tempER = byte.Parse(xEndColorR.Value);
                XElement xEndColorG = xRoot.Element("EndColorG");
                byte tempEG = byte.Parse(xEndColorG.Value);
                XElement xEndColorB = xRoot.Element("EndColorB");
                byte tempEB = byte.Parse(xEndColorB.Value);
                numericUpDownEndingAlpha.Value = (decimal)tempEA;
                numericUpDownEndingRed.Value = (decimal)tempER;
                numericUpDownEndingGreen.Value = (decimal)tempEG;
                numericUpDownEndingBlue.Value = (decimal)tempEB;

                XElement xSource = xRoot.Element("Source");
                comboBoxSourceBlend.SelectedIndex = int.Parse(xSource.Value) - 1;

                XElement xDest = xRoot.Element("Dest");
                comboBoxDestinationBlend.SelectedIndex = int.Parse(xDest.Value) -1;


                XElement xGravPosX = xRoot.Element("GravPosX");
                numericUpDownPointGravityPositionX.Value = decimal.Parse(xGravPosX.Value);

                XElement xGravPosY = xRoot.Element("GravPosY");
                numericUpDownPointGravityPositionY.Value = decimal.Parse(xGravPosY.Value);

                XElement xGravPower = xRoot.Element("GravPower");
                numericUpDownPointGravityPower.Value = decimal.Parse(xGravPower.Value);

                XElement xGravDistX = xRoot.Element("GravDistX");
                emitterObject.GravityDistX = float.Parse(xGravPosX.Value);

                XElement xGravDistY = xRoot.Element("GravDistY");
                emitterObject.GravityDistY = float.Parse(xGravPosY.Value);
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
            if (gravityMoveOK)
            {
                if (e.X >= 0 && e.X <= graphics_PanelViewer.Width)
                {
                    emitterObject.GravityPosX = e.X;
                    numericUpDownPointGravityPositionX.Value = (decimal)emitterObject.GravityPosX;
                }
                if (e.Y >= 0 && e.Y <= graphics_PanelViewer.Height)
                {
                    emitterObject.GravityPosY = e.Y;
                    numericUpDownPointGravityPositionY.Value = (decimal)emitterObject.GravityPosY;
                }
            }
        }
        private void graphics_PanelViewer_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                gravityMoveOK = true;
            }
            if (e.Button == MouseButtons.Left)
            {
                mouseMoveOK = true;
            }
        }
        private void graphics_PanelViewer_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                gravityMoveOK = false;
            }
            if (e.Button == MouseButtons.Left)
            {
                mouseMoveOK = false;
            }
        }
        private void graphics_PanelViewer_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                gravityMoveOK = true;
            }
            if (e.Button == MouseButtons.Left)
            {
                mouseMoveOK = true;
            }
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
            if (gravityMoveOK)
            {
                if (e.X >= 0 && e.X <= graphics_PanelViewer.Width)
                {
                    emitterObject.GravityPosX = e.X;
                    numericUpDownPointGravityPositionX.Value = (decimal)emitterObject.GravityPosX;
                }
                if (e.Y >= 0 && e.Y <= graphics_PanelViewer.Height)
                {
                    emitterObject.GravityPosY = e.Y;
                    numericUpDownPointGravityPositionY.Value = (decimal)emitterObject.GravityPosY;
                }
            }
        }

        private void numericUpDownRotation_ValueChanged_1(object sender, EventArgs e)
        {
            emitterObject.Rotation = (float)numericUpDownRotation.Value;
        }
        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                FilePath = dlg.SelectedPath;
                Properties.Settings.Default.Path = FilePath;
                Properties.Settings.Default.Save();
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void numericUpDownStartingScale_ValueChanged_1(object sender, EventArgs e)
        {
            emitterObject.ScaleStart = (float)numericUpDownStartingScale.Value;
        }
        private void numericUpDownEndingScale_ValueChanged_1(object sender, EventArgs e)
        {
            emitterObject.ScaleEnd = (float)numericUpDownEndingScale.Value;
        }

        private void numericUpDownPointGravityPositionX_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.GravityPosX = (float)numericUpDownPointGravityPositionX.Value;
        }
        private void numericUpDownPointGravityPositionY_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.GravityPosY = (float)numericUpDownPointGravityPositionY.Value;
        }
        private void numericUpDownPointGravityPower_ValueChanged(object sender, EventArgs e)
        {
            emitterObject.GravityPower = (float)numericUpDownPointGravityPower.Value;
        }


    }
}
