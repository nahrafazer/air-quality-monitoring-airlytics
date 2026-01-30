//gp2y1010au0fread.ino

float convertpm25ToISPU(float x) {
  float Ia, Ib, Xa, Xb;
  float I;

  if (x <= 15.5) {
    Ia = 50; Ib = 0; Xa = 15.5; Xb = 0;
  } else if (x <= 55.4) {
    Ia = 100; Ib = 50; Xa = 55.4; Xb = 15.5;
  } else if (x <= 150.4) {
    Ia = 200; Ib = 100; Xa = 150.4; Xb = 55.4;
  } else if (x <= 250.4) {
    Ia = 300; Ib = 200; Xa = 250.4; Xb = 150.4;
  } else if (x <= 500) {
    Ia = 300; Ib = 300; Xa = 500; Xb = 250.4;
  } else {
    return 301; // 300++
  }

  I = ((Ia - Ib) / (Xa - Xb)) * (x - Xb) + Ib;
  return I;
}

float convertpm10ToISPU(float x) {
  float Ia, Ib, Xa, Xb;
  float I;

  if (x <= 50) {
    Ia = 50; Ib = 0; Xa = 50; Xb = 0;
  } else if (x <= 150) {
    Ia = 100; Ib = 50; Xa = 150; Xb = 50;
  } else if (x <= 350) {
    Ia = 200; Ib = 100; Xa = 350; Xb = 150;
  } else if (x <= 420) {
    Ia = 300; Ib = 200; Xa = 420; Xb = 350;
  } else if (x <= 500) {
    Ia = 300; Ib = 300; Xa = 500; Xb = 420;
  } else {
    return 301; // 300++
  }

  I = ((Ia - Ib) / (Xa - Xb)) * (x - Xb) + Ib;
  return I;
}

void readPM25() {
  int total = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    digitalWrite(GP2Y_LED_PIN, LOW);
    delayMicroseconds(280);

    total += analogRead(GP2Y_ANALOG_PIN);

    delayMicroseconds(40);
    digitalWrite(GP2Y_LED_PIN, HIGH);
    delayMicroseconds(9680);
  }

  sensorValue_PM25 = total / NUM_SAMPLES;
  voutPM25 = (sensorValue_PM25 / 4095.0) * 3.3;
  // pm25ugm3 = 219.51 * voutPM25 - 11.023;
  // pm25ugm3 = 217.77 * voutPM25 - 8.3577;
  pm25ugm3 = 218.7 * voutPM25 - 9.7854;
  pm25ISPU = convertpm25ToISPU(pm25ugm3);

  // Serial.print("Nilai Rata-rata PM2.5: ");
  // Serial.println(sensorValue_PM25);
}

void readPM10() {
  int total = 0;
  
  for (int i = 0; i < NUM_SAMPLES; i++) {
    digitalWrite(GP2Y_LED_PIN, LOW);
    delayMicroseconds(280);

    total += analogRead(GP2Y_ANALOG_PIN);

    delayMicroseconds(40);
    digitalWrite(GP2Y_LED_PIN, HIGH);
    delayMicroseconds(9680);
  }

  sensorValue_PM10 = total / NUM_SAMPLES;
  // pm10ugm3 = total / NUM_SAMPLES;
  voutPM10 = (sensorValue_PM10 / 4095.0) * 3.3; 
  // pm10ugm3 = 287.02 * voutPM10 - 13.844;
  pm10ugm3 = 288.27 * voutPM10 - 15.753;
  pm10ISPU = convertpm10ToISPU(pm10ugm3);
  // Serial.print("Nilai Rata-rata PM10: ");
  // Serial.println(sensorValue_PM10);
}