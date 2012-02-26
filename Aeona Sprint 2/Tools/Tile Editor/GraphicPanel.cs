using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;


namespace GraphicsNamespace
{
    // Graphics Panel class
    // Used in the toolbox to make a panel that redraws when
    // resized and is double buffered
    public class GraphicsPanel : Panel
    {
        public GraphicsPanel()
        {
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            this.BackColor = Color.White;
        }
    }
}
