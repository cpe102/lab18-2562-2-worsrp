#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct student{
    string name;
    int id;
    char gender;
    float gpa;
};

struct course{
    string name;
    int id;
    vector<string> lecture_list;
    vector<student *> student_list;
};

student *findstudent(vector<student> allstudents,float key){ //Correct this line
    for(unsigned int i = 0; i < allstudents.size(); i++){
        if(allstudents[i].id  == key) return &allstudents[i];
    }
}

void printreport(vector<course> allcourses){
    for(unsigned int i = 0;i < allcourses.size(); i++){
        cout << "-----------------------------------------------------------------------------\n";
        cout << "Course:\t\t" << allcourses[i].name << " ("<< allcourses[i].id << ")\n\n";
        cout << "Lecturers:\t";
        for(unsigned int j = 0; j < allcourses[i].lecture_list.size();j++){
            if(j != 0) cout << ", ";
            cout << allcourses[i].lecture_list[j];
        }
        cout << "\n\nStudents:\t";
        for(unsigned int j = 0; j < allcourses[i].student_list.size();j++){
            if(j != 0) cout << "\t\t";
            cout << setw(15) << left << allcourses[i].student_list[j]->name << "\t";
            cout << allcourses[i].student_list[j]->id << "\t";
            cout << allcourses[i].student_list[j]->gender << "\t";
            cout << allcourses[i].student_list[j]->gpa << "\n";
        }

    }
    cout << "-----------------------------------------------------------------------------\n";
}

int main(){
    ifstream student_file("students.txt");
    ifstream course_file("courses.txt");
    vector<student> allstudents;
    vector<course> allcourses;

    string textline;
    char format[] = "%[^,],%d,%c,%f";
    char namedata[100],gender;
    int stdID;
    float gpa;
    while(getline(student_file,textline)){
        sscanf(textline.c_str(),format,namedata,&stdID,&gender,&gpa);
        student s={namedata,stdID,gender,gpa};
        allstudents.push_back(s);
    }

    int state = 1;
    while(getline(course_file,textline)){
        if(state == 1){
            course c;
            int loc = textline.find_first_of('(');
            c.name = textline.substr(0,loc-1);
            c.id = atof(textline.substr(loc+1,5).c_str());
            getline(course_file,textline);

            allcourses.push_back(c);
            state = 2;
        }else if(state == 2){
            if(textline == "> Students"){
                state = 3;
            }else{
                allcourses[allcourses.size()-1].lecture_list.push_back(textline);
                //Append lecture_list;
            }
        }else{
            if(textline == "---------------------------------------"){
                state = 1;
            }else{
                 student *p = findstudent(allstudents, atof(textline.c_str()));
                 allcourses[allcourses.size()-1].student_list.push_back(p);
                 //Append student_list;
            }
        }
    }
    printreport(allcourses);

}
