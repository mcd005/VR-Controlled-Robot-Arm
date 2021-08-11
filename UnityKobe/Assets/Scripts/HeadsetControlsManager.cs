using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.UI;
using System.Text;

// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
    public string textValue;
    public Text textElement;

    // CHASSIS control data
    public string LThumbstickUp;
    public string LThumbstickDown;
    public string LThumbstickRight;
    public string LThumbstickLeft;
    public string LIndexTrigger;
    public string LHandTrigger;

    // BIG ARM data

    // PLATFORM/SMALL ARM data


    private string json = "poop";

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("sYEAGGAGGAAA");
        textElement.text = textValue;

        LThumbstickUp = "";
        LThumbstickDown = "";
        LThumbstickRight = "";
        LThumbstickLeft = "";


        InvokeRepeating("SendOperatorData", 1.0f, 1.0f);
            
    }

    // Update is called once per frame
    void Update()
    {
        //textElement.text = getData();
        //Debug.Log("I am updating!");
        //LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp).ToString();
        //LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown).ToString();
        //LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight).ToString();
        //LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft).ToString();
        //Debug.Log("i am done updating");

        ////updateJSON();
        //PutToJSON();
    }

    void SendOperatorData()
    {
        StartCoroutine(PutToJSON());
    }

    private IEnumerator PutToJSON()
    {
        LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp).ToString();
        LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown).ToString();
        LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight).ToString();
        LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft).ToString();

        json = JsonUtility.ToJson(this);
        Debug.Log(json);

        /**
         * for now
         */
        var request = new UnityWebRequest("localHost:5000/", "POST");
        byte[] bodyRaw = Encoding.UTF8.GetBytes(json);
        request.uploadHandler = (UploadHandler)new UploadHandlerRaw(bodyRaw);
        request.downloadHandler = (DownloadHandler)new DownloadHandlerBuffer();
        request.SetRequestHeader("Content-Type", "application/json");
        yield return request.SendWebRequest();

        if (request.error != null)
        {
            Debug.Log("Error");
            Debug.Log("Status Code: " + request.responseCode);
        }
        else
        {
            Debug.Log("All OK");
            Debug.Log("Status Code: " + request.responseCode);
        }
    }

    public string getJSONFormatData()
    {
        Debug.Log("in headsetcontrolsmanager");
        Debug.Log("what does json look like here: " + json);
        return json;
    }

    private string getData()
    {
        // note: https://docs.unity3d.com/2019.2/Documentation/Manual/OculusControllers.html <-- name of diff parts of controller
        string data = "<u> Right controller <u>";
        data += "\n Position: " + OVRInput.GetLocalControllerPosition(OVRInput.Controller.RHand).ToString("F3");
        //RControllerPos = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RTouch).ToString("F3");
        data += "\n A button press: " + OVRInput.Get(OVRInput.Button.One).ToString();
        data += "\n B button press: " + OVRInput.Get(OVRInput.Button.Two).ToString();
        data += "\n ThumbstickPos: " + OVRInput.Get(OVRInput.Axis2D.SecondaryThumbstick).ToString("F3");
        data += "\n Thumbstick up: " + OVRInput.Get(OVRInput.Button.SecondaryThumbstickUp).ToString();
        data += "\n Index trigger: " + OVRInput.Get(OVRInput.Axis1D.SecondaryIndexTrigger).ToString();
        data += "\n Hand trigger: " + OVRInput.Get(OVRInput.Axis1D.SecondaryHandTrigger).ToString();
        data += "\n Thumb rest: " + OVRInput.Get(OVRInput.Touch.SecondaryThumbRest).ToString();
        data += "\n Haptic feedback: ";
        // Debug.Log(OVRInput.GetLocalControllerPosition(OVRInput.Controller.RTouch));

        return data;
    }


}
