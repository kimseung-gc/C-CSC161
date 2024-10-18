#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floatStack.h"
#include "frequencyStack.h"
#include "stringFunctionsExtended.h"
#include "dataAnalysis.h"
#include "savingLoadingFunctions.h"

#ifndef __dataAnalysisUnited_h__
#define __dataAnalysisUnited_h__

/* void printingBufferSizeKR(FILE * stream, char * item, int bufferMAX)
 * Pre-conditions: The pointer to the file stream where it has to be the file opened
 * with writing access. The printing item is needed to measure the string length of
 * the printing item. It has to be in Korean as each Korean character is consist of 
 * 3 bytes and the buffer size is calculated accordingly. The bufferMAX is required
 * to place the next item at the position of bufferMAX.
 * Post-conditions: 
 * Comment: This is a helper function for saveData function, but this function
 * is no longer used as the CPI data is converted into English.
 */
void 
printingBufferSizeKR(FILE * stream, char * item, int bufferMAX);

/* void saveData(dataStack_t * stack, char * fileName)
 * Pre-conditions: The input has to be a data stack and a string with the fileName.
 * Post-conditions: The function produces a txt file that has the data stack saved
 * with a format of <Region>     <Standard Dev>  <Average>         <Mode>       
 * <Min>        <Q1>         <Median>       <Q3>       <Max>. As the names are in 
 * Korean, the buffer should be externally calculated which in out case it is going
 * to be done by printingBufferSizeKR() function. After saving (for each node), it
 * will clear the data node.
 */
void 
saveData(dataStack_t * stack, char * fileName);

/* char * reverseName(char * str)
 * Pre-conditions: The input has to be a string (the output of bringName preferrably)
 * with a '\0' indicator at the last index as strlen is going to be used.
 * Post-conditions: It will make the name reversed.
 * Comment: This is a helper function for bringName function.
 */
char * 
reverseName(char * str);

/* char * bringName(char * str)
 * Pre-conditions: The input has to be a string (the string on the first column of 
 * the CPI data txt file). This will extract the name of the region that the CPI is
 * investigated on.
 * Comment: This is a helper function for stringSplitCPI function.
 */
char * 
bringName(char * str);

/* char * subString(char * str, int i, int j)
 * Pre-conditions: The input has to be a string with a proper '\0' at the last index 
 * and two integers where the string will be extracted on the index from i to i+j. 
 * Note that i+j < strlen(str).
 * Post-conditions: It will return the string substringed from index i to index i+j.
 * Comment: This is a helper function for stringSplitCPI function.
 */
char * 
subString(char * str, int i, int j);

/* bool isNumber(char * str, unsinged long i)
 * Pre-conditions: THe input has to be a string and a starting index
 */
bool
isNumber(char * str, unsigned long i);

/* bool isEmptyFreq(char * stringSentence, char * token)
 * Pre-condition: The input has to be a string that is each line of the input file, 
 * and a token (the splitter of each data in the input file). In our case, the token
 * is going to be "\"\t\"".
 * Post-condition: It returns a float stack with all the data from the CPI file 
 * assigned. It will return a float stack named "Empty!"
 */
floatStack 
stringSplitCPI(char * stringSentence, char * token);

/* bool isEmptyFreq(const freqStack * stack)
 * Pre-condition: The input has to be a pointer to freqStack.
 * Post-condition: It returns a boolean about whether the frequency stack is empty.
 */
bool 
isEmptyFreq (const freqStack * stack);

/* bool initializeFreq(freqStack * stack)
 * Pre-condition: The input has to be a pointer to freqStack.
 * Post-condition: It returns nothing, but it sets up (initializes) the frequency 
 * stack by setting size as 0, length as 0, and top as a new stack node and its 
 * data -1.0, frequency 0, and next as NULL.
 */
void 
initializeFreq(freqStack * stack);

/* void addFreq(freqStack * stack, double dt)
 * Pre-conditions: The input has to be a frequency stack and a double dt. While the 
 * process, the dt is converted into a integer and it goes through the counting 
 * process (for convenience as CPI is usually double, but double is too precise to be
 * used as frequency count).
 * Post-conditions: The function itself does not return anything, but it adds (int)dt's 
 * frequency onto the stack. If the (int) dt is unprecedented, then it dynamically 
 * allocates memory to add on to the stack, and adds the frequency. While adding the
 * stack, the function adds the stack to the position where 
 * current stack<(int)dt<previous stack.
 * Comment: This function is used as a helper function for countFreq.
 */
void 
addFreq (freqStack * stack, double dt);

/* freqStack countFreq(const floatStack * stack)
 * Pre-conditions: The input has to be a pointer to the floatStack to count the 
 * frequency.
 * Post-conditions: This function returns the freqStack that has gone through
 * the process of counting the integerized data of the stack. The function uses 
 * addFreq function which keeps the freqStack sorted.
 */
freqStack
countFreq(const floatStack * stack);

/* void printFreq(freqStack * stack)
 * Pre-conditions: The input has to be a frequency stack which has gone through the 
 * countFreq function. (otherwise, it will print that the stack is empty or unwanted 
 * stack)
 * Post-conditions: The function itself does not return anything, but it prints the
 * frequency list onto the terminal.
 */
void
printFreq (freqStack * stack);

