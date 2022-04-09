#include <Pinger.h>
#include <ESP8266WiFi.h>
#define LED_RED 4
#define LED_GREEN 5
#define LED_BLUE 16
extern "C"
{
  #include <lwip/icmp.h> 
  }
Pinger pinger;
void setup()
{  
  Serial.begin(9600);

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
  bool stationConnected = WiFi.begin(
  "wifiSSID",
  "wifiPASSWORD");
  if(!stationConnected)
  {
    Serial.println("Error, unable to connect specified WiFi network.");
  }
  Serial.print("Connecting to AP...");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Ok\n");
    pinger.OnReceive([](const PingerResponse& response)
  {
    if (response.ReceivedResponse)
    {
      Serial.printf("Reply from %s: bytes=%d time=%lums TTL=%d\n",response.DestIPAddress.toString().c_str(),    response.EchoMessageSize - sizeof(struct icmp_echo_hdr),        response.ResponseTime,        response.TimeToLive);
  
  
 


digitalWrite(LED_BLUE, HIGH);
digitalWrite(LED_RED, LOW);


  
    
    }
    else
    {
      Serial.printf("Request timed out.\n");
     digitalWrite(LED_RED, HIGH);
     digitalWrite(LED_BLUE, LOW);
 
    }
    return true;
  });
    pinger.OnEnd([](const PingerResponse& response)
  {
    float loss = 100;
    if(response.TotalReceivedResponses > 0)
    {
      loss = (response.TotalSentRequests - response.TotalReceivedResponses) * 100 / response.TotalSentRequests;
    }
  
    
    Serial.printf(
      "Ping statistics for %s:\n",response.DestIPAddress.toString().c_str());

  
  Serial.printf(
      "    Packets: Sent = %lu, Received = %lu, Lost = %lu (%.2f%% loss),\n",response.TotalSentRequests,response.TotalReceivedResponses,response.TotalSentRequests - response.TotalReceivedResponses,loss);

    if(response.TotalReceivedResponses > 0)
    {
      Serial.printf("Approximate round trip times in milli-seconds:\n");
      Serial.printf("    Minimum = %lums, Maximum = %lums, Average = %.2fms\n",response.MinResponseTime,response.MaxResponseTime,response.AvgResponseTime);
    }
    return true;
  });
 }
void loop()
{
  if(pinger.Ping(IPAddress(8,8,8,8)) == false){Serial.println("Error during last ping command.");}


  delay(10000);
}
