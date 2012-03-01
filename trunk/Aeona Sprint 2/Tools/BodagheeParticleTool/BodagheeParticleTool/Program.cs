using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace BodagheeParticleTool
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());

            //Make the form
            Form1 theForm = new Form1();

            //Display the form
            theForm.Show();

            while (theForm.Looping)
            {
                theForm.Update();
                theForm.Render();
                Application.DoEvents();
            }
        }
    }
}
