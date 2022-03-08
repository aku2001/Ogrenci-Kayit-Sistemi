#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRING_SIZE 50
#define ENROLLED_MSG "kayitli"
#define WITHDRAW_MSG "birakti"
#define LESSON_REMOVED_MSG "ders kapandi"
#define STUDENTS_FILE "ogrenciler.txt"
#define LESSONS_FILE "dersler.txt"
#define STATUS_FILE "OgrenciDersKayit.txt"

typedef struct lesson{
    struct lesson *next;    
    char lessonCode[STRING_SIZE];
    char lessonName[STRING_SIZE];
    int lessonCredit;
    int lessonCapacity;

    int currentCapacity;
    int *studentNumbers;
}Lesson;

typedef struct student{
    struct student *next;
    struct student *prev;

    int studentNumber;
    char name[STRING_SIZE];
    char surname[STRING_SIZE];

    int totalLessons;
    int totalCredit;
}Student;

typedef struct enrollmentStatus{
    struct enrollmentStatus *next;
    int uId;
    
    int studentNumber;
    char lessonCode[STRING_SIZE];
    
    char enrollmentDate[STRING_SIZE];
    char status[STRING_SIZE];

}EnrollmentStatus; 

// LESSON DECLERATION
void addLesson(Lesson **lessonsHead);
void placeLesson(Lesson **lessonsHead, Lesson *newLesson);
void removeLesson(Lesson *lessonsHead, EnrollmentStatus *statusHead, int *uId);

void printLessons(void *lessonsHead);
int listStudentsForLesson(Lesson *lessonsHead,Student *studentsHead,char *lessonCode);

void saveLessons(Lesson *lessonsHead);
void readLessons(Lesson **lessonsHead);



// STUDENT DECLERATION
void addStudent(Student **studentsHead);
void placeStudent(Student **studentsHead, Student *newStudent);
void removeStudent(Student *studentsHead,EnrollmentStatus *statusHead,Lesson *lessonsHead);

void saveStudents(Student *studentsHead);
void readStudents(Student **studentsHead);

int enrollToLesson(EnrollmentStatus **statusHead, Student *studentsHead, Lesson *lessonsHead, int studentNumber, char *lessonCode, int maxLesson, int maxCredit, int *uId);
int withdrawFromLesson(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead, int studentNumber, char *lessonCode);

void listLessonsForStudent(EnrollmentStatus *statusHead,Lesson *lessonsHead, int studentNumber);
void printStudents(void *studentsHead);


// EROLLMENT STATUS DECLERATION
void addEnrollmentStatus(EnrollmentStatus  **statusHead, char *lessonCode, int studentNumber, char *date,char *status, int *uId);
int withdrawnEnrollmentStatus(EnrollmentStatus *statusHead, char *lessonCode, int studentNumber);
void removedEnrollmentStatus(EnrollmentStatus *statusHead, int *uId, char *lessonCode);

int checkEnrollment(EnrollmentStatus *statusHead, int studentNumber, char *lessonCode);

void saveEnrollmentStatus(EnrollmentStatus *statusHead);
void readEnrollmentStatus(EnrollmentStatus **statusHead, Lesson *lessonsHead, int *uId);
void printStatus(void *statusHead);

// MENU DECLERATIONS
void displayMenu();
void enrollToLessonMenu(EnrollmentStatus **statusHead, Student *studentsHead, Lesson *lessonsHead, int maxLesson, int maxCredit, int *uId);
void withdrawFromLessonMenu(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead);
void listLessonsForStudentMenu(EnrollmentStatus *statusHead,Lesson *lessonsHead);
void listStudentsForLessonMenu(Lesson *lessonsHead,Student *studentsHead);
void freeMemory(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead);

