# Embedded 3D Engine

[![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)

Written by Lukas Vyhnalek aka KiLLA.<br/>
BSD license, read LICENSE for more information.<br/>
All text above must be included in any redistribution.<br/>

### DESCRIPTION
Set of tools for basic 3D on embedded platforms.

### FEATURES

---

- Python script reads .obj file exported from Blender and creates .h file to include in your project
- Engine in include file to put into project folder rather than library to make development easier
- Examples of use
- object_3D internal format (optional)
- development status - beta/stable
- operating system independent (to some extent)
- designed to rely on as few external modules / libraries as possible

| Operating System | Installation methods | State |
| --- | --- | --- |
| Linux | manual | Tested |
| Windows | manual | NOT Tested |
| macOS | manual | NOT Tested |


### USAGE

---

- open Blender, create or open desired 3D model and export it as Wavefront (.obj)
- open the folder containing new .obj file, copy obj_to_header.py there, mark it executable
- open terminal and paste "./obj_to_header.py 20 include.h yourfile.obj" , execute it and include.h file gets created from yourfile.obj @ 20 pixels per Blender's meter
- include the engine.h and include.h in your project


### LIMITATIONS

---

- uses line-drawing methods from display device's library (Adafruit_GFX)
- 65535 triangles per object max
- precision of vertices int8_t - increasing it is trivial but has major impact on SRAM usage
- 16MHz Atmega328 draws ~1000 unfilled triangles / second


### SUPPORTED HARDWARE

---
| MCU | State |
| --- | --- |
| atmega328 | ok |
| stm32 | TODO |
| esp8266 | TODO |
| esp32 | TODO |

| DISPLAY | State |
| --- | --- |
| SSD1306 | ok |
| SSH1106 | TODO |
| ST7735 | TODO |
| 19264-05 v3 | TODO |


### TODO

---

- finish port of print function from other project, including basic font (done)
- optimize some here and there
- add more functions and possibly put into class so it can be used as a library as well
- add colour modes
