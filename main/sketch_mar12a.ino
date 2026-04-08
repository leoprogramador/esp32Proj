#include <TFT_eSPI.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ===== IMAGENS =====
#include "PASSO0.h"
#include "PASSO1.h"
#include "PASSO2.h"
#include "PASSO3.h"
#include "PASSO4.h"
#include "PASSO5.h"
#include "PASSO6.h"
#include "PASSO7.h"
#include "PASSO8.h"

TFT_eSPI tft = TFT_eSPI();
HardwareSerial dfSerial(2);
DFRobotDFPlayerMini player;

// ===== HC-SR04 =====
const int trigPin = 19;
const int echoPin = 21;
const float DISTANCIA_DET = 4.0;
bool sensorAtivo = false;

// ===== POTENCIÓMETRO =====
const int potPin = 34;
int volume = -1;

// ===== CONTROLE =====
int contador = 0;
bool iniciou = false;
unsigned long tempoAnterior = 0;

// ===== TEMPOS =====
const unsigned long intervaloNormal = 6700;
const unsigned long intervaloCurto = 4000;

// ===== ARRAYS =====
const uint16_t* imagens[7] = {
  PASSO1, PASSO2, PASSO3, PASSO4, PASSO5, PASSO6, PASSO7
};

const int larguras[7] = {
  PASSO1_WIDTH, PASSO2_WIDTH, PASSO3_WIDTH,
  PASSO4_WIDTH, PASSO5_WIDTH, PASSO6_WIDTH, PASSO7_WIDTH
};

const int alturas[7] = {
  PASSO1_HEIGHT, PASSO2_HEIGHT, PASSO3_HEIGHT,
  PASSO4_HEIGHT, PASSO5_HEIGHT, PASSO6_HEIGHT, PASSO7_HEIGHT
};

// ===== COR =====
uint16_t swapColor(uint16_t c) {
  return (c >> 8) | (c << 8);
}

// ===== ZOOM =====
void pushImageZoom(const uint16_t* img, int w, int h) {
  int targetW = 480;
  int targetH = 320;

  for (int y = 0; y < targetH; y++) {
    int srcY = y * h / targetH;
    for (int x = 0; x < targetW; x++) {
      int srcX = x * w / targetW;
      tft.drawPixel(x, y, swapColor(img[srcY * w + srcX]));
    }
  }
}

// ===== DISTÂNCIA =====
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 30000);
  float distancia = duracao / 58.0;

  if (distancia == 0) distancia = 300;
  return distancia;
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(potPin, INPUT);

  // ===== TELA INICIAL =====
  tft.fillScreen(TFT_BLACK);
  pushImageZoom(PASSO0, PASSO0_WIDTH, PASSO0_HEIGHT);

  // ===== DFPLAYER =====
  dfSerial.begin(9600, SERIAL_8N1, 27, 26);
  if (player.begin(dfSerial)) {
    player.volume(15);
    Serial.println("DFPlayer OK");
  }
}

void loop() {

  // ===== VOLUME =====
  int leitura = analogRead(potPin);
  int novoVolume = map(leitura, 0, 4095, 0, 30);

  if (novoVolume != volume) {
    volume = novoVolume;
    player.volume(volume);
  }

  // ===== SENSOR =====
  float distancia = medirDistancia();

  if (!iniciou && distancia <= DISTANCIA_DET && !sensorAtivo) {
    iniciou = true;
    contador = 0;
    tempoAnterior = millis();
    sensorAtivo = true;

    pushImageZoom(imagens[0], larguras[0], alturas[0]);
    player.play(1);

    Serial.println("Iniciou ciclo");
  }

  if (distancia > DISTANCIA_DET + 1.0) {
    sensorAtivo = false;
  }

  // ===== CONTROLE DE TEMPO DINÂMICO =====
  unsigned long intervaloAtual = intervaloNormal;

  // 👉 PASSO6 → PASSO7 mais rápido
  if ((contador == 5)||(contador == 6)||(contador == 4)) {
    intervaloAtual = intervaloCurto;
  }

  // ===== TROCA DE IMAGENS =====
  if (iniciou && millis() - tempoAnterior >= intervaloAtual) {

    tempoAnterior = millis();
    contador++;

    // PASSOS 1 → 7
    if (contador < 7) {
      pushImageZoom(imagens[contador], larguras[contador], alturas[contador]);
    }
    // PASSO FINAL (8)
    else if (contador == 7) {
      pushImageZoom(PASSO8, PASSO8_WIDTH, PASSO8_HEIGHT);
      Serial.println("Parabéns!");
      // player.play(8); // opcional
    }
    // FIM → volta para início
    else {
      iniciou = false;

      tft.fillScreen(TFT_BLACK);
      pushImageZoom(PASSO0, PASSO0_WIDTH, PASSO0_HEIGHT);

      Serial.println("Voltou ao início");
    }
  }
}