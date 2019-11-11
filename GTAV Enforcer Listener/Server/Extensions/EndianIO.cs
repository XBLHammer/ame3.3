using System;
using System.IO;

namespace Server.Extensions
{
    class EndianIO
    {
        private readonly EndianStyle EndianStyle;
        private readonly string FilePath;
        private readonly bool isFile;

        public EndianIO(Stream stream, EndianStyle endianstyle)
        {
            this.FilePath = string.Empty;
            this.EndianStyle = EndianStyle.LittleEndian;
            this.EndianStyle = endianstyle;
            this.Stream = stream;
            this.isFile = false;
            this.Open();
        }

        public EndianIO(string filepath, EndianStyle endianstyle)
        {
            this.FilePath = string.Empty;
            this.EndianStyle = EndianStyle.LittleEndian;
            this.EndianStyle = endianstyle;
            this.FilePath = filepath;
            this.isFile = true;
            this.Open();
        }

        public EndianIO(byte[] buffer, EndianStyle endianstyle)
        {
            this.FilePath = string.Empty;
            this.EndianStyle = EndianStyle.LittleEndian;
            this.EndianStyle = endianstyle;
            this.Stream = new MemoryStream(buffer);
            this.isFile = false;
            this.Open();
        }

        public EndianIO(string filepath, EndianStyle endianstyle, FileMode filemode)
        {
            this.FilePath = string.Empty;
            this.EndianStyle = EndianStyle.LittleEndian;
            this.EndianStyle = endianstyle;
            this.FilePath = filepath;
            this.isFile = true;
            this.Open(filemode);
        }

        public void Open()
        {
            this.Open(FileMode.Open);
        }

        public void Open(FileMode filemode)
        {
            if (!this.Opened)
            {
                if (this.isFile)
                {
                    this.Stream = new FileStream(this.FilePath, filemode, FileAccess.ReadWrite);
                }
                this.Reader = new EndianReader(Stream, EndianStyle);
                this.Writer = new EndianWriter(Stream, EndianStyle);
                this.Opened = true;
            }
        }

        public void Close()
        {
            if (this.Opened)
            {
                this.Stream.Close();
                this.Reader.Close();
                this.Writer.Close();
                this.Opened = false;
            }
        }

        public byte[] ToArray()
        {
            return ((MemoryStream)this.Stream).ToArray();
        }

        public bool Opened
        {
            get;
            set;
        }

        public long Position
        {
            get
            {
                return this.Stream.Position;
            }
            set
            {
                this.Stream.Position = value;
            }
        }

        public Stream Stream
        {
            get;
            set;
        }

        public EndianReader Reader
        {
            get;
            set;
        }

        public EndianWriter Writer
        {
            get;
            set;
        }
    }
}