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

