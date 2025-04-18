#include "StudentSystem.h"
#include <iostream>

int main() {
    // Create adapter that makes legacy system compatible with modern interface
    std::unique_ptr<ModernStudentSystem> adaptedSystem = std::make_unique<StudentSystemAdapter>();
    
    // Client code works with the modern interface via adapter
    StudentManagementClient client(adaptedSystem.get());
    
    std::cout << "Welcome to Student Management System\n";
    std::cout << "====================================\n";
    
    // Adding students through the adapter
    client.registerNewStudent(1001, "John Smith", 3.75);
    client.registerNewStudent(1002, "Emily Johnson", 3.92);
    client.registerNewStudent(1003, "Michael Brown", 3.45);
    
    // Displaying students
    std::cout << "\nStudent Records:\n";
    std::cout << "----------------\n";
    client.displayAllStudents();

    // Removing a student
    std::cout << "\nRemoving student with ID 1002...\n";
    client.removeStudent(1002);

    // Displaying students after removal
    std::cout << "\nUpdated Student Records:\n";
    std::cout << "-------------------------\n";
    client.displayAllStudents();

    // Updating student details
    std::cout << "\nUpdating details for student with ID 1003...\n";
    client.updateStudentDetails(1003, "Michael Brown Jr.", 3.85);

    // Displaying students after update
    std::cout << "\nFinal Student Records:\n";
    std::cout << "-----------------------\n";
    client.displayAllStudents();

    return 0;
}