int main(){
    int i,j,uId=10000,abort=0,maxCredit=25, maxLesson=10, studentNumber,chosen;
    Lesson *lessonsHead;
    Student *studentsHead;
    EnrollmentStatus *statusHead;

    lessonsHead = NULL; studentsHead = NULL; statusHead = NULL;

    //Define print functions 
    void (*printFunctions[])(void *head) = {printStudents,printLessons,printStatus};

    if(access(STUDENTS_FILE,F_OK) == 0){
        readStudents(&studentsHead);
    }
    
    if(access(LESSONS_FILE,F_OK) == 0){
        readLessons(&lessonsHead);
    }

    if(access(STATUS_FILE,F_OK) == 0){
        readEnrollmentStatus(&statusHead,lessonsHead,&uId);
    }

    // MENU STARTS

    


    abort = 0;
    printf("\nWELCOME TO STUDENT ENROLLMENT SYSTEM\n\n");
    
    printf("Enter the maximum number of credit a student can take: ");
    scanf("%d",&maxCredit);
    
    printf("Enter the maximum number of lessons a student can take: ");
    scanf("%d",&maxLesson);

    while(!abort){
        displayMenu();

        printf("\nEnter Your Choice: ");
        scanf("%d",&chosen);

        if(chosen == 1){
            addStudent(&studentsHead);
            saveStudents(studentsHead);
        }
        else if(chosen == 2){
            removeStudent(studentsHead,statusHead,lessonsHead);
            saveStudents(studentsHead);
            saveEnrollmentStatus(statusHead);

        }
        else if(chosen == 3){
            addLesson(&lessonsHead);
            saveLessons(lessonsHead);
        }
        else if(chosen == 4){
            removeLesson(lessonsHead,statusHead,&uId);
            saveLessons(lessonsHead);
            saveEnrollmentStatus(statusHead);
            saveStudents(studentsHead);
        }
        else if(chosen == 5){          
            enrollToLessonMenu(&statusHead,studentsHead,lessonsHead,maxLesson,maxCredit,&uId);
            saveEnrollmentStatus(statusHead);
            saveStudents(studentsHead);
        }
        else if(chosen == 6){
            withdrawFromLessonMenu(statusHead,studentsHead,lessonsHead);
            saveEnrollmentStatus(statusHead);
            saveStudents(studentsHead);
        }
        else if(chosen == 7){
            listLessonsForStudentMenu(statusHead,lessonsHead);
        }
        else if(chosen == 8){
            listStudentsForLessonMenu(lessonsHead,studentsHead);
        }
        else if(chosen == 9){
            (*printFunctions[1])(lessonsHead);
        }
        else if(chosen == 10){
            (*printFunctions[0])(studentsHead);
        }
        else if(chosen == 11){
            (*printFunctions[2])(statusHead);
        }
        else if(chosen == 12){
            freeMemory(statusHead,studentsHead,lessonsHead);
            abort = 1;
        }
        else{
            printf("\nPlease Enter a Number Between 1-12\n");
        }


    }

    return 0;



}

// FUNCTIONS FOR MENU START
void displayMenu(){
    printf("\nMENU: \n1- Add Student \n2- Delete Student \n3- Add Lesson \n4- Delete Lesson \n5- Enroll To a Lesson \n6- Withdraw From a Lesson\n");
    printf("7- List Lessons of a Particular Student \n8- List Students of a Particular Lesson \n9- List Lessons \n10- List Students \n11- List Status \n12- Exit\n");
}

void enrollToLessonMenu(EnrollmentStatus **statusHead, Student *studentsHead, Lesson *lessonsHead, int maxLesson, int maxCredit, int *uId){
    int studentNumber, abort;
    char lessonCode[STRING_SIZE];

    printf("Enter the Number Of The Student: ");
    scanf("%d",&studentNumber);

    printf("Enter the Code of The Lessons: ");
    scanf("%s",lessonCode);


    if(enrollToLesson(statusHead,studentsHead,lessonsHead,studentNumber,lessonCode,maxLesson,maxCredit,uId)){
        printf("\nStudent %d, Succesfully Enrolled To Lesson %s\n",studentNumber,lessonCode);
    }
}

void withdrawFromLessonMenu(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead){
    int studentNumber,abort; 
    char lessonCode[STRING_SIZE];

    printf("Enter the Number Of The Student: ");
    scanf("%d",&studentNumber);

    printf("Enter the Code of The Lessons: ");
    scanf("%s",lessonCode);

    if(withdrawFromLesson(statusHead,studentsHead,lessonsHead,studentNumber,lessonCode)){
        printf("\nStudent %d, Succesfully Withdraw From Lesson %s\n",studentNumber,lessonCode);
    }

}

void listLessonsForStudentMenu(EnrollmentStatus *statusHead, Lesson *lessonsHead){
    int studentNumber;
    printf("Enter the Number Of The Student: ");
    scanf("%d",&studentNumber);
    listLessonsForStudent(statusHead,lessonsHead,studentNumber);
}

void listStudentsForLessonMenu(Lesson *lessonsHead, Student *studentsHead){
    char lessonCode[STRING_SIZE];

    printf("Enter the Code of The Lessons: ");
    scanf("%s",lessonCode);

    listStudentsForLesson(lessonsHead,studentsHead,lessonCode);
}

