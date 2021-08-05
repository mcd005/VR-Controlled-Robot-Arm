using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using UnityEngine;

// using System.Net.Sockets.dll;

namespace CommsManagerSpace
{

    public class CommsManager
    {
        #region private members
        /// <summary>
        /// TCPListener to listen for incomming TCP connection
        /// requests.
        /// </summary>
        private TcpListener tcpListener;
        /// <summary>
        /// Background thread for TcpServer workload.
        /// </summary>
        private Thread tcpListenerThread;
        /// <summary>
        /// Create handle to connected tcp client.
        /// </summary>
        private TcpClient connectedTcpClient;
        #endregion

        // Use this for initialization
        void Start()
        {
            // Start TcpServer background thread
            tcpListenerThread = new Thread(new ThreadStart(ListenForIncommingRequests));
            tcpListenerThread.IsBackground = true;
            tcpListenerThread.Start();
        }

        // Update is called once per frame
        void Update()
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                SendMessage();
            }
        }

        /// <summary>
        /// Runs in background TcpServerThread; Handles incomming TcpClient requests
        /// </summary>
        private void ListenForIncommingRequests()
        {
            try
            {
                // Create listener on localhost port 8052.
                tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 8052);
                tcpListener.Start();
                Debug.Log("Server is listening");
                Byte[] bytes = new Byte[1024];
                while (true)
                {
                    using (connectedTcpClient = tcpListener.AcceptTcpClient())
                    {
                        // Get a stream object for reading
                        using (NetworkStream stream = connectedTcpClient.GetStream())
                        {
                            int length;
                            // Read incomming stream into byte arrary.
                            while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                            {
                                var incommingData = new byte[length];
                                Array.Copy(bytes, 0, incommingData, 0, length);
                                // Convert byte array to string message.
                                string clientMessage = Encoding.ASCII.GetString(incommingData);
                                Debug.Log("client message received as: " + clientMessage);
                            }
                        }
                    }
                }
            }
            catch (SocketException socketException)
            {
                Debug.Log("SocketException " + socketException.ToString());
            }
        }
        /// <summary>
        /// Send message to client using socket connection.
        /// </summary>
        public void SendMessage()
        {
            if (connectedTcpClient == null)
            {
                return;
            }

            try
            {
                // Get a stream object for writing.
                NetworkStream stream = connectedTcpClient.GetStream();
                if (stream.CanWrite)
                {
                    string serverMessage = "This is a message from your server.";
                    // Convert string message to byte array.
                    byte[] serverMessageAsByteArray = Encoding.ASCII.GetBytes(serverMessage);
                    // Write byte array to socketConnection stream.
                    stream.Write(serverMessageAsByteArray, 0, serverMessageAsByteArray.Length);
                    Debug.Log("Server sent his message - should be received by client");
                }
            }
            catch (SocketException socketException)
            {
                Debug.Log("Socket exception: " + socketException);
            }
        }


        // private static int localPort;
        //
        // // prefs
        // private string IP;  // define in init
        // public int port;  // define in init
        //
        // private UdpClient upd;
        //
        // public CommsManager() {
        //   IP = "192.168.4.1"; //https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html#:~:text=The%20network%20established%20by%20softAP,has%20only%20one%20hardware%20channel.
        //   port = 111;
        // }
        //
        // // code from https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.udpclient?view=net-5.0#constructors
        // public void establishConnection() {
        //     upd = new UdpClient(port);
        //     TcpListener tcp = new TcpListener(IPAddress.Parse(IP), port);
        //     udp.Connect(IP, port);
        //
        //     Byte[] sendBytes = Encoding.ASCII.GetBytes("kobe 8");
        //
        //     udp.Send(sendBytes, sendBytes.Length);
        //
        //     //IPEndPoint object will allow us to read datagrams sent from any source.
        //     IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
        //
        //     // Blocks until a message returns on this socket from a remote host.
        //     Byte[] receiveBytes = udp.Receive(ref RemoteIpEndPoint);
        //     string returnData = Encoding.ASCII.GetString(receiveBytes);
        //
        //     // Uses the IPEndPoint object to determine which of these two hosts responded.
        //     Debug.Log("This is the message you received " +
        //                               returnData.ToString());
        //     Debug.Log("This message was sent from " +
        //                              RemoteIpEndPoint.Address.ToString() +
        //                              " on their port number " +
        //                              RemoteIpEndPoint.Port.ToString());
        //
        //     udp.Close();
        // }
        //
        // /*
        // * main method that sends the Data
        // */
        // public int sendData() {
        //
        //   return 27;
        // }

    }
}
