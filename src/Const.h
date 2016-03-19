/*
Copyright (C) 2000,2001 Stefan Duffner 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#define CONT_WIDTH 		640
#define CONT_HEIGHT 		480

#define ZOOM_FACTOR 		1.2
#define MAX_ZOOM 		50.0
#define MIN_ZOOM 		0.05

#define PI 			3.1415926536

#define CPOINT_SIZE 		4

#define ARROW_ANGLE 		20.0
#define ARROW_LENGTH 		15

#define START_DISTANCE 		20
#define ITRANS_DEFAULT_LENGTH	60

#define CANVAS_MARGIN 		100
#define CANVAS_MINX 		100
#define CANVAS_MINY 		100

#define MAX_MRUENTRIES 		10

#define MAX_BIN_INPUTLENGTH	1024
#define MAX_ASCII_INPUTLENGTH	256
#define MAX_ASCII_OUTPUTLENGTH	4
#define MAX_TEXT_INPUTLENGTH	1024
#define MAX_TEXT_OUTPUTLENGTH	1024
#define MAX_CHARARRAY_LENGTH	1024

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ROUND(a) ((a)<0?int((a)+0.5):(-1)*int((-a)+0.5))