void freeMemory(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead){
    EnrollmentStatus *nextStatus;
    Lesson *nextLesson;
    Student *nextStudent;

    nextStatus = statusHead->next;
    while(nextStatus!= NULL){
        free(statusHead);
        statusHead = nextStatus;
        nextStatus = nextStatus->next;
    }
    free(statusHead);

    nextLesson = lessonsHead->next;
    while(nextLesson!= NULL){
        
        if(lessonsHead->studentNumbers != NULL){
            free(lessonsHead->studentNumbers);
        }

        free(lessonsHead);
        lessonsHead = nextLesson;
        nextLesson = nextLesson->next;
    }
    free(lessonsHead);

    nextStudent = studentsHead->next;
    while(nextStudent!= NULL){
        free(studentsHead);
        studentsHead = nextStudent;
        nextStudent = nextStudent->next;
    }
    free(studentsHead);
}
// FUNCTIONS FOR MENU END



// FUNCTIONS FOR LESSONS START

void addLesson(Lesson **lessonsHead){
    Lesson *newLesson = (Lesson*) malloc(sizeof(Student));

    printf("\nADDING NEW LESSON: \n");
    printf("Enter the Lessons's Code (It should be Unique): ");
    scanf("%s",newLesson->lessonCode);
    printf("Enter the Lessons's Name: ");
    scanf("%s",newLesson->lessonName);
    printf("Enter the Lessons's Credit: ");
    scanf("%d",&newLesson->lessonCredit);
    printf("Enter the Lessons's Capacity: ");
    scanf("%d",&newLesson->lessonCapacity);

    newLesson->currentCapacity = 0;
    newLesson->next = NULL;
    newLesson->studentNumbers = NULL;


    placeLesson(lessonsHead,newLesson);

}

void placeLesson(Lesson **lessonsHeadPointer, Lesson *newLesson){
    Lesson *tmp, *lessonToUpdate;
    int cmpRes;

    // Add lesson to the list

    if(*lessonsHeadPointer == NULL){
        // Create a Head
        *lessonsHeadPointer = newLesson;
    }
    else{
        tmp = *lessonsHeadPointer;
        lessonToUpdate = NULL;

        do{
            cmpRes = strcmp(tmp->lessonCode,newLesson->lessonCode);

            if(cmpRes < 0 ){
                lessonToUpdate = tmp;
            }
            tmp = tmp->next;
        }while(cmpRes != 0 && tmp != NULL);

        if(cmpRes){
            printf("\nLesson %s is Succesfully Added\n",newLesson->lessonCode);
            if(lessonToUpdate == NULL){
                // Change head
                tmp = newLesson;
                newLesson = *lessonsHeadPointer;
                *lessonsHeadPointer = tmp;
                tmp->next = newLesson;

            }
            else{
                // Add struct in between
                tmp = lessonToUpdate->next;
                lessonToUpdate->next = newLesson;
                newLesson->next = tmp;
            }
        }  
        else{
            printf("\nThe Lesson Code Should Be Unique. Please Try Again! \n");
        }
    }
}

void removeLesson(Lesson *lessonsHead, EnrollmentStatus *statusHead, int *uId){
    char lessonCode[STRING_SIZE];
    Lesson *currentLesson, *lessonToUpdate, *tmp;

    printf("Enter the Code of the Lesson You would Like to Delete: ");
    scanf("%s",lessonCode);


    currentLesson = lessonsHead;
    lessonToUpdate = lessonsHead;


    while(currentLesson != NULL && strcmp(currentLesson->lessonCode,lessonCode)){
        lessonToUpdate = currentLesson;
        currentLesson = currentLesson->next;
    }
    

    if(currentLesson != NULL){
        // Remove The Lesson
        printf("\nLesson %s Removed Successfully\n",currentLesson->lessonCode);
        
        if(currentLesson == lessonsHead){
            // Remove lessons head
            lessonToUpdate = currentLesson->next;
            *currentLesson = *lessonToUpdate;
            free(lessonToUpdate);
        }
        else{
            // Remove in between
            tmp = currentLesson->next;
            lessonToUpdate->next = tmp;
            free(currentLesson);
        }

        removedEnrollmentStatus(statusHead,uId,lessonCode);
    }
    else{
        printf("\nCould Not Find The Wanted Lesson To Delete. Please Try Again! \n");
    }    
}

