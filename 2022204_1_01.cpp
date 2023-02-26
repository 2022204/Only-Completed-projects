#include<iostream>
#include<string.h>
using namespace std;



struct Address
{
    int houseno;
    string street;
    string city;
void output_address()
{
    cout<<"House No: "<<houseno<<"\t Street: "<<street<<"\tCity: "<<city<<endl;
}
void input_address()
{
    cout<<"House No(e.g 707): ";
    cin>>houseno;
    cout<<"Street: ";
    cin>>street;
    cout<<"City: ";
    cin>>city;
}
};




enum Departments
{
    CYS,FES,FEE,FCSE,FME,FCE,MGS,FCME
};




union Identifier
{
    string name;
    string regno;
    Departments department;
};



struct Person
{
int age;
string name;
Address address;
};



struct Course
{
string name;
string code;
string teacher_name;
char grades[3];
int marks;
void taketeachersname(string s)
{
    teacher_name = s;
}
void Course_output()
{
    cout<<"Name: "<<name<<endl;
    cout<<"Code: "<<code<<endl<<endl;
}
void teachersname()
{
    cout<<"\nTeacher: "<<teacher_name<<endl;
}
};




struct Student
{
Person person;
string regno;
string department;
Course enrolled_courses[100];
int course_counter=0;
void enrollcourses(Course c)
{
    enrolled_courses[course_counter]=c;
    course_counter++;
    cout<<"Course Enrolled Successfully"<<endl<<endl;
}
void unenrollingcourse(Course c)
{
    for(int i=0 ; i <course_counter ; i++)
    {
        if(c.code == enrolled_courses[i].code && c.name == enrolled_courses[i].name)
        {
        Course temp = enrolled_courses[i];
        enrolled_courses[i]=enrolled_courses[course_counter];
        enrolled_courses[course_counter]=temp;
        course_counter--;
        break;
        }
    }
    cout<<"Courses Removed Successfully"<<endl<<endl;
}
void Student_output()
{
    cout<<"Name: "<<person.name<<"\tAge: "<<person.age<<"\tReg No: "<<regno<<"\tDepartment: "<<department<<endl;
    cout<<"Address"<<endl;
    person.address.output_address();
}
void Courses_enrolled()
{
    for(int i = 0; i < course_counter ; i++)
    {
        enrolled_courses[i].Course_output();
    }
}
};




struct Teacher
{
Person person;
string department; 
int salary;
Course courses_assigned[100];
int course_counter = 0;
void assigningcourse(Course c)
{
    courses_assigned[course_counter] = c;
    courses_assigned[course_counter].taketeachersname(person.name);
    cout<<"Course Assigned Successfully"<<endl;
    course_counter++;
}
void unassigningcourse(Course c)
{
for(int i = 0; i < course_counter ; i++)
{
    if(c.code == courses_assigned[i].code && c.name == courses_assigned[i].name)
    {
        Course temp = courses_assigned[i];
        courses_assigned[i] = courses_assigned[course_counter-1];
        courses_assigned[course_counter-1] = temp;
        course_counter--;
        break;
    }
}
cout<<"Course Un-Assigned successfully"<<endl<<endl;
}
void Teacher_output()
{
cout<<"Name: "<<person.name<<"\tAge: "<<person.age<<"\tDepartment: "<<department<<"\tSalary: "<<salary<<endl;
cout<<"Address"<<endl;
person.address.output_address();

}
void assigned_courses()
{
    cout<<"Name: "<<person.name<<"\tDepartment: "<<department<<endl;
    cout<<"Courses assigned"<<endl;
    cout<<"-----------"<<endl;
    for (int i = 0 ; i < course_counter ; i++)
    {
        courses_assigned[i].Course_output();
    }

    cout<<endl<<endl;
}

};




