package p1atest;


public class SingleEntry {

    private int n;
    private double observedProbability;
    private double minAllowed, maxAllowed;
    private boolean noOutputFound = true;

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    public double getObservedProbability() {
        return observedProbability;
    }

    public void setObservedProbability(double observedProbability) {
        this.observedProbability = observedProbability;
    }

    public boolean isNoOutputFound() {
        return noOutputFound;
    }

    public void setNoOutputFound(boolean noOutputFound) {
        this.noOutputFound = noOutputFound;
    }

    public double getMinAllowed() {
        return minAllowed;
    }

    public void setMinAllowed(double minAllowed) {
        this.minAllowed = minAllowed;
    }

    public double getMaxAllowed() {
        return maxAllowed;
    }

    public void setMaxAllowed(double maxAllowed) {
        this.maxAllowed = maxAllowed;
    }
   
}