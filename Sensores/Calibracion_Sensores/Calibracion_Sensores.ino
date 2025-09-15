// Calibracion_Sensores.ino - CÓDIGO CORREGIDO

#define PIN_Sensor_ON 7
#define BUZZER_PIN 8

int v_s_min[6] = { 1023, 1023, 1023, 1023, 1023, 1023 };
int v_s_max[6] = { 0, 0, 0, 0, 0, 0 };
volatile int s_p[6];
boolean online;

int pos;
int l_pos;

void beep() {
  tone(BUZZER_PIN, 1000, 100);
  delay(150);
}

void Sensors_init() {
  pinMode(PIN_Sensor_ON, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void calibracion() {
  digitalWrite(PIN_Sensor_ON, HIGH);
  // ... (el resto de tu código de calibración igual)
}

void readSensors() {
  digitalWrite(PIN_Sensor_ON, HIGH);
  // ... (el resto de tu código de lectura igual)
}

int GetPos() {
  // ... (tu código de posición igual)
}

// --- NUEVO: Setup y Loop ---
void setup() {
  Serial.begin(9600);
  Sensors_init();
  calibracion();
  Serial.println("Calibración completada. Iniciando monitoréo...");
}

void loop() {
  int currentPos = GetPos();
  
  Serial.print("Valores: ");
  for(int i = 0; i < 6; i++) {
    Serial.print(s_p[i]);
    Serial.print("\t");
  }
  
  Serial.print(" | Pos: ");
  Serial.print(currentPos);
  Serial.print(" | Online: ");
  Serial.println(online);
  
  delay(200);
}
