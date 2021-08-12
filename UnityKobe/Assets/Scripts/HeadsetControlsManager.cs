using UnityEngine;
using System.Collections;
using System.Collections.Generic;

//public enum SmallArmControl
//{
//    Up = 1,
//    Down = 2,
//    Invalid = 27,
//    DoNothing = 0,

    //Do = 0 // 0 = Nothing, 1 = Up and 2 = Down <-- less variables less risk of overlapping instructions

    /*
     * Direction = U, D, N <-- one variable and letter describes movement direction of the arm 
     */
//}

//public enum BigArmControl
//{
//    // servo name = degree of rotation
//    W = 0, // wrist flexor
//    C = 0, // claw
//    R = 0, // wrist rotator
//    E = 0, // elbow
//    S = 0  // shoulder
//}


//public enum ChassisControl
//{
//    Direction = 0, // 0 = dont move, 1 = forward, 2 = right, 3 = down, 4 = left
//    Rotations = 0 // degree of rotation can be negative or positive
//}

public class BigArmControl
{
    public int W { get; set; } // <-- now we can edit the degree of movement for each servo
    public int C { get; set; }
    public int R { get; set; }
    public int E { get; set; }
    public int S { get; set; }
}

public class SmallArmControl
{
    public string verticalDirection { get; set; } // U, D, N <-- one variable and letter describes vertical movement direction of the arm
}

public class ChassisControl
{
    public int direction { get; set; } // 0 = dont move, 1 = forward, 2 = right, 3 = down, 4 = left <-- one variable and letter describes movement direction of the arm
    public int rotation { get; set; } // 
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

    // Separator controllers
    public SmallArmControl smallArm;
    public BigArmControl bigArm;
    public ChassisControl chassis;

    // other idea -- too much overhead to have other classes so just make public vars



    // Start is called before the first frame update
    void Start() {
        

    }
    
    // Update is called once per frame
    void Update()
    {
        getControllerData();
        json = toJSON(this);
        //smallArmControl = translateChassisData(RAButtonPress, RBButtonPress);
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

        bigArm.W = 20;
        bigArm.E = 30;
        bigArm.C = 10;
        bigArm.S = 60;
        bigArm.R = 50;
    }

    void translateChassisData()
    {

    }

    private void translateSmallArmData(bool AButton, bool BButton)
    {
        if (AButton && BButton)
        {
            // don't move
           smallArm.verticalDirection = "N";
        }
        else if (AButton)
        {
            // go up
            smallArm.verticalDirection = "U";
        }
        else if (BButton)
        {
            // go down
            smallArm.verticalDirection = "D";
        }
        else
        {
            // don't move
            smallArm.verticalDirection = "N";
        }
    }

    //private SmallArmControl translateChassisData(bool AButton, bool BButton)
    //{
    //if (AButton && BButton)
    //{
    //    // don't move
    //    return 0;
    //}
    //else if (AButton)
    //{
    //    // go up
    //    return 1;
    //} else if (BButton)
    //{
    //    // go down
    //    return 2;
    //} else
    //{
    //    // don't move
    //    return 0;
    //}

    //if (AButton && BButton)
    //{
    //    return SmallArmControl.Invalid;
    //}
    //else if (AButton)
    //{
    //    return SmallArmControl.Up;
    //}
    //else if (BButton)
    //{
    //    return SmallArmControl.Down;
    //}
    //else
    //{
    //    return SmallArmControl.DoNothing;
    //}
    //}

    private int mapPlatformMoveToInt(string direction)
    {
        if (direction == "up") { return 1; }
        else if (direction == "down") { return 2; }
        else { return 0;  }
    }

    public string getJSON()
    {
        return json;
    }

    private string toJSON(HeadsetControlsManager headsetControlsManager)
    {
        return JsonUtility.ToJson(headsetControlsManager);
    }

}
