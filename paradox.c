#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 1000

int main() {

  /* Declare variables */
  FILE * inFile;
  FILE * outFile;
  char buffer [100];
  int sampleSize;
  int dupTrials;

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
    rand();

    /* Loop through input file */
    while ( fgets(buffer, 100, inFile) != NULL ) {
      sampleSize = atoi(buffer);
      if (sampleSize > 0) {
        // printf("======================================================================\nSamples: %i, Trials: %i\n", sampleSize, TRIALS);
        int x;
        int y;
        int z;
        dupTrials = 0;


        /* Perform the requested number of trials */
        for (x=0; x < TRIALS; x++) {
          //printf("Trial [%i]: ", x);

          // /* Generate the random sample data and add to an array */
          int randNumber[sampleSize];
          for (y=0; y < sampleSize; y++) {
            randNumber[y] = rand() % 365 + 1;
            //printf("%i ", randNumber[y]);
          }
          //printf("\n");

          /* Create array to be used in checking of duplicates */
          int dupNumber[sampleSize];
          int a;
          for (a=0; a < sampleSize; a++) {
            dupNumber[a] = 0;
          }

          /* Loop through the random array and find duplicates */
          int dupFound;
          dupFound = 0;
          for (y=0; y < sampleSize; y++) {
            for (z=0; z < sampleSize; z++) {
              if (randNumber[y] == randNumber[z]) {
                dupNumber[y]++;
                if (dupNumber[y] > 1) {
                  dupFound = 1;
                  //printf("Dup Found! (%i)\n", randNumber[y]);
                }
              }
            }
            // printf("\nNumber of (%i): %i", randNumber[y], dupNumber[y]);
          }


          if (dupFound == 1) {
            // printf("+++Duplicate found.\n");
            dupTrials++;
          } else {
            // printf("---No duplicate found.\n");
          }

        }
        float ratio;
        ratio = ((float)dupTrials / (float)TRIALS);
        printf("Samples: %i, Trials: %i, Ratio: (%i / %i) = %f\n", sampleSize, TRIALS, dupTrials, TRIALS, ratio);
        //fputs(buffer, outFile);
      }
    }

  }

  fclose(inFile);
  fclose(outFile);
  return 0;

}
