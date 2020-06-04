using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UdpClient
{
	public partial class ClientFrom : Form
	{
		private const string ipAddr = "127.0.0.1";
		private const int datagramSize = 50004;
		private const int imagePartSize = 50000;
		private const int port = 4242;
		private static Bitmap screenShot;
		byte[] img;
		int totalBytes = 0;
		bool isRecording = false;
		public ClientFrom()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			StopSharingButton.Enabled = false;
		}

		private void StartSharingButton_Click(object sender, EventArgs e)
		{
			isRecording = true;
			StartSharingButton.Enabled = false;
			StopSharingButton.Enabled = true;
			var th = new Thread(Share);
			th.Start();
		}

		private void StopSharingButton_Click(object sender, EventArgs e)
		{
			isRecording = false;
			StartSharingButton.Enabled = true;
			StopSharingButton.Enabled = false;
		}

		private void Share()
		{
			var ip = IPAddress.Parse(ipAddr);
			var socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
			var ep = new IPEndPoint(ip, port);
			socket.SendTo(new byte[0], ep);
			isRecording = true;
			while (isRecording)
			{
				Thread.Sleep(5);
				var pos = 0;

				screenShot = new Bitmap(Screen.PrimaryScreen.Bounds.Width, 
					Screen.PrimaryScreen.Bounds.Height, 
					PixelFormat.Format32bppArgb);
				var gScreen = Graphics.FromImage(screenShot);
				gScreen.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, 
					Screen.PrimaryScreen.Bounds.Y, 0, 0,
					Screen.PrimaryScreen.Bounds.Size, 
					CopyPixelOperation.SourceCopy);
				img = CompressImage(screenShot);

				var imagePartsArray = new List<byte[]>();
				totalBytes = img.Length % datagramSize != 0 ? img.Length / datagramSize + 1 : img.Length / datagramSize;
				
				while (pos < img.Length)
				{
					byte[] bytes = (img.Length - pos) >= imagePartSize ? new byte[datagramSize] : new byte[img.Length - pos + 4];
					Array.Copy(img, pos, bytes, 0, bytes.Length - 4);
					pos += bytes.Length - 4;
					bytes[bytes.Length - 4] = (byte) totalBytes;

					imagePartsArray.Add(bytes);
				}

				foreach (var imagePart in imagePartsArray)
				{
					socket.SendTo(imagePart, ep);
					Thread.Sleep(2);
				}
			}
			socket.Close();
		}

		private byte[] CompressImage(Bitmap image)
		{
			using (var ms = new MemoryStream())
			{
				using (var gzip = new GZipStream(ms, CompressionMode.Compress))
				{
					image.Save(gzip, ImageFormat.Jpeg);
				}
				return ms.ToArray();
			}
		}
	}
}