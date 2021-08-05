using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using CommsManagerSpace;
// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
  public string textValue;
  public Text textElement;
  // public Transform trackingSpace;

  //public Controller rightController;

  // Start is called before the first frame update
  void Start()
  {
      Debug.Log("sYEAGGAGGAAA");
      textElement.text = textValue;
  }

  // Update is called once per frame
  void Update()
  {
      textElement.text = getData();
  }

  private string getData() {
    // note: https://docs.unity3d.com/2019.2/Documentation/Manual/OculusControllers.html <-- name of diff parts of controller
    string data = "<u> Right controller <u>";
    data += "\n Position: " + OVRInput.GetLocalControllerPosition(OVRInput.Controller.RTouch).ToString("F3");
    data += "\n A button press: " + OVRInput.Get(OVRInput.Button.One).ToString();
    data += "\n B button press: " + OVRInput.Get(OVRInput.Button.Two).ToString();
    data += "\n ThumbstickPos: " + OVRInput.Get(OVRInput.Axis2D.SecondaryThumbstick).ToString("F3");
    data += "\n Thumbstick up: " + OVRInput.Get(OVRInput.Button.SecondaryThumbstickUp).ToString();
    data += "\n Index trigger: " + OVRInput.Get(OVRInput.Axis1D.SecondaryIndexTrigger).ToString();
    data += "\n Hand trigger: " + OVRInput.Get(OVRInput.Axis1D.SecondaryHandTrigger).ToString();
    data += "\n Thumb rest: " + OVRInput.Get(OVRInput.Touch.SecondaryThumbRest).ToString();
    data += "\n Haptic feedback: " ;
    // Debug.Log(OVRInput.GetLocalControllerPosition(OVRInput.Controller.RTouch));

    // let see if this works :/
    CommsManager comm = new CommsManager();
    comm.SendMessage();


    return data;
  }
}