/* void clearFreq(freqStack * stack)
 * Pre-conditions: The input has to be a pointer to an initialized frequency stack
 * Post-conditions: The function will not return anything, but it will empty out the
 * frequency stack. 
 * Comments: This is done in the data analysis step when the frequency stack is no
 * longer needed.
 */
void
clearFreq(freqStack * stack);

/* bool isEmptyFloat(const floatStack * stack)
 * Pre-conditions: The input has to be a float stack pointer. The stack has to be
 * initialized.
 * Post-conditions: The function returns a boolean that returns whether the input
 * float stack is empty.
 */
bool
isEmptyFloat (const floatStack * stack);

/* bool isFullFloat()
 * Pre-conditions: None
 * Post-conditions: The function returns a boolean that returns whether the computer
 * that the program is executed has space to dynamically allocate memory for a float
 * stack.
 */
bool
isFullFloat ();

/* void initializeFloat(floatStack * stack, char * name)
 * Pre-conditions: The input has to be a pointer to a float stack and a valid name
 * string. The last index of the name has to be '\0'.
 * Post-conditions: This functions itself does not return anything, but it initializes
 * the stack by setting the name of the stack as input name, size as 0, and top as NULL.
 */
void
initializeFloat(floatStack * stack, char * name);

/* bool push (floatStack * stack, double item)
 * Pre-conditions: The input has to be the pointer to the floatStack and the item has 
 * to be a double.
 * Post-conditions: Item float is added to stack and returns true or else stack is 
 * unmodified and returns false (when stack is full).
 */
bool
push (floatStack * stack, double item);

/* void printFloat(const floatStack * stack)
 * Pre-conditions: The input has to be a pointer to the float stack.
 * Post-conditions: The function does not return anything, but it prints out the data
 * that the input file had and that was loaded onto the stack.
 */
void
printFloat (const floatStack * stack);

/* void clearFloat(floatStack * stack)
 * Pre-conditions: The input has to be a pointer to a valid initialized float stack.
 * Post-conditions: It will not return anything, but it will clear out the float stack
 * data.
 * Comments: This process is done in the data analysis step when float stack is no longer
 * needed.
 */
void
clearFloat(floatStack * stack);

/* void printingBufferSizeKRforData(char * item, int bufferMAX)
 * Pre-conditions: The input has to be a Korean string that is going to be printed 
 * with a valid '\0' indicator at the last index of the item. The other input has 
 * to be an integer which is going to be the size of the buffer.
 * Post-conditions: This will shift the next printing item by bufferMAX (same 
 * effect as %-<bufferMAX>s), but adjusted with Korean.
 * Comments: This is a helper function for printData function, but this function
 * is no longer used as the CPI data is converted into English.
 */
void
printingBufferSizeKRforData(char * item, int bufferMAX);

/* void printData(dataStack_t * stack)
 * Pre-conditions: The input has to be a data stack with all the data from the input
 * files analyzed.
 * Post-conditions: This will shift the next print all the data in the same format
 * that is saved. This function may print that the input file is empty when the data
 * is not analyzed or the stack is empty.
 * Comments: This is a helper function for printData function
 */
void
printData(dataStack_t * stack);

/* int findMode(freqStack * stack)
 * Pre-conditions: This function requires an initialized frequency stack pointer 
 * to be input.
 * Post-conditions: This functions will return the mode of the frequency stack. If 
 * the stack is empty, it will return -1 which is invalid for CPI.
 * Comments: This is a helper function for makeNewData() function.
 */
int
findMode(freqStack * stack);

/* double average(floatStack * stack)
 * Pre-conditions: This function requires a valid, initialized float stack pointer 
 * to be input.
 * Post-conditions: This will return the average of the float stack. If the stack
 * is empty, it will return -1.0 which is an invalid average for CPI.
 * Comments: This is a helper function for makeNewData() function.
 */
double 
average(floatStack * stack);

/* double stdDevHelper(stackNode * node, double avg)
 * Pre-conditions: The input has to be a pointer to the first stack node and the
 * average of the float stack.
 * Post-conditions: This will return the square of a standard deviation of
 * the stack nodes.
 * Comments: This is a helper function for stdDev function.
 */
double 
stdDevHelper(stackNode * node, double avg);

/* double stdDev(floatStack * stack)
 * Pre-conditions: The input has to be a pointer to the float stack.
 * Post-conditions: This will return the standard deviation of the stack.
 * Comments: This is a helper function for makeNewData() function.
 */
double 
stdDev(floatStack * stack);

/* void findQ1Q2Q3(freqStack * sortedStack, dataStack_t * dest)
 * Pre-conditions: The input has to be a pointer to the frequency stack and
 * the destination data stack pointer.
 * Post-conditions: This will not return anything, but it will find the first
 * quarter, median and the third quarter of the data set and assign them accordingly
 * to the destination data stack.
 * Comments: This is a helper function for makeNewData() function.
 */
void
findQ1Q2Q3(freqStack * sortedStack, dataStack_t * dest);

/* void makeNewData(dataStack_t ** stack, floatStack * flSt)
 * Pre-conditions: The input has to be a double pointer to the data stack that has to
 * be both initialized and has to be assigned datas. The other input has to be the
 * float stack that has gone through the stringSplit process.
 * Post-conditions: This function itself will not produce any outputs, but it will
 * initialize the data stack and assign new data stack types by allocating memory
 * and assigning data structures with its helper functions.
 */
void
makeNewData(dataStack_t ** stack, floatStack * flSt);

#endif