/*
Copyright (c) 2020, Lukas Vyhnalek aka KiLLA
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
#include "object_3D_data.h"

struct object3D
{
  const int8_t (*vert_list)[3];
  uint16_t numVerts;

  const uint8_t (*faces_list)[3];
  uint16_t numTriPolys;
};

const object3D number_0 [] PROGMEM = {number_0_verts, sizeof(number_0_verts) / sizeof(number_0_verts[0]), number_0_tris, sizeof(number_0_tris) / sizeof(number_0_tris[0])};
const object3D number_1 [] PROGMEM = {number_1_verts, sizeof(number_1_verts) / sizeof(number_1_verts[0]), number_1_tris, sizeof(number_1_tris) / sizeof(number_1_tris[0])};
const object3D number_2 [] PROGMEM = {number_2_verts, sizeof(number_2_verts) / sizeof(number_2_verts[0]), number_2_tris, sizeof(number_2_tris) / sizeof(number_2_tris[0])};
const object3D number_3 [] PROGMEM = {number_3_verts, sizeof(number_3_verts) / sizeof(number_3_verts[0]), number_3_tris, sizeof(number_3_tris) / sizeof(number_3_tris[0])};
const object3D number_4 [] PROGMEM = {number_4_verts, sizeof(number_4_verts) / sizeof(number_4_verts[0]), number_4_tris, sizeof(number_4_tris) / sizeof(number_4_tris[0])};
const object3D number_5 [] PROGMEM = {number_5_verts, sizeof(number_5_verts) / sizeof(number_5_verts[0]), number_5_tris, sizeof(number_5_tris) / sizeof(number_5_tris[0])};
const object3D number_6 [] PROGMEM = {number_6_verts, sizeof(number_6_verts) / sizeof(number_6_verts[0]), number_6_tris, sizeof(number_6_tris) / sizeof(number_6_tris[0])};
const object3D number_7 [] PROGMEM = {number_7_verts, sizeof(number_7_verts) / sizeof(number_7_verts[0]), number_7_tris, sizeof(number_7_tris) / sizeof(number_7_tris[0])};
const object3D number_8 [] PROGMEM = {number_8_verts, sizeof(number_8_verts) / sizeof(number_8_verts[0]), number_8_tris, sizeof(number_8_tris) / sizeof(number_8_tris[0])};
const object3D number_9 [] PROGMEM = {number_9_verts, sizeof(number_9_verts) / sizeof(number_9_verts[0]), number_9_tris, sizeof(number_9_tris) / sizeof(number_9_tris[0])};


const object3D* const numbers3D[10] PROGMEM = {number_0, number_1, number_2, number_3, number_4, number_5, number_6, number_7, number_8, number_9};

*/

////////////////////////////////
// DEVICE SELECT
extern Adafruit_SSD1306 display;


