#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "wifiname";
const char *password = "wifipassword";
const int relayPin = D1;  

ESP8266WebServer server(80);

IPAddress staticIP(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

bool isAdminAuthenticated = false;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi-network...");
  }

  Serial.println("WiFi-Connected!");

  server.on("/", HTTP_GET, login);
  server.on("/controlpanel", HTTP_GET, handlePower);
  server.on("/turnon", HTTP_GET, handleTurnOn);
  server.on("/checklogin", HTTP_POST, handleCheckLogin);
  server.on("/failedlogin", HTTP_GET, handlefailedlogin);


  server.begin();
}

void loop() {
  server.handleClient();
}

void login() {
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
  html += "    <meta charset='UTF-8'>";
  html += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "    <title>Login Page</title>";
  html += "    <style>";
  html += "        * {";
  html += "            margin: 0;";
  html += "            padding: 0;";
  html += "            box-sizing: border-box;";
  html += "        }";
  html += "        body {";
  html += "            font-family: Arial, sans-serif;";
  html += "            background-color: #000;";
  html += "            color: #fff;";
  html += "            margin: 0;";
  html += "            padding: 0;";
  html += "        }";
  html += "        .container {";
  html += "            max-width: 400px;";
  html += "            margin: 0 auto;";
  html += "            padding: 20px;";
  html += "            background-color: #111;";
  html += "            border-radius: 10px;";
  html += "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);";
  html += "        }";
  html += "        h1 {";
  html += "            font-size: 24px;";
  html += "            margin-bottom: 10px;";
  html += "            color: #02ff00;";
  html += "            text-align: center;";
  html += "        }";
  html += "        form {";
  html += "            text-align: center;";
  html += "            margin-bottom: 20px;";
  html += "        }";
  html += "        input[type='text'], input[type='password'] {";
  html += "            width: 100%;";
  html += "            padding: 10px;";
  html += "            margin: 5px 0;";
  html += "            display: inline-block;";
  html += "            border: 2px solid #02ff00;";
  html += "            border-radius: 5px;";
  html += "            background-color: #222;";
  html += "            color: #fff;";
  html += "        }";
  html += "        input[type='submit'] {";
  html += "            padding: 10px 20px;";
  html += "            background-color: #02ff00;";
  html += "            color: #000;";
  html += "            border: none;";
  html += "            border-radius: 5px;";
  html += "            cursor: pointer;";
  html += "            font-size: 16px;";
  html += "            transition: background-color 0.3s ease;";
  html += "        }";
  html += "        input[type='submit']:hover {";
  html += "            background-color: #0056b3;";
  html += "            transform: scale(1.05);";
  html += "        }";
  html += "        p {";
  html += "            text-align: center;";
  html += "            margin-top: 10px;";
  html += "            font-size: 16px;";
  html += "        }";
  html += "    </style>";
  html += "</head>";
  html += "<body>";
  html += "    <div class='container'>";
  html += "        <h1>Login Page</h1>";
  html += "        <form action='/checklogin' method='post'>";
  html += "            Username: <input type='text' name='username'><br>";
  html += "            Password: <input type='password' name='password'><br>";
  html += "            <input type='submit' value='Login'>";
  html += "        </form>";

  server.send(200, "text/html", html);
}

  
void handlefailedlogin() {
String html = "<!DOCTYPE html>";
    html += "<html lang='en'>";
    html += "<head>";
    html += "    <meta charset='UTF-8'>";
    html += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "    <title>Login Page</title>";
    html += "    <style>";
    html += "        * {";
    html += "            margin: 0;";
    html += "            padding: 0;";
    html += "            box-sizing: border-box;";
    html += "        }";
    html += "        body {";
    html += "            font-family: Arial, sans-serif;";
    html += "            background-color: #000;";
    html += "            color: #fff;";
    html += "            margin: 0;";
    html += "            padding: 0;";
    html += "        }";
    html += "        .container {";
    html += "            max-width: 400px;";
    html += "            margin: 0 auto;";
    html += "            padding: 20px;";
    html += "            background-color: #111;";
    html += "            border-radius: 10px;";
    html += "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);";
    html += "        }";
    html += "        h1 {";
    html += "            font-size: 24px;";
    html += "            margin-bottom: 10px;";
    html += "            color: #ff0000;";
    html += "            text-align: center;";
    html += "        }";
    html += "        form {";
    html += "            text-align: center;";
    html += "            margin-bottom: 20px;";
    html += "        }";
    html += "        input[type='text'], input[type='password'] {";
    html += "            width: 100%;";
    html += "            padding: 10px;";
    html += "            margin: 5px 0;";
    html += "            display: inline-block;";
    html += "            border: 2px solid #ff0000;";
    html += "            border-radius: 5px;";
    html += "            background-color: #222;";
    html += "            color: #fff;";
    html += "        }";
    html += "        input[type='submit'] {";
    html += "            padding: 10px 20px;";
    html += "            background-color: #ff0000;";
    html += "            color: #fff;";
    html += "            border: none;";
    html += "            border-radius: 5px;";
    html += "            cursor: pointer;";
    html += "            font-size: 16px;";
    html += "            transition: background-color 0.3s ease;";
    html += "        }";
    html += "        input[type='submit']:hover {";
    html += "            background-color: #800000;";
    html += "            transform: scale(1.05);";
    html += "        }";
    html += "    </style>";
    html += "</head>";
    html += "<body>";
    html += "    <div class='container'>";
    html += "        <h1>Login Page</h1>";
    html += "        <p>Incorrect username or password. Please try again.</p>";
    html += "        <form action='/checklogin' method='post'>";
    html += "            Username: <input type='text' name='username'><br>";
    html += "            Password: <input type='password' name='password'><br>";
    html += "            <input type='submit' value='Login'>";
    html += "        </form>";
    html += "    </div>";
    html += "</body>";
    html += "</html>";

  server.send(200, "text/html", html);
}

