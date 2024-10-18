/* Program to demonstrate an image declaration as well as simple pixel
   iteration and assignments */

#include <stdio.h>
#include "MyroC.h"

int
main (void)
{

  printf ("Program to create and display a white picture with a black dot\n");
  Pixel blackPix = {0, 0, 0};
  Pixel whitePix = {255, 255, 255};

  /* declare picture and set proper dimensions */
  Picture myArt = {.height=192, .width=256};
  /* alternatively, dimensions could be set explicitly, as follows: */
  //myArt.height= 192;
  //myArt.width = 256;

  /* color all pixels white */
  for (int row = 0; row < myArt.height; row++)
    for (int col = 0; col < myArt.width; col++)
      myArt.pix_array [row][col] = whitePix;
  
  /* place 2-by-2 black dot in the middle of the picture */
  myArt.pix_array [myArt.height/2]   [myArt.width/2]   = blackPix;
  myArt.pix_array [myArt.height/2+1] [myArt.width/2]   = blackPix;
  myArt.pix_array [myArt.height/2]   [myArt.width/2+1] = blackPix;
  myArt.pix_array [myArt.height/2+1] [myArt.width/2+1] = blackPix;

  /* display the image for 10 seconds */
  rDisplayPicture (&myArt, 10, "display of myArt");

  return 0;

}