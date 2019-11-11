using System;
using System.IO;

namespace Server.Helpers
{
    public class EndianWriter : BinaryWriter
    {
        private readonly EndianStyle endianStyle;

        public EndianWriter(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.endianStyle = endianstyle;
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }

        public override void Write(float value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(double value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(short value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(ushort value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(int value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(uint value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(long value)
        {
            this.Write(value, this.endianStyle);
        }

        public override void Write(ulong value)
        {
            this.Write(value, this.endianStyle);
        }

        public void Write(float value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(double value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(short value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(ushort value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(int value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(uint value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(long value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }

        public void Write(ulong value, EndianStyle endianstyle)
        {
            byte[] bytes = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            base.Write(bytes);
        }
    }
}