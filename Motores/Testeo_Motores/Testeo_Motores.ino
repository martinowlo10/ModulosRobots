// Testeo_Motores.ino - Control básico de motores DC con L298N
// Open Lambot - Testeo de motores

// ====== FALTA AJUSTARLOS ======
#define MOTOR_IZQ_ENA 5    // PWM velocidad motor izquierdo
#define MOTOR_IZQ_IN1 4    // Control dirección 1 izquierdo
#define MOTOR_IZQ_IN2 3    // Control dirección 2 izquierdo

#define MOTOR_DER_ENB 6    // PWM velocidad motor derecho  
#define MOTOR_DER_IN3 7    // Control dirección 1 derecho
#define MOTOR_DER_IN4 8    // Control dirección 2 derecho
// ======================================================

void setup() {
  Serial.begin(9600);
  
  // Configurar pines de motores como salidas
  pinMode(MOTOR_IZQ_ENA, OUTPUT);
  pinMode(MOTOR_IZQ_IN1, OUTPUT);
  pinMode(MOTOR_IZQ_IN2, OUTPUT);
  
  pinMode(MOTOR_DER_ENB, OUTPUT);
  pinMode(MOTOR_DER_IN3, OUTPUT);
  pinMode(MOTOR_DER_IN4, OUTPUT);
  
  // Inicializar motores detenidos
  detenerMotores();
  
  Serial.println("=== TESTEO DE MOTORES OPEN LAMBOT ===");
  Serial.println("Comandos disponibles:");
  Serial.println("w - Avanzar");
  Serial.println("s - Retroceder");
  Serial.println("a - Girar izquierda");
  Serial.println("d - Girar derecha");
  Serial.println("q - Giro suave izquierda");
  Serial.println("e - Giro suave derecha");
  Serial.println("x - Detener");
  Serial.println("1 - Velocidad lenta (50)");
  Serial.println("2 - Velocidad media (100)");
  Serial.println("3 - Velocidad normal (150)");
  Serial.println("4 - Velocidad rápida (200)");
  Serial.println("5 - Velocidad máxima (255)");
  Serial.println("========================");
}

// Función para controlar motor izquierdo
void controlMotorIzq(int velocidad, bool adelante) {
  analogWrite(MOTOR_IZQ_ENA, velocidad);
  digitalWrite(MOTOR_IZQ_IN1, adelante ? HIGH : LOW);
  digitalWrite(MOTOR_IZQ_IN2, adelante ? LOW : HIGH);
}

// Función para controlar motor derecho
void controlMotorDer(int velocidad, bool adelante) {
  analogWrite(MOTOR_DER_ENB, velocidad);
  digitalWrite(MOTOR_DER_IN3, adelante ? HIGH : LOW);
  digitalWrite(MOTOR_DER_IN4, adelante ? LOW : HIGH);
}

// Función para detener ambos motores
void detenerMotores() {
  analogWrite(MOTOR_IZQ_ENA, 0);
  analogWrite(MOTOR_DER_ENB, 0);
  digitalWrite(MOTOR_IZQ_IN1, LOW);
  digitalWrite(MOTOR_IZQ_IN2, LOW);
  digitalWrite(MOTOR_DER_IN3, LOW);
  digitalWrite(MOTOR_DER_IN4, LOW);
}

// Función para avanzar
void avanzar(int velocidad) {
  controlMotorIzq(velocidad, true);
  controlMotorDer(velocidad, true);
  Serial.print("AVANZANDO - Velocidad: ");
  Serial.println(velocidad);
}

// Función para retroceder
void retroceder(int velocidad) {
  controlMotorIzq(velocidad, false);
  controlMotorDer(velocidad, false);
  Serial.print("RETROCEDIENDO - Velocidad: ");
  Serial.println(velocidad);
}

// Función para girar izquierda (giro sobre sí mismo)
void girarIzquierda(int velocidad) {
  controlMotorIzq(velocidad, false);
  controlMotorDer(velocidad, true);
  Serial.print("GIRO IZQUIERDA - Velocidad: ");
  Serial.println(velocidad);
}

// Función para girar derecha (giro sobre sí mismo)
void girarDerecha(int velocidad) {
  controlMotorIzq(velocidad, true);
  controlMotorDer(velocidad, false);
  Serial.print("GIRO DERECHA - Velocidad: ");
  Serial.println(velocidad);
}

// Función para giro suave izquierda (curva)
void giroSuaveIzquierda(int velocidad) {
  controlMotorIzq(velocidad/2, true);
  controlMotorDer(velocidad, true);
  Serial.print("GIRO SUAVE IZQUIERDA - Velocidad: ");
  Serial.println(velocidad);
}

// Función para giro suave derecha (curva)
void giroSuaveDerecha(int velocidad) {
  controlMotorIzq(velocidad, true);
  controlMotorDer(velocidad/2, true);
  Serial.print("GIRO SUAVE DERECHA - Velocidad: ");
  Serial.println(velocidad);
}

// Variable para controlar velocidad
int velocidad = 150;  // Velocidad media por defecto

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();
    
    switch (comando) {
      case 'w':  // Avanzar
        avanzar(velocidad);
        break;
        
      case 's':  // Retroceder
        retroceder(velocidad);
        break;
        
      case 'a':  // Girar izquierda (sobre sí mismo)
        girarIzquierda(velocidad);
        break;
        
      case 'd':  // Girar derecha (sobre sí mismo)
        girarDerecha(velocidad);
        break;
        
      case 'q':  // Giro suave izquierda (curva)
        giroSuaveIzquierda(velocidad);
        break;
        
      case 'e':  // Giro suave derecha (curva)
        giroSuaveDerecha(velocidad);
        break;
        
      case 'x':  // Detener
        detenerMotores();
        Serial.println("Motores DETENIDOS");
        break;
        
      case '1': 
        velocidad = 50;
        Serial.print("Velocidad cambiada a: ");
        Serial.println(velocidad);
        break;
        
      case '2': 
        velocidad = 100;
        Serial.print("Velocidad cambiada a: ");
        Serial.println(velocidad);
        break;
        
      case '3': 
        velocidad = 150;
        Serial.print("Velocidad cambiada a: ");
        Serial.println(velocidad);
        break;
        
      case '4': 
        velocidad = 200;
        Serial.print("Velocidad cambiada a: ");
        Serial.println(velocidad);
        break;
        
      case '5': 
        velocidad = 255;
        Serial.print("Velocidad cambiada a: ");
        Serial.println(velocidad);
        break;
      
      default:
        Serial.println("Comando no reconocido");
        break;
    }
  }
  
  delay(10);
}
