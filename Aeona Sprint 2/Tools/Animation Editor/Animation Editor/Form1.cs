﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;
using System.Xml.Linq;

namespace Animation_Editor
{
    public partial class Form1 : Form
    {
        SpriteSheet[,] AnimationSheet = new SpriteSheet[1,1];
        int CurrentAction = 1;
        int imageid = -1;
        public bool Looping = true;
        bool m_bIsPlaying = false;
        int m_nFrameNumber = 1;
        float m_fScale = 1.0f;
        float m_fTimer = 0.0f;
        BindingList<Frame> frameList = new BindingList<Frame>();
        BindingList<Animation> animationList = new BindingList<Animation>();

        ManagedTextureManager TM = ManagedTextureManager.Instance;
        ManagedDirect3D D3D = ManagedDirect3D.Instance;
        private Point start = Point.Empty;
        private Point end = Point.Empty;
        private String FilePath = String.Empty;
        System.DateTime PreviousTimeStamp = new System.DateTime();
        public Form1()
        {
            InitializeComponent();
            D3D.InitManagedDirect3D(graphicsPanelPlayer);
            D3D.InitManagedDirect3D(MainPanel);
            TM.InitManagedTextureManager(ManagedDirect3D.Instance.Device, ManagedDirect3D.Instance.Sprite);
            Size tempSize = new Size(800, 600);
            hScrollBar1.Maximum = tempSize.Height;
            vScrollBar1.Maximum = tempSize.Width;
            listBoxFrames.DataSource = frameList;

            Frame f = new Frame();
            String tempS = "Frame " + (frameList.Count + 1);
            f.Name = tempS;
            Point tempP = new Point((int)numericUpDownCurrentPointX.Value, (int)numericUpDownCurrentPointY.Value);
            f.Anchor = tempP;
            Rectangle tempF = new Rectangle((int)numericUpDownXPosition.Value, (int)numericUpDownYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.FrameRect = tempF;
            Rectangle tempC = new Rectangle((int)numericUpDownCollisionXPosition.Value, (int)numericUpDownCollisionYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.FrameDuration = 0.25M;
            f.TriggerEvent = "NONE";
            f.WeaponAnchor = Point.Empty;
            f.WeaponPoint = Point.Empty;
            f.WeaponAngle = 0;
            frameList.Add(f);
            listBoxFrames.DataSource = null;
            listBoxFrames.DataSource = frameList;

            listBoxAnimations.DataSource = animationList;

            listBoxAnimations.DataSource = null;
            listBoxAnimations.DataSource = animationList;

            DrawFrameRect.BackColor = Color.DodgerBlue;
            DrawFrameRect.ForeColor = Color.White;
            listBoxFrames.SelectedIndex = frameList.Count - 1;
            FilePath = Properties.Settings.Default.Path;
            //FilePath = Application.StartupPath.Remove(Application.StartupPath.Length - 26, 26);
            //FilePath += "resource";
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
            dlg.InitialDirectory = FilePath;
            dlg.Filter = "Images(*.BMP;*.JPG;*.JPEG;*.GIF;*.PNG;*.TGA;*.DDS)|*.BMP;*.JPG;*.JPEG;*.GIF;*.PNG;*.TGA;*.DDS|All files (*.*)|*.*";
            dlg.FilterIndex = 1;

            if (DialogResult.OK == dlg.ShowDialog())
            {
                imageid = TM.LoadTexture(dlg.FileName, 0);
                //FilePath = dlg.FileName;
                SpriteSheet temp = new SpriteSheet(dlg.FileName);
                AnimationSheet[0, 0] = temp;

                Graphics g = MainPanel.CreateGraphics();

                Size tempSize = new Size(temp.Sheet.Width, temp.Sheet.Height);
                if ((tempSize.Width - MainPanel.Width) >= 0)
                    hScrollBar1.Maximum = tempSize.Width - MainPanel.Width;
                else
                    hScrollBar1.Maximum = 0;

                if ((tempSize.Height - MainPanel.Height) >= 0)
                    vScrollBar1.Maximum = tempSize.Height - MainPanel.Height;
                else
                    vScrollBar1.Maximum = 0;
            }
        }
        
        public void Render()
        {
            Point offset = Point.Empty;
            offset.X -= hScrollBar1.Value;
            offset.Y -= vScrollBar1.Value;
            D3D.ChangeDisplayParam(MainPanel);
            {
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);
                if (imageid >= 0)
                    TM.Draw(imageid, offset.X, offset.Y, 1.0f, 1.0f, Rectangle.Empty, 0, 0, 0.0f, Color.White.ToArgb());
                D3D.Sprite.Flush();

                if (end != Point.Empty && CurrentAction == 1 || CurrentAction == 2)
                {
                    Rectangle temp = new Rectangle();
                    temp.X = start.X + offset.X;
                    temp.Y = start.Y + offset.Y;
                    temp.Width = end.X - start.X;
                    temp.Height = end.Y - start.Y;
                    D3D.DrawEmptyRect(temp, Color.Black,1);
                }
                else if (end != Point.Empty && CurrentAction == 5)
                {
                    D3D.DrawLine(start.X, start.Y, end.X, end.Y, Color.Black, 1);
                }
                else if (start != Point.Empty && CurrentAction == 3 || start != Point.Empty && CurrentAction == 4)
                {
                    Point tempPoint = new Point(start.X + offset.X, start.Y + offset.Y);

                    D3D.DrawLine(tempPoint.X - 5, tempPoint.Y, tempPoint.X + 5, tempPoint.Y, Color.Black, 1);
                    D3D.DrawLine(tempPoint.X, tempPoint.Y - 5, tempPoint.X, tempPoint.Y + 5, Color.Black, 1);
                }
                if(listBoxAnimations.SelectedIndex != -1)
                {
                    for (int i = 0; i < animationList[listBoxAnimations.SelectedIndex].NumFrames; i++)
                    {

                        Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[i];

                        Rectangle drawRect = new Rectangle(tempFrame.FrameRect.X + offset.X,
                            tempFrame.FrameRect.Y + offset.Y, tempFrame.FrameRect.Width, tempFrame.FrameRect.Height);

                        D3D.DrawEmptyRect(drawRect, Color.DodgerBlue, 1);

                        Rectangle CollisionRect = new Rectangle(tempFrame.Collision.X + offset.X,
                            tempFrame.Collision.Y + offset.Y, tempFrame.Collision.Width, tempFrame.Collision.Height);

                        D3D.DrawEmptyRect(CollisionRect, Color.Purple, 1);

                        if (tempFrame.Anchor != Point.Empty)
                        {
                            Point tempPoint = new Point(tempFrame.Anchor.X + offset.X, tempFrame.Anchor.Y + offset.Y);

                            D3D.DrawLine(tempPoint.X - 5, tempPoint.Y, tempPoint.X + 5, tempPoint.Y, Color.Red, 1);
                            D3D.DrawLine(tempPoint.X, tempPoint.Y - 5, tempPoint.X, tempPoint.Y + 5, Color.Red, 1);
                        }
                        if (tempFrame.WeaponAnchor != Point.Empty && tempFrame.WeaponPoint != Point.Empty)
                        {
                            Point tempPoint1 = new Point(tempFrame.WeaponAnchor.X + offset.X, tempFrame.WeaponAnchor.Y + offset.Y);
                            Point tempPoint2 = new Point(tempFrame.WeaponPoint.X + offset.X, tempFrame.WeaponPoint.Y + offset.Y);
                            D3D.DrawLine(tempPoint1.X, tempPoint1.Y, tempPoint2.X, tempPoint2.Y, Color.Gold, 1);
                        }
                        
                    }
                }
                else
                {
                    for (int i = 0; i < frameList.Count; i++)
                    {

                        Frame tempFrame = frameList[i];

                        Rectangle drawRect = new Rectangle(tempFrame.FrameRect.X + offset.X,
                            tempFrame.FrameRect.Y + offset.Y, tempFrame.FrameRect.Width, tempFrame.FrameRect.Height);

                        D3D.DrawEmptyRect(drawRect, Color.DodgerBlue, 1);

                        Rectangle CollisionRect = new Rectangle(tempFrame.Collision.X + offset.X,
                            tempFrame.Collision.Y + offset.Y, tempFrame.Collision.Width, tempFrame.Collision.Height);

                        D3D.DrawEmptyRect(CollisionRect, Color.Purple, 1);

                        if (tempFrame.Anchor != Point.Empty)
                        {
                            Point tempPoint = new Point(tempFrame.Anchor.X + offset.X, tempFrame.Anchor.Y + offset.Y);

                            D3D.DrawLine(tempPoint.X - 5, tempPoint.Y, tempPoint.X + 5, tempPoint.Y, Color.Red, 1);
                            D3D.DrawLine(tempPoint.X, tempPoint.Y - 5, tempPoint.X, tempPoint.Y + 5, Color.Red, 1);
                        }

                        if (tempFrame.WeaponAnchor != Point.Empty)
                        {
                            Point tempPoint = new Point(tempFrame.WeaponAnchor.X + offset.X, tempFrame.WeaponAnchor.Y + offset.Y);

                            D3D.DrawLine(tempPoint.X - 5, tempPoint.Y, tempPoint.X + 5, tempPoint.Y, Color.Green, 1);
                            D3D.DrawLine(tempPoint.X, tempPoint.Y - 5, tempPoint.X, tempPoint.Y + 5, Color.Green, 1);
                        }
                        if (tempFrame.WeaponAnchor != Point.Empty && tempFrame.WeaponPoint != Point.Empty)
                        {
                            Point tempPoint1 = new Point(tempFrame.WeaponAnchor.X + offset.X, tempFrame.WeaponAnchor.Y + offset.Y);
                            Point tempPoint2 = new Point(tempFrame.WeaponPoint.X + offset.X, tempFrame.WeaponPoint.Y + offset.Y);
                            D3D.DrawLine(tempPoint1.X, tempPoint1.Y, tempPoint2.X, tempPoint2.Y, Color.Gold, 1);
                        }
                    }
                }
                

                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
            }
            D3D.ChangeDisplayParam(graphicsPanelPlayer);
            {
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);
                if (animationList.Count > 0 && listBoxAnimations.SelectedIndex != -1)
                {
                    Animation temp = (Animation)animationList[listBoxAnimations.SelectedIndex];
                        System.DateTime StartTimeStamp = System.DateTime.Now;
                        System.TimeSpan ElapsedTime = StartTimeStamp - PreviousTimeStamp;
                        PreviousTimeStamp = StartTimeStamp;
                        Update((float)ElapsedTime.Milliseconds / 1000.0F);
                        if (imageid >= 0)
                            TM.Draw(imageid, (int)(graphicsPanelPlayer.Width * .5F) - (temp.Frames[m_nFrameNumber].Anchor.X - temp.Frames[m_nFrameNumber].FrameRect.X),
                                (int)(graphicsPanelPlayer.Height * .5F) - (temp.Frames[m_nFrameNumber].Anchor.Y - temp.Frames[m_nFrameNumber].FrameRect.Y),
                                m_fScale, m_fScale, temp.Frames[m_nFrameNumber].FrameRect, 0, 0, 0.0f, Color.White.ToArgb());
                }
                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
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
            DrawWeaponPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponAngle.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponAngle.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
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
            DrawWeaponPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponAngle.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponAngle.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
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
            DrawWeaponPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponAngle.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponAngle.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            CurrentAction = 3;
        }

        private void ToolStripNew_Click(object sender, EventArgs e)
        {
            //  Animation Name
            textBoxAnimationName.Text = string.Empty;
            //  Clear Frames
            //listBoxFrames.Items.Clear();
            animationList.Clear();
            frameList.Clear();
            listBoxFrames.ClearSelected();
            listBoxAnimations.ClearSelected();
            //  Current Point
            numericUpDownCurrentPointX.Value = 0.00M;
            numericUpDownCurrentPointY.Value = 0.00M;
            // Current Rect
            numericUpDownXPosition.Value = 0;
            numericUpDownYPosition.Value = 0;
            numericUpDownHeight.Value = 0;
            numericUpDownWidth.Value = 0;
            //  Weapon Anchor Point
            numericUpDownWeaponPointX.Value = 0;
            numericUpDownWeaponPointY.Value = 0;
            //  Weapon point
            numericUpDownWeaponPointY2.Value = 0;
            numericUpDownWeaponPointX2.Value = 0;
            //  Weapon Angle 
            numericUpDownAngle.Value = 0;
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
            String tempS = "Frame " + (frameList.Count + 1);
            f.Name = tempS;
            Point tempP = new Point((int)numericUpDownCurrentPointX.Value, (int)numericUpDownCurrentPointY.Value);
            f.Anchor = tempP;
            Rectangle tempF = new Rectangle((int)numericUpDownXPosition.Value, (int)numericUpDownYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.FrameRect = tempF;
            Rectangle tempC = new Rectangle((int)numericUpDownCollisionXPosition.Value, (int)numericUpDownCollisionYPosition.Value, (int)numericUpDownWidth.Value, (int)numericUpDownHeight.Value);
            f.WeaponAnchor = Point.Empty;
            f.WeaponPoint = Point.Empty;
            f.WeaponAngle = 0;
            frameList.Add(f);
            listBoxFrames.DataSource = null;
            listBoxFrames.DataSource = frameList;

            imageid = -1;

            Size tempSize = new Size(800, 600);
            hScrollBar1.Maximum = tempSize.Width - MainPanel.Width;
            vScrollBar1.Maximum = tempSize.Height - MainPanel.Height;
            

            listBoxFrames.SelectedIndex = frameList.Count - 1;
        }

        private void MainPanel_MouseDown(object sender, MouseEventArgs e)
        {
            Point offset = e.Location;
            offset.X += hScrollBar1.Value;
            offset.Y += vScrollBar1.Value;
            if ((e.Button & MouseButtons.Left) != 0)
            {
                start.X = offset.X;
                start.Y = offset.Y;
            }
   
        }

        private void MainPanel_MouseMove(object sender, MouseEventArgs e)
        {
            Point offset = e.Location;
            offset.X += hScrollBar1.Value;
            offset.Y += vScrollBar1.Value;
            if (((e.Button & MouseButtons.Left) != 0) && (start != Point.Empty))
            {
                end.X = offset.X;
                end.Y = offset.Y;
            }
        }

        private void MainPanel_MouseUp(object sender, MouseEventArgs e)
        {
            Rectangle temp = new Rectangle();
            if (start != Point.Empty)
            {
                if (listBoxAnimations.SelectedIndex != -1 && end != Point.Empty)
                {
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
                    else if ((end.Y - start.Y) < 0)
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
                    if (animationList[listBoxAnimations.SelectedIndex].NumFrames != 0 && listBoxFrames.SelectedIndex >= 0 )
                    {
                        switch (CurrentAction)
                        {
                            case 1:
                                {
                                    if (end != Point.Empty)
                                    {
                                        //  Draw Frame Rect
                                        Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                                        tempFrame.FrameRect = temp;
                                        animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                            case 2:
                                {
                                    if (end != Point.Empty)
                                    {
                                        //  Draw Collision Rect
                                        Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                                        tempFrame.Collision = temp;
                                        animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                            case 3:
                                {
                                    //  Draw Anchor Point
                                    Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                                    tempFrame.Anchor = start;
                                    animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
                                    break;
                                }
                            case 4:
                                {
                                    //  Draw Anchor Point
                                    Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                                    tempFrame.WeaponAnchor = start;
                                    animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
                                    break;
                                }
                            case 5:
                                {
                                    //  Draw Collision Rect
                                    if (end != Point.Empty)
                                    {
                                        Frame tempFrame = animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                                        tempFrame.WeaponAnchor = start;
                                        tempFrame.WeaponPoint = end;

                                        Double tempAngle = Math.Atan2(tempFrame.WeaponAnchor.X - tempFrame.WeaponPoint.X, tempFrame.WeaponAnchor.Y - tempFrame.WeaponPoint.Y);
                                        if (tempAngle > 0)
                                            tempAngle = tempAngle * (180 / Math.PI);
                                        else
                                            tempAngle = 360 + tempAngle * (180 / Math.PI);
                                        tempFrame.WeaponAngle = (Decimal)tempAngle;

                                        animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                        }

                    }

                    start = Point.Empty;
                    end = Point.Empty;
                }
                else
                {
                    if (end != Point.Empty)
                    {
                        if ((end.X - start.X) < 0 && (end.Y - start.Y) < 0 )
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
                        else if ((end.Y - start.Y) < 0)
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
                    }



                    if (frameList.Count != 0 && listBoxFrames.SelectedIndex >= 0)
                    {
                        switch (CurrentAction)
                        {
                            case 1:
                                {
                                    if (end != Point.Empty)
                                    {
                                        //  Draw Frame Rect
                                        Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                                        tempFrame.FrameRect = temp;
                                        frameList[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                            case 2:
                                {
                                    //  Draw Collision Rect
                                    if (end != Point.Empty)
                                    {
                                        Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                                        tempFrame.Collision = temp;
                                        frameList[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                            case 3:
                                {
                                    //  Draw Anchor Point
                                    Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                                    tempFrame.Anchor = start;
                                    frameList[listBoxFrames.SelectedIndex] = tempFrame;
                                    break;
                                }
                            case 4:
                                {
                                    //  Draw Anchor Point
                                    //Point temp2 = start;
                                    Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                                    tempFrame.WeaponAnchor = start;

                                    frameList[listBoxFrames.SelectedIndex] = tempFrame;
                                    break;
                                }
                            case 5:
                                {
                                    //  Draw Collision Rect
                                    if (end != Point.Empty)
                                    {
                                        Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                                        tempFrame.WeaponAnchor = start;
                                        tempFrame.WeaponPoint = end;

                                        Double tempAngle = Math.Atan2(tempFrame.WeaponAnchor.X - tempFrame.WeaponPoint.X, tempFrame.WeaponAnchor.Y - tempFrame.WeaponPoint.Y);
                                        if(tempAngle > 0)
                                            tempAngle = tempAngle *(180/Math.PI);
                                        else
                                            tempAngle = 360 + tempAngle * (180 / Math.PI);
                                        tempFrame.WeaponAngle = (Decimal)tempAngle;

                                        frameList[listBoxFrames.SelectedIndex] = tempFrame;
                                    }
                                    break;
                                }
                        }

                    }

                    start = Point.Empty;
                    end = Point.Empty;
                }
            }
        }

        private void FrameListAdd_Click(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                Frame f = new Frame();
                String tempS = "Frame " + (animationList[listBoxAnimations.SelectedIndex].NumFrames + 1);
                f.Name = tempS;
                Point tempP = new Point(0, 0);
                f.Anchor = tempP;
                Rectangle tempF = new Rectangle(0, 0, 0, 0);
                f.FrameRect = tempF;
                Rectangle tempC = new Rectangle(0, 0, 0, 0);
                f.FrameDuration = 0.25M;
                f.TriggerEvent = "NONE";
                f.WeaponAnchor = Point.Empty;
                f.WeaponPoint = Point.Empty;
                f.WeaponAngle = 0;
                animationList[listBoxAnimations.SelectedIndex].Frames.Add(f);
                animationList[listBoxAnimations.SelectedIndex].NumFrames++;
                listBoxFrames.DataSource = animationList[listBoxAnimations.SelectedIndex].Frames;
            }
            else
            {
                listBoxFrames.DataSource = frameList;
                Frame f = new Frame();
                String tempS = "Frame " + (frameList.Count + 1);
                f.Name = tempS;
                Point tempP = new Point(0, 0);
                f.Anchor = tempP;
                Rectangle tempF = new Rectangle(0, 0, 0, 0);
                f.FrameRect = tempF;
                Rectangle tempC = new Rectangle(0, 0, 0, 0);
                f.FrameDuration = 0.25M;
                f.TriggerEvent = "NONE";
                f.WeaponAnchor = Point.Empty;
                f.WeaponPoint = Point.Empty;
                f.WeaponAngle = 0;
                frameList.Add(f);
            }
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
            if (listBoxAnimations.SelectedIndex != -1)
            {
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
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
                //  Weapon Anchor Point
                numericUpDownWeaponPointX.Value = tempFrame.WeaponAnchor.X;
                numericUpDownWeaponPointY.Value = tempFrame.WeaponAnchor.Y;
                //  Weapon point
                numericUpDownWeaponPointX2.Value = tempFrame.WeaponPoint.X;
                numericUpDownWeaponPointY2.Value = tempFrame.WeaponPoint.Y;
                //  Weapon Angle 
                numericUpDownAngle.Value = tempFrame.WeaponAngle;
                //  Frame Duration
                numericUpDownFrameDuration.Value = tempFrame.FrameDuration;
                //  Trigger Event
                TextBoxFrameTriggerEvent.Text = tempFrame.TriggerEvent;
            }
            else if(listBoxFrames.SelectedIndex != -1)
            {
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
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
                //  Weapon Anchor Point
                numericUpDownWeaponPointX.Value = tempFrame.WeaponAnchor.X;
                numericUpDownWeaponPointY.Value = tempFrame.WeaponAnchor.Y;
                //  Weapon point
                numericUpDownWeaponPointX2.Value = tempFrame.WeaponPoint.X;
                numericUpDownWeaponPointY2.Value = tempFrame.WeaponPoint.Y;
                //  Weapon Angle 
                numericUpDownAngle.Value = tempFrame.WeaponAngle;
                //  Frame Duration
                numericUpDownFrameDuration.Value = tempFrame.FrameDuration;
                //  Trigger Event
                TextBoxFrameTriggerEvent.Text = tempFrame.TriggerEvent;
            }
          
        }

        private void numericUpDownCurrentPointX_ValueChanged(object sender, EventArgs e)
        {

            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;
                    
                temp.X = (int)numericUpDownCurrentPointX.Value;
                tempFrame.Anchor = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;

                temp.X = (int)numericUpDownCurrentPointX.Value;
                tempFrame.Anchor = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCurrentPointY_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;

                temp.Y = (int)numericUpDownCurrentPointY.Value;
                tempFrame.Anchor = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Anchor;

                temp.Y = (int)numericUpDownCurrentPointY.Value;
                tempFrame.Anchor = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownXPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.X = (int)numericUpDownXPosition.Value;
                tempFrame.FrameRect = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if(listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.X = (int)numericUpDownXPosition.Value;
                tempFrame.FrameRect = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownYPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Y = (int)numericUpDownYPosition.Value;
                tempFrame.FrameRect = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Y = (int)numericUpDownYPosition.Value;
                tempFrame.FrameRect = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownHeight_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Height = (int)numericUpDownHeight.Value;
                tempFrame.FrameRect = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Height = (int)numericUpDownHeight.Value;
                tempFrame.FrameRect = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownWidth_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Width = (int)numericUpDownWidth.Value;
                tempFrame.FrameRect = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.FrameRect;

                temp.Width = (int)numericUpDownWidth.Value;
                tempFrame.FrameRect = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionXPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.X = (int)numericUpDownCollisionXPosition.Value;
                tempFrame.Collision = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.X = (int)numericUpDownCollisionXPosition.Value;
                tempFrame.Collision = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionYPosition_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Y = (int)numericUpDownCollisionYPosition.Value;
                tempFrame.Collision = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Y = (int)numericUpDownCollisionYPosition.Value;
                tempFrame.Collision = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionHeight_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Height = (int)numericUpDownCollisionHeight.Value;
                tempFrame.Collision = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Height = (int)numericUpDownCollisionHeight.Value;
                tempFrame.Collision = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownCollisionWidth_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Width = (int)numericUpDownCollisionWidth.Value;
                tempFrame.Collision = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Rectangle temp = new Rectangle();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.Collision;

                temp.Width = (int)numericUpDownCollisionWidth.Value;
                tempFrame.Collision = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void buttonPlayerPlay_Click(object sender, EventArgs e)
        {
            Play();
        }

        private void buttonPlayerStop_Click(object sender, EventArgs e)
        {
            Stop();
        }

        private void PlayerReset_Click(object sender, EventArgs e)
        {
            Reset();
        }

        private void Play()
        {
            Reset();
            m_bIsPlaying = true;
        }

        private void Stop()
        {
            m_bIsPlaying = false;
        }

        private void Reset()
        {
            m_nFrameNumber = 0;
            m_fTimer = 0;
        }

        private void Update(float fElaspedTime)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                Animation temp = (Animation)animationList[listBoxAnimations.SelectedIndex];
                if (!m_bIsPlaying)
                    return;
                m_fTimer += fElaspedTime;
                m_fTimer = ((float)temp.Speed) * m_fTimer;
                if (m_fTimer > ((float)temp.Frames[m_nFrameNumber].FrameDuration))
                {
                    m_fTimer -= ((float)temp.Frames[m_nFrameNumber].FrameDuration);
                    m_nFrameNumber++;
                    if (m_nFrameNumber >= temp.Frames.Count)
                    {
                        if (temp.Looping)
                        {
                            Play();
                        }
                        else
                        {
                            Stop();
                            m_nFrameNumber = temp.Frames.Count - 1;
                        }
                    }
                }
            }
            
        }

        private void AnimationListAdd_Click(object sender, EventArgs e)
        {
           if(listBoxFrames.SelectedIndex != -1)
            {
                
                Animation Temp = new Animation();
                Temp.Name = textBoxAnimationName.Text;
                BindingList<Frame> frames = new BindingList<Frame>();
                for (int i = 0; i < frameList.Count; i++)
                    frames.Add((Frame)frameList[i]);
                Temp.Frames = frames;
                Temp.NumFrames = frameList.Count;
                Temp.Speed = numericUpDownAnimationSpeed.Value;
                Temp.Looping = checkBoxLooping.Checked;
                Temp.Oslating = checkBoxOslating.Checked;
                if (Temp.Name != String.Empty)
                {
                    animationList.Add(Temp);
                    frameList.Clear();
                }
            }
            
            
        }

        private void numericUpDownFrameDuration_ValueChanged(object sender, EventArgs e)
        {
            if (frameList.Count != 0)
            {
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                tempFrame.FrameDuration = numericUpDownFrameDuration.Value;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void listBoxAnimations_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                
                Animation temp = (Animation)animationList[listBoxAnimations.SelectedIndex];
                listBoxFrames.DataSource = animationList[listBoxAnimations.SelectedIndex].Frames;
                listBoxFrames.SelectedIndex = 0;
               
                textBoxAnimationName.Text = temp.Name;
                checkBoxLooping.Checked = temp.Looping;
                checkBoxOslating.Checked = temp.Oslating;
                numericUpDownAnimationSpeed.Value = temp.Speed;
            }

        }

        private void ToolStripSaveXML_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Xml Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.DefaultExt = "xml";
            dlg.InitialDirectory = FilePath;
            if (DialogResult.OK == dlg.ShowDialog())
            {
               XElement root = new XElement("Animations");
               String tempstring = String.Empty;
               String fowardString = String.Empty;
               String tempFilename = String.Empty;
            //   String destFile = Application.StartupPath.Remove(Application.StartupPath.Length - 26, 26);
               String destFile = FilePath;
            //   destFile += "resource\\";
            //
            //
               
               for (int j = AnimationSheet[0, 0].Filepath.Length - 1; j >= 0; j--)
             {
                 if (AnimationSheet[0, 0].Filepath[j].Equals('\\'))
                     break;
                 else
                     tempstring += AnimationSheet[0, 0].Filepath[j];
             }
               destFile += "\\";
             for (int l = tempstring.Length - 1; l >= 0; l--)
             {
                 destFile += tempstring[l];
                 fowardString += tempstring[l];
             }

             //if (tempFilename != destFile)
             //{
             //    System.IO.File.Copy(AnimationSheet[0, 0].Filepath, destFile, true);
             //}
               
               XAttribute FileName = new XAttribute("FileName",fowardString);
               root.Add(FileName);

               for (int i = 0; i < animationList.Count; i++)
               {
                   Animation temp = (Animation)animationList[i];
                   XElement Animation = new XElement("Animation");
                   root.Add(Animation);
                   XAttribute name = new XAttribute("name",temp.Name);
                   Animation.Add(name);
                   XAttribute looping = new XAttribute("looping",  (temp.Looping ? 1 : 0));
                   Animation.Add(looping);
                   XAttribute oslating = new XAttribute("oslating", (temp.Oslating ? 1 : 0));
                   Animation.Add(oslating);
                   XAttribute playing = new XAttribute("playing", (temp.Playing ? 1 : 0));
                   Animation.Add(playing);
                   XAttribute speed = new XAttribute("speed", temp.Speed);
                   Animation.Add(speed);
                   XAttribute NumFrames = new XAttribute("NumFrames", temp.NumFrames);
                   Animation.Add(NumFrames);

                   for (int j = 0; j < temp.Frames.Count; j++)
                   {
                       Frame tempF = temp.Frames[j];
                       XElement Frame = new XElement("Frame");
                       Animation.Add(Frame);

                       XAttribute Duration = new XAttribute("duration", tempF.FrameDuration);
                       Frame.Add(Duration);
                       XAttribute fEvent = new XAttribute("event", tempF.TriggerEvent);
                       Frame.Add(fEvent);

                       XElement DrawRect = new XElement("DrawRect");
                       Frame.Add(DrawRect);

                       XAttribute dX = new XAttribute("x", tempF.FrameRect.X);
                       DrawRect.Add(dX);
                       XAttribute dY = new XAttribute("y", tempF.FrameRect.Y);
                       DrawRect.Add(dY);
                       XAttribute dWidth = new XAttribute("width", tempF.FrameRect.Width);
                       DrawRect.Add(dWidth);
                       XAttribute dHeight = new XAttribute("height", tempF.FrameRect.Height);
                       DrawRect.Add(dHeight);

                       XElement CollisionRect = new XElement("CollisionRect");
                       Frame.Add(CollisionRect);

                       XAttribute cX = new XAttribute("x", tempF.Collision.X - tempF.FrameRect.X);
                       CollisionRect.Add(cX);
                       XAttribute cY = new XAttribute("y", tempF.Collision.Y - tempF.FrameRect.Y);
                       CollisionRect.Add(cY);
                       XAttribute cWidth = new XAttribute("width", tempF.Collision.Width);
                       CollisionRect.Add(cWidth);
                       XAttribute cHeight = new XAttribute("height", tempF.Collision.Height);
                       CollisionRect.Add(cHeight);

                       XElement AnchorPoint = new XElement("Anchor");
                       Frame.Add(AnchorPoint);

                       XAttribute pX = new XAttribute("x", tempF.Anchor.X - tempF.FrameRect.X);
                       AnchorPoint.Add(pX);
                       XAttribute pY = new XAttribute("y", tempF.Anchor.Y - tempF.FrameRect.Y);
                       AnchorPoint.Add(pY);

                       XElement Weapon = new XElement("Weapon");
                       
                       XAttribute wpX = new XAttribute("x", tempF.WeaponAnchor.X - tempF.FrameRect.X);
                       Weapon.Add(wpX);
                       XAttribute wpY = new XAttribute("y", tempF.WeaponAnchor.Y - tempF.FrameRect.Y);
                       Weapon.Add(wpY);
                       XAttribute wpX2 = new XAttribute("x2", tempF.WeaponPoint.X - tempF.FrameRect.X);
                       Weapon.Add(wpX2);
                       XAttribute wpY2 = new XAttribute("y2", tempF.WeaponPoint.Y - tempF.FrameRect.Y);
                       Weapon.Add(wpY2);
                       XAttribute wpA = new XAttribute("angle", tempF.WeaponAngle);
                       Weapon.Add(wpA);

                       Frame.Add(Weapon);
                       
                   }
               }
               root.Save(dlg.FileName);
            }
        }

        private void toolStripOpenXML_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Xml Files|*.xml";
            dlg.FilterIndex = 2;
            dlg.InitialDirectory = FilePath;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                XElement root = XElement.Load(dlg.FileName);
                XAttribute FileName = root.Attribute("FileName");
                animationList.Clear();
                frameList.Clear();
               
                String tempFilePath = FilePath;
                tempFilePath += "\\";
                tempFilePath += FileName.Value;

                imageid = TM.LoadTexture(tempFilePath, 0);
                SpriteSheet temp = new SpriteSheet(tempFilePath);
                AnimationSheet[0, 0] = temp;

                //Graphics g = MainPanel.CreateGraphics();
                Size tempSize = new Size(temp.Sheet.Width, temp.Sheet.Height);

                if ((tempSize.Width - MainPanel.Width) >= 0)
                    hScrollBar1.Maximum = tempSize.Width - MainPanel.Width;
                else
                    hScrollBar1.Maximum = 0;

                if ((tempSize.Height - MainPanel.Height) >= 0)
                    vScrollBar1.Maximum = tempSize.Height - MainPanel.Height;
                else
                    vScrollBar1.Maximum = 0;

                IEnumerable<XElement> xAnimations = root.Elements("Animation");

                //BindingList<Frame> frames = new BindingList<Frame>();

                


                foreach (XElement xAnimation in xAnimations)
                {
                    Animation Temp = new Animation();
                    XAttribute name = xAnimation.Attribute("name");
                    Temp.Name = name.Value;
                    XAttribute looping = xAnimation.Attribute("looping");
                    Temp.Looping = (int.Parse(looping.Value) == 1) ? true : false;
                    XAttribute oslating = xAnimation.Attribute("oslating");
                    Temp.Oslating = (int.Parse(oslating.Value) == 1) ? true : false;
                    XAttribute playing = xAnimation.Attribute("playing");
                    Temp.Playing = (int.Parse(playing.Value) == 1) ? true : false;
                    XAttribute speed = xAnimation.Attribute("speed");
                    Temp.Speed = decimal.Parse(speed.Value);
                    XAttribute NumFrames = xAnimation.Attribute("NumFrames");
                    Temp.NumFrames = int.Parse(NumFrames.Value);

                    IEnumerable<XElement> xFrames = xAnimation.Elements("Frame");
                    
                    foreach (XElement xFrame in xFrames)
                    {
                        Frame TempFrame = new Frame();
                        TempFrame.Name = "Frame " + (frameList.Count + 1);
                        XAttribute duration = xFrame.Attribute("duration");
                        TempFrame.FrameDuration = decimal.Parse(duration.Value);
                        XAttribute events = xFrame.Attribute("event");
                        TempFrame.TriggerEvent = events.Value;

                        XElement xDrawRect = xFrame.Element("DrawRect");
                        {
                            Rectangle tempDraw = new Rectangle();
                            XAttribute dx = xDrawRect.Attribute("x");
                            tempDraw.X = int.Parse(dx.Value);
                            XAttribute dy = xDrawRect.Attribute("y");
                            tempDraw.Y = int.Parse(dy.Value);
                            XAttribute dwidth = xDrawRect.Attribute("width");
                            tempDraw.Width = int.Parse(dwidth.Value);
                            XAttribute dheight = xDrawRect.Attribute("height");
                            tempDraw.Height = int.Parse(dheight.Value);
                            TempFrame.FrameRect = tempDraw;
                        }
                        XElement xCollisionRect = xFrame.Element("CollisionRect");
                        {
                            Rectangle tempCollision = new Rectangle();
                            XAttribute cx = xCollisionRect.Attribute("x");
                            tempCollision.X = int.Parse(cx.Value);
                            tempCollision.X += TempFrame.FrameRect.X;
                            XAttribute cy = xCollisionRect.Attribute("y");
                            tempCollision.Y = int.Parse(cy.Value);
                            tempCollision.Y += TempFrame.FrameRect.Y;
                            XAttribute cwidth = xCollisionRect.Attribute("width");
                            tempCollision.Width = int.Parse(cwidth.Value);
                            XAttribute cheight = xCollisionRect.Attribute("height");
                            tempCollision.Height = int.Parse(cheight.Value);
                            TempFrame.Collision = tempCollision;
                        }
                        XElement xAnchor = xFrame.Element("Anchor");
                        {
                            Point tempPoint = new Point();
                            XAttribute ax = xAnchor.Attribute("x");
                            tempPoint.X = int.Parse(ax.Value);
                            tempPoint.X += TempFrame.FrameRect.X;
                            XAttribute ay = xAnchor.Attribute("y");
                            tempPoint.Y = int.Parse(ay.Value);
                            tempPoint.Y += TempFrame.FrameRect.Y;
                            TempFrame.Anchor = tempPoint;
                        }
                        XElement xWeapon = xFrame.Element("Weapon");
                        {
                            Point tempWeapon1 = Point.Empty;
                            Point tempWeapon2 = Point.Empty;
                            Decimal tempAngle = 0;
                        
                            XAttribute wx1 = xWeapon.Attribute("x");
                            tempWeapon1.X = int.Parse(wx1.Value);
                            XAttribute wy1 = xWeapon.Attribute("y");
                            tempWeapon1.Y = int.Parse(wy1.Value);
                        
                            TempFrame.WeaponAnchor = tempWeapon1;
                        
                            XAttribute wx2 = xWeapon.Attribute("x2");
                            tempWeapon2.X = int.Parse(wx2.Value);
                            XAttribute wy2 = xWeapon.Attribute("y2");
                            tempWeapon2.Y = int.Parse(wy2.Value);
                        
                            TempFrame.WeaponPoint = tempWeapon2;
                        
                            XAttribute wa = xWeapon.Attribute("angle");
                            tempAngle = Decimal.Parse(wa.Value);
                        
                            TempFrame.WeaponAngle = tempAngle;
                        }
                        frameList.Add(TempFrame);
                    }
                    BindingList<Frame> frames = new BindingList<Frame>();
                    for (int i = 0; i < frameList.Count; i++)
                        frames.Add((Frame)frameList[i]);
                    Temp.Frames = new BindingList<Frame>(frames);
                    frameList.Clear();
                    animationList.Add(Temp);
                }
            }
        }

        private void FrameListRemove_Click(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Frames.Remove(animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex]);
                animationList[listBoxAnimations.SelectedIndex].NumFrames = animationList[listBoxAnimations.SelectedIndex].Frames.Count;
                for (int i = 0; i < frameList.Count; i++)
                {
                    Frame temp = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[i];
                    String tempS = "Frame " + (i + 1);
                    temp.Name = tempS;
                    animationList[listBoxAnimations.SelectedIndex].Frames[i] = temp;
                }
            }
            else if(listBoxFrames.SelectedIndex != -1)
            {
                frameList.RemoveAt(listBoxFrames.SelectedIndex);
                for (int i = 0; i < frameList.Count; i++)
                {
                    Frame temp = (Frame)frameList[i];
                    String tempS = "Frame " + (i + 1);
                    temp.Name = tempS;
                    frameList[i] = temp;
                }
            }
        }

        private void AnimationListRemove_Click(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
                animationList.RemoveAt(listBoxAnimations.SelectedIndex);
        }

        private void buttonPlayerNextFrame_Click(object sender, EventArgs e)
        {
            Animation temp = (Animation)animationList[listBoxAnimations.SelectedIndex];
            if (temp.Frames.Count > m_nFrameNumber+1)
            {
                m_nFrameNumber++;
            }
        }

        private void buttonPlayerPrevFrame_Click(object sender, EventArgs e)
        {
            Animation temp = (Animation)animationList[listBoxAnimations.SelectedIndex];
            if (0 <= m_nFrameNumber-1)
            {
                m_nFrameNumber--;
            }
        }

        private void buttonZoomIn_Click(object sender, EventArgs e)
        {
            //ZOOM IN
            m_fScale *= 2;
        }

        private void buttonZoomOut_Click(object sender, EventArgs e)
        {
            //ZOOM OUT
            m_fScale *= 0.5f;
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

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            Render();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            Render();
        }

        private void DeSelect_Click(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                if (listBoxAnimations.GetSelected(listBoxAnimations.SelectedIndex) == true)
                    listBoxAnimations.SetSelected(listBoxAnimations.SelectedIndex, false);
            }
            frameList.Clear();
            listBoxFrames.DataSource = frameList;
            
            Stop();
            textBoxAnimationName.Text = String.Empty;
            numericUpDownAnimationSpeed.Value = 1.0M;
            numericUpDownFrameDuration.Value = 0.25M;
            checkBoxLooping.Checked = false;
            checkBoxOslating.Checked = false;
        }

        private void textBoxAnimationName_Leave(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Name = textBoxAnimationName.Text;
                listBoxAnimations.DataSource = null;
                listBoxAnimations.DataSource = animationList;
            }
        }

        private void checkBoxLooping_Leave(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Looping = checkBoxLooping.Checked;
                listBoxAnimations.DataSource = null;
                listBoxAnimations.DataSource = animationList;
            }
        }

        private void checkBoxOslating_CheckedChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Oslating = checkBoxOslating.Checked;
                listBoxAnimations.DataSource = null;
                listBoxAnimations.DataSource = animationList;
            }
        }

        private void numericUpDownAnimationSpeed_Leave(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Speed = numericUpDownAnimationSpeed.Value;
                listBoxAnimations.DataSource = null;
                listBoxAnimations.DataSource = animationList;
            }
        }

        private void numericUpDownFrameDuration_Leave(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex != -1)
            {
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex].FrameDuration = numericUpDownFrameDuration.Value;
                listBoxAnimations.DataSource = null;
                listBoxAnimations.DataSource = animationList;
            }
        }

