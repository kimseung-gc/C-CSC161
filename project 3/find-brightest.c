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

/* Pre-condition: It takes in the address of an image (Picture type).
 * Post-condition: It returns the maximum sum of RGB.
 */
int findSumOfMaxRGB(Picture * pic);

/* Pre-condition: It takes in the address of an image (Picture type).
 * Post-condition: It does not return anything.
 * This function prints out the coordinates that the maximum sum of RGB
 * happens where that place will be the brightest of all the other coordinates.
 * If there are multiple, they print all of them.
 */
void printMaxRGBCoord(Picture * pic);

int
main(void)
{
  rConnect("/dev/rfcomm0");
  Picture pict = rTakePicture();                 // Takes a photo with Scribbler2 bot, and saves as pict.
  rDisplayPicture (&pict, 5, "display of pict"); /* Displays pict on a window named "display of pict" for 5
                                                    seconds. */
  printMaxRGBCoord (&pict);                      /* Prints the coordinate that has the maximum RGB value
                                                    (AKA the brightest RGB value) found out by the maximum
                                                    of R+G+B. This function is designed to print all the
                                                    coordinates that the maximum occurs. */
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
  testImg.pix_array [10][100] = whitePix;
  testImg.pix_array [98][153] = whitePix;
  printMaxRGBCoord (&testImg);
  */
  rDisconnect();
  return 0;
}

int
findSumOfMaxRGB(Picture * pic)
{
  int maxRGB = 0;
  int sumRGB = 0;
  for(int i = 0; i < pic->height; i++){
    for(int j = 0; j < pic->width; j++){
      sumRGB = pic->pix_array[i][j].R + pic->pix_array[i][j].G + pic->pix_array[i][j].B;
      if (sumRGB>maxRGB){
        maxRGB = sumRGB;
      }
    }
  }
  return maxRGB;
}

void
printMaxRGBCoord(Picture * pic){
  int maxVal = findSumOfMaxRGB(pic);
  int sumRGB = 0;
  printf("The brightest pixel occurs in: ");
  for(int i = 0; i < pic->height; i++){
    for(int j = 0; j < pic->width; j++){
      sumRGB = pic->pix_array[i][j].R + pic->pix_array[i][j].G + pic->pix_array[i][j].B;
      if (sumRGB == maxVal){
        printf ("(%d, %d) ", i, j);
      }
    }
  }
  printf("\n");
}