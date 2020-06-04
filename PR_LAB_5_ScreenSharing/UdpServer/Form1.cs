using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UdpServer
{
	public partial class Form1 : Form
	{
		private const int datagramSize = 50004;
		private const int imagePartSize = 50000;
		private const int port = 4242;
		private Socket _socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
		private byte[] _buffer;
		public List<byte[]> imagePartsArray;
		public int bytesCount = 0;
		private static IPEndPoint ipEndPoint = new IPEndPoint(IPAddress.Any, port);
		private EndPoint ep = ipEndPoint as EndPoint;
		public Form1()
		{
			_buffer = new byte[ushort.MaxValue];
			imagePartsArray = new List<byte[]>();
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			_socket.Bind(ipEndPoint);
			_socket.BeginReceiveFrom(_buffer, 0, _buffer.Length, SocketFlags.None, ref ep,
				new AsyncCallback(RunServer), _socket);
		}

		private void RunServer(IAsyncResult ar)
		{
			while (true)
			{
				int i = 0;
				int arraysCount = -1;
				while (i != arraysCount)
				{
					var imagePartBytesWithSuffix = new byte[datagramSize];
					var n = _socket.ReceiveFrom(imagePartBytesWithSuffix, ref ep);
					bytesCount += n - 4;
					var imgPart = new byte[n - 4];
					var suffix = new byte[4];
					Array.Copy(imagePartBytesWithSuffix, n - 4, suffix, 0, 4);
					Array.Copy(imagePartBytesWithSuffix, 0, imgPart, 0, imgPart.Length);
					arraysCount = BitConverter.ToInt32(suffix, suffix.Length - 4);
					imagePartsArray.Add(imgPart);
					i++;
				}

				var fullImage = new byte[bytesCount];
				for (int j = 0; j < imagePartsArray.Count; j++)
				{
					Array.Copy(imagePartsArray[j], 0, fullImage, j * imagePartSize, imagePartsArray[j].Length);
				}

				var decompressed = DecompressImage(fullImage);

				using (var ms = new MemoryStream(decompressed))
				{
					var image = (Bitmap) Bitmap.FromStream(ms);
					pictureBox1.Image = image;
					imagePartsArray.Clear();
					bytesCount = 0;
				}
			}
		}

		private byte[] DecompressImage(byte[] image)
		{
			using (var ms = new MemoryStream(image))
			{
				using (var decMs = new MemoryStream())
				{
					using (var bs = new BufferedStream(new GZipStream(ms, CompressionMode.Decompress), 4096))
					{
						bs.CopyTo(decMs);
					}
					return decMs.ToArray();
				}
			}
		}

		private void pictureBox1_Click(object sender, EventArgs e)
		{

		}
	}
}