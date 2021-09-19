using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HandData : MonoBehaviour
{
    public OVRSkeleton skeleton;
    private List<OVRBone> fingerBones;

    public string textValue;
    public Text textElement;
    // Start is called before the first frame update
    void Start()
    {
        fingerBones = new List<OVRBone>(skeleton.Bones);
        textElement.text = "why u do zis";
    }

    // Update is called once per frame
    void Update()
    {
      string data = "poop";
      foreach (var bone in fingerBones) {
        data += " " + bone.Id;
      }
      // data = skeleton.transform.InverseTransformPoint(fingerBones[2].Transform.position).ToString();
      data += fingerBones[4].Transform.position;
      textElement.text = data;
    }
}