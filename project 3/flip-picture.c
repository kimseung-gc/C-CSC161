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

/* Pre-conditions: The input must be the address of an image, and the integer indices
 * that you will flip.
 * Post-conditions: This functions does not give any output
 * However, the function rather changes the original picture objects where i1 and i2 
 * will be swapped.
 */
void swapRows(Picture * pic, int i1, int i2);

/* Pre-conditions: The input must be the address of an image.
 * Post-conditions: This functions does not give any output
 * However, the original Picture object is inverted upside down (flipped).
 */
void flipImg(Picture * pic);

int
main (void){
  rConnect("/dev/rfcomm0");
  Picture pict = rTakePicture();                         // Takes a photo with Scribbler2 bot, and saves as pict.
  rDisplayPicture (&pict, 5, "display of pict");         /* Displays pict on a window named "display of pict" for
                                                            5 seconds. */
  flipImg (&pict);                                       // Flips pict upside down.
  rDisplayPicture (&pict, 5, "display of flipped pict"); /* Displays pict turned upside down on a window named 
                                                            "display of pict." */
  /*
  // This part is for test purposes only. This line creates a test image 
  // with various colors so that it can produce an image with colors 
  // that will show how the setPictureMax function works.
  Pixel whitePix = {255, 255, 255};
  Pixel blackPix = {0, 0, 0};
  int col1 = 0;
  Picture testImg = {.height=192, .width=256};                         
  for (int row = 0; row < testImg.height; row++)
  {
    for (col1 = 0; col1 < testImg.width; col1++)
    {
      testImg.pix_array [row][col1] = blackPix;
    }
  }
  testImg.pix_array [0][128] = whitePix;
  testImg.pix_array [0][129] = whitePix;
  testImg.pix_array [1][128] = whitePix;
  testImg.pix_array [1][129] = whitePix;
  rDisplayPicture (&testImg, 5, "display of testImg");
  flipImg (&pict);
  rDisplayPicture (&testImg, 5, "display of flipped testImg");
  */
  rDisconnect();
  return 0;
}

void
swapRows(Picture * pic, int i1, int i2){
  Pixel temp;
  for(int j = 0; j < pic->width; j++){
    temp = pic->pix_array[i1][j];
    pic->pix_array[i1][j] = pic->pix_array[i2][j];
    pic->pix_array[i2][j] = temp;
  }
}

void
flipImg(Picture * pic){
  int max = pic->height/2;
  int invertedI = pic->height-1;
  for(int i = 0; i < max; i++){
    swapRows(pic, i, invertedI-i);
  }
}