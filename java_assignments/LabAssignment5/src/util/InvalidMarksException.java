package util;

/**
 * Custom exception for invalid marks input
 * Demonstrates custom exception handling
 */
public class InvalidMarksException extends Exception {
    public InvalidMarksException(String message) {
        super(message);
    }

    public InvalidMarksException(String message, Throwable cause) {
        super(message, cause);
    }
}