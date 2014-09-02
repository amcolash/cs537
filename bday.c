#include <stdio.h>

int main() {

  /* Declare variables */
  FILE * inFile;
  FILE * outFile;
  char buffer [100];

  /* Initialize files */
  inFile = fopen("sampleIn.txt", "r");
  outFile = fopen("sampleOut.txt", "w");

  if (inFile == NULL || outFile == NULL) {
    fprintf(stderr, "Cannot open file\n");
    fclose(inFile);
    fclose(outFile);
    return 1;

  } else {
    /* Loop through input file */
    while ( fgets(buffer, 100, inFile) != NULL ) {
      printf("%s", buffer);
    }

  }

  fclose(inFile);
  fclose(outFile);
  return 0;

}