void saveLessons(Lesson *lessonsHead){
    Lesson *currentLesson;
    FILE *fp;

    fp = fopen(LESSONS_FILE,"w");

    currentLesson = lessonsHead;

    while(currentLesson!=NULL){
        fprintf(fp,"%s,%s,%d,%d\n",currentLesson->lessonCode,currentLesson->lessonName,currentLesson->lessonCredit,currentLesson->lessonCapacity);
        currentLesson = currentLesson->next;
    }

    fclose(fp);
}

void readLessons(Lesson **lessonsHead){
    Lesson *newLesson;
    const int bufSize = 256;
    char buffer[bufSize], msg[bufSize];
    int i,j,msgNumber;

    FILE *fp;
    fp = fopen(LESSONS_FILE,"r");

    // printf("\nReading Lessons:\n");

    msgNumber = 0;
    while(fgets(buffer,bufSize,fp)){
        i=0;
        newLesson = (Lesson*) malloc(sizeof(Lesson));

        msgNumber=0;
        while(buffer[i] != '\0'){
            j=0;
            while(buffer[i] != ',' && buffer[i] != '\0'){
                msg[j] = buffer[i];
                j++;i++;
            }
            i++;
            msg[j] = '\0';
            if(msgNumber == 0){
                strcpy(newLesson->lessonCode,msg);
            }
            else if(msgNumber == 1){
                strcpy(newLesson->lessonName,msg);
            }
            else if(msgNumber == 2){
                newLesson->lessonCredit = atoi(msg);
            }
            else if(msgNumber == 3){
                newLesson->lessonCapacity = atoi(msg);
            }
            msgNumber++;            
        }

        placeLesson(lessonsHead,newLesson);
    }

    printf("\n");
    fclose(fp);
}

int listStudentsForLesson(Lesson *lessonsHead,Student *studentsHead, char *lessonCode){
    Lesson *currentLesson;
    Student *currentStudent;
    FILE *fp = NULL;
    char fileName[STRING_SIZE];
    int i;


    currentLesson = lessonsHead;
    while(currentLesson != NULL && strcmp(currentLesson->lessonCode,lessonCode)){
        currentLesson = currentLesson->next;
    }


    if(currentLesson != NULL){
        for(i=0;i<currentLesson->currentCapacity;i++){
            if(fp == NULL){
                sprintf(fileName,"%s.txt",lessonCode);
                fp = fopen(fileName,"w");
            }

            // Write to The File
            currentStudent = studentsHead;
            while(currentStudent != NULL && currentStudent->studentNumber != currentLesson->studentNumbers[i]){
                currentStudent = currentStudent->next;
            }

            if(currentStudent != NULL){
                // printf("%d\n",currentLesson->studentNumbers[i]);
                fprintf(fp,"Name: %s %s, Student Number: %d \n",currentStudent->name,currentStudent->surname,currentLesson->studentNumbers[i]);
            }

        }

        if(fp != NULL){
            fclose(fp);
            printf("\nThe List Has Been Created\n");
        }
        else{
            printf("\nThe Lesson Doesn't Have Any Student\n");
        }
        return 1;
    }
    else{
        printf("\nThere is no Lesson with Code: %s\n",lessonCode);
        return 0;
    }



}

void printLessons(void *lessonsHead){
    Lesson *currentLesson;
    lessonsHead = (Student*)lessonsHead;


    currentLesson = lessonsHead;

    if(lessonsHead == NULL){
        printf("No Lesson To Display\n");
    }
    else{
        printf("\nCurrent Lessons: \n");
        while(currentLesson != NULL){
            printf("Code: %s, Name:%s, Lesson Capacity: %d, Current Capacity: %d, Credit: %d \n",currentLesson->lessonCode, currentLesson->lessonName,
                                                            currentLesson->lessonCapacity, currentLesson->currentCapacity,currentLesson->lessonCredit);
            currentLesson = currentLesson->next;
        }
    }
}

// FUNCTIONS FOR LESSONS END


// FUNCTIONS FOR STUDENT START

void addStudent(Student **studentsHead){
    Student *newStudent = (Student*) malloc(sizeof(Student));

    printf("\nADDING NEW STUDENT: \n");
    printf("Enter Student's Name: ");
    scanf("%s",newStudent->name);
    printf("Enter Student's Surname: ");
    scanf("%s",newStudent->surname);
    printf("Enter Student's Number: ");
    scanf("%d",&newStudent->studentNumber);

    newStudent->totalCredit = 0;
    newStudent->totalLessons = 0;
    newStudent->next = NULL;
    newStudent->prev = NULL;


    placeStudent(studentsHead,newStudent);
}

