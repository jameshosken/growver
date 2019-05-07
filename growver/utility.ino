void printAnalogValues( int val1, int val2, int val3, int val4) {
  // send to Serial output every 100ms
  // use the Serial Ploter for a good visualization

  if (millis() > refresh_time) {
    Serial.print(val1, 4);
    Serial.print(",");
    Serial.print(val2, 4);
    Serial.print(",");
    Serial.print(val3, 4);
    Serial.print(",");
    Serial.print(val4, 4);
    Serial.println();

    refresh_time = millis() + SERIAL_REFRESH_TIME;
  }
}

void getAnalogValues(int values[4]) {
  // read a reference value from A0 and map it from 0 to 100
  float real_value1 = analogRead(A0) / 1024.0 * 100.0;
  float filtered_value1 = simpleKalmanFilter1.updateEstimate(real_value1);

  float real_value2 = analogRead(A1) / 1024.0 * 100.0;
  float filtered_value2 = simpleKalmanFilter2.updateEstimate(real_value2);

  float real_value3 = analogRead(A2) / 1024.0 * 100.0;
  float filtered_value3 = simpleKalmanFilter3.updateEstimate(real_value3);

  float real_value4 = analogRead(A3) / 1024.0 * 100.0;
  float filtered_value4 = simpleKalmanFilter4.updateEstimate(real_value4);
  
  values[0] = (int)filtered_value1;     //Surely this is bound to lead to off by one problems later.
  values[1] = (int)filtered_value2;
  values[2] = (int)filtered_value3;
  values[3] = (int)filtered_value4;
}
