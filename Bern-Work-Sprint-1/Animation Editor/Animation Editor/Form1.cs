using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;

namespace Animation_Editor
{
    public partial class Form1 : Form
    {
        SpriteSheet[,] AnimationSheet = new SpriteSheet[1,1];
        int CurrentAction = 1;
        int imageid = -1;
        public bool Looping = true;
        bool m_bIsPlaying = false;
        int m_nFrameNumber = 0;
        float m_fTimer = 0.0f;
        ManagedTextureManager TM = ManagedTextureManager.Instance;
        ManagedDirect3D D3D = ManagedDirect3D.Instance;
        private Point start = Point.Empty;
        private Point end = Point.Empty;
        public Form1()
        {
            InitializeComponent();
            Graphics g = MainPanel.CreateGraphics();
            D3D.InitManagedDirect3D(graphicsPanelPlayer);
            D3D.InitManagedDirect3D(MainPanel);
            TM.InitManagedTextureManager(ManagedDirect3D.Instance.Device,ManagedDirect3D.Instance.Sprite);
            Size tempSize = new Size(800, 600);
            MainPanel.AutoScrollMinSize = tempSize;

            Frame f = new Frame();
            String tempS = "Frame " + (listBoxFrames.Items.Count + 1);
            f.Name = tempS;
            Point tempP = new Point((int)numericUpDownCurrentPointX.Value, (int)numericUpDownCurrentPointY.Value);
            f.Anchor = tempP;
            Rectangle tempF = new Rectangle((int)numericUpDownXPosition.Value, (int)numericUpDownYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.FrameRect = tempF;
            Rectangle tempC = new Rectangle((int)numericUpDownCollisionXPosition.Value, (int)numericUpDownCollisionYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);

            listBoxFrames.Items.Add(f);

            DrawFrameRect.BackColor = Color.DodgerBlue;
            DrawFrameRect.ForeColor = Color.White;
            listBoxFrames.SelectedIndex = listBoxFrames.Items.Count - 1;
        }

        private void ToolStripExit_Click(object sender, EventArgs e)
        {
            Looping = false;
            if(TM != null)
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

        private void toolStripImportAnimationImage_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            if(DialogResult.OK == dlg.ShowDialog())
            {
                imageid = TM.LoadTexture(dlg.FileName,0);
                SpriteSheet temp = new SpriteSheet(dlg.FileName);
                AnimationSheet[0,0] = temp;

                Graphics g = MainPanel.CreateGraphics();
                Size tempSize = new Size(temp.sheet.Width, temp.sheet.Height);
                MainPanel.AutoScrollMinSize = tempSize;
            }
        }
        
        public void Render()
        {
            D3D.ChangeDisplayParam(MainPanel);
            {
                Point offset = Point.Empty;
                offset.X += MainPanel.AutoScrollPosition.X;
                offset.Y += MainPanel.AutoScrollPosition.Y;
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);
                if (imageid >= 0)
                    TM.Draw(imageid, offset.X, offset.Y, 1.0f, 1.0f, Rectangle.Empty, 0, 0, 0.0f, Color.White.ToArgb());
                D3D.Sprite.Flush();

                if (end != Point.Empty)
                {
                    Rectangle temp = new Rectangle();
                    temp.X = start.X + offset.X;
                    temp.Y = start.Y + offset.Y;
                    temp.Width = end.X - start.X;
                    temp.Height = end.Y - start.Y;
                    D3D.DrawEmptyRect(temp, Color.Black);
                }

                for (int i = 0; i < listBoxFrames.Items.Count; i++)
                {

                    Frame tempFrame = (Frame)listBoxFrames.Items[i];
                    Rectangle drawRect = new Rectangle(tempFrame.FrameRect.X + offset.X,
                        tempFrame.FrameRect.Y + offset.Y, tempFrame.FrameRect.Width, tempFrame.FrameRect.Height);

                    D3D.DrawEmptyRect(drawRect, Color.DodgerBlue);

                    Rectangle CollisionRect = new Rectangle(tempFrame.Collision.X + offset.X,
                        tempFrame.Collision.Y + offset.Y, tempFrame.Collision.Width, tempFrame.Collision.Height);

                    D3D.DrawEmptyRect(CollisionRect, Color.Purple);

                    if (tempFrame.Anchor != Point.Empty)
                    {
                        Point tempPoint = new Point(tempFrame.Anchor.X, tempFrame.Anchor.Y);

                        D3D.DrawLine(tempFrame.Anchor.X - 5, tempFrame.Anchor.Y, tempFrame.Anchor.X + 5, tempFrame.Anchor.Y, Color.Red);
                        D3D.DrawLine(tempFrame.Anchor.X, tempFrame.Anchor.Y - 5, tempFrame.Anchor.X, tempFrame.Anchor.Y + 5, Color.Red);
                    }

                }

                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
            }
            D3D.ChangeDisplayParam(graphicsPanelPlayer);
            {

            }
        }