void placeStudent(Student **studentsHeadPointer, Student *newStudent){
    Student *currentStudent, *studentToUpdate, *tmpPointer, tmp;
    int cmpRes;


    if(*studentsHeadPointer == NULL){
        // printf("First Student Added\n");
        *studentsHeadPointer = newStudent;
    }
    else{
        currentStudent = *studentsHeadPointer;
        studentToUpdate = NULL;

        do{
            cmpRes = currentStudent->studentNumber - newStudent->studentNumber;
            if(cmpRes < 0){
                studentToUpdate = currentStudent;
            }
            currentStudent = currentStudent->next;
        }while(currentStudent != NULL && cmpRes != 0);


        if(cmpRes){
            printf("\nStudent %d Succesfully Added\n",newStudent->studentNumber);            

            if(studentToUpdate == NULL){
                // Change Head
                tmpPointer = newStudent;
                newStudent = *studentsHeadPointer;
                *studentsHeadPointer = tmpPointer;

                tmpPointer->next = newStudent;
                newStudent->prev = tmpPointer;
             
            }
            else{
                tmpPointer = studentToUpdate->next;
                newStudent->next = tmpPointer;

                
                studentToUpdate->next = newStudent;
                newStudent->prev = studentToUpdate;
                
                if(tmpPointer != NULL){
                    tmpPointer->prev = newStudent;
                }
                
            }
                        
        }
        else{
            printf("\nStudent Number Must Be Unique. Please Try Again!\n");
        }
    }
}

void removeStudent(Student *studentsHead,EnrollmentStatus *statusHead,Lesson *lessonsHead){
    int studentNumber;
    Student * currentStudent, *studentToUpdate, *tmp;
    EnrollmentStatus *currentStatus;

    printf("Enter the Number of the Student You Would Like To Delete: ");
    scanf("%d",&studentNumber);

   

    currentStudent = studentsHead;

    // Check if student exist
    while(currentStudent != NULL && currentStudent->studentNumber != studentNumber){
        currentStudent = currentStudent->next;
    }

    if(currentStudent != NULL){

        // Withdarw from the lessons the student got into
        currentStatus = statusHead;
        while(currentStatus != NULL){
            if(currentStatus->studentNumber == studentNumber && !strcmp(currentStatus->status, ENROLLED_MSG)){
                withdrawFromLesson(statusHead, studentsHead, lessonsHead, studentNumber, currentStatus->lessonCode);
            }
            currentStatus = currentStatus->next;
        }

        // Remove The Student
        if(currentStudent == studentsHead){
            *studentsHead = *(currentStudent->next);
            studentsHead->prev = NULL;
        }
        else{
            currentStudent->prev->next = currentStudent->next;
            if(currentStudent->next != NULL){
                currentStudent->next->prev = currentStudent->prev;
            }
        }

        printf("\nStudent With Number %d is Sucessfully Deleted\n",studentNumber);
    }
    else{
        printf("\nCould Not Find The Wanted Student. Please Try Again! \n");
    }    
}

void saveStudents(Student *studentsHead){
    Student *currentStudent;

    FILE *fp;
    fp = fopen(STUDENTS_FILE,"w");

    currentStudent = studentsHead;

    while(currentStudent!=NULL){
        fprintf(fp,"%d,%s,%s,%d,%d\n",currentStudent->studentNumber,currentStudent->name,currentStudent->surname,currentStudent->totalCredit,currentStudent->totalLessons);
        currentStudent = currentStudent->next;
    }
    
    fclose(fp);
}

void readStudents(Student **studentsHead){
    Student *newStudent;
    const int bufSize = 256;
    char buffer[bufSize], msg[bufSize];
    int i,j,msgNumber;

    FILE *fp;
    fp = fopen(STUDENTS_FILE,"r");

    // printf("\nReading Students:\n");

    msgNumber = 0;
    while(fgets(buffer,bufSize,fp)){
        i=0;
        newStudent = (Student*) malloc(sizeof(Student));

        msgNumber=0;
        while(buffer[i] != '\0'){
            j=0;
            while(buffer[i] != ',' && buffer[i] != '\0'){
                msg[j] = buffer[i];
                j++;i++;
            }
            i++;
            msg[j] = '\0';
            if(msgNumber == 0){
                newStudent->studentNumber = atoi(msg);
            }
            else if(msgNumber == 1){
                strcpy(newStudent->name,msg);
            }
            else if(msgNumber == 2){
                strcpy(newStudent->surname,msg);
            }
            else if(msgNumber == 3){
                newStudent->totalCredit = atoi(msg);
            }
            else if(msgNumber == 4){
                newStudent->totalLessons = atoi(msg);
            }
            msgNumber++;            
        }

        placeStudent(studentsHead,newStudent);

    }

    printf("\n");
    fclose(fp);
}

