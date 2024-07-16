#ifndef WEB_H
#define WEB_H

#include <WiFi.h>
#include <WebServer.h>
#include "text.h"

void web_start();
void web_run();
void web_stop();
void web_disp();

#endif