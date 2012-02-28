using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Animation_Editor
{
    class Frame
    {
        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        private Rectangle frameRect;
        public System.Drawing.Rectangle FrameRect
        {
            get { return frameRect; }
            set { frameRect = value; }
        }

        private Rectangle collision;
        public System.Drawing.Rectangle Collision
        {
            get { return collision; }
            set { collision = value; }
        }

        private Point anchor;
        public System.Drawing.Point Anchor
        {
            get { return anchor; }
            set { anchor = value; }
        }
        private Point weaponAnchor;
        public System.Drawing.Point WeaponAnchor
        {
            get { return weaponAnchor; }
            set { weaponAnchor = value; }
        }
        private string triggerEvent;
        public string TriggerEvent
        {
            get { return triggerEvent; }
            set { triggerEvent = value; }
        }
        private decimal frameDuration;
        public decimal FrameDuration
        {
            get { return frameDuration; }
            set { frameDuration = value; }
        }
        public override string ToString()
        {
            return name;
        }
    }
}
