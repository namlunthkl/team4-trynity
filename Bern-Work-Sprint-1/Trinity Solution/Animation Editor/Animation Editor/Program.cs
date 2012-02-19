using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Animation_Editor
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
            Form1 theform = new Form1();

            //Display the form
            theform.Show();
            
            while (theform.Looping)
            {

                theform.Update();

                theform.Render();

                Application.DoEvents();
            }
        }
    }
}
