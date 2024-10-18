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

#define RSCALE 0.30f /* defines how much the R of the RGB has to be scaled to
                        be converted into a pixel of black and white. */
#define GSCALE 0.59f /* defines how much the G of the RGB has to be scaled to
                        be converted into a pixel of black and white. */
#define BSCALE 0.11f /* defines how much the B of the RGB has to be scaled to
                        be converted into a pixel of black and white. */

/* Pre-conditions: The input has to be the address of the Picture object
 * and requires the definition of Picture or include the MyroC.h lib.
 * Post-conditions: The function will not return anything, but affect
 * the original object.
 * It converts the colored RGB picture into a single valued pixel black
 * and white image.
 */
void colorToGray (Picture * pic);

/* Pre-conditions: The input has to a Pixel type and requires the 
 * definition of Picture or include the MyroC.h lib.
 * Post-conditions: The function will return the maximum value of RGB
 * with all the other values of RGB set to 0.
 * It finds the maximum value of RGB and set all the other values to
 * 0 in the scale of single Pixel.
 */
Pixel maxRGB (Pixel pix);

/* Pre-conditions: The input has to be the address of the Picture object
 * and requires the definition of Picture or include the MyroC.h lib.
 * Post-conditions: The function will not return anything, but affect
 * the original object.
 * It removes all the other RGB values that are smaller than the maximum 
 * value of the RGB pixel.
 */
void setPictureMax (Picture * pic);

int
main(void)
{
  rConnect("/dev/rfcomm0");
  Picture pict1 = rTakePicture();                                      // Takes a photo with Scribbler2 bot, and saves as pict1.
  Picture pict2 = rTakePicture();                                      /* We are taking two photos as the functions colorToGray and
                                                                          setPictureMax both modifies the original picture object.
                                                                          Thus, we decided two utilize two different pictures. */
  rDisplayPicture (&pict1, 5, "display of pict1");                     /* Displays pict1 on a window named "display of pict1" for 5
                                                                          seconds. */
  rDisplayPicture (&pict2, 5, "display of pict2");                     /* Displays pict2 on a window named "display of pict2" for 5
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
      testImg.pix_array [row][col1] = (Pixel) {0, 255, 255};
    }
  }
  rDisplayPicture (&testImg, 5, "display of test image"); 
  */
  colorToGray (&pict1);                                                // Converts the original pict1 object into grey scale
  setPictureMax(&pict2);                                               /* It converts pict2 as a picture with only the maximum 
                                                                          value of RGB and setting rest of the RGB as 0. It kind of
                                                                          looks like a infra-red image. */
  rDisplayPicture (&pict1, 5, "display of pict1 in black and white");  /* It displays the grey-scaled converted pict on a window
                                                                          named "display of pict1 in black and white." */
  rDisplayPicture (&pict2, 5, "display of pict2 set max pixel");       /* It displays the maximized pixel converted pict2 on a window
                                                                          named "display of pict2 set max pixel." */
  /*
  // This part is for test purposes only. This line creates a test image 
  // with various colors so that it can produce an image with colors 
  // that will show how the setPictureMax function works.
  setPictureMax(&testImg);
  rDisplayPicture (&testImg, 5, "display of test image");
  */
  rDisconnect();
  return 0;
}

void
colorToGray (Picture * pic){
  unsigned char pix = 0.0;
  for(int i = 0; i < pic->height; i++){
    for(int j = 0; j < pic->width; j++){
      pix = 0;
      pix += pic->pix_array[i][j].R*RSCALE;
      pix += pic->pix_array[i][j].G*GSCALE;
      pix += pic->pix_array[i][j].B*BSCALE;
      pic->pix_array[i][j] = (Pixel) {pix, pix, pix};
    }
  }
}

Pixel
maxRGB(Pixel pix){
  unsigned char tempArr[3] = {pix.R, pix.G, pix.B};
  unsigned char max = tempArr[0];
  for(int i = 1; i<3; i++){
    if(tempArr[i] > max){
      max = tempArr[i];
      tempArr[i-1] = 0;
    }
    else{
      tempArr[i] = 0;
    }
  }
  return (Pixel){tempArr[0], tempArr[1], tempArr[2]};
}

void
setPictureMax (Picture * pic){
  for(int i = 0; i<pic->height; i++){
    for(int j = 0; j<pic->width; j++){
      pic->pix_array[i][j] = maxRGB(pic->pix_array[i][j]);
    }
  }
}