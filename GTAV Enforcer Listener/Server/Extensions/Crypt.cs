using System;
using System.Threading;
using System.Security;
using System.Security.Cryptography;

namespace Server.Extensions
{
    class Crypt
    {
        public static byte[] CSHA(byte[] data)
        {
            SHA1 SHA = SHA1.Create();
            SHA.Initialize();
            SHA.TransformFinalBlock(data, 0, data.Length);
            return SHA.Hash;
        }

        public static void CRC4(ref byte[] data, byte[] key)
        {
            byte num;
            int num2;
            byte[] buffer = new byte[0x100];
            byte[] buffer2 = new byte[0x100];
            for (num2 = 0; num2 < 0x100; num2++)
            {
                buffer[num2] = (byte)num2;
                buffer2[num2] = key[num2 % key.GetLength(0)];
            }
            int index = 0;
            for (num2 = 0; num2 < 0x100; num2++)
            {
                index = ((index + buffer[num2]) + buffer2[num2]) % 0x100;
                num = buffer[num2];
                buffer[num2] = buffer[index];
                buffer[index] = num;
            }
            num2 = index = 0;
            for (int i = 0; i < data.GetLength(0); i++)
            {
                num2 = (num2 + 1) % 0x100;
                index = (index + buffer[num2]) % 0x100;
                num = buffer[num2];
                buffer[num2] = buffer[index];
                buffer[index] = num;
                int num5 = (buffer[num2] + buffer[index]) % 0x100;
                data[i] = (byte)(data[i] ^ buffer[num5]);
            }
        }

        public static byte[] Random(int count)
        {
            Random random = new Random(0x2048);
            Random random2 = new Random(0x4096);
            Random random3 = new Random(0x8196);
            Random random4 = new Random(0xFFFF);
            byte[] buffer = new byte[count];
            byte[] buffer2 = new byte[count];
            byte[] buffer3 = new byte[count];
            byte[] buffer4 = new byte[count];
            byte[] buffer5 = new byte[count];
            for (int a = 0; a < 10; a++)
            {
                random.NextBytes(buffer2);
                random.NextBytes(buffer3);
                random.NextBytes(buffer4);
                random.NextBytes(buffer5);
                Thread.Sleep(1);
                random = new Random(Environment.TickCount + 0x1024);
                Thread.Sleep(1);
                random = new Random(Environment.TickCount + 0x2048);
                Thread.Sleep(1);
                random = new Random(Environment.TickCount + 0x4096);
                Thread.Sleep(1);
                random = new Random(Environment.TickCount + 0x8192);
                for (int b = 0; b < count; b++)
                {
                    buffer[b] = (byte)(buffer[b] ^ buffer2[b] + 1);
                    buffer[b] = (byte)(buffer[b] ^ buffer3[b] + 2);
                    buffer[b] = (byte)(buffer[b] ^ buffer4[b] + 3);
                    buffer[b] = (byte)(buffer[b] ^ buffer5[b] + 3);
                    byte[] bytes = BitConverter.GetBytes(Environment.TickCount);
                    buffer[b] = (byte)(buffer[b] ^ bytes[0] + 2);
                    buffer[b] = (byte)(buffer[b] ^ bytes[1] + 1);
                    buffer[b] = (byte)(buffer[b] ^ bytes[2] + 1);
                    buffer[b] = (byte)(buffer[b] ^ bytes[3] + 2);
                    buffer[b] = (byte)(buffer[b] ^ bytes[3] + 3);
                    buffer[b] = (byte)(buffer[b] ^ bytes[2] + 3);
                    buffer[b] = (byte)(buffer[b] ^ bytes[1] + 2);
                    buffer[b] = (byte)(buffer[b] ^ bytes[0] + 1);
                }
            }
            return buffer;
        }
    }
}