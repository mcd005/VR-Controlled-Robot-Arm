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

          // hardcoding the device name
          WebCamTexture mycam = new WebCamTexture(devices[0].name);

          rend.material.mainTexture = mycam;
          if (mycam == null) {
            Debug.Log("No device connected");
          } else {
            mycam.Play();
          }
    }
}
