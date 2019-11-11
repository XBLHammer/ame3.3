using System;
using System.IO;

namespace Server.Extensions
{
    internal class SecureStream : Stream
    {
        public Stream Stream;
        public SecureStream(Stream stream)
        {
            this.Stream = stream;
        }

        public override void Flush()
        {
            this.Stream.Flush();
        }

        public override void SetLength(long value)
        {
            this.Stream.SetLength(value);
        }

        public override long Seek(long offset, SeekOrigin seekorigin)
        {
            return this.Stream.Seek(offset, seekorigin);
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            byte[] buffer2 = new byte[count];
            int num = this.Stream.Read(buffer2, 0, count);
            while (num != count)
            {
                int num2 = this.Stream.Read(buffer2, num, count - num);
                if (num2 <= 0)
                {
                    break;
                }
                num += num2;
            }
            Buffer.BlockCopy(buffer2, 0, buffer, offset, num);
            return num;
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            byte[] destination = new byte[count];
            Buffer.BlockCopy(buffer, offset, destination, 0, count);
            this.Stream.Write(destination, 0, count);
        }

        public override long Length
        {
            get
            {
                return this.Stream.Length;
            }
        }

        public override long Position
        {
            get
            {
                return this.Stream.Position;
            }
            set
            {
                this.Stream.Position = this.Position;
            }
        }

        public override bool CanSeek
        {
            get
            {
                return this.Stream.CanSeek;
            }
        }

        public override bool CanRead
        {
            get
            {
                return this.Stream.CanRead;
            }
        }

        public override bool CanWrite
        {
            get
            {
                return this.Stream.CanWrite;
            }
        }
    }
}