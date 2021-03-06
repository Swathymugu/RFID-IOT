#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
 
const char* ssid ="swathy";         
const char* password = "swathy29";                 
 
int ledPin = D0; // GPIO13
WiFiServer server(80);

SoftwareSerial mySerial(D1,D0);

String stringOne;
String stringTwo;
String stringThree;
 char i;


void setup() 
{
  mySerial.begin(9600); // Setting the baud rate of Software Serial Library  
  Serial.begin(9600);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
Serial.println("/");
  
}

void loop() 
{
  if(mySerial.available()>0)
  {
    //char n1='10004B0388D0';
char n2='10004BA6CD30';

  i = mySerial.read();
stringOne=String(i);
  //stringTwo=String(n1);
  stringThree=String(n2);

  if(stringOne.equals(stringThree))
  {
    Serial.println("REENA ECE THIRD YEAR");
  }
   
  
  }
   WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");



  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = HIGH;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<H1><center>Welcome</center></H1><Br>");
  client.println("   <hr color= green>");
  client.println("<center><a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.print("Led pin is now: ");
 
   if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
 
  client.println("  </center> <hr color= green>");
  client.println("</html>");
  
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  
  }
  
