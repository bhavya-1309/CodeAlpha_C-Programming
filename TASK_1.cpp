#include <iostream>
using namespace std;

void inputCourseData(float grades[], float credits[], int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        cout << "\nEnter details for Course " << i + 1 << ":\n";

        cout << "  Grade (0.0 - 10.0): ";
        cin >> grades[i];

        while (grades[i] < 0.0 || grades[i] > 10.0) {
            cout << "  Invalid grade. Enter again (0.0 - 10.0): ";
            cin >> grades[i];
        }

        cout << "  Credit Hours: ";
        cin >> credits[i];

        while (credits[i] <= 0) {
            cout << "  Credit hours must be positive. Enter again: ";
            cin >> credits[i];
        }
    }
}

void calculateCGPA(const float grades[], const float credits[], int numCourses, float& totalGradePoints, float& totalCredits) {
    totalGradePoints = 0;
    totalCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        totalGradePoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }
}

void displayResults(const float grades[], const float credits[], int numCourses, float totalCredits, float totalGradePoints) {
    cout << "\n===== COURSE DETAILS =====\n";
    for (int i = 0; i < numCourses; i++) {
        cout << "Course " << i + 1 << " -> Grade: " << grades[i]
             << ", Credit Hours: " << credits[i] << endl;
    }

    float cgpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0;

    cout << "\nTotal Credit Hours: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Final CGPA (Out of 10): " << cgpa << endl;
}

int main() {
    const int MAX_COURSES = 100;
    float grades[MAX_COURSES], credits[MAX_COURSES];
    int numCourses;
    float totalGradePoints, totalCredits;

    cout << "===== CGPA CALCULATOR =====\n";
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    while (numCourses <= 0 || numCourses > MAX_COURSES) {
        cout << "Invalid number of courses. Please enter between 1 and " << MAX_COURSES << ": ";
        cin >> numCourses;
    }

    inputCourseData(grades, credits, numCourses);
    calculateCGPA(grades, credits, numCourses, totalGradePoints, totalCredits);
    displayResults(grades, credits, numCourses, totalCredits, totalGradePoints);

    return 0;
}