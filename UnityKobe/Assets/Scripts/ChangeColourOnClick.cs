using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeColourOnClick : MonoBehaviour
{
    private bool toggle = true;

    // Start is called before the first frame update
    void Start()
    {
        if (OVRInput.Get(OVRInput.Axis2D.PrimaryThumbstick) != null)
        {
            this.GetComponent<Renderer>().material.SetColor("_Color", Color.red);
        }
    }

    // Update is called once per frame
    void Update()
    {
        // if (OVRInput.GetDown(OVRInput.Button.One)){
        //   this.GetComponent<Renderer>().material.SetColor("_Color", Color.red);
        // }

        // var devices = new List<UnityEngine.XR.InputDevice>();
        // UnityEngine.XR.InputDevices.GetDevices(devices);
        // if (devices.Count > 0) {
        //   this.GetComponent<Renderer>().material.SetColor("_Color", Color.red);
        // }
        OVRInput.Update();
        if (OVRInput.Get(OVRInput.Button.One))
        {
            toggle = !toggle;
            if (toggle)
            {
                this.GetComponent<Renderer>().material.SetColor("_Color", Color.green);
            }
            else
            {
                this.GetComponent<Renderer>().material.SetColor("_Color", Color.blue);
            }
        }
        // bool triggerValue;
        // if (device.TryGetFeatureValue(UnityEngine.XR.CommonUsages.triggerButton, out triggerValue) && triggerValue)
        // {
        //
        //     Debug.Log("Trigger button is pressed.");
        // }
    }
}
