# Projeto-IOT
--- 

## Autores
- Ana Clara Gierse Raymundo
- Erica Gonçalves de Oliveira
- Luana Domingo Branco
- Victor Luiz de Sá Alves
## Sobre o Projeto

Este projeto apresenta o desenvolvimento de um **sistema IoT integrado** para monitoramento de idosos, combinando:

- Botão de emergência manual  
- Detecção automática de quedas via **acelerômetro**
- Notificações instantâneas via **WhatsApp**
- Armazenamento histórico no **InfluxDB**
- Visualização em tempo real no **Grafana**

O sistema é composto por **dois ESP32 simulados no Wokwi**, que enviam dados através de **MQTT** para o **Node-RED**, responsável pela lógica de processamento e disparo das notificações.

![10a9b45d-4545-4cb7-a5aa-963be400eb45](https://github.com/user-attachments/assets/4a931465-fc7c-4cab-bd67-3f4234e48777)
Dispositivo com aceleometro

![9fa1aae0-e140-4b7f-b4ab-a5c3e8e2f6f6](https://github.com/user-attachments/assets/5f8cf734-7ca3-496b-84f6-ab175ccc8367)
Dispositivo com botão

![de6336c3-d2f6-4b42-acd3-b5176ceb85fa](https://github.com/user-attachments/assets/e486c649-1287-4703-89fa-375f70f02031)
Nó botão

![3a930339-e1ad-456a-aaa9-8481f4068dc2](https://github.com/user-attachments/assets/342c50b4-9fa6-4476-9a9c-b81cdaa5db9c)
Nó acelerometro

Trata-se de uma solução de **baixo custo**, alinhada aos ODS 3 e 11 da Agenda 2030 da ONU e voltada à segurança da população idosa.

---

##  Componentes Utilizados

###  Hardware (Simulado no Wokwi)
- ESP32 (2 unidades)  
- Botão 
- Acelerômetro ADXL345  

###  Software & Serviços
- Wokwi (simulação dos dispositivos)  
- MQTT – HiveMQ Broker  
- Node-RED (processamento e lógica do sistema)  
- API do WhatsApp (alertas em tempo real)  
- InfluxDB (banco de dados de séries temporais)  
- Grafana (dashboards interativos)

---

##  Como Executar o Projeto

### 1 Clone o repositório
```bash
git clone https://github.com/anagierse/Projeto-IOT.git
cd Projeto-IOT
```
### 2 Acesse os códigos no Wokwi

Os links dos simuladores estão na pasta /wokwi/.

### 3 Configure o Node-RED

Instale o Node-RED:

```bash
npm install -g node-red
```

Importe o fluxo localizado em:
```bash
/node-red/fluxo.json
```

### 4 Configure o InfluxDB

Crie o bucket com o nome: Projeto_IOT

Configure o token e a organização no Node-RED

### 5 Configure o WhatsApp

Defina o número do cuidador no fluxo Node-RED e faça de acordo com a documentação do node parea coletar o token:


### 6 Execute tudo

Inicie o Node-RED

Abra o Wokwi

Visualize os dados no Grafana

Teste o botão e simule quedas no acelerômetro

