package p1btest;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

/**
 *
 * @author jmishra
 */
public class CoreTest implements Runnable {

    private Process runxv6;
    private String xv6Path;
    private boolean found22675 = false, found27385 = false, found54770 = false, crashed = true;

    @Override
    public void run() {
        try {
            runxv6 = Runtime.getRuntime().exec("make -C " + xv6Path + "/" + " qemu-nox");

            Thread.sleep(7000);

            BufferedReader qemuOutput = new BufferedReader(
                    new InputStreamReader(
                            runxv6.getInputStream()));
            BufferedWriter qemuInput = new BufferedWriter(
                    new OutputStreamWriter(
                            runxv6.getOutputStream()));
            qemuInput.append("tester");
            qemuInput.newLine();
            qemuInput.flush();

            Thread.sleep(5000);

            String linesFromQemuOutput;
            
            while ((linesFromQemuOutput = qemuOutput.readLine()) != null) {
                if (linesFromQemuOutput.contains("22675")) {
                    found22675 = true;
                }
                if (linesFromQemuOutput.contains("27385")) {
                    found27385 = true;
                }
                if (linesFromQemuOutput.contains("54770")) {
                    found54770 = true;
                }
                if (linesFromQemuOutput.toLowerCase().contains("placeholder")) {
                    crashed = false;
                }
                if (linesFromQemuOutput.toLowerCase().contains("end of tests")) {
                    break;
                }
            }
        } catch (Exception e) {
            
        }
    }

    public Process getRunxv6() {
        return runxv6;
    }

    public void setRunxv6(Process runxv6) {
        this.runxv6 = runxv6;
    }

    public String getXv6Path() {
        return xv6Path;
    }

    public void setXv6Path(String xv6Path) {
        this.xv6Path = xv6Path;
    }

    public boolean isFound22675() {
        return found22675;
    }

    public void setFound22675(boolean found22675) {
        this.found22675 = found22675;
    }

    public boolean isFound27385() {
        return found27385;
    }

    public void setFound27385(boolean found27385) {
        this.found27385 = found27385;
    }

    public boolean isFound54770() {
        return found54770;
    }

    public void setFound54770(boolean found54770) {
        this.found54770 = found54770;
    }

    public boolean isCrashed() {
        return crashed;
    }

    public void setCrashed(boolean crashed) {
        this.crashed = crashed;
    }
    
    

}