        private void DrawFrameRect_Click(object sender, EventArgs e)
        {
            DrawFrameRect.BackColor = Color.DodgerBlue;
            DrawFrameRect.ForeColor = Color.White;
            DrawCollisionRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawCollisionRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawAnchorPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawAnchorPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            CurrentAction = 1;
        }

        private void DrawCollisionRect_Click(object sender, EventArgs e)
        {
            DrawFrameRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawFrameRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawCollisionRect.BackColor = Color.Purple;
            DrawCollisionRect.ForeColor = Color.White;
            DrawAnchorPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawAnchorPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            CurrentAction = 2;
        }

        private void DrawAnchorPoint_Click(object sender, EventArgs e)
        {
            DrawFrameRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawFrameRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawCollisionRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawCollisionRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawAnchorPoint.BackColor = Color.Red;
            DrawAnchorPoint.ForeColor = Color.White;
            CurrentAction = 3;
        }

        private void ToolStripNew_Click(object sender, EventArgs e)
        {
            //  Animation Name
            textBoxAnimationName.Text = string.Empty;
            //  Clear Frames
            listBoxFrames.Items.Clear();
            //  Current Point
            numericUpDownCurrentPointX.Value = 0.00M;
            numericUpDownCurrentPointY.Value = 0.00M;
            // Current Rect
            numericUpDownXPosition.Value = 0;
            numericUpDownYPosition.Value = 0;
            numericUpDownHeight.Value = 0;
            numericUpDownWidth.Value = 0;
            //  Frame Duration
            numericUpDownFrameDuration.Value = 0.25M;
            //  Animation Speed
            numericUpDownAnimationSpeed.Value = 1.00M;
            //  Trigger Event
            TextBoxFrameTriggerEvent.Text = string.Empty;
            //  Unselect Buttons
            int CurrentAction = 1;
            DrawFrameRect.BackColor = Color.DodgerBlue;
            DrawFrameRect.ForeColor = Color.White;
            DrawCollisionRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawCollisionRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawAnchorPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawAnchorPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);

            Frame f = new Frame();
            String tempS = "Frame " + (listBoxFrames.Items.Count + 1);
            f.Name = tempS;
            Point tempP = new Point((int)numericUpDownCurrentPointX.Value, (int)numericUpDownCurrentPointY.Value);
            f.Anchor = tempP;
            Rectangle tempF = new Rectangle((int)numericUpDownXPosition.Value, (int)numericUpDownYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.FrameRect = tempF;
            Rectangle tempC = new Rectangle((int)numericUpDownCollisionXPosition.Value, (int)numericUpDownCollisionYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);

            listBoxFrames.Items.Add(f);

           
            listBoxFrames.SelectedIndex = listBoxFrames.Items.Count - 1;
        }

        private void MainPanel_MouseDown(object sender, MouseEventArgs e)
        {
            Point offset = e.Location;
            offset.X -= MainPanel.AutoScrollPosition.X;
            offset.Y -= MainPanel.AutoScrollPosition.Y;
            if ((e.Button & MouseButtons.Left) != 0)
            {
                start.X = offset.X;
                start.Y = offset.Y;
            }
   
        }

        private void MainPanel_MouseMove(object sender, MouseEventArgs e)
        {
            Point offset = e.Location;
            offset.X -= MainPanel.AutoScrollPosition.X;
            offset.Y -= MainPanel.AutoScrollPosition.Y;
            if (((e.Button & MouseButtons.Left) != 0) && (start != Point.Empty))
            {
                end.X = offset.X;
                end.Y = offset.Y;
            }
        }

        private void MainPanel_MouseUp(object sender, MouseEventArgs e)
        {

            Rectangle temp = new Rectangle();
            if ((end.X - start.X) < 0 && (end.Y - start.Y) < 0)
            {
                temp.X = end.X;
                temp.Y = end.Y;
                temp.Width = start.X - end.X;
                temp.Height = start.Y - end.Y;
            }
            else if ((end.X - start.X) < 0)
            {
                temp.X = end.X;
                temp.Y = start.Y;
                temp.Width = start.X - end.X;
                temp.Height = end.Y - start.Y;
            }
            else if((end.Y - start.Y) < 0)
            {
                temp.X = start.X;
                temp.Y = end.Y;
                temp.Width = end.X - start.X;
                temp.Height = start.Y - end.Y;
            }
            else
            {
                temp.X = start.X;
                temp.Y = start.Y;
                temp.Width = end.X - start.X;
                temp.Height = end.Y - start.Y;
            }
            

            if (listBoxFrames.Items.Count != 0 && listBoxFrames.SelectedIndex >= 0)
            {
                switch (CurrentAction)
                {
                    case 1:
                        {
                            //  Draw Frame Rect
                            Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                            tempFrame.FrameRect = temp;
                            listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
                            break;
                        }
                    case 2:
                        {
                            //  Draw Collision Rect
                            Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                            tempFrame.Collision = temp;
                            listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
                            break;
                        }
                    case 3:
                        {
                            //  Draw Anchor Point
                            Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                            tempFrame.Anchor = start;
                            listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
                            break;
                        }
                }
                
            }
            
            start = Point.Empty;
            end = Point.Empty;
        }

