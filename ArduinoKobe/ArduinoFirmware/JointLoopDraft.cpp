// Main loop starts
// Arm is at rest position i.e. standing up
// Read position from serial
// 	S10 E100 W50
// 	S10 E100 W50
// 	S12 E100 W50
// If position has changed then update the relevant joint


int shoulderAngle = SHOULDER_REST_ANGLE;
int newShoulderAngle = SHOULDER_REST_ANGLE;
bool shoulderAngleHasChanged = False;

int elbowAngle = ELBOW_REST_ANGLE;
int newElbowAngle = ELBOW_REST_ANGLE;
bool elbowAngleHasChanged = False;

void setup
{
	// Set joints to their at rest position but using a moveJointToAngle() function so it does it slowly
}


void loop
{
	readCoordsFromSerial()
	checkIfCoordsHaveChanged()
	if (waistPosChanged)
	{
		updateWaist();
	}
	if (shoulderPosChanged)
	{
		updateShoulder();
	}
}

void readCoordsFromSerial()
{
	// We read S100, E50 etc..
	newShoulderAngle = 100;
	newElbowAngle = 50;
}

void checkIfCoordsHaveChanged()
{
	shoulderPosChanged = newShoulderAngle != shoulderAngle;
	elbowPosChanged = newElbowAngle != elbowAngle;
}







