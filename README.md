
Adapter Design Pattern Example: Student Management System
Problem Statement
In software development, we often encounter situations where we need to integrate new code with existing legacy systems. These legacy systems might have interfaces that are not compatible with our current requirements. There are two solutions to this problem:

Rewrite the legacy code: This is a time-consuming, risky, and expensive process.
Create an adapter: This allows the legacy code to work with the new system.
This project demonstrates the second approach using the Adapter Design Pattern.

Project Overview
This project implements a simple Student Management System with the following components:

Modern Interface (ModernStudentSystem): The interface our client code expects to work with.
Legacy System (LegacyStudentDatabase): The legacy student database system with an incompatible interface.
Adapter (StudentSystemAdapter): A class that makes the legacy system compatible with the modern interface.
Client (StudentManagementClient): The client that interacts with the modern interface.
The Adapter Design Pattern
What is the Adapter Pattern?
The Adapter Pattern is a structural design pattern that allows objects with incompatible interfaces to collaborate. It acts as a bridge between two incompatible interfaces by wrapping an instance of one class and exposing it through a different interface.

Structure of the Adapter Pattern
Target: The interface that clients use (ModernStudentSystem).
Adaptee: The existing class with an incompatible interface (LegacyStudentDatabase).
Adapter: The class that adapts the Adaptee to the Target interface (StudentSystemAdapter).
Client: The entity that collaborates with objects conforming to the Target interface (StudentManagementClient).
Problem Addressed by the Adapter Pattern
The Adapter Pattern solves the following problems:

Integrating legacy systems with new code.
Making third-party libraries work with your existing code.
Allowing objects with different interfaces to work together.
Why Use the Adapter Pattern in This Project?
In our Student Management System, we have:

A legacy student database system that stores and retrieves student records.
A need to create a new modern system, without rewriting the legacy code.
Interfaces that don't match (e.g., different method names, parameter types).
The Adapter Pattern allows us to:

Reuse the existing legacy code.
Present a clean, modern interface to client code.
Make future changes to either side with minimal impact.
Implementation Details
The Target Interface (ModernStudentSystem)
Defines the interface expected by client code:

C++
class ModernStudentSystem {
public:
    virtual ~ModernStudentSystem() = default;
    virtual void addStudent(int id, const std::string& name, double gpa) = 0;
    virtual std::vector<std::string> getAllStudentsInfo() const = 0;
    virtual int getTotalStudents() const = 0;
};
The Legacy System (LegacyStudentDatabase)
Represents our existing legacy code with an incompatible interface:

C++
class LegacyStudentDatabase {
public:
    void insertStudentRecord(int studentId, const std::string& fullName, float academicScore);
    int getRecordCount() const;
    std::vector<std::string> fetchAllRecords() const;
};
The Adapter (StudentSystemAdapter)
Implements the target interface and delegates calls to the legacy system:

C++
class StudentSystemAdapter : public ModernStudentSystem {
private:
    std::unique_ptr<LegacyStudentDatabase> legacySystem;

public:
    StudentSystemAdapter() : legacySystem(std::make_unique<LegacyStudentDatabase>()) {}

    void addStudent(int id, const std::string& name, double gpa) override {
        float academicScore = static_cast<float>(gpa); // Convert GPA (double) to academicScore (float)
        legacySystem->insertStudentRecord(id, name, academicScore);
    }

    std::vector<std::string> getAllStudentsInfo() const override {
        return legacySystem->fetchAllRecords();
    }

    int getTotalStudents() const override {
        return legacySystem->getRecordCount();
    }
};
How the Adapter Solves the Problem
The adapter implements the modern interface that our client code expects.
Internally, it delegates calls to the legacy system.
It handles any necessary data conversion (e.g., double to float).
The client code interacts with the legacy system without knowing its details.
Benefits of This Implementation
Separation of Concerns: The client code doesn't need to know about the legacy system.
Single Responsibility Principle: Each class has a clear, focused responsibility.
Open/Closed Principle: The system is extended without modifying existing code.
Reusability: The legacy code is reused without changes.
When to Use the Adapter Pattern
The Adapter Pattern is useful in the following scenarios:

You want to use an existing class, but its interface doesn't match what you need.
You need to use several existing subclasses, but adapting their interface via subclassing is impractical.
You need to create a reusable class that works with classes having incompatible interfaces.
You need to integrate classes that can't be altered (e.g., third-party libraries or legacy code).
Testing the Adapter Pattern
This project includes Google Test cases to verify:

The adapter correctly forwards method calls to the legacy system.
Data conversion between interfaces works as expected.
The client interacts seamlessly with the adapted system.
These tests ensure that our implementation of the Adapter Pattern is functional and robust.

Conclusion
The Adapter Design Pattern provides an elegant solution for working with incompatible interfaces. In our Student Management System, it enabled us to reuse a legacy student database system without modifications, while exposing a clean and modern interface to client code.

Building and Running
To build and run the project:

bash
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
