#ifndef WEB_H
#define WEB_H

#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>

#include "text.h"

void web_start();
void web_run();
void web_stop();
void web_disp();

extern bool is_web_running;

#endif