int enrollToLesson(EnrollmentStatus **statusHeadPointer, Student *studentsHead, Lesson *lessonsHead, int studentNumber, char *lessonCode, int maxLesson, int maxCredit, int *uId){
    int *tmp,i,j;
    char date[STRING_SIZE];
    Lesson *currentLesson;
    Student *currentStudent;

    currentStudent = studentsHead;
    currentLesson = lessonsHead;

    while(currentStudent!= NULL && currentStudent->studentNumber != studentNumber){
        currentStudent = currentStudent->next;
    }

    while(currentLesson!= NULL && strcmp(currentLesson->lessonCode,lessonCode)){
        currentLesson = currentLesson->next;
    }

    if(currentLesson == NULL){
        printf("\nThe Wanted Lesson Could Not Be Found! \n");
        return 0;
    }
    else if(currentStudent == NULL){
        printf("\nThe Wanted Student Could Not Be Found! \n");
        return 0;
    }


    if(!checkEnrollment(*statusHeadPointer,studentNumber,lessonCode)){
        if(currentLesson->currentCapacity < currentLesson->lessonCapacity){
            if(currentStudent->totalLessons < maxLesson && currentStudent->totalCredit < maxCredit){

                currentLesson->currentCapacity ++;
                currentStudent->totalCredit = currentStudent->totalCredit + currentLesson->lessonCredit;
                currentStudent->totalLessons = currentStudent->totalLessons +1; 

                if(currentLesson->studentNumbers == NULL){
                    currentLesson->studentNumbers = (int*) malloc(currentLesson->currentCapacity* sizeof(int));
                    currentLesson->studentNumbers[0] = currentStudent->studentNumber;
                }
                else{
                    tmp = (int*) realloc(currentLesson->studentNumbers, currentLesson->currentCapacity* sizeof(int));
                    if(tmp != NULL){
                        currentLesson->studentNumbers = tmp;
                    }
                    else{   
                        printf("\nThere Is Not Enough Memory Space\n");
                        return 0;
                    }

                    // Find the Place For New Student Number
                    i=0;
                    while( i< currentLesson->currentCapacity-1 && currentLesson->studentNumbers[i] < currentStudent->studentNumber){
                        i++;
                    }
                    
                    // Reorder The Student Numbers
                    j= currentLesson->currentCapacity-1;
                    while(j > i){
                        currentLesson->studentNumbers[j] = currentLesson->studentNumbers[j-1];
                        j--;
                    }
                    currentLesson->studentNumbers[i] = currentStudent->studentNumber;

                }

                printf("Please Enter the Date: ");
                scanf("%s",date);
                // strcpy(date,"10/10/2021");
                addEnrollmentStatus(statusHeadPointer,currentLesson->lessonCode,currentStudent->studentNumber,date,ENROLLED_MSG,uId);
                return 1;

            }
            printf("\nStudent's Maximum Lesson or Credit Capacity is Full \n");
            return 0;
        }
        printf("\nLesson's Capacity is Full \n");
        return 0;
    }
    else{
        printf("\nAlready Enrolled \n");
        return 0;
    }
}

int checkEnrollment(EnrollmentStatus *statusHead, int studentNumber,char *lessonCode){
    EnrollmentStatus *currentStatus;

    currentStatus = statusHead;
    while(currentStatus != NULL && (currentStatus->studentNumber != studentNumber || strcmp(currentStatus->lessonCode,lessonCode) || strcmp(currentStatus->status,ENROLLED_MSG) )){
        currentStatus = currentStatus->next;
    }
    if(currentStatus != NULL){
        return 1;
    }
    return 0;
}

