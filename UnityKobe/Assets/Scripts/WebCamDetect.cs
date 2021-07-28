using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WebCamDetect : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
          WebCamDevice[] devices = WebCamTexture.devices;
          Renderer rend = this.GetComponentInChildren<Renderer>();

          for (int i = 0; i < devices.Length; i++){
            Debug.Log(devices[i].name);
          }
          // hardcoding the device name
          WebCamTexture mycam = new WebCamTexture(devices[1].name);

          rend.material.mainTexture = mycam;
          if (mycam == null) {
            Debug.Log("No device connected");
          } else {
            mycam.Play();
          }
    }
}
