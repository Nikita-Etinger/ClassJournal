#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
using namespace std;
#define cls system("cls")
using namespace std;
class Student;
class Journal;
class Group;
void exportTxt(Journal& journal);
void selectActionsUarterMenu(Journal& journal, int indexGroup, int indexStudent, int indexUarter);
void selectActionsStudentMenu(Journal& journal, int indexGroup, int indexStudent);
void selectGroupMenu(Journal& journal);
void selectStudentMenu(Journal& journal, int indexGroup);
void selectStudentsMenu(Journal& journal, int indexGroup);
void addGroupMenu(Journal& journal);

class Student {
    int** quarterMark=nullptr;
    int counter[4] = { 0, 0, 0, 0 };
    int resultQuarter[4]= { 0, 0, 0, 0 };
    int resultYear=0;
    int correctResultYear = 0;
    string name="";

public:
    Student() {
        quarterMark = new int* [4];
        for (int i = 0; i < 4; ++i) {
            quarterMark[i] = nullptr;
        }
    }
    Student(const std::string& newName):Student() {
        name = newName;
    }

    //// Конструктор копирования
    Student(const Student& other) : name(other.name), resultYear(other.resultYear) {
        // Глубокое копирование массива quarterMark
        quarterMark = new int* [4];
        for (int i = 0; i < 4; ++i) {
            quarterMark[i] = new int[other.counter[i]];
            for (int j = 0; j < other.counter[i]; ++j) {
                quarterMark[i][j] = other.quarterMark[i][j];
            }
            counter[i] = other.counter[i];
            resultQuarter[i] = other.resultQuarter[i];
        }
    }

    // Оператор присваивания
    Student& operator=(const Student& other) {
        if (this != &other) {
            // Освобождение памяти от текущих данных
            if (quarterMark != nullptr) {
                for (int i = 0; i < 4; ++i) {
                    if (quarterMark[i] != nullptr)
                        delete[] quarterMark[i];
                }
                if (quarterMark != nullptr)
                    delete[] quarterMark;
            }

            // Глубокое копирование массива quarterMark
            quarterMark = new int* [4];
            for (int i = 0; i < 4; ++i) {
                quarterMark[i] = new int[other.counter[i]];
                for (int j = 0; j < other.counter[i]; ++j) {
                    quarterMark[i][j] = other.quarterMark[i][j];
                }
                counter[i] = other.counter[i];
                resultQuarter[i] = other.resultQuarter[i];
            }

            // Копирование имени и результата за год
            name = other.name;
            resultYear = other.resultYear;
        }
        return *this;
    }

    ~Student() {
        // Освобождение памяти при удалении объекта
        if (quarterMark != nullptr) {
            for (int i = 0; i < 4; ++i) {
                if (quarterMark[i] != nullptr)
                    delete[] quarterMark[i];
            }
            if (quarterMark != nullptr)
                delete[] quarterMark;
        }
    }

