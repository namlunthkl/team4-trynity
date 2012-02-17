using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Animation_Editor
{
    class SpriteSheet
    {
        public SpriteSheet(string FilePath)
        {
            this.filepath = FilePath;
            sheet = new Bitmap(FilePath);
        }

        public string filepath;
        public string Filepath
        {
            get { return filepath; }
            set { filepath = value; }
        }
        public Bitmap sheet;
        public System.Drawing.Bitmap Sheet
        {
            get { return sheet; }
            set { sheet = value; }
        }
    }
}