int withdrawFromLesson(EnrollmentStatus *statusHead, Student *studentsHead, Lesson *lessonsHead, int studentNumber, char *lessonCode){
    int *tmp,i,j;

    Lesson *currentLesson;
    Student *currentStudent;

    currentStudent = studentsHead;
    currentLesson = lessonsHead;

    while(currentStudent!= NULL && currentStudent->studentNumber != studentNumber){
        currentStudent = currentStudent->next;
    }

    while(currentLesson!= NULL && strcmp(currentLesson->lessonCode,lessonCode)){
        currentLesson = currentLesson->next;
    }

    if(currentLesson == NULL){
        printf("\nThere is No Lesson With the Code: %s\n",lessonCode);
        return 0;
    }
    else if(currentStudent == NULL){
        printf("\nThere is No Student With the Number: %d\n",studentNumber);
        return 0;
    }
    
    // Find The Student from currentLesson's studentNumbers list
    i=0;
    while(i < currentLesson->currentCapacity && currentLesson->studentNumbers[i] != currentStudent->studentNumber){
        i++;
    }

    // Shift the currentLesson's studentNumbers list to delete the current student's number and resize the list
    if(i < currentLesson->currentCapacity){
        while(i< currentLesson->currentCapacity){
            currentLesson->studentNumbers[i] = currentLesson->studentNumbers[i+1];
            i++;
        }

        currentLesson->currentCapacity--;
        currentLesson->studentNumbers = (int*) realloc(currentLesson->studentNumbers,currentLesson->currentCapacity * sizeof(int));
        
        currentStudent->totalCredit = currentStudent->totalCredit - currentLesson->lessonCredit;
        currentStudent->totalLessons = currentStudent->totalLessons -1 ;

        withdrawnEnrollmentStatus(statusHead,currentLesson->lessonCode,currentStudent->studentNumber);
        return 1;
    }
    else{
        printf("\nThe Student Did Not Enroll To %s\n",lessonCode);
        return 0;
    }

}

void listLessonsForStudent(EnrollmentStatus *statusHead,Lesson *lessonsHead, int studentNumber){
    EnrollmentStatus *currentStatus;
    Lesson *currentLesson;
    FILE *fp = NULL;
    char fileName[STRING_SIZE];
    int i=0;


    currentStatus = statusHead;

    while(currentStatus != NULL){
        if(currentStatus->studentNumber == studentNumber && !strcmp(currentStatus->status,ENROLLED_MSG)){

            if(fp == NULL){
                sprintf(fileName,"%d_DERSPROGRAMI.txt",studentNumber);
                fp = fopen(fileName,"w");
            }

            // printf("%s : %s\n",currentStatus->lessonCode,currentStatus->status);,
            currentLesson = lessonsHead;
            while(currentLesson!=NULL && strcmp(currentLesson->lessonCode,currentStatus->lessonCode)){
                currentLesson = currentLesson->next;
            }

            if(currentLesson != NULL){
                fprintf(fp,"Code: %s, Name: %s, Credit: %d\n",currentStatus->lessonCode,currentLesson->lessonName,currentLesson->lessonCredit);
            }

        }
        currentStatus = currentStatus->next;
    }

    if(fp == NULL){
        printf("\nThere is no Student With The Given Number or The Student Doesn't Have any Lessons\n");
    }
    else{
        printf("\nThe List Has Been Created\n");
        fclose(fp);
    }
}

void printStudents(void *studentsHead){
    Student *currentStudent;
    studentsHead = (Student*)studentsHead;

    printf("\nPrinting Students\n");
    currentStudent = studentsHead;
    
    while(currentStudent != NULL){
        printf("Number: %d, Name: %s, Surname: %s, Total Credit: %d, Total Lesson: %d \n",currentStudent->studentNumber,currentStudent->name,currentStudent->surname, 
                                                                                currentStudent->totalCredit,currentStudent->totalLessons);
        currentStudent = currentStudent->next;
    }
    
}

// FUNCTIONS FOR STUDENT END


// FUNCTIONS FOR STUDENTENROLLMENT STATUS START


void addEnrollmentStatus(EnrollmentStatus  **statusHead, char *lessonCode, int studentNumber, char *date,char *status, int *uId){
    EnrollmentStatus *currentStatus, *tmp, *newStatus;

    // Create a New Status
    newStatus = (EnrollmentStatus*) malloc(sizeof(EnrollmentStatus));
    newStatus->next = NULL;
    strcpy(newStatus->lessonCode,lessonCode);
    newStatus->studentNumber = studentNumber;
    strcpy(newStatus->enrollmentDate,date);
    newStatus->uId = *uId;
    strcpy(newStatus->status,status);
    *uId = *uId +1; 



    // Link The New Status
    if(*statusHead == NULL) {
        *statusHead = newStatus;
    }
    else{
        currentStatus = *statusHead;
        while(currentStatus->next != NULL){
            currentStatus = currentStatus->next;
        }
        currentStatus->next = newStatus;
    }


}

