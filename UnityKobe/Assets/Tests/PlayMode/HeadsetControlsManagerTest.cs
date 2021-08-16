using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;
using UnityEngine;
using UnityEngine.TestTools;


public class HeadsetControlsManagerTest
{
    HeadsetControlsManager headsetControlsManager = new GameObject().AddComponent<HeadsetControlsManager>();

    [UnityTest]
    public IEnumerator TranslateBigArmDataTest()
    {
        headsetControlsManager.translateBigArmData(new Vector3(0.0f, 0.0f, 0.0f));

        int expectedBigArmWristFlexor = 90;
        int expectedBigArmClaw = 90;
        int expectedBigArmWristRotator = 90;
        int expectedBigArmElbow = 90;
        int expectedBigArmShoulder = 90;

        Assert.AreEqual(expectedBigArmWristFlexor, headsetControlsManager.bigArmWristFlexor);
        Assert.AreEqual(expectedBigArmClaw, headsetControlsManager.bigArmClaw);
        Assert.AreEqual(expectedBigArmWristRotator, headsetControlsManager.bigArmWristRotator);
        Assert.AreEqual(expectedBigArmElbow, headsetControlsManager.bigArmElbow);
        Assert.AreEqual(expectedBigArmShoulder, headsetControlsManager.bigArmShoulder);

        // more tests when math will change!

        yield return null;
    }

    [UnityTest]
    public IEnumerator TranslateSmallArmDataTest()
    {
        // bool AButton, boolBButton
        var expectedDirection = SmallArmControl.DO_NOTHING;

        headsetControlsManager.translateSmallArmData(true, true);
        Assert.AreEqual(expectedDirection, headsetControlsManager.smallArmVerticalDirection);

        expectedDirection = SmallArmControl.UP;
        headsetControlsManager.translateSmallArmData(true, false);
        Assert.AreEqual(expectedDirection, headsetControlsManager.smallArmVerticalDirection);


        expectedDirection = SmallArmControl.DOWN;
        headsetControlsManager.translateSmallArmData(false, true);
        Assert.AreEqual(expectedDirection, headsetControlsManager.smallArmVerticalDirection);

        expectedDirection = SmallArmControl.DO_NOTHING;
        headsetControlsManager.translateSmallArmData(false, false);
        Assert.AreEqual(expectedDirection, headsetControlsManager.smallArmVerticalDirection);

        yield return null;
    }

    [UnityTest]
    public IEnumerator TranslateChassisDataTest()
    {
        ChassisControlData chassisData = headsetControlsManager.getChassisControlDataObject();

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = true;
        headsetControlsManager.translateChassisData(chassisData);
        var expectedDirection = ChassisDirection.FORWARD;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = true;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.BACKWARDS;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = true;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.LEFT;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = true;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.RIGHT;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 1.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.ROTATE_RIGHT;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 1.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.ROTATE_LEFT;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 1.0f;
        chassisData.LIndexTrigger = 1.0f;
        chassisData.LThumbstickDown = true;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.BACKWARDS;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        chassisData.LHandTrigger = 1.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = true;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = false;
        headsetControlsManager.translateChassisData(chassisData);
        expectedDirection = ChassisDirection.LEFT;
        Assert.AreEqual(expectedDirection, headsetControlsManager.chassisDirection);

        yield return null;
    }


    [UnityTest]
    public IEnumerator ToJSONTest()
    {

        ChassisControlData chassisData = new ChassisControlData();

        headsetControlsManager.getControllerData();
        headsetControlsManager.translateChassisData(chassisData);
        headsetControlsManager.translateBigArmData(new Vector3(0.0f, 0.0f, 0.0f));
        headsetControlsManager.translateSmallArmData(false, false);
        headsetControlsManager.toJSON(headsetControlsManager);
        var json = headsetControlsManager.getJSON();
        //Debug.Log(json);
        var expectedJson = "{\"bigArmWristFlexor\":90,\"bigArmClaw\":90,\"bigArmWristRotator\":90,\"bigArmElbow\":90,\"bigArmShoulder\":90,\"smallArmVerticalDirection\":2,\"chassisDirection\":6}";
        Assert.AreEqual(expectedJson, json);

        chassisData.LHandTrigger = 0.0f;
        chassisData.LIndexTrigger = 0.0f;
        chassisData.LThumbstickDown = false;
        chassisData.LThumbstickLeft = false;
        chassisData.LThumbstickRight = false;
        chassisData.LThumbstickUp = true;
        headsetControlsManager.translateBigArmData(new Vector3(1.0000f, -0.3000f, 5.0000f));
        headsetControlsManager.translateSmallArmData(true, false);
        // could be not passing because information gets changed to quickly -- will only stay for one frame
        expectedJson = "{\"bigArmWristFlexor\":90,\"bigArmClaw\":90,\"bigArmWristRotator\":90,\"bigArmElbow\":90,\"bigArmShoulder\":90,\"smallArmVerticalDirection\":0,\"chassisDirection\":0}";
        headsetControlsManager.toJSON(headsetControlsManager);
        json = headsetControlsManager.getJSON();
        //Debug.Log("1" + json);
        Assert.AreEqual(expectedJson, json);

        //chassisData.LHandTrigger = 1.0f;
        //chassisData.LIndexTrigger = 1.0f;
        //chassisData.LThumbstickDown = false;
        //chassisData.LThumbstickLeft = false;
        //chassisData.LThumbstickRight = true;
        //chassisData.LThumbstickUp = false;
        //headsetControlsManager.translateBigArmData(new Vector3(1.0000f, -0.3000f, 5.0000f));
        //headsetControlsManager.translateSmallArmData(false, false);
        //expectedJson = "{\"bigArmWristFlexor\":90,\"bigArmClaw\":90,\"bigArmWristRotator\":90,\"bigArmElbow\":90,\"bigArmShoulder\":90,\"smallArmVerticalDirection\":2,\"chassisDirection\":3}";
        //headsetControlsManager.toJSON(headsetControlsManager);
        //json = headsetControlsManager.getJSON();
        ////Debug.Log("2" + json);
        //Assert.AreEqual(expectedJson, json);

        //chassisData.LHandTrigger = 0.0f;
        //chassisData.LIndexTrigger = 1.0f;
        //chassisData.LThumbstickDown = false;
        //chassisData.LThumbstickLeft = false;
        //chassisData.LThumbstickRight = false;
        //chassisData.LThumbstickUp = true;
        //headsetControlsManager.translateBigArmData(new Vector3(0.0f, 10.000f, -5.0000f));
        //headsetControlsManager.translateSmallArmData(false, true);
        //expectedJson = "{\"bigArmWristFlexor\":90,\"bigArmClaw\":90,\"bigArmWristRotator\":90,\"bigArmElbow\":90,\"bigArmShoulder\":90,\"smallArmVerticalDirection\":1,\"chassisDirection\":0}";
        //headsetControlsManager.toJSON(headsetControlsManager);
        //json = headsetControlsManager.getJSON();
        ////Debug.Log("3" + json);
        //Assert.AreEqual(expectedJson, json);

        // others ? ...


        yield return null;
    }
}