struct Admin
{
void output()
{
    cout<<"Name: Hasan Abbas\t Salary: 1.5 Million Dollars\t"<<endl;
}
Student students[100];
Teacher teachers[100];
Course courses[100];
int student_counter=0;
int teacher_counter=0;
int course_counter=0;
int findteacher()
{
    Teacher s;
    cout<<"Enter Name of teacher: ";
    cin>>s.person.name;
    cout<<"Enter Department of teacher: ";
    cin>>s.department;
    for(int i = 0 ; i < teacher_counter ; i++)
    {
        if(s.person.name == teachers[i].person.name && s.department == teachers[i].department)
        {
            return i;
        }
    }
    cout<<"Teacher Not found"<<endl;
}
int findstudent()
{
    Student s;
    cout<<"Enter Name of Student: ";
    cin>>s.person.name;
    cout<<"Enter Reg No of student: ";
    cin>>s.regno;
    cout<<"Enter Department of Student: ";
    cin>>s.department;
    for(int i = 0 ; i < student_counter ; i++)
    {
        if(s.person.name == students[i].person.name && s.department == students[i].department && s.regno == students[i].regno)
        {
            return i;
        }
    }
    cout<<"Student Not found!!"<<endl<<endl;
}
int findcourse()
{
    Course c;
    cout<<"Enter Course name(e.g Calculus_1): ";
    cin>>c.name;
    cout<<"Enter Code(Mt101): ";
    cin>>c.code;
    for(int i = 0 ; i < course_counter ; i++)
    {
        if(c.name == courses[i].name && c.code == courses[i].code)
        {
            return i;
        }
    }
        cout<<"Course Not found!!"<<endl;
}
void addstudent()
{
    Student s;
    cout<<"Enter the name of the student: ";
    cin>>s.person.name;
    cout<<"Enter age of the student: ";
    cin>>s.person.age;
    cout<<"Enter Address"<<endl;
    s.person.address.input_address();
    cout<<"Enter department of the student: ";
    cin>>s.department;
    cout<<"Enter registration number of the student: ";
    cin>>s.regno;
    students[student_counter]=s;
    student_counter++;
}
void removestudent()
{
    Student s;
    cout<<"Enter the name of the student: ";
    cin>>s.person.name;
    cout<<"Enter regno of the student: ";
    cin>>s.regno;
    cout<<"Enter department of the student: ";
    cin>>s.department;
    bool found=false;
    for(int i = 0; i < student_counter ;i++)
    {
        if(s.person.name == students[i].person.name && s.regno == students[i].regno && s.department == students[i].department)
        {
            Student temp;
            temp=students[i];
            students[i]=students[student_counter-1];
            students[student_counter-1]=temp;
            student_counter--;
            found = true;
        }
    }
    if(found == false)
    {
        cout<<"Student not found"<<endl;
    }
    else
    {
        cout<<"Student removed successfully"<<endl;
    }
}
void updatestudent()
{
    Student s;
    cout<<"Enter the name of the student: ";
    cin>>s.person.name;
    cout<<"Enter regno of the student: ";
    cin>>s.regno;
    cout<<"Enter department of the student: ";
    cin>>s.department;
    bool found=false;
    for(int i = 0; i < student_counter ;i++)
    {
        if(s.person.name == students[i].person.name && s.regno == students[i].regno && s.department == students[i].department)
        {
            cout<<"Enter New name: ";
            cin>>students[i].person.name;
            cout<<"Enter New Reg.No: ";
            cin>>students[i].regno;
            cout<<"Enter New department: ";
            cin>>students[i].department;
            found=true;
        }
    }
    if(found==true)
    {
        cout<<"Successfully changed"<<endl;
    }
    else 
    {
        cout<<"Student not found"<<endl;
    }
}
void checkstudentrecord()
{
    for(int i = 0 ; i < student_counter ; i++)
    {
        students[i].Student_output();
        cout<<endl<<endl;
    }

}
void unenrollstudents()
{
    int indexS=findstudent();
    int indexC=findcourse();
    students[indexS].unenrollingcourse(courses[indexC]);
}
void addteacher()
{
    Teacher s;
    cout<<"Enter the name of the Teacher: ";
    cin>>s.person.name;
    cout<<"Enter age of the Teacher: ";
    cin>>s.person.age;
    cout<<"Enter Address"<<endl;
    s.person.address.input_address();
    cout<<"Enter department of the Teacher: ";
    cin>>s.department;
    cout<<"Enter Salary: ";
    cin>>s.salary;
    teachers[teacher_counter]=s;
    teacher_counter++;
}
void removeteacher()
{
    Teacher s;
    cout<<"Enter the name of the Teacher: ";
    cin>>s.person.name;
    cout<<"Enter age of the Teacher: ";
    cin>>s.person.age;
    cout<<"Enter department of the Teacher: ";
    cin>>s.department;
    bool found=false;
    for(int i=0;i<teacher_counter;i++)
    {
        if(teachers[i].person.name==s.person.name && teachers[i].department==s.department && teachers[i].person.age==s.person.age)
        {
            Teacher temp=teachers[teacher_counter-1];
            teachers[teacher_counter-1]=teachers[i];
            teachers[i]=temp;
            teacher_counter--;
            found=true;
            break;
        }
    }
    if(found==false)
    {
        cout<<"Teacher not found"<<endl;
    }
    else
    {
        cout<<"Teacher removed successfully"<<endl;
    }
}
void updateteacher()
{
    Teacher s;
    cout<<"Enter the name of the Teacher: ";
    cin>>s.person.name;
    cout<<"Enter age of the Teacher: ";
    cin>>s.person.age;
    cout<<"Enter department of the Teacher: ";
    cin>>s.department;
    bool found=false;
    for(int i=0;i<teacher_counter;i++)
    {
        if(teachers[i].person.name==s.person.name && teachers[i].department==s.department && teachers[i].person.age==s.person.age)
        {
            cout<<"Teacher found"<<endl;
            cout<<"Enter new name for the Teacher: ";
            cin>>teachers[i].person.name;
            cout<<"Enter new age for teacher: ";
            cin>>teachers[i].person.age;
            cout<<"Enter new department: ";
            cin>>teachers[i].department;
            found=true;
            break;
        }
    }
    if(found==false)
    {
        cout<<"teacher not found!!"<<endl;
    }
    else
    {
        cout<<"Teacher updated successfully"<<endl;
    }
}
void checkteacherrecord()
{
    for(int i = 0 ;i < teacher_counter ; i++)
    {
        teachers[i].Teacher_output();
        cout<<endl<<endl;
    }
}
void addcourse()
{
    Course c;
    cout<<"Enter Course name(e.g Applied_Physics): ";
    cin>>c.name;
    cout<<"Enter course name(e.g MT101): ";
    cin>>c.code;
    courses[course_counter]=c;
    course_counter++;
}
void removecourse()
{
Course s;
    cout<<"Enter Course name(like Applied_physics(use underscorea as space)): ";
    cin>>s.name;
    cout<<"Enter Course code(like PH101): ";
    cin>>s.code;
    bool found=false;
    for(int i=0;i<course_counter;i++)
    {
        if(courses[i].name==s.name && courses[i].code==s.code)
        {
            Course temp=courses[i];
            courses[i]=courses[course_counter-1];
            courses[course_counter-1]=temp;
            course_counter--;
            found=true;
            break;
        }
    }
    if(found==false)
    {
        cout<<"Course not found"<<endl;
    }
}
void updatecourse()
{
    Course s;
    cout<<"Enter Course name(like Applied_physics): ";
    cin>>s.name;
    cout<<"Enter Course code(like PH101): ";
    cin>>s.code;
    bool found = false;
    for(int i = 0 ; i < course_counter ; i++)
    {
        if(courses[i].name == s.name && courses[i].code == s.code)
        {
            cout<<"Enter new name for course: ";
            cin>>courses[i].name;
            cout<<"Enter new Code for course: ";
            cin>>courses[i].code;
            found = true;
            break;
        }
    }
    if(found == false)
    {
        cout<<"Course not found"<<endl;
    }
}
void checkcourserecord()
{
    for(int i = 0 ; i < course_counter ; i++)
    {
        courses[i].Course_output();
    }
}
void allocatecourse()
{
    Teacher t;
    Course c;
    cout<<"Enter teacher name: ";
    cin>>t.person.name;
    cout<<"Enter Department: ";
    cin>>t.department;
    cout<<"Enter Course name(Calculus-1): ";
    cin>>c.name;
    cout<<"Enter Course Code(e.g MT101): ";
    cin>>c.code;
    bool found = false;
    for(int i = 0 ; i < teacher_counter ; i++)
    {
        for (int j = 0 ; j < course_counter ; j++)
        {
            if(t.person.name == teachers[i].person.name && t.department == teachers[i].department)
            {
                if(c.name == courses[j].name && c.code == courses[j].code)
                {
                    found = true;
                    teachers[i].assigningcourse(courses[j]);
                }
            }
        }
    }
    if(found == false)
    {
        cout<<"Teacher or Course not found"<<endl;
    }
}
void unallocatecourse()
{
    Teacher t;
    Course c;
    cout<<"Enter teacher name: ";
    cin>>t.person.name;
    cout<<"Enter Department: ";
    cin>>t.department;
    cout<<"Enter Course name(Calculus-1): ";
    cin>>c.name;
    cout<<"Enter Course Code(e.g MT101): ";
    cin>>c.code;
    bool found = false;
    for(int i = 0 ; i < teacher_counter ; i++)
    {
        for (int j = 0 ; j < course_counter ; j++)
        {
            if(t.person.name == teachers[i].person.name && t.department==teachers[i].department)
            {
                if(c.name == courses[j].name && c.code == courses[j].code)
                {
                    found = true;
                    teachers[i].unassigningcourse(courses[j]);
                }
            }
        }
    }
    if(found == false)
    {
        cout<<"Teacher or Course not found"<<endl;
    }
}
};
Admin sys;



