using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SGP;

namespace Tile_Editor
{
    public partial class TilesetOptions : Form
    {
        //      Tileset image
        int m_imgTileset;
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

        public GraphicsNamespace.GraphicsPanel PanelPreview
        {
            get { return panelPreview; }
        }

        

        public TilesetOptions()
        {
            InitializeComponent();

            
        }

        public void Initialize(string szNameID, CTileEditor formEditor, int imgTileset, Size sizeTileset, Size sizeTile,
            Color colorTransparent, string szPath)
        {
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

            panelPreview.AutoScrollMinSize = new Size(
                    m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);

        }

        public void Render(ManagedTextureManager TM, ManagedDirect3D D3D)
        {

            Point ptOffset = Point.Empty;
            ptOffset.X += panelPreview.AutoScrollPosition.X;
            ptOffset.Y += panelPreview.AutoScrollPosition.Y;

            //e.Graphics.DrawImage(m_imgTileset, ptOffset.X, ptOffset.Y);
            TM.Draw(m_imgTileset, ptOffset.X, ptOffset.Y, 1.0f, 1.0f, Rectangle.Empty, 0, 0, 0.0f, Color.White.ToArgb());
            D3D.Sprite.Flush();

            for (int nVertIndex = 0; nVertIndex < m_sizeTileset.Height; ++nVertIndex)
            {
                for (int nHorIndex = 0; nHorIndex < m_sizeTileset.Width; ++nHorIndex)
                {
                    Point ptPosition = new Point(nHorIndex * m_sizeTile.Width + ptOffset.X,
                        nVertIndex * m_sizeTile.Height + ptOffset.Y);
                    //e.Graphics.DrawRectangle(Pens.Black, new Rectangle(ptPosition, m_sizeTile));
                    D3D.DrawEmptyRect(new Rectangle(ptPosition, m_sizeTile), Color.Black, 1.0f);
                }
            }
        }

        private void numTileWidth_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTile.Width = (int)numTileWidth.Value;
            panelPreview.AutoScrollMinSize = new Size(
                m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTileHeight_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTile.Height = (int)numTileHeight.Value;
            panelPreview.AutoScrollMinSize = new Size(
                m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTilesetWidth_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTileset.Width = (int)numTilesetWidth.Value;
            panelPreview.AutoScrollMinSize = new Size(
                m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void numTilesetHeight_ValueChanged(object sender, EventArgs e)
        {
            m_sizeTileset.Height = (int)numTilesetHeight.Value;
            panelPreview.AutoScrollMinSize = new Size(
                m_sizeTileset.Width * m_sizeTile.Width, m_sizeTileset.Height * m_sizeTile.Height);
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            //m_imgTileset.MakeTransparent(buttonTransparent.BackColor);
            m_formEditor.TilesetBitmap = m_imgTileset;
            m_formEditor.SizeTile = m_sizeTile;
            m_formEditor.SizeTileset = m_sizeTileset;
            m_formEditor.TransparentColor = buttonTransparent.BackColor;

            m_formEditor.UpdateAutoScrollSizes();

            m_formEditor.TilesetFileName = m_szFileName;
            m_formEditor.TilesetID = m_szNameID;
        }

        private void buttonImport_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgTilesetBitmap = new OpenFileDialog();
            dlgTilesetBitmap.InitialDirectory = m_szPath;


            if (DialogResult.OK == dlgTilesetBitmap.ShowDialog())
            {
                m_imgTileset = ManagedTextureManager.Instance.LoadTexture(dlgTilesetBitmap.FileName, buttonTransparent.BackColor.ToArgb());

                Graphics tilesetGraphics = panelPreview.CreateGraphics();
                //m_imgTileset.SetResolution(tilesetGraphics.DpiX, tilesetGraphics.DpiY);
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
        }

        private void textBoxNameID_TextChanged(object sender, EventArgs e)
        {
            m_szNameID = textBoxNameID.Text;
        }
    }
}
