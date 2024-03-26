#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX1 150
#define MAX_LINE 2000
#define INITIAL_SIZE 10

//+------------------------------------------------+----------------------------------------------------+
// Dunia Jaser 1201345
// Section 1 - Dr. Ahmed Abusnaina
//+------------------------------------------------+----------------------------------------------------+
typedef struct node_hash* pointer;

typedef struct node_hash{
    int hours;
    char code[MAX1];
    char key_course_name[MAX1];
    char department[MAX1];
    char topics[MAX1][MAX1];
    int state;
}Hash;

Hash additinoal_array[MAX1]; // for addtional info from user;
int indx = 0;
/********************************************************
    when state is -1 means that cell is EMPTY.
    when state is 0 means that cell is OCCUPIED.
    when state is 1 means that cell is DELETED.
********************************************************/
int size1 = INITIAL_SIZE;
int size2 = INITIAL_SIZE;

int number_Of_Collisons_Open_Addressing = 0;
int number_Of_Collisons_Double_Addressing = 0;
int numberOfReading = 0;// to let the user read from file only one time.
pointer *table1pointer;///pointer to table 1 that follows open addressing linear probing.
pointer *table2pointer;///pointer to table 2 that follows double addressing.
int number_of_elements1 = 0;// to find out the value of Load factor (𝜆) for table 1 that should be between 0.6 and 0.7
int number_of_elements2 = 0;// to find out the value of Load factor (𝜆) for table 2 that should be between 0.6 and 0.7
int course_is_deleted1 = 0;//to know if the course is deleted or not in table 1.
int course_is_deleted2 = 0;//to know if the course is deleted or not in table 2

