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

        if (devices.Length > 1)
        {
            for (int i = 0; i < devices.Length; i++)
            {
                Debug.Log(devices[i].name);
            }
            // hardcoding the device name
            WebCamTexture mycam = new WebCamTexture(devices[1].name);

            Debug.Log(mycam.deviceName + " jfdjfjfjf");
            rend.material.mainTexture = mycam;
            if (mycam.deviceName == "FaceTime HD Camera (Built-in)")
            {
                Debug.Log("Ricoh Theta is not connected / on / in camera live mode");
            }
            else
            {
                // bool linkConnected = false;
                // if (linkConnected == false) {
                //
                // } else {
                mycam.Play();
                // }
            }
        }
    }

    private void runWithoutLink() {

    }
}
