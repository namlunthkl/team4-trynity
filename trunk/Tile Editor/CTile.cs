using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tile_Editor
{
    class CTile
    {
        int nPosX;
        public int PosX
        {
            get { return nPosX; }
            set { nPosX = value; }
        }

        int nPosY;
        public int PosY
        {
            get { return nPosY; }
            set { nPosY = value; }
        }

        byte byteTileInfo;
        public byte TileInfo
        {
            get { return byteTileInfo; }
            set { byteTileInfo = value; }
        }

       
        string szEvent;
        public string Event
        {
            get { return szEvent; }
            set { szEvent = value; }
        }

        public CTile()
        {
            nPosX = -1;
            nPosY = -1;
            byteTileInfo = 0;
            szEvent = "none";
        }
    }

    class CLayer
    {
        //      Array of Tiles
        CTile[,] tileMap;
        internal CTile[,] TileMap
        {
            get { return tileMap; }
            set { tileMap = value; }
        }

        bool m_bVisible = true;
        public bool Visible
        {
            get { return m_bVisible; }
            set { m_bVisible = value; }
        }

        int m_nID = 0;
        public int ID
        {
            get { return m_nID; }
            set { m_nID = value; }
        }
    }

    class TilePlaced
    {
        int nPosX;
        int nPosY;

    }
}
