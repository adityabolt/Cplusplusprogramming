#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>

using namespace std;
int n=0;
void writetofile();
void deleterecord();
void modifyrecord();
void readfromfile();
int menu();

int menuchoice(){
  int choice;
  cout<<"\nEnter 1 to go back to the main menu and anything else to exit: ";
  cin>>choice;
  if(choice==1){
    menu();
    return 0;
  }
  else{
    system("cls");
    cout<<"C++ Project By Aditya";
    exit(0);
  }
  return 0;
}

class dateofbirth{
public:
  int dd,mm,yy;
public:
  void acceptdob();
  int calculateage();
};
void dateofbirth::acceptdob(){
  string temp;
  cout<<"Enter Dob in the format(dd/mm/yyyy): ";
  cin>>temp;
  dd=stoi(temp.substr(0,2));
  mm=stoi(temp.substr(3,2));
  yy=stoi(temp.substr(6,4));
}
int dateofbirth::calculateage(){
  time_t now=time(0);
  tm *ltm=localtime(&now);
  int pday=ltm->tm_mday;
  int pmonth=1+ltm->tm_mon;
  int pyear=1900+ltm->tm_year;
  int age;
  if(pmonth>=mm){
    if(pmonth==mm){
      if(pday>=dd)
        age=pyear-yy;
      else
        age=pyear-yy-1;
      }
    else
      age=pyear-yy;
  }
  else
    age=pyear-yy-1;
  return age;
}

class student{
public:
  char first_name[20],last_name[20],coursename[20];
  int age;
  long int regno;
  dateofbirth dob;
public:
  void addrecord();
  void modifyrecord();
};
void student::modifyrecord(){
  int choice=0;
  system("cls");
  cout<<"Enter (1)for yes and anything else for no\n";
  cout<<"Change first name? ";
  cin>>choice;
  if(choice==1){
    cout<<"\nEnter first name: ";
    cin>>first_name;
  }
  cout<<"Change last name? ";
  cin>>choice;
  if(choice==1){
    cout<<"\nEnter last name: ";
    cin>>last_name;
  }
  cout<<"Change course name? ";
  cin>>choice;
  if(choice==1){
    cout<<"\nEnter course name: ";
    cin>>coursename;
  }
  cout<<"Change Date of Birth? ";
  cin>>choice;
  if(choice==1){
    dob.acceptdob();
    age=dob.calculateage();
  }
  cout<<"Change register no? ";
  cin>>choice;
  if(choice==1){
    cout<<"\nEnter new register no: ";
    cin>>regno;
  }
}
void student::addrecord(){
  system("cls");
  cout<<"Enter first name: ";
  cin>>first_name;
  cout<<"Enter last name: ";
  cin>>last_name;
  cout<<"Enter course name: ";
  cin>>coursename;
  dob.acceptdob();
  age=dob.calculateage();
  cout<<"Enter register no: ";
  cin>>regno;
}

student stu[100];

int menu(){
  int choice=0;
  system("cls");
  cout<<"\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
  cout<<"\n\n\n\n";
  cout<<"\n \t\t\t 1. Add    Records";
  cout<<"\n \t\t\t 2. List   Records";
  cout<<"\n \t\t\t 3. Modify Records";
  cout<<"\n \t\t\t 4. Delete Records";
  cout<<"\n \t\t\t 5. Exit   Program\n\n";
  cout<<"\t\t\t Select Your Choice :=> ";
  cin>>choice;
  switch(choice){
    case 1:
            stu[n].addrecord();
            n++;
            writetofile();
            menuchoice();
            break;
    case 2:
            readfromfile();
            system("cls");
            cout<<"\t\t\tRecords in the database\n";
            for(int r=0;r<100;r++)cout<<"-";
            cout<<endl;
            for(int i=0;i<n;i++){
              for(int r=0;r<100;r++)cout<<"*";
              cout<<"\nName: "<<stu[i].first_name<<" "<<stu[i].last_name<<"\t\tCourse: "<<stu[i].coursename
              <<"\nDob: "<<stu[i].dob.dd<<"/"<<stu[i].dob.mm<<"/"<<stu[i].dob.yy
              <<"\t\tAge: "<<stu[i].age<<"\nRegister no: "<<stu[i].regno<<endl;
              for(int r=0;r<100;r++)cout<<"*";
            }
            menuchoice();
            break;
    case 3: modifyrecord();menuchoice();break;
    case 4: deleterecord();menuchoice();break;
    case 5: exit(0);break;
    default: cout<<"\a\nInvalid Entry ";system("pause");menu();
  }
  return 0;
}
void writetofile(){
  FILE *ptr=fopen("students.txt","wt");
  int i=0;
  while(i<n){
    fprintf(ptr,"%s %s %s %d %d/%d/%d %ld\n",stu[i].first_name,stu[i].last_name,stu[i].coursename,
    stu[i].age,stu[i].dob.dd,stu[i].dob.mm,stu[i].dob.yy,stu[i].regno);
    i++;
  }
  fclose(ptr);
}
void  readfromfile(){
  FILE *ptr=fopen("students.txt","r");
  n=0;char line[100];
  while(fgets(line,100,ptr)){
    sscanf(line,"%s %s %s %d %d/%d/%d %ld\n",stu[n].first_name,stu[n].last_name,stu[n].coursename,
    &stu[n].age,&stu[n].dob.dd,&stu[n].dob.mm,&stu[n].dob.yy,&stu[n].regno);
    n++;
  }
  fclose(ptr);
}
void modifyrecord(){
  readfromfile();
  int reggno,i=0,check=0;
  system("cls");
  cout<<"Enter register no: ";
  cin>>reggno;
  while(i<n){
    if(stu[i].regno==reggno){
      check=1;
      break;
    }
    i++;
  }
  if(check==1){
    stu[i].modifyrecord();
    writetofile();
    readfromfile();
  }
  else{
    cout<<"\nInvalid Register no, ";
    system("pause");
    menu();
    return;
  }
}
void deleterecord(){
  readfromfile();
  int reggno,i=0,check=0;
  system("cls");
  cout<<"Enter register no: ";
  cin>>reggno;
  FILE *ptr=fopen("students.txt","wt");
  while(i<n){
    if(stu[i].regno==reggno){
      i++;check=1;
      cout<<"Record Deleted Successfully";
      continue;
    }
    fprintf(ptr,"%s %s %s %d %d/%d/%d %ld\n",stu[i].first_name,stu[i].last_name,stu[i].coursename,
    stu[i].age,stu[i].dob.dd,stu[i].dob.mm,stu[i].dob.yy,stu[i].regno);
    i++;
  }
  if(check==0)  cout<<"Record not found";
  fclose(ptr);
  readfromfile();
}

int main(){
  readfromfile();
  menu();
}
