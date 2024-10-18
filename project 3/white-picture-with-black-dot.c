
    /***********************************************************************
     * Name(s)  Seunghyeon Kim, Joyce Gill                                 *
     * Assignment name (Project  3)                                        *
     * Image Processing                                                    *
     * Assignment for 10/04/2023                                           *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     None                                                            *
     *   Help obtained                                                     *
     *     Original Author: Henry Walker                                   *
     *     Prof. Johnson                                                   *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: SHK, JHG                                               *
     ***********************************************************************/

/* Program to demonstrate an image declaration as well as simple pixel
   iteration and assignments */

#include <stdio.h>
#include <MyroC.h>

int
main (void)
{

  printf ("Program to create and display a white picture with a black dot\n");
  Pixel blackPix = {0, 0, 0};

  Pixel whitePix = {255, 255, 255};

  /*For question 1d*/
  Pixel redPix = {255, 0, 0};
  Pixel greenPix = {0, 255, 0};
  Pixel bluePix = {0, 0, 255};
  /* Each of the pixels were defined by using the fact that the RGB
   * represents Red, Green, Blue which turning on the pixel accordingly 
   * will show each of the colors indicated above.
   */
  
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

  /* place 2-by-2 red dot in top middle of the picture */
  myArt.pix_array [0] [myArt.width/2]     = redPix;
  myArt.pix_array [1] [myArt.width/2]     = redPix;
  myArt.pix_array [0] [myArt.width/2+1]   = redPix;
  myArt.pix_array [1] [myArt.width/2+1]   = redPix;
  
  /* place 2-by-2 green dot in left middle of the picture */
  myArt.pix_array [myArt.height/2]   [0]   = greenPix;
  myArt.pix_array [myArt.height/2+1] [0]   = greenPix;
  myArt.pix_array [myArt.height/2]   [1]   = greenPix;
  myArt.pix_array [myArt.height/2+1] [1]   = greenPix;

  /* place 2-by-2 blue dot in bottom middle of the picture */
  myArt.pix_array [myArt.height-2] [myArt.width/2]     = bluePix;
  myArt.pix_array [myArt.height-1] [myArt.width/2]     = bluePix;
  myArt.pix_array [myArt.height-2] [myArt.width/2+1]   = bluePix;
  myArt.pix_array [myArt.height-1] [myArt.width/2+1]   = bluePix;

  
  /* display the image for 10 seconds */
  rDisplayPicture (&myArt, 10, "display of myArt");

  return 0;

}
