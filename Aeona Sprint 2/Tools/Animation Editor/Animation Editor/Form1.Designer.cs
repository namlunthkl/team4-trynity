namespace Animation_Editor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripNew = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripImportAnimationImage = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripOpenXML = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripSaveXML = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.ToolStripOpenBinary = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSaveBinary = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.ToolStripExit = new System.Windows.Forms.ToolStripMenuItem();
            this.GroupBoxDraw = new System.Windows.Forms.GroupBox();
            this.DrawWeaponAngle = new System.Windows.Forms.Button();
            this.DrawWeaponPoint = new System.Windows.Forms.Button();
            this.DrawAnchorPoint = new System.Windows.Forms.Button();
            this.DrawCollisionRect = new System.Windows.Forms.Button();
            this.DrawFrameRect = new System.Windows.Forms.Button();
            this.GroupBoxEditAnchorPoint = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDownCurrentPointY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownCurrentPointX = new System.Windows.Forms.NumericUpDown();
            this.GroupBoxEditFrameRect = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDownWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownHeight = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownYPosition = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownXPosition = new System.Windows.Forms.NumericUpDown();
            this.groupBoxAnimation = new System.Windows.Forms.GroupBox();
            this.checkBoxOslating = new System.Windows.Forms.CheckBox();
            this.checkBoxLooping = new System.Windows.Forms.CheckBox();
            this.FrameListRemove = new System.Windows.Forms.Button();
            this.FrameListAdd = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.listBoxFrames = new System.Windows.Forms.ListBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxAnimationName = new System.Windows.Forms.TextBox();
            this.groupBoxFrame = new System.Windows.Forms.GroupBox();
            this.TextBoxFrameTriggerEvent = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.numericUpDownFrameDuration = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownAnimationSpeed = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBoxAnimationPlayer = new System.Windows.Forms.GroupBox();
            this.groupBoxChangeFrame = new System.Windows.Forms.GroupBox();
            this.buttonPlayerPrevFrame = new System.Windows.Forms.Button();
            this.buttonPlayerNextFrame = new System.Windows.Forms.Button();
            this.PlayerReset = new System.Windows.Forms.Button();
            this.buttonPlayerStop = new System.Windows.Forms.Button();
            this.buttonPlayerPlay = new System.Windows.Forms.Button();
            this.groupBoxZoom = new System.Windows.Forms.GroupBox();
            this.buttonZoomOut = new System.Windows.Forms.Button();
            this.buttonZoomIn = new System.Windows.Forms.Button();
            this.groupBoxEditCollisionRect = new System.Windows.Forms.GroupBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.numericUpDownCollisionWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownCollisionHeight = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownCollisionYPosition = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownCollisionXPosition = new System.Windows.Forms.NumericUpDown();
            this.groupBoxAllAnimations = new System.Windows.Forms.GroupBox();
            this.AnimationListRemove = new System.Windows.Forms.Button();
            this.DeSelect = new System.Windows.Forms.Button();
            this.AnimationListAdd = new System.Windows.Forms.Button();
            this.listBoxAnimations = new System.Windows.Forms.ListBox();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.groupBoxWeaponPoint = new System.Windows.Forms.GroupBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.numericUpDownWeaponPointY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownWeaponPointX = new System.Windows.Forms.NumericUpDown();
            this.WeaponAngleGroupBox1 = new System.Windows.Forms.GroupBox();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.numericUpDownWeaponPointY2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownWeaponPointX2 = new System.Windows.Forms.NumericUpDown();
            this.label18 = new System.Windows.Forms.Label();
            this.numericUpDownAngle = new System.Windows.Forms.NumericUpDown();
            this.graphicsPanelPlayer = new Animation_Editor.GraphicsPanel();
            this.MainPanel = new Animation_Editor.GraphicsPanel();
            this.menuStrip1.SuspendLayout();
            this.GroupBoxDraw.SuspendLayout();
            this.GroupBoxEditAnchorPoint.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCurrentPointY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCurrentPointX)).BeginInit();
            this.GroupBoxEditFrameRect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownYPosition)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownXPosition)).BeginInit();
            this.groupBoxAnimation.SuspendLayout();
            this.groupBoxFrame.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameDuration)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAnimationSpeed)).BeginInit();
            this.groupBoxAnimationPlayer.SuspendLayout();
            this.groupBoxChangeFrame.SuspendLayout();
            this.groupBoxZoom.SuspendLayout();
            this.groupBoxEditCollisionRect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionYPosition)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionXPosition)).BeginInit();
            this.groupBoxAllAnimations.SuspendLayout();
            this.groupBoxWeaponPoint.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointX)).BeginInit();
            this.WeaponAngleGroupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointY2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointX2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAngle)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1022, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripNew,
            this.toolStripSeparator4,
            this.toolStripMenuItem1,
            this.toolStripSeparator2,
            this.toolStripImportAnimationImage,
            this.toolStripSeparator,
            this.toolStripOpenXML,
            this.ToolStripSaveXML,
            this.toolStripSeparator1,
            this.ToolStripOpenBinary,
            this.toolStripSaveBinary,
            this.toolStripSeparator3,
            this.ToolStripExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // ToolStripNew
            // 
            this.ToolStripNew.Image = ((System.Drawing.Image)(resources.GetObject("ToolStripNew.Image")));
            this.ToolStripNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ToolStripNew.Name = "ToolStripNew";
            this.ToolStripNew.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.ToolStripNew.Size = new System.Drawing.Size(201, 22);
            this.ToolStripNew.Text = "&New";
            this.ToolStripNew.Click += new System.EventHandler(this.ToolStripNew_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(198, 6);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(201, 22);
            this.toolStripMenuItem1.Text = "Set Enviroment Path";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(198, 6);
            // 
            // toolStripImportAnimationImage
            // 
            this.toolStripImportAnimationImage.Name = "toolStripImportAnimationImage";
            this.toolStripImportAnimationImage.Size = new System.Drawing.Size(201, 22);
            this.toolStripImportAnimationImage.Text = "Import Animation Sheet";
            this.toolStripImportAnimationImage.Click += new System.EventHandler(this.toolStripImportAnimationImage_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(198, 6);
            // 
            // toolStripOpenXML
            // 
            this.toolStripOpenXML.Image = ((System.Drawing.Image)(resources.GetObject("toolStripOpenXML.Image")));
            this.toolStripOpenXML.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripOpenXML.Name = "toolStripOpenXML";
            this.toolStripOpenXML.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.toolStripOpenXML.Size = new System.Drawing.Size(201, 22);
            this.toolStripOpenXML.Text = "&Open XML";
            this.toolStripOpenXML.Click += new System.EventHandler(this.toolStripOpenXML_Click);
            // 
            // ToolStripSaveXML
            // 
            this.ToolStripSaveXML.Image = ((System.Drawing.Image)(resources.GetObject("ToolStripSaveXML.Image")));
            this.ToolStripSaveXML.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ToolStripSaveXML.Name = "ToolStripSaveXML";
            this.ToolStripSaveXML.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.ToolStripSaveXML.Size = new System.Drawing.Size(201, 22);
            this.ToolStripSaveXML.Text = "&Save XML";
            this.ToolStripSaveXML.Click += new System.EventHandler(this.ToolStripSaveXML_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(198, 6);
            // 
            // ToolStripOpenBinary
            // 
            this.ToolStripOpenBinary.Enabled = false;
            this.ToolStripOpenBinary.Image = ((System.Drawing.Image)(resources.GetObject("ToolStripOpenBinary.Image")));
            this.ToolStripOpenBinary.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ToolStripOpenBinary.Name = "ToolStripOpenBinary";
            this.ToolStripOpenBinary.Size = new System.Drawing.Size(201, 22);
            this.ToolStripOpenBinary.Text = "Open Binary";
            // 
            // toolStripSaveBinary
            // 
            this.toolStripSaveBinary.Enabled = false;
            this.toolStripSaveBinary.Image = ((System.Drawing.Image)(resources.GetObject("toolStripSaveBinary.Image")));
            this.toolStripSaveBinary.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripSaveBinary.Name = "toolStripSaveBinary";
            this.toolStripSaveBinary.Size = new System.Drawing.Size(201, 22);
            this.toolStripSaveBinary.Text = "Save Binary";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(198, 6);
            // 
            // ToolStripExit
            // 
            this.ToolStripExit.Name = "ToolStripExit";
            this.ToolStripExit.Size = new System.Drawing.Size(201, 22);
            this.ToolStripExit.Text = "E&xit";
            this.ToolStripExit.Click += new System.EventHandler(this.ToolStripExit_Click);
            // 
            // GroupBoxDraw
            // 
            this.GroupBoxDraw.Controls.Add(this.DrawWeaponAngle);
            this.GroupBoxDraw.Controls.Add(this.DrawWeaponPoint);
            this.GroupBoxDraw.Controls.Add(this.DrawAnchorPoint);
            this.GroupBoxDraw.Controls.Add(this.DrawCollisionRect);
            this.GroupBoxDraw.Controls.Add(this.DrawFrameRect);
            this.GroupBoxDraw.Location = new System.Drawing.Point(677, 27);
            this.GroupBoxDraw.Name = "GroupBoxDraw";
            this.GroupBoxDraw.Size = new System.Drawing.Size(167, 168);
            this.GroupBoxDraw.TabIndex = 2;
            this.GroupBoxDraw.TabStop = false;
            this.GroupBoxDraw.Text = "Draw";
            // 
            // DrawWeaponAngle
            // 
            this.DrawWeaponAngle.Location = new System.Drawing.Point(7, 139);
            this.DrawWeaponAngle.Name = "DrawWeaponAngle";
            this.DrawWeaponAngle.Size = new System.Drawing.Size(149, 24);
            this.DrawWeaponAngle.TabIndex = 4;
            this.DrawWeaponAngle.Text = "Weapon Angle";
            this.DrawWeaponAngle.UseVisualStyleBackColor = true;
            this.DrawWeaponAngle.Click += new System.EventHandler(this.DrawWeaponAngle_Click);
            // 
            // DrawWeaponPoint
            // 
            this.DrawWeaponPoint.Location = new System.Drawing.Point(7, 110);
            this.DrawWeaponPoint.Name = "DrawWeaponPoint";
            this.DrawWeaponPoint.Size = new System.Drawing.Size(149, 23);
            this.DrawWeaponPoint.TabIndex = 3;
            this.DrawWeaponPoint.Text = "Weapon Anchor Point";
            this.DrawWeaponPoint.UseVisualStyleBackColor = true;
            this.DrawWeaponPoint.Click += new System.EventHandler(this.DrawWeaponPoint_Click);
            // 
            // DrawAnchorPoint
            // 
            this.DrawAnchorPoint.BackColor = System.Drawing.SystemColors.Control;
            this.DrawAnchorPoint.Location = new System.Drawing.Point(7, 80);
            this.DrawAnchorPoint.Name = "DrawAnchorPoint";
            this.DrawAnchorPoint.Size = new System.Drawing.Size(149, 24);
            this.DrawAnchorPoint.TabIndex = 2;
            this.DrawAnchorPoint.Text = "Anchor Point";
            this.DrawAnchorPoint.UseVisualStyleBackColor = false;
            this.DrawAnchorPoint.Click += new System.EventHandler(this.DrawAnchorPoint_Click);
            // 
            // DrawCollisionRect
            // 
            this.DrawCollisionRect.Location = new System.Drawing.Point(7, 50);
            this.DrawCollisionRect.Name = "DrawCollisionRect";
            this.DrawCollisionRect.Size = new System.Drawing.Size(149, 24);
            this.DrawCollisionRect.TabIndex = 1;
            this.DrawCollisionRect.Text = "Collision Rectangle";
            this.DrawCollisionRect.UseVisualStyleBackColor = true;
            this.DrawCollisionRect.Click += new System.EventHandler(this.DrawCollisionRect_Click);
            // 
            // DrawFrameRect
            // 
            this.DrawFrameRect.Location = new System.Drawing.Point(7, 20);
            this.DrawFrameRect.Name = "DrawFrameRect";
            this.DrawFrameRect.Size = new System.Drawing.Size(149, 24);
            this.DrawFrameRect.TabIndex = 0;
            this.DrawFrameRect.Text = "Frame Rectangle";
            this.DrawFrameRect.UseVisualStyleBackColor = true;
            this.DrawFrameRect.Click += new System.EventHandler(this.DrawFrameRect_Click);
            // 
            // GroupBoxEditAnchorPoint
            // 
            this.GroupBoxEditAnchorPoint.Controls.Add(this.label2);
            this.GroupBoxEditAnchorPoint.Controls.Add(this.label1);
            this.GroupBoxEditAnchorPoint.Controls.Add(this.numericUpDownCurrentPointY);
            this.GroupBoxEditAnchorPoint.Controls.Add(this.numericUpDownCurrentPointX);
            this.GroupBoxEditAnchorPoint.Location = new System.Drawing.Point(850, 27);
            this.GroupBoxEditAnchorPoint.Name = "GroupBoxEditAnchorPoint";
            this.GroupBoxEditAnchorPoint.Size = new System.Drawing.Size(167, 72);
            this.GroupBoxEditAnchorPoint.TabIndex = 3;
            this.GroupBoxEditAnchorPoint.TabStop = false;
            this.GroupBoxEditAnchorPoint.Text = "Edit Anchor Point :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Y Position :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "X Position :";
            // 
            // numericUpDownCurrentPointY
            // 
            this.numericUpDownCurrentPointY.Location = new System.Drawing.Point(75, 13);
            this.numericUpDownCurrentPointY.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCurrentPointY.Name = "numericUpDownCurrentPointY";
            this.numericUpDownCurrentPointY.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCurrentPointY.TabIndex = 1;
            this.numericUpDownCurrentPointY.ValueChanged += new System.EventHandler(this.numericUpDownCurrentPointY_ValueChanged);
            // 
            // numericUpDownCurrentPointX
            // 
            this.numericUpDownCurrentPointX.Location = new System.Drawing.Point(75, 39);
            this.numericUpDownCurrentPointX.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCurrentPointX.Name = "numericUpDownCurrentPointX";
            this.numericUpDownCurrentPointX.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCurrentPointX.TabIndex = 0;
            this.numericUpDownCurrentPointX.ValueChanged += new System.EventHandler(this.numericUpDownCurrentPointX_ValueChanged);
            // 
            // GroupBoxEditFrameRect
            // 
            this.GroupBoxEditFrameRect.Controls.Add(this.label6);
            this.GroupBoxEditFrameRect.Controls.Add(this.label5);
            this.GroupBoxEditFrameRect.Controls.Add(this.label4);
            this.GroupBoxEditFrameRect.Controls.Add(this.label3);
            this.GroupBoxEditFrameRect.Controls.Add(this.numericUpDownWidth);
            this.GroupBoxEditFrameRect.Controls.Add(this.numericUpDownHeight);
            this.GroupBoxEditFrameRect.Controls.Add(this.numericUpDownYPosition);
            this.GroupBoxEditFrameRect.Controls.Add(this.numericUpDownXPosition);
            this.GroupBoxEditFrameRect.Location = new System.Drawing.Point(850, 107);
            this.GroupBoxEditFrameRect.Name = "GroupBoxEditFrameRect";
            this.GroupBoxEditFrameRect.Size = new System.Drawing.Size(167, 125);
            this.GroupBoxEditFrameRect.TabIndex = 4;
            this.GroupBoxEditFrameRect.TabStop = false;
            this.GroupBoxEditFrameRect.Text = "Edit Frame Rectangle :";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(25, 103);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Width :";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Height :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(60, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Y Position :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "X Position :";
            // 
            // numericUpDownWidth
            // 
            this.numericUpDownWidth.Location = new System.Drawing.Point(73, 101);
            this.numericUpDownWidth.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownWidth.Name = "numericUpDownWidth";
            this.numericUpDownWidth.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownWidth.TabIndex = 3;
            this.numericUpDownWidth.ValueChanged += new System.EventHandler(this.numericUpDownWidth_ValueChanged);
            // 
            // numericUpDownHeight
            // 
            this.numericUpDownHeight.Location = new System.Drawing.Point(73, 74);
            this.numericUpDownHeight.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownHeight.Name = "numericUpDownHeight";
            this.numericUpDownHeight.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownHeight.TabIndex = 2;
            this.numericUpDownHeight.ValueChanged += new System.EventHandler(this.numericUpDownHeight_ValueChanged);
            // 
            // numericUpDownYPosition
            // 
            this.numericUpDownYPosition.Location = new System.Drawing.Point(73, 20);
            this.numericUpDownYPosition.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownYPosition.Name = "numericUpDownYPosition";
            this.numericUpDownYPosition.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownYPosition.TabIndex = 1;
            this.numericUpDownYPosition.ValueChanged += new System.EventHandler(this.numericUpDownYPosition_ValueChanged);
            // 
            // numericUpDownXPosition
            // 
            this.numericUpDownXPosition.Location = new System.Drawing.Point(73, 47);
            this.numericUpDownXPosition.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownXPosition.Name = "numericUpDownXPosition";
            this.numericUpDownXPosition.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownXPosition.TabIndex = 0;
            this.numericUpDownXPosition.ValueChanged += new System.EventHandler(this.numericUpDownXPosition_ValueChanged);
            // 
            // groupBoxAnimation
            // 
            this.groupBoxAnimation.Controls.Add(this.checkBoxOslating);
            this.groupBoxAnimation.Controls.Add(this.checkBoxLooping);
            this.groupBoxAnimation.Controls.Add(this.FrameListRemove);
            this.groupBoxAnimation.Controls.Add(this.FrameListAdd);
            this.groupBoxAnimation.Controls.Add(this.label8);
            this.groupBoxAnimation.Controls.Add(this.listBoxFrames);
            this.groupBoxAnimation.Controls.Add(this.label7);
            this.groupBoxAnimation.Controls.Add(this.textBoxAnimationName);
            this.groupBoxAnimation.Location = new System.Drawing.Point(677, 388);
            this.groupBoxAnimation.Name = "groupBoxAnimation";
            this.groupBoxAnimation.Size = new System.Drawing.Size(340, 249);
            this.groupBoxAnimation.TabIndex = 5;
            this.groupBoxAnimation.TabStop = false;
            this.groupBoxAnimation.Text = "Animation:";
            // 
            // checkBoxOslating
            // 
            this.checkBoxOslating.AutoSize = true;
            this.checkBoxOslating.Enabled = false;
            this.checkBoxOslating.Location = new System.Drawing.Point(263, 39);
            this.checkBoxOslating.Name = "checkBoxOslating";
            this.checkBoxOslating.Size = new System.Drawing.Size(64, 17);
            this.checkBoxOslating.TabIndex = 8;
            this.checkBoxOslating.Text = "Oslating";
            this.checkBoxOslating.UseVisualStyleBackColor = true;
            this.checkBoxOslating.CheckedChanged += new System.EventHandler(this.checkBoxOslating_CheckedChanged);
            // 
            // checkBoxLooping
            // 
            this.checkBoxLooping.AutoSize = true;
            this.checkBoxLooping.Location = new System.Drawing.Point(141, 39);
            this.checkBoxLooping.Name = "checkBoxLooping";
            this.checkBoxLooping.Size = new System.Drawing.Size(64, 17);
            this.checkBoxLooping.TabIndex = 7;
            this.checkBoxLooping.Text = "Looping";
            this.checkBoxLooping.UseVisualStyleBackColor = true;
            this.checkBoxLooping.Leave += new System.EventHandler(this.checkBoxLooping_Leave);
            // 
            // FrameListRemove
            // 
            this.FrameListRemove.Location = new System.Drawing.Point(186, 217);
            this.FrameListRemove.Name = "FrameListRemove";
            this.FrameListRemove.Size = new System.Drawing.Size(143, 23);
            this.FrameListRemove.TabIndex = 6;
            this.FrameListRemove.Text = "Remove";
            this.FrameListRemove.UseVisualStyleBackColor = true;
            this.FrameListRemove.Click += new System.EventHandler(this.FrameListRemove_Click);
            // 
            // FrameListAdd
            // 
            this.FrameListAdd.Location = new System.Drawing.Point(6, 217);
            this.FrameListAdd.Name = "FrameListAdd";
            this.FrameListAdd.Size = new System.Drawing.Size(143, 23);
            this.FrameListAdd.TabIndex = 4;
            this.FrameListAdd.Text = "Add";
            this.FrameListAdd.UseVisualStyleBackColor = true;
            this.FrameListAdd.Click += new System.EventHandler(this.FrameListAdd_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(4, 51);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(61, 13);
            this.label8.TabIndex = 3;
            this.label8.Text = "Frame List :";
            // 
            // listBoxFrames
            // 
            this.listBoxFrames.FormattingEnabled = true;
            this.listBoxFrames.Location = new System.Drawing.Point(6, 67);
            this.listBoxFrames.Name = "listBoxFrames";
            this.listBoxFrames.Size = new System.Drawing.Size(323, 147);
            this.listBoxFrames.TabIndex = 2;
            this.listBoxFrames.SelectedIndexChanged += new System.EventHandler(this.listBoxFrames_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 16);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(90, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "Animation Name :";
            // 
            // textBoxAnimationName
            // 
            this.textBoxAnimationName.Location = new System.Drawing.Point(141, 13);
            this.textBoxAnimationName.Name = "textBoxAnimationName";
            this.textBoxAnimationName.Size = new System.Drawing.Size(186, 20);
            this.textBoxAnimationName.TabIndex = 0;
            this.textBoxAnimationName.Leave += new System.EventHandler(this.textBoxAnimationName_Leave);
            // 
            // groupBoxFrame
            // 
            this.groupBoxFrame.Controls.Add(this.TextBoxFrameTriggerEvent);
            this.groupBoxFrame.Controls.Add(this.label11);
            this.groupBoxFrame.Controls.Add(this.label10);
            this.groupBoxFrame.Controls.Add(this.numericUpDownFrameDuration);
            this.groupBoxFrame.Controls.Add(this.numericUpDownAnimationSpeed);
            this.groupBoxFrame.Controls.Add(this.label9);
            this.groupBoxFrame.Location = new System.Drawing.Point(675, 643);
            this.groupBoxFrame.Name = "groupBoxFrame";
            this.groupBoxFrame.Size = new System.Drawing.Size(340, 100);
            this.groupBoxFrame.TabIndex = 6;
            this.groupBoxFrame.TabStop = false;
            this.groupBoxFrame.Text = "Edit Current Frame :";
            // 
            // TextBoxFrameTriggerEvent
            // 
            this.TextBoxFrameTriggerEvent.Location = new System.Drawing.Point(141, 67);
            this.TextBoxFrameTriggerEvent.Name = "TextBoxFrameTriggerEvent";
            this.TextBoxFrameTriggerEvent.Size = new System.Drawing.Size(164, 20);
            this.TextBoxFrameTriggerEvent.TabIndex = 12;
            this.TextBoxFrameTriggerEvent.Leave += new System.EventHandler(this.TextBoxFrameTriggerEvent_Leave);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(27, 70);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 13);
            this.label11.TabIndex = 11;
            this.label11.Text = "Trigger Event :";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(19, 41);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(85, 13);
            this.label10.TabIndex = 10;
            this.label10.Text = "Frame Duration :";
            // 
            // numericUpDownFrameDuration
            // 
            this.numericUpDownFrameDuration.DecimalPlaces = 2;
            this.numericUpDownFrameDuration.Increment = new decimal(new int[] {
            5,
            0,
            0,
            131072});
            this.numericUpDownFrameDuration.Location = new System.Drawing.Point(221, 39);
            this.numericUpDownFrameDuration.Maximum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDownFrameDuration.Name = "numericUpDownFrameDuration";
            this.numericUpDownFrameDuration.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownFrameDuration.TabIndex = 9;
            this.numericUpDownFrameDuration.Value = new decimal(new int[] {
            25,
            0,
            0,
            131072});
            this.numericUpDownFrameDuration.ValueChanged += new System.EventHandler(this.numericUpDownFrameDuration_ValueChanged);
            this.numericUpDownFrameDuration.Leave += new System.EventHandler(this.numericUpDownFrameDuration_Leave);
            // 
            // numericUpDownAnimationSpeed
            // 
            this.numericUpDownAnimationSpeed.DecimalPlaces = 2;
            this.numericUpDownAnimationSpeed.Increment = new decimal(new int[] {
            5,
            0,
            0,
            131072});
            this.numericUpDownAnimationSpeed.Location = new System.Drawing.Point(221, 13);
            this.numericUpDownAnimationSpeed.Name = "numericUpDownAnimationSpeed";
            this.numericUpDownAnimationSpeed.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownAnimationSpeed.TabIndex = 8;
            this.numericUpDownAnimationSpeed.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownAnimationSpeed.Leave += new System.EventHandler(this.numericUpDownAnimationSpeed_Leave);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(11, 15);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(93, 13);
            this.label9.TabIndex = 0;
            this.label9.Text = "Animation Speed :";
            // 
            // groupBoxAnimationPlayer
            // 
            this.groupBoxAnimationPlayer.Controls.Add(this.groupBoxChangeFrame);
            this.groupBoxAnimationPlayer.Controls.Add(this.PlayerReset);
            this.groupBoxAnimationPlayer.Controls.Add(this.buttonPlayerStop);
            this.groupBoxAnimationPlayer.Controls.Add(this.buttonPlayerPlay);
            this.groupBoxAnimationPlayer.Controls.Add(this.groupBoxZoom);
            this.groupBoxAnimationPlayer.Location = new System.Drawing.Point(0, 658);
            this.groupBoxAnimationPlayer.Name = "groupBoxAnimationPlayer";
            this.groupBoxAnimationPlayer.Size = new System.Drawing.Size(354, 107);
            this.groupBoxAnimationPlayer.TabIndex = 7;
            this.groupBoxAnimationPlayer.TabStop = false;
            this.groupBoxAnimationPlayer.Text = "Animation Player :";
            // 
            // groupBoxChangeFrame
            // 
            this.groupBoxChangeFrame.Controls.Add(this.buttonPlayerPrevFrame);
            this.groupBoxChangeFrame.Controls.Add(this.buttonPlayerNextFrame);
            this.groupBoxChangeFrame.Location = new System.Drawing.Point(186, 19);
            this.groupBoxChangeFrame.Name = "groupBoxChangeFrame";
            this.groupBoxChangeFrame.Size = new System.Drawing.Size(162, 46);
            this.groupBoxChangeFrame.TabIndex = 6;
            this.groupBoxChangeFrame.TabStop = false;
            this.groupBoxChangeFrame.Text = "Change Frame :";
            // 
            // buttonPlayerPrevFrame
            // 
            this.buttonPlayerPrevFrame.Location = new System.Drawing.Point(6, 17);
            this.buttonPlayerPrevFrame.Name = "buttonPlayerPrevFrame";
            this.buttonPlayerPrevFrame.Size = new System.Drawing.Size(72, 23);
            this.buttonPlayerPrevFrame.TabIndex = 5;
            this.buttonPlayerPrevFrame.Text = "Prev. Frame";
            this.buttonPlayerPrevFrame.UseVisualStyleBackColor = true;
            this.buttonPlayerPrevFrame.Click += new System.EventHandler(this.buttonPlayerPrevFrame_Click);
            // 
            // buttonPlayerNextFrame
            // 
            this.buttonPlayerNextFrame.Location = new System.Drawing.Point(84, 18);
            this.buttonPlayerNextFrame.Name = "buttonPlayerNextFrame";
            this.buttonPlayerNextFrame.Size = new System.Drawing.Size(72, 23);
            this.buttonPlayerNextFrame.TabIndex = 4;
            this.buttonPlayerNextFrame.Text = "Next Frame";
            this.buttonPlayerNextFrame.UseVisualStyleBackColor = true;
            this.buttonPlayerNextFrame.Click += new System.EventHandler(this.buttonPlayerNextFrame_Click);
            // 
            // PlayerReset
            // 
            this.PlayerReset.Location = new System.Drawing.Point(237, 71);
            this.PlayerReset.Name = "PlayerReset";
            this.PlayerReset.Size = new System.Drawing.Size(109, 23);
            this.PlayerReset.TabIndex = 3;
            this.PlayerReset.Text = "Reset";
            this.PlayerReset.UseVisualStyleBackColor = true;
            this.PlayerReset.Click += new System.EventHandler(this.PlayerReset_Click);
            // 
            // buttonPlayerStop
            // 
            this.buttonPlayerStop.Location = new System.Drawing.Point(122, 71);
            this.buttonPlayerStop.Name = "buttonPlayerStop";
            this.buttonPlayerStop.Size = new System.Drawing.Size(109, 23);
            this.buttonPlayerStop.TabIndex = 2;
            this.buttonPlayerStop.Text = "Stop";
            this.buttonPlayerStop.UseVisualStyleBackColor = true;
            this.buttonPlayerStop.Click += new System.EventHandler(this.buttonPlayerStop_Click);
            // 
            // buttonPlayerPlay
            // 
            this.buttonPlayerPlay.Location = new System.Drawing.Point(7, 71);
            this.buttonPlayerPlay.Name = "buttonPlayerPlay";
            this.buttonPlayerPlay.Size = new System.Drawing.Size(109, 23);
            this.buttonPlayerPlay.TabIndex = 1;
            this.buttonPlayerPlay.Text = "Play";
            this.buttonPlayerPlay.UseVisualStyleBackColor = true;
            this.buttonPlayerPlay.Click += new System.EventHandler(this.buttonPlayerPlay_Click);
            // 
            // groupBoxZoom
            // 
            this.groupBoxZoom.Controls.Add(this.buttonZoomOut);
            this.groupBoxZoom.Controls.Add(this.buttonZoomIn);
            this.groupBoxZoom.Location = new System.Drawing.Point(7, 19);
            this.groupBoxZoom.Name = "groupBoxZoom";
            this.groupBoxZoom.Size = new System.Drawing.Size(129, 48);
            this.groupBoxZoom.TabIndex = 0;
            this.groupBoxZoom.TabStop = false;
            this.groupBoxZoom.Text = "Zoom :";
            // 
            // buttonZoomOut
            // 
            this.buttonZoomOut.Location = new System.Drawing.Point(66, 19);
            this.buttonZoomOut.Name = "buttonZoomOut";
            this.buttonZoomOut.Size = new System.Drawing.Size(53, 23);
            this.buttonZoomOut.TabIndex = 1;
            this.buttonZoomOut.Text = "Out";
            this.buttonZoomOut.UseVisualStyleBackColor = true;
            this.buttonZoomOut.Click += new System.EventHandler(this.buttonZoomOut_Click);
            // 
            // buttonZoomIn
            // 
            this.buttonZoomIn.Location = new System.Drawing.Point(6, 19);
            this.buttonZoomIn.Name = "buttonZoomIn";
            this.buttonZoomIn.Size = new System.Drawing.Size(54, 23);
            this.buttonZoomIn.TabIndex = 0;
            this.buttonZoomIn.Text = "In";
            this.buttonZoomIn.UseVisualStyleBackColor = true;
            this.buttonZoomIn.Click += new System.EventHandler(this.buttonZoomIn_Click);
            // 
            // groupBoxEditCollisionRect
            // 
            this.groupBoxEditCollisionRect.Controls.Add(this.label12);
            this.groupBoxEditCollisionRect.Controls.Add(this.label13);
            this.groupBoxEditCollisionRect.Controls.Add(this.label14);
            this.groupBoxEditCollisionRect.Controls.Add(this.label15);
            this.groupBoxEditCollisionRect.Controls.Add(this.numericUpDownCollisionWidth);
            this.groupBoxEditCollisionRect.Controls.Add(this.numericUpDownCollisionHeight);
            this.groupBoxEditCollisionRect.Controls.Add(this.numericUpDownCollisionYPosition);
            this.groupBoxEditCollisionRect.Controls.Add(this.numericUpDownCollisionXPosition);
            this.groupBoxEditCollisionRect.Location = new System.Drawing.Point(850, 238);
            this.groupBoxEditCollisionRect.Name = "groupBoxEditCollisionRect";
            this.groupBoxEditCollisionRect.Size = new System.Drawing.Size(167, 125);
            this.groupBoxEditCollisionRect.TabIndex = 9;
            this.groupBoxEditCollisionRect.TabStop = false;
            this.groupBoxEditCollisionRect.Text = "Edit Collision Rectangle :";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(25, 103);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 13);
            this.label12.TabIndex = 7;
            this.label12.Text = "Width :";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(22, 76);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(44, 13);
            this.label13.TabIndex = 6;
            this.label13.Text = "Height :";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(7, 22);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(60, 13);
            this.label14.TabIndex = 5;
            this.label14.Text = "Y Position :";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(7, 49);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(60, 13);
            this.label15.TabIndex = 4;
            this.label15.Text = "X Position :";
            // 
            // numericUpDownCollisionWidth
            // 
            this.numericUpDownCollisionWidth.Location = new System.Drawing.Point(73, 101);
            this.numericUpDownCollisionWidth.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCollisionWidth.Name = "numericUpDownCollisionWidth";
            this.numericUpDownCollisionWidth.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCollisionWidth.TabIndex = 3;
            this.numericUpDownCollisionWidth.ValueChanged += new System.EventHandler(this.numericUpDownCollisionWidth_ValueChanged);
            // 
            // numericUpDownCollisionHeight
            // 
            this.numericUpDownCollisionHeight.Location = new System.Drawing.Point(73, 74);
            this.numericUpDownCollisionHeight.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCollisionHeight.Name = "numericUpDownCollisionHeight";
            this.numericUpDownCollisionHeight.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCollisionHeight.TabIndex = 2;
            this.numericUpDownCollisionHeight.ValueChanged += new System.EventHandler(this.numericUpDownCollisionHeight_ValueChanged);
            // 
            // numericUpDownCollisionYPosition
            // 
            this.numericUpDownCollisionYPosition.Location = new System.Drawing.Point(73, 19);
            this.numericUpDownCollisionYPosition.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCollisionYPosition.Name = "numericUpDownCollisionYPosition";
            this.numericUpDownCollisionYPosition.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCollisionYPosition.TabIndex = 1;
            this.numericUpDownCollisionYPosition.ValueChanged += new System.EventHandler(this.numericUpDownCollisionYPosition_ValueChanged);
            // 
            // numericUpDownCollisionXPosition
            // 
            this.numericUpDownCollisionXPosition.Location = new System.Drawing.Point(73, 47);
            this.numericUpDownCollisionXPosition.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownCollisionXPosition.Name = "numericUpDownCollisionXPosition";
            this.numericUpDownCollisionXPosition.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownCollisionXPosition.TabIndex = 0;
            this.numericUpDownCollisionXPosition.ValueChanged += new System.EventHandler(this.numericUpDownCollisionXPosition_ValueChanged);
            // 
            // groupBoxAllAnimations
            // 
            this.groupBoxAllAnimations.Controls.Add(this.AnimationListRemove);
            this.groupBoxAllAnimations.Controls.Add(this.DeSelect);
            this.groupBoxAllAnimations.Controls.Add(this.AnimationListAdd);
            this.groupBoxAllAnimations.Controls.Add(this.listBoxAnimations);
            this.groupBoxAllAnimations.Location = new System.Drawing.Point(360, 450);
            this.groupBoxAllAnimations.Name = "groupBoxAllAnimations";
            this.groupBoxAllAnimations.Size = new System.Drawing.Size(315, 275);
            this.groupBoxAllAnimations.TabIndex = 10;
            this.groupBoxAllAnimations.TabStop = false;
            this.groupBoxAllAnimations.Text = "Animations";
            // 
            // AnimationListRemove
            // 
            this.AnimationListRemove.Location = new System.Drawing.Point(211, 244);
            this.AnimationListRemove.Name = "AnimationListRemove";
            this.AnimationListRemove.Size = new System.Drawing.Size(96, 23);
            this.AnimationListRemove.TabIndex = 9;
            this.AnimationListRemove.Text = "Remove";
            this.AnimationListRemove.UseVisualStyleBackColor = true;
            this.AnimationListRemove.Click += new System.EventHandler(this.AnimationListRemove_Click);
            // 
            // DeSelect
            // 
            this.DeSelect.Location = new System.Drawing.Point(109, 246);
            this.DeSelect.Name = "DeSelect";
            this.DeSelect.Size = new System.Drawing.Size(96, 23);
            this.DeSelect.TabIndex = 13;
            this.DeSelect.Text = "Deselect";
            this.DeSelect.UseVisualStyleBackColor = true;
            this.DeSelect.Click += new System.EventHandler(this.DeSelect_Click);
            // 
            // AnimationListAdd
            // 
            this.AnimationListAdd.Location = new System.Drawing.Point(7, 244);
            this.AnimationListAdd.Name = "AnimationListAdd";
            this.AnimationListAdd.Size = new System.Drawing.Size(96, 23);
            this.AnimationListAdd.TabIndex = 7;
            this.AnimationListAdd.Text = "Add";
            this.AnimationListAdd.UseVisualStyleBackColor = true;
            this.AnimationListAdd.Click += new System.EventHandler(this.AnimationListAdd_Click);
            // 
            // listBoxAnimations
            // 
            this.listBoxAnimations.FormattingEnabled = true;
            this.listBoxAnimations.Location = new System.Drawing.Point(7, 19);
            this.listBoxAnimations.Name = "listBoxAnimations";
            this.listBoxAnimations.Size = new System.Drawing.Size(302, 212);
            this.listBoxAnimations.TabIndex = 0;
            this.listBoxAnimations.SelectedIndexChanged += new System.EventHandler(this.listBoxAnimations_SelectedIndexChanged);
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(0, 418);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(638, 17);
            this.hScrollBar1.TabIndex = 11;
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Location = new System.Drawing.Point(641, 27);
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(17, 388);
            this.vScrollBar1.TabIndex = 12;
            this.vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // groupBoxWeaponPoint
            // 
            this.groupBoxWeaponPoint.Controls.Add(this.label17);
            this.groupBoxWeaponPoint.Controls.Add(this.label16);
            this.groupBoxWeaponPoint.Controls.Add(this.numericUpDownWeaponPointY);
            this.groupBoxWeaponPoint.Controls.Add(this.numericUpDownWeaponPointX);
            this.groupBoxWeaponPoint.Location = new System.Drawing.Point(677, 204);
            this.groupBoxWeaponPoint.Name = "groupBoxWeaponPoint";
            this.groupBoxWeaponPoint.Size = new System.Drawing.Size(167, 72);
            this.groupBoxWeaponPoint.TabIndex = 13;
            this.groupBoxWeaponPoint.TabStop = false;
            this.groupBoxWeaponPoint.Text = "Edit Weapon Anchor Point :";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(9, 41);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(60, 13);
            this.label17.TabIndex = 2;
            this.label17.Text = "X Position :";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(9, 16);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(60, 13);
            this.label16.TabIndex = 3;
            this.label16.Text = "Y Position :";
            // 
            // numericUpDownWeaponPointY
            // 
            this.numericUpDownWeaponPointY.Location = new System.Drawing.Point(75, 13);
            this.numericUpDownWeaponPointY.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownWeaponPointY.Name = "numericUpDownWeaponPointY";
            this.numericUpDownWeaponPointY.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownWeaponPointY.TabIndex = 1;
            this.numericUpDownWeaponPointY.ValueChanged += new System.EventHandler(this.numericUpDownWeaponPointY_ValueChanged);
            // 
            // numericUpDownWeaponPointX
            // 
            this.numericUpDownWeaponPointX.Location = new System.Drawing.Point(75, 39);
            this.numericUpDownWeaponPointX.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownWeaponPointX.Name = "numericUpDownWeaponPointX";
            this.numericUpDownWeaponPointX.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownWeaponPointX.TabIndex = 0;
            this.numericUpDownWeaponPointX.ValueChanged += new System.EventHandler(this.numericUpDownWeaponPointX_ValueChanged);
            // 
            // WeaponAngleGroupBox1
            // 
            this.WeaponAngleGroupBox1.Controls.Add(this.label19);
            this.WeaponAngleGroupBox1.Controls.Add(this.label20);
            this.WeaponAngleGroupBox1.Controls.Add(this.numericUpDownWeaponPointY2);
            this.WeaponAngleGroupBox1.Controls.Add(this.numericUpDownWeaponPointX2);
            this.WeaponAngleGroupBox1.Controls.Add(this.label18);
            this.WeaponAngleGroupBox1.Controls.Add(this.numericUpDownAngle);
            this.WeaponAngleGroupBox1.Location = new System.Drawing.Point(677, 282);
            this.WeaponAngleGroupBox1.Name = "WeaponAngleGroupBox1";
            this.WeaponAngleGroupBox1.Size = new System.Drawing.Size(167, 100);
            this.WeaponAngleGroupBox1.TabIndex = 14;
            this.WeaponAngleGroupBox1.TabStop = false;
            this.WeaponAngleGroupBox1.Text = "Edit Weapon Angle :";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(9, 46);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(60, 13);
            this.label19.TabIndex = 9;
            this.label19.Text = "Y Position :";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(9, 73);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(60, 13);
            this.label20.TabIndex = 8;
            this.label20.Text = "X Position :";
            // 
            // numericUpDownWeaponPointY2
            // 
            this.numericUpDownWeaponPointY2.Location = new System.Drawing.Point(75, 44);
            this.numericUpDownWeaponPointY2.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownWeaponPointY2.Name = "numericUpDownWeaponPointY2";
            this.numericUpDownWeaponPointY2.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownWeaponPointY2.TabIndex = 7;
            this.numericUpDownWeaponPointY2.ValueChanged += new System.EventHandler(this.numericUpDownWeaponPointY2_ValueChanged);
            // 
            // numericUpDownWeaponPointX2
            // 
            this.numericUpDownWeaponPointX2.Location = new System.Drawing.Point(75, 71);
            this.numericUpDownWeaponPointX2.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownWeaponPointX2.Name = "numericUpDownWeaponPointX2";
            this.numericUpDownWeaponPointX2.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownWeaponPointX2.TabIndex = 6;
            this.numericUpDownWeaponPointX2.ValueChanged += new System.EventHandler(this.numericUpDownWeaponPointX2_ValueChanged);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(9, 16);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(40, 13);
            this.label18.TabIndex = 4;
            this.label18.Text = "Angle :";
            // 
            // numericUpDownAngle
            // 
            this.numericUpDownAngle.Enabled = false;
            this.numericUpDownAngle.Location = new System.Drawing.Point(75, 14);
            this.numericUpDownAngle.Maximum = new decimal(new int[] {
            8192,
            0,
            0,
            0});
            this.numericUpDownAngle.Name = "numericUpDownAngle";
            this.numericUpDownAngle.Size = new System.Drawing.Size(81, 20);
            this.numericUpDownAngle.TabIndex = 3;
            this.numericUpDownAngle.ValueChanged += new System.EventHandler(this.numericUpDownAngle_ValueChanged);
            // 
            // graphicsPanelPlayer
            // 
            this.graphicsPanelPlayer.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.graphicsPanelPlayer.Location = new System.Drawing.Point(0, 456);
            this.graphicsPanelPlayer.Name = "graphicsPanelPlayer";
            this.graphicsPanelPlayer.Size = new System.Drawing.Size(354, 196);
            this.graphicsPanelPlayer.TabIndex = 8;
            // 
            // MainPanel
            // 
            this.MainPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.MainPanel.Location = new System.Drawing.Point(0, 27);
            this.MainPanel.Name = "MainPanel";
            this.MainPanel.Size = new System.Drawing.Size(638, 388);
            this.MainPanel.TabIndex = 1;
            this.MainPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.MainPanel_MouseDown);
            this.MainPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MainPanel_MouseMove);
            this.MainPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.MainPanel_MouseUp);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1022, 769);
            this.Controls.Add(this.WeaponAngleGroupBox1);
            this.Controls.Add(this.groupBoxWeaponPoint);
            this.Controls.Add(this.vScrollBar1);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.groupBoxAllAnimations);
            this.Controls.Add(this.groupBoxEditCollisionRect);
            this.Controls.Add(this.graphicsPanelPlayer);
            this.Controls.Add(this.groupBoxAnimationPlayer);
            this.Controls.Add(this.groupBoxFrame);
            this.Controls.Add(this.groupBoxAnimation);
            this.Controls.Add(this.GroupBoxEditFrameRect);
            this.Controls.Add(this.GroupBoxEditAnchorPoint);
            this.Controls.Add(this.GroupBoxDraw);
            this.Controls.Add(this.MainPanel);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Animation Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.GroupBoxDraw.ResumeLayout(false);
            this.GroupBoxEditAnchorPoint.ResumeLayout(false);
            this.GroupBoxEditAnchorPoint.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCurrentPointY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCurrentPointX)).EndInit();
            this.GroupBoxEditFrameRect.ResumeLayout(false);
            this.GroupBoxEditFrameRect.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownYPosition)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownXPosition)).EndInit();
            this.groupBoxAnimation.ResumeLayout(false);
            this.groupBoxAnimation.PerformLayout();
            this.groupBoxFrame.ResumeLayout(false);
            this.groupBoxFrame.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameDuration)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAnimationSpeed)).EndInit();
            this.groupBoxAnimationPlayer.ResumeLayout(false);
            this.groupBoxChangeFrame.ResumeLayout(false);
            this.groupBoxZoom.ResumeLayout(false);
            this.groupBoxEditCollisionRect.ResumeLayout(false);
            this.groupBoxEditCollisionRect.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionYPosition)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCollisionXPosition)).EndInit();
            this.groupBoxAllAnimations.ResumeLayout(false);
            this.groupBoxWeaponPoint.ResumeLayout(false);
            this.groupBoxWeaponPoint.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointX)).EndInit();
            this.WeaponAngleGroupBox1.ResumeLayout(false);
            this.WeaponAngleGroupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointY2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWeaponPointX2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAngle)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ToolStripNew;
        private System.Windows.Forms.ToolStripMenuItem ToolStripOpenBinary;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripMenuItem ToolStripSaveXML;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem ToolStripExit;
        private System.Windows.Forms.ToolStripMenuItem toolStripOpenXML;
        private System.Windows.Forms.ToolStripMenuItem toolStripSaveBinary;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem toolStripImportAnimationImage;
        private GraphicsPanel MainPanel;
        private System.Windows.Forms.GroupBox GroupBoxDraw;
        private System.Windows.Forms.Button DrawAnchorPoint;
        private System.Windows.Forms.Button DrawCollisionRect;
        private System.Windows.Forms.Button DrawFrameRect;
        private System.Windows.Forms.GroupBox GroupBoxEditAnchorPoint;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownCurrentPointY;
        private System.Windows.Forms.NumericUpDown numericUpDownCurrentPointX;
        private System.Windows.Forms.GroupBox GroupBoxEditFrameRect;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numericUpDownWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownYPosition;
        private System.Windows.Forms.NumericUpDown numericUpDownXPosition;
        private System.Windows.Forms.GroupBox groupBoxAnimation;
        private System.Windows.Forms.Button FrameListRemove;
        private System.Windows.Forms.Button FrameListAdd;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ListBox listBoxFrames;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxAnimationName;
        private System.Windows.Forms.GroupBox groupBoxFrame;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown numericUpDownFrameDuration;
        private System.Windows.Forms.NumericUpDown numericUpDownAnimationSpeed;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox TextBoxFrameTriggerEvent;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.GroupBox groupBoxAnimationPlayer;
        private System.Windows.Forms.GroupBox groupBoxZoom;
        private System.Windows.Forms.Button buttonZoomOut;
        private System.Windows.Forms.Button buttonZoomIn;
        private System.Windows.Forms.GroupBox groupBoxChangeFrame;
        private System.Windows.Forms.Button buttonPlayerPrevFrame;
        private System.Windows.Forms.Button buttonPlayerNextFrame;
        private System.Windows.Forms.Button PlayerReset;
        private System.Windows.Forms.Button buttonPlayerStop;
        private System.Windows.Forms.Button buttonPlayerPlay;
        private System.Windows.Forms.CheckBox checkBoxOslating;
        private System.Windows.Forms.CheckBox checkBoxLooping;
        private GraphicsPanel graphicsPanelPlayer;
        private System.Windows.Forms.GroupBox groupBoxEditCollisionRect;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.NumericUpDown numericUpDownCollisionWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownCollisionHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownCollisionYPosition;
        private System.Windows.Forms.NumericUpDown numericUpDownCollisionXPosition;
        private System.Windows.Forms.GroupBox groupBoxAllAnimations;
        private System.Windows.Forms.Button AnimationListRemove;
        private System.Windows.Forms.Button AnimationListAdd;
        private System.Windows.Forms.ListBox listBoxAnimations;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.Button DeSelect;
        private System.Windows.Forms.Button DrawWeaponPoint;
        private System.Windows.Forms.GroupBox groupBoxWeaponPoint;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.NumericUpDown numericUpDownWeaponPointY;
        private System.Windows.Forms.NumericUpDown numericUpDownWeaponPointX;
        private System.Windows.Forms.Button DrawWeaponAngle;
        private System.Windows.Forms.GroupBox WeaponAngleGroupBox1;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.NumericUpDown numericUpDownAngle;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.NumericUpDown numericUpDownWeaponPointY2;
        private System.Windows.Forms.NumericUpDown numericUpDownWeaponPointX2;
    }
}

