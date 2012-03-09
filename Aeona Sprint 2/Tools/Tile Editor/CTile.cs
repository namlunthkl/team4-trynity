using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tile_Editor
{
    public enum ETileByte
    {
        BIT_TILE_COLLISION = 0, BIT_EVENT_ANY_COLLISION,
        BIT_EVENT_PLAYER_COLLISION, BIT_EVENT_ACTION_BUTTON,
        BIT_EVENT_BASIC_ATTACK, BIT_EVENT_FIRE_BLADE,
        BIT_EVENT_EARTH_HAMMER, BIT_EVENT_AIR_CROSSBOW
    };

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
            szEvent = "";
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
}
