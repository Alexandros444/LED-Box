import json


def pos_to_idx(x,y, y_len=8):
    n_row = x * y_len
    up_row = x % 2

    if up_row:
        n = n_row + y_len - 1 - y
    else:
        n = n_row + y

    return n

diagram = {
    "version": 1,
    "author": "Alexander Mohr",
    "editor": "wokwi",
    "parts": [
        { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 200, "left": 100, "attrs": {} }
    ],
    "connections": [
    [ "esp:TX", "$serialMonitor:RX", "", [] ],
    [ "esp:RX", "$serialMonitor:TX", "", [] ],
    ],
}

width = 32
height = 8


for x in range(width):
    for y in range(height):
        idx = pos_to_idx(x,y)
        led_part = {
            "type": "wokwi-neopixel", "id": f"rgb{idx}", "top": y*20, "left": x*20, "attrs": {}
        }
        led_conn = [
            [ f"rgb{idx}:VSS", f"rgb{idx+1}:VSS", "black", [] ],
            [ f"rgb{idx}:VDD", f"rgb{idx+1}:VDD", "black", []],
            [ f"rgb{idx}:DOUT", f"rgb{idx+1}:DIN", "black", []],
        ]
        if idx == 0:
            led_conn.append([ "rgb0:DIN", "esp:21", "black", []])
            led_conn.append([ "rgb0:VSS", "esp:GND.2", "black", []])
            led_conn.append([ "rgb0:VDD", "esp:5V", "black", []])
        if idx != 255:
            diagram["connections"].extend(led_conn)
        
        diagram["parts"].append(led_part)
        idx += 1

with open('diagram.json', 'w') as f:
    json.dump(diagram, f,indent=4)


a = {
  "version": 1,
  "author": "Anonymous maker",
  "editor": "wokwi",
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0, "attrs": {} },
    { "type": "wokwi-neopixel", "id": "rgb1", "top": -100, "left": -100, "attrs": {} },
    { "type": "wokwi-neopixel", "id": "rgb2", "top": -100, "left": -130, "attrs": {} },
    { "type": "wokwi-neopixel", "id": "rgb3", "top": -100, "left": -160, "attrs": {} }
  ],
  "connections": [
    [ "esp:TX", "$serialMonitor:RX", "", [] ],
    [ "esp:RX", "$serialMonitor:TX", "", [] ],
    [ "rgb1:DIN", "esp:21", "green", [ "h0" ] ],
    [ "rgb1:VSS", "esp:GND.2", "black", [ "v18.3", "h215.16" ] ],
    [ "rgb1:VDD", "esp:5V", "red", [ "v-19.2", "h139.01" ] ],
    [ "rgb1:DOUT", "rgb2:DIN", "green", [ "h-19.2", "v-10.5" ] ],
    [ "rgb2:VSS", "rgb1:VSS", "black", [ "v18.3", "h47.2", "v-18.3" ] ],
    [ "rgb2:VDD", "rgb1:VDD", "red", [ "h0", "v-19.2", "h38.4" ] ],
    [ "rgb2:DOUT", "rgb3:DIN", "green", [] ],
    [ "rgb3:VSS", "rgb2:VSS", "black", [ "v9.2", "h30" ] ],
    [ "rgb3:VDD", "rgb2:VDD", "red", [ "v-9.1", "h30" ] ]
  ],
  "dependencies": {}
}