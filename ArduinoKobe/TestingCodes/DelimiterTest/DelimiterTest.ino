//serial monitor if desired
// * is used as the data string delimiter
// , is used to delimit individual data 

String readString; //main captured String 
String angle; //data String
String fuel;
String speed1;
String altidude;

int ind1; // , locations
int ind2;
int ind3;
int ind4;

void setup() {
  Serial.begin(9600);
  Serial.println("serial delimit test 11-12-13"); // so I can keep track of what is loaded
}

void loop() {


  // 130,hi,7.2,389*

  if (Serial.available())  {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c == '*') {
      //do stuff
      
      Serial.println();
      Serial.print("captured String is : "); 
      Serial.println(readString); //prints string to serial port out
      
      ind1 = readString.indexOf(',');  //finds location of first ,
      angle = readString.substring(0, ind1);   //captures first data String
      ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      fuel = readString.substring(ind1+1, ind2+1);   //captures second data String
      ind3 = readString.indexOf(',', ind2+1 );
      speed1 = readString.substring(ind2+1, ind3+1);
      ind4 = readString.indexOf(',', ind3+1 );
      altidude = readString.substring(ind3+1); //captures remain part of data after last ,

      Serial.print("angle = ");
      Serial.println(angle); 
      Serial.print("fuel = ");
      Serial.println(fuel);
      Serial.print("speed = ");
      Serial.println(speed1);
      Serial.print("altidude = ");
      Serial.println(altidude);
      Serial.println();
      Serial.println();
      
      readString=""; //clears variable for new input
      angle="";
      fuel="";
      speed1="";
      altidude="";
    }  
    else {     
      readString += c; //makes the string readString
    }
  }
}
