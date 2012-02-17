using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Limas_Tile_Editor
{
    public partial class TilesetOptions : Form
    {
        //      Tileset image
        Bitmap m_imgTileset;
        //      Tileset size in number of tiles
        Size m_sizeTileset;
        //      Single tile size in pixels
        Size m_sizeTile;
        //      Reference to the tile editor window
        CTileEditor m_formEditor;
        //      Tileset File Name
        string m_szFileName = "C:/Users/Daniel Lima/Desktop/TRINITY/Tools/Lima's Tile Editor/Resources/Default.png";   // TODO: Change to default tileset location
        //      Tileset Name ID
        string m_szNameID = "untitled";
        string m_szPath = "";

        public TilesetOptions(string szNameID, CTileEditor formEditor, Bitmap imgTileset, Size sizeTileset, Size sizeTile,
            Color colorTransparent, string szPath)
        {
            InitializeComponent();

            // Initialize all variables to the passed parameters
            m_formEditor = formEditor;
            m_imgTileset = imgTileset;
            m_sizeTileset = sizeTileset;
            m_sizeTile = sizeTile;
            m_szNameID = szNameID;
            buttonTransparent.BackColor = colorTransparent;
            m_szPath = szPath;

            numTilesetWidth.Value = sizeTileset.Width;
            numTilesetHeight.Value = sizeTileset.Height;
            numTileWidth.Value = sizeTile.Width;
            numTileHeight.Value = sizeTile.Height;
            textBoxNameID.Text = szNameID;

            Graphics tilesetGraphics = panelPreview.CreateGraphics();
            m_imgTileset.SetResolution(tilesetGraphics.DpiX, tilesetGraphics.DpiY);
            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void panelPreview_Paint(object sender, PaintEventArgs e)
        {
            Point ptOffset = Point.Empty;
            ptOffset.X += panelPreview.AutoScrollPosition.X;
            ptOffset.Y += panelPreview.AutoScrollPosition.Y;

            e.Graphics.DrawImage(m_imgTileset, ptOffset.X, ptOffset.Y);

            for (int nVertIndex = 0; nVertIndex < m_sizeTileset.Height; ++nVertIndex)
            {
                for (int nHorIndex = 0; nHorIndex < m_sizeTileset.Width; ++nHorIndex)
                {
                    Point ptPosition = new Point(nHorIndex * m_sizeTile.Width + ptOffset.X,
                        nVertIndex * m_sizeTile.Height + ptOffset.Y);
                    e.Graphics.DrawRectangle(Pens.Black, new Rectangle(ptPosition, m_sizeTile));
                }
            }
        }

        private void numTileWidth_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTile.Width = (int)numTileWidth.Value;
            panelPreview.Invalidate();
            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTileHeight_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTile.Height = (int)numTileHeight.Value;
            panelPreview.Invalidate();
            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTilesetWidth_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTileset.Width = (int)numTilesetWidth.Value;
            panelPreview.Invalidate();
            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTilesetHeight_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTileset.Height = (int)numTilesetHeight.Value;
            panelPreview.Invalidate();
            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            m_imgTileset.MakeTransparent(buttonTransparent.BackColor);
            m_formEditor.TilesetBitmap = m_imgTileset;
            m_formEditor.SizeTile = m_sizeTile;
            m_formEditor.SizeTileset = m_sizeTileset;
            m_formEditor.TransparentColor = buttonTransparent.BackColor;

            m_formEditor.UpdateAutoScrollSizes();

            m_formEditor.TilesetFileName = m_szFileName;
            m_formEditor.TilesetID = m_szNameID;

            m_formEditor.InvalidateMap(sender, e);
            m_formEditor.InvalidateTileset(sender, e);

            this.Close();
        }

        private void buttonImport_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgTilesetBitmap = new OpenFileDialog();
            dlgTilesetBitmap.InitialDirectory = m_szPath;


            if (DialogResult.OK == dlgTilesetBitmap.ShowDialog())
            {
                m_imgTileset = new Bitmap(dlgTilesetBitmap.FileName);
                
                Graphics tilesetGraphics = panelPreview.CreateGraphics();
                m_imgTileset.SetResolution(tilesetGraphics.DpiX, tilesetGraphics.DpiY);
                panelPreview.AutoScrollMinSize = new Size(
                        m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);

                m_szFileName = dlgTilesetBitmap.FileName;

                panelPreview.Invalidate();
            }
        }

        private void buttonTransparent_Click(object sender, EventArgs e)
        {
            ColorDialog dlgTransparentColor = new ColorDialog();

            dlgTransparentColor.Color = buttonTransparent.BackColor;

            if (DialogResult.OK == dlgTransparentColor.ShowDialog())
            {
                buttonTransparent.BackColor = dlgTransparentColor.Color;
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBoxNameID_TextChanged(object sender, EventArgs e)
        {
            m_szNameID = textBoxNameID.Text;
        }
    }
}