        private void TextBoxFrameTriggerEvent_Leave(object sender, EventArgs e)
        {
           if (listBoxAnimations.SelectedIndex != -1)
           {
               animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex].TriggerEvent = TextBoxFrameTriggerEvent.Text;
               listBoxAnimations.DataSource = null;
               listBoxAnimations.DataSource = animationList;
           }
        }

        private void DrawWeaponPoint_Click(object sender, EventArgs e)
        {
            DrawFrameRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawFrameRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawCollisionRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawCollisionRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawAnchorPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawAnchorPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponPoint.BackColor = Color.Green;
            DrawWeaponPoint.ForeColor = Color.White;
            DrawWeaponAngle.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponAngle.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            CurrentAction = 4;
        }

        private void numericUpDownWeaponPointX_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponAnchor;

                temp.X = (int)numericUpDownWeaponPointX.Value;
                tempFrame.WeaponAnchor = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponAnchor;

                temp.X = (int)numericUpDownWeaponPointX.Value;
                tempFrame.WeaponAnchor = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownWeaponPointY_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponAnchor;

                temp.Y = (int)numericUpDownWeaponPointY.Value;
                tempFrame.WeaponAnchor = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponAnchor;

                temp.Y = (int)numericUpDownWeaponPointY.Value;
                tempFrame.WeaponAnchor = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void DrawWeaponAngle_Click(object sender, EventArgs e)
        {
            DrawFrameRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawFrameRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawCollisionRect.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawCollisionRect.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawAnchorPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawAnchorPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponPoint.BackColor = Color.FromKnownColor(KnownColor.Control);
            DrawWeaponPoint.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            DrawWeaponAngle.BackColor = Color.Gold;
            DrawWeaponAngle.ForeColor = Color.White;

            CurrentAction = 5;
        }


