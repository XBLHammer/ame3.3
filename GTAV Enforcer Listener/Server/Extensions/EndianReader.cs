using System;
using System.IO;
using System.Text;

namespace Server.Extensions
{
    class EndianReader : BinaryReader
    {
        private readonly EndianStyle EndianStyle;

        public EndianReader(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.EndianStyle = endianstyle;
        }

        public override float ReadSingle()
        {
            return this.ReadSingle(this.EndianStyle);
        }

        public float ReadSingle(EndianStyle endianstyle)
        {
            byte[] Buffer = base.ReadBytes(0x04);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            return BitConverter.ToSingle(Buffer, 0);
        }

        public override double ReadDouble()
        {
            return this.ReadDouble(this.EndianStyle);
        }

        public double ReadDouble(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x08);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToDouble(buffer, 0);
        }

        public override short ReadInt16()
        {
            return this.ReadInt16(this.EndianStyle);
        }

        public short ReadInt16(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x02);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToInt16(buffer, 0);
        }

        public int ReadInt24()
        {
            return this.ReadInt24(this.EndianStyle);
        }

        public int ReadInt24(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x03);
            if (endianstyle == EndianStyle.BigEndian)
            {
                return (((buffer[0] << 0x10) | (buffer[1] << 8)) | buffer[2]);
            }
            return (((buffer[2] << 0x10) | (buffer[1] << 8)) | buffer[0]);
        }

        public override int ReadInt32()
        {
            return this.ReadInt32(this.EndianStyle);
        }

        public int ReadInt32(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x04);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToInt32(buffer, 0);
        }

        public override long ReadInt64()
        {
            return this.ReadInt64(this.EndianStyle);
        }

        public long ReadInt64(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x08);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToInt64(buffer, 0);
        }

        public override ushort ReadUInt16()
        {
            return this.ReadUInt16(this.EndianStyle);
        }

        public ushort ReadUInt16(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(2);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToUInt16(buffer, 0);
        }

        public override uint ReadUInt32()
        {
            return this.ReadUInt32(this.EndianStyle);
        }

        public uint ReadUInt32(EndianStyle endianstyle)
        {
            byte[] buffer = base.ReadBytes(0x04);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            return BitConverter.ToUInt32(buffer, 0);
        }

        public override ulong ReadUInt64()
        {
            return this.ReadUInt64(this.EndianStyle);
        }

        public ulong ReadUInt64(EndianStyle endianstyle)
        {
            byte[] Buffer = base.ReadBytes(0x08);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            return BitConverter.ToUInt64(Buffer, 0);
        }

        public string ReadStringNullTerminated()
        {
            string str = string.Empty;
            while (true)
            {
                byte num = this.ReadByte();
                if (num == 0)
                {
                    return str;
                }
                str = str + ((char)num);
            }
        }

        public string ReadUnicodeString(int Length)
        {
            return this.ReadUnicodeString(Length, this.EndianStyle);
        }

        public string ReadUnicodeString(int length, EndianStyle endianstyle)
        {
            string str = string.Empty;
            int num = 0;
            for (int i = 0; i < length; i++)
            {
                ushort num3 = this.ReadUInt16(endianstyle);
                num++;
                if (num3 == 0)
                {
                    break;
                }
                str = str + ((char)num3);
            }
            int num4 = (length - num) * 2;
            this.BaseStream.Seek((long)num4, SeekOrigin.Current);
            return str;
        }

        public string ReadUnicodeNullTermString()
        {
            string str = string.Empty;
            while (true)
            {
                ushort num = this.ReadUInt16(EndianStyle.BigEndian);
                if (num == 0)
                {
                    return str;
                }
                str = str + ((char)num);
            }
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }

        public uint SeekNReed(long address)
        {
            base.BaseStream.Position = address;
            return this.ReadUInt32();
        }
    }
}