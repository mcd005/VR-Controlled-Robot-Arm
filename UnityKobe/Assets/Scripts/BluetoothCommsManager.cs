using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO.Ports;
using System.Threading;


public class BluetoothCommsManager : MonoBehaviour
{
    static SerialPort _serialPort;
    public HeadsetControlsManager headsetControlsManager;
    // Start is called before the first frame update
    void Start()
    {
      // Create a new SerialPort object with default settings.
      _serialPort = new SerialPort();

      // Allow the user to set the appropriate properties.
      _serialPort.PortName = "COM13";
      // _serialPort.BaudRate = SetPortBaudRate(_serialPort.BaudRate);
      // _serialPort.Parity = SetPortParity(_serialPort.Parity);
      // _serialPort.DataBits = SetPortDataBits(_serialPort.DataBits);
      // _serialPort.StopBits = SetPortStopBits(_serialPort.StopBits);
      // _serialPort.Handshake = SetPortHandshake(_serialPort.Handshake);

      // Set the read/write timeouts
      _serialPort.ReadTimeout = 500;
      _serialPort.WriteTimeout = 500;

      _serialPort.Open();

      headsetControlsManager = FindObjectOfType<HeadsetControlsManager>();

      InvokeRepeating("SendData", 1.0f, 0.5f);
    }

    void SendData()
    {
      // string json = headsetControlsManager.getJSON();
      string json = headsetControlsManager.getData();
      if (!string.IsNullOrEmpty(json)) {
        _serialPort.Write(json);
        Debug.Log(json);
              // System.Threading.Thread.Sleep(100);
        }
    }


    void OnApplicationQuit() {
      _serialPort.Close();
    }
}
