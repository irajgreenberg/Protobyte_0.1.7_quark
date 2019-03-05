/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */
 
import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400,400);
  frameRate(5);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,12000);
  
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1",12002);
}


void draw() {
  background(0);  
  
  OscMessage myMessage = new OscMessage("/dataForMatt");
  
  myMessage.add(0); /* add an int to the osc message */
  myMessage.add(int(random(81)));
  myMessage.add(0.0f);
  myMessage.add((float)random(1, 4));

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}

void mousePressed() {
  /* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/dataForMatt");
  
  myMessage.add(0); /* add an int to the osc message */
  myMessage.add(int(random(81)));
  myMessage.add(0.0f);
  myMessage.add((float)random(60, 210));

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}

void mouseReleased() {
  /* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/reich");
  
  myMessage.add(0); /* add an int to the osc message */
  myMessage.add(0);
  myMessage.add(0);
  myMessage.add(0.0f);

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
}