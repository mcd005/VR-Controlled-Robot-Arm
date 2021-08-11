using UnityEngine;

public enum SmallArmControl
{
    Up = 1,
    Down = 2,
    Invalid = 27,
    DoNothing = 0
}

// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
    // CHASSIS control data
    private string LThumbstickUp;
    private string LThumbstickDown;
    private string LThumbstickRight;
    private string LThumbstickLeft;
    private string LIndexTrigger;
    private string LHandTrigger;

    // BIG ARM data
    private Vector3 RControllerPos = new Vector3(0.0f, 0.0f, 0.0f);

    // PLATFORM/SMALL ARM data
    private bool RAButtonPress;
    private bool RBButtonPress;

    private string json = "";

    public SmallArmControl smallArmControl;

    // Start is called before the first frame update
    void Start()
    {        
        InvokeRepeating("PutToJSON", 1.0f, 0.01f);
    }

    // Update is called once per frame
    void Update()
    {
        getControllerData();
        json = toJSON(this);
        smallArmControl = translateChassisData(RAButtonPress, RBButtonPress);
    }

    void getControllerData() {

        // chassis
        LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp).ToString();
        LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown).ToString();
        LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight).ToString();
        LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft).ToString();
        LIndexTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryIndexTrigger).ToString();
        LHandTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryHandTrigger).ToString();

        // big arm
        RControllerPos = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RHand);


        // small arm
        RAButtonPress = OVRInput.Get(OVRInput.Button.One);
        RBButtonPress = OVRInput.Get(OVRInput.Button.Two);
    }

    private SmallArmControl translateChassisData(bool AButton, bool BButton)
    {
        if (AButton && BButton)
        {
            return SmallArmControl.Invalid;
        }
        else if (AButton)
        {
            return SmallArmControl.Up;
        } else if (BButton)
        {
            return SmallArmControl.Down;
        } else
        {
            return SmallArmControl.DoNothing;
        }
    }

    public string getJSON()
    {
        return json;
    }

    private string toJSON(HeadsetControlsManager controller)
    {
        return JsonUtility.ToJson(controller);
    }

}
