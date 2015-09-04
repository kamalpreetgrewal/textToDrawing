This repository enables the user to input a text file whose 
drawing can be easily created in softwares like LibreCAD, AutoCAD
etc.

The input file is parsed and saved as a DXF file when the program
is run. The input file can have the following format:

**wall(l=100,h=130,cx=10,cy=10)** <br>
     where l is length of the wall, <br>
      h is height of the wall, <br>
      cx is x-coordinate of bottom-left corner of wall, and <br>
      cy is y-coordinate of bottom-left corner of wall. <br>
