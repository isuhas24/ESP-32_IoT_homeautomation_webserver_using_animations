#include<WiFi.h>
#define relay_pin 26
const char* ssid="ESP-32";
const char* password="Wanderer@24";
WiFiServer server(80);
String html="<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>ESP-32 Web-Server</title>\
    <style>\
        h1{\
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;\
            text-align: center;\
        }\
        h3{\
            font-family:'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;\
            text-align: center;\
        }\
        body{\
            background-color:lightblue;\
        }\
        .box{\
            position:relative;\
            margin:auto;\
            width:300px;\
            height:300px;\
        }\
        .circle{\
            position:absolute;\
            width:40%;\
            height:40%;\
            background:white;\
            top:20%;\
            left:25%;\
            margin:0 auto;\
            border-radius:50%;\
        }\
        .trapezoid{\
            position:absolute;\
            background:white;\
            height:30%;\
            width:40%;\
            left:25%;\
            top:42%;\
            -webkit-clip-path:polygon(0 0,100% 0,80% 100%,20% 100%);\
        }\
        .bottom1{\
            position:absolute;\
            height:5%;\
            width:25%;\
            background:grey;\
            top:72%;\
            left:32.5%;\
            z-index: 1;\
        }\
        .bottom1:before{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            left:-8%;\
        }\
        .bottom1:after{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            right:-8%;\
        }\
        .bottom2{\
            position:absolute;\
            height:5%;\
            width:22%;\
            background:grey;\
            top:78%;\
            left:34.5%;\
            z-index: 1;\
        }\
        .bottom2:before{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            left:-8%;\
        }\
        .bottom2:after{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            right:-8%;\
        }\
        .bottom3{\
            position:absolute;\
            height:5%;\
            width:18%;\
            background:grey;\
            top:84%;\
            left:36%;\
            z-index:1;\
        }\
        .bottom3:before{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            left:-8%;\
        }\
        .bottom3:after{\
            content:\"\";\
            height: 100%;\
            width:20%;\
            background:grey;\
            display:block;\
            position:absolute;\
            border-radius:50%;\
            right:-8%;\
        }\
        .halfcircle{\
            height: 20px;\
            width:45px;\
            border-radius:0 0 45px 45px;\
            background:black;\
            margin:0 auto;\
            top:88%;\
            position:relative;\
            left:-5%;\
        }\
        .offbutton{\
            padding:1%;\
            margin-left:75%;\
            background-color:black;\
            color:white;\
            width:20%;\
            font-size:20px;\
            border-radius:10%;\
            cursor:pointer;\
        }\
        .onbutton{\
            padding:1%;\
            margin-left:75%;\
            margin-top:55%;\
            margin-bottom:5%;\
            background-color:black;\
            color:white;\
            width:20%;\
            font-size:20px;\
            border-radius:10%;\
            cursor:pointer;\
        }\
    </style>\
</head>\
<body>\
    <h1>IoT using ESP-32</h1>\
    <h3>LED bulb</h3>\
    <div class=\"box\">\
        <div class=\"circle\"></div>\
        <div class=\"trapezoid\"></div>\
        <div class=\"bottom1\"></div>\
        <div class=\"bottom2\"></div>\
        <div class=\"bottom3\"></div>\
        <div class=\"halfcircle\"></div>\
        <a href=\"/26/on\"><button class=\"onbutton\" onclick=\"on()\">ON</button></a>\
        <a href=\"/26/off\"><button class=\"offbutton\" onclick=\"off()\">OFF</button></a>\
    </div>\
    <script>\
        function on(){\
            var x=document.getElementsByClassName(\"circle\");\
            x[0].style.background=\"yellow\";\
            var v=document.getElementsByClassName(\"trapezoid\");\
            v[0].style.background=\"yellow\";\
        }\
        function off(){\
            var x=document.getElementsByClassName(\"circle\");\
            x[0].style.background=\"white\";\
            var v=document.getElementsByClassName(\"trapezoid\");\
            v[0].style.background=\"white\";\
        }\
    </script>\
</body>\
</html>";
void connect_WiFi(){
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(100);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relay_pin,OUTPUT);
  digitalWrite(relay_pin,HIGH);
  Serial.println("setting soft access point");
  WiFi.softAP(ssid,password);
  IPAddress IP=WiFi.softAPIP();
  Serial.println("AP IP address is:");
  Serial.println(IP);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client=server.available();
  if(client){
    String request=client.readStringUntil('\r');
    if(request.indexOf("GET /26/on")!=-1){
      digitalWrite(relay_pin,LOW);
    }
    if(request.indexOf("GET /26/off")!=-1){
      digitalWrite(relay_pin,HIGH);
    }
    client.print(html);
    request="";
  }
}
