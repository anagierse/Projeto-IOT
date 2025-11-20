#include <WiFi.h>
#include <Wire.h>
#include "MPU6050.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>

MPU6050 mpu;

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "TESTMACK10428453/Queda";

const int PINO_BUZZER = 13;
bool quedaDetectada = false;
unsigned long tempoUltimaQueda = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32_MPU6050_Queda")) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando em 5s...");
      delay(5000);
    }
  }
}

void enviarAlertaQueda() {
  Serial.println("🚨 QUEDA DETECTADA!");
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(PINO_BUZZER, HIGH);
    delay(200);
    digitalWrite(PINO_BUZZER, LOW);
    delay(100);
  }

  if (!client.connected()) {
    conectarMQTT();
  }
  
  StaticJsonDocument<200> doc;
  
  doc["evento"] = "emergencia";
  doc["tipo"] = "queda_detectada";
  doc["dispositivo"] = "ESP32_MPU6050_Queda";
  doc["timestamp"] = millis();
  doc["status"] = "ativo";
  doc["valor"] = 1;
  
  String mensagemJSON;
  serializeJson(doc, mensagemJSON);
  
  bool enviado = client.publish(mqtt_topic, mensagemJSON.c_str());
  
  Serial.print("Mensagem MQTT publicada: ");
  Serial.println(mensagemJSON);

  if (enviado) {
    Serial.println("MQTT enviado com sucesso!");
  } else {
    Serial.println("Falha no envio MQTT!");
  }
}

bool detectarQueda(float ax, float ay, float az) {
  float total = sqrt(ax*ax + ay*ay + az*az);
  return (total > 2.5f);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_BUZZER, OUTPUT);
  
  Wire.begin(21,22);
  mpu.initialize();
  
  Serial.print("Conectando WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Conectado!");
  
  client.setServer(mqtt_server, mqtt_port);
  
  Serial.println("✅ Sistema de detecção de quedas pronto!");
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();
  
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  if (quedaDetectada && (millis() - tempoUltimaQueda > 5000)) {
    quedaDetectada = false;
    Serial.println("✅ Sistema resetado");
  }

  if (!quedaDetectada && detectarQueda(ax_g, ay_g, az_g)) {
    enviarAlertaQueda();
    quedaDetectada = true;
    tempoUltimaQueda = millis();
  }

  delay(100);
}