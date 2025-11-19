package util;

/**
 * Loader class implementing Runnable for multithreading
 * Simulates loading process with a progress indicator
 */
public class Loader implements Runnable {
    private String message;
    private int duration; // in milliseconds

    public Loader(String message, int duration) {
        this.message = message;
        this.duration = duration;
    }

    @Override
    public void run() {
        try {
            System.out.print(message);
            int steps = duration / 200; // Number of dots to display
            
            for (int i = 0; i < steps; i++) {
                Thread.sleep(200);
                System.out.print(".");
            }
            System.out.println(" Done!");
            
        } catch (InterruptedException e) {
            System.out.println("\nLoading interrupted: " + e.getMessage());
            Thread.currentThread().interrupt();
        }
    }

    /**
     * Static method to simulate loading with default message
     * @param message Loading message
     */
    public static void simulateLoading(String message) {
        Loader loader = new Loader(message, 1000);
        Thread thread = new Thread(loader);
        thread.start();
        try {
            thread.join(); // Wait for loading to complete
        } catch (InterruptedException e) {
            System.out.println("Loading interrupted");
            Thread.currentThread().interrupt();
        }
    }
}