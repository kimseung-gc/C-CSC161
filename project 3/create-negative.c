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
     *     Prof. Johnson                                                   *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: SHK, JHG                                               *
     ***********************************************************************/

#include <stdio.h>
#include <MyroC.h>

#define MAXCOLOR 255

/* Pre-condition: Takes in the pixel value of an image
 * Post-condition: It returns the pixel that is inverted by MAXCOLOR-V
 * where V is the element of {pix.R, pix.G, pix.B}.
 * Note that this function does not affect the original object.
 */
Pixel invertPixel(Pixel pix);

/* Pre-condition: Takes in address of the picture
 * Post-condition: This function does not return any output.
 * This function affects the original picture object where it changes the value
 * for each of the pixel inverted by the previous function.
 */
void invertPixPic (Picture * pic);

int
main(void)
{
  rConnect("/dev/rfcomm0");
  Picture pict = rTakePicture();                                      // Takes a photo with Scribbler2 bot, and saves as pict.
  rDisplayPicture (&pict, 5, "display of pict");                      /* Displays pict on a window named "display of pict1" for 5
                                                                         seconds. */
  /*
  // This part is for test purposes only. This line creates a test image 
  // with various colors so that it can produce an image with colors 
  // that will show how the setPictureMax function works.
  Pixel whitePix = {255, 255, 255};
  Pixel blackPix = {0, 0, 0};
  int col1 = 0;
  int col2 = 0;
  Picture testImg = {.height=192, .width=256};                         
  for (int row = 0; row < testImg.height; row++)
  {
    for (col1 = 0; col1 < testImg.width/3; col1++)
    {
      testImg.pix_array [row][col1] = whitePix;
    }
    for (col2 = col1+1; col2 < testImg.width/3*2; col2++)
    {
      testImg.pix_array [row][col2] = blackPix;
    }
    for (col1 = col2+1; col1 < testImg.width; col1++)
    {
      testImg.pix_array [row][col1] = (Pixel) {251, 244, 211};
    }
  }
  rDisplayPicture (&testImg, 5, "display of test image"); 
  */
  invertPixPic (&pict);                                               /* It converts the original pict image as the image that has
                                                                         inverted each of the values of the pixels by the formula 
                                                                         {R, G, B} = {MAXCOLOR - R, MAXCOLOR - G, MAXCOLOR - B}. 
                                                                         After using this function, the images looks as if it was
                                                                         taken in an haunted house. */
  rDisplayPicture (&pict, 5, "display of pict with inverted pixels"); /* It displays the inverted pixel converted pict on a window
                                                                         named "display of pict with inverted pixels." */
  /*
  // This part is for test purposes only. This line creates a test image 
  // with various colors so that it can produce an image with colors 
  // that will show how the setPictureMax function works.
  invertPixPic(&testImg);
  rDisplayPicture (&testImg, 5, "display of test image");
  */
  rDisconnect();
  return 0;
}

Pixel
invertPixel(Pixel pix){
  unsigned char invR = MAXCOLOR-pix.R;
  unsigned char invG = MAXCOLOR-pix.G;
  unsigned char invB = MAXCOLOR-pix.B;
  return (Pixel) {invR, invG, invB};
}

void invertPixPic (Picture * pic)
{
  Pixel tempPix;
  for(int i = 0; i < pic->height; i++){
    for(int j = 0; j < pic->width; j++){
      tempPix = invertPixel(pic->pix_array[i][j]);
      pic->pix_array[i][j] = tempPix;
    }
  }
}