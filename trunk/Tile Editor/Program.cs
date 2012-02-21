using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Tile_Editor
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
            // Application.Run(new Form1());

            // Make the form
            CTileEditor formEditor = new CTileEditor();

            // Display the form
            formEditor.Show();

            // Start the main program loop
            while (formEditor.IsRunning)
            {
                // Call our form's Update function
                formEditor.Update();

                if (formEditor.ToolTileset != null)
                    formEditor.ToolTileset.Update();

                // Call our form's Render function
                formEditor.Render();

                // Handle events
                Application.DoEvents();
            }
        }
    }
}
