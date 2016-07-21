#include "MQTT/MQTT.h"

int ledd7 = D7; //LED to know if the program is running 

void callback(char* topic, byte* payload, unsigned int length);
/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
 byte server[] = {192,168,201,28};
 MQTT client(server,1883,callback);
//MQTT client("m12.cloudmqtt.com", 13434, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    if (message.equals("RED"))    
        RGB.color(255, 0, 0);
    else if (message.equals("GREEN"))    
        RGB.color(0, 255, 0);
    else if (message.equals("BLUE"))    
        RGB.color(0, 0, 255);
    else if (message.equals("STOP"))    
        RGB.color(255, 255, 255);
    else if (message.equals("SWITCH_D7"))
        blink_d7(5);
    else if (message.equals("TALK"))
        client.publish("COLOR","Welcome to Talk Mode of PHOTON");
    else if ((message.equals("HELLO")) || (message.equals("HI")) || (message.equals("YO")))
    {
        client.publish("COLOR", "Hey What's up ?"); 
        blink_d7(1); 
    }
    else if((message.equals("BYE")) || (message.equals("ADIOS")))
    {
        client.publish("COLOR", "Good Bye and Have a nice day");
        blink_d7(3); 
        RGB.color(0,0,0);
    }
    else
    {
        RGB.color(100,100,100);
    }    
    delay(1000);
}

void blink(void)
{
    digitalWrite(ledd7, HIGH); 
    delay(1000); 
    digitalWrite(ledd7,LOW); 
    delay(1000);
}
void blink_d7(int count)
{
    for(int i =0; i<count; i++)
    {
        blink(); 
    }
}

void setup_led(void)
{
    pinMode(ledd7,OUTPUT); 
}

void setup() 
{
    RGB.control(true);
    
    setup_led(); 
    
    // connect to the server
    //client.connect("sparkclient","qqwynymm","6mpZdQyzo1r6"); //id, username, password
    client.connect("sparkclient");

    // publish/subscribe
    if (client.isConnected()) 
    {
        //For successful Client Connection Blink D7 like Twice
        blink_d7(3); 
        client.publish("COLOR","Hello World");
        
        client.subscribe("COLOR");
    }
    else
    {
        blink_d7(1); 
    }
}

void loop() 
{
    if (client.isConnected())
        client.loop();
}