void admin()
{
    cout<<"Welcome Admin of GIKI. What Do you want to do?"<<endl;
    bool loop=true;
    int input;
    do 
    {
        int option;
        cout<<"Select from the following"<<endl;
        cout<<"(1)Add a new Student in system"<<endl;
        cout<<"(2)Remove a student from system"<<endl;
        cout<<"(3)Update student detail"<<endl;
        cout<<"(4)Check record of all students"<<endl;
        cout<<"(5)Un-enroll a student from a course"<<endl;
        cout<<"(6)Add a new teacher"<<endl;
        cout<<"(7)Remove a teacher"<<endl;
        cout<<"(8)Update teacher detail"<<endl;
        cout<<"(9)Check record of all teachers"<<endl;
        cout<<"(10)Add a course in the system"<<endl; 
        cout<<"(11)Remove a course"<<endl;
        cout<<"(12)Update course detail"<<endl;
        cout<<"(13)Check record of all courses"<<endl;
        cout<<"(14)Allocate a course to a teacher"<<endl;
        cout<<"(15)De-allocate a course from teacher"<<endl; 
        cout<<"(16)Return to main menu"<<endl;
        cin>>option;
        cout<<endl<<endl;
        switch(option)
        {
            case 1:
                sys.addstudent();
            break;
            case 2:
                sys.removestudent();
            break;
            case 3:
                sys.updatestudent();
            break;
            case 4:
                sys.checkstudentrecord();
            break;
            case 5:
                sys.unenrollstudents();
            break;
            case 6:
                sys.addteacher();
                break;
            case 7:
                sys.removeteacher();
            break;
            case 8:
                sys.updateteacher();
            break;
            case 9:
                sys.checkteacherrecord();
            break;
            case 10:
                sys.addcourse();
            break;
            case 11:
                sys.removecourse();
            break;
            case 12:
                sys.updatecourse();
            break;
            case 13:
                sys.checkcourserecord();
            break;
            case 14:
                sys.allocatecourse();
            break;
            case 15:
                sys.unallocatecourse();
            break;
            case 16:
                return;
                break;
            default:
                cout<<"Invalid input"<<endl;
            break;
        }
        cout<<endl<<endl;
        cout<<"Do you want to continue"<<endl;
        cout<<"(1)Yes\t(2)No"<<endl;
        cin>>input;
        cout<<endl<<endl;
    }while(input==1);

}



