using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum SmallArmControl
{
    UP = 0,
    DOWN,
    DO_NOTHING,
}

public enum ChassisDirection
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    ROTATE_LEFT,
    ROTATE_RIGHT
}



// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
    // CHASSIS control data
    private bool LThumbstickUp;
    private bool LThumbstickDown;
    private bool LThumbstickRight;
    private bool LThumbstickLeft;
    private float LIndexTrigger;
    private float LHandTrigger;

    // BIG ARM data
    private Vector3 RControllerPos = new Vector3(0.0f, 0.0f, 0.0f);

    // PLATFORM/SMALL ARM data
    private bool RAButtonPress;
    private bool RBButtonPress;

    private string json = "";

    public int bigArmWristFlexor;
    public int bigArmClaw;
    public int bigArmWristRotator;
    public int bigArmElbow;
    public int bigArmShoulder;

    public SmallArmControl smallArmVerticalDirection; // U, D, N <-- one variable and letter describes vertical movement direction of the arm

    public ChassisDirection chassisDirection; // 0 = dont move, 1 = forward, 2 = right, 3 = down, 4 = left <-- one variable and letter describes movement direction of the arm

    // Start is called before the first frame update
    void Start()
    {
    }
    
    // Update is called once per frame
    void Update()
    {
        getControllerData();
        translateChassisData();
        translateBigArmData(new Vector3(0,0,0));
        translateSmallArmData(false,false);
        json = toJSON(this);
    }

    void getControllerData()
    {
        // chassis
        LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp);
        LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown);
        LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight);
        LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft);
        LIndexTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryIndexTrigger);
        LHandTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryHandTrigger);

        // big arm 
        RControllerPos = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RHand);

        // small arm
        RAButtonPress = OVRInput.Get(OVRInput.Button.One);
        RBButtonPress = OVRInput.Get(OVRInput.Button.Two);
    }

    void translateBigArmData(Vector3 position)
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;
        // complex mathematics for x, y, z to ouput degree for each servo

        bigArmWristFlexor = 90;
        bigArmClaw = 90;
        bigArmWristRotator = 90;
        bigArmElbow = 90;
        bigArmShoulder = 90;
    }

    void translateChassisData()
    {
        chassisDirection = ChassisDirection.UP;
    }

    private void translateSmallArmData(bool AButton, bool BButton)
    {
        if (AButton && BButton)
        {
            smallArmVerticalDirection = SmallArmControl.DO_NOTHING;
        }
        else if (AButton)
        {
            smallArmVerticalDirection = SmallArmControl.UP;
        }
        else if (BButton)
        {
            smallArmVerticalDirection = SmallArmControl.DOWN;
        }
        else
        {
            smallArmVerticalDirection = SmallArmControl.DO_NOTHING;
        }
    }

    public string getJSON()
    {
        Debug.Log(json);
        return json;
    }

    private string toJSON(HeadsetControlsManager headsetControlsManager)
    {
        return JsonUtility.ToJson(headsetControlsManager);
    }

}
