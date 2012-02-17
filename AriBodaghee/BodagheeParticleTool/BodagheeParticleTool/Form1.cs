using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BodagheeParticleTool
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void pictureBoxEndingColor_Click(object sender, EventArgs e)
        {

        }
        private void changeBackgroundColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog backGroundColor = new ColorDialog();
            backGroundColor.Color = pictureBoxViewer.BackColor;
            if (DialogResult.OK == backGroundColor.ShowDialog())
            {
                pictureBoxViewer.BackColor = backGroundColor.Color;
            }
        }
        private void buttonCustomStartingColor_Click(object sender, EventArgs e)
        {
            ColorDialog drawColor = new ColorDialog();
            Color var = new Color();
            //drawColor.Color = pictureBoxStartingColor.BackColor;
            if ( DialogResult.OK == drawColor.ShowDialog() )
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
            pictureBoxStartingColor.BackColor = Color.FromArgb( (int)numericUpDownStartingAlpha.Value, (int)numericUpDownStartingRed.Value, (int)numericUpDownStartingGreen.Value, (int)numericUpDownStartingBlue.Value);
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
            pictureBoxStartingColor.BackColor = Color.FromArgb( trackBarStartingAlpha.Value, trackBarStartingRed.Value, trackBarStartingGreen.Value, trackBarStartingBlue.Value);
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
    }
}