int withdrawnEnrollmentStatus(EnrollmentStatus *statusHead, char *lessonCode, int studentNumber){
    EnrollmentStatus *currentStatus;
    currentStatus = statusHead;

    // Change Enrollment Status of the Given LessonCode to Withdraw


    while(currentStatus != NULL && (currentStatus->studentNumber != studentNumber || strcmp(currentStatus->lessonCode,lessonCode))){
        currentStatus = currentStatus->next;
    }

    if(currentStatus != NULL){
        strcpy(currentStatus->status,WITHDRAW_MSG);
        return 1;
    }
    else{
        return 0;
    }
}

void removedEnrollmentStatus(EnrollmentStatus *statusHead, int *uId, char *lessonCode){
    EnrollmentStatus *currentStatus;
    currentStatus = statusHead;

    // Change Enrollment Status of the Given LessonCode to Removed

    while(currentStatus != NULL){
        if(!strcmp(currentStatus->lessonCode,lessonCode) && !strcmp(currentStatus->status, ENROLLED_MSG)){
            strcpy(currentStatus->status,LESSON_REMOVED_MSG);
        }
        currentStatus = currentStatus->next;
    }
}

void saveEnrollmentStatus(EnrollmentStatus *statusHead){
    EnrollmentStatus *currentStatus;

    FILE *fp;
    fp = fopen(STATUS_FILE,"w");

    currentStatus = statusHead;
    printf("\nSaving Enrollment Status:\n");

    while(currentStatus!=NULL){
        fprintf(fp,"%d,%s,%d,%s,%s\n",currentStatus->uId,currentStatus->lessonCode,currentStatus->studentNumber,currentStatus->enrollmentDate,currentStatus->status);
        currentStatus = currentStatus->next;
    }
    
    fclose(fp);
}

void readEnrollmentStatus(EnrollmentStatus **statusHead, Lesson *lessonsHead, int *uId){
    Lesson *currentLesson;
    EnrollmentStatus *newStatus = (EnrollmentStatus*) malloc(sizeof(EnrollmentStatus)) ;

    const int bufSize = 256;
    char buffer[bufSize], msg[bufSize];
    int i,j,msgNumber;

    FILE *fp;
    fp = fopen(STATUS_FILE,"r");

    // printf("\nReading Status:\n");

    msgNumber = 0;
    while(fgets(buffer,bufSize,fp)){
        i=0;
        msgNumber=0;
        while(buffer[i] != '\0'){
            j=0;
            while(buffer[i] != ',' && buffer[i] != '\0'){
                msg[j] = buffer[i];
                j++;i++;
            }
            i++;
            msg[j] = '\0';
            if(msgNumber == 0){
                newStatus->uId = atoi(msg);
            }
            else if(msgNumber == 1){
                strcpy(newStatus->lessonCode,msg);
            }
            else if(msgNumber == 2){
                newStatus->studentNumber = atoi(msg);
            }
            else if(msgNumber == 3){
                strcpy(newStatus->enrollmentDate,msg);
            }
            else if(msgNumber == 4){
                // Remove Newline Character From the Msg
                msg[j-1] = '\0';
                strcpy(newStatus->status,msg);
            }
            msgNumber++;            
        }

        addEnrollmentStatus(statusHead,newStatus->lessonCode,newStatus->studentNumber,newStatus->enrollmentDate,newStatus->status,&newStatus->uId);


        // About Lesson
        if(!strcmp(newStatus->status,ENROLLED_MSG)){
            currentLesson = lessonsHead;
            while(currentLesson != NULL && strcmp(currentLesson->lessonCode,newStatus->lessonCode)){
                currentLesson = currentLesson->next;
            }

            if(currentLesson != NULL){
                currentLesson->currentCapacity = currentLesson->currentCapacity + 1;
                currentLesson->studentNumbers = realloc(currentLesson->studentNumbers,currentLesson->currentCapacity*sizeof(int));
                currentLesson->studentNumbers[currentLesson->currentCapacity-1] = newStatus->studentNumber;
            }
        }


    }

    *uId = newStatus->uId;
    free(newStatus);

    fclose(fp);
}

void printStatus(void *statusHead){
    EnrollmentStatus *currentStatus;
    statusHead = (EnrollmentStatus*)statusHead;

    printf("\nPrinting Enrollments\n");
    currentStatus = statusHead;
    
    while(currentStatus != NULL){
        printf("Id: %d, lesson Code: %s, S. Number: %d, Status: %s\n",currentStatus->uId, currentStatus->lessonCode, currentStatus->studentNumber,currentStatus->status);
        currentStatus = currentStatus->next;
    }
}

// FUNCTIONS FOR STUDENT ENROLLMENT STATUS END