        private void FrameListAdd_Click(object sender, EventArgs e)
        {
            //  Current Point
            numericUpDownCurrentPointX.Value = 0;
            numericUpDownCurrentPointY.Value = 0;
            // Current Rect
            numericUpDownXPosition.Value = 0;
            numericUpDownYPosition.Value = 0;
            numericUpDownHeight.Value = 0;
            numericUpDownWidth.Value = 0;
            //  collision rect
            numericUpDownCollisionXPosition.Value = 0;
            numericUpDownCollisionYPosition.Value = 0;
            numericUpDownCollisionHeight.Value = 0;
            numericUpDownCollisionWidth.Value = 0;
            //  Anchor Point
            numericUpDownCurrentPointX.Value = 0.0M;
            numericUpDownCurrentPointY.Value = 0.0M;
            //  Frame Duration
            numericUpDownFrameDuration.Value = .25M;
            //  Trigger Event
            TextBoxFrameTriggerEvent.Text = string.Empty;

            Frame f = new Frame();
            String tempS = "Frame " + (listBoxFrames.Items.Count+1);
            f.Name = tempS;
            Point tempP = new Point((int)numericUpDownCurrentPointX.Value,(int)numericUpDownCurrentPointY.Value);
            f.Anchor = tempP;
            Rectangle tempF = new Rectangle((int)numericUpDownXPosition.Value,(int)numericUpDownYPosition.Value,(int)numericUpDownWidth.Value,(int)numericUpDownHeight.Value);
            f.FrameRect = tempF;
            Rectangle tempC = new Rectangle((int)numericUpDownCollisionXPosition.Value,(int)numericUpDownCollisionYPosition.Value,(int)numericUpDownWidth.Value,(int)numericUpDownHeight.Value);
            
            listBoxFrames.Items.Add(f);

            
            listBoxFrames.SelectedIndex = listBoxFrames.Items.Count-1;
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

        private void listBoxFrames_SelectedIndexChanged(object sender, EventArgs e)
        {
            Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
            //  Current Point
            numericUpDownCurrentPointX.Value = tempFrame.Anchor.X;
            numericUpDownCurrentPointY.Value = tempFrame.Anchor.Y;
            // Current Rect
            numericUpDownXPosition.Value = tempFrame.FrameRect.Left;
            numericUpDownYPosition.Value = tempFrame.FrameRect.Top;
            numericUpDownHeight.Value = tempFrame.FrameRect.Height;
            numericUpDownWidth.Value = tempFrame.FrameRect.Width;
            //  collision rect
            numericUpDownCollisionXPosition.Value = tempFrame.Collision.Left;
            numericUpDownCollisionYPosition.Value = tempFrame.Collision.Top;
            numericUpDownCollisionHeight.Value = tempFrame.Collision.Height;
            numericUpDownCollisionWidth.Value = tempFrame.Collision.Width;
            //  Anchor Point
            numericUpDownCurrentPointX.Value = tempFrame.Anchor.X;
            numericUpDownCurrentPointY.Value = tempFrame.Anchor.Y;
            //  Frame Duration
            numericUpDownFrameDuration.Value = tempFrame.FrameDuration;
            //  Trigger Event
            TextBoxFrameTriggerEvent.Text = tempFrame.TriggerEvent;
        }

        private void numericUpDownCurrentPointX_ValueChanged(object sender, EventArgs e)
        {
            
            if(listBoxFrames.Items.Count != 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;
                    
                temp.X = (int)numericUpDownCurrentPointX.Value;
                tempFrame.Anchor = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCurrentPointY_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;

                temp.Y = (int)numericUpDownCurrentPointY.Value;
                tempFrame.Anchor = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownXPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.X = (int)numericUpDownXPosition.Value;
                tempFrame.FrameRect = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownYPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Y = (int)numericUpDownYPosition.Value;
                tempFrame.FrameRect = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownHeight_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Height = (int)numericUpDownHeight.Value;
                tempFrame.FrameRect = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownWidth_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Width = (int)numericUpDownWidth.Value;
                tempFrame.FrameRect = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionXPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.X = (int)numericUpDownCollisionXPosition.Value;
                tempFrame.Collision = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionYPosition_ValueChanged(object sender, EventArgs e)
        {
             if(listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Y = (int)numericUpDownCollisionYPosition.Value;
                tempFrame.Collision = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionHeight_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Height = (int)numericUpDownCollisionHeight.Value;
                tempFrame.Collision = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionWidth_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxFrames.Items.Count != 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)listBoxFrames.Items[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Width = (int)numericUpDownCollisionWidth.Value;
                tempFrame.Collision = temp;
                listBoxFrames.Items[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void buttonPlayerPlay_Click(object sender, EventArgs e)
        {
            PlayerReset_Click(sender, e);
            m_bIsPlaying = true;
        }

        private void buttonPlayerStop_Click(object sender, EventArgs e)
        {
            m_bIsPlaying = false;
        }

        private void PlayerReset_Click(object sender, EventArgs e)
        {
            m_nFrameNumber = 0;
            m_fTimer = 0;
        }

        
    }
}