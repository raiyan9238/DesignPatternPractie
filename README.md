# Adapter Design Pattern Example: Student Management System

## Problem Statement

In software development, we often encounter situations where we need to integrate new code with existing legacy systems. These legacy systems might have interfaces that are not compatible with our current requirements. We have two options:

1. Rewrite the legacy code (time-consuming, risky, and expensive)
2. Create an adapter that allows the legacy code to work with the new system

This project demonstrates the second approach using the Adapter Design Pattern.

## Project Overview

This project implements a simple Student Management System with the following components:

1. A modern interface (`ModernStudentSystem`) that our client code expects to work with
2. A legacy student database system (`LegacyStudentDatabase`) with an incompatible interface
3. An adapter (`StudentSystemAdapter`) that makes the legacy system compatible with the modern interface
4. A client (`StudentManagementClient`) that works with the modern interface

## The Adapter Design Pattern

### What is the Adapter Pattern?

The Adapter Pattern is a structural design pattern that allows objects with incompatible interfaces to collaborate. It acts as a bridge between two incompatible interfaces by wrapping an instance of one class into an adapter class that presents the interface expected by clients.

### Structure of the Adapter Pattern

1. **Target**: This is the interface that clients use (`ModernStudentSystem`)
2. **Adaptee**: This is the existing class with an incompatible interface (`LegacyStudentDatabase`)
3. **Adapter**: This class adapts the Adaptee to the Target interface (`StudentSystemAdapter`)
4. **Client**: Collaborates with objects conforming to the Target interface (`StudentManagementClient`)

### Problem Addressed by the Adapter Pattern

The Adapter Pattern solves the problem of:
- Integrating legacy systems with new code
- Making third-party libraries work with your existing code
- Allowing objects with different interfaces to work together

## Why Use the Adapter Pattern in This Project?

In our Student Management System:

1. We have a legacy student database system that stores and retrieves student records
2. We want to create a new modern system without rewriting the legacy code
3. The interfaces don't match (different method names, parameter types, etc.)

The Adapter Pattern is perfect for this scenario as it allows us to:
- Reuse the existing legacy code
- Present a clean, modern interface to client code
- Make future changes to either side with minimal impact

## Implementation Details

### The Target Interface (`ModernStudentSystem`)

This interface defines what our client code expects:

```cpp
class ModernStudentSystem {
public:
    virtual ~ModernStudentSystem() = default;
    virtual void addStudent(int id, const std::string& name, double gpa) = 0;
    virtual std::vector<std::string> getAllStudentsInfo() const = 0;
    virtual int getTotalStudents() const = 0;
};
```

### The Legacy System (`LegacyStudentDatabase`)

This class represents our existing legacy code with an incompatible interface:

```cpp
class LegacyStudentDatabase {
    // ...
public:
    void insertStudentRecord(int studentId, const std::string& fullName, float academicScore);
    int getRecordCount() const;
    std::vector<std::string> fetchAllRecords() const;
};
```

### The Adapter (`StudentSystemAdapter`)

The adapter implements the target interface and delegates to the legacy system:

```cpp
class StudentSystemAdapter : public ModernStudentSystem {
private:
    std::unique_ptr<LegacyStudentDatabase> legacySystem;

public:
    StudentSystemAdapter() : legacySystem(std::make_unique<LegacyStudentDatabase>()) {}

    void addStudent(int id, const std::string& name, double gpa) override {
        // Convert the gpa (double) to academicScore (float)
        float academicScore = static_cast<float>(gpa);
        legacySystem->insertStudentRecord(id, name, academicScore);
    }

    std::vector<std::string> getAllStudentsInfo() const override {
        return legacySystem->fetchAllRecords();
    }

    int getTotalStudents() const override {
        return legacySystem->getRecordCount();
    }
};
```

### How the Adapter Solves the Problem

1. The adapter implements the modern interface that our client code expects
2. Internally, it delegates calls to the legacy system
3. It handles any necessary data conversion (like double to float)
4. The client code can work with the legacy system without knowing its details

## Benefits of This Implementation

1. **Separation of concerns**: The client code doesn't need to know about the legacy system
2. **Single Responsibility Principle**: Each class has a clear responsibility
3. **Open/Closed Principle**: We extended the system without modifying existing code
4. **Reusability**: We reused the legacy code without changes

## When to Use the Adapter Pattern

Consider using the Adapter pattern when:

1. You want to use an existing class, but its interface doesn't match what you need
2. You need to use several existing subclasses, but it's impractical to adapt their interface by subclassing each one
3. You need to create a reusable class that cooperates with classes that have incompatible interfaces
4. You need to integrate classes that can't be altered (third-party libraries, legacy code)

## Testing the Adapter Pattern

The project includes Google Test cases to verify:

1. That the adapter correctly forwards method calls to the legacy system
2. That data conversion between interfaces works correctly
3. That the client can work with the adapted system

These tests ensure that our implementation of the Adapter Pattern works as expected and handles all the required functionality.

## Conclusion

The Adapter Design Pattern provides an elegant solution to the problem of incompatible interfaces. In our Student Management System example, it allowed us to reuse a legacy student database system with a modern interface, without modifying the legacy code. This demonstrates how design patterns can solve common software development problems in a structured and reusable way.

## Building and Running

To build and run the project:

```bash
# Create a build directory
mkdir build && cd build

# Generate build files with CMake
cmake ..

# Build the project
cmake --build .

# Run the main program
./StudentSystem

# Run the tests
./StudentSystemTests
```
#   D e s i g n P a t t e r n P r a c t i e  
 