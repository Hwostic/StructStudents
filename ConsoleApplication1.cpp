//СТРУКТУРА СТУДЕНТЫ 

#include <iostream>
using namespace std;

const int SIZE = 5;
struct Address
{
    char street[100];
    char city[50];
    int postalCode;

};


struct Grade {
    char subject[100];
      int grade;
};

struct Student {
    char firstName[50];
    char lastName[50];
    Address address;
    Grade grades[SIZE];
};

struct StudentList {
    Student* students;
    int capacity;
    int count = 0;
};


void fillStudent(Student& student,
    const char* firstName,
    const char* lastName,
    const char* street,
    const char* city,
    int postalCode,
    int* grade,
    const char* subject[])
{
    strncpy_s(student.firstName, firstName, sizeof(student.firstName) - 1);
    student.firstName[sizeof(student.firstName) - 1] = '\0';
    strncpy_s(student.lastName, lastName, sizeof(student.lastName) - 1);
    student.lastName[sizeof(student.lastName) - 1] = '\0';
    strncpy_s(student.address.street, street, sizeof(student.address.street) - 1);
    student.address.street[sizeof(student.address.street) - 1] = '\0';
    strncpy_s(student.address.city, city, sizeof(student.address.city) - 1);
    student.address.city[sizeof(student.address.city) - 1] = '\0';


    student.address.postalCode = postalCode;


    for (int i = 0; i < SIZE; i++)
    {
        student.grades[i].grade = grade[i];
        strncpy_s(student.grades[i].subject, subject[i], sizeof(student.grades[i].subject)-1);
        student.grades[i].subject[sizeof(student.grades[i].subject) - 1] = '\0';
    }
}
void printStudent(Student& student)
{

    cout << "Student: " << endl << student.firstName << " "
        << student.lastName << endl
        << "Address: " << student.address.city << ", "
        << student.address.street << ", "
        << student.address.postalCode << endl << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "Predmet: " << student.grades[i].subject << " Grade: " << student.grades[i].grade << endl << endl;
    }
    cout << "__________________________" <<endl ;
}

void addStudent(StudentList& list, Student student)
{
    if (list.count ==list.capacity)
    {
        list.capacity *= 2;
        Student* newList = new Student[list.capacity];
        for (int i = 0; i < list.count; i++)
            {
                newList[i] = list.students[i];
            }
        delete[] list.students;
        list.students = newList;
    }
   
    list.students[list.count++] = student;

}

void findAndDeleteStudentLastName(StudentList& list, const char* lastName) //поиск по фамилии
{
    bool isDelete = false;
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(list.students[i].lastName, lastName) == 0)
        {
            list.students[i] = list.students[i+1];
            list.count--;
            isDelete = true;
        }
      
    }
    if (!isDelete)
    {
        cout << "Такого студента нет"<<endl;
    }
    
    
}



void printStudentList(StudentList list)
{
    for (int i = 0; i < list.count; i++)
    {
        printStudent(list.students[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "RU");

    Student student;
    Student student2;
    int arr[] = { 5,4,3,4,5 };
  
    const char* subject[] = {"Mathematic","Fysic","English","History","Geometry"};
    fillStudent(student, "Ivan", "Ivanov", "Street", "City", 150, arr, subject);
    fillStudent(student2, "Petr", "Petrov", "Street", "Scotland", 150, arr, subject);
    StudentList list;
    list.capacity = 2;
    list.students = new Student[list.capacity];

    
    
    addStudent(list, student);
    addStudent(list, student2);
    printStudentList(list);
    findAndDeleteStudentLastName(list, "Ivano");
    printStudentList(list);
 
}

