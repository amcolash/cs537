#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 5

int main() {

  /* Declare variables */
  FILE * inFile;
  FILE * outFile;
  char buffer [100];
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
      if (sampleSize > 0) {
        printf("======================================================================\nSamples: %i, Trials: %i\n", sampleSize, TRIALS);
        int x;
        int y;
        int z;

        /* Perform the requested number of trials */
        for (x=0; x < TRIALS; x++) {

          printf("\nTrial [%i]: ", x);

          // int randNumber[sampleSize];
          int randNumber[5] = {1,1,2,2,3};
          // /* Generate the random sample data and add to an array */
          for (y=0; y < sampleSize; y++) {
          //   randNumber[y] = rand() % 365 + 1;
            printf("%i ", randNumber[y]);
          }

          /* Now loop through and check to see if duplicate items exist */
          int dupNumber[sampleSize];
          int dupFound;
          for (y=0; y < sampleSize; y++) {
            for (z=0; z < sampleSize; z++) {
              if (randNumber[y] == randNumber[z]) {
                dupNumber[y]++;                
              }
            }
            printf("\nNumber of (%i): %i", randNumber[y], dupNumber[y]);
          }

        }
        printf("\n");
        //fputs(buffer, outFile);
      }
    }

  }

  fclose(inFile);
  fclose(outFile);
  return 0;

}