        private void numericUpDownWeaponPointY2_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponPoint;

                temp.Y = (int)numericUpDownWeaponPointY2.Value;
                tempFrame.WeaponPoint = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponPoint;

                temp.Y = (int)numericUpDownWeaponPointY2.Value;
                tempFrame.WeaponPoint = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownWeaponPointX2_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponPoint;

                temp.X = (int)numericUpDownWeaponPointX2.Value;
                tempFrame.WeaponPoint = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Point temp = new Point();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];
                temp = tempFrame.WeaponPoint;

                temp.X = (int)numericUpDownWeaponPointX2.Value;
                tempFrame.WeaponPoint = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }

        private void numericUpDownAngle_ValueChanged(object sender, EventArgs e)
        {
            if (listBoxAnimations.SelectedIndex >= 0)
            {
                Decimal temp = new Decimal();
                Frame tempFrame = (Frame)animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex];
                
                temp = numericUpDownAngle.Value;
                tempFrame.WeaponAngle = temp;
                animationList[listBoxAnimations.SelectedIndex].Frames[listBoxFrames.SelectedIndex] = tempFrame;
            }
            else if (listBoxFrames.SelectedIndex != -1)
            {
                Decimal temp = new Decimal();
                Frame tempFrame = (Frame)frameList[listBoxFrames.SelectedIndex];

                temp = numericUpDownAngle.Value;
                tempFrame.WeaponAngle = temp;
                frameList[listBoxFrames.SelectedIndex] = tempFrame;
            }
        }
    }
}