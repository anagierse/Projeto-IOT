#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* SSIDName = "Wokwi-GUEST";
const char* SSIDPass = "";

const char* BrokerURL = "broker.hivemq.com";
int BrokerPort = 1883;
const char* MQTTClientName = "ESP32_BotaoEmergencia_001";
const char* Topico_Emergencia = "TESTMACK10428453/Ativado";

const int PINO_BOTAO = 4;  
const int PINO_BUZZER = 21; 

WiFiClient espClient;
PubSubClient clienteMQTT(espClient);

void conectarWiFi() {
  Serial.print("Conectando-se ao Wi-Fi");
  Serial.println(SSIDName);
  WiFi.begin(SSIDName, SSIDPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void mqttReconnect() {
  while (!clienteMQTT.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (clienteMQTT.connect(MQTTClientName)) {
      Serial.println(" conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" tentando em 5 segundos...");
      delay(5000);
    }
  }
}

void enviarMensagemEmergencia() {
  if (!clienteMQTT.connected()) mqttReconnect();
  
  StaticJsonDocument<200> doc;
  
  doc["evento"] = "emergencia";
  doc["tipo"] = "botao_ativado";
  doc["dispositivo"] = "ESP32_BotaoEmergencia_001";
  doc["timestamp"] = millis();
  doc["status"] = "ativo";
  doc["valor"] = 1;  
  
  String mensagemJSON;
  serializeJson(doc, mensagemJSON);
  
  clienteMQTT.publish(Topico_Emergencia, mensagemJSON.c_str());
  
  Serial.print("Mensagem MQTT publicada: ");
  Serial.println(mensagemJSON);

  digitalWrite(PINO_BUZZER, HIGH);
  delay(800);
  digitalWrite(PINO_BUZZER, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_BUZZER, OUTPUT);
  digitalWrite(PINO_BUZZER, LOW);

  conectarWiFi();
  clienteMQTT.setServer(BrokerURL, BrokerPort);

  Serial.println("Sistema pronto. Pressione o botão para enviar emergência!");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) conectarWiFi();
  if (!clienteMQTT.connected()) mqttReconnect();
  clienteMQTT.loop();

  static int estadoAnterior = HIGH;
  int leitura = digitalRead(PINO_BOTAO);

  if (leitura == LOW && estadoAnterior == HIGH) { 
    enviarMensagemEmergencia();
  }
  estadoAnterior = leitura;

  delay(50); 
}