////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTileEditor.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 10:00 PM
//    Purpose				:	To handle all behavior of the Tile
//                              Editor form
////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using GraphicsNamespace;
using System.Drawing.Imaging;
using System.Xml.Linq;
using SGP;

namespace Tile_Editor
{
    public partial class CTileEditor : Form
    {
        //////////////////////////////////////////////////////////////////////////
        //	------------------------------------------------------------------	//
        //							DATA	MEMBERS								//
        //	------------------------------------------------------------------	//
        //////////////////////////////////////////////////////////////////////////

        // Is the form running?
        bool m_bRunning;
        public bool IsRunning
        {
            get { return m_bRunning; }
            set { m_bRunning = value; }
        }

        // D3D Variables
        ManagedDirect3D D3D = ManagedDirect3D.Instance;
        ManagedTextureManager TM = ManagedTextureManager.Instance;

        //  Tileset info
        //      Options Tool Window
        TilesetOptions m_toolTileset = null;
        public TilesetOptions ToolTileset
        {
            get { return m_toolTileset; }
            set { m_toolTileset = value; }
        }
        //      Tileset source file
        string m_szTilesetFileName;
        public string TilesetFileName
        {
            get { return m_szTilesetFileName; }
            set { m_szTilesetFileName = value; }
        }
        //      Tileset image
        int m_imgTileset;
        public int TilesetBitmap
        {
            get { return m_imgTileset; }
            set { m_imgTileset = value; }
        }
        //      Tileset size in number of tiles
        Size m_sizeTileset;
        public Size SizeTileset
        {
            get { return m_sizeTileset; }
            set { m_sizeTileset = value; }
        }

        //      Single tile size in pixels
        Size m_sizeTile;
        public Size SizeTile
        {
            get { return m_sizeTile; }
            set { m_sizeTile = value; }
        }

        //      Transparent Color
        Color m_colorTransparent;
        public Color TransparentColor
        {
            get { return m_colorTransparent; }
            set { m_colorTransparent = value; }
        }
        //      Name ID
        string m_szTilesetNameID;
        public string TilesetID
        {
            get { return m_szTilesetNameID; }
            set { m_szTilesetNameID = value; }
        }

        //      Selected tile in the tileset, position
        //      in number of tiles
        Point m_ptSelectedOnTileset;
        //      For multi select
        Rectangle m_rectMultiSelected;
        bool m_bSelectingRect;

        //  Map Info
        //      Array of layers
        List<CLayer> m_listLayers;
        //      Map size, in tiles
        Size m_sizeMap;
        //      Selected tile in the map, position
        Point m_ptSelectedOnMap;
        //      Used so user can paint a lot of tiles by holding
        //      the mouse's left button
        bool m_bMousePainting;

        //  Other
        //      Clipboard 
        CTile m_tileClipboard;
        //      Relative file path
        string m_szPath = "";

        //////////////////////////////////////////////////////////////////////////
        //	------------------------------------------------------------------	//
        //					    	    FUNCTIONS		    					//
        //	------------------------------------------------------------------	//
        //////////////////////////////////////////////////////////////////////////

        //  Constructor
        public CTileEditor()
        {
            // Initialize the window
            InitializeComponent();

            // Window is running...
            m_bRunning = true;

            // Create the tileset tool
            m_toolTileset = new TilesetOptions();
            m_toolTileset.FormClosed += new FormClosedEventHandler(toolTileset_FormClosed);

            // Initialize Direct3D and Texture Manager so we
            // can draw stuff to the screen
            D3D.InitManagedDirect3D(mapPanel);
            D3D.InitManagedDirect3D(tilesetPanel);
            D3D.InitManagedDirect3D(m_toolTileset.PanelPreview);
            TM.InitManagedTextureManager(D3D.Device, D3D.Sprite);

            // Create the layers array
            m_listLayers = new List<CLayer>();

            // Get the map size
            m_sizeMap = new Size(10, 10);

            //  Create the map with the right size for all layers
            // Initialize the layer
            CLayer firstLayer = new CLayer();

            // Initialize the layer's tilemap
            firstLayer.TileMap = new CTile[m_sizeMap.Width, m_sizeMap.Height];
            for (int nHorIndex = 0; nHorIndex < m_sizeMap.Width; nHorIndex++)
            {
                for (int nVertIndex = 0; nVertIndex < m_sizeMap.Height; nVertIndex++)
                {
                    // Calling new CTile() will 
                    firstLayer.TileMap[nHorIndex, nVertIndex] = new CTile();

                    // First layer should be initialized to basic ground tiles, that
                    // are usually in (0,0) position in the tileset
                    firstLayer.TileMap[nHorIndex, nVertIndex].PosX = 0;
                    firstLayer.TileMap[nHorIndex, nVertIndex].PosY = 0;
                }
            }

            // Add the first layer to the layer list
            m_listLayers.Add(firstLayer);
            checkBoxVisible.Checked = firstLayer.Visible;

            // Init all variables to default values
            InitVariables();

            // Initialize the tool and show it
            m_toolTileset.Initialize(m_szTilesetNameID, this, m_imgTileset,
                   m_sizeTileset, m_sizeTile, m_colorTransparent, m_szPath);
            m_toolTileset.Show(this);

            // Set the path variable to what is saved in the settings
            m_szPath = Properties.Settings.Default.Path;


            // If a map was saved the last time the editor was used, open it
            if (Properties.Settings.Default.LastMapSaved != "New")
                OpenMap(Properties.Settings.Default.LastMapSaved);
            if (Properties.Settings.Default.LastTilesetSaved != "New")
                LoadTileset(Properties.Settings.Default.LastTilesetSaved);

        }

