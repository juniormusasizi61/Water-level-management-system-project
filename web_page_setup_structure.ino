void handleSetMaxDistance() {
  if (server.hasArg("max_distance")) {
    maxDistance = server.arg("max_distance").toInt();
    Serial.println("Maximum distance set to: " + String(maxDistance));
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleSetThreshold() {
  if (server.hasArg("threshold")) {
    threshold = server.arg("threshold").toInt();
    Serial.println("Threshold set to: " + String(threshold));
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleSetPhoneNumber() {
  if (server.hasArg("phone_number")) {
    phoneNumber = server.arg("phone_number");
    Serial.println("Phone number set to: " + phoneNumber);
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}
void handleWaterLevel() {
  String json = "{\"level\": " + String(waterLevel) + "}";
  server.send(200, "application/json", json);
}