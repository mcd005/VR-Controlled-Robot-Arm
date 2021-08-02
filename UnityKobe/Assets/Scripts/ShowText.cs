using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShowText : MonoBehaviour
{

    public string textValue;
    public Text textElement;

    //public Controller rightController;

    // Start is called before the first frame update
    void Start()
    {
        textElement.text = textValue;
    }

    // Update is called once per frame
    void Update()
    {
        //textElement.text = textValue;
        textElement.text = OVRInput.GetLocalControllerPosition(OVRInput.Controller.RTouch).ToString();
    }
}
