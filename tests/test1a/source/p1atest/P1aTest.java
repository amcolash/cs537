package p1atest;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author jmishra
 */
public class P1aTest {

    private static int score;
    private static List<String> messages = new ArrayList<String>();
    private static List<SingleEntry> entries = new ArrayList<SingleEntry>();

    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length != 1) {
            System.out.println("Usage java -jar ~cs537-2/ta/tests/test1a/P1aTest.jar path-to-your-source-DIRECTORY");
            System.exit(0);
        }
        File sourceDir = new File(args[0]);
        if (sourceDir.isFile()) {
            System.out.println("You might have entered a path to a file instead of a directory!");
            System.out.println("Usage java -jar ~cs537-2/ta/tests/test1a/P1aTest.jar path-to-your-source-DIRECTORY");
            System.exit(0);
        }
        File source = new File(sourceDir.getCanonicalPath() + "/paradox.c");
        if (!source.exists()) {
            messages.add("The source file does not exist. Are you calling it paradox.c? You get a 0");
            score = 0;
            displaySummaryAndExit(messages, score);
        }
 
        File input = new File("/u/c/s/cs537-2/ta/tests/test1a/input");
        
        File output = new File(sourceDir.getCanonicalPath() + "/output");

        String binaryPath = source.getParentFile().getCanonicalPath()
                + "/paradox.o";

        Process compiler = Runtime.getRuntime().exec("gcc -O -Wall -o "
                + binaryPath + " " + source.getCanonicalPath());
        
        Thread.sleep(5000);

        BufferedReader compilerOutput = new BufferedReader(
                new InputStreamReader(compiler.getInputStream()));

        BufferedReader compilerError = new BufferedReader(new InputStreamReader(
                compiler.getErrorStream()));

        String linesFromOutput, linesFromError;

        while ((linesFromError = compilerError.readLine()) != null) {
            if (linesFromError.toLowerCase().contains("error")) {
                messages.add("Your program failed to compile! - You get a 0");
                score = 0;
                displaySummaryAndExit(messages, score);
            }
        }

        // Time to run the program
        Process changeToExecutable = Runtime.getRuntime().exec("chmod +x "
                + binaryPath);
        
        Thread.sleep(2000);

        // Check command line validation and bad input file errors
        Process paradoxCommandLine0 = Runtime.getRuntime().exec(binaryPath
                + " -m " + input.getCanonicalPath() + " -o " + output
                .getCanonicalPath());
        BufferedReader paradoxCommandLineError0 = new BufferedReader(
                new InputStreamReader(
                        paradoxCommandLine0.getErrorStream()));

        Process paradoxCommandLine1 = Runtime.getRuntime().exec(binaryPath
                + " -i " + input.getCanonicalPath() + " -m " + output
                .getCanonicalPath());
        BufferedReader paradoxCommandLineError1 = new BufferedReader(
                new InputStreamReader(
                        paradoxCommandLine1.getErrorStream()));
        
        Thread.sleep(5000);

        String linesFromCommandLine0;
        boolean correctMessageFound0 = false;
        while ((linesFromCommandLine0 = paradoxCommandLineError0.readLine())
                != null) {
            if (linesFromCommandLine0.toLowerCase().contains("usage")) {
                correctMessageFound0 = true;
            }
        }

        String linesFromCommandLine1;
        boolean correctMessageFound1 = false;
        while ((linesFromCommandLine1 = paradoxCommandLineError1.readLine())
                != null) {
            if (linesFromCommandLine1.toLowerCase().contains("usage")) {
                correctMessageFound1 = true;
            }
        }        

        Process paradoxNonexistentInputFile = Runtime.getRuntime().exec(
                binaryPath + " -i " + input.getCanonicalPath() + "xyz -o "
                + output.getCanonicalPath());
        BufferedReader paradoxNonexistentInputFileError = new BufferedReader(
                new InputStreamReader(
                        paradoxNonexistentInputFile.getErrorStream()));

        String linesFromNonexistentInputFile;
        boolean correctMessageFound2 = false;
        while ((linesFromNonexistentInputFile = paradoxNonexistentInputFileError
                .readLine()) != null) {
            if (linesFromNonexistentInputFile.toLowerCase().contains("open")) {
                correctMessageFound2 = true;
            }
        }
        
        Thread.sleep(5000);
        
        if (correctMessageFound0 && correctMessageFound1) {
            messages.add("Command line validation tests passed - 5 points gained");
            score += 5;
        } else {
            messages.add("Command line validation tests failed - 5 points lost");
        }

        if (correctMessageFound2) {
            messages.add("Nonexistent input file error message test passed - 5 points gained");
            score += 5;
        } else {
            messages.add("Nonexistent input file error message test failed - 5 points lost");
        }

        setupEntries();

        Process paradox = Runtime.getRuntime().exec(binaryPath + " -i " + input
                .getCanonicalPath() + " -o " + output.getCanonicalPath());
        
        Thread.sleep(30000);

        // Test output file starts here
        // Does it even exist?
        if (!output.exists()) {
            messages.add(
                    "Output file does not exist. Do you create an output file and write probabilities into that? Cannot continue!");
            displaySummaryAndExit(messages, score);
        } else {
            BufferedReader outputFile = new BufferedReader(
                    new FileReader(output));
            // Inspect the output lines
            int count = 0;
            String linesFromProgramOutput;
            boolean faultyFormatting = false;
            while ((linesFromProgramOutput = outputFile.readLine()) != null) {
                if (linesFromProgramOutput.isEmpty()) {
                    ++count;
                    continue;
                }
                if (count > (entries.size() - 1)) {
                    break;
                }
                if ((linesFromProgramOutput.length() != 4)
                        || (linesFromProgramOutput.charAt(1) != '.')
                        || (!isProperNumber(linesFromProgramOutput))) {
                    faultyFormatting = true;
                }
                SingleEntry entry = entries.get(count);
                if (isProperNumber(linesFromProgramOutput)) {
                    entry.setObservedProbability(Double.parseDouble(
                            linesFromProgramOutput));
                    entry.setNoOutputFound(false);
                } else {
                    entry.setNoOutputFound(true);
                }
                ++count;
            }
            if (!faultyFormatting) {
                messages.add(
                        "Floating point formatting test passed - 5 points gained");
                score += 5;
            } else {
                messages.add("Floating point formatting test failed - 5 points lost");
            }
        }

        for (SingleEntry filledEntry : entries) {
            if (filledEntry.isNoOutputFound()) {
                messages.add(
                        "Output Probability not found for N = " + filledEntry
                        .getN() + " in your output file - 1 point lost");
                continue;
            }
            if (filledEntry.getObservedProbability() > 1.00 || filledEntry
                    .getObservedProbability() < 0) {
                messages.add(
                        "Output Probability for N = " + filledEntry.getN() + " is either less than 0 or more than 1 - 1 point lost");
                continue;
            }
            double lowerRange
                    = filledEntry.getMinAllowed();
            double upperRange
                    = filledEntry.getMaxAllowed();
            if ((filledEntry.getObservedProbability() >= lowerRange) && (filledEntry
                    .getObservedProbability() <= upperRange)) {
                messages.add(
                        "Output probability for N = " + filledEntry.getN() + " passed tests - 1 point gained");
                score += 1;
            } else {
                messages.add(
                        "Output probability for N = " + filledEntry.getN() + " falied tests - 1 point lost");
            }
        }

        displaySummaryAndExit(messages, score);

    }

    private static void displaySummaryAndExit(List<String> list, int score) {
        System.out.println(
                "The test run generated the following messages:");
        for (String s : messages) {
            System.out.println(s);
        }
        System.out.println("Your score out of 90 is " + score);
        System.exit(0);
    }

    private static boolean isProperNumber(String number) {
        try {
            double d = Double.parseDouble(number);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }

    private static void setupEntries() throws FileNotFoundException, IOException {
        BufferedReader outputFile = new BufferedReader(
                new FileReader("/u/c/s/cs537-2/ta/tests/test1a/correct"));
        
        String linesFromCorrectOutput;

        while ((linesFromCorrectOutput = outputFile.readLine()) != null) {
            SingleEntry entry = new SingleEntry();
            String parts[] = linesFromCorrectOutput.split(",");
            entry.setN(Integer.parseInt(parts[0]));
            entry.setMinAllowed(Double.parseDouble(parts[1]));
            entry.setMaxAllowed(Double.parseDouble(parts[2]));
            entries.add(entry);
        }
    }

}