void handleCheckLogin() {
  String username = server.arg("username");
  String password = server.arg("password");

  if (username.equals("admin") && password.equals("admin")) {
    isAdminAuthenticated = true;
    server.sendHeader("Location", "/controlpanel", true);
    server.send(302, "text/plain", "");
  } else {
    isAdminAuthenticated = false;
    server.sendHeader("Location", "/failedlogin", true);
    server.send(302, "text/plain", "");
  }
}

void handlePower() {
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
  html += "    <meta charset='UTF-8'>";
  html += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "    <title>Computer Control</title>";
  html += "    <style>";
  html += "        * {";
  html += "            margin: 0;";
  html += "            padding: 0;";
  html += "            box-sizing: border-box;";
  html += "        }";
  html += "        body {";
  html += "            font-family: Arial, sans-serif;";
  html += "            background-color: #000;";
  html += "            color: #fff;";
  html += "            margin: 0;";
  html += "            padding: 0;";
  html += "        }";
  html += "        .container {";
  html += "            max-width: 1200px;";
  html += "            margin: 0 auto;";
  html += "            padding: 20px;";
  html += "            background-color: #111;";
  html += "            border-radius: 10px;";
  html += "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);";
  html += "        }";
  html += "        h2 {";
  html += "            font-size: 24px;";
  html += "            margin-bottom: 10px;";
  html += "            color: #02ff00;";
  html += "            text-align: center;";
  html += "        }";
  html += "        .content {";
  html += "            text-align: center;";
  html += "            margin-bottom: 20px;";
  html += "        }";
  html += "        #turnOn-button {";
  html += "            padding: 20px 40px;";
  html += "            background-color: #02ff00;";
  html += "            color: #000;";
  html += "            border: none;";
  html += "            border-radius: 10px;";
  html += "            cursor: pointer;";
  html += "            font-size: 24px;";
  html += "            transition: background-color 0.3s ease;";
  html += "        }";
  html += "        #turnOn-button:hover {";
  html += "            background-color: #0056b3;";
  html += "            transform: scale(1.05);";
  html += "        }";
  html += "    </style>";
  html += "</head>";
  html += "<body>";
  html += "    <div class='container'>";
  html += "        <div class='content'>";
  html += "            <h2>Computer Control</h2>";
  html += "            <button id='turnOn-button' onclick='turnOn()'>Turn On</button>";
  html += "        </div>";
  html += "    </div>";
  html += "    <script>";
  html += "        function turnOn() {";
  html += "            fetch('/turnon');";
  html += "        }";
  html += "    </script>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}



void handleTurnOn() {
  digitalWrite(relayPin, LOW);
  delay(500);
  digitalWrite(relayPin, HIGH);
  server.send(200, "text/plain", "Computer turned on!");
}
