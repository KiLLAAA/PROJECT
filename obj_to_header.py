#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
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
"""

################
# IMPORTS
import sys
import re

################################[ PARSER ]################################
class DataProcessing():
    def __init__(self, text):
        self.importedText = text
        self.vertexcount = 0
        self.facescount = 0
        
        self.tris = []
        self.verts = []

        self.string_tris = ""
        self.string_verts = ""

        self.importData(self.importedText)

    ################
    # IMPORT
    def importData(self, importedText):
        """Import text to parse"""
        # prepare data to be read from the string
        stringsfound = re.sub('v (-?[\d.]+) (-?[\d.]+) (-?[\d.]+)', self.foundvertex, importedText) #
        
        stringsfound = re.sub('f (-?[\d.]+)\/\/.+ (-?[\d.]+)\/\/.+ (-?[\d.]+)\/\/.+', self.found_face, importedText) #

    def foundvertex(self, matchobj):
        """Adds value to current"""
        tempdict = {}
        tempdict['type'] = "vertex"
        tempdict['line'] = self.importedText[:matchobj.end(1)].count('\n')
        tempdict['X'] = float(matchobj.group(1))
        tempdict['Y'] = float(matchobj.group(2))
        tempdict['Z'] = float(matchobj.group(3))
        self.verts.append(tempdict) # append data
        
        self.vertexcount = self.vertexcount + 1
        
        return str(matchobj.group(1))

    def found_face(self, matchobj):
        """Adds value to current"""
        tempdict = {}
        tempdict['type'] = "tri_face"
        tempdict['line'] = self.importedText[:matchobj.end(1)].count('\n')
        tempdict['a'] = int(matchobj.group(1))
        tempdict['b'] = int(matchobj.group(2))
        tempdict['c'] = int(matchobj.group(3))
        self.tris.append(tempdict) # append data
        
        self.facescount = self.facescount + 1
        
        return str(matchobj.group(1))

################################[ GLOBAL ]################################
def get_name(input_path):
    inputMatch = re.search(r'[\/]?([a-zA-Z0-9_-]+).obj', input_path) # search for strings inside curly braces first
    # if found, scan extracted string further for hex values
    if inputMatch:
          return inputMatch.group(1)
    else: return "name"

################################[ MAIN ]################################
text_defines_verts = ""
text_defines_tris = ""
text_mixed_data = ""
text_verts = ""
text_tris = ""

################
# INPUT
for infile in sys.argv[3:]:
    try:
        with open(infile) as fileobj:
            sys.stdout.write("Input file: " + str(infile) + "\r\n")
            text = fileobj.read()
            proc = DataProcessing(text)
    except:
        sys.stdout.write("Error opening input file: " + str(infile) + "\r\n")
        sys.exit()
    else:
        zoom = float(sys.argv[1])
        #zoom = 1
        proc.string_verts = "\r\n\r\nconst int8_t %s_verts[%s][3] PROGMEM = {" % (get_name(infile), (get_name(infile)).upper() + "_VERTS")
        for vertex in proc.verts:
            text_x = str(int(float(vertex['X']) * zoom)) # -int = flip axis X
            text_y = str(-int(float(vertex['Y']) * zoom)) # -int = flip axis Y
            text_z = str(int(float(vertex['Z']) * zoom)) # -int = flip axis Z
            proc.string_verts += "\r\n  {" + text_x + ", " + text_y + ", " + text_z + "}," 
        proc.string_verts += "\r\n};"
        
        text_verts += proc.string_verts
        text_mixed_data += proc.string_verts
        
        proc.string_tris = "\r\n\r\nconst uint8_t %s_tris[%s][3] PROGMEM = {" % (get_name(infile), (get_name(infile)).upper() + "_TRIS")
        for tri_face in proc.tris:
            proc.string_tris += "\r\n  {" + str(int(tri_face['a'])-1) + ", " + str(int(tri_face['b'])-1)+ ", " + str(int(tri_face['c'])-1) + "},"
        proc.string_tris += "\r\n};"
        
        text_tris += proc.string_tris
        text_mixed_data += proc.string_tris
        
        text_defines_verts += "\r\n#define " + (get_name(infile)).upper() + "_VERTS " + str(proc.vertexcount)
        text_defines_tris += "\r\n#define " + (get_name(infile)).upper() + "_TRIS " + str(proc.facescount)
        
################
# OUTPUT
if (text_mixed_data != ""):
    outfile = str(sys.argv[2])
    outdata = text_defines_verts + text_defines_tris + text_mixed_data
    try:
        with open(outfile, "w") as outfileobj:
            outfileobj.write(outdata)
    except:
        sys.stdout.write("Error opening output file: " + str(outfile) + "\r\n")
        sys.exit()
    else:
        sys.stdout.write("Output written to: " + str(outfile) + "\r\n")
        sys.exit()
else:
    sys.stdout.write("Warning! No data to write to output." + "\r\n")
    sys.exit()