void student()
{
int indexS;
int indexT;
int indexC;
int option,input;
indexS=sys.findstudent();
cout<<endl<<endl;
do{
cout<<"Select from the following"<<endl;
cout<<"(1)Check Your details"<<endl;
cout<<"(2)Enroll any available course"<<endl;
cout<<"(3)See your final grades"<<endl;
cout<<"(4)See list of your teachers"<<endl;
cout<<"(5)See your enrolled course"<<endl;
cout<<"(6)Go back to main menu"<<endl;
cin>>option;
cout<<endl<<endl;
switch(option)
{
case 1:
    cout<<"<<<<<----------------------Profile Details------------------------------>>>>>"<<endl;
    sys.students[indexS].Student_output();
    break;
case 2:
    cout<<"<<<<<-------------------------Courses Available-------------------------->>"<<endl<<endl;
    for(int i = 0; i < sys.course_counter ; i++)
    {
        cout<<"("<<i+1<<")"<<sys.courses[i].code<<"\t\t";
    }
    cout<<endl<<endl;
    int index;
    cout<<"Which one do you want to enroll(Enter index only): ";
    cin>>index;
    index=index-1;
    sys.students[indexS].enrollcourses(sys.courses[index]);
    cout<<endl<<endl;
    break;
case 3:
    cout<<"<<<<<<<----------------------Grades And Marks--------------------->>>>>>"<<endl<<endl;
    cout<<"Name: "<<sys.students[indexS].person.name<<"\tReg No: "<<sys.students[indexS].regno<<"\tDepartment: "<<sys.students[indexS].department<<endl;
    for(int i = 0 ; i < sys.students[indexS].course_counter ; i++)
    {
        cout<<"Course: "<<sys.students[indexS].enrolled_courses[i].code<<"\t\tYour Grade: "<<sys.students[indexS].enrolled_courses[i].grades<<"\t\tMarks: "<<sys.students[indexS].enrolled_courses[i].marks<<endl;
    }
    break;
case 4:
    cout<<"<<<<-------------------------My teachers----------------------------->>>>>>"<<endl;
    for(int i = 0 ; i < sys.students[indexS].course_counter ; i++)
    {
        for(int j = 0 ; j < sys.teacher_counter ; j++)
        {
            for(int k = 0 ; k < sys.teachers[j].course_counter ; k++)
            if( sys.students[indexS].enrolled_courses[i].code == sys.teachers[j].courses_assigned[k].code)
            {
                cout<<"Course: "<<sys.students[indexS].enrolled_courses[i].code<<endl;
                cout<<"Name: "<<sys.teachers[j].person.name<<"\t\t Department: "<<sys.teachers[j].department<<endl;
            }
        }
    }
    break;
case 5:
    cout<<"<<<<<---------------------Enrolled COurses --------------------->>>>>> "<<endl<<endl;
    for(int i = 0 ; i < sys.students[indexS].course_counter ; i++)
    {
        cout<<"("<<i+1<<")Course: "<<sys.students[indexS].enrolled_courses[i].name;
        cout<<"\t\tCode: "<<sys.students[indexS].enrolled_courses[i].code<<endl<<endl;
    }
    cout<<endl<<endl;
    break;
case 6:
    return;
    break;
default:
    cout<<"Invalid input"<<endl;
}
cout<<endl<<endl;
cout<<"do you want to continue?"<<endl;
cout<<"(1)Yes\t(2)No"<<endl;
cin>>input;
cout<<endl<<endl;
}while(input==1);
}


