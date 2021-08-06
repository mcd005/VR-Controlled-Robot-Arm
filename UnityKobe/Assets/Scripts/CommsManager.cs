using System.Collections;
using UnityEngine;
using UnityEngine.Networking;
using System.Text;

namespace CommsManagerSpace
{

    public class CommsManager : MonoBehaviour
    {
        public string json;
        private void Start()
        {
            Debug.Log("lalal");

            OperatorData data = new OperatorData();

            data.RControllerPos = "(1, 2, 3)";
            data.AButtonPressed = "False";

            json = JsonUtility.ToJson(data);
            Debug.Log(json);
            StartCoroutine(SendData());

        }

        // adapted from: https://answers.unity.com/questions/1491938/sending-an-https-post-request-with-json-body.html
        IEnumerator SendData()
        {
            var request = new UnityWebRequest("http://localhost:5000/", "POST");
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

        private class OperatorData
        {
            public string RControllerPos;
            public string AButtonPressed; 
        }

    }
}
