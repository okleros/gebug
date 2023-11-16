# Gebug (Graphical Debug)

Small [stb-style](https://github.com/nothings/stb) header only library meant to solve some debugging issues I had while working for a while on a [Neural Network from scratch](https://nnfs.io/) in C. Most of the times I needed to be able to see the weights matrix graphically, because the numbers didn't make any sense for me, personally.

The library does not have any third-party dependencies and does not need to be built or compiled. Since it is stb-style header only, both the headers and the implementations are on the same file, and you will have to `#define GEBUG_IMPLEMENTATION` so the implementations also come in with the include directive.

## Quick start
As explained earlier, Gebug does not need to me compiled nor built in any form, instead, you simply clone the header file contained in this repository and type
```console
#define GEBUG_IMPLEMENTATION

#include "gebug.h"
```
on the file you want to use Gebug.

There is a main data structure called the `gebug_canvas`, which contains the pixel array, width and height of the canvas. All the other work is done inside this pixel array.

## Inspiration
This project was inspired by [Tsoding's olive.c](https://github.com/tsoding/olive.c) library, but does not in any way contains copy-and-paste code from him.

## Demos
As I develop the project, I will be updating the session of demos below:

### Rectangles:
![three rectangles overlapping](https://i.imgur.com/eFKyjTj.png)
### Circles
![five circles with different centers, radii and colors](https://i.imgur.com/x3guOqs.png)
### Triangles
TODO