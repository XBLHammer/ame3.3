using System;
using System.IO;

namespace Server.Helpers
{
    public class EndianReader : BinaryReader
    {
        private readonly EndianStyle endianStyle;

        public EndianReader(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.endianStyle = endianstyle;
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }

        public override short ReadInt16()
        {
            return this.ReadInt16(this.endianStyle);
        }

        public short ReadInt16(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(2);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToInt16(bytes, 0);
        }

        public override ushort ReadUInt16()
        {
            return this.ReadUInt16(this.endianStyle);
        }

        public ushort ReadUInt16(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(2);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToUInt16(bytes, 0);
        }

        public override int ReadInt32()
        {
            return this.ReadInt32(this.endianStyle);
        }

        public int ReadInt32(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(4);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToInt32(bytes, 0);
        }

        public override uint ReadUInt32()
        {
            return this.ReadUInt32(this.endianStyle);
        }

        public uint ReadUInt32(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(4);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToUInt32(bytes, 0);
        }

        public override long ReadInt64()
        {
            return this.ReadInt64(this.endianStyle);
        }

        public long ReadInt64(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(8);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToInt64(bytes, 0);
        }

        public override ulong ReadUInt64()
        {
            return this.ReadUInt64(this.endianStyle);
        }

        public ulong ReadUInt64(EndianStyle endianstyle)
        {
            byte[] bytes = base.ReadBytes(8);
            if (endianstyle == EndianStyle.BigEndian)
                Array.Reverse(bytes);

            return BitConverter.ToUInt64(bytes, 0);
        }
    }
}