/// function prototypes
void display_menu();
void read_courses_info();
void add_to_hash_table_method1(pointer,pointer*/*,int*/);
int assci_code(char[],int);
void initialize_table(pointer[],int);
void print_hash_table(pointer[], int);
void add_to_hash_table_method2(pointer, pointer*, int );
double Loud_Factor(int,int);
int rehashing(int);// to find out the value of the array of the hash table to keep the Load Factor between 0.6 and 0.7
int isPrime(int);
void print_hash_table2(pointer *, int);
int double_addressing_hp(int, int);
void insert_course_from_user();
void search_for_a_specific_word();
void write_into_file();
void compare();
void delete_a_course();
/****************************************************************************************************/
int main()
{
    read_courses_info();
    display_menu();
    return 0;
}
///***************************************************************************************************************************
void display_menu(){
    printf("\n****************************************-MENU-********************************************\n");
    printf("Choose one of these options:\n");
    printf("1) Print hashed tables (including empty spots).\n");
    printf("2) Print out table size and the load factor.\n");
    printf("3) Print out the used hash functions.\n");
    printf("4) Insert a new record to hash table.\n");
    printf("5) Search for a specific.\n");
    printf("6) Delete a specific record.\n");
    printf("7) Compare between the two methods in terms of number of collisions occurred.\n");
    printf("8) Save hash table back to a file.\n");
    printf("9) Exit the program.\n");
    int choice;
    scanf("%d",&choice);
    printf("******************************************************************************************\n");
    if (choice == 1){
        printf("The first hash table------------------------\n\n");
        print_hash_table2(table1pointer,size1);
        printf("\nThe second hash table------------------------\n\n");
        print_hash_table2(table2pointer,size2);
        display_menu();
    }
    else if (choice == 2){
        printf("For table 1--------------\n");
        printf("\n-------------- The Load Factor %.3f --------------\n",Loud_Factor(size1,number_of_elements1));
        printf("---------------- The Table Size %d --------------\n\n",size1);
        printf("For table 2--------------\n");
        printf("\n-------------- The Load Factor %.3f --------------\n",Loud_Factor(size2,number_of_elements2));
        printf("---------------- The Table Size %d --------------\n",size2);
        display_menu();
    }
    else if (choice == 3){
        printf("For table 1:\n");
        printf("The method used is open-addressing (linear Probing):\n");
        printf("The hash function:\nhi(key) = [h(key) + i] %% tableSize for i = 0, 1, . . . , tableSize-1 \n");
        printf("-----------------------------------------------------------------------------\n");
        printf("For table 2:\n");
        printf("The method used is double addressing:\n");
        printf("The hash function:\nhi(key) = [h(key) + i*hp(key)]%% tableSize for i = 0, 1, . . . , tableSize-1\n");
        printf("=> hp(key) = 1 + key %% (tableSize - 1)\n");

        display_menu();
    }
    else if (choice == 4){
        insert_course_from_user();
        display_menu();
    }
    else if (choice == 5){
        search_for_a_specific_word();
        display_menu();
    }
    else if (choice == 6){
        delete_a_course();
        display_menu();
    }
    else if (choice == 7){
            compare();
            display_menu();
    }
    else if (choice == 8){
        printf("The operation done successfully!\n");
        write_into_file();
        display_menu();
    }
    else if (choice == 9 ){//exit from the program.
        printf("Hope you enjoy trying this program ^_^\n");
        exit(0);
    }
    else {
        printf("Not a valid choice. \n");
        display_menu();
    }


}
///***************************************************************************************************************************
void read_courses_info(){
    number_Of_Collisons_Double_Addressing = 0;
    number_of_elements1 =0;
    number_of_elements2 = 0;
    number_Of_Collisons_Open_Addressing =0;
    FILE *in = fopen("offered_courses.txt","r");
    if(in == NULL){
            printf("The courses file not found!\n");
            exit(0);
        }
    int lines_count = 0;
    char c;
    for( c = fgetc(in); c != EOF ; c = fgetc(in) ){
            if( c == '\n')
                lines_count += 1;
    }
    fclose(in);
    pointer table1[size1] ;//linear table
    pointer table2[size2] ;// double addressing table
    initialize_table(table1,size1);
    initialize_table(table2,size2);

    table1pointer = table1;
    table2pointer = table2;

    FILE *input = fopen("offered_courses.txt","r");
    int times = 0;
    char *token;
    pointer temp, tem;
    while(input != NULL){
        times++;
        if(times == lines_count+1)
            break;
        temp = (pointer)malloc(sizeof(struct node_hash));
        tem = (pointer)malloc(sizeof(struct node_hash));
        char line[MAX_LINE];
        fgets(line,sizeof(line),input);

        token = strtok(line,":");//course name
        strcpy(temp->key_course_name,token);
        strcpy(tem->key_course_name,token);

        token = strtok(NULL,"#");//course hours
        temp->hours = atoi(token);
        tem->hours = atoi(token);

        token = strtok(NULL,"#");//course code
        strcpy(temp->code,token);
        strcpy(tem->code,token);

        token = strtok(NULL,"/");//department
        strcpy(temp->department,token);
        strcpy(tem->department,token);

        int i = 0;
        while(token != NULL){
            token = strtok(NULL,", ");
            strcpy(temp->topics[i],token);
            strcpy(tem->topics[i],token);

            int lengthString = strlen(token);
            if(temp->topics[i][lengthString-1] == '\n'){
                temp->topics[i][lengthString-1] = '\0';
                tem->topics[i][lengthString-1] = '\0';
                break;
            }

            i++;
        }

        if(i == 0 ){
            printf("The topics should be one or more!\n");
        }
        else{
                temp->state = -1 ;
                number_of_elements1 += 1;
                number_of_elements2 += 1;
            add_to_hash_table_method1(temp,table1pointer/*,size*/);
            add_to_hash_table_method2(tem,table2pointer,size2);
        }


    }
    fclose(input);
     /* the case when the user add and then the load factor became 0.7 so I have to add the new nodes added from user in array of structure
     and add them to the arrays when rehasing*/
     if( strcmp(additinoal_array[0].code, "") != 0){
        for(int i = 0 ; i < sizeof(additinoal_array) ; i++){
            if( strcmp(additinoal_array[i].code, "") == 0){
                break;
            }
            pointer t =(pointer)malloc(sizeof(struct node_hash));
            strcpy(t->code,additinoal_array[i].code);
            strcpy(t->key_course_name,additinoal_array[i].key_course_name);
            strcpy(t->department,additinoal_array[i].department);
            t->state = -1;
            t->hours = additinoal_array[i].hours;
            for(int j = 0 ; j <sizeof(additinoal_array[i].topics);j++){
                    if(strcmp(additinoal_array[i].topics[j],"") == 0)
                        break;
                    strcpy(t->topics[j],additinoal_array[i].topics[j]);
            }
            add_to_hash_table_method1(t,table1pointer/*,size*/);
            add_to_hash_table_method2(t,table2pointer,size2);

        }
    }
    display_menu();
}
///***************************************************************************************************************************
void initialize_table(pointer table1[],int size){
    for(int i = 0 ; i < size ; i++){
      table1[i]= NULL;
    }
}
///***************************************************************************************************************************
// add to hash table 1 using open addressing-Linear Probing
void add_to_hash_table_method1(pointer temp, pointer *table1/*,int size*/){
    double load =  Loud_Factor(size1,number_of_elements1) ;
   // printf("size %d load %.1f elements %d\n",size1,load,number_of_elements1);
    if( load >=0 && load < 0.75){
        int code = assci_code(temp->key_course_name,MAX1);
        int index = code%size1;
   ///  printf("Table 1 %s %d \n",temp->key_course_name,index);
        int index1;
        if(table1[index] == NULL){
            table1[index] = temp;
            table1[index]->state = 0;
        }else{
          /*  if(table1[index]->state == -1){
                 table1[index] = temp;
                table1[index]->state = 0;
            }*/
            if(table1[index]->state == 1){//the cell is deleted so we can add in its place
                //table1[index] = NULL;
                table1[index] = temp;
                table1[index]->state = 0;
            }
        if(table1[index]->state == 0){
                //occupied -> collision
                number_Of_Collisons_Open_Addressing += 1;
                for(int j = 1; j< size1 ;j++){
                    index1 = (index +  j) % size1;
                    if(table1[index1] == NULL || table1[index]->state == 1 ){//if the cell is empty or have deleted cell, then add
                  ///   printf("%s %d\n",temp->key_course_name,index1);
                        table1[index1] = temp;
                        table1[index1]->state = 0;
                        break;
                    }
                    if(table1[index1]->state == 0){
                        number_Of_Collisons_Open_Addressing += 1;
                     }
                }
            }
        }
    } else{// rehash
        int old = size1;
            size1 = rehashing(size1);//the new size
            printf("The old hash size for table 1 is %d, the new hash size is %d\n",old,size1);
            read_courses_info();
    }

}
///***************************************************************************************************************************
int double_addressing_hp(int tableSize, int key){
   return 1 + key % (tableSize - 1) ;
}
///***************************************************************************************************************************
// finds out the first prime number of the doubling table size
int rehashing(int temp){
    int doubledSized = 2*temp + 1; // newTable= prime>2*oldSize
    while(isPrime(doubledSized) != 1){
        doubledSized += 1 ;
    }
    int result = doubledSized;
   return result;
}
///***************************************************************************************************************************
int isPrime(int x){ // returns 1 if the number is prime, otherwise it will return 0
    int prime = 1;
    for(int i = 2 ; i <= x/2 ; i++ ){
        if(x%i == 0){
           prime = 0;
           break;
        }
    }
    return prime;
}
///***************************************************************************************************************************
double Loud_Factor(int size,int number_of_elements ){
    if( size == 0 )
        return 0 ;
    else
        return ((double)number_of_elements/size);
}
///***************************************************************************************************************************
int assci_code(char temp[],int size){
    int assci_sum = 0;
    for(int i = 0 ; i <strlen(temp); i++){
        assci_sum += (int)temp[i];
    }
///    printf("%s %d\n",temp,assci_sum);
    return assci_sum;
}
///***************************************************************************************************************************
// add to hash table 2 using double hashing
void add_to_hash_table_method2(pointer temp, pointer *table, int size){
    if(Loud_Factor(size,number_of_elements2)>=0 && Loud_Factor(size,number_of_elements2) < 0.75){
        int code = assci_code(temp->key_course_name,MAX1);
        int index = (code%size)%size;
  ///  printf("Table 2 %s %d \n",temp->key_course_name,index);
        int index1;
            if(table[index] == NULL){
            table[index] = temp;
            table[index]->state = 0;
        }else{
            if(table[index]->state == 1){//the cell is deleted so we can add in its place
              //  table[index] = NULL;
                table[index] = temp;
                table[index]->state = 0;
            }
        if(table[index]->state == 0){
                //occupied -> collision
                number_Of_Collisons_Double_Addressing += 1;
                for(int j = 1; j<size ;j++){
                        int h = double_addressing_hp(size,code);
                    index1 = (index + j*h)%size;
                    if(table[index1] == NULL){
            ///         printf("%s %d\n",temp->key_course_name,index1);
                        table[index1] = temp;
                        table[index1]->state = 0;
                        break;
                    }
                     if(table[index1]->state == 0){
                        number_Of_Collisons_Double_Addressing += 1;
                     }
                }
            }
        }

    }else{// rehash
            int old = size2;
            size2 = rehashing(size2);//the new size
            printf("The old hash size for table 2 is %d, the new hash size is %d\n",old,size1);
            read_courses_info();

    }
}
///***************************************************************************************************************************
void print_hash_table(pointer table1[], int size){
    for(int i = 0 ; i < size; i++){
        if(table1[i] != NULL && table1[i]->state == 0 ){
        printf("%d]-%s %s\n",i,table1[i]->code,table1[i]->key_course_name);
        }
    else{ printf("%d]-EMPTY CELL\n",i);}

    }
    printf("******************************************************************************************\n");

}
///***************************************************************************************************************************
void print_hash_table2(pointer *table1, int size){
     for(int i = 0 ; i < size; i++){
        if(table1[i] != NULL && table1[i]->state == 0 ){
        printf("%d]-%s %s\n",i,table1[i]->code,table1[i]->key_course_name);
        }
    else{ printf("%d]-EMPTY CELL\n",i);}

    }
    printf("******************************************************************************************\n");
}
///***************************************************************************************************************************
void insert_course_from_user(){
    pointer temp = (pointer)malloc(sizeof(struct node_hash));
    Hash temp1;
    printf("Enter the course code:\n");
    scanf("%s",temp->code);
    strcpy(temp1.code,temp->code);

    printf("Enter the course name:\n");
    fflush(stdin);// because it takes \n as a choice for the menu.
    gets(temp->key_course_name);
    strcpy(temp1.key_course_name,temp->key_course_name);

    printf("Enter the department:\n");
    fflush(stdin);// because it takes \n as a choice for the menu.
    gets(temp->department);
    strcpy(temp1.department,temp->department);

    printf("Enter the course hours:\n");
    scanf("%d",&temp->hours);
    int numberOfTopics;
    printf("Enter the number of topics(the number should be 1 or more):\n");
    scanf("%d",&numberOfTopics);
    if(numberOfTopics >=1 ){
        for(int i = 0 ; i < numberOfTopics ; i++){
        printf("Enter topic #%d:\n",(i+1));
            fflush(stdin);// because it takes \n as a choice for the menu.
            gets(temp->topics[i]);
            strcpy(temp1.topics[i],temp->topics[i]);
        }
    }else{
        printf("The number should be more than 1!\n");
        while(numberOfTopics < 1){
             printf("Enter the number of topics(the number should be 1 or more):\n");
            scanf("%d",&numberOfTopics);
           } if(numberOfTopics >=1 ){
            for(int i = 0 ; i < numberOfTopics ; i++){
            printf("Enter topic #%d:\n",(i+1));
            fflush(stdin);// because it takes \n as a choice for the menu.
            gets(temp->topics[i]);
            }
        }
    }
    printf("-----------------------------------------------------------------\n");
    additinoal_array[indx] = temp1;
    indx += 1;
    add_to_hash_table_method1(temp,table1pointer/*,size*/);
    add_to_hash_table_method2(temp,table2pointer,size2);
}
///***************************************************************************************************************************
void search_for_a_specific_word(){
    printf("Choose which table you want to search in:\n");
    printf("1)Table 1 Open Addressing Linear probing.\n");
    printf("2)Table 2 Double Addressing.\n");
    int choice;
    scanf("%d",&choice);
    if( choice != 1 && choice != 2){
    while( choice != 1 && choice != 2){
        printf("The choice should be 1 or 2! please try again\n");
        printf("Choose which table you want to search in:\n");
        printf("1)Table 1 Open Addressing Linear probing.\n");
        printf("2)Table 2 Double Addressing.\n");
        scanf("%d",&choice);
         if(choice == 1 || choice == 2)
            break;
    }
}
    printf("Enter the course name:\n");
    char name[MAX1];
    fflush(stdin);
    gets(name);
    printf("-------------------------------------------------\n");
    int exists =0;
    if(choice == 1){
       for(int i = 0; i < size1; i++){
            if(table1pointer[i] != NULL && strcmp(table1pointer[i]->key_course_name,name) == 0){
                exists = 1 ;
                if( table1pointer[i]->state == 1 ){
                    printf("The course you are searching for is deleted!\n");
                    printf("its information:\n");

                }
                printf("Course Name: %s\n",table1pointer[i]->key_course_name);
                printf("Course code: %s\n",table1pointer[i]->code);
                printf("Course department: %s\n",table1pointer[i]->department);
                printf("Course hours: %d\n",table1pointer[i]->hours);
                printf("Course topics: %s",table1pointer[i]->topics[0]);
                for(int j = 1 ; j < sizeof(table1pointer[i]->topics); j++){
                        if(strcmp(table1pointer[i]->topics[j],"") == 0){
                            printf("\n");
                            break;
                        }

                    printf(", %s",table1pointer[i]->topics[j]);
                }
                printf("\n");
            }
       }
    if(exists == 0){
        printf("The course you are searching for is not exist.\n");
    }

    }else if(choice == 2){
               for(int i = 0; i < size2; i++){
            if(table1pointer[i] != NULL && strcmp(table1pointer[i]->key_course_name,name) == 0){
                exists = 1 ;
                if( table1pointer[i]->state == 1 ){
                    printf("The course you are searching for is deleted!\n");
                    printf("its information:\n");
                }
                printf("Course Name: %s\n",table1pointer[i]->key_course_name);
                printf("Course code: %s\n",table1pointer[i]->code);
                printf("Course department: %s\n",table1pointer[i]->department);
                printf("Course hours: %d\n",table1pointer[i]->hours);
                printf("Course topics: %s",table1pointer[i]->topics[0]);
                for(int j = 1 ; j < sizeof(table1pointer[i]->topics); j++){
                        if(strcmp(table1pointer[i]->topics[j],"") == 0){
                            printf("\n");
                            break;
                        }

                    printf(", %s",table1pointer[i]->topics[j]);
                }
            }
       }
    if(exists == 0){
        printf("The course you are searching for is not exist.\n");
    }

    }else{
        printf("Not a valid choice.\n");
        search_for_a_specific_word();
    }

}
///***************************************************************************************************************************
void write_into_file(){
    FILE *out;
    out = fopen("saved_courses.txt","w");
    for(int i = 0; i < size2; i++){
        if(table2pointer[i] != NULL && table2pointer[i]->state == 0){
            fprintf(out,"%s:%d#%s#%s/",table2pointer[i]->key_course_name,table2pointer[i]->hours,table2pointer[i]->code,table2pointer[i]->department);
            fprintf(out,"%s",table2pointer[i]->topics[0]);
            for(int j = 1 ; j<sizeof(table2pointer[i]->topics); j++){
            if(strcmp(table2pointer[i]->topics[j],"") == 0){
                fprintf(out,"\n");
                break;
            }
            fprintf(out,", %s",table2pointer[i]->topics[j]);
            }
        }

        }
    fclose(out) ;
}
///***************************************************************************************************************************
void delete_a_course(){
    printf("Enter the course name:\n");
    char name[MAX1];
    fflush(stdin);
    gets(name);
    int length = strlen(name);
    printf("%d\n",length);
    for(int i = 0 ; i < size1; i++){
        if(table1pointer[i] != NULL){
        if( strcmp(table1pointer[i]->key_course_name ,name) == 0){
            printf("The course is found and successfully deleted from table 1. \n");
            table1pointer[i]->state = 1;
            course_is_deleted1 = 1;
             table1pointer[i] = NULL;
            number_of_elements1 -= 1;
            }
        }
    }

    for(int i = 0 ; i < size2; i++){
        if(table2pointer[i] != NULL){
        if( strcmp(table2pointer[i]->key_course_name ,name) == 0){
            printf("The course is found and successfully deleted from table 2. \n");
            table2pointer[i]->state = 1;
            course_is_deleted2 = 1;
            table2pointer[i] = NULL;
            number_of_elements2 -= 1;
            }
        }
    }
    if(course_is_deleted2 == 0){
        printf("The course(%s) is not exist in table 2!\n",name);
    }
     if(course_is_deleted1 == 0){
        printf("The course(%s) is not exist in table 1!\n",name);
    }

}
///***************************************************************************************************************************
void compare(){
    printf( "Number of collisions(Open addressing- linear) : %d \n",number_Of_Collisons_Open_Addressing);
    printf( "Number of collisions(Double addressing) : %d \n",number_Of_Collisons_Double_Addressing);
    if(number_Of_Collisons_Open_Addressing < number_Of_Collisons_Double_Addressing){

      printf("The open addressing method is better than double addressing in this case.\n");

    }else if (number_Of_Collisons_Open_Addressing > number_Of_Collisons_Double_Addressing){
          printf("The double addressing method is better than open addressing in this case.\n");
    }else{
        printf("The open addressing method has the same number of collisions as double addressing in this case.\n");
    }
}
