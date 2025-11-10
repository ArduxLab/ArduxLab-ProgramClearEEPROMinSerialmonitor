/**
 * PROGRAM CLEAR EEPROM VIA SERIAL COMMAND
 * Upload program ini, lalu ketik 'CLEAR' di Serial Monitor
 */

#include <EEPROM.h>

#define EEPROM_SIZE 512

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("EEPROM CLEANER - Serial Command Version");
  Serial.println("Ketik 'CLEAR' untuk menghapus semua data EEPROM");
  Serial.println("Ketik 'CHECK' untuk melihat data EEPROM");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readString();
    command.trim();
    
    if (command == "CLEAR" || command == "clear") {
      clearEEPROM();
    }
    else if (command == "CHECK" || command == "check") {
      checkEEPROM();
    }
    else {
      Serial.println("❌ Command tidak dikenali");
      Serial.println("✅ Gunakan: CLEAR atau CHECK");
    }
  }
}

void clearEEPROM() {
  Serial.println("🗑️  Menghapus EEPROM...");
  
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  EEPROM.end();
  
  Serial.println("✅ EEPROM berhasil dihapus!");
  Serial.println("🔁 Reset ESP32 manual lalu upload program utama");
}

void checkEEPROM() {
  Serial.println("📋 Data EEPROM:");
  
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0; i < EEPROM_SIZE; i += 16) {
    Serial.print("0x");
    if (i < 16) Serial.print("0");
    Serial.print(i, HEX);
    Serial.print(": ");
    
    for (int j = 0; j < 16; j++) {
      byte value = EEPROM.read(i + j);
      if (value < 16) Serial.print("0");
      Serial.print(value, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  EEPROM.end();
}