////////////////////////////////
// FUNCTION PRIMITIVES
void rotate_vertices(int8_t vert_list[][3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ);
void rotate_vertices(const int8_t (*vert_list)[3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ);

void scale_vertices(int8_t vert_list[][3], int8_t scaled_list[][3], uint8_t vert_count, float scale);
void scale_vertices(const int8_t (*vert_list)[3], int8_t scaled_list[][3], uint8_t vert_count, float scale);

void draw_tri_polys(int8_t vert_list[][3], uint8_t faces_list[][3], uint8_t list_size, int16_t x, int16_t y);
void draw_tri_polys(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y);
void draw_tri_polys(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y);


/*
void draw_3D_number(uint8_t number, float scale, int16_t x, int16_t y, float rotX, float rotY, float rotZ) {
  if (number > 9) {
    return;
  };
  const object3D* object = (const object3D*) pgm_read_ptr(&numbers3D[number]);
  uint8_t vertcount = pgm_read_word(&object->numVerts); //number_0
  uint8_t polycount = pgm_read_word(&object->numTriPolys); //number_0
  const int8_t (*vert_list)[3] = pgm_read_ptr(&object->vert_list);
  const uint8_t (*faces_list)[3] = pgm_read_ptr(&object->faces_list);

  
   // int8_t vertlist_temp[vertcount][3]; // temp
   // rotate_vertices(vert_list, vertlist_temp, vertcount, rotX, rotY, rotZ); // rotate
   // scale_vertices(vertlist_temp, vertlist_temp, vertcount, scale); // scale
   // draw_tri_polys(vertlist_temp, faces_list, polycount, x, y);
  
  draw_tri_polys(vert_list, faces_list, polycount, x, y, scale, rotX, rotY, rotZ); // TODO
  draw_tri_polys(vert_list, faces_list, polycount, x, y);
};
*/

////////////////
// ROTATION

void rotate_vertices(int8_t vert_list[][3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ)
{
  float sin_rotX = sin(rotX);
  float cos_rotX = cos(rotX);
  float sin_rotY = sin(rotY);
  float cos_rotY = cos(rotY);
  float sin_rotZ = sin(rotZ);
  float cos_rotZ = cos(rotZ);

  for (int i = 0; i < vert_count; i++) {
    //rotateY
    float rotz = vert_list[i][2] * cos_rotY - vert_list[i][0] * sin_rotY;
    float rotx = vert_list[i][2] * sin_rotY + vert_list[i][0] * cos_rotY;
    float roty = vert_list[i][1];
    //rotateX
    float rotyy = roty * cos_rotX - rotz * sin_rotX;
    float rotzz = roty * sin_rotX + rotz * cos_rotX;
    float rotxx = rotx;
    //rotateZ
    float rotxxx = rotxx * cos_rotZ - rotyy * sin_rotZ;
    float rotyyy = rotxx * sin_rotZ + rotyy * cos_rotZ;
    float rotzzz = rotzz;

    rotated_list[i][0] = rotxxx;
    rotated_list[i][1] = rotyyy;
    rotated_list[i][2] = rotzzz;
  }
}

void rotate_vertices(const int8_t (*vert_list)[3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ)
{
  Serial.println("rotate_vertices>PGM");
  for (int i = 0; i < vert_count; i++) {
    //rotateY
    float rotz = (int8_t)pgm_read_byte(&vert_list[i][2]) * cos(rotY) - (int8_t)pgm_read_byte(&vert_list[i][0]) * sin(rotY); //(int8_t)
    float rotx = (int8_t)pgm_read_byte(&vert_list[i][2]) * sin(rotY) + (int8_t)pgm_read_byte(&vert_list[i][0]) * cos(rotY);
    float roty = (int8_t)pgm_read_byte(&vert_list[i][1]);
    //rotateX
    float rotyy = roty * cos(rotX) - rotz * sin(rotX);
    float rotzz = roty * sin(rotX) + rotz * cos(rotX);
    float rotxx = rotx;
    //rotateZ
    float rotxxx = rotxx * cos(rotZ) - rotyy * sin(rotZ);
    float rotyyy = rotxx * sin(rotZ) + rotyy * cos(rotZ);
    float rotzzz = rotzz;

    rotated_list[i][0] = rotxxx;
    rotated_list[i][1] = rotyyy;
    rotated_list[i][2] = rotzzz;
  }
}

////////////////
// SCALE
void scale_vertices(int8_t vert_list[][3], int8_t scaled_list[][3], uint8_t vert_count, float scale)
{
  for (int i = 0; i < vert_count; i++) {
    //
    scaled_list[i][0] = vert_list[i][0] * scale;
    scaled_list[i][1] = vert_list[i][1] * scale;
    scaled_list[i][2] = vert_list[i][2] * scale;
  }
}

void scale_vertices(const int8_t (*vert_list)[3], int8_t scaled_list[][3], uint8_t vert_count, float scale)
{
  for (int i = 0; i < vert_count; i++) {
    //
    scaled_list[i][0] = (int8_t)pgm_read_byte(&vert_list[i][0]) * scale;
    scaled_list[i][1] = (int8_t)pgm_read_byte(&vert_list[i][1]) * scale;
    scaled_list[i][2] = (int8_t)pgm_read_byte(&vert_list[i][2]) * scale;
  }
}

////////////////
// DRAW
void draw_tri_polys(int8_t vert_list[][3], uint8_t faces_list[][3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + vert_list[faces_list[i][0]][0], y + vert_list[faces_list[i][0]][1], x + vert_list[faces_list[i][1]][0], y + vert_list[faces_list[i][1]][1], WHITE);
    display.drawLine(x + vert_list[faces_list[i][1]][0], y + vert_list[faces_list[i][1]][1], x + vert_list[faces_list[i][2]][0], y + vert_list[faces_list[i][2]][1], WHITE);
    display.drawLine(x + vert_list[faces_list[i][2]][0], y + vert_list[faces_list[i][2]][1], x + vert_list[faces_list[i][0]][0], y + vert_list[faces_list[i][0]][1], WHITE);
  }
}

void draw_tri_polys(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], WHITE);
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], WHITE);
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], WHITE);
  }
}

void draw_tri_polys(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]), WHITE);
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]), WHITE);
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]), WHITE);
  }
}

void draw_tri_polys_filled(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.fillTriangle(x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], WHITE);
  }
}

void draw_tri_polys(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float scale, float rotX, float rotY, float rotZ)
{
  int8_t vert_temp[3][3];
  for (uint16_t i = 0; i < list_size; i++) {
    //
    vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]) * scale;
    vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]) * scale;
    vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][2]) * scale;

    vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]) * scale;
    vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]) * scale;
    vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][2]) * scale;

    vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]) * scale;
    vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]) * scale;
    vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][2]) * scale;

    rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

    display.drawLine(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], WHITE);
    display.drawLine(x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], WHITE);
    display.drawLine(x + vert_temp[2][0], y + vert_temp[2][1], x + vert_temp[0][0], y + vert_temp[0][1], WHITE);
  }
}

void draw_tri_polys_filled(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float scale, float rotX, float rotY, float rotZ)
{
  int8_t vert_temp[3][3];
  for (uint16_t i = 0; i < list_size; i++) {
    //
    vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]) * scale;
    vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]) * scale;
    vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][2]) * scale;

    vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]) * scale;
    vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]) * scale;
    vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][2]) * scale;

    vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]) * scale;
    vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]) * scale;
    vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][2]) * scale;

    rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

    display.fillTriangle(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], WHITE);
  }
}

////////////////
// TODO
void char_to_vertices(uint8_t character, uint8_t out_vertices_array[][3], uint16_t array_size)
{
  uint8_t pixel_diameter = 6;
  // TODO:
}




