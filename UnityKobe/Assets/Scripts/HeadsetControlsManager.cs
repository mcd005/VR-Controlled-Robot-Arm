using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.UI;
using System.Text;

using UnityEngine.XR.Interaction.Toolkit;

// FOR NOW very basic - can I record the position of the right hand controller through the environment?
// displays all the data from the headset onto the text display
public class HeadsetControlsManager : MonoBehaviour
{
    public string textValue;
    public Text textElement;

    //public XRRig xrRig;

    // CHASSIS control data
    public string LThumbstickUp;
    public string LThumbstickDown;
    public string LThumbstickRight;
    public string LThumbstickLeft;
    public string LIndexTrigger;
    public string LHandTrigger;

    // BIG ARM data
    public Vector3 RControllerPos;

    // PLATFORM/SMALL ARM data
    public bool RAButtonPress;
    public bool RBButtonPress;

    private string json = "";

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("sYEAGGAGGAAA");
        //textElement.text = textValue;

        LThumbstickUp = "";
        LThumbstickDown = "";
        LThumbstickRight = "";
        LThumbstickLeft = "";
        LIndexTrigger = "";
        LHandTrigger = "";

        RControllerPos = new Vector3(0.0f, 0.0f, 0.0f);

        RAButtonPress = false;
        RBButtonPress = false;
        
        InvokeRepeating("SendOperatorData", 1.0f, 0.01f);

        //xrRig = FindObjectOfType<XRRig>();
        //Debug.Log(xrRig);
        //xrRig 
    }

    // Update is called once per frame
    void Update()
    {
    }

    void SendOperatorData()
    {
        StartCoroutine(PutToJSON());
    }

    void getOperatorData() {

        // translatorClasses

        LThumbstickUp = OVRInput.Get(OVRInput.Button.PrimaryThumbstickUp).ToString();
        LThumbstickDown = OVRInput.Get(OVRInput.Button.PrimaryThumbstickDown).ToString();
        LThumbstickRight = OVRInput.Get(OVRInput.Button.PrimaryThumbstickRight).ToString();
        LThumbstickLeft = OVRInput.Get(OVRInput.Button.PrimaryThumbstickLeft).ToString();
        LIndexTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryIndexTrigger).ToString();
        LHandTrigger = OVRInput.Get(OVRInput.Axis1D.PrimaryHandTrigger).ToString();

        RControllerPos = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RHand);

        RAButtonPress = OVRInput.Get(OVRInput.Button.One);
        RBButtonPress = OVRInput.Get(OVRInput.Button.Two);
    }

    private IEnumerator PutToJSON()
    {

        getOperatorData();
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

}
