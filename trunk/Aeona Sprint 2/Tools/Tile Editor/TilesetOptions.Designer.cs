namespace Tile_Editor
{
    partial class TilesetOptions
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
            this.buttonSave = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.panelPreview = new GraphicsNamespace.GraphicsPanel();
            this.buttonTransparent = new System.Windows.Forms.Button();
            this.buttonImport = new System.Windows.Forms.Button();
            this.groupBoxTile = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.numTileHeight = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.numTileWidth = new System.Windows.Forms.NumericUpDown();
            this.groupBoxTileset = new System.Windows.Forms.GroupBox();
            this.textBoxNameID = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.numTilesetHeight = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numTilesetWidth = new System.Windows.Forms.NumericUpDown();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBoxTile.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTileHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTileWidth)).BeginInit();
            this.groupBoxTileset.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTilesetHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTilesetWidth)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(243, 249);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(218, 33);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "Apply";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.buttonTransparent);
            this.groupBox1.Controls.Add(this.buttonImport);
            this.groupBox1.Location = new System.Drawing.Point(9, 7);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(218, 275);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Image";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.panelPreview);
            this.groupBox2.Location = new System.Drawing.Point(20, 100);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(180, 169);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Preview";
            // 
            // panelPreview
            // 
            this.panelPreview.BackColor = System.Drawing.Color.White;
            this.panelPreview.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelPreview.Location = new System.Drawing.Point(3, 18);
            this.panelPreview.Name = "panelPreview";
            this.panelPreview.Size = new System.Drawing.Size(174, 148);
            this.panelPreview.TabIndex = 0;
            // 
            // buttonTransparent
            // 
            this.buttonTransparent.Location = new System.Drawing.Point(20, 62);
            this.buttonTransparent.Name = "buttonTransparent";
            this.buttonTransparent.Size = new System.Drawing.Size(180, 30);
            this.buttonTransparent.TabIndex = 1;
            this.buttonTransparent.Text = "Transparent Color";
            this.buttonTransparent.UseVisualStyleBackColor = true;
            this.buttonTransparent.Click += new System.EventHandler(this.buttonTransparent_Click);
            // 
            // buttonImport
            // 
            this.buttonImport.Location = new System.Drawing.Point(20, 26);
            this.buttonImport.Name = "buttonImport";
            this.buttonImport.Size = new System.Drawing.Size(180, 30);
            this.buttonImport.TabIndex = 0;
            this.buttonImport.Text = "Import Image";
            this.buttonImport.UseVisualStyleBackColor = true;
            this.buttonImport.Click += new System.EventHandler(this.buttonImport_Click);
            // 
            // groupBoxTile
            // 
            this.groupBoxTile.Controls.Add(this.label8);
            this.groupBoxTile.Controls.Add(this.label7);
            this.groupBoxTile.Controls.Add(this.label3);
            this.groupBoxTile.Controls.Add(this.numTileHeight);
            this.groupBoxTile.Controls.Add(this.label4);
            this.groupBoxTile.Controls.Add(this.numTileWidth);
            this.groupBoxTile.Location = new System.Drawing.Point(243, 145);
            this.groupBoxTile.Name = "groupBoxTile";
            this.groupBoxTile.Size = new System.Drawing.Size(218, 98);
            this.groupBoxTile.TabIndex = 1;
            this.groupBoxTile.TabStop = false;
            this.groupBoxTile.Text = "Single Tile";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(166, 62);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(43, 17);
            this.label8.TabIndex = 3;
            this.label8.Text = "pixels";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(166, 28);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(43, 17);
            this.label7.TabIndex = 3;
            this.label7.Text = "pixels";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 17);
            this.label3.TabIndex = 1;
            this.label3.Text = "Width:";
            // 
            // numTileHeight
            // 
            this.numTileHeight.Location = new System.Drawing.Point(90, 60);
            this.numTileHeight.Name = "numTileHeight";
            this.numTileHeight.Size = new System.Drawing.Size(70, 22);
            this.numTileHeight.TabIndex = 6;
            this.numTileHeight.ValueChanged += new System.EventHandler(this.numTileHeight_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 62);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 17);
            this.label4.TabIndex = 1;
            this.label4.Text = "Height:";
            // 
            // numTileWidth
            // 
            this.numTileWidth.Location = new System.Drawing.Point(90, 26);
            this.numTileWidth.Name = "numTileWidth";
            this.numTileWidth.Size = new System.Drawing.Size(70, 22);
            this.numTileWidth.TabIndex = 5;
            this.numTileWidth.ValueChanged += new System.EventHandler(this.numTileWidth_ValueChanged);
            // 
            // groupBoxTileset
            // 
            this.groupBoxTileset.Controls.Add(this.textBoxNameID);
            this.groupBoxTileset.Controls.Add(this.label9);
            this.groupBoxTileset.Controls.Add(this.label6);
            this.groupBoxTileset.Controls.Add(this.label5);
            this.groupBoxTileset.Controls.Add(this.label1);
            this.groupBoxTileset.Controls.Add(this.numTilesetHeight);
            this.groupBoxTileset.Controls.Add(this.label2);
            this.groupBoxTileset.Controls.Add(this.numTilesetWidth);
            this.groupBoxTileset.Location = new System.Drawing.Point(243, 7);
            this.groupBoxTileset.Name = "groupBoxTileset";
            this.groupBoxTileset.Size = new System.Drawing.Size(218, 132);
            this.groupBoxTileset.TabIndex = 0;
            this.groupBoxTileset.TabStop = false;
            this.groupBoxTileset.Text = "Tileset";
            // 
            // textBoxNameID
            // 
            this.textBoxNameID.Location = new System.Drawing.Point(90, 97);
            this.textBoxNameID.Name = "textBoxNameID";
            this.textBoxNameID.Size = new System.Drawing.Size(110, 22);
            this.textBoxNameID.TabIndex = 4;
            this.textBoxNameID.TextChanged += new System.EventHandler(this.textBoxNameID_TextChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(20, 100);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(66, 17);
            this.label9.TabIndex = 4;
            this.label9.Text = "Name ID:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(167, 62);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 17);
            this.label6.TabIndex = 3;
            this.label6.Text = "tiles";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(167, 28);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 17);
            this.label5.TabIndex = 3;
            this.label5.Text = "tiles";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Width:";
            // 
            // numTilesetHeight
            // 
            this.numTilesetHeight.Location = new System.Drawing.Point(90, 60);
            this.numTilesetHeight.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numTilesetHeight.Name = "numTilesetHeight";
            this.numTilesetHeight.Size = new System.Drawing.Size(70, 22);
            this.numTilesetHeight.TabIndex = 3;
            this.numTilesetHeight.ValueChanged += new System.EventHandler(this.numTilesetHeight_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Height:";
            // 
            // numTilesetWidth
            // 
            this.numTilesetWidth.Location = new System.Drawing.Point(90, 26);
            this.numTilesetWidth.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numTilesetWidth.Name = "numTilesetWidth";
            this.numTilesetWidth.Size = new System.Drawing.Size(70, 22);
            this.numTilesetWidth.TabIndex = 2;
            this.numTilesetWidth.ValueChanged += new System.EventHandler(this.numTilesetWidth_ValueChanged);
            // 
            // TilesetOptions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(470, 289);
            this.ControlBox = false;
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBoxTile);
            this.Controls.Add(this.groupBoxTileset);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TilesetOptions";
            this.Text = "TilesetOptions";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBoxTile.ResumeLayout(false);
            this.groupBoxTile.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTileHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTileWidth)).EndInit();
            this.groupBoxTileset.ResumeLayout(false);
            this.groupBoxTileset.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTilesetHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTilesetWidth)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private GraphicsNamespace.GraphicsPanel panelPreview;
        private System.Windows.Forms.Button buttonTransparent;
        private System.Windows.Forms.Button buttonImport;
        private System.Windows.Forms.GroupBox groupBoxTile;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numTileHeight;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numTileWidth;
        private System.Windows.Forms.GroupBox groupBoxTileset;
        private System.Windows.Forms.TextBox textBoxNameID;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numTilesetHeight;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numTilesetWidth;
    }
}