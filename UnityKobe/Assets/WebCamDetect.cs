using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WebCamDetect : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
          WebCamDevice[] devices = WebCamTexture.devices;
          Debug.Log("Number of web cams connected: " + devices.Length);

          for (int i = 0; i < devices.Length; i++) {
            Debug.Log(i + " " + devices[i].name);
          }

          Renderer rend = this.GetComponentInChildren<Renderer>();

          // hardcoding the device name
          WebCamTexture mycam = new WebCamTexture(devices[0].name);

          Debug.Log(mycam.deviceName + " mycam");
          // Debug.Log(mycam.deviceName + " deviceName");

          // mycam.deviceName = camName;

          // Debug.Log("poop");

          rend.material.mainTexture = mycam;

          Debug.Log("LALALALA: " + rend.material.mainTexture);
          if (mycam == null) {
            Debug.Log("fack");
          } else {
            mycam.Play();
          }
    }
}
