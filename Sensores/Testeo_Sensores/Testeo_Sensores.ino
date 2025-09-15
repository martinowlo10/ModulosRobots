// Testeo_Sensores.ino - Para testeo continuo SIN calibración

#define PIN_Sensor_ON 7
#define BUZZER_PIN 8

// Usamos los valores de calibración que ya obtuviste
int v_s_min[6] = { 350, 340, 330, 320, 310, 300 };  // EJEMPLO - usa tus valores reales
int v_s_max[6] = { 850, 840, 830, 820, 810, 800 };  // EJEMPLO - usa tus valores reales

volatile int s_p[6];
boolean online;
int pos;
int l_pos;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_Sensor_ON, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("=== MODO TESTEO SENSORES ===");
  Serial.println("Leyendo valores sin recalibrar...");
}

void readSensors() {
  digitalWrite(PIN_Sensor_ON, HIGH);
  delay(10);  // Pequeña estabilización
  
  volatile int s[6];
  s[0] = analogRead(A0);  // ¡VERIFICA TUS PINES REALES!
  s[1] = analogRead(A1);
  s[2] = analogRead(A2);
  s[3] = analogRead(A3);
  s[4] = analogRead(A4);
  s[5] = analogRead(A5);

  for (int i = 0; i < 6; i++) {
    if (s[i] < v_s_min[i]) s[i] = v_s_min[i];
    if (s[i] > v_s_max[i]) s[i] = v_s_max[i];
    s_p[i] = map(s[i], v_s_min[i], v_s_max[i], 100, 0);
  }

  volatile int sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];
  online = (sum > 100);
  
  digitalWrite(PIN_Sensor_ON, LOW);
}

int GetPos() {
  readSensors();
  int prom = -2.5 * s_p[0] - 1.5 * s_p[1] - 0.5 * s_p[2] + 0.5 * s_p[3] + 1.5 * s_p[4] + 2.5 * s_p[5];
  int sum = s_p[0] + s_p[1] + s_p[2] + s_p[3] + s_p[4] + s_p[5];

  if (online) {
    pos = int(100.0 * prom / sum);
  } else {
    pos = (l_pos < 0) ? -255 : 255;
  }
  l_pos = pos;
  return pos;
}

void loop() {
  int currentPos = GetPos();
  
  // Mostrar valores individuales
  Serial.print("Sensores: ");
  for(int i = 0; i < 6; i++) {
    Serial.print(s_p[i]);
    Serial.print("\t");
  }
  
  // Mostrar posición relativa
  Serial.print(" | Posición: ");
  Serial.print(currentPos);
  
  // Mostrar estado online/offline
  Serial.print(" | ");
  Serial.println(online ? "EN LÍNEA" : "FUERA DE LÍNEA");
  
  delay(200);  // Lectura cada 200ms
}
