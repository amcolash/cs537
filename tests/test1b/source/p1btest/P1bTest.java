package p1btest;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

/**
 *
 * @author jmishra
 */
public class P1bTest {

    private static int score;
    private static List<String> messages = new ArrayList<String>();
    private static Process runxv6;
    private static long diff;

    @SuppressWarnings("empty-statement")
    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length != 1) {
            System.out.println("Usage java -jar ~cs537-2/ta/tests/test1b/P1bTest.jar path-to-your-xv6-root-source-DIRECTORY");
            System.exit(0);
        }

        File sourceDir = new File(args[0]);
        if (sourceDir.isFile()) {
            System.out.println("You might have entered a path to a file instead of a directory!");
            System.out.println("Usage java -jar ~cs537-2/ta/tests/test1b/P1bTest.jar path-to-your-xv6-root-source-DIRECTORY");
            System.exit(0);
        }
        
        System.out.println("This test takes about 45 seconds to finish. Please wait...");
        // Copy tester.c
        String xv6Path = sourceDir.getCanonicalPath();
        Process copyTester = Runtime.getRuntime().exec("cp /u/c/s/cs537-2/ta/tests/test1b/tester.c " + xv6Path + "/user/");        

        Thread.sleep(1000);
        
        //make
        Process make = Runtime.getRuntime().exec("make -C " + xv6Path + "/");               
        
        Thread.sleep(30000);
        
        CoreTest coreTestRunnable = new CoreTest();
                        
        if (make.exitValue() != 0) {
            messages.add("Your xv6 code failed to compile. You get a 0");
            score = 0;
            displaySummaryAndExit(messages, score, coreTestRunnable);
        }
        
        coreTestRunnable.setXv6Path(xv6Path);
        Thread coreTest = new Thread(coreTestRunnable);
        coreTest.start();
        
        coreTest.join(20000);

        if (coreTestRunnable.isCrashed()) {
            messages.add("Your kernel crashed/is taking a very long time while booting. You get a 0");
            score = 0;
            displaySummaryAndExit(messages, score, coreTestRunnable);
        }

        if (coreTestRunnable.isFound22675()) {
            messages.add("Test for initialization of counter to 0 passed - 25 points gained");
            score += 25;
        } else {
            messages.add("Counter not initialized to zero - You get a 0");
            score = 0;
            displaySummaryAndExit(messages, score, coreTestRunnable);
        }

        if (coreTestRunnable.isFound27385()) {
            messages.add("Test for addition of 20 numbers passed - 35 points gained");
            score += 35;
        } else {
            messages.add("Test for addition of 20 numbers failed - 35 points lost - No further testing");
            displaySummaryAndExit(messages, score, coreTestRunnable);
        }

        if (coreTestRunnable.isFound54770()) {
            messages.add("Test for addition in a second process passed - 10 points gained");
            score += 10;
        } else {
            messages.add("Test for addition in a second process failed - 10 points lost");
            displaySummaryAndExit(messages, score, coreTestRunnable);
        }
        displaySummaryAndExit(messages, score, coreTestRunnable);
    }

    private static void displaySummaryAndExit(List<String> list, int score, CoreTest ct) throws InterruptedException {
        System.out.println(
                "The test run generated the following messages:");
        for (String s : messages) {
            System.out.println(s);
        }
        System.out.println("Your score out of 70 is " + score);
        if (ct.getRunxv6() != null) {
            ct.getRunxv6().destroy();
        }        
        Thread.sleep(3000);
        System.exit(0);
    }

}