void teacher()
{
cout<<"Welcome Dear teacher."<<endl;
int input;
int option;
int indexT=sys.findteacher();
cout<<endl<<endl;
do
{
cout<<"Select from the following"<<endl;
cout<<"(1)Check your details"<<endl;
cout<<"(2)List of courses allocated"<<endl;
cout<<"(3)List of students in each course"<<endl;
cout<<"(4)Assign marks and grade to each student"<<endl;
cout<<"(5)Grades of Each Student"<<endl;
cout<<"(6)Go back to main menu"<<endl;
cin>>option;
cout<<endl<<endl;
switch(option)
{
    case 1:
        cout<<endl<<endl;
            cout<<"<<<<<----------------------------Profile Detail--------------------------->>>>>"<<endl;
            sys.teachers[indexT].Teacher_output();
        break;
    case 2:
        cout<<endl<<endl;
            cout<<"<<<<<---------------------------Courses Assigned--------------------------->>>>>"<<endl;
            sys.teachers[indexT].assigned_courses();
        break;
    case 3:
        cout<<endl<<endl;
        cout<<"<<<<<--------------------------Students in each Course------------------------->>>>>"<<endl;
        for(int  i = 0 ; i < sys.teachers[indexT].course_counter ; i++)
        {
            for(int j = 0 ; j < sys.student_counter ; j++)
            {
                for(int k = 0 ; k < sys.students[j].course_counter ; k++)
                {
                    if(sys.teachers[indexT].courses_assigned[i].name  == sys.students[j].enrolled_courses[k].name && sys.teachers[indexT].courses_assigned[i].code  == sys.students[j].enrolled_courses[k].code)
                    {
                        cout<<"\t\tCourse:  "<<sys.teachers[indexT].courses_assigned[i].code<<endl;
                        cout<<"Name: "<<sys.students[j].person.name<<"\tReg No: "<<sys.students[j].regno<<endl;
                    }
                }
                cout<<endl<<endl;
            }
        }
    break;
    case 4:
        cout<<endl<<endl;
        cout<<"<<<<<------------------------Assigning marks and grade to students--------->>>>>"<<endl;
        for(int  i = 0 ; i < sys.teachers[indexT].course_counter ; i++)
        {
            for(int j = 0 ; j < sys.student_counter ; j++)
            {
                for(int k = 0 ; k < sys.students[j].course_counter ; k++)
                {
                    if(sys.teachers[indexT].courses_assigned[i].name  == sys.students[j].enrolled_courses[k].name && sys.teachers[indexT].courses_assigned[i].code  == sys.students[j].enrolled_courses[k].code)
                    {
                        cout<<"\t\tCourse: "<<sys.teachers[indexT].courses_assigned[i].code<<endl;
                        cout<<"Name: "<<sys.students[j].person.name<<"\t\tReg No: "<<sys.students[j].regno<<endl;
                        cout<<"Enter His/Her Marks: ";
                        cin>>sys.students[j].enrolled_courses[k].marks;
                        cout<<"Enter His/Her Grades: ";
                        cin>>sys.students[j].enrolled_courses[k].grades;
                        cout<<endl<<endl;
                    }
                }
                cout<<endl<<endl;
            }
        }
    break;
    case 5:
        cout<<endl<<endl;
        cout<<"<<<<<-------------------------Grades of Students------------------------------->>>>>"<<endl;
        for(int i = 0;i < sys.teachers[indexT].course_counter;i++)
            {
                for(int j = 0; j < sys.student_counter ; j++)
                {
                    for(int k = 0 ; k < sys.students[j].course_counter ; k++)
                    {
                        if(sys.students[j].enrolled_courses[k].code == sys.teachers[indexT].courses_assigned[i].code)
                        {
                            cout<<"Course: "<<sys.teachers[indexT].courses_assigned[i].code<<endl;
                            cout<<"Name: "<<sys.students[j].person.name<<"\t\tReg No: "<<sys.students[j].regno<<endl;
                            cout<<"Grades: "<<sys.students[j].enrolled_courses[k].grades<<"\t\tMarks: "<<sys.students[j].enrolled_courses[k].marks<<endl<<endl;
                        }
                    }
                    cout<<endl<<endl;
                }
            }
        cout<<endl<<endl;
    break;
    case 6: 
        return;
        break;
    default:
        cout<<"Invalid Option"<<endl;
    break;
}
cout<<endl<<endl;
cout<<"Do you want to continue?"<<endl;
cout<<"(1)Yes\t(2)No"<<endl;
cin>>input;
cout<<endl<<endl;
}while(input==1);
}



int main()
{
    cout<<"<<<<--------------------------Welcome to GIKI.Management.com----------------------------->>"<<endl;
    int option;
    do{
    cout<<endl<<endl;
    cout<<"Which one are you?"<<endl;
    cout<<"(1)Teacher"<<endl;
    cout<<"(2)Admin"<<endl;
    cout<<"(3)Student"<<endl;
    cout<<"(4)End program"<<endl;
    cin>>option;
    cout<<endl<<endl;
    switch(option)
    {
    case 1:
        teacher();
        break;
    case 2:
        admin();
        break;
    case 3:
        student();
        break;
    case 4:
        return 0;
        break;
    default:
        cout<<"Invalid choice"<<endl;
        break;
    }}while(true);
    return 0;
}