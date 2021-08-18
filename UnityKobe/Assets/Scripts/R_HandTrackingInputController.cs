using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class R_HandTrackingInputController : OVRGrabber
{
    private OVRHand r_hand;
    public string textValue;
    public Text textElement;
    // Start is called before the first frame update
    protected override void Start()
    {
      base.Start();
      Debug.Log("The right hand script is running");
      textElement.text = textValue;
      r_hand = GetComponent<OVRHand>();
    }

    // Update is called once per frame
    public override void Update()
    {
      base.Update();
      string data = "<u> Right controller <u>";
      // data += "\n Position: " + OVRInput.GetLocalControllerPosition(OVRInput.Controller.Hand).ToString("F3");

      textElement.text = data;
      // float pinchStrength = r_hand.GetFingerPinchStrength(OVRHandFinger.Index);
      // textElement.text = pinchStrength.ToString();
      // var hand = GetComponent<OVRHand>();
      // bool isIndexFingerPinching = hand.GetFingerIsPinching(HandFinger.Index);
      // float ringFingerPinchStrength = hand.GetFingerPinchStrength(HandFinger.Index);
      // TrackingConfidence confidence = hand.GetFingerConfidence(HandFinger.Index);
      //
      // Debug.Log(isIndexFingerPinching);
      // Debug.Log(ringFingerPinchStrength);
      // Debug.Log(confidence);
    }
}
