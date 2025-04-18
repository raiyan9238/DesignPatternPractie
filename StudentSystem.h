#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

// Target interface that our client code expects
class ModernStudentSystem {
public:
    virtual ~ModernStudentSystem() = default;
    virtual void addStudent(int id, const std::string& name, double gpa) = 0;
    virtual void removeStudent(int id) = 0; // New method to remove a student
    virtual void updateStudentDetails(int id, const std::string& name, double gpa) = 0; // New method to update details
    virtual std::vector<std::string> getAllStudentsInfo() const = 0;
    virtual int getTotalStudents() const = 0;
};

// Legacy (adaptee) class with incompatible interface
class LegacyStudentDatabase {
private:
    struct StudentRecord {
        int studentId;
        std::string fullName;
        float academicScore;
    };
    std::vector<StudentRecord> records;

public:
    // Legacy method to insert a record
    void insertStudentRecord(int studentId, const std::string& fullName, float academicScore) {
        records.push_back({studentId, fullName, academicScore});
        std::cout << "Legacy system: Added student with ID " << studentId << std::endl;
    }

    // Legacy method to remove a record
    void deleteStudentRecord(int studentId) {
        auto it = std::remove_if(records.begin(), records.end(),
                                 [studentId](const StudentRecord& record) {
                                     return record.studentId == studentId;
                                 });
        if (it != records.end()) {
            records.erase(it, records.end());
            std::cout << "Legacy system: Removed student with ID " << studentId << std::endl;
        } else {
            std::cout << "Legacy system: Student with ID " << studentId << " not found" << std::endl;
        }
    }

    // Legacy method to update a record
    void updateStudentRecord(int studentId, const std::string& fullName, float academicScore) {
        for (auto& record : records) {
            if (record.studentId == studentId) {
                record.fullName = fullName;
                record.academicScore = academicScore;
                std::cout << "Legacy system: Updated student with ID " << studentId << std::endl;
                return;
            }
        }
        std::cout << "Legacy system: Student with ID " << studentId << " not found" << std::endl;
    }

    // Legacy method to retrieve records count
    int getRecordCount() const {
        return records.size();
    }

    // Legacy method to get student information
    std::vector<std::string> fetchAllRecords() const {
        std::vector<std::string> result;
        for (const auto& record : records) {
            result.push_back("ID: " + std::to_string(record.studentId) +
                             ", Name: " + record.fullName +
                             ", Score: " + std::to_string(record.academicScore));
        }
        return result;
    }
};

// Adapter class - adapts LegacyStudentDatabase to ModernStudentSystem interface
class StudentSystemAdapter : public ModernStudentSystem {
private:
    std::unique_ptr<LegacyStudentDatabase> legacySystem;

public:
    StudentSystemAdapter() : legacySystem(std::make_unique<LegacyStudentDatabase>()) {}

    void addStudent(int id, const std::string& name, double gpa) override {
        float academicScore = static_cast<float>(gpa);
        legacySystem->insertStudentRecord(id, name, academicScore);
    }

    void removeStudent(int id) override {
        legacySystem->deleteStudentRecord(id);
    }

    void updateStudentDetails(int id, const std::string& name, double gpa) override {
        float academicScore = static_cast<float>(gpa);
        legacySystem->updateStudentRecord(id, name, academicScore);
    }

    std::vector<std::string> getAllStudentsInfo() const override {
        return legacySystem->fetchAllRecords();
    }

    int getTotalStudents() const override {
        return legacySystem->getRecordCount();
    }
};

// Client class that works with the ModernStudentSystem interface
class StudentManagementClient {
private:
    ModernStudentSystem* system;

public:
    StudentManagementClient(ModernStudentSystem* system) : system(system) {}

    void registerNewStudent(int id, const std::string& name, double gpa) {
        system->addStudent(id, name, gpa);
    }

    void removeStudent(int id) {
        system->removeStudent(id);
    }

    void updateStudentDetails(int id, const std::string& name, double gpa) {
        system->updateStudentDetails(id, name, gpa);
    }

    void displayAllStudents() const {
        std::cout << "Total Students: " << system->getTotalStudents() << std::endl;
        auto students = system->getAllStudentsInfo();
        for (const auto& info : students) {
            std::cout << info << std::endl;
        }
    }
};
