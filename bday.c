#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  /* Declare variables */
  FILE * inFile;
  FILE * outFile;
  char buffer [100];
  int randNum;
  int sampleSize;

  /* Initialize files */
  inFile = fopen("sampleIn.txt", "r");
  outFile = fopen("sampleOut.txt", "w");

  if (inFile == NULL || outFile == NULL) {
    fprintf(stderr, "Cannot open file\n");
    fclose(inFile);
    fclose(outFile);
    return 1;

  } else {
    /* Initialze random number generator */
    //srand(1);
    srand(time(NULL));

    /* Loop through input file */
    while ( fgets(buffer, 100, inFile) != NULL ) {
      sampleSize = atoi(buffer);
      printf("========================================\nSamples: %i\n", sampleSize);
      int x;
      for (x=0; x < sampleSize; x++) {
        randNum = rand() % 365 + 1;
        printf("%i, ", randNum);
      }
      printf("\n");
      fputs(buffer, outFile);
    }

  }

  fclose(inFile);
  fclose(outFile);
  return 0;

}
