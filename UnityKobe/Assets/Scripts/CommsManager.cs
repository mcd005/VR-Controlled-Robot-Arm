using System.Collections;
using UnityEngine;
using UnityEngine.Networking;
using System.Text;


/*
 * think about the fact that if data is sent all the time then movement may be  staggered
 * this will not look good
 * For now get the data to be sent to webserver repeatedly every second
 * then make it send a block of data when there is a change
 * add buffers for example a 5 degree change in controller position is not enough to warrant 
 * sending data <-- is that really true though what if it needs to be precise
 */
public class CommsManager : MonoBehaviour
{
    public string json;
    private GameObject operatorData;

    void Start()
    {
        Debug.Log("lalal");

        // will need to get real data
        OperatorData data = new OperatorData();

        data.RControllerPos = "(1, 2, 3)";
        data.AButtonPressed = "False";

        //json = JsonUtility.ToJson(data);
        //Debug.Log(json);

        //StartCoroutine(SendData());

        operatorData = GameObject.Find("XR Rig");

        Debug.Log(operatorData.GetComponent<HeadsetControlsManager>().getJSONFormatData());
        InvokeRepeating("ReadControllerDataDump", 1.0f, 1.0f);

    }

    //private void Update()
    //{
    //    Debug.Log("commsManager update");
    //    Debug.Log(json);
    //}

    private void ReadControllerDataDump()
    {
        //Debug.Log("Invoked repeatedly");
        //json = operatorData.getJSONFormatData();
        //Debug.Log("JSON received from headsetcontrols manager: " + json);
        //Debug.Log("what is happening" + operatorData.getJSONFormatData());
        //StartCoroutine(SendData());
    }

    // adapted from: https://answers.unity.com/questions/1491938/sending-an-https-post-request-with-json-body.html
    IEnumerator SendData()
    {
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

    // fake class to replicate where the data comes from
    private class OperatorData
    {
        public string RControllerPos;
        public string AButtonPressed;
    }
}
