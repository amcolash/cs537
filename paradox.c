#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#define TRIALS 1000

void usage() {
  fprintf(stderr, "usage: paradox -i inputfile -o outputfile\n");
  exit(1);
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  FILE * inFile;
  FILE * outFile;
  char buffer [1024];
  char iFile[1024];
  char oFile[1024];
  int option;
  int sampleSize;
  int dupTrials;
  int * randNumber;
  int * dupNumber;

  if (argc != 5 ) {
    usage();
  }

  while ((option = getopt(argc, argv, "i:o:")) != -1) {
    switch (option) {
      case 'i':
        sprintf(iFile, "%s", optarg);
        //iFile = optarg;
        break;
      case 'o':
        sprintf(oFile, "%s", optarg);
        //oFile = optarg;
        break;
      case '?':
        usage();
        break;
    }
  }

  /* Initialize files */
  inFile = fopen(iFile, "r");
  if (inFile == NULL) {
    fprintf(stderr, "Error: Cannot open input file: %s\n", iFile);
    exit(1);
  }

  outFile = fopen(oFile, "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error: Cannot open output file: %s\n", oFile);
    exit(1);
  }

  /* Initialze random number generator */
  srand(time(NULL));
  rand();

  /* Loop through input file */
  while ( fgets(buffer, 1024, inFile) != NULL ) {
    sampleSize = atoi(buffer);
    // printf("======================================================================\nSamples: %i, Trials: %i\n", sampleSize, TRIALS);
    int x;
    int y;
    int z;
    dupTrials = 0;


    /* Perform the requested number of trials */
    for (x=0; x < TRIALS; x++) {
      //printf("Trial [%i]: ", x);

      /* Generate the random sample data and add to an array */
      /* Also make an array of duplicate number counts and reset it */
      randNumber = (int*) malloc(sampleSize * sizeof(int));
      dupNumber = (int*) malloc(sampleSize * sizeof(int));
      for (y=0; y < sampleSize; y++) {
        randNumber[y] = rand() % 365 + 1;
        dupNumber[y] = 0;
      }
      //printf("\n");

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

      /* Clean up memory */
      free(randNumber);
      free(dupNumber);

      if (dupFound == 1) {
        dupTrials++;
      }

    }
    float ratio;
    ratio = ((float)dupTrials / (float)TRIALS);
    printf("Samples: %i, Trials: %i, Ratio: (%i / %i) = %.2f\n", sampleSize, TRIALS, dupTrials, TRIALS, ratio);
    sprintf(buffer, "%.2f\n", ratio);
    fputs(buffer, outFile);
  }

  fclose(inFile);
  fclose(outFile);
  exit(0);
}
