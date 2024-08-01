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
