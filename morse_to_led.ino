// Mapa de Código Morse
const char *morse[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--.."
};

bool waitingForResponse = false;

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serie a 9600 baudios
  pinMode(LED_BUILTIN, OUTPUT); // Configura el pin LED como salida
  Serial.println("Ingrese una oración para traducir a Morse:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Lee la entrada del usuario
    input.trim(); // Elimina espacios en blanco al principio y al final

    if (waitingForResponse) {
      if (input.equalsIgnoreCase("Y")) {
        Serial.println("Y: Ingrese una oración para traducir a Morse:");
        waitingForResponse = false;
      } else if (input.equalsIgnoreCase("N")) {
        Serial.println("N: Programa terminado.");
        while (true); // Detener el programa
      } else {
        Serial.println("Respuesta no válida. ¿Quiere traducir otra oración? (Y/N):");
      }
    } else {
      input.toUpperCase(); // Convierte la oración a mayúsculas
      Serial.println("Traduciendo oración...");
      translateToMorse(input);
      Serial.println("¿Quiere traducir otra oración? (Y/N):");
      waitingForResponse = true;
    }
  }
}

void translateToMorse(String sentence) {
  for (int i = 0; i < sentence.length(); i++) {
    char c = sentence.charAt(i);
    if (c >= 'A' && c <= 'Z') {
      flashMorse(morse[c - 'A']);
    } else if (c == ' ') {
      delay(700); // Pausa para espacio entre palabras
    }
  }
  Serial.println("Traducción completada.");
}

void flashMorse(const char *code) {
  while (*code) {
    if (*code == '.') {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200); // Punto: LED encendido por 200 ms
      digitalWrite(LED_BUILTIN, LOW);
      delay(200); // Espacio entre puntos y rayas
    } else if (*code == '-') {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(600); // Raya: LED encendido por 600 ms
      digitalWrite(LED_BUILTIN, LOW);
      delay(200); // Espacio entre puntos y rayas
    }
    code++;
  }
  delay(600); // Pausa entre letras
}