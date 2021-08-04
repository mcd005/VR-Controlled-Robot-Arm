using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Threading;

// code adapted from https://forum.arduino.cc/t/send-information-from-unity-to-arduino/307703
public class CommsManager : MonoBehaviour {

    SerialPort port = new SerialPort("\\\\.\\COM11", 9600);

    void Start ()
    {
        port.Open();
        Debug.Log("poopo");
        foreach(string str in SerialPort.GetPortNames())
        {
            Debug.Log(string.Format("Existing COM port: {0}", str));
        }
    }


    void Update ()
    {
        // Debug.Log("" + System.IO.Ports.SerialPort.GetPortNames());

        // byte[] b = BitConverter.GetBytes(MyInt);
        port.Write("0");
        /**
        Rishan on arduino side can write script to receive it - 1st must open wifi port
        */
    }

}
