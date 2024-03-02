#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for sort
#include <string>

using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

vector<string> tokenize(const string& s, const string& del = ",") {
    vector<string> tokens;
    size_t start = 0, end = s.find(del);
    while (end != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start));
    return tokens;
}

vector<Course> loadCoursesFromFile() {
    ifstream fin("abcu.txt", ios::in);
    vector<Course> courses;
    string line;

    while (getline(fin, line)) {
        if (line == "-1") break;

        Course course;
        vector<string> tokenizedInformation = tokenize(line);

        course.courseNumber = tokenizedInformation[0];
        course.name = tokenizedInformation[1];

        for (int i = 2; i < tokenizedInformation.size(); ++i) {
            course.prerequisites.push_back(tokenizedInformation[i]);
        }

        courses.push_back(course);
    }

    fin.close();
    return courses;
}

void printCourse(const Course& course) {
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: ";
    for (const auto& prerequisite : course.prerequisites) {
        cout << prerequisite << " ";
    }
    cout << "\n\n";
}

void printCourseList(vector<Course>& courses) {
    sort(courses.begin(), courses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : courses) {
        printCourse(course);
    }
}

void searchCourse(const vector<Course>& courses) {
    string courseNumber;
    cout << "Enter courseNumber: ";
    cin >> courseNumber;

    bool found = false;
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            found = true;
            printCourse(course);
            break;
        }
    }

    if (!found) {
        cout << "Course with given course number not found\n";
    }
}

int main() {
    vector<Course> courses;

    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "4. Exit\n";

    int choice;
    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            courses = loadCoursesFromFile();
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            searchCourse(courses);
            break;
        case 4:
            cout << "Exit\n";
            break;
        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 4);

    return 0;
}