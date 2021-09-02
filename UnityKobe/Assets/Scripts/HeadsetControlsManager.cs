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
    FORWARD = 0,
    BACKWARDS,
    LEFT,
    RIGHT,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    NONE
}

public struct ChassisControlData
{
    public bool LThumbstickUp;
    public bool LThumbstickDown;
    public bool LThumbstickRight;
    public bool LThumbstickLeft;

    public float LIndexTrigger;
    public float LHandTrigger;

    public bool thumbStickUsed()
    {
        if (LThumbstickLeft || LThumbstickDown || LThumbstickRight || LThumbstickUp)
        {
            return true;
        } else
        {
            return false;
        }
    }
}

// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
    // CHASSIS control data

    private ChassisControlData chassisControlData = new ChassisControlData();

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
      InvokeRepeating("updateData", 1.0f, 0.1f);
    }

    private void updateData()
    {
      getControllerData();
      translateChassisData(chassisControlData);
      translateBigArmData(RControllerPos);
      translateSmallArmData(RAButtonPress,RBButtonPress);
      // json = toJSON(this);
    }

    public void getControllerData()
    {
        // chassis
        chassisControlData.LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp);
        chassisControlData.LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown);
        chassisControlData.LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight);
        chassisControlData.LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft);
        chassisControlData.LIndexTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryIndexTrigger);
        chassisControlData.LHandTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryHandTrigger);

        // big arm
        RControllerPos = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RHand);

        // small arm
        RAButtonPress = OVRInput.Get(OVRInput.Button.One);
        RBButtonPress = OVRInput.Get(OVRInput.Button.Two);
    }

    public void translateBigArmData(Vector3 position)
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;
        // complex mathematics for x, y, z to ouput degree for each servo

        bigArmWristFlexor = 60;
        bigArmClaw = 0;
        bigArmWristRotator = 0;
        bigArmElbow = 0;
        bigArmShoulder = 0;
    }

    public void translateChassisData(ChassisControlData chassisControlData)
    {
        // thumbstick cannot be in two different position
        // put priority on forward, backward, left and right movement
        if (chassisControlData.LHandTrigger > 0 && !chassisControlData.thumbStickUsed())
        {
            chassisDirection = ChassisDirection.LEFT;
        }
        else if (chassisControlData.LIndexTrigger > 0 && !chassisControlData.thumbStickUsed())
        {
            chassisDirection = ChassisDirection.RIGHT;
        }
        else if (chassisControlData.LThumbstickUp)
        {
            chassisDirection = ChassisDirection.FORWARD;
        }
        else if (chassisControlData.LThumbstickDown)
        {
            chassisDirection = ChassisDirection.BACKWARDS;
        }
        else if (chassisControlData.LThumbstickLeft)
        {
            chassisDirection = ChassisDirection.ROTATE_LEFT;
        }
        else if (chassisControlData.LThumbstickRight)
        {
            chassisDirection = ChassisDirection.ROTATE_RIGHT;
        } else
        {
            chassisDirection = ChassisDirection.NONE;
        }
    }

    public void translateSmallArmData(bool AButton, bool BButton)
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

    public string getData() {
      int smallArmValue = (int) smallArmVerticalDirection;
      int chassisDirectionValue = (int) chassisDirection;
      return $"D{smallArmValue},K{chassisDirectionValue},";
    }


    // these are useless now ... we do not use JSON anymore!
    public string getJSON()
    {
        return json;
    }

    public ChassisControlData getChassisControlDataObject()
    {
        return chassisControlData;
    }


    public string toJSON(HeadsetControlsManager headsetControlsManager)
    {
        return JsonUtility.ToJson(headsetControlsManager);

    }

}