        public void Render()
        {
            D3D.ChangeDisplayParam(tilesetPanel);
            {
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);

                RenderTileset();

                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
            }

            D3D.ChangeDisplayParam(mapPanel);
            {
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);

                RenderMap();

                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
            }

            D3D.ChangeDisplayParam(m_toolTileset.PanelPreview);
            {
                D3D.DeviceBegin();
                D3D.SpriteBegin();
                D3D.Clear(Color.White);

                m_toolTileset.Render(TM, D3D);

                D3D.SpriteEnd();
                D3D.DeviceEnd();
                D3D.Present();
            }
        }


        void RenderMap()
        {
            // 0. Get the scroll bars offsets
            Point ptOffset = Point.Empty;
            // ptOffset.X += mapPanel.AutoScrollPosition.X;
            // ptOffset.Y += mapPanel.AutoScrollPosition.Y;
            ptOffset.X -= hScrollBarMap.Value;
            ptOffset.Y -= vScrollBarMap.Value;

            for (int nLayerIndex = 0; nLayerIndex < tabLayers.TabCount; ++nLayerIndex)
            {
                // If this layer isn't visible, skip the painting code
                if (m_listLayers[nLayerIndex].Visible == false)
                    continue;

                Color colDraw = Color.White;
                if (tabLayers.SelectedIndex != nLayerIndex && checkBoxTransparency.Checked == true)
                {
                    colDraw = Color.FromArgb(80, colDraw);
                }

                // Loop through the map
                for (int nHorIndex = 0; nHorIndex < m_sizeMap.Width; nHorIndex++)
                {
                    for (int nVertIndex = 0; nVertIndex < m_sizeMap.Height; nVertIndex++)
                    {
                        // Get current tile
                        CTile curTile = m_listLayers[nLayerIndex].TileMap[nHorIndex, nVertIndex];

                        // Get the destination and source rects based on tile data
                        Point ptPosition = new Point(
                            nHorIndex * m_sizeTile.Width + ptOffset.X,
                            nVertIndex * m_sizeTile.Height + ptOffset.Y);

                        Rectangle rSource = new Rectangle(curTile.PosX * m_sizeTile.Width,
                            curTile.PosY * m_sizeTile.Height, m_sizeTile.Width, m_sizeTile.Height);

                        // Draw a section of the tileset
                        if (curTile.PosX != -1 && curTile.PosY != -1)
                        {
                            // Imaging attributes
                            // e.Graphics.DrawImage(TilesetBitmap, rDestination, rSource, GraphicsUnit.Pixel);
                            TM.Draw(m_imgTileset, ptPosition.X, ptPosition.Y, 1.0f, 1.0f, rSource, 0, 0, 0.0f, colDraw.ToArgb());
                            D3D.Sprite.Flush();
                        }
                        // If "View IDs" is selected, draw IDs for all tiles
                        if (checkViewIDs.Checked)
                        {
                            string szID = curTile.TileID.ToString();
                            // e.Graphics.DrawString(szID, SystemFonts.DefaultFont, Brushes.Black, ptPosition);
                            D3D.DrawText(szID, ptPosition.X, ptPosition.Y, Color.Black);
                        }
                        // If "View Grid" is selected, draw grid using the offset
                        if (checkViewGrid.Checked)
                            // e.Graphics.DrawEmptyRectangle(Pens.Black, new Rectangle(ptPosition, SizeTile));
                            D3D.DrawEmptyRect(new Rectangle(ptPosition, SizeTile), Color.Black);
                    }
                }
            }

            // 4. Mark the selected tile with a thick rectangle
            if (checkViewGrid.Checked)
            {
                Point ptSelectedPosition = new Point(
                    m_ptSelectedOnMap.X * m_sizeTile.Width + ptOffset.X,
                    m_ptSelectedOnMap.Y * m_sizeTile.Height + ptOffset.Y);

                // e.Graphics.DrawEmptyRectangle(new Pen(Color.Black, 3.0f), new Rectangle(ptSelectedPosition, SizeTile));
                D3D.DrawEmptyRect(new Rectangle(ptSelectedPosition, SizeTile), Color.Red);
            }
        }

        //  Recreates the map with the size gotten from the UI
        void RecreateMap(object sender, EventArgs e)
        {
            //  Update sizeMap variable
            m_sizeMap = new Size((int)numMapWidth.Value, (int)numMapHeight.Value);

            //  Recreate maps
            for (int nLayerIndex = 0; nLayerIndex < tabLayers.TabCount; nLayerIndex++)
            {
                //      Create a temporary variable for the new map
                CTile[,] tempMap = new CTile[m_sizeMap.Width, m_sizeMap.Height];
                //      Loop through the new map
                for (int nHorIndex = 0; nHorIndex < m_sizeMap.Width; nHorIndex++)
                {
                    for (int nVertIndex = 0; nVertIndex < m_sizeMap.Height; nVertIndex++)
                    {
                        // If there was a tile in this position in the old map, copy it
                        if (nHorIndex < m_listLayers[nLayerIndex].TileMap.GetLength(0) && nVertIndex < m_listLayers[nLayerIndex].TileMap.GetLength(1))
                            tempMap[nHorIndex, nVertIndex] = m_listLayers[nLayerIndex].TileMap[nHorIndex, nVertIndex];
                        // Else, initialize it
                        else
                            tempMap[nHorIndex, nVertIndex] = new CTile();
                    }
                }
                //      Set the tile map variable to be the new map
                m_listLayers[nLayerIndex].TileMap = tempMap;

                //  Update autoscroll min size
                UpdateAutoScrollSizes();
            }

        }

        public void UpdateAutoScrollSizes()
        {
            hScrollBarMap.Maximum = m_sizeMap.Width * m_sizeTile.Width;
            vScrollBarMap.Maximum = m_sizeMap.Height * m_sizeTile.Height;

            hScrollBarTileset.Maximum = m_sizeTileset.Width * m_sizeTile.Width;
            vScrollBarTileset.Maximum = m_sizeTileset.Height * m_sizeTile.Height;
        }


        //  Renders the tileset with a grid to the Tileset Panel
        void RenderTileset()
        {
            // 0. Get the scroll bars offsets
            Point ptOffset = Point.Empty;
            // ptOffset.X += tilesetPanel.AutoScrollPosition.X;
            // ptOffset.Y += tilesetPanel.AutoScrollPosition.Y;
            ptOffset.X -= hScrollBarTileset.Value;
            ptOffset.Y -= vScrollBarTileset.Value;

            // 1. Draw the tileset image using the offset
            // e.Graphics.DrawImage(TilesetBitmap, ptOffset);
            TM.Draw(m_imgTileset, ptOffset.X, ptOffset.Y, 1.0f, 1.0f, Rectangle.Empty, 0, 0, 0.0f, Color.White.ToArgb());
            D3D.Sprite.Flush();

            // 2. Draw the grid using the offset
            for (int nVertIndex = 0; nVertIndex < SizeTileset.Height; ++nVertIndex)
            {
                for (int nHorIndex = 0; nHorIndex < SizeTileset.Width; ++nHorIndex)
                {
                    Point ptPosition = new Point(
                        nHorIndex * m_sizeTile.Width + ptOffset.X,
                        nVertIndex * m_sizeTile.Height + ptOffset.Y);

                    // e.Graphics.DrawEmptyRectangle(Pens.Black, new Rectangle(ptPosition, SizeTile));
                    D3D.DrawEmptyRect(new Rectangle(ptPosition, SizeTile), Color.Black);
                    
                }
            }

            // 3. Mark the selected tile with a thick rectangle
            Point ptSelectedPosition = new Point(
                m_rectMultiSelected.X + ptOffset.X,
                m_rectMultiSelected.Y + ptOffset.Y);

            // e.Graphics.DrawEmptyRectangle(new Pen(Color.White, 3.0f), new Rectangle(ptSelectedPosition, m_rectMultiSelected.Size));
            D3D.DrawEmptyRect(new Rectangle(ptSelectedPosition, m_rectMultiSelected.Size), Color.White);
        }


        private void mapPanel_MouseClick(object sender, MouseEventArgs e)
        {
            // Mouse scroll bars offset
            Point ptOffset = e.Location;
            //ptOffset.X -= mapPanel.AutoScrollPosition.X;
            //ptOffset.Y -= mapPanel.AutoScrollPosition.Y;
            ptOffset.X += hScrollBarMap.Value;
            ptOffset.Y += vScrollBarMap.Value;

            // Paint scroll bars offsets
            Point ptPaintOffset = Point.Empty;
            //ptPaintOffset.X += mapPanel.AutoScrollPosition.X;
            //ptPaintOffset.Y += mapPanel.AutoScrollPosition.Y;
            ptPaintOffset.X -= hScrollBarMap.Value;
            ptPaintOffset.Y -= vScrollBarMap.Value;

            if (ptOffset.X >= 0 && ptOffset.X < m_sizeMap.Width * SizeTile.Width
                   && ptOffset.Y >= 0 && ptOffset.Y < m_sizeMap.Height * SizeTile.Height)
            {
                // If the left button was pressed, draw
                if (e.Button == System.Windows.Forms.MouseButtons.Left)
                {
                    if (tabLayers.SelectedIndex != -1)
                    {
                        int HorIndex = ptOffset.X / SizeTile.Width;
                        int VertIndex = ptOffset.Y / SizeTile.Height;

                        Point ptSelectedOnTileset = new Point();
                        ptSelectedOnTileset.X = m_rectMultiSelected.X / SizeTile.Width;
                        ptSelectedOnTileset.Y = m_rectMultiSelected.Y / SizeTile.Height;

                        for (int i = m_rectMultiSelected.Left; i < m_rectMultiSelected.Right; i += SizeTile.Width)
                        {
                            for (int j = m_rectMultiSelected.Top; j < m_rectMultiSelected.Bottom; j += SizeTile.Height)
                            {
                                int DifferenceX = (m_rectMultiSelected.Right - i) / SizeTile.Width - 1;
                                int DifferenceY = (m_rectMultiSelected.Bottom - j) / SizeTile.Height - 1;

                                if (HorIndex + DifferenceX < m_sizeMap.Width && VertIndex + DifferenceY < m_sizeMap.Height)
                                {
                                    CTile selectedTile = m_listLayers[tabLayers.SelectedIndex].TileMap[HorIndex + DifferenceX, VertIndex + DifferenceY];

                                    selectedTile.PosX = ptSelectedOnTileset.X + DifferenceX;
                                    selectedTile.PosY = ptSelectedOnTileset.Y + DifferenceY;

                                    m_listLayers[tabLayers.SelectedIndex].TileMap[HorIndex + DifferenceX, VertIndex + DifferenceY] = selectedTile;

                                }
                            }
                        }
                    }
                }
                // If the right button was pressed, select
                if (e.Button == System.Windows.Forms.MouseButtons.Right)
                {
                    if (tabLayers.SelectedIndex != -1)
                    {
                        m_ptSelectedOnMap.X = ptOffset.X / SizeTile.Width;
                        m_ptSelectedOnMap.Y = ptOffset.Y / SizeTile.Height;

                        CTile curTile = m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y];

                        textBoxEvent.Text = curTile.Event;
                        //comboBoxType.SelectedIndex = curTile.TileID;

                    }
                }
            }
        }

        private void mapPanel_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                m_bMousePainting = true;
            }
        }

        private void mapPanel_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                m_bMousePainting = false;
            }
        }

        private void mapPanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_bMousePainting == true)
            {
                // Mouse scroll bars offset
                Point ptOffset = e.Location;
                //ptOffset.X -= mapPanel.AutoScrollPosition.X;
                //ptOffset.Y -= mapPanel.AutoScrollPosition.Y;
                ptOffset.X += hScrollBarMap.Value;
                ptOffset.Y += vScrollBarMap.Value;

                // Paint scroll bars offsets
                Point ptPaintOffset = Point.Empty;
                //ptPaintOffset.X += mapPanel.AutoScrollPosition.X;
                //ptPaintOffset.Y += mapPanel.AutoScrollPosition.Y;
                ptPaintOffset.X -= hScrollBarMap.Value;
                ptPaintOffset.Y -= vScrollBarMap.Value;

                if (ptOffset.X >= 0 && ptOffset.X < m_sizeMap.Width * SizeTile.Width
                   && ptOffset.Y >= 0 && ptOffset.Y < m_sizeMap.Height * SizeTile.Height)
                {
                    if (tabLayers.SelectedIndex != -1)
                    {
                        int HorIndex = ptOffset.X / SizeTile.Width;
                        int VertIndex = ptOffset.Y / SizeTile.Height;

                        CTile selectedTile = m_listLayers[tabLayers.SelectedIndex].TileMap[HorIndex, VertIndex];

                        Point ptSelectedOnTileset = new Point();
                        ptSelectedOnTileset.X = m_rectMultiSelected.X / SizeTile.Width;
                        ptSelectedOnTileset.Y = m_rectMultiSelected.Y / SizeTile.Height;

                        selectedTile.PosX = ptSelectedOnTileset.X;
                        selectedTile.PosY = ptSelectedOnTileset.Y;

                        m_listLayers[tabLayers.SelectedIndex].TileMap[HorIndex, VertIndex] = selectedTile;

                    }
                }
            }

        }

        private void textEvent_TextChanged(object sender, EventArgs e)
        {
            m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y].Event = textBoxEvent.Text;
        }

        private void copyToolStripButton_Click(object sender, EventArgs e)
        {
            m_tileClipboard = m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y];
        }

        private void pasteToolStripButton_Click(object sender, EventArgs e)
        {
            // Paint scroll bars offsets
            Point ptPaintOffset = Point.Empty;
            // ptPaintOffset.X += mapPanel.AutoScrollPosition.X;
            // ptPaintOffset.Y += mapPanel.AutoScrollPosition.Y;
            ptPaintOffset.X -= hScrollBarMap.Value;
            ptPaintOffset.Y -= vScrollBarMap.Value;


            m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y] = m_tileClipboard;

        }

        private void cutToolStripButton_Click(object sender, EventArgs e)
        {
            // Paint scroll bars offsets
            Point ptPaintOffset = Point.Empty;
            // ptPaintOffset.X += mapPanel.AutoScrollPosition.X;
            // ptPaintOffset.Y += mapPanel.AutoScrollPosition.Y;
            ptPaintOffset.X -= hScrollBarMap.Value;
            ptPaintOffset.Y -= vScrollBarMap.Value;

            m_tileClipboard = m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y];
            m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y] = new CTile();

        }

        private void deleteToopStripButton_Click(object sender, EventArgs e)
        {
            // Paint scroll bars offsets
            Point ptPaintOffset = Point.Empty;
            // ptPaintOffset.X += mapPanel.AutoScrollPosition.X;
            // ptPaintOffset.Y += mapPanel.AutoScrollPosition.Y;
            ptPaintOffset.X -= hScrollBarMap.Value;
            ptPaintOffset.Y -= vScrollBarMap.Value;

            m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y] = new CTile();

        }

        private void newLayerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TabPage tabNew = new TabPage();
            tabNew.Name = "tabLayer" + tabLayers.TabCount;
            tabNew.Text = "Layer " + tabLayers.TabCount;

            tabLayers.TabPages.Add(tabNew);

            CLayer newLayer = new CLayer();

            newLayer.TileMap = new CTile[m_sizeMap.Width, m_sizeMap.Height];
            for (int nHorIndex = 0; nHorIndex < newLayer.TileMap.GetLength(0); nHorIndex++)
            {
                for (int nVertIndex = 0; nVertIndex < newLayer.TileMap.GetLength(1); nVertIndex++)
                {
                    newLayer.TileMap[nHorIndex, nVertIndex] = new CTile();
                }
            }

            m_listLayers.Add(newLayer);
        }

        private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        private void toolTileset_FormClosed(object sender, EventArgs e)
        {
            m_toolTileset = null;
        }

        private void tabLayers_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (tabLayers.SelectedIndex != -1)
            {
                checkBoxVisible.Checked = m_listLayers[tabLayers.SelectedIndex].Visible;
            }
        }

        private void checkBoxVisible_CheckedChanged(object sender, EventArgs e)
        {
            if (tabLayers.SelectedIndex != -1)
            {
                m_listLayers[tabLayers.SelectedIndex].Visible = checkBoxVisible.Checked;
            }
        }

        private void deleteLayerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (tabLayers.SelectedIndex != -1)
            {
                m_listLayers.RemoveAt(tabLayers.SelectedIndex);
                tabLayers.TabPages.RemoveAt(tabLayers.SelectedIndex);
            }
        }




        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSaveFile = new SaveFileDialog();
            dlgSaveFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgSaveFile.FilterIndex = 2;
            dlgSaveFile.DefaultExt = "xml";
            dlgSaveFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgSaveFile.ShowDialog())
            {
                //  Root
                XElement xRoot = new XElement("Root");
                //      Tileset name
                XAttribute attrTilesetName = new XAttribute("tileset", TilesetID);
                xRoot.Add(attrTilesetName);

                //  Map
                XElement xMap = new XElement("Map");
                xRoot.Add(xMap);
                //      X Position - posX
                XAttribute attrPosX = new XAttribute("posX", (int)mapPosX.Value);
                //      Y Position - posY
                XAttribute attrPosY = new XAttribute("posY", (int)mapPosY.Value);
                //      Map Width - width
                XAttribute attrWidth = new XAttribute("width", m_sizeMap.Width);
                //      Map Height - height
                XAttribute attrHeight = new XAttribute("height", m_sizeMap.Height);
                //  Add attributes
                xMap.Add(attrPosX);
                xMap.Add(attrPosY);
                xMap.Add(attrWidth);
                xMap.Add(attrHeight);


                //  Every Layer
                for (int nLayerIndex = 0; nLayerIndex < tabLayers.TabCount; nLayerIndex++)
                {
                    XElement xLayer = new XElement("Layer");
                    xMap.Add(xLayer);

                    //  Every Tile

                    for (int nVertIndex = 0; nVertIndex < m_sizeMap.Height; nVertIndex++)
                    {
                        for (int nHorIndex = 0; nHorIndex < m_sizeMap.Width; nHorIndex++)
                        {
                            XElement xTile = new XElement("Tile");
                            xLayer.Add(xTile);

                            // Get current tile
                            CTile curTile = m_listLayers[nLayerIndex].TileMap[nHorIndex, nVertIndex];

                            //      X Position - PosX
                            XAttribute attrTilePosX = new XAttribute("PosX", curTile.PosX);
                            //      Y Position - PosY
                            XAttribute attrTilePosY = new XAttribute("PosY", curTile.PosY);
                            //      ID Type - Type
                            XAttribute attrIDType = new XAttribute("Type", curTile.TileID);
                            //      Event String - Event
                            XAttribute attrEventString = new XAttribute("Event", curTile.Event);
                            //  Add attributes
                            xTile.Add(attrTilePosX);
                            xTile.Add(attrTilePosY);
                            xTile.Add(attrIDType);
                            xTile.Add(attrEventString);
                        }
                    }
                }


                xRoot.Save(dlgSaveFile.FileName);

                Properties.Settings.Default.LastMapSaved = dlgSaveFile.FileName;

                DialogResult SaveTileset = MessageBox.Show("Do you want to save the tileset too?", "Save", MessageBoxButtons.YesNo);
                if (SaveTileset == DialogResult.Yes)
                    exportToolStripMenuItem_Click(sender, e);
            }
        }


        private void openToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgOpenFile.FilterIndex = 2;
            dlgOpenFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgOpenFile.ShowDialog())
            {
                OpenMap(dlgOpenFile.FileName);

                DialogResult OpenTileset = MessageBox.Show("Do you want to open the tileset too?", "Open", MessageBoxButtons.YesNo);
                if (OpenTileset == DialogResult.Yes)
                    importToolStripMenuItem_Click(sender, e);
            }
        }

        void OpenMap(string szFilename)
        {
            // Clean up our variables
            m_listLayers.Clear();


            //  Root
            XElement xRoot = XElement.Load(szFilename);

            //  Map
            XElement xMap = xRoot.Element("Map");

            //      X Position - posX
            XAttribute attrPosX = xMap.Attribute("posX");
            //      Y Position - posY
            XAttribute attrPosY = xMap.Attribute("posY");
            //      Map Width - width
            XAttribute attrWidth = xMap.Attribute("width");
            //      Map Height - height
            XAttribute attrHeight = xMap.Attribute("height");
            //  Add attributes
            mapPosX.Value = int.Parse(attrPosX.Value);
            mapPosY.Value = int.Parse(attrPosY.Value);
            m_sizeMap.Width = int.Parse(attrWidth.Value);
            m_sizeMap.Height = int.Parse(attrHeight.Value);

            //  Get All Layers
            IEnumerable<XElement> xLayers = xMap.Elements("Layer");

            foreach (XElement xLayer in xLayers)
            {
                // Create a layer
                CLayer curLayer = new CLayer();
                curLayer.TileMap = new CTile[m_sizeMap.Width, m_sizeMap.Height];

                int nHorIndex = 0;
                int nVertIndex = 0;

                // Get all tiles
                IEnumerable<XElement> xTiles = xLayer.Elements("Tile");

                foreach (XElement xTile in xTiles)
                {
                    CTile curTile = new CTile();

                    //      X Position - PosX
                    XAttribute attrTilePosX = xTile.Attribute("PosX");
                    //      Y Position - PosY
                    XAttribute attrTilePosY = xTile.Attribute("PosY");
                    //      ID Type - Type
                    XAttribute attrIDType = xTile.Attribute("Type");
                    //      Event String - Event
                    XAttribute attrEventString = xTile.Attribute("Event");
                    //  Add attributes
                    curTile.PosX = int.Parse(attrTilePosX.Value);
                    curTile.PosY = int.Parse(attrTilePosY.Value);
                    curTile.TileID = int.Parse(attrIDType.Value);
                    curTile.Event = attrEventString.Value;

                    curLayer.TileMap[nHorIndex, nVertIndex] = curTile;

                    nHorIndex++;
                    if (nHorIndex >= m_sizeMap.Width)
                    {
                        nHorIndex = 0;
                        nVertIndex++;
                    }
                }

                m_listLayers.Add(curLayer);
            }


            UpdateAutoScrollSizes();
            ResetInterface();


        }

        // Export the tileset
        private void exportToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSaveFile = new SaveFileDialog();
            dlgSaveFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgSaveFile.FilterIndex = 2;
            dlgSaveFile.DefaultExt = "xml";
            dlgSaveFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgSaveFile.ShowDialog())
            {
                //  Root
                XElement xRoot = new XElement("Tileset");

                //      Tileset Width - width
                XAttribute attrWidth = new XAttribute("width", SizeTileset.Width);
                //      Tileset Height - height
                XAttribute attrHeight = new XAttribute("height", SizeTileset.Height);
                //      Single Tile Width - tilewidth
                XAttribute attrTileWidth = new XAttribute("tilewidth", SizeTile.Width);
                //      Single Tile Height - tileheight
                XAttribute attrTileHeight = new XAttribute("tileheight", SizeTile.Height);
                //      Image File - image
                XAttribute attrImageFile = new XAttribute("image", TilesetFileName);
                //      Transparent Color - transparent
                XAttribute attrTransparentColor = new XAttribute("transparent", TransparentColor.ToArgb());
                //      Tileset Name - id
                XAttribute attrTilesetName = new XAttribute("id", TilesetID);

                //  Add attributes
                xRoot.Add(attrWidth);
                xRoot.Add(attrHeight);
                xRoot.Add(attrTileWidth);
                xRoot.Add(attrTileHeight);
                xRoot.Add(attrImageFile);
                xRoot.Add(attrTransparentColor);
                xRoot.Add(attrTilesetName);

                xRoot.Save(dlgSaveFile.FileName);

                Properties.Settings.Default.LastTilesetSaved = dlgSaveFile.FileName;
            }
        }

        // Import the tileset
        private void importToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.Filter = "All Files|*.*|XML Files|*.xml";
            dlgOpenFile.FilterIndex = 2;
            dlgOpenFile.InitialDirectory = m_szPath;

            if (DialogResult.OK == dlgOpenFile.ShowDialog())
            {
                LoadTileset(dlgOpenFile.FileName);

            }

        }

        void LoadTileset(string szFilename)
        {
            //  Root
            XElement xRoot = XElement.Load(szFilename);

            //      Tileset Width - width
            XAttribute attrWidth = xRoot.Attribute("width");
            //      Tileset Height - height
            XAttribute attrHeight = xRoot.Attribute("height");
            //      Single Tile Width - tilewidth
            XAttribute attrTileWidth = xRoot.Attribute("tilewidth");
            //      Single Tile Height - tileheight
            XAttribute attrTileHeight = xRoot.Attribute("tileheight");
            //      Image File - image
            XAttribute attrImageFile = xRoot.Attribute("image");
            //      Transparent Color - transparent
            XAttribute attrTransparentColor = xRoot.Attribute("transparent");
            //      Tileset Name - id
            XAttribute attrTilesetName = xRoot.Attribute("id");

            // Set attributes
            m_sizeTileset.Width = int.Parse(attrWidth.Value);
            m_sizeTileset.Height = int.Parse(attrHeight.Value);
            m_sizeTile.Width = int.Parse(attrTileWidth.Value);
            m_sizeTile.Height = int.Parse(attrTileHeight.Value);
            TilesetFileName = attrImageFile.Value;
            TransparentColor = Color.FromArgb(int.Parse(attrTransparentColor.Value));
            TilesetID = attrTilesetName.Value;

            TilesetBitmap = TM.LoadTexture(TilesetFileName, TransparentColor.ToArgb());
            UpdateAutoScrollSizes();

        }

        private void newToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            m_listLayers.Clear();

            // Get the map size
            m_sizeMap = new Size(10, 10);

            //  Create the map with the right size for all layers
            // Initialize the layer
            CLayer firstLayer = new CLayer();

            // Initialize the layer's tilemap
            firstLayer.TileMap = new CTile[m_sizeMap.Width, m_sizeMap.Height];
            for (int nHorIndex = 0; nHorIndex < m_sizeMap.Width; nHorIndex++)
            {
                for (int nVertIndex = 0; nVertIndex < m_sizeMap.Height; nVertIndex++)
                {
                    // Calling new CTile() will 
                    firstLayer.TileMap[nHorIndex, nVertIndex] = new CTile();

                    // First layer should be initialized to basic ground tiles, that
                    // are usually in (0,0) position in the tileset
                    firstLayer.TileMap[nHorIndex, nVertIndex].PosX = 0;
                    firstLayer.TileMap[nHorIndex, nVertIndex].PosY = 0;
                }
            }

            m_listLayers.Add(firstLayer);

            checkBoxVisible.Checked = firstLayer.Visible;

            InitVariables();

            ResetInterface();

        }


        void InitVariables()
        {
            //  Default values for variables
            mapPosX.Value = 0;
            mapPosY.Value = 0;
            m_imgTileset = TM.LoadTexture("C:/Users/Daniel Lima/Desktop/TRINITY/Tools/Lima's Tile Editor/Resources/Default.png", Color.White.ToArgb());
            SizeTileset = new Size(9, 8);
            SizeTile = new Size(32, 32);
            m_ptSelectedOnTileset = new Point(0, 0);
            m_bMousePainting = false;
            m_szTilesetFileName = "C:/Users/Daniel Lima/Desktop/TRINITY/Tools/Lima's Tile Editor/Resources/Default.png";
            m_colorTransparent = Color.White;
            m_szTilesetNameID = "untitled";
            m_rectMultiSelected = new Rectangle();
            m_bSelectingRect = false;

            //  For scroll bars
            Graphics tilesetGraphics = tilesetPanel.CreateGraphics();
            //TilesetBitmap.SetResolution(tilesetGraphics.DpiX, tilesetGraphics.DpiY);
            UpdateAutoScrollSizes();
        }

        void ResetInterface()
        {

            int nWidth = m_sizeMap.Width;
            int nHeight = m_sizeMap.Height;

            numMapWidth.Value = nWidth;
            numMapHeight.Value = nHeight;

            tabLayers.TabPages.Clear();

            for (int uiIndexLayer = 0; uiIndexLayer < m_listLayers.Count(); ++uiIndexLayer)
            {
                TabPage tabNew = new TabPage();
                tabNew.Name = "tabLayer" + tabLayers.TabCount;
                tabNew.Text = "Layer " + tabLayers.TabCount;

                tabLayers.TabPages.Add(tabNew);
            }
        }

        private void setPathToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlgFolderBrowser = new FolderBrowserDialog();

            if (DialogResult.OK == dlgFolderBrowser.ShowDialog(this))
            {
                m_szPath = dlgFolderBrowser.SelectedPath;
                Properties.Settings.Default.Path = m_szPath;

                Properties.Settings.Default.Save();
            }
        }

        private void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            //m_listLayers[tabLayers.SelectedIndex].TileMap[m_ptSelectedOnMap.X, m_ptSelectedOnMap.Y].TileID = comboBoxType.SelectedIndex;
        }

        private void tilesetPanel_MouseDown(object sender, MouseEventArgs e)
        {
            // Mouse scroll bars offset
            Point ptOffset = e.Location;
            // ptOffset.X = ptOffset.X - tilesetPanel.AutoScrollPosition.X;
            // ptOffset.Y = ptOffset.Y - tilesetPanel.AutoScrollPosition.Y;
            ptOffset.X += hScrollBarTileset.Value;
            ptOffset.Y += vScrollBarTileset.Value;
            ptOffset.X -= ptOffset.X % SizeTile.Width;
            ptOffset.Y -= ptOffset.Y % SizeTile.Height;

            m_bSelectingRect = true;

            m_rectMultiSelected = new Rectangle();
            m_rectMultiSelected.Location = ptOffset;
        }


        private void tilesetPanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_bSelectingRect == true)
            {
                // Mouse scroll bars offset
                Point ptOffset = e.Location;
                // ptOffset.X = ptOffset.X - tilesetPanel.AutoScrollPosition.X + SizeTile.Width;
                // ptOffset.Y = ptOffset.Y - tilesetPanel.AutoScrollPosition.Y + SizeTile.Height;
                ptOffset.X = ptOffset.X + hScrollBarTileset.Value + SizeTile.Width;
                ptOffset.Y = ptOffset.Y + vScrollBarTileset.Value + SizeTile.Height;
                ptOffset.X -= ptOffset.X % SizeTile.Width;
                ptOffset.Y -= ptOffset.Y % SizeTile.Height;

                m_rectMultiSelected.Size = new Size(ptOffset.X - m_rectMultiSelected.Left,
                    ptOffset.Y - m_rectMultiSelected.Top);
            }
        }

        private void tilesetPanel_MouseUp(object sender, MouseEventArgs e)
        {
            // Mouse scroll bars offset
            Point ptOffset = e.Location;
            // ptOffset.X = ptOffset.X - tilesetPanel.AutoScrollPosition.X + SizeTile.Width;
            // ptOffset.Y = ptOffset.Y - tilesetPanel.AutoScrollPosition.Y + SizeTile.Height;
            ptOffset.X = ptOffset.X + hScrollBarTileset.Value + SizeTile.Width;
            ptOffset.Y = ptOffset.Y + vScrollBarTileset.Value + SizeTile.Height;
            ptOffset.X -= ptOffset.X % SizeTile.Width;
            ptOffset.Y -= ptOffset.Y % SizeTile.Height;

            m_bSelectingRect = false;

            m_rectMultiSelected.Size = new Size(ptOffset.X - m_rectMultiSelected.Left,
                ptOffset.Y - m_rectMultiSelected.Top);
        }

        private void CTileEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            Properties.Settings.Default.Save();

            if (TM != null)
            {
                TM.ShutdownManagedTextureManager();
                TM = null;
            }

            if (D3D != null)
            {
                D3D.Shutdown();
                D3D = null;
            }

            m_bRunning = false;
        }


    }
}
