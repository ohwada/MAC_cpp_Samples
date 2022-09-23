#include <SPI.h>
#include "mongoose.h"

#define SS_PIN 3    // Slave select pin
struct mg_mgr mgr;  // Mongoose event manager
struct mip_spi spi = {
    NULL,                                               // SPI data
    [](void *) { digitalWrite(SS_PIN, LOW); },          // begin transation
    [](void *) { digitalWrite(SS_PIN, HIGH); },         // end transaction
    [](void *, uint8_t c) { return SPI.transfer(c); },  // execute transaction
};

void setup() {
  Serial.begin(115200);
  pinMode(SS_PIN, OUTPUT);
  SPI.begin();

  // Set logging function to a serial print
  mg_log_set_fn([](char ch, void *) { Serial.print(ch); }, NULL);
  mg_mgr_init(&mgr);

  delay(3000);
  MG_INFO(("Starting TCP/IP stack..."));

  // Init TCP/IP stack. Set MAC address. Set IP to 0, to enable DHCP
  struct mip_cfg c = {.mac = {0, 0, 1, 2, 3, 4}, .ip = 0, .mask = 0, .gw = 0};
  mip_init(&mgr, &c, &mip_driver_w5500, &spi);

  // Start a 5 sec timer, print status message periodically
  mg_timer_add(
      &mgr, 5000, MG_TIMER_REPEAT,
      [](void *) {
        MG_INFO(("ethernet: %s", mip_driver_w5500.up(&spi) ? "up" : "down"));
      },
      NULL);

  // Setup HTTP listener. Respond "ok" on any HTTP request
  mg_http_listen(
      &mgr, "http://0.0.0.0",
      [](struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        if (ev == MG_EV_HTTP_MSG) mg_http_reply(c, 200, "", "ok\n");
      },
      &mgr);
}

void loop() {
  mg_mgr_poll(&mgr, 1);
}
