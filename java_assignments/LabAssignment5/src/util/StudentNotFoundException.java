package util;

/**
 * Custom exception for when a student is not found
 * Demonstrates custom exception handling
 */
public class StudentNotFoundException extends Exception {
    public StudentNotFoundException(String message) {
        super(message);
    }

    public StudentNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }
}