    void addMark(int quarter, int mark) {
        if (quarterMark[quarter] == nullptr) {
            quarterMark[quarter] = new int[1];
            counter[quarter] = 0;
        }

        int* updatedQuarterMark = new int[counter[quarter] + 1];
        for (int i = 0; i < counter[quarter]; ++i) {
            updatedQuarterMark[i] = quarterMark[quarter][i];
        }
        updatedQuarterMark[counter[quarter]] = mark;

        // Освобождение памяти старого массива перед присвоением нового массива
        delete[] quarterMark[quarter];

        quarterMark[quarter] = updatedQuarterMark;
        counter[quarter]++;
    }
    void showAllUarter() {
        cout << name << endl;
        for (int i = 0; i < 4; i++) {
            cout << "uarter " << i+1 << endl;
            showUarter(i, 0);

        }
        cout << endl;
    }
    void showUarter(int quarter, bool showIndex = false) {
        if (showIndex) {
            cout << "index|mark" << endl;
            for (int i = 0; i < counter[quarter]; i++) {
                cout << i+1 << "    |" << quarterMark[quarter][i] << endl;
            }
            
        }
        else {
            for (int i = 0; i < counter[quarter]; i++) {
                cout << quarterMark[quarter][i] << " ";
            }
        }
        cout << endl;
    }
    void editMark(int indexUarter, int indexMark, int newMark) {
        quarterMark[indexUarter][indexMark] = newMark;
    }
    string getName() {
        return name;
    }
    int getCounterUarter(int indexUarter) {
        return counter[indexUarter];
    }
    void showAdress() {
        cout << this<<endl;
    }
    void calculateResult(bool save=0) {
       /* cout << "CALC" << endl;*/
        for (int i = 0; i < 4; i++) {
            if (counter[i] != 0) {
                int sum = 0;
                for (int j = 0; j < counter[i]; j++) {
                    sum += quarterMark[i][j];
                }

                resultQuarter[i] = sum / counter[i];
                
            }
        }
        if (save) {
            if (getYearMark() > float((resultQuarter[0] + resultQuarter[1] + resultQuarter[2] + resultQuarter[3]) / 4)) {
                resultYear++;
            }
            else
                resultYear--;
        }
    }
    int showResultUarter() {
        calculateResult();
        for (int i = 0; i < 4; i++) {
            cout << "1: " << resultQuarter[i] << endl;
        }
        cout << endl;
    }
    string getImportData() {
        calculateResult(1);
        string importData = name + ";";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < counter[i]; j++) {
                importData += to_string(quarterMark[i][j]) + " ";
            }
            importData += ";";
        }
        for (int i = 0; i < 4; i++) {
            importData += to_string(resultQuarter[i]) + " ";
        }
        importData += ";";
        importData += to_string(correctResultYear);
        return importData;
    }
    void showAllUartersResult() {
        for (int i = 0; i < 4; i++) {
            calculateResult();
            cout << i+1 << "|QAURTER: " << resultQuarter[i] << endl;
        }
    }
    float getYearMark() {
        return float((float(resultQuarter[0]) + float(resultQuarter[1]) + float(resultQuarter[2]) + float(resultQuarter[3])) / 4);
    }
    void upDownYearMark(bool up) {
        if (up == 1) {
            correctResultYear = ceil( getYearMark());//округляет вверх
        }
        else correctResultYear = floor(getYearMark());//округляет вниз
    }
    int getCorrectresultYearMark() {
        return correctResultYear;
    }
};

class Group {
    string name="";
    Student* students = nullptr;
    int counter = 0;

public:
    Group() {

    }
    Group(string nameGroup) {
        name = nameGroup;
    }

    int searchStudent(string nameStudent) {
        for (int i = 0; i < counter; i++) {
            if (students[i].getName() == nameStudent)
                return i;
        }
        return -1; // Возвращаем -1, если студент не найден
    }
    string getName() {
        return name;
    }
    void showAll(bool showIndex = 0) {
        if (showIndex) {
            cout << "index|mark" << endl;
            for (int i = 0; i < counter; i++) {
                cout << i << " | " << name << endl;
            }
        }
        else for (int i = 0; i < counter; i++) {
            cout << name << endl;
        }
    }
    void showAllNameStudents(bool showIndex = 0) {
        if (counter == 0) {
            cout << "Студентов в данной группе нет" << endl << endl;
            return;
        }
        if (showIndex) {
            cout << "index|Name" << endl;
            for (int i = 0; i < counter; i++) {
                cout << i+1 << " | " << students[i].getName() << endl;
            }
        }
        else for (int i = 0; i < counter; i++) {
            cout << students[i].getName() << endl;
        }

    }
    int getCounter() {
        return counter;
    }
    void showAllUartersMarks(int indexStudent, bool showIndex = 0) {
        students[indexStudent].showAllUarter();
    }
    void showUarterStudent(int indexStudent, int indexUarter, int showIndex = 0) {
        students[indexStudent].showUarter(indexUarter, 1);

    }
    int getCounterUarter(int indexStudent, int indexUarter) {
        return students[indexStudent].getCounterUarter(indexUarter);
    }
    void addMark(int indexStudent, int indexUarter, int newMark) {
        students[indexStudent].addMark(indexUarter, newMark);
    }
    void addStudent(string nameStudent) {
        Student* buf = new Student[counter + 1];
        for (int i = 0; i < counter; i++) {
            buf[i] = students[i];
        }
        buf[counter++] = Student(nameStudent);
        delete[]students;
        students = buf;
    }
    void deleteStudent(int indexStudent){
        Student* buf = new Student[counter - 1];
        for (int i = 0; i < indexStudent; i++) {
            buf[i] = students[i];
        }
        for (int i = indexStudent + 1; i < counter; i++) {
            buf[i - 1] = students[i];
        }
        delete[]students;
        students = buf;
        counter--;
    }
    void editMark(int indexStudent,int indexUarter, int indexMark, int newMark) {
        students[indexStudent].editMark(indexUarter,indexMark, newMark);
    }
    void addStudent(const Student& newStudent) {
        Student* buf = new Student[counter + 1];
        for (int i = 0; i < counter; i++) {
            buf[i] = students[i];
        }
        buf[counter++] = newStudent;
        delete[] students;
        students = buf;
    }
    void ShowAdressStudent(int indexStudent) {
        students[indexStudent].showAdress();
    }
    void showStudentResulUarter(int indexStudent) {
        students[indexStudent].showResultUarter();
    }
    string getImportData(int indexStudent) {
        
        return students[indexStudent].getImportData();
    }
    void showAllUartersResult(int indexStudent) {
        students[indexStudent].showAllUartersResult();
    }
    string getNameStudent(int indexStudent) {
        return students[indexStudent].getName();
    }
    float getYearMark(int indexStudent) {
       return students[indexStudent].getYearMark();
    }
    void upDownYearMark(int indexStudent, bool up) {
        students[indexStudent].upDownYearMark(up);
    }
    int getCorrectresultYearMark(int indexStudent) {
        return students[indexStudent].getCorrectresultYearMark();
    }
};


class Journal {
    Group* groups = nullptr;
    int counter = 0;

public:
    Journal(){}
    bool addGroup(string nameGroup) {
        int index = searchGroup(nameGroup);
        if (index !=1) {
            Group* buf = new Group[counter + 1];
            for (int i = 0; i < counter; i++) {
                buf[i] = groups[i];

            }
            Group newGroup(nameGroup);
            buf[counter++] = Group(nameGroup);
            delete[] groups;
            groups = buf;
            return 1;
        }
        return 0;

    }
    void removeGroup(int index) {
        Group* buf = new Group[counter - 1];
        int j = 0;
        for (int i = 0; i < counter; i++) {
            if (i != index) {
                buf[j] = groups[i];
                j++;
            }
        }
        delete[] groups;
        groups = buf;
        counter--;
    }
    int searchGroup(string nameGroup) {
        for (int i = 0; i < counter; i++) {
            if (nameGroup == groups[i].getName()) return 1;
        }
        return -1;
    }
    bool addGroup(Group& newGroup) {
        Group* buf = new Group[counter + 1];
        for (int i = 0; i < counter; i++) {
            buf[i] = groups[i];
        }
        buf[counter++] = newGroup;
        delete[]groups;
        groups = buf;
    }
    bool addStudent(string nameStudent, string nameGroup) {
        int index = searchGroup(nameGroup);
        if (index != -1) {
            groups[index].addStudent(nameStudent);
            return 1;
        }
        return 0;
    }
    void showAllGroups(bool showIndex = 0) {
        if (showIndex) {
            cout << "index|Name" << endl;
            for (int i = 0; i < counter; i++) {
                cout<<i+1<<" |" << groups[i].getName() << endl;
            }
        }
        else for (int i = 0; i < counter; i++) {
            cout << groups[i].getName() << endl;
        }
    }
    int getCounter() {
        return counter;
    }
    void showStudentsInGroup(int indexGroup, bool showIndex = 0) {
        groups[indexGroup].showAll(showIndex);
    }
    int getCounterGroup(int index) {
        return groups[index].getCounter();
    }
    void showAllUartersMarks(int indexGroup, int indexStudent, bool showIndex = 0) {
        groups[indexGroup].showAllUartersMarks(indexStudent);
    }
    void showAllMarksOneUarters(int indexGroup, int indexStudent) {
    }
    void showUarterMarksStudent(int indexGroup, int indexStudent, int indexUarter, int showIndex = 0) {
        groups[indexGroup].showUarterStudent(indexStudent, indexUarter, showIndex);

    }
    int getCounterMarks(int indexStudent, int indexGroup, int indexUarter) {
        return groups[indexGroup].getCounterUarter(indexStudent, indexUarter);
    }
    void showAllStudents(int indexGroup,bool showIndex) {
        groups[indexGroup].showAllNameStudents(showIndex);
    }
    void addMark(int indexGroup,int indexStudent,int indexUarter,int newMark){
        groups[indexGroup].addMark(indexStudent, indexUarter, newMark);
    
    }
    void editMark(int indexGroup, int indexStudent, int indexUarter,int indexMark, int newMark){
        groups[indexGroup].editMark(indexStudent, indexUarter, indexMark, newMark);
    
    }
    void deleteStudent(int indexGroup, int indexStudent) {
        groups[indexGroup].deleteStudent(indexStudent);
    }
    void addStudent(int indexGroup, string nameStudent) {
        groups[indexGroup].addStudent(nameStudent);
    }
    void addStudent(int indexGroup,Student& newStudent) {
        groups[indexGroup].addStudent(newStudent);

    }
    ~Journal() {
        delete[]groups;
    }
    // Конструктор переноса
    Journal(Journal&& other) {
        groups = other.groups;
        counter = other.counter;
        other.groups = nullptr;
        other.counter = 0;
    }


    Journal(Group* newGroups,int counter) {
        delete[]groups;
        this->counter = counter;
        groups = newGroups;
    }
    string getNameGroup(int indexGroup) {
        return groups[indexGroup].getName();
    }
    string getImportData(int indexGroup, int indexStudent) {
        return groups[indexGroup].getImportData(indexStudent);
    }
    void showAllUartersResult(int indexGroup, int  indexStudent) {
        groups[indexGroup].showAllUartersResult(indexStudent);
    }
    string getNameStudent(int indexGroup, int indexStudent) {
        return groups[indexGroup].getNameStudent(indexStudent);
    }
    float getYearMark(int indexGroup, int indexStudent) {
       return groups[indexGroup].getYearMark(indexStudent);
    }
    void upDownYearMark(int indexGroup, int indexStudent,bool up) {
        groups[indexGroup].upDownYearMark(indexStudent, up);
    }
    int getCorrectresultYearMark(int indexGroup, int indexStudent) {
        return groups[indexGroup].getCorrectresultYearMark(indexStudent);
    }
};











//поскольку после каждого действия требуется обновления фаила сохранения, во все меню отправляется объект journal
void changeYearMark(Journal& journal, int indexGroup, int indexStudent) {
    
    int choice;
    
    while (true) {
        cout << "Фактический годовой результат: "<<"" << journal.getYearMark(indexGroup, indexStudent) << endl;
        cout << "Откорректированный годовой результат: " << "" << journal.getCorrectresultYearMark(indexGroup, indexStudent) << endl;
        // Отображение меню действий со студентами
        cout << "Меню действий с годовой оценкой:" << endl;
        cout << "1. Округлить в большую сторону" << endl;
        cout << "2. Округлить в меньшую сторону" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;
        string nameStudent;
        switch (choice) {
        case 1:
            cls;
            journal.upDownYearMark(indexGroup, indexStudent, 1);
            break;
        case 2:
            cls;
            journal.upDownYearMark(indexGroup, indexStudent, 0);
            break;
        case 0:
            cout << "Выход из меню действий со студентами" << endl;
            cls;
            return;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
        exportTxt(journal);
    }


}
void deleteGroupMenu(Journal& journal) {
    int choice;

    while (true) {

        // Отображение главного меню
        cout << "Меню удаления группы:" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите индекс группы: ";
        cin >> choice;

        if (choice >= 1 && choice <= journal.getCounter()) {
            journal.removeGroup(choice - 1);
        }
        if (choice == 0) {
            cout << "Выход из меню удаления группы" << endl;
            cls;
            return;
        }
        else {
            cout << "Указанной группы не сущестувет. Попробуйте снова." << endl;
            
        }
    }


}
void showMainMenu(Journal& journal) {
    int choice;

    while (true) {
        
        // Отображение главного меню
        cout << "Главное меню:" << endl;
        cout << "1. Вывести все группы" << endl;
        cout << "2. Выбрать группу" << endl;
        cout << "3. Добавить группу" << endl;
        cout << "4. Удалить группу" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cls;
            journal.showAllGroups();
            break;
        case 2:
            cls;
            selectGroupMenu(journal);
            break;
        case 3:
            cls;
            addGroupMenu(journal);
            break;
        case 4:

            break;
        case 0:
            cout << "До свидания!" << endl;
            cls;
            return;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
    }
}
void selectActionsUarterMenu(Journal& journal, int indexGroup, int indexStudent, int indexUarter) {
    int choice;
    int newMark;
    while (true) {
        // Отображение меню действий с кварталом
        cout << "Меню действий c "<<indexUarter<<" кварталом:" << endl;
        cout << "1. Добавить оценку" << endl;
        cout << "2. Изменить оценку" << endl;
        cout << "3. Показать квартал" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "Выход из меню действий со студентом" << endl;
            return;
        case 1:
            cls;
            cout << "Введите новую оценку" << endl;
            cin >> newMark;
            if (newMark >= 1 && newMark <= 5) {
                journal.addMark(indexGroup, indexStudent, indexUarter-1, newMark);
            }
            else cout << "Некорректная оценка" << endl;
            
            break;
        case 2:
            int indexMark;
            cout << "Введите индекс оценки" << endl;
            cin >> indexMark;
            if (indexMark >= 1 && indexMark <= journal.getCounterMarks(indexStudent, indexGroup, indexUarter)) {
                cout << "Введите новую оценку" << endl;
                cin >> newMark;
                journal.editMark(indexGroup, indexStudent,indexUarter, indexMark-1,newMark);

            }
            else if (choice == 0) {
                cout << "Выход из меню выбора квартала" << endl;
                cls;
                return;
            }
            else {
                cout << "Некорректный номер квартала. Попробуйте снова." << endl;
            }
            break;
        case 3:
            cls;
            cout << indexUarter << endl;
            journal.showUarterMarksStudent(indexGroup, indexStudent, indexUarter);
            break;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
           
        }
        exportTxt(journal);
    }



}
// Меню управлени студентом
void selectActionsStudentMenu(Journal& journal, int indexGroup, int indexStudent) {
    int choice;

    while (true) {
        // Отображение меню действий со студентом

        cout << "Меню действий со студентом"<<journal.getNameStudent(indexGroup,indexStudent)<< ":" << endl;
        cout << "1. Вывести все кварталы с оценками" << endl;
        cout << "2. Выбрать квартал" << endl;
        cout << "3. Показать средний балл по кварталам" << endl;
        cout << "4. Показать средний годовой балл" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cls;
            journal.showAllUartersMarks(indexGroup, indexStudent, 0);
            break;
        case 3:
            cls;
            journal.showAllUartersResult(indexGroup, indexStudent);
            break;
        case 4:
            cls;
            changeYearMark(journal,indexGroup,indexStudent);
            break;
        case 2:
            int indexUarter;
            cout << "Введите номер квартала (от 1 до 4): ";
            cin >> indexUarter;
            if (indexUarter >= 1 && indexUarter <= 4) {
                selectActionsUarterMenu(journal, indexGroup, indexStudent, indexUarter);
            }
            else {
                cout << "Некорректный номер квартала. Попробуйте снова." << endl;
            }
            break;
        case 0:
            cls;
            cout << "Выход из меню действий со студентом" << endl;
            cls;
            return;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
        exportTxt(journal);
    }
}
//меню выбора группы
void selectGroupMenu(Journal& journal) {
    int indexGroup;

    while (true) {
        cls;
        // Отображение меню выбора группы
        cout << "Меню выбора группы:" << endl;
        cout << "0. Выход" << endl;

        // Отображение списка групп
        journal.showAllGroups(true);

        cout << "Введите номер группы: ";
        cin >> indexGroup;
        if (indexGroup == 0) {
            cout << "Выход из меню выбора группы" << endl;
            cls;
            return;
        }
        indexGroup--;
        if (journal.getCounter() >= indexGroup) {
            selectStudentsMenu(journal, indexGroup);
        }
        else cout << "Группы с таким индексом не существует." << endl;

    }
}
//меню выбора студента
void selectStudentMenu(Journal& journal, int indexGroup) {
    int choice;

    while (true) {
        cls;
        // Отображение меню выбора студента
        cout << "Меню выбора студента:" << endl;
        cout << "0. Выход" << endl;

        // Отображение списка студентов в заданной группе
        journal.showAllStudents(indexGroup, 1);

        cout << "Введите индекс студента: ";
        cin >> choice;
        
        if (choice == 0) {
            cout << "Выход из меню выбора студента" << endl;
            cls;
            return;
        }
        choice--;
        if (journal.getCounterGroup(indexGroup) > choice) {
            selectActionsStudentMenu(journal, indexGroup, choice);
        }
        else cout << "Студента с таким индексом не существует." << endl;
        exportTxt(journal);
    }
}
//меню выбора действий со студентами в гурппе
void selectStudentsMenu(Journal& journal, int indexGroup) {
    int choice;
   
    while (true) {
        // Отображение меню действий со студентами
        cout << "Меню действий со студентами в группе "<<journal.getNameGroup(indexGroup)<<":" << endl;
        cout << "1. Вывести список студентов" << endl;
        cout << "2. Выбрать студента" << endl;
        cout << "3. Удалить студента" << endl;
        cout << "4. Добавить студента" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;
        string nameStudent;
        switch (choice) {
        case 1:
            cls;
            journal.showAllStudents(indexGroup,0);
            break;
        case 2:
            cls;
            selectStudentMenu(journal,indexGroup);
            break;
        case 3:
            cls;
            int indexStudent;
            journal.showAllStudents(indexGroup, 1);
            cout << "Введите индекс студента для удаления" << endl;
            cin >> indexStudent;
            if (indexStudent >= 1 && indexStudent <= journal.getCounterGroup(indexGroup)-1) {
                cout << journal.getCounterGroup(indexGroup);
                journal.deleteStudent(indexGroup, indexStudent - 1);
            }
            else cout << "Студента с таким индексом не существует" << endl;
            
            break;
        case 4:
            cls;
            cout << "Введите имя нового студента" << endl;

            cin.ignore();
            getline(cin, nameStudent);
            journal.addStudent(indexGroup, nameStudent);
            break;
        case 0:
            cout << "Выход из меню действий со студентами" << endl;
            cls;
            return;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
        exportTxt(journal);
    }
}
void addGroupMenu(Journal& journal) {
    int choice;

    while (true) {
        // Отображение меню добавления группы
        cout << "Меню добавления группы:" << endl;
        cout << "1. Ввести название группы" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cls;
            string newNameGroup;
            cout << "Введите название новой группы: ";
            cin >> newNameGroup;
            if (journal.addGroup('.' + newNameGroup)) {
                cout << "Группа " << newNameGroup << " добавлена" << endl << endl;
            }
            else {
                cout << "Такая группа уже существует" << endl << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из меню добавления группы" << endl;
            return;
        default:
            cout << "Некорректный выбор. Попробуйте снова." << endl;
            break;
        }
        exportTxt(journal);
    }
}
void exportTxt(Journal& journal){
    ofstream out;
    out.open("save.txt");
    //i-коллво групп
    //j-колво учеников
    //k-индекс студента
    //l-четверти
    for (int i = 0; i < journal.getCounter(); i++) {//группы
        out << journal.getNameGroup(i)<<endl;
        for (int j = 0; j < journal.getCounterGroup(i); j++) {//студенты
            out << journal.getImportData(i, j) << endl;
            
        }
    }
    out.close();
}



Journal importTxt(string path) {
    ifstream in;
    string nameStudent;
    string nameGroup;
    int indexStudent = 0;
    int strIndex = 0;
    int indexUarter = 0;

    string mark;
    in.open("save.txt");
    if (in.is_open()) {
        string str;
        int countGroup=0;
        while (getline(in, str)) {
            if (str[0] == '.') {
                countGroup++;
            }   
        }
        in.close();
        Group* groups = new Group[countGroup];

        int indexGroup=0;
        in.open(path);

        while (getline(in, str)) {
            if (str[0] == '.') {
                nameGroup = "";
                for (int i = 0; i < str.length(); i++) {
                    nameGroup+=str[i];
                }
                groups[indexGroup] = Group(nameGroup);
               
                indexGroup++;
                indexStudent = 0;
            }
            else {

                //запись имени
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ';') {
                        strIndex = i;
                        break;
                    }
                    nameStudent += str[i];
                }
                Student bufStudent(nameStudent);
                groups[indexGroup-1].addStudent(bufStudent);

                //запись оценок четвертей
                strIndex++;
                for (int i = strIndex; i < str.length(); i++) {
                    if (str[i] == ';') {
                        indexUarter++;
                        if (indexUarter == 4) {
                            /*groups[indexGroup - 1].addMark(indexStudent, indexUarter-1, stoi(mark));*/

                            break;
                        }
                    }
                    else if (str[i] == ' ') {
                        groups[indexGroup - 1].addMark(indexStudent, indexUarter, stoi(mark));
                    }
                    mark = str[i];
                }
                indexStudent++;
            }
            nameStudent = "";
            nameGroup = "";
            strIndex = 0;
            indexUarter = 0;
            str = "";
        }
        in.close();
        //in.open(path);
        //for (int i = 0; i < indexGroup; i++) {
        //    groups[i].showAllNameStudents(1);
        //}
        //groups[indexGroup - 1].showAll();
        Journal journal(groups, countGroup);
        return journal;
    }
}






int main() {
    setlocale(LC_ALL, "");
    Journal journal(importTxt("save.txt"));
    showMainMenu(journal);
}

