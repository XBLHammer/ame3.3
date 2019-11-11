using System;
using System.IO;
using System.Text;

namespace Server.Extensions
{
    public class EndianWriter : BinaryWriter
    {
        private readonly EndianStyle EndianStyle;

        public EndianWriter(Stream stream, EndianStyle endianstyle)
            : base(stream)
        {
            this.EndianStyle = endianstyle;
        }

        public void Seek(long position)
        {
            base.BaseStream.Position = position;
        }

        public void SeekNWrite(long position, int value)
        {
            base.BaseStream.Position = position;
            base.Write(value);
        }

        public override void Write(double value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(float value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(int value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(short value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(long value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(uint Value)
        {
            this.Write(Value, this.EndianStyle);
        }

        public override void Write(ushort value)
        {
            this.Write(value, this.EndianStyle);
        }

        public override void Write(ulong value)
        {
            this.Write(value, this.EndianStyle);
        }

        public void Write(float value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            base.Write(buffer);
        }

        public void Write(int value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            base.Write(buffer);
        }

        public void Write(short value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            base.Write(buffer);
        }

        public void Write(double value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            base.Write(buffer);
        }

        public void Write(long value, EndianStyle endianstyle)
        {
            byte[] buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(buffer);
            }
            base.Write(buffer);
        }

        public void Write(ushort value, EndianStyle endianstyle)
        {
            byte[] Buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            base.Write(Buffer);
        }

        public void Write(uint value, EndianStyle endianstyle)
        {
            byte[] Buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            base.Write(Buffer);
        }

        public void Write(ulong value, EndianStyle endianstyle)
        {
            byte[] Buffer = BitConverter.GetBytes(value);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            base.Write(Buffer);
        }

        public void WriteInt24(int Value)
        {
            this.WriteInt24(Value, this.EndianStyle);
        }

        public void WriteInt24(int value, EndianStyle endianstyle)
        {
            byte[] Buffer = BitConverter.GetBytes(value);
            Array.Resize<byte>(ref Buffer, 3);
            if (endianstyle == EndianStyle.BigEndian)
            {
                Array.Reverse(Buffer);
            }
            base.Write(Buffer);
        }

        public void WriteString(string value)
        {
            char[] Buffer = value.ToCharArray();
            base.Write(Buffer);
        }

        public void WriteUnicodeString(string value)
        {
            byte[] Buffer = Encoding.BigEndianUnicode.GetBytes(value);
            base.Write(Buffer);
            base.Write(new byte[2]);
        }

        public void WriteUnicodeString(string str, int length)
        {
            this.WriteUnicodeString(str, length, this.EndianStyle);
        }

        public void WriteUnicodeString(string str, int length, EndianStyle endianstyle)
        {
            int num = str.Length;
            for (int i = 0; i < num; i++)
            {
                if (i > length)
                {
                    break;
                }
                ushort num2 = str[i];
                this.Write(num2, endianstyle);
            }
            int num3 = (length - num) * 2;
            if (num3 > 0)
            {
                this.Write(new byte[num3]);
            }
        }
    }
}