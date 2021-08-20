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
    public string jsonData;
    public HeadsetControlsManager headsetControlsManager;

    void Start()
    {
        // instantiates headsetControllerObject that has data
        headsetControlsManager = FindObjectOfType<HeadsetControlsManager>();

        // repeatedly calls a method that gets the data from headsetControlsManager in JSON format and sends it to webserver
        InvokeRepeating("ReadControllerDataDump", 1.0f, 1.0f);
    }

    private void ReadControllerDataDump()
    {
        StartCoroutine(SendData(headsetControlsManager.getJSON()));
    }

    // adapted from: https://answers.unity.com/questions/1491938/sending-an-https-post-request-with-json-body.html
    IEnumerator SendData(string jsonData)
    {
        var request = new UnityWebRequest("http://192.168.0.59:5000/", "POST");
        byte[] bodyRaw = Encoding.UTF8.GetBytes(jsonData);
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
}
