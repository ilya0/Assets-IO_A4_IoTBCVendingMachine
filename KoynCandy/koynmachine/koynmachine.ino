#include <ESP8266WiFi.h>
#include "Koyn.h"
#define LED_PIN 16

BitcoinAddress myAddress("tb1qx2xn4q2t0ahezdhc4u76sdatskjr2p8wjpkack", ADDRESS_ENCODED);

void setup()
{
  WiFi.begin("You are being watched", "password1");
  while (WiFi.status()  != WL_CONNECTED)
  {
    yield();
  }
  Koyn.begin();
  Koyn.onNewTransaction(&paymentCallback);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (Koyn.isSynced())
  {
    Koyn.trackAddress(&myAddress);
  }
  Koyn.run();
}

void paymentCallback(BitcoinTransaction tx)
{
  for (int j = 0; j < tx.getOutputsCount(); j++)
  {
    BitcoinAddress to;
    tx.getOutput(j, &to);
    if (to == myAddress)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(1000);
      digitalWrite(LED_PIN, LOW);
      break;
    }
  }
}
