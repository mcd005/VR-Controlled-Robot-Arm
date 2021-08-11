using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

[System.Serializable]

// struc = class without functions to hold data
public struct Gesture {

  public string name;
  public List<Vector3> fingerDatas;
  public UnityEvent onRecognized;
}

public class gestureDetector : MonoBehaviour
{

    public OVRSkeleton skeleton;
    public List<Gesture> gestures;
    private List<OVRBone> fingerBones;

    public string textValue;
    public Text textElement;
    // Start is called before the first frame update
    void Start()
    {
      fingerBones = new List<OVRBone>(skeleton.Bones);
      textElement.text = textValue;
    }

    // Update is called once per frame
    void Update()
    {
      //string data = "";
      //for (int i = 0; i < fingerBones.Length; i++) {
      //  data += "\n " + fingerBones[0];
      //}
      //textElement.text = fingerBones[0].Transform.position.ToString();
      // if (Input.GetKeyDown(KeyCode.Space)) {
      //   Save();
      // }
    }

    void Save() {
      // Gesture g = new Gesture();
      // g.name = "New gesture";
      // List<Vector3> data = new List<Vector3>();
      //
      // foreach (var bone in fingerBones) {
      //   data.Add(skeleton.transform.InverseTransformPoint(bone.Transform.position));
      // }
      // g.fingerDatas = data;
      // gestures.Add(g);
    }
}
