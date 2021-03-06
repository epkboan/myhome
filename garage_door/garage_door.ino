/*
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * http://www.mysensors.org/build/relay
 */

#define MY_DEBUG
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_FREQUENCY RFM69_433MHZ // RFM69_433MHZ for development branch, RF69_433MHZ for master
#define MY_RFM69_NEW_DRIVER 

#define MY_REPEATER_FEATURE
#define MY_NODE_ID 60

#define MY_RFM69_NETWORKID (170)

#define CHILD_ID_RELAY        2
#define CHILD_ID_DOOR_DOWN    3
#define CHILD_ID_DOOR_UP      4
#define CHILD_ID_DOOR_STATUS  5

#define DOOR_TOGGLE_RELAY_PIN 4
#define DOOR_DOWN_PIN         6
#define DOOR_UP_PIN           7

#define STATE_OPEN            1
#define STATE_CLOSED          2
#define STATE_MOTION          3
#define STATE_STOPPED         4

#include <MySensors.h>
#include <Bounce2.h>

MyMessage doorUpMsg(CHILD_ID_DOOR_UP, V_TRIPPED);
MyMessage doorDownMsg(CHILD_ID_DOOR_DOWN, V_TRIPPED);
MyMessage statusMsg(CHILD_ID_DOOR_STATUS, V_TEXT);

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE

Bounce debouncerDown = Bounce(); 
Bounce debouncerUp = Bounce(); 

static bool toggleSwitch=false;
static uint8_t sentValueDown=2;
static uint8_t sentValueUp=2;
static unsigned long lastChangeTime;
static uint8_t state = STATE_CLOSED;
void before()
{
}

void setup()
{
  pinMode(DOOR_TOGGLE_RELAY_PIN, OUTPUT);   
  digitalWrite(DOOR_TOGGLE_RELAY_PIN, LOW); 

  // Window sensor that is closed when garage door is down
  pinMode(DOOR_DOWN_PIN, INPUT);   
  digitalWrite(DOOR_DOWN_PIN, HIGH);   // Activate internal pull-ups
  // After setting up the button, setup debouncer
  debouncerDown.attach(DOOR_DOWN_PIN);
  debouncerDown.interval(5);

  // Window sensor that is closed when garage door fully up
  pinMode(DOOR_UP_PIN, INPUT);   
  digitalWrite(DOOR_UP_PIN, HIGH);     // Activate internal pull-ups
  // After setting up the button, setup debouncer
  debouncerUp.attach(DOOR_UP_PIN);
  debouncerUp.interval(5);

}

void presentation()
{
    sendSketchInfo("Garage", "1.1");
    
    present(CHILD_ID_RELAY, S_BINARY);  
    present(CHILD_ID_DOOR_DOWN, S_DOOR);
    present(CHILD_ID_DOOR_UP, S_DOOR);
    present(CHILD_ID_DOOR_STATUS, S_INFO);
}

void loop()
{
  uint8_t value;

  // Have we received the order to toggle the Garge Door
  if(toggleSwitch == true) {
    digitalWrite(DOOR_TOGGLE_RELAY_PIN, HIGH);
    // Emulate the lenght of a human button push ;-)
    wait(500);
    digitalWrite(DOOR_TOGGLE_RELAY_PIN, LOW);
    toggleSwitch = false;
  }

  // Garage door fully down sensor
  debouncerDown.update();
  value = debouncerDown.read();
  if (value != sentValueDown) {
    // Value has changed from last transmission, send the updated value
    sentValueDown = value;
    lastChangeTime = millis();
    if(value == LOW) {
      send(doorDownMsg.set(false)); // Not tripped
      send(statusMsg.set("Closed"));
      state = STATE_CLOSED;
    } else {
      send(doorDownMsg.set(true)); // Tripped
      send(statusMsg.set("Opening"));
      state = STATE_MOTION;
    }
  }

  // Garage door fully up sensor
  debouncerUp.update();
  value = debouncerUp.read();
  if (value != sentValueUp) {
    // Value has changed from last transmission, send the updated value
    sentValueUp = value;
    lastChangeTime = millis();

    if(value == LOW) {
      send(doorUpMsg.set(false)); // Not tripped
      send(statusMsg.set("Open"));
      state = STATE_OPEN;
    } else {
      send(doorUpMsg.set(true));  // Tripped
      send(statusMsg.set("Closing"));
      state = STATE_MOTION;
    }
  }

  // More than 30 seconds elapsed and still not open nor closed then we assume state stopped
  if((state == STATE_MOTION) && (millis() > (lastChangeTime + 30*1000))) {
     state = STATE_STOPPED;
     send(statusMsg.set("Stopped"));
  }
}

void receive(const MyMessage &message)
{
  // We only expect one type of message from controller. But we better check anyway.
  if (message.type==V_STATUS) {
    toggleSwitch = true;    
  }
}
