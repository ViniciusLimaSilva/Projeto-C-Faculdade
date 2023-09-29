#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2); // Endere�o do display I2C e tamanho

void setup() {
  Serial.begin(9600); // Inicializa a comunica��o serial
  lcd.init(); // Inicializa o display
  lcd.backlight(); // Liga o backlight do display
  lcd.setCursor(0, 0);
  lcd.print("Valor:");
}

void loop() {
  int valorPotenciometro = analogRead(A0); // L� o valor do potenci�metro
  Serial.print("Valor do Potenci�metro: ");
  Serial.println(valorPotenciometro); // Exibe o valor no monitor serial
  lcd.setCursor(0, 1);
  lcd.print("           "); // Limpa a linha do display
  lcd.setCursor(0, 1);
  lcd.print(valorPotenciometro);
  delay(1000); // Aguarda 1 segundo antes de ler novamente
}
