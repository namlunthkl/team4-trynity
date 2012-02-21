using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace Animation_Editor
{
    class Animation
    {
        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        private bool looping;
        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }
        private bool oslating;
        public bool Oslating
        {
            get { return oslating; }
            set { oslating = value; }
        }

        private bool playing;
        public bool Playing
        {
            get { return playing; }
            set { playing = value; }
        }
        private decimal speed;
        public decimal Speed
        {
            get { return speed; }
            set { speed = value; }
        }
        private int numFrames;
        public int NumFrames
        {
            get { return numFrames; }
            set { numFrames = value; }
        }
        private BindingList<Frame> frames;
        public BindingList<Frame> Frames
        {
            get { return frames; }
            set { frames = value; }
        }
        public override string ToString()
        {
            return name;
        }
    }
}
