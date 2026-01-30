//mics6814read.ino
float convertNo2ToISPU(float x) {
  float Ia, Ib, Xa, Xb;
  float I;

  if (x <= 80) {
    Ia = 50; Ib = 0; Xa = 80; Xb = 0;
  } else if (x <= 200) {
    Ia = 100; Ib = 50; Xa = 200; Xb = 80;
  } else if (x <= 1130) {
    Ia = 200; Ib = 100; Xa = 1130; Xb = 200;
  } else if (x <= 2260) {
    Ia = 300; Ib = 200; Xa = 2260; Xb = 1130;
  } else if (x <= 3000) {
    Ia = 300; Ib = 300; Xa = 3000; Xb = 2260;
  } else {
    return 301; // 300++
  }

  I = ((Ia - Ib) / (Xa - Xb)) * (x - Xb) + Ib;
  return I;
}

float convertCOToISPU(float x) {
  float Ia, Ib, Xa, Xb;
  float I;

  if (x <= 4000) {
    Ia = 50; Ib = 0; Xa = 4000; Xb = 0;
  } else if (x <= 8000) {
    Ia = 100; Ib = 50; Xa = 8000; Xb = 4000;
  } else if (x <= 15000) {
    Ia = 200; Ib = 100; Xa = 15000; Xb = 8000;
  } else if (x <= 30000) {
    Ia = 300; Ib = 200; Xa = 30000; Xb = 15000;
  } else if (x <= 45000) {
    Ia = 300; Ib = 300; Xa = 45000; Xb = 30000;
  } else {
    return 301; // 300++
  }

  I = ((Ia - Ib) / (Xa - Xb)) * (x - Xb) + Ib;
  return I;
}

void readCO() {
  sensorValue_CO = analogRead(CO_ANALOG_PIN);
  coPPM = 0.0839 * (4095 - sensorValue_CO) - 4.103;
  // coPPM = 0.078 * (4095 - sensorValue_CO) - 1.6902;

    if (coPPM < 0) {
    coPPM = 0;
  }
  cougm3 = coPPM * (coMolarMass / molarVolume) * 1000;
  coISPU = convertCOToISPU(no2ugm3);

  // Serial.print("Nilai Analog CO: ");
  // Serial.println(sensorValue_CO);
  // Serial.print("CO (estimasi): ");
  // Serial.print(sensorValue_CO);
  // Serial.println(" ppm");
}

void readNO2() {
  sensorValue_NO2 = analogRead(NO2_ANALOG_PIN);
  
  float voutNO2 = (sensorValue_PM10 / 4095.0) * 3.3;
  no2PPM = 3.66445 * voutNO2 - 2.09660;

  if (no2PPM < 0.05) {
    no2PPM = 0;
  } else if (no2PPM > 10.0) {
    no2PPM = 10.0;
  }
  no2ugm3 = no2PPM * (no2MolarMass / molarVolume) * 1000;
  no2ISPU = convertNo2ToISPU(no2ugm3);

  // Serial.print("Nilai Analog NO2: ");
  // Serial.println(sensorValue_NO2);
  // Serial.print("NO2 (estimasi): ");
  // Serial.print(no2PPM);
  // Serial.println(" ppm");
}