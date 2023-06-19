/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
                                                            Feliciano, Jan Robee E., DLSU ID# 12207004
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h> 
#include <ctype.h> 
#include <conio.h>

#define MAX_RECORDS 100 //defines the maximum amount of records this program can hold

/*BOOLEAN VALUES*/
#define TRUE 1
#define FALSE 0
#define NOT_FOUND -1
#define LOGIN_FAILED -1
#define CANCEL_LOGIN -2 //MUST NOT BE THE SAME AS LOGIN_FAILED

/*USER REGISTRATION DETAILS*/
#define USER_ID     1
#define PASSWORD    2
#define NAME        3
#define ADDRESS     4
#define CONTACT     5
#define SEX         6
#define FIRST_DOSE              7
#define FIRST_DOSE_VACCINE      8
#define FIRST_DOSE_LOCATION     9
#define SECOND_DOSE             10
#define SECOND_DOSE_VACCINE     11
#define SECOND_DOSE_LOCATION    12
#define BOOSTER_DOSE            13
#define BOOSTER_DOSE_VACCINE    14
#define BOOSTER_DOSE_LOCATION   15

/*USER APPOINTMENT DETAILS*/
#define APPOINTMENT_ID  16
#define LOCATION        17
#define VACCINE         18
#define DATE            19
#define TIME            20
#define DOSE            21

/*CHATBOT*/
#define CONVERSATION_ID     1
#define QUESTION            2
#define ANSWER              3
#define CONNECTED_QUESTION  4
#define CONNECTED_ANSWER    5

/*TABLES*/
#define REGISTRATION_TABLE  1
#define APPOINTMENT_TABLE   2
#define CHATBOT_TABLE       3

/*PROMPTS*/
#define PROMPT_TERMINATING_PROGRAM  1
#define FILE_OPEN_ERROR             2
#define MAX_RECORD_ERROR            3
#define PROMPT_ERROR                4
#define INVALID_INPUT               5
#define MAIN_MENU                   6
#define VACCINE_REGISTRATION_MENU   7
#define USER_REGISTRATION_MENU      8
#define VACCINE_APPOINTMENT_MENU    9
#define MANAGE_APPOINTMENT_MENU     10
#define START_CHATBOT               11
#define DATA_MANAGEMENT_MENU        12
#define USER_DATA_MENU              13
#define APPOINTMENT_DATA_MENU       14
#define ADMIN_DATA_MENU             15
#define CHATBOT_DATA_MENU           16
#define SEARCH_DATA_MENU            17
#define EXPORT_DATA_MENU            18
#define IMPORT_DATA_MENU            19

/*DATA*/
#define USER 1
#define APPOINTMENT 2
#define CHATBOT 3
#define ALL 4


#define COLUMN_LENGTH 80 //80 characters per column (the largest size limit for a variable is chatbot question which contains a maximum of 80 characters)
#define REGISTRATION_ROWS 15 //the number of rows in user registration table
#define APPOINTMENT_ROWS 7 //the number of rows in appointment table
#define CHATBOT_ROWS 5 //the number of rows in chatbot table

#define CHATBOT_NAME "MichaelBot" //defines the chatbot's name

struct Record1
{
    /*REGISTRATION*/
    char userID[50]; //max. 10 digits
    char password[50]; //max. 10 characters
    char name[50]; //max. 20 characters
    char address[50]; //max. 30 characters
    char contact[50]; //max. 10 digits
    char sex[50]; //max. 10 characters

    char firstDose[50]; //max. 10 characters (DATE)
    char firstVaccine[50]; //max. 10 characters (BRAND)
    char firstDoseLocation[50]; //max. 10 characters (LOCATION)

    char secondDose[50]; //max. 10 characters (DATE)
    char secondVaccine[50]; //max. 10 characters (BRAND)
    char secondDoseLocation[50]; //max. 10 characters (LOCATION)

    char boosterDose[50]; //max. 10 characters (DATE)
    char boosterVaccine[50]; //max. 10 characters (BRAND)
    char boosterDoseLocation[50]; //max. 10 characters (LOCATION)

    /*APPOINTMENT*/
    char appID[50]; //max. 10 digits
    char location[50]; //max. 10 characters
    char vaccine[50]; //max. 10 characters
    char date[50]; //max. 11 characters
    char time[50]; //max. 6 characters
    char dose[50]; //max. 10 characters

    /*ADMIN STATUS*/
    int isAdmin;
};

typedef struct Record1 Account;

struct Record2
{
    char conversationID[50];
    char question[100];
    char answer[100]; 
    char connectedQuestion[100];
    char connectedAnswer[100];
};

typedef struct Record2 Chatbot;



/*  initializeMasterAdmin modifies User[0] so it could serve as the master admin.
    @param User[] - struct containing the details of a user
*/
void 
initializeMasterAdmin(Account User[])
{
    //NOTE: This is a test user to validate a lot of inputs involving user accounts.
    //This is the master admin.
    strcpy(User[0].userID, "0"); //the master admin's userID should always be 0
    strcpy(User[0].password, "1234");
    strcpy(User[0].name, "Robee");
    strcpy(User[0].address, "N/A");
    strcpy(User[0].contact, "N/A");
    strcpy(User[0].sex, "N/A"); //max. 10 characters

    strcpy(User[0].firstDose, "N/A"); //max. 10 characters (DATE)
    strcpy(User[0].firstVaccine, "N/A"); //max. 10 characters (BRAND)
    strcpy(User[0].firstDoseLocation, "N/A"); //max. 10 characters (LOCATION)

    strcpy(User[0].secondDose, "N/A"); //max. 10 characters (DATE)
    strcpy(User[0].secondVaccine, "N/A"); //max. 10 characters (BRAND)
    strcpy(User[0].secondDoseLocation, "N/A"); //max. 10 characters (LOCATION)

    strcpy(User[0].boosterDose, "N/A"); //max. 10 characters (DATE)
    strcpy(User[0].boosterVaccine, "N/A"); //max. 10 characters (BRAND)
    strcpy(User[0].boosterDoseLocation, "N/A");//max. 10 characters (LOCATION)

    strcpy(User[0].appID, "0");
    strcpy(User[0].location, "N/A"); //max. 10 characters
    strcpy(User[0].vaccine, "N/A"); //max. 10 characters
    strcpy(User[0].date, "N/A"); //max. 11 characters
    strcpy(User[0].time, "N/A");//max. 6 characters
    strcpy(User[0].dose, "N/A");//max. 10 characters

    User[0].isAdmin = TRUE;
}

/*  initializeChatbot initializes the Chatbot so it already contains conversations when the program starts
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
initializeChatbot(Chatbot Conversation[])
{
    //NOTE: These are basic conversations that the Chatbot starts with.
    strcpy(Conversation[0].conversationID, "0");
    strcpy(Conversation[0].question, "hello");
    strcpy(Conversation[0].answer, "Hello! Feel free to ask me anything and I'll try my best to answer :)");

    strcpy(Conversation[1].conversationID, "00");
    strcpy(Conversation[1].question, "goodbye");
    strcpy(Conversation[1].answer, "Goodbye! If you want to exit my program, simply type 'exit'.");

    strcpy(Conversation[2].conversationID, "000");
    strcpy(Conversation[2].question, "thank you");
    strcpy(Conversation[2].answer, "No problem. I am always happy to help!");

    strcpy(Conversation[3].conversationID, "0000");
    strcpy(Conversation[3].question, "is vaccination mandatory");
    strcpy(Conversation[3].answer, "According to DOH.gov: No, vaccination is not mandatory, but is encouraged.");
    strcpy(Conversation[3].connectedQuestion, "When will the COVID-19 vaccine be available");
    strcpy(Conversation[3].connectedAnswer, "According to DOH.gov: Vaccine supplies will arrive in the first quarter of 2021.");

    strcpy(Conversation[4].conversationID, "00000");
    strcpy(Conversation[4].question, "how many active cases are there right now");
    strcpy(Conversation[4].answer, "According to covid19.gov.ph: There are 9,080 active cases as of 02 April 2023.");
    strcpy(Conversation[4].connectedQuestion, "How many asymptomatic cases are there right now");
    strcpy(Conversation[4].connectedAnswer, "There are 6,527 asymptomatic cases as of 02 April 2023. (covid19.gov.ph)");
}

/*  displayDivider displays a divider.
*/
void 
displayDivider()
{
    int i;

    printf("\n"); 

    for (i = 0; i < COLUMN_LENGTH * 2.25; i++)
    {
        printf("─");//prints a divider
    }

    printf("\n\n");
}

/*  displayPrompt displays a prompt (message or menu)
    @param nItem - single-digit integer always presented as a constant
    Pre-condition: nItem is a defined constant that expands to a number from 1-19 (representing 19 prompts).
*/
void 
displayPrompt(int nItem)
{
    switch (nItem)
    {
        case PROMPT_TERMINATING_PROGRAM:
            displayDivider();
            printf("\nTerminating program...\n\n");  
            break;

        case FILE_OPEN_ERROR:
            displayDivider();
            printf("\a");
            printf("\nERROR OPENING FILE.\n\n");
            break;

        case MAX_RECORD_ERROR:
            displayDivider();
            printf("\a");
            printf("\nSorry, the maximum amount of records for this program has been reached.\n\n");
            break;

        case PROMPT_ERROR:
            displayDivider();
            printf("\a");
            break;

        case INVALID_INPUT:
            displayDivider();
            printf("\a");
            printf("\nPlease enter a valid input.\n\n");
            break;

        case MAIN_MENU:
            displayDivider();
            printf("MAIN MENU\n\n");

            printf("1 - Vaccine Registration Menu\n");
            printf("2 - Data Management Menu\n\n");

            printf("Input: ");
            break;

        case VACCINE_REGISTRATION_MENU:   
            displayDivider();
            printf("VACCINE REGISTRATION MENU\n\n");

            printf("1 - User Registration\n");
            printf("2 - Vaccine Appointment\n");
            printf("3 - Chatbot (FAQs)\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;
        
        case USER_REGISTRATION_MENU:
            displayDivider();
            printf("USER REGISTRATION\n\n");

            printf("1 - Register a new account\n");
            printf("2 - View my account\n");
            printf("3 - Exit\n\n");

            printf("Input: ");   
            break;

        case VACCINE_APPOINTMENT_MENU:
            displayDivider();
            printf("VACCINATION APPOINTMENT\n\n");

            printf("1 - Appointment Request\n");
            printf("2 - Manage Appointment\n");
            printf("3 - Exit\n\n");

            printf("Input: ");
            break;

        case MANAGE_APPOINTMENT_MENU:
            displayDivider();
            printf("MANAGE APPOINTMENT\n\n");
            
            printf("Which Would you like to do?\n\n");

            printf("1 - Cancel my appointment.\n");
            printf("2 - Reschedule my appointment.\n");
            printf("3 - Change my vaccine center location and preferred vaccination brand.\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;

        case START_CHATBOT:
            displayDivider();
            printf("CHATBOT (FAQs)\n\n");
            
            printf("Hello! I'm %s!\n", CHATBOT_NAME);
            printf("Before we begin, please note that while I can process most inputs, it is \n");
            printf("still best to enter simple keywords and avoid using special characters so I may assist you better :D\n\n");

            printf("Also, if you want to exit my program, just enter 'exit'.\n\n");

            printf("How may I help you?\n");
            break;
        
        case DATA_MANAGEMENT_MENU:
            displayDivider();
            printf("DATA MANAGEMENT MENU\n\n");

            printf("1 - User\n");
            printf("2 - Appointment\n");
            printf("3 - Manage Admins\n");
            printf("4 - Chatbot\n");
            printf("5 - Search\n");
            printf("6 - Export\n");
            printf("7 - Import\n");
            printf("8 - Exit Menu\n\n");

            printf("Input: ");
            break;

        case USER_DATA_MENU:
            displayDivider();
            printf("USER\n\n");

            printf("1 - Add New User\n");
            printf("2 - View All Users\n");
            printf("3 - Edit User Details\n");
            printf("4 - Delete User\n");
            printf("5 - Exit\n\n");

            printf("Input: ");
            break; 

        case APPOINTMENT_DATA_MENU:
            displayDivider();
            printf("APPOINTMENT\n\n");

            printf("1 - Add New Appointment\n");
            printf("2 - View All Appointments\n");
            printf("3 - Edit Appointment\n");
            printf("4 - Delete Appointment\n");
            printf("5 - Exit\n\n");

            printf("Input: ");
            break;   

        case ADMIN_DATA_MENU:
            displayDivider();
            printf("MANAGE ADMINS\n\n");

            printf("1 - Add New Admin\n");
            printf("2 - View All Admins\n");
            printf("3 - Remove Admin\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;            

        case CHATBOT_DATA_MENU:
            displayDivider();
            printf("CHATBOT\n\n");

            printf("1 - Add New Question and Answer\n");
            printf("2 - View All Questions and Answers\n");
            printf("3 - Edit Questions and Answers\n");
            printf("4 - Delete Questions and Answers\n");
            printf("5 - Exit\n\n");

            printf("Input: ");
            break;                
            
        case SEARCH_DATA_MENU:
            displayDivider();
            printf("SEARCH\n\n");

            printf("1 - Search User\n");
            printf("2 - Search Appointment\n");
            printf("3 - Search Question and Answer\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;

        case EXPORT_DATA_MENU:
            displayDivider();
            printf("EXPORT\n\n");

            printf("1 - Export Users\n");
            printf("2 - Export Appointments\n");
            printf("3 - Export Chatbot Questions and Answers\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;

        case IMPORT_DATA_MENU:
            displayDivider();
            printf("IMPORT\n\n");

            printf("1 - Import Users\n");
            printf("2 - Import Appointments\n");
            printf("3 - Import Chatbot Questions and Answers\n");
            printf("4 - Exit\n\n");

            printf("Input: ");
            break;
    }
}

/*  displayTopBorder displays a top border (used for tables).
*/
void 
displayTopBorder()
{
    /*TOP BORDER (┌─┬─┐)*/
    printf("┌");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┬");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┐\n");
}

/*  displayMiddleBorder displays a middle border (used for tables).
*/
void 
displayMiddleBorder()
{
    /*MIDDLE BORDER (├─┼─┤)*/
    printf("├");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┼");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┤\n");
}

/*  displayBottomBorder displays a bottom border (used for tables).
*/
void 
displayBottomBorder()
{
    /*BOTTOM BORDER (└─┴─┘)*/
    printf("└");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┴");
    for (int col = 0; col < COLUMN_LENGTH; col++)
    {
        printf("─");
    }
    printf("┘\n");
}

/*  displayRow displays a row (used for tables)
    @param nTable - integer always presented as a constant
    @param cFirstCol[] - a string containing what is written in the first column of the table
    @param cSecondCol[] - a string containing what is written in the second column of the table
    @param nRowItem - an integer specifying what item is being printed on the row
    Pre-condition: nTable is a defined constant that expands to a number from 1-3 (representing 3 tables); The limit of nRowItem's range is specified by a constant connected to the constant for nTable.
    (Example: if nTable == REGISTRATION_TABLE then nRowItem == 1 to REGISTRATION_ROWS).
*/
void 
displayRow( int nTable, 
            char cFirstCol[], 
            char cSecondCol[], 
            int nRowItem)
{
    printf("│");

    printf("%s", cFirstCol);

    for (int col = 0; col < COLUMN_LENGTH - strlen(cFirstCol); col++)
    {
        printf(" ");
    }

    printf("│");

    if (nTable == REGISTRATION_TABLE && nRowItem == PASSWORD) //prints the appropriate column for the password row
    {
        for (int j = 0; j < strlen(cSecondCol); j++)
        {
            printf("*");
        }
    }
    else
    {
        printf("%s", cSecondCol);  
    }

    for (int col = 0; col < COLUMN_LENGTH - strlen(cSecondCol); col++)
    {
        printf(" ");
    }   

    printf("│\n");

    switch (nTable)
    {
        case REGISTRATION_TABLE:

            if (nRowItem < REGISTRATION_ROWS)
            {
                displayMiddleBorder(); /*MIDDLE BORDER (├─┼─┤)*/
            }
            else
            {
                displayBottomBorder(); /*BOTTOM BORDER (└─┴─┘)*/
            }
            break;

        case APPOINTMENT_TABLE:

            if (nRowItem < APPOINTMENT_ROWS)
            {
                displayMiddleBorder(); /*MIDDLE BORDER (├─┼─┤)*/
            }
            else 
            {
                displayBottomBorder(); /*BOTTOM BORDER (└─┴─┘)*/
            }
            break;

        case CHATBOT_TABLE:

            if (nRowItem < CHATBOT_ROWS)
            {
                displayMiddleBorder(); /*MIDDLE BORDER (├─┼─┤)*/
            }
            else 
            {
                displayBottomBorder(); /*BOTTOM BORDER (└─┴─┘)*/
            }
            break;
    }

}

/*  displayRegistration displays a user's account as a table
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the User in the array of structures
*/
void 
displayRegistration(Account User[], 
                    int nIndex)
{
    int nRowNum;

    displayTopBorder();

    for (nRowNum = 1; nRowNum <= REGISTRATION_ROWS; nRowNum++)
    {
        switch (nRowNum)
        {
            case 1:
                displayRow(REGISTRATION_TABLE, "userID", User[nIndex].userID, nRowNum);
                break;
            case 2: //password row will be left as blank in final source code
                //displayRow(REGISTRATION_TABLE, "password", User[nIndex].password, nRowNum);
                break;
            case 3:
                displayRow(REGISTRATION_TABLE, "name", User[nIndex].name, nRowNum);
                break;
            case 4:
                displayRow(REGISTRATION_TABLE, "address", User[nIndex].address, nRowNum);
                break;
            case 5:
                displayRow(REGISTRATION_TABLE, "contact", User[nIndex].contact, nRowNum);
                break;
            case 6:
                displayRow(REGISTRATION_TABLE, "sex", User[nIndex].sex, nRowNum);
                break;
            case 7:
                displayRow(REGISTRATION_TABLE, "first dose", User[nIndex].firstDose, nRowNum);
                break;
            case 8:
                displayRow(REGISTRATION_TABLE, "first dose vaccine", User[nIndex].firstVaccine, nRowNum);
                break;
            case 9:
                displayRow(REGISTRATION_TABLE, "first dose location", User[nIndex].firstDoseLocation, nRowNum);
                break;
            case 10:
                displayRow(REGISTRATION_TABLE, "second dose", User[nIndex].secondDose, nRowNum);
                break;
            case 11:
                displayRow(REGISTRATION_TABLE, "second dose vaccine", User[nIndex].secondVaccine, nRowNum);
                break;
            case 12:
                displayRow(REGISTRATION_TABLE, "second dose location", User[nIndex].secondDoseLocation, nRowNum);
                break;
            case 13:
                displayRow(REGISTRATION_TABLE, "booster dose", User[nIndex].boosterDose, nRowNum);
                break;
            case 14:
                displayRow(REGISTRATION_TABLE, "booster dose vaccine", User[nIndex].boosterVaccine, nRowNum);
                break;
            case 15:
                displayRow(REGISTRATION_TABLE, "booster dose location", User[nIndex].boosterDoseLocation, nRowNum);
                break;
        }
    }
}       

/*  displayAppointment displays a user's appointment as a table
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the User in the array of structures
*/
void 
displayAppointment( Account User[], 
                    int nIndex)
{
    int nRowNum;

    displayTopBorder();

    for (nRowNum = 1; nRowNum <= APPOINTMENT_ROWS; nRowNum++)
    {
        switch (nRowNum)
        {
            case 1:
                displayRow(APPOINTMENT_TABLE, "appID", User[nIndex].appID, nRowNum);
                break;
            case 2:
                displayRow(APPOINTMENT_TABLE, "name", User[nIndex].name, nRowNum);
                break;
            case 3:
                displayRow(APPOINTMENT_TABLE, "location", User[nIndex].location, nRowNum);
                break;
            case 4:
                displayRow(APPOINTMENT_TABLE, "vaccine", User[nIndex].vaccine, nRowNum);
                break;
            case 5:
                displayRow(APPOINTMENT_TABLE, "date", User[nIndex].date, nRowNum);
                break;
            case 6:
                displayRow(APPOINTMENT_TABLE, "time", User[nIndex].time, nRowNum);
                break;
            case 7:
                displayRow(APPOINTMENT_TABLE, "dose", User[nIndex].dose, nRowNum);
                break;
        }
    }
}

/*  displayConversation displays a chatbot's conversation details as a table
    @param Conversation[] - struct containing the details of a chatbot conversation
    @param nIndex - integer containing the index of the Conversation in the array of structures
*/
void 
displayConversation(Chatbot Conversation[], 
                    int nIndex)
{
    int rownum;

    displayTopBorder();

    for (rownum = 1; rownum <= APPOINTMENT_ROWS; rownum++)
    {
        switch (rownum)
        {
            case 1:
                displayRow(CHATBOT_TABLE, "conversationID", Conversation[nIndex].conversationID, rownum);
                break;
            case 2:
                displayRow(CHATBOT_TABLE, "question", Conversation[nIndex].question, rownum);
                break;
            case 3:
                displayRow(CHATBOT_TABLE, "answer", Conversation[nIndex].answer, rownum);
                break;
            case 4:
                displayRow(CHATBOT_TABLE, "connected question", Conversation[nIndex].connectedQuestion, rownum);
                break;
            case 5:
                displayRow(CHATBOT_TABLE, "connected answer", Conversation[nIndex].connectedAnswer, rownum);
                break;
        }
    }
}

/*  getRecord fetches the index of the user containing the specified ID
    @param User[] - struct containing the details of a user
    @param ID[] - string containing the userID to be searched 
    @return NOT_FOUND (expands to -1) if a user with the specified ID is not found. Otherwise, returns that user's index.
*/
int 
getRecord(  Account User[], 
            char ID[])
{
    int i;
    int nIndex = NOT_FOUND; //returns -1 if the index is not found (meaning there is no matching record).

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (strcmp(ID, User[i].userID) == 0)
        {
            nIndex = i;
        }
    }

    return nIndex; //returns -1 if the record with the given ID does not exist. Otherwise, returns that record's index.
}

/*  getConversation fetches the index of the chatbot Conversation containing the specified ID
    @param Conversation[] - struct containing the details of a chatbot conversation
    @param ID[] - string containing the conversationID to be searched 
    @return NOT_FOUND (expands to -1) if a conversation with the specified ID is not found. Otherwise, returns that conversation's index.
*/
int 
getConversation(Chatbot Conversation[], 
                char ID[])
{
    int i;
    int nIndex = NOT_FOUND; //returns -1 if the index is not found (meaning there is no matching record).

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (strcmp(ID, Conversation[i].conversationID) == 0)
        {
            nIndex = i;
        }
    }

    return nIndex; //returns -1 if the record with the given ID does not exist. Otherwise, returns that record's index.
}

/*  getEmptyUserIndex fetches the index of the first user element that contains no values in the array of structures
    @param User[] - struct containing the details of a user
    @return NOT_FOUND (expands to -1) if all users in the array of structs contain something. Otherwise, returns the index of the empty struct.
*/
int 
getEmptyUserIndex(Account User[])
{
    int i;
    int nIndex;

    i = 0;
    nIndex = NOT_FOUND;

    while (nIndex == NOT_FOUND && i < MAX_RECORDS)
    {
        if (strlen(User[i].userID) == 0) //if a user struct's userID has no value, then it is empty.
        {
            nIndex = i;
        }       
        else
        {
            ++i;
        }
    }
    
    return nIndex; //returns the index of the empty struct if found, otherwise returns not found (only happens when MAX_RECORDS is reached).
}

/*  getEmptyConversationIndex fetches the index of the first conversation element that contains no values in the array of structures
    @param Conversation[] - struct containing the details of a chatbot conversation
    @return NOT_FOUND (expands to -1) if all chatbot conversations in the array of structs contain something. Otherwise, returns the index of the empty struct.
*/
int 
getEmptyConversationIndex(Chatbot Conversation[])
{
    int i;
    int nIndex;

    i = 0;
    nIndex = NOT_FOUND;

    while (nIndex == NOT_FOUND && i < MAX_RECORDS)
    {
            if (strlen(Conversation[i].conversationID) == 0)
            {
                nIndex = i;
            }
            else
            {
                ++i;
            }
    }

    return nIndex;
}

/*  terminateProgram promotes code readability by showing what a boolean value does
    @param nBoolean - integer always presented as a defined constant (TRUE or FALSE)
    @return TRUE if nBoolean is TRUE; FALSE if nBoolean is FALSE
*/
int 
terminateProgram(int nBoolean)
{
    return nBoolean;
}

/*  enterPassword converts the user's password input to "*" in real time
    @param password[10] - string that holds the user's password
    @return the user's entered password
*/
char 
enterPassword(char password[10])
{
    int i;
    int nStop;
    
    char ch;

    i = 0;
    nStop = 0;

    while(TRUE && nStop == FALSE)
    {
        ch = getch();

        if (ch == 13) //CR / carriage return (user presses enter)
        {
            password[i] = '\0'; 
            nStop = TRUE; //stops receiving input
        }
        else if (ch == 8) //BS / backspace (user presses backspace)
        {
            if(i > 0)
            {
                i--;
                printf("\b \b");
            }

        }
        else if (i < 10)
        {
            password[i++] = ch;
            printf("* \b");
        }
    }

    return *password;
}

/*  userLogin prompts the user to log in to their account
    @param User[] - struct containing the details of a user
    @param nAttempts - integer containing the number of attempts the user is given to log in with their password
    @return the index of the user if the login is successful. Otherwise, returns CANCEL_LOGIN (expands to -2) if the user inputs a userID that does not exist; LOGIN_FAILED (expands to -1) if the user fails to log in within the specified number of attempts;
*/
int 
userLogin(  Account User[], 
            int nAttempts)
{
    char inputID[50];
    char inputPassword[50];

    int nLoggedIn;
    int nIndex;

    nLoggedIn = LOGIN_FAILED;
    nIndex = NOT_FOUND;

    displayDivider();

    while (nLoggedIn != CANCEL_LOGIN && nIndex == NOT_FOUND)
    {
        inputID[0] = '\0';

        printf("Enter userID: ");
        scanf("%s", inputID);

        nIndex = getRecord(User, inputID);

        if (nIndex == NOT_FOUND)
        {
            nLoggedIn = CANCEL_LOGIN;
        }
    }
    
    if (nIndex != NOT_FOUND && nIndex != CANCEL_LOGIN)
    {
        while (nAttempts > 0 && nLoggedIn == LOGIN_FAILED)
        {
            if (nAttempts > 1)
            {            
                printf("Enter password (%d attempts left): ", nAttempts);
            }
            else
            {
                printf("Enter password (%d attempt left): ", nAttempts);
            }
            
            enterPassword(inputPassword); //this function converts the input of the user to * in real time

            if (strcmp(inputPassword, User[nIndex].password) == 0)
            {
                nLoggedIn = nIndex;
                printf("\n");
            }
            else
            {
                printf("\a");
                --nAttempts;

                printf("\n");
            }
        }

        if (nAttempts == 0)
        {
            displayDivider();
            printf("\nLogin failed.\n\n");
        }
    }

    if (nLoggedIn == CANCEL_LOGIN)
    {
        displayDivider();
        printf("\a");
        printf("Sorry, it looks like that userID does not exist.\n");
    }

    return nLoggedIn; // returns -1 or -2 if the user fails / cancels login respectively, otherwise returns the index of the account associated with the user's userID
}

/*  adminLogin prompts the user to log in to their account
    @param User[] - struct containing the details of a user
    @param nAttempts - integer containing the number of attempts the user is given to log in with their password
    @return the index of the user if the login is successful. Otherwise, returns CANCEL_LOGIN (expands to -2) if the user inputs a userID that does not exist / is not an admin; LOGIN_FAILED (expands to -1) if the user fails to log in within the specified number of attempts; 
*/
int 
adminLogin( Account User[], 
            int nAttempts)
{
    char inputID[50];
    char inputPassword[50];

    int nLoggedIn;
    int nIndex;

    nLoggedIn = LOGIN_FAILED;
    nIndex = NOT_FOUND;

    displayDivider();

    while (nLoggedIn != CANCEL_LOGIN && nIndex == NOT_FOUND)
    {
        inputID[0] = '\0';

        printf("Enter userID: ");
        scanf("%s", inputID);

        nIndex = getRecord(User, inputID);

        if (nIndex == NOT_FOUND || User[nIndex].isAdmin == FALSE) // checks if there is a user with the specified ID exists and checks if that user is an admin
        {
            nLoggedIn = CANCEL_LOGIN;
        }
    }
    
    if (nIndex != NOT_FOUND && nIndex != CANCEL_LOGIN)
    {
        while (nAttempts > 0 && nLoggedIn == LOGIN_FAILED)
        {
            if (nAttempts > 1)
            {            
                printf("Enter password (%d attempts left): ", nAttempts);
            }
            else
            {
                printf("Enter password (%d attempt left): ", nAttempts);
            }
            
            enterPassword(inputPassword);

            if (strcmp(inputPassword, User[nIndex].password) == 0)
            {
                nLoggedIn = nIndex;
                printf("\n");
            }
            else
            {
                printf("\a");
                --nAttempts;

                printf("\n");
            }
        }

        if (nAttempts == 0)
        {
            displayDivider();
            printf("\nLogin failed.\n\n");
        }
    }

    if (nLoggedIn == CANCEL_LOGIN)
    {
        displayDivider();
        printf("\a");
        printf("Sorry, it looks like that userID does not exist / is unauthorized.\n");
    }
    

    return nLoggedIn; // returns -1 or -2 if the user fails / cancels login respectively, otherwise returns the index of the account associated with the user's userID
}

/*  sortUsers sorts the Users according to nItem
    @param nItem - integer always presented as a constant 
    @param User[] - struct containing the details of a user
    Pre-condition: nItem is a defined constant that expands to either 1 or 16 (USER_ID or APPOINTMENT_ID)
*/
void 
sortUsers(  int nItem, 
            Account User[])
{
    int i;
    int j;
    int k;

    Account temp;
    int ctr; //the number of user accounts that exist

    ctr = 0;

    switch (nItem)
    {
        case USER_ID: // selection sorts users in ascending order by userID
            for (k = 0; k < MAX_RECORDS; k++)
            {
                if (strlen(User[k].userID) > 0)
                {
                    ++ctr;
                }
            }

            for (i = 0; i < ctr - 1; i++)
            {
                for (j = i + 1; j < ctr; j++)
                {
                    if (strcmp(User[i].userID, User[j].userID) > 0)
                    {
                        temp = User[i];
                        User[i] = User[j];
                        User[j] = temp;
                    }
                }
            }       
            break;
        
        case APPOINTMENT_ID: // selection sorts users in ascending order by appID
            for (k = 0; k < MAX_RECORDS; k++)
            {
                if (strlen(User[k].appID) > 0)
                {
                    ++ctr;
                }
            }

            for (i = 0; i < ctr - 1; i++)
            {
                for (j = i + 1; j < ctr; j++)
                {
                    if (strcmp(User[i].appID, User[j].appID) > 0)
                    {
                        temp = User[i];
                        User[i] = User[j];
                        User[j] = temp;
                    }
                }
            }    
            break;           
    }
}

/*  sortConversations sorts the chatbot Conversations according to conversationID
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
sortConversations(Chatbot Conversation[])
{
    int i;
    int j;
    int k;

    Chatbot temp;
    int ctr;

    ctr = 0;

    for (k = 0; k < MAX_RECORDS; k++)
    {
        if (strlen(Conversation[k].conversationID) > 0)
        {
            ++ctr;
        }
    }

    for (i = 0; i < ctr - 1; i++)
    {
        for (j = i + 1; j < ctr; j++)
        {
            if (strcmp(Conversation[i].conversationID, Conversation[j].conversationID) > 0)
            {
                temp = Conversation[i];
                Conversation[i] = Conversation[j];
                Conversation[j] = temp;
            }
        }
    }       
}

/*  isValidRegistration determines if the entered item is valid or not
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    @param nItem - integer containing the item to be validated
    @return TRUE if the entered item is valid. Otherwise, returns FALSE
    Pre-condition - nItem should be a defined constant that expands from 1-15 (Representing the 15 details in user registration).
*/
int 
isValidRegistration(Account User[], 
                    int nIndex, 
                    int nItem)
{
    int j; //to verify a record with another record
    int k; //to verify strings bit-by-bit
    int nRet;
    
    nRet = TRUE;
    
    switch (nItem)
    {
        case USER_ID:

            if (strlen(User[nIndex].userID) > 10) //check if the user's userID is greater than 10 digits
            {
                nRet = FALSE;
            }
            else
            {
                for (j = 0; j < MAX_RECORDS; j++)
                {
                    if (strcmp(User[nIndex].userID, User[j].userID) == 0) //checks if the user's userID is the same as other patients' userIDs
                    {   
                        if (j != nIndex)
                        {
                            nRet = FALSE;
                            displayDivider();
                            printf("*That ID is already in use.\n");
                        }
                    }
                }

                for (k = 0; k < strlen(User[nIndex].userID); k++) //checks if the user's userID is a number
                {    
                    if (isdigit(User[nIndex].userID[k]) == FALSE) 
                    {
                        nRet = FALSE;
                    }
                }
            }
            
            break;

        case PASSWORD:

            if (strlen(User[nIndex].password) > 10) //checks if entered password is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].password); k++) //checks if the user's password contains a space (' ')
                {
                    if (User[nIndex].password[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }
            
            break;

        case NAME:

            if (strlen(User[nIndex].name) > 20) //checks if entered name is more than 20 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].name); k++) //checks if the user's name contains only letters
                {
                    if (User[nIndex].name[k] != ' ' && User[nIndex].name[k] != '\0')
                    {
                        if (isalpha(User[nIndex].name[k]) == FALSE) 
                        { 
                            nRet = FALSE;
                        }
                    }               
                }
            }

            break;

        case ADDRESS:

            if (strlen(User[nIndex].address) > 30) //checks if entered address is more than 30 characters
            {
                nRet = FALSE;
            }
            
            break;

        case CONTACT:

            if (strlen(User[nIndex].contact) > 10) //checks if entered contact is more than 10 digits
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].contact); k++) //checks if the user's contact is a number
                {    
                    if (isdigit(User[nIndex].contact[k]) == FALSE) 
                    {
                        nRet = FALSE;
                    }
                }
            }

            break;

        case SEX:

            if (strlen(User[nIndex].sex) > 10)
            {
                nRet = FALSE;
            }
            else
            {
                if ((strcmp("MALE", User[nIndex].sex) != 0) && (strcmp("Male", User[nIndex].sex) != 0) && (strcmp("male", User[nIndex].sex) != 0)
                    && (strcmp("FEMALE", User[nIndex].sex) != 0) && (strcmp("Female", User[nIndex].sex) != 0) && (strcmp("female", User[nIndex].sex) != 0))
                {
                    nRet = FALSE;
                }
            }
            
            break;

        case FIRST_DOSE:

            if (strlen(User[nIndex].firstDose) > 10) //checks if entered date is more than 10 characters
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].firstDose[4] != '-') || (User[nIndex].firstDose[7] != '-')) //checks if correct format (YYYY-MM-DD)
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].firstDose[5] == '1') && (User[nIndex].firstDose[6] > '2')) //checks if month is valid
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].firstDose[8] == '3') && (User[nIndex].firstDose[9] > '1')) //checks if day is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].firstDose[5] > '1') //checks if month is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].firstDose[8] > '3') //checks if day is valid
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].firstDose); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].firstDose[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case FIRST_DOSE_VACCINE:

            if (strlen(User[nIndex].firstVaccine) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].firstVaccine); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].firstVaccine[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case FIRST_DOSE_LOCATION:

            if (strlen(User[nIndex].firstDoseLocation) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].firstDoseLocation); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].firstDoseLocation[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case SECOND_DOSE:

            if (strlen(User[nIndex].secondDose) > 10) //checks if entered date is more than 10 characters
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].secondDose[4] != '-') || (User[nIndex].secondDose[7] != '-')) //checks if correct format (YYYY-MM-DD)
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].secondDose[5] == '1') && (User[nIndex].secondDose[6] > '2')) //checks if month is valid
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].secondDose[8] == '3') && (User[nIndex].secondDose[9] > '1')) //checks if day is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].secondDose[5] > '1') //checks if month is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].secondDose[8] > '3') //checks if day is valid
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].secondDose); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].secondDose[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case SECOND_DOSE_VACCINE:

            if (strlen(User[nIndex].secondVaccine) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].secondVaccine); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].secondVaccine[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case SECOND_DOSE_LOCATION:

            if (strlen(User[nIndex].secondDoseLocation) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].secondDoseLocation); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].secondDoseLocation[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

        case BOOSTER_DOSE:
 
            if (strlen(User[nIndex].boosterDose) > 10) //checks if entered date is more than 10 characters
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].boosterDose[4] != '-') || (User[nIndex].boosterDose[7] != '-')) //checks if correct format (YYYY-MM-DD)
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].boosterDose[5] == '1') && (User[nIndex].boosterDose[6] > '2')) //checks if month is valid
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].boosterDose[8] == '3') && (User[nIndex].boosterDose[9] > '1')) //checks if day is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].boosterDose[5] > '1') //checks if month is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].boosterDose[8] > '3') //checks if day is valid
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].boosterDose); k++) //checks if the the string contains a space (' ')
                    {
                        if (User[nIndex].boosterDose[k] == ' ')
                        {
                            nRet = FALSE; 
                        }               
                    }
            }

            break;

        case BOOSTER_DOSE_VACCINE:

            if (strlen(User[nIndex].boosterVaccine) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].boosterVaccine); k++) //checks if the the string contains a space (' ')
                    {
                        if (User[nIndex].boosterVaccine[k] == ' ')
                        {
                            nRet = FALSE; 
                        }               
                    }
            }

            break;

        case BOOSTER_DOSE_LOCATION:

            if (strlen(User[nIndex].boosterDoseLocation) > 10) //checks if entered contact is more than 10 characters
            {
                nRet = FALSE;
            }
            else
            {
                for (k = 0; k < strlen(User[nIndex].boosterDoseLocation); k++) //checks if the the string contains a space (' ')
                {
                    if (User[nIndex].boosterDoseLocation[k] == ' ')
                    {
                        nRet = FALSE; 
                    }               
                }
            }

            break;

    }

    if (nRet == FALSE)
    {
        displayPrompt(INVALID_INPUT);
    }

    return nRet;
}

/*  isValidAppointment determines if the entered item is valid or not
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    @param nItem - integer containing the item to be validated
    @return TRUE if the entered item is valid. Otherwise, returns FALSE
    Pre-condition - the item to be checked should already contain something before function is called (i.e. User[2].appID must already have a value before appID is checked); 
    nIndex should be the index of a user that already has a appID; nItem should be a defined constant that expands from 16-21 (Representing the 6 details in an appointment (excluding name)).
*/
int 
isValidAppointment( Account User[], 
                    int nIndex, 
                    int nItem)
{
    int j; //to verify a record with another record
    int k; //to verify strings bit-by-bit
    int nRet;

    nRet = TRUE;
    
    switch (nItem)
    {
        case APPOINTMENT_ID:

            if (strlen(User[nIndex].appID) > 10)
            {
                nRet = FALSE;
            }
            else
            {
                for (j = 0; j < MAX_RECORDS; j++)
                {
                    if (strcmp(User[nIndex].appID, User[j].appID) == 0) //checks if the user's appID is the same as other users' appIDs
                    {   
                        if (j != nIndex)
                        {
                            nRet = FALSE;
                            displayDivider();
                            printf("*That ID is already in use.\n");
                        }
                    }
                }

                for (k = 0; k < strlen(User[nIndex].appID); k++) //checks if the user's appID is a number
                {    
                    if (isdigit(User[nIndex].appID[k]) == FALSE) 
                    {
                        nRet = FALSE;
                    }
                }
            }
            
            break;

        case LOCATION:

            if (strlen(User[nIndex].location) > 10)
            {
                nRet = FALSE;
            }
            
            break;

        case VACCINE:

            if (strlen(User[nIndex].vaccine) > 10)
            {
                nRet = FALSE;
            }

            break;

        case DATE: //(YYYY-MM-DD)

            if (strlen(User[nIndex].date) > 11) //checks if entered date is more than 11 characters
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].date[4] != '-') || (User[nIndex].date[7] != '-')) //checks if correct format (YYYY-MM-DD)
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].date[5] == '1') && (User[nIndex].date[6] > '2')) //checks if month is valid
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].date[8] == '3') && (User[nIndex].date[9] > '1')) //checks if day is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].date[5] > '1') //checks if month is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].date[8] > '3') //checks if day is valid
            {
                nRet = FALSE;
            }
            
            break;

        case TIME: //(24:00)

            if (strlen(User[nIndex].time) > 6)
            {
                nRet = FALSE;
            }
            else if (User[nIndex].time[2] != ':')
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].time[0] == '2') && (User[nIndex].time[1] > '4')) //checks if hour is valid
            {
                nRet = FALSE;
            }
            else if ((User[nIndex].time[3] == '5') && (User[nIndex].time[4] > '9')) //checks if minute is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].time[0] > '2') //checks if hour is valid
            {
                nRet = FALSE;
            }
            else if (User[nIndex].time[3] > '5') //checks if minute is valid
            {
                nRet = FALSE;
            }

            break;

        case DOSE:

            if (strlen(User[nIndex].dose) > 10)
            {
                nRet = FALSE;
            }
            
            break;

    }

    if (nRet == FALSE)
    {
        displayPrompt(INVALID_INPUT);
    }

    return nRet;    
}

/*  isValidConversation determines if the entered item is valid or not
    @param Conversation[] - struct containing the details of a chatbot conversation
    @param nIndex - integer containing the index of the chatbot conversation
    @param nItem - integer containing the item to be validated
    @return TRUE if the entered item is valid. Otherwise, returns FALSE
    Pre-condition - the item to be checked should already contain something before function is called (i.e. Conversation[2].conversationID must already have a value before conversationID is checked); 
    nIndex should be the index of a conversation that already has a conversationID; nItem should be a defined constant that expands from 1-5 (Representing the 5 details of a chatbot conversation).
*/
int 
isValidConversation(Chatbot Conversation[], 
                    int nIndex, 
                    int nItem)
{
    int j; //to verify a record with another record
    int k; //to verify strings bit-by-bit
    int nRet;

    nRet = TRUE;

    switch (nItem)
    {
        case CONVERSATION_ID:

            if (strlen(Conversation[nIndex].conversationID) > 20)
            {
                nRet = FALSE;
            }
            else
            {
                for (j = 0; j < MAX_RECORDS; j++)
                {
                    if (strcmp(Conversation[nIndex].conversationID, Conversation[j].conversationID) == 0)
                    {
                        if (nIndex != j)
                        {
                            nRet = FALSE;
                            displayDivider();
                            printf("That conversationID is already in use.\n");
                        }
                    }
                }
                
                for (k = 0; k < strlen(Conversation[nIndex].conversationID); k++) //checks if the user's userID is a number
                {    
                    if (isdigit(Conversation[nIndex].conversationID[k]) == FALSE) 
                    {
                        nRet = FALSE;
                    }
                }
            }
            break;

        case QUESTION:

            if (strlen(Conversation[nIndex].question) > 80)
            {
                nRet = FALSE;
            }
            break;
        

        case ANSWER:

            if (strlen(Conversation[nIndex].answer) > 80)
            {
                nRet = FALSE;
            }
            break;

        
        case CONNECTED_QUESTION:

            if (strlen(Conversation[nIndex].connectedQuestion) > 80)
            {
                nRet = FALSE;
            }
            break;

        case CONNECTED_ANSWER:

            if (strlen(Conversation[nIndex].connectedAnswer) > 80)
            {
                nRet = FALSE;
            }
            break;
    }


    if (nRet == FALSE)
    {
        displayPrompt(INVALID_INPUT);
    }

    return nRet;
}

/*  userRegistration updates the account contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
*/
void 
userRegistration(   Account User[], 
                    int nIndex)
{
    char cUserInputProceed;
    int nValid; 
    int ch;

    nValid = TRUE;

    while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets

    /*userID*/
    do
    {
        User[nIndex].userID[0] = '\0';
        
        printf("userID (maximum of 10 digits): ");
        fgets(User[nIndex].userID, 50, stdin);

        User[nIndex].userID[strlen(User[nIndex].userID) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
    
        nValid = isValidRegistration(User, nIndex, USER_ID);
    
    } while (nValid == FALSE);

    /*password*/
    do
    {
        User[nIndex].password[0] = '\0';

        printf("password (maximum of 10 characters): ");
        fgets(User[nIndex].password, 50, stdin);

        User[nIndex].password[strlen(User[nIndex].password) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, PASSWORD);

    } while (nValid == FALSE);

    /*name*/
    do
    {
        User[nIndex].name[0] = '\0';

        printf("name (maximum of 20 characters): ");
        fgets(User[nIndex].name, 50, stdin);

        User[nIndex].name[strlen(User[nIndex].name) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, NAME);

    } while (nValid == FALSE);

    /*address*/
    do
    {
        User[nIndex].address[0] = '\0';

        printf("address (maximum of 30 characters): ");
        fgets(User[nIndex].address, 50, stdin);

        User[nIndex].address[strlen(User[nIndex].address) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, ADDRESS);

    } while (nValid == FALSE);

    /*contact*/
    do
    {
        User[nIndex].contact[0] = '\0';

        printf("contact (maximum of 10 characters): ");
        fgets(User[nIndex].contact, 50, stdin);

        User[nIndex].contact[strlen(User[nIndex].contact) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, CONTACT);

    } while (nValid == FALSE);

    /*sex*/
    do
    {
        User[nIndex].sex[0] = '\0';

        printf("sex (Male/Female): ");
        fgets(User[nIndex].sex, 50, stdin);

        User[nIndex].sex[strlen(User[nIndex].sex) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, SEX);

    } while (nValid == FALSE);

    /*first dose*/
    do
    {
        User[nIndex].firstDose[0] = '\0';

        printf("first dose (YYYY-MM-DD): ");
        fgets(User[nIndex].firstDose, 50, stdin);

        User[nIndex].firstDose[strlen(User[nIndex].firstDose) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, FIRST_DOSE);

    } while (nValid == FALSE);

    /*first dose vaccine*/
    do
    {
        User[nIndex].firstVaccine[0] = '\0';

        printf("first vaccine (maximum of 10 characters): ");
        fgets(User[nIndex].firstVaccine, 50, stdin);

        User[nIndex].firstVaccine[strlen(User[nIndex].firstVaccine) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, FIRST_DOSE_VACCINE);

    } while (nValid == FALSE);

    /*first dose location*/
    do
    {
        User[nIndex].firstDoseLocation[0] = '\0';

        printf("first dose location (maximum of 10 characters): ");
        fgets(User[nIndex].firstDoseLocation, 50, stdin);

        User[nIndex].firstDoseLocation[strlen(User[nIndex].firstDoseLocation) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

        nValid = isValidRegistration(User, nIndex, FIRST_DOSE_LOCATION);

    } while (nValid == FALSE);

    displayDivider();
    printf("Do you want to enter a second and booster dose? (Y/N)\n\n");

    printf("Input: ");
    scanf(" %c", &cUserInputProceed);

    if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
    {
        displayDivider();
        while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets
        /*second dose*/
        do
        {
            User[nIndex].secondDose[0] = '\0';

            printf("second dose (YYYY-MM-DD): ");
            fgets(User[nIndex].secondDose, 50, stdin);

            User[nIndex].secondDose[strlen(User[nIndex].secondDose) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, SECOND_DOSE);

        } while (nValid == FALSE);

        /*second dose vaccine*/
        do
        {
            User[nIndex].secondVaccine[0] = '\0';

            printf("second vaccine (maximum of 10 characters): ");
            fgets(User[nIndex].secondVaccine, 50, stdin);

            User[nIndex].secondVaccine[strlen(User[nIndex].secondVaccine) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, SECOND_DOSE_VACCINE);

        } while (nValid == FALSE);

        /*second dose location*/
        do
        {
            User[nIndex].secondDoseLocation[0] = '\0';

            printf("second dose location (maximum of 10 characters): ");
            fgets(User[nIndex].secondDoseLocation, 50, stdin);

            User[nIndex].secondDoseLocation[strlen(User[nIndex].secondDoseLocation) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, SECOND_DOSE_LOCATION);

        } while (nValid == FALSE);

        /*booster dose*/
        do
        {
            User[nIndex].boosterDose[0] = '\0';

            printf("booster dose (YYYY-MM-DD): ");
            fgets(User[nIndex].boosterDose, 50, stdin);

            User[nIndex].boosterDose[strlen(User[nIndex].boosterDose) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, BOOSTER_DOSE);

        } while (nValid == FALSE);

        /*booster dose vaccine*/
        do
        {
            User[nIndex].boosterVaccine[0] = '\0';

            printf("booster vaccine (maximum of 10 characters): ");
            fgets(User[nIndex].boosterVaccine, 50, stdin);

            User[nIndex].boosterVaccine[strlen(User[nIndex].boosterVaccine) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, BOOSTER_DOSE_VACCINE);

        } while (nValid == FALSE);

        /*booster dose location*/
        do
        {
            User[nIndex].boosterDoseLocation[0] = '\0';

            printf("booster dose location (maximum of 10 characters): ");
            fgets(User[nIndex].boosterDoseLocation, 50, stdin);

            User[nIndex].boosterDoseLocation[strlen(User[nIndex].boosterDoseLocation) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()

            nValid = isValidRegistration(User, nIndex, BOOSTER_DOSE_LOCATION);

        } while (nValid == FALSE);
    }
    else
    {
        strcpy(User[nIndex].secondDose, "N/A");
        strcpy(User[nIndex].secondVaccine, "N/A");
        strcpy(User[nIndex].secondDoseLocation, "N/A");
        strcpy(User[nIndex].boosterDose, "N/A");
        strcpy(User[nIndex].boosterVaccine, "N/A");
        strcpy(User[nIndex].boosterDoseLocation, "N/A");
    }
    printf("\n");

    displayRegistration(User, nIndex);

    printf("\nYour account was registered successfully!\n\n");    
    
    
}

/*  appointmentRequest updates the appointment contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    Pre-Condition: The user must have registered an account first.
*/
void 
appointmentRequest( Account User[], 
                    int nIndex)
{
    int nValid = TRUE;
    int ch;
    
    nValid = TRUE;

    while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets

    /*appID*/
    do
    {
        User[nIndex].appID[0] = '\0';
        
        printf("appID (maximum of 10 digits): ");
        fgets(User[nIndex].appID, 50, stdin);

        User[nIndex].appID[strlen(User[nIndex].appID) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, APPOINTMENT_ID);
       
    } while (nValid == FALSE);

    /*name*/
        //Already uses the name from user registration

    /*location*/
    do
    {
        User[nIndex].location[0] = '\0';
        
        printf("location (maximum of 10 characters): ");
        fgets(User[nIndex].location, 50, stdin);

        User[nIndex].location[strlen(User[nIndex].location) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, LOCATION);
       
    } while (nValid == FALSE);

    /*vaccine*/
    do
    {
        User[nIndex].vaccine[0] = '\0';
        
        printf("vaccine (maximum of 10 characters): ");
        fgets(User[nIndex].vaccine, 50, stdin);

        User[nIndex].vaccine[strlen(User[nIndex].vaccine) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, VACCINE);
       
    } while (nValid == FALSE);

    /*date*/
    do
    {
        User[nIndex].date[0] = '\0';
        
        printf("date (YYYY-MM-DD): ");
        fgets(User[nIndex].date, 50, stdin);

        User[nIndex].date[strlen(User[nIndex].date) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, DATE);
       
    } while (nValid == FALSE);

    /*time*/
    do
    {
        User[nIndex].time[0] = '\0';
        
        printf("time (24-hour format): ");
        fgets(User[nIndex].time, 50, stdin);

        User[nIndex].time[strlen(User[nIndex].time) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, TIME);
       
    } while (nValid == FALSE);

    /*dose*/
    do
    {
        User[nIndex].dose[0] = '\0';
        
        printf("dose (maximum of 10 characters): ");
        fgets(User[nIndex].dose, 50, stdin);

        User[nIndex].dose[strlen(User[nIndex].dose) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, DOSE);
       
    } while (nValid == FALSE);


    printf("\n");

    displayAppointment(User, nIndex);

    printf("\nYour appointment was requested successfully!\n\n");
}

/*  chatbot is the primary function that allows the user to interact with the chatbot feature
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
chatbot(Chatbot Conversation[])
{
    char cUserInput[100];
    char cUserResponse[100];
    char cUserFollowUp[100];

    int nAnswerFound;

    int i;
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets
    

    displayPrompt(START_CHATBOT);

    while (strcmp("exit", cUserInput) != 0) //the user types 'exit' if they want to exit the chatbot program
    {
        
        i = 0; //resets the value of i after every loop
        cUserInput[0] = '\0';
        cUserResponse[0] = '\0';
        cUserFollowUp[0] = '\0';
        nAnswerFound = FALSE;

        printf("\n");
        printf(">> ");
        fgets(cUserInput, 100, stdin);

        cUserInput[strlen(cUserInput) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
        strlwr(cUserInput); //pre-defined function in string.h library that converts the string argument into lowercase

        if (strcmp("exit", cUserInput) == 0)
        {
            printf("\n");
            printf("bot>> Sure, have a good day!\n");
        }
        else
        {
            while (nAnswerFound == FALSE && i < MAX_RECORDS)
            {
                if (strstr(Conversation[i].question, cUserInput) == 0) //pre-defined function in string.h library that checks if the substring is present in the main string
                {
                    ++i;
                }
                else
                {
                    if (strcmp(Conversation[i].question, cUserInput) != 0) //checks if the user's input and the defined question is exactly the same
                    {
                        printf("\n");
                        printf("bot>> Did you mean:\n");
                        printf("%s?\n", Conversation[i].question);

                        printf("\n");
                        printf(">> ");
                        scanf("%s", cUserResponse);
                        strlwr(cUserResponse);

                        if (strcmp("yes", cUserResponse) == 0)
                        {
                            nAnswerFound = TRUE;

                            printf("\n");
                            printf("bot>> ");
                            printf("%s\n", Conversation[i].answer);
                            
                            while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets

                            if (strlen(Conversation[i].connectedQuestion) > 0)
                            {
                                printf("\n");
                                printf("bot>> People also ask me:\n");
                                printf("%s?\n", Conversation[i].connectedQuestion);
                                
                                printf("\n");
                                printf("Do you want to hear the answer?\n");

                                printf("\n");
                                printf(">> ");
                                scanf("%s", cUserFollowUp);
                                strlwr(cUserFollowUp);

                                if (strcmp("yes", cUserFollowUp) == 0 || strcmp("sure", cUserFollowUp) == 0)
                                {
                                    printf("\n");
                                    printf("bot>> ");
                                    printf("%s\n", Conversation[i].connectedAnswer);  
                                }
                                else
                                {
                                    printf("\n");
                                    printf("bot>> Okay.\n");
                                }
                                
                                while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets
                            }
                            
                        }
                        else
                        {
                            nAnswerFound = FALSE;
                            ++i;

                            while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets
                        }               
                    }
                    else
                    {
                        nAnswerFound = TRUE;
                        printf("\n");
                        printf("bot>> ");
                        printf("%s\n", Conversation[i].answer);  

                        if (strlen(Conversation[i].connectedQuestion) > 0)
                        {
                            printf("\n");
                            printf("bot>> People also ask me:\n");
                            printf("%s?\n", Conversation[i].connectedQuestion);
                            
                            printf("\n");
                            printf("Do you want to hear the answer?\n");

                            printf("\n");
                            printf(">> ");
                            scanf("%s", cUserFollowUp);
                            strlwr(cUserFollowUp);

                            if (strcmp("yes", cUserFollowUp) == 0 || strcmp("sure", cUserFollowUp) == 0)
                            {
                                printf("\n");
                                printf("bot>> ");
                                printf("%s\n", Conversation[i].connectedAnswer);
                            }

                            while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets
                        }
                    }
                }
            }

            if (nAnswerFound == FALSE)
            {
                printf("\a");
                printf("\nbot>> Sorry, I don't know the answer. Please type another question.\n");
            }
        }
    }   
}

/*  cancelAppointment cancels an appointment by deleting the appointment contents of a given user index in the array of structs
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    Pre-Condition: The user must have made an appointment request first.
*/
void 
cancelAppointment(  Account User[], 
                    int nIndex)
{
    char cUserInput;
    
    if (nIndex == 0)
    {
        displayPrompt(PROMPT_ERROR);
        printf("Sorry, that appointment cannot be deleted.\n");
    }
    else
    {
        printf("Are you sure you want to cancel your appointment? (Y/N)\n");
        scanf(" %c", &cUserInput);

        if (cUserInput == 'Y' || cUserInput == 'y')
        {
            User[nIndex].appID[0] = '\0';
            User[nIndex].location[0] = '\0';
            User[nIndex].vaccine[0] = '\0';
            User[nIndex].date[0] = '\0';
            User[nIndex].time[0] = '\0';
            User[nIndex].dose[0] = '\0';        

            printf("\n");

            displayAppointment(User, nIndex);

            printf("\nYour appointment was cancelled successfully!\n\n");
        }
    }
    
}

/*  rescheduleAppointment updates the appointment date and time of a given user index in the array of structs
    @param User[] - struct containing the details of a user 
    @param nIndex - integer containing the index of the user
    Pre-Condition: The user must have made an appointment request first.
*/
void 
rescheduleAppointment(  Account User[], 
                        int nIndex)
{
    int nValid;
    int ch;

    nValid = TRUE;

    while((ch = getchar() != '\n') && ch != EOF); //clears the input buffer before asking for input via fgets

    /*date*/
    do
    {
        User[nIndex].date[0] = '\0';
        
        printf("date (YYYY-MM-DD): ");
        fgets(User[nIndex].date, 50, stdin);

        User[nIndex].date[strlen(User[nIndex].date) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, DATE);
       
    } while (nValid == FALSE);

    /*time*/
    do
    {
        User[nIndex].time[0] = '\0';
        
        printf("time (24-hour format): ");
        fgets(User[nIndex].time, 50, stdin);

        User[nIndex].time[strlen(User[nIndex].time) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, TIME);
       
    } while (nValid == FALSE);

    printf("\n");

    displayAppointment(User, nIndex);

    printf("\nYour appointment was rescheduled successfully!\n\n");
}

/*  changeVaccineAppointment updates the appointment vaccination center location and preferred vaccination brand of a given user index
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    Pre-Condition: The user must have made an appointment request first.
*/
void 
changeVaccineAppointment(   Account User[], 
                            int nIndex)
{
    int nValid;
    int ch;

    nValid = TRUE;

    while((ch = getchar() != '\n') && ch != EOF); //clears the input buffer before asking for input via fgets
   
    /*location*/
    do
    {
        User[nIndex].location[0] = '\0';
        
        printf("location (maximum of 10 characters): ");
        fgets(User[nIndex].location, 50, stdin);

        User[nIndex].location[strlen(User[nIndex].location) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, LOCATION);
       
    } while (nValid == FALSE);

    /*vaccine*/
    do
    {
        User[nIndex].vaccine[0] = '\0';
        
        printf("vaccine (maximum of 10 characters): ");
        fgets(User[nIndex].vaccine, 50, stdin);

        User[nIndex].vaccine[strlen(User[nIndex].vaccine) - 1] = '\0'; //removes the trailing '\n' character that occurs when receiving an input via fgets()  
     
        nValid = isValidAppointment(User, nIndex, VACCINE);
       
    } while (nValid == FALSE);

    printf("\n");

    displayAppointment(User, nIndex);

    printf("\nYour vaccination center location and preferred vaccine brand were changed successfully!\n\n");
}

/*  manageAppointment is a menu that allows the user to decide on how they want to manage their appointment
    @param User[] - struct containing the details of a user
    @param nIndex - integer containing the index of the user
    
*/
void 
manageAppointment(  Account User[], 
                    int nIndex)
{
    int nUserInput; 

    nUserInput = 0;

    while (nUserInput != 4)
    {
        displayPrompt(MANAGE_APPOINTMENT_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Cancel my appointment.
                if (strlen(User[nIndex].appID) != 0)
                {
                    cancelAppointment(User, nIndex);
                }
                else
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("Please make an appointment request first.\n\n");
                }
                break;

            case 2: // Reschedule my appointment.
                if (strlen(User[nIndex].appID) != 0)
                {
                    rescheduleAppointment(User, nIndex);
                }
                else
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("Please make an appointment request first.\n\n");
                }
                break;

            case 3: // Change my vaccine center location and preferred vaccination brand.
                if (strlen(User[nIndex].appID) != 0)
                {
                    changeVaccineAppointment(User, nIndex);
                }
                else
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("Please make an appointment request first.\n\n");
                }
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }       
    }
}

/*  addNewUser lets the admin add a new user by updating an empty user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
addNewUser(Account User[])
{
    char cUserInput;
    int nIndex;

    cUserInput = 'Y';

    while (cUserInput == 'Y' || cUserInput == 'y')
    {
        displayDivider();
        nIndex = getEmptyUserIndex(User);

        if (nIndex != NOT_FOUND)
        {
            userRegistration(User, nIndex);

            printf("\n");

            displayDivider();
            printf("Do you want to add another user? (Y/N)\n\n");

            printf("Input: ");
            scanf(" %c", &cUserInput);
        }
        else
        {
            displayPrompt(MAX_RECORD_ERROR);
            cUserInput = 'N';
        }
    }
}

/*  viewAllUsers lets the admin view all of the users currently in the program in table format
    @param User[] - struct containing the details of a user
*/
void 
viewAllUsers(Account User[])
{
    int i;
    int nRecords = 0;

    sortUsers(USER_ID, User);    

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (strlen(User[i].userID) != 0)
        {
            ++nRecords;
            printf("\n");
            printf("User %s: \n", User[i].userID);
            displayRegistration(User, i);
            printf("\n");      
        }
    }         

    if (nRecords == 1)
    {
        printf("\nThis program currently holds %d account.\n\n", nRecords);                
    }
    else
    {
        printf("\nThis program currently holds %d accounts.\n\n", nRecords);
    }

}

/*  editUserDetails lets the admin edit a user by updating the contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
editUserDetails(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputEditAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputEditAnother = 'Y';
    nIndex = NOT_FOUND;

    while ((cUserInputEditAnother == 'Y' || cUserInputEditAnother == 'y')
            && (cUserInput == 'Y' || cUserInput == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user you wish to edit: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be edited.\n");
                }

            } while (strcmp(inputID, "0") == 0);
            
            

            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            userRegistration(User, nIndex);

            printf("\n");

            displayDivider();
            printf("Do you want to edit another user? (Y/N)\n\n");

            printf("Input: ");
            scanf(" %c", &cUserInputEditAnother);
        }    
    }
}

/*  deleteUser lets the admin delete a user by clearing all the contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
deleteUser(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputProceed;
    char cUserInputDeleteAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputProceed = 'Y';
    cUserInputDeleteAnother = 'Y';

    nIndex = NOT_FOUND;

    while ((cUserInput == 'Y' || cUserInput == 'y')
            && (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            && (cUserInputDeleteAnother == 'Y' || cUserInputDeleteAnother == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user you wish to delete: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be deleted.\n");
                }
            } while (strcmp(inputID, "0") == 0);
            
            
            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            displayDivider();
            printf("\nAre you sure you want to delete the user with the following details? (Y/N)\n\n");

            displayRegistration(User, nIndex);
            displayAppointment(User, nIndex);
            printf("\n");
        
            printf("Input: ");
            scanf(" %c", &cUserInputProceed);

            if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            {
                User[nIndex].userID[0] = '\0';
                User[nIndex].password[0] = '\0';
                User[nIndex].name[0] = '\0';
                User[nIndex].address[0] = '\0';
                User[nIndex].contact[0] = '\0';
                User[nIndex].sex[0] = '\0';
                User[nIndex].firstDose[0] = '\0';
                User[nIndex].firstVaccine[0] = '\0';
                User[nIndex].firstDoseLocation[0] = '\0';
                User[nIndex].secondDose[0] = '\0';
                User[nIndex].secondVaccine[0] = '\0';
                User[nIndex].secondDoseLocation[0] = '\0';
                User[nIndex].boosterDose[0] = '\0';
                User[nIndex].boosterVaccine[0] = '\0';
                User[nIndex].boosterDoseLocation[0] = '\0';
                User[nIndex].appID[0] = '\0';
                User[nIndex].location[0] = '\0';
                User[nIndex].vaccine[0] = '\0';
                User[nIndex].date[0] = '\0';
                User[nIndex].time[0] = '\0';
                User[nIndex].dose[0] = '\0';
                User[nIndex].isAdmin = FALSE;

                displayDivider();
                printf("User account deleted successfully.\n");

                displayDivider();
                printf("Do you want to delete another user? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInputDeleteAnother);
            }
        }
    }
}

/*  addNewAppointment lets the admin add a new appointment by updating an empty user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
addNewAppointment(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputAddAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputAddAnother = 'Y';
    nIndex = NOT_FOUND;

    while ((cUserInputAddAnother == 'Y' || cUserInputAddAnother == 'y')
            && (cUserInput == 'Y' || cUserInput == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user you wish to add an appointment for: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be edited.\n");
                }
            } while (strcmp(inputID, "0") == 0);
            
            

            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            if (strlen(User[nIndex].appID) > 0)
            {
                displayPrompt(PROMPT_ERROR);
                printf("Sorry, that user already has an appointment. You can only edit their appointment details.\n");
                cUserInputAddAnother = 'N';
            }
            else
            {
                appointmentRequest(User, nIndex);

                printf("\n");

                displayDivider();
                printf("Do you want to add another appointment? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInputAddAnother);
            }
            
        }    


    }
    
}

/*  viewAllAppointments lets the admin view all of the appointments currently in the program in table format
    @param User[] - struct containing the details of a user
*/
void 
viewAllAppointments(Account User[])
{
    int i;
    int nRecords;

    nRecords = 0;

    sortUsers(APPOINTMENT_ID, User);    

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (strlen(User[i].appID) > 0)
        {
            ++nRecords;
            printf("\n");
            printf("User %s's Appointment: \n", User[i].userID);
            displayAppointment(User, i);
            printf("\n");      
        }
    }         

    if (nRecords == 1)
    {
        printf("\nThis program currently holds %d appointment.\n\n", nRecords);                
    }
    else
    {
        printf("\nThis program currently holds %d appointments.\n\n", nRecords);
    }

}

/*  editAppointment lets the admin edit an appointment by updating the contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
editAppointment(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputEditAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputEditAnother = 'Y';

    nIndex = NOT_FOUND;

    while ((cUserInputEditAnother == 'Y' || cUserInputEditAnother == 'y')
            && (cUserInput == 'Y' || cUserInput == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user whose appointment you wish to edit: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be edited.\n");
                }

            } while (strcmp(inputID, "0") == 0);
            
            

            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            if (strlen(User[nIndex].appID) == 0) //checks if the user has an appointment
            {
                displayPrompt(PROMPT_ERROR);
                printf("That user does not have an appointment.\n");
                cUserInputEditAnother = 'N';
            }
            else
            {
                appointmentRequest(User, nIndex);

                printf("\n");

                displayDivider();
                printf("Do you want to edit another appointment? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInputEditAnother);
            }
        }    
    }
}

/*  deleteAppointment lets the admin delete a user by clearing the appointment contents of a particular user index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
deleteAppointment(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputDelete;
    char cUserInputDeleteAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputDelete = 'Y';
    cUserInputDeleteAnother = 'Y';

    nIndex = NOT_FOUND;

    while ((cUserInput == 'Y' || cUserInput == 'y')
            && (cUserInputDelete == 'Y' || cUserInputDelete == 'y')
            && (cUserInputDeleteAnother == 'Y' || cUserInputDeleteAnother == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user whose appointment you wish to delete: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat appointment cannot be deleted.\n");
                }
            } while (strcmp(inputID, "0") == 0);
            
            
            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            if (strlen(User[nIndex].appID) == 0) //checks if the user has an appointment
            {
                displayPrompt(PROMPT_ERROR);
                printf("That user does not have an appointment.\n");
                cUserInputDeleteAnother = 'N';
            }
            else
            {
                displayDivider();
                printf("\nAre you sure you want to delete the appointment with the following details? (Y/N)\n\n");

                displayAppointment(User, nIndex);
                printf("\n");
            
                printf("Input: ");
                scanf(" %c", &cUserInputDelete);

                if (cUserInputDelete == 'Y' || cUserInputDelete == 'y')
                {
                    User[nIndex].appID[0] = '\0';
                    User[nIndex].location[0] = '\0';
                    User[nIndex].vaccine[0] = '\0';
                    User[nIndex].date[0] = '\0';
                    User[nIndex].time[0] = '\0';
                    User[nIndex].dose[0] = '\0';
                
                    printf("\n\nUser appointment deleted successfully.\n\n");

                    displayDivider();
                    printf("Do you want to delete another appointment? (Y/N)\n\n");

                    printf("Input: ");
                    scanf(" %c", &cUserInputDeleteAnother);
                }    
            } 
        }
    }
}

/*  addNewAdmin lets the admin add another admin by updating one of the members (isAdmin) in the user struct
    @param User[] - struct containing the details of a user
*/
void 
addNewAdmin(Account User[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputProceed;
    char cUserInputAddAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputProceed = 'Y';
    cUserInputAddAnother = 'Y';

    nIndex = NOT_FOUND;

    while ((cUserInput == 'Y' || cUserInput == 'y')
            && (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            && (cUserInputAddAnother == 'Y' || cUserInputAddAnother == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the user you wish to add as admin: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be edited.\n");
                }

            } while (strcmp(inputID, "0") == 0);
            
            
            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            displayDivider();
            printf("\nAre you sure you want to give admin status to the user with the following details? (Y/N)\n\n");

            displayRegistration(User, nIndex);
            printf("\n");
        
            printf("Input: ");
            scanf(" %c", &cUserInputProceed);

            if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            {
                User[nIndex].isAdmin = TRUE;
                
                displayDivider();
                printf("User added as admin successfully.\n");

                displayDivider();
                printf("Do you want to add another admin? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInputAddAnother);
            }
        }
    }
}

/*  viewAllAdmins lets the admin view all of the admins currently in the program in table format
    @param User[] - struct containing the details of a user
*/
void 
viewAllAdmins(Account User[])
{
    int i;
    int nRecords;
    
    nRecords = 0;

    sortUsers(USER_ID, User);    

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (User[i].isAdmin == TRUE)
        {
            ++nRecords;
            printf("\n");
            printf("User %s: \n", User[i].userID);
            displayRegistration(User, i);
            printf("\n");      
        }
    }         

    if (nRecords == 1)
    {
        printf("\nThis program currently has %d admin.\n\n", nRecords);                
    }
    else
    {
        printf("\nThis program currently has %d admins.\n\n", nRecords);
    }

}

/*  removeAdmin lets the admin remove an admin by updating one of the members (isAdmin) in the user struct
    @param User[] - struct containing the details of a user
*/
void 
removeAdmin(Account User[])
{
    //NOTE: An admin can delete themself, but once they exit the Data Management Menu they can no longer access it again.
    //The master admin cannot delete themself.

    char inputID[50];

    char cUserInput;
    char cUserInputProceed;
    char cUserInputRemoveAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputProceed = 'Y';
    cUserInputRemoveAnother = 'Y';

    nIndex = NOT_FOUND;

    while ((cUserInput == 'Y' || cUserInput == 'y')
            && (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            && (cUserInputRemoveAnother == 'Y' || cUserInputRemoveAnother == 'y'))
    {
        while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
        {
            do
            {
                printf("\nEnter the userID of the admin you wish to remove: ");
                scanf("%s", inputID);

                if (strcmp(inputID, "0") == 0)
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("\nThat user cannot be deleted.\n");
                }

            } while (strcmp(inputID, "0") == 0);
            
            
            nIndex = getRecord(User, inputID);

            if (nIndex == NOT_FOUND)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nUser not found. Try again? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInput);
            }
        }

        if (nIndex != NOT_FOUND)
        {
            displayDivider();
            printf("\nAre you sure you want to remove the admin status of the user with the following details? (Y/N)\n\n");

            displayRegistration(User, nIndex);
            printf("\n");
        
            printf("Input: ");
            scanf(" %c", &cUserInputProceed);

            if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
            {
                User[nIndex].isAdmin = FALSE;
            
                printf("\n\nAdmin removed successfully.\n\n");

                displayDivider();
                printf("Do you want to remove another admin? (Y/N)\n\n");

                printf("Input: ");
                scanf(" %c", &cUserInputRemoveAnother);
            }
        }
    }
}

/*  addNewConversation lets the admin update the contents of a particular chatbot conversation index
    @param Conversation[] - struct containing the details of a chatbot conversation
    @param nIndex - integer containing the index of the Conversation in the array of structures
*/
void 
addNewConversation( Chatbot Conversation[], 
                    int nIndex)
{
    char cUserInput;
    int nValid;
    int ch;
    
    nValid = TRUE;

    while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets

    /*conversationID*/
    do
    {
        Conversation[nIndex].conversationID[0] = '\0';

        printf("conversationID (maximum of 20 characters): ");
        fgets(Conversation[nIndex].conversationID, 50, stdin);

        Conversation[nIndex].conversationID[strlen(Conversation[nIndex].conversationID) - 1] = '\0'; //removes the trailing /n

        nValid = isValidConversation(Conversation, nIndex, CONVERSATION_ID);

    } while (nValid == FALSE);    

    /*question*/
    do
    {
        Conversation[nIndex].question[0] = '\0';

        printf("question (NOTE: Please enter a unique phrase and refrain from entering a single word): ");
        fgets(Conversation[nIndex].question, 50, stdin);

        Conversation[nIndex].question[strlen(Conversation[nIndex].question) - 1] = '\0'; //removes the trailing /n
        strlwr(Conversation[nIndex].conversationID);


        nValid = isValidConversation(Conversation, nIndex, QUESTION);

    } while (nValid == FALSE);

    /*answer*/
    do
    {
        Conversation[nIndex].answer[0] = '\0';

        printf("answer: ");
        fgets(Conversation[nIndex].answer, 50, stdin);

        Conversation[nIndex].answer[strlen(Conversation[nIndex].answer) - 1] = '\0'; //removes the trailing /n

        nValid = isValidConversation(Conversation, nIndex, ANSWER);

    } while (nValid == FALSE);

    printf("\nDo you want to add a connected question? (Y/N)\n");
    printf("*A connected question is a follow-up query that relates to the main question.\n\n");

    printf("Input: ");
    scanf(" %c", &cUserInput);

    while((ch = getchar()) != '\n' && ch != EOF); //clears the input buffer before asking for input via fgets

    if (cUserInput == 'Y' || cUserInput == 'y')
    {
        /*connected question*/
        do
        {
            Conversation[nIndex].connectedQuestion[0] = '\0';

            printf("connected question: ");
            fgets(Conversation[nIndex].connectedQuestion, 50, stdin);

            Conversation[nIndex].connectedQuestion[strlen(Conversation[nIndex].connectedQuestion) - 1] = '\0'; //removes the trailing /n

            nValid = isValidConversation(Conversation, nIndex, CONNECTED_QUESTION);

        } while (nValid == FALSE);            

        /*connected answer*/
        do
        {
            Conversation[nIndex].connectedAnswer[0] = '\0';

            printf("connected answer: ");
            fgets(Conversation[nIndex].connectedAnswer, 50, stdin);

            Conversation[nIndex].connectedAnswer[strlen(Conversation[nIndex].connectedAnswer) - 1] = '\0'; //removes the trailing /n

            nValid = isValidConversation(Conversation, nIndex, CONNECTED_ANSWER);

        } while (nValid == FALSE);
    }

    //NOTE: Even if connected question and answer have no content, they still should not contain a string (e.g. "N/A") because the chatbot detects the existence of a connected question through its string length.

    printf("\n");

    displayConversation(Conversation, nIndex);
}

/*  viewAllConversations lets the admin view all of the chatbot Conversations currently in the program in table format
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
viewAllConversations(Chatbot Conversation[])
{
    int i;
    int nRecords;

    nRecords = 0;

    sortConversations(Conversation);    

    for (i = 0; i < MAX_RECORDS; i++)
    {
        if (strlen(Conversation[i].question) > 0)
        {
            ++nRecords;
            printf("\n");
            printf("Conversation %s: \n", Conversation[i].conversationID);
            displayConversation(Conversation, i);
            printf("\n");               
        }
   
    }
       

    if (nRecords == 1)
    {
        printf("\nThis program currently holds %d conversation.\n\n", nRecords);                
    }
    else
    {
        printf("\nThis program currently holds %d conversations.\n\n", nRecords);
    }   
}

/*  editConversation lets the admin edit a chatbot conversation by updating the contents of a particular conversation index in the array of structs
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
editConversation(Chatbot Conversation[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputEditAnother;

    int nIndex;

    cUserInput = 'Y';
    cUserInputEditAnother = 'Y';

    nIndex = NOT_FOUND;

    while (nIndex == NOT_FOUND && cUserInput == 'Y')
    {
        do
        {
            printf("\nEnter the conversationID of the question and answer you wish to edit: ");
            scanf("%s", inputID);

            if (strcmp(inputID, "0") == 0)
            {
                displayPrompt(PROMPT_ERROR);
                printf("\nThat conversation cannot be edited.\n");
            }

        } while (strcmp(inputID, "0") == 0);       

        nIndex = getConversation(Conversation, inputID);

        if (nIndex == NOT_FOUND)
        {
            displayPrompt(PROMPT_ERROR);
            printf("\nConversation not found. Try again? (Y/N)\n\n");

            printf("Input: ");
            scanf(" %c", &cUserInput);       
        }
    }

    if (nIndex != NOT_FOUND)
    {
        addNewConversation(Conversation, nIndex);

        printf("\n\nConversation was edited successfully.\n\n");

        displayDivider();
        printf("Do you want to edit another conversation? (Y/N)\n\n");

        printf("Input: ");
        scanf(" %c", &cUserInputEditAnother);

        if (cUserInputEditAnother == 'Y' || cUserInputEditAnother == 'y')
        {
            editConversation(Conversation);
        }
    }
}

/*  deleteConversation lets the admin delete a chatbot conversation by clearing the appointment contents of a particular conversation index in the array of structs
    @param User[] - struct containing the details of a user
*/
void 
deleteConversation(Chatbot Conversation[])
{
    char inputID[50];

    char cUserInput;
    char cUserInputDelete;
    char cUserInputDeleteAnother;
    int nIndex;

    
    cUserInput = 'Y';
    cUserInputDelete = 'Y';
    cUserInputDeleteAnother = 'Y';

    nIndex = NOT_FOUND;

    while (nIndex == NOT_FOUND && (cUserInput == 'Y' || cUserInput == 'y'))
    {
        printf("\nEnter the conversationID of the question and answer you wish to delete: ");
        scanf("%s", inputID);


        nIndex = getConversation(Conversation, inputID);

        if (nIndex == NOT_FOUND)
        {
            displayPrompt(PROMPT_ERROR);
            printf("\nConversation not found. Try again? (Y/N)\n\n");

            printf("Input: ");
            scanf(" %c", &cUserInput);       
        }
    }

    if (nIndex != NOT_FOUND)
    {
        displayDivider();
        printf("Are you sure you want to delete the conversation with the following details? (Y/N) \n\n");

        displayConversation(Conversation, nIndex);
        printf("\n");

        printf("Input: ");
        scanf(" %c", &cUserInputDelete);

        if (cUserInputDelete == 'Y' || cUserInputDelete == 'y')
        {
            Conversation[nIndex].conversationID[0] = '\0';
            Conversation[nIndex].question[0] = '\0';
            Conversation[nIndex].answer[0] = '\0';
            Conversation[nIndex].connectedQuestion[0] = '\0';
            Conversation[nIndex].connectedAnswer[0] = '\0';

            printf("\n\nConversation deleted successfully.\n\n");

            displayDivider();
            printf("Do you want to delete another conversation? (Y/N)\n\n");

            printf("Input: ");
            scanf(" %c", &cUserInputDeleteAnother);

            if (cUserInputDeleteAnother == 'Y' || cUserInputDeleteAnother == 'y')
            {
                deleteConversation(Conversation);
            }        
        }
    }    
}

/*  exportUsers exports the details of all users currently in the program
    @param User[] - struct containing the details of a user
*/
void 
exportUsers(Account User[])
{
    FILE *fFileName;
    FILE *fUsers;

    char fileName[100];
    char cUserInputProceed;

    int nValid;

    int i;

    nValid = FALSE;
    
    sortUsers(USER_ID, User); //sorts users by userID before export

    displayDivider();

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to export to (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }
    }

    printf("\n");
    printf("You are about to export data to the following files:\n");
    printf("%s\n", fileName);
    printf("Users.txt\n\n");

    printf("Proceed? (Y/N)\n\n");

    printf("Input: ");
    scanf(" %c", &cUserInputProceed);

    if ((cUserInputProceed == 'Y') || (cUserInputProceed == 'y'))
    {
        fUsers = fopen("Users.txt", "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(User[i].userID) > 0) //checks if a user exists (meaning they have a userID)
            {
                fprintf(fUsers, "%s", User[i].userID); // user id
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].password); // password
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].name); // name
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].address); // address
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].contact); // contact number
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].sex); // sex
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].firstDoseLocation); // location1
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].firstDose); // date1
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].firstVaccine); // vaccine1
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].secondDoseLocation); // location2
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].secondDose); // date2
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].secondVaccine); // vaccine2
                fprintf(fUsers, "\n");
                fprintf(fUsers, "%s", User[i].boosterDoseLocation); // location3
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].boosterDose); // date3
                fprintf(fUsers, " ");
                fprintf(fUsers, "%s", User[i].boosterVaccine); // vaccine3
                fprintf(fUsers, "\n");

                fprintf(fUsers, "\n"); //moves on to the next user
            }
        }

        fclose(fUsers);

        fFileName = fopen(fileName, "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(User[i].userID) > 0) //checks if a user exists (meaning they have a userID)
            {
                fprintf(fFileName, "%s", User[i].userID); // user id
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].password); // password
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].name); // name
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].address); // address
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].contact); // contact number
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].sex); // sex
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].firstDoseLocation); // location1
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].firstDose); // date1
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].firstVaccine); // vaccine1
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].secondDoseLocation); // location2
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].secondDose); // date2
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].secondVaccine); // vaccine2
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].boosterDoseLocation); // location3
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].boosterDose); // date3
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].boosterVaccine); // vaccine3
                fprintf(fFileName, "\n");

                fprintf(fFileName, "\n"); //moves on to the next user
            }
        }

        fclose(fFileName);

        printf("\n");
        displayDivider();
        printf("Files exported successfully.\n");
    }
    
    
    /*
    EXPECTED OUTPUT
    
    <user1 id><space><password><new line>
    <name><new line>
    <address><new line>
    <contact number><new line>
    <sex><new line>
    <location1><space><date1><space><vaccine1><new line>
    <location2><space><date2><space><vaccine2><new line>
    <location3><space><date3><space><vaccine3><new line>
    <new line>
    <user2 id><space><password><new line>
    <name><new line>
    <address><new line>
    <contact number><new line>
    <sex><new line>
    <location1><space><date1><space><vaccine1><new line>
    <location2><space><date2><space><vaccine2><new line>
    <location3><space>><date3><space><vaccine3><new line>
    <new line>
    ...
    <userN id><space><password><new line>
    <name><new line>
    <address><new line>
    <contact number><new line>
    <sex><new line>
    <location1><space><date1><space><vaccine1><new line>
    <location2><space><date2><space><vaccine2><new line>
    <location3><space><date3><space><vaccine3><new line>
    <new line>
    <eof>
    */
}

/*  exportAppointments exports the details of all appointments currently in the program
    @param User[] - struct containing the details of a user
*/
void 
exportAppointments(Account User[])
{
    FILE *fFileName;
    FILE *fAppointments;

    char fileName[100];
    char cUserInputProceed;

    int nValid;

    int i;

    nValid = FALSE;

    sortUsers(APPOINTMENT_ID, User); //sorts users by appID before export

    displayDivider();

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to export to (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }       
    }

    printf("\n");
    printf("You are about to export data to the following files:\n");
    printf("%s\n", fileName);
    printf("Appointment.txt\n\n");

    printf("Proceed? (Y/N)\n\n");

    printf("Input: ");
    scanf(" %c", &cUserInputProceed);

    if ((cUserInputProceed == 'Y') || (cUserInputProceed == 'y'))
    {
        fAppointments = fopen("Appointment.txt", "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(User[i].appID) > 0) //checks if an appointment exists (meaning they have an appID)
            {
                fprintf(fAppointments, "%s", User[i].appID); // appointment id
                fprintf(fAppointments, " ");
                fprintf(fAppointments, "%s", User[i].userID); // user id
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].name); // name
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].location); // location
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].vaccine); // vaccine
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].date); // date
                fprintf(fAppointments, " ");
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].time); // time
                fprintf(fAppointments, "\n");
                fprintf(fAppointments, "%s", User[i].dose); //  dose
                fprintf(fAppointments, "\n");

                fprintf(fAppointments, "\n"); //moves on to the next appointment
            }
        }

        fclose(fAppointments);

        fFileName = fopen(fileName, "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(User[i].appID) > 0) //checks if an appointment exists (meaning they have an appID)
            {
                fprintf(fFileName, "%s", User[i].appID); // appointment id
                fprintf(fFileName, " ");
                fprintf(fFileName, "%s", User[i].userID); // user id
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].name); // name
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].location); // location
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].vaccine); // vaccine
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].date); // date
                fprintf(fFileName, " ");
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].time); // time
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", User[i].dose); //  dose
                fprintf(fFileName, "\n");

                fprintf(fFileName, "\n"); //moves on to the next appointment
            }
        }

        fclose(fFileName);

        printf("\n");
        displayDivider();
        printf("Files exported successfully.\n");
    }
    


    /*
    EXPECTED OUTPUT:

    <appointment1 id><space><user id><new line>
    <name><new line>
    <location><new line>
    <vaccine><new line>
    <date><space><new line>
    <time><new line>
    <dose><new line>
    <new line>
    <appointment2 id><space><user id><new line>
    <name><new line>
    <location><new line>
    <vaccine><new line>
    <date><space><new line>
    <time><new line>
    <dose><new line>
    <new line>
    ...
    <appointmentN id><space><user id><new line>
    <name><new line>
    <location><new line>
    <vaccine><new line>
    <date><space><new line>
    <time><new line>
    <dose><new line>
    <new line>
    <eof>
    */
}

/*  exportChatbot exports the questions and answers of all chatbot conversations
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
exportChatbot(Chatbot Conversation[])
{
    FILE *fFileName;
    FILE *fChatbot;

    char fileName[100];

    char cUserInputProceed;
    int nValid;

    int i;

    nValid = FALSE;

    sortConversations(Conversation);

    displayDivider();

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to export to (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }
    }

    printf("\n");
    printf("You are about to export data to the following files:\n");
    printf("%s\n", fileName);
    printf("Chatbot.txt\n\n");

    printf("NOTE: To conform with the Machine Project specifications, this program will not export conversationIDs, connected questions, and connected answers.\n\n");

    printf("Proceed? (Y/N)\n\n");

    printf("Input: ");
    scanf(" %c", &cUserInputProceed);

    if ((cUserInputProceed == 'Y') || (cUserInputProceed == 'y'))
    {
        fChatbot = fopen("Chatbot.txt", "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(Conversation[i].conversationID) > 0)
            {
                fprintf(fChatbot, "%s", Conversation[i].question);
                fprintf(fChatbot, "\n");
                fprintf(fChatbot, "%s", Conversation[i].answer);
                fprintf(fChatbot, "\n");

                //moves on to the next chatbot question and answer
            }
        }

        fclose(fChatbot);      

        fFileName = fopen(fileName, "w");

        for (i = 0; i < MAX_RECORDS; i++)
        {
            if (strlen(Conversation[i].conversationID) > 0)
            {
                fprintf(fFileName, "%s", Conversation[i].question);
                fprintf(fFileName, "\n");
                fprintf(fFileName, "%s", Conversation[i].answer);
                fprintf(fFileName, "\n");

                //moves on to the next chatbot question and answer
            }
        }

        fclose(fFileName);         

    }

    /*
    EXPECTED OUTPUT

    <question1><new line>
    <answer1><new line>
    <question2><new line>
    <answer2><new line>
    ...
    <questionN><new line>
    <answerN><new line>
    <eof>
    */
}

/*  exportAllData exports all data into their respective files
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
    @param nItem - integer that is presented as a constant
    Pre-condition: nItem is a constant that expands fom 1-4
*/
void 
exportAllData(  Account User[], 
                Chatbot Conversation[],
                int nItem)
{
    FILE *fUsers;
    FILE *fAppointments;
    FILE *fChatbot;

    int i;

    
    switch (nItem)
    {
        case USER:
            /*EXPORTING USERS TO USERS.TXT*/ 
            fUsers = fopen("Users.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(User[i].userID) > 0) //checks if a user exists (meaning they have a userID)
                {
                    fprintf(fUsers, "%s", User[i].userID); // user id
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].password); // password
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].name); // name
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].address); // address
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].contact); // contact number
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].sex); // sex
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].firstDoseLocation); // location1
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].firstDose); // date1
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].firstVaccine); // vaccine1
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].secondDoseLocation); // location2
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].secondDose); // date2
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].secondVaccine); // vaccine2
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].boosterDoseLocation); // location3
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].boosterDose); // date3
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].boosterVaccine); // vaccine3
                    fprintf(fUsers, "\n");

                    fprintf(fUsers, "\n"); //moves on to the next user
                }
            }

            fclose(fUsers);

            displayDivider();
            printf("User data copied to Users.txt.\n");
            break;

        case APPOINTMENT:
            /*EXPORTING APPOINTMENTS TO APPOINTMENT.TXT*/
            fAppointments = fopen("Appointment.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(User[i].appID) > 0) //checks if an appointment exists (meaning they have an appID)
                {
                    fprintf(fAppointments, "%s", User[i].appID); // appointment id
                    fprintf(fAppointments, " ");
                    fprintf(fAppointments, "%s", User[i].userID); // user id
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].name); // name
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].location); // location
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].vaccine); // vaccine
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].date); // date
                    fprintf(fAppointments, " ");
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].time); // time
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].dose); //  dose
                    fprintf(fAppointments, "\n");

                    fprintf(fAppointments, "\n"); //moves on to the next appointment
                }
            }

            fclose(fAppointments);

            displayDivider();
            printf("Appointment data copied to Appointment.txt.\n");
            break;

        case CHATBOT:
            /*EXPORTING QUESTIONS AND ANSWERS TO CHATBOT.TXT*/
            fChatbot = fopen("Chatbot.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(Conversation[i].conversationID) > 0)
                {
                    fprintf(fChatbot, "%s", Conversation[i].question);
                    fprintf(fChatbot, "\n");
                    fprintf(fChatbot, "%s", Conversation[i].answer);
                    fprintf(fChatbot, "\n");

                    //moves on to the next chatbot question and answer
                }
            }
            
            fclose(fChatbot);

            displayDivider();
            printf("Question and Answer data copied to Chatbot.txt.\n");
            break;

        case ALL:
            /*EXPORTING USERS TO USERS.TXT*/ 
            fUsers = fopen("Users.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(User[i].userID) > 0) //checks if a user exists (meaning they have a userID)
                {
                    fprintf(fUsers, "%s", User[i].userID); // user id
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].password); // password
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].name); // name
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].address); // address
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].contact); // contact number
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].sex); // sex
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].firstDoseLocation); // location1
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].firstDose); // date1
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].firstVaccine); // vaccine1
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].secondDoseLocation); // location2
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].secondDose); // date2
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].secondVaccine); // vaccine2
                    fprintf(fUsers, "\n");
                    fprintf(fUsers, "%s", User[i].boosterDoseLocation); // location3
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].boosterDose); // date3
                    fprintf(fUsers, " ");
                    fprintf(fUsers, "%s", User[i].boosterVaccine); // vaccine3
                    fprintf(fUsers, "\n");

                    fprintf(fUsers, "\n"); //moves on to the next user
                }
            }

            fclose(fUsers);

            /*EXPORTING APPOINTMENTS TO APPOINTMENT.TXT*/
            fAppointments = fopen("Appointment.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(User[i].appID) > 0) //checks if an appointment exists (meaning they have an appID)
                {
                    fprintf(fAppointments, "%s", User[i].appID); // appointment id
                    fprintf(fAppointments, " ");
                    fprintf(fAppointments, "%s", User[i].userID); // user id
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].name); // name
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].location); // location
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].vaccine); // vaccine
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].date); // date
                    fprintf(fAppointments, " ");
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].time); // time
                    fprintf(fAppointments, "\n");
                    fprintf(fAppointments, "%s", User[i].dose); //  dose
                    fprintf(fAppointments, "\n");

                    fprintf(fAppointments, "\n"); //moves on to the next appointment
                }
            }

            fclose(fAppointments);  

            /*EXPORTING QUESTIONS AND ANSWERS TO CHATBOT.TXT*/
            fChatbot = fopen("Chatbot.txt", "w");

            for (i = 0; i < MAX_RECORDS; i++)
            {
                if (strlen(Conversation[i].conversationID) > 0)
                {
                    fprintf(fChatbot, "%s", Conversation[i].question);
                    fprintf(fChatbot, "\n");
                    fprintf(fChatbot, "%s", Conversation[i].answer);
                    fprintf(fChatbot, "\n");

                    //moves on to the next chatbot question and answer
                }
            }
            
            fclose(fChatbot);
            
            printf("\n");
            printf("User data copied to Users.txt.\n\n");
            printf("Appointment data copied to Appointment.txt.\n\n");
            printf("Question and Answer data copied to Chatbot.txt.\n\n");
            break;
    }
}

/*  importUsers imports the contents of a file containing user contents
    @param User[] - struct containing the details of a user
    Pre-condition: The file to be imported must be related to user contents only, 
    must be in the correct format,
    must not have spaces in contents relating to userID, password, vaccine locations, vaccine dates, and vaccine brands,
    and must not have a blank area where a particular detail should be.
*/
void 
importUsers(Account User[])
{
    FILE *fUsers;
    char fileName[100];

    char tempUserID[100]; 
    char tempPassword[100];
    char tempName[100];
    char tempAddress[100];
    char tempContact[100];
    char tempSex[100];
    char tempLocation1[100];
    char tempDate1[100];
    char tempVaccine1[100];
    char tempLocation2[100];
    char tempDate2[100];
    char tempVaccine2[100];
    char tempLocation3[100];
    char tempDate3[100];
    char tempVaccine3[100];

    char nUserInputProceed;
    int nValid;

    int nValidID;

    int nStartingIndex;
    int i;

    int j;
    int k;

    nValid = FALSE;
    nValidID = TRUE;
    nStartingIndex = getEmptyUserIndex(User);
    i = nStartingIndex;

    displayDivider();

    printf("*WARNING*\n\n");

    printf("To limit errors in the reading of files, please avoid: \n");
    printf("- importing a file that is not in the correct format (as specified in the machine project specifications).\n");
    printf("- spaces in contents relating to userID, password, vaccine locations, vaccine dates, and vaccine brands.\n");
    printf("- leaving an area blank. If a particular detail has no content, please put N/A in place of it.\n\n");

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to import (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }
    }

    fUsers = fopen(fileName, "r");

    if (fUsers == NULL)
    {
        displayPrompt(FILE_OPEN_ERROR);
    }
    else
    { 
        while ((fscanf(fUsers, "%s %s ", tempUserID, tempPassword) == 2) && i < MAX_RECORDS) //loops as long as fscanf receives 2 arguments AND max records allowed is not reached
        {

            nValidID = TRUE;

            //NOTE: i starts from the first empty index
            fgets(tempName, sizeof(tempName), fUsers);
            tempName[strlen(tempName) - 1] = '\0'; //removes the trailing newline character
            
            fgets(tempAddress, sizeof(tempAddress), fUsers);
            tempAddress[strlen(tempAddress) - 1] = '\0'; //removes the trailing newline character

            fgets(tempContact, sizeof(tempContact), fUsers);
            tempContact[strlen(tempContact) - 1] = '\0'; //removes the trailing newline character

            fgets(tempSex, sizeof(tempSex), fUsers);
            tempSex[strlen(tempSex) - 1] = '\0'; //removes the trailing newline character

            fscanf(fUsers, "%s %s %s", tempLocation1, tempDate1, tempVaccine1);
            fscanf(fUsers, "%s %s %s", tempLocation2, tempDate2, tempVaccine2);
            fscanf(fUsers, "%s %s %s", tempLocation3, tempDate3, tempVaccine3);

            if (strlen(User[0].userID) == 0)
            {
                strcpy(User[i].userID, tempUserID);
                strcpy(User[i].password, tempPassword);
                strcpy(User[i].name, tempName);
                strcpy(User[i].address, tempAddress);
                strcpy(User[i].contact, tempContact);
                strcpy(User[i].sex, tempSex);
                strcpy(User[i].firstDoseLocation, tempLocation1);
                strcpy(User[i].firstDose, tempDate1);
                strcpy(User[i].firstVaccine, tempVaccine1);
                strcpy(User[i].secondDoseLocation, tempLocation2);
                strcpy(User[i].secondDose, tempDate2);
                strcpy(User[i].secondVaccine, tempVaccine2);
                strcpy(User[i].boosterDoseLocation, tempLocation3);
                strcpy(User[i].boosterDose, tempDate3);
                strcpy(User[i].boosterVaccine, tempVaccine3);
                ++i;
            }
            else
            {
                for (j = 0; j < MAX_RECORDS; j++)
                {
                    if (strcmp(tempUserID, User[j].userID) == 0) //checks if the userID being imported is already being used
                    {
                        nValidID = FALSE;
                    }
                }


                if (nValidID == FALSE) //checks if the userID in text file is the same as the userID reserved for the master admin
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("ERROR: User with userID %s in text file could not be imported because their ID is already being used.\n", tempUserID);
                }
                else
                {
                    displayDivider();
                    printf("\n");
                    printf("Import the following contents? (Y/N)\n");
                    printf("user id: %s\n", tempUserID);
                    printf("password: ");
                    /*prints the imported user's password as asterisks*/
                    for (k = 0; k < strlen(tempPassword); k++) 
                    {
                        printf("*");
                    }
                    printf("\n");

                    printf("name: %s\n", tempName);
                    printf("address: %s\n", tempAddress);
                    printf("contact number: %s\n", tempContact);
                    printf("sex: %s\n", tempSex);
                    printf("location 1 (first dose location): %s\n", tempLocation1);
                    printf("date 1 (first dose): %s\n", tempDate1);
                    printf("vaccine 1 (first dose vaccine): %s\n", tempVaccine1);
                    printf("location 2 (second dose location): %s\n", tempLocation2);
                    printf("date 2 (second dose): %s\n", tempDate2);
                    printf("vaccine 2 (second dose vaccine): %s\n", tempVaccine2);
                    printf("location 3 (booster dose location): %s\n", tempLocation3);
                    printf("date 3 (booster dose): %s\n", tempDate3);
                    printf("vaccine 3 (booster dose vaccine): %s\n\n", tempVaccine3);

                    printf("Input: ");
                    scanf(" %c", &nUserInputProceed);

                    if (nUserInputProceed == 'Y' || nUserInputProceed == 'y')
                    {
                        strcpy(User[i].userID, tempUserID);
                        strcpy(User[i].password, tempPassword);
                        strcpy(User[i].name, tempName);
                        strcpy(User[i].address, tempAddress);
                        strcpy(User[i].contact, tempContact);
                        strcpy(User[i].sex, tempSex);
                        strcpy(User[i].firstDoseLocation, tempLocation1);
                        strcpy(User[i].firstDose, tempDate1);
                        strcpy(User[i].firstVaccine, tempVaccine1);
                        strcpy(User[i].secondDoseLocation, tempLocation2);
                        strcpy(User[i].secondDose, tempDate2);
                        strcpy(User[i].secondVaccine, tempVaccine2);
                        strcpy(User[i].boosterDoseLocation, tempLocation3);
                        strcpy(User[i].boosterDose, tempDate3);
                        strcpy(User[i].boosterVaccine, tempVaccine3);
                        ++i;
                    }     
                }
                
            }
            
        }
        
        
        displayDivider();

        if (i == MAX_RECORDS)
        {
            
            printf("\n");
            printf("The maximum amount of records allowed has been reached.\n");
        }

        printf("Import successful.\n");
    }

    fclose(fUsers);
}

/*  importAppointments imports the contents of a file containing appointment contents
    @param User[] - struct containing the details of a user
    Pre-condition: The file to be imported must be related to appointment contents only, 
    must be in the correct format, 
    must not have spaces in contents relating to appID and userID,
    and must not have a blank area where a particular detail should be.
*/
void 
importAppointments(Account User[])
{
    FILE *fAppointments;
    char fileName[100];

    char tempAppID[100]; 
    char tempUserID[100]; 
    char tempName[100];
    char tempLocation[100];
    char tempVaccine[100];
    char tempDate[100];
    char tempTime[100];
    char tempDose[100];

    char cUserInputProceed;
    int nValid;

    int nValidID;

    int nStartingIndex;
    int i;
    int j;


    nValid = FALSE;
    nStartingIndex = getEmptyUserIndex(User);
    i = nStartingIndex;

    displayDivider();

    printf("*WARNING*\n\n");

    printf("To limit errors in the reading of files, please avoid: \n");
    printf("- importing a file that is not in the correct format (as specified in the machine project specifications).\n");
    printf("- spaces in contents relating to appID and userID.\n");
    printf("- leaving an area blank. If a particular detail has no content, please put N/A in place of it.\n\n");

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to import (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }
    }

    fAppointments = fopen(fileName, "r");

    if (fAppointments == NULL)
    {
        displayPrompt(FILE_OPEN_ERROR);
    }
    else
    {
        while ((fscanf(fAppointments, "%s %s ", tempAppID, tempUserID) == 2) && i < MAX_RECORDS) //loops as long as fscanf receives 2 arguments AND max records allowed is not reached
        {
            nValidID = TRUE;

            //NOTE: i starts from the first empty index
            fgets(tempName, sizeof(tempName), fAppointments);
            tempName[strlen(tempName) - 1] = '\0'; //removes the trailing newline character

            fgets(tempLocation, sizeof(tempLocation), fAppointments);
            tempLocation[strlen(tempLocation) - 1] = '\0'; //removes the trailing newline character

            fgets(tempVaccine, sizeof(tempVaccine), fAppointments);
            tempVaccine[strlen(tempVaccine) - 1] = '\0'; //removes the trailing newline character

            fgets(tempDate, sizeof(tempDate), fAppointments);
            tempDate[strlen(tempDate) - 1] = '\0'; //removes the trailing newline character

            fgets(tempTime, sizeof(tempTime), fAppointments);
            tempTime[strlen(tempTime) - 1] = '\0'; //removes the trailing newline character

            fgets(tempDose, sizeof(tempDose), fAppointments);

            if (getc(fAppointments) != EOF) //checks if the next line is EOF
            {
                tempDose[strlen(tempDose) - 1] = '\0'; //removes the trailing newline character
            }

            if (strlen(User[0].appID) == 0) //checks if there are already appointments loaded in the current run
            {
                strcpy(User[i].appID, tempAppID);
                strcpy(User[i].userID, tempUserID);
                strcpy(User[i].name, tempName);
                strcpy(User[i].location, tempLocation);
                strcpy(User[i].vaccine, tempVaccine);
                strcpy(User[i].date, tempDate);
                strcpy(User[i].time, tempTime);
                strcpy(User[i].dose, tempDose);
                ++i;
            }
            else
            {
                for (j = 0; j < MAX_RECORDS; j++)
                {
                    if (strcmp(tempUserID, User[j].userID) == 0) //checks if the userID being imported is already being used
                    {
                        nValidID = FALSE;
                    }

                    if (strcmp(tempAppID, User[j].appID) == 0) //checks if the appID being imported is already being used
                    {
                        nValidID = FALSE;
                    }
                }


                if (nValidID == FALSE) //checks if the userID in text file is the same as the userID reserved for the master admin
                {
                    displayPrompt(PROMPT_ERROR);
                    printf("ERROR: User with userID %s in text file could not be imported because their userID/appID is already being used.\n", tempUserID);
                }
                else
                {
                    displayDivider();
                    printf("\n");
                    printf("Import the following contents? (Y/N)\n");
                    printf("appointment id: %s\n", tempAppID);
                    printf("user id: %s\n", tempUserID);
                    printf("name: %s\n", tempName);
                    printf("location: %s\n", tempLocation);
                    printf("vaccine: %s\n", tempVaccine);
                    printf("date: %s\n", tempDate);
                    printf("time: %s\n", tempTime);
                    printf("dose: %s\n\n", tempDose);
                    
                    printf("Input: ");
                    scanf(" %c", &cUserInputProceed);

                    if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
                    {
                        strcpy(User[i].appID, tempAppID);
                        strcpy(User[i].userID, tempUserID);
                        strcpy(User[i].name, tempName);
                        strcpy(User[i].location, tempLocation);
                        strcpy(User[i].vaccine, tempVaccine);
                        strcpy(User[i].date, tempDate);
                        strcpy(User[i].time, tempTime);
                        strcpy(User[i].dose, tempDose);
                        ++i;
                    }    
                }
                
            }
        }
        
        
        displayDivider();

        if (i == MAX_RECORDS)
        { 
            printf("\n");
            printf("The maximum amount of records allowed has been reached.\n");
        }

        printf("Import successful.\n");
    }

    fclose(fAppointments);
}

/*  importChatbot imports the contents of a file containing chatbot question and answer contents
    @param Conversation[] - struct containing the details of a chatbot conversation
    Pre-condition: The file to be imported must be related to chatbot conversation questions and answers only, 
    must be in the correct format, 
    and must not have a blank area where a particular detail should be.
*/
void 
importChatbot(Chatbot Conversation[])
{
    FILE *fChatbot;
    char fileName[100];

    char tempQuestion[100]; //temporary variable that will hold the line containing the question
    char tempAnswer[100]; //temporary variable that will hold the line containing the answer

    char cUserInputProceed;
    int nValid;

    int nStartingIndex;
    int i;

    nValid = FALSE;
    nStartingIndex = getEmptyConversationIndex(Conversation);
    i = nStartingIndex;

    displayDivider();

    printf("*WARNING*\n\n");

    printf("To limit errors in the reading of files, please avoid: \n");
    printf("- importing a file that is not in the correct format (as specified in the machine project specifications).\n");
    printf("- leaving an area blank. If a particular detail has no content, please put N/A in place of it.\n\n");

    while (nValid == FALSE)
    {
        printf("Enter the name of the file you wish to import (must include the file extension): ");
        scanf("%s", fileName);

        if (strstr(fileName, ".txt") == 0) //checks if the entered file name contains the required file extension
        {
            displayPrompt(INVALID_INPUT);
        }
        else
        {
            nValid = TRUE;
        }
    }

    fChatbot = fopen(fileName, "r");

    if (fChatbot == NULL)
    {
        displayPrompt(FILE_OPEN_ERROR);
    }
    else
    {
        while (fgets(tempQuestion, sizeof(tempQuestion), fChatbot) && i < MAX_RECORDS) //loops until fgets reaches EOF and max records allowed is not reached
        {
            //NOTE: i starts from the first empty index
            tempQuestion[strlen(tempQuestion) - 1] = '\0'; //removes the trailing newline character

            fgets(tempAnswer, sizeof(tempAnswer), fChatbot);
            tempAnswer[strlen(tempAnswer) - 1] = '\0'; //removes the trailing newline character


            if (strlen(Conversation[0].question) == 0) // checks if there are currently no questions and answers
            {
                strcpy(Conversation[i].question, tempQuestion);
                strcpy(Conversation[i].answer, tempAnswer);
                ++i;
            }
            else
            {
                displayDivider();
                printf("\n");
                printf("Import the following contents? (Y/N)\n");
                printf("Question: %s\n", tempQuestion);
                printf("Answer: %s\n\n", tempAnswer);
             
                printf("Input: ");
                scanf(" %c", &cUserInputProceed);

                if (cUserInputProceed == 'Y' || cUserInputProceed == 'y')
                {
                    strcpy(Conversation[i].question, tempQuestion);
                    strcpy(Conversation[i].answer, tempAnswer);
                    ++i;
                }
            }
            
        }
        
        
        displayDivider();

        if (i == MAX_RECORDS)
        {
            
            printf("\n");
            printf("The maximum amount of records allowed has been reached.\n");
        }

        printf("Import successful.\n");
    }

    fclose(fChatbot);
}

/*  userRegistrationMENU is a menu function that lets the user interact with the User Registration Menu
    @param User[] - struct containing the details of a user
    @return TRUE if the program has been terminated. Otherwise, returns FALSE
*/
int 
userRegistrationMENU(Account User[])
{
    int nUserInput;
    int nUserAccount; //will contain the user's index if they log in successfully.
    int nProgramTerminated;
    int nIndex;

    nUserInput = 0;
    nProgramTerminated = FALSE;


    while (nUserInput != 3 && nProgramTerminated == FALSE)
    {
        displayPrompt(USER_REGISTRATION_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Register a new account
                nIndex = getEmptyUserIndex(User);

                if (nIndex != NOT_FOUND)
                {
                    userRegistration(User, nIndex);
                }
                else
                {
                    displayPrompt(MAX_RECORD_ERROR);
                }
                
                break;

            case 2: // View my account
                /*PROMPT USER TO LOG-IN*/
                nUserAccount = userLogin(User, 3);

                if (nUserAccount == LOGIN_FAILED)
                {
                    nProgramTerminated = terminateProgram(TRUE);
                }
                else if (nUserAccount != CANCEL_LOGIN)
                {
                    displayRegistration(User, nUserAccount);
                }
                break;

            case 3: //Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;        
        }
    }

    return nProgramTerminated;
}

/*  vaccineAppointmentMENU is a menu function that lets the user interact with the Vaccine Appointment Menu
    @param User[] - struct containing the details of a user
    @return TRUE if the program has been terminated. Otherwise, returns FALSE
*/
int 
vaccineAppointmentMENU(Account User[])
{
    int nUserInput;
    int nUserAccount; //will contain the user's index if the user logs in successfully
    int nProgramTerminated;

    nUserInput = 0;
    nProgramTerminated = FALSE;


    /*PROMPT USER TO LOG-IN*/
    nUserAccount = userLogin(User, 3);

    if (nUserAccount == LOGIN_FAILED)
    {
        nProgramTerminated = terminateProgram(TRUE);
    } 
    else if (nUserAccount != CANCEL_LOGIN)
    {
        while (nUserInput != 3)
        {
                     
            displayPrompt(VACCINE_APPOINTMENT_MENU);
            scanf("%d", &nUserInput);

            switch (nUserInput)
            {
                case 1: // Appointment Request
                    if (strlen(User[nUserAccount].appID) != 0)
                    {
                        printf("\nViewing your appointment request...\n\n");
                        displayAppointment(User, nUserAccount);
                    }
                    else
                    {   
                        appointmentRequest(User, nUserAccount);
                    }
                    break;

                case 2: // Manage Appointment
                    if (strlen(User[nUserAccount].appID) != 0)
                    {
                        manageAppointment(User, nUserAccount);
                    }
                    else
                    {
                        displayPrompt(PROMPT_ERROR);
                        printf("Please make an appointment request first.\n");
                    }
                    break;

                case 3: //Exit
                    break;

                default:
                    displayPrompt(INVALID_INPUT);
                    break;        
            }
        }
    }
    

    return nProgramTerminated;
}

/*  vaccineAppointmentMENU is a menu function that lets the user interact with the Vaccine Registration Menu
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
    @return TRUE if the program has been terminated. Otherwise, returns FALSE
*/
int 
vaccineRegistrationMENU(Account User[], 
                        Chatbot Conversation[])
{
    int nUserInput;
    int nProgramTerminated;

    nUserInput = 0;
    nProgramTerminated = FALSE;
    

    while (nUserInput != 4 && nProgramTerminated == FALSE)
    {
        displayPrompt(VACCINE_REGISTRATION_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // User Registration Menu
                nProgramTerminated = userRegistrationMENU(User);
                break;

            case 2: // Vaccine Appointment Menu
                nProgramTerminated = vaccineAppointmentMENU(User);
                break;

            case 3: // Chatbot
                chatbot(Conversation);
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;        
        }
    }

    return nProgramTerminated;
}

/*  userDataMENU is a menu function that lets the admin interact with the User sub-menu
    @param User[] - struct containing the details of a user
*/
void 
userDataMENU(Account User[])
{
    int nUserInput;

    nUserInput = 0;


    while (nUserInput != 5)
    {
        displayPrompt(USER_DATA_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Add New User
                addNewUser(User);
                break;

            case 2: // View All Users
                viewAllUsers(User);
                break;

            case 3: // Edit User Details
                editUserDetails(User);
                break;

            case 4: // Delete User
                deleteUser(User);
                break;

            case 5: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;        
        }
    }
}

/*  appointmentDataMENU is a menu function that lets the admin interact with the Appointment sub-menu
    @param User[] - struct containing the details of a user
*/
void 
appointmentDataMENU(Account User[])
{
    int nUserInput;

    nUserInput = 0;


    while (nUserInput != 5)
    {
        displayPrompt(APPOINTMENT_DATA_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Add New Appointment
                addNewAppointment(User);
                break;

            case 2: // View All Appointments
                viewAllAppointments(User);
                break;

            case 3: // Edit Appointment
                editAppointment(User);
                break;

            case 4: // Delete Appointment
                deleteAppointment(User);
                break;

            case 5: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;        
        }
    }
}

/*  adminDataMENU is a menu function that lets the admin interact with the Admin sub-menu
    @param User[] - struct containing the details of a user
*/
void 
adminDataMENU(Account User[])
{
    int nUserInput;

    nUserInput = 0;

    while (nUserInput != 4)
    {
        displayPrompt(ADMIN_DATA_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Add New Admin
                addNewAdmin(User);
                break;

            case 2: // View All Admins
                viewAllAdmins(User);
                break;

            case 3: // Remove Admin
                removeAdmin(User);
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;        
        }
    }
}

/*  chatbotDataMENU is a menu function that lets the admin interact with the Chatbot sub-menu
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
chatbotDataMENU(Chatbot Conversation[])
{
    int nUserInput;
    char nUserInputAnother;
    int nIndex;

    nUserInput = 0;
    nUserInputAnother = 'Y';


    while (nUserInput != 5)
    {
        displayPrompt(CHATBOT_DATA_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Add New Question and Answer
                while (nUserInputAnother == 'Y' || nUserInputAnother == 'y')
                {
                    nIndex = getEmptyConversationIndex(Conversation);

                    if (nIndex == NOT_FOUND)
                    {
                        displayPrompt(MAX_RECORD_ERROR);
                    }
                    else
                    {
                        displayDivider();
                        printf("NOTE: You do not have to add a question mark as the chatbot will do that already.\n");
                        printf("Also, this program will automatically convert your question input to lowercase, so please do not be alarmed.\n\n");

                        addNewConversation(Conversation, nIndex);
                        
                        printf("\n");

                        printf("The conversation was added successfully!\n");

                        printf("\n");

                        displayDivider();
                        printf("Do you want to add another question and answer? (Y/N)\n\n");

                        printf("Input: ");
                        scanf(" %c", &nUserInputAnother);
                    }            
                }
                break;
            
            case 2: // View All Questions and Answers
                viewAllConversations(Conversation);
                break;
            
            case 3: // Edit Questions and Answers
                editConversation(Conversation);
                break;

            case 4: // Delete Questions and Answers
                deleteConversation(Conversation);
                break;

            case 5: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }
    }
}   

/*  searchDataMENU is a menu function that lets the admin interact with the Search sub-menu 
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
searchDataMENU( Account User[], 
                Chatbot Conversation[])
{
    //This function allows the admin to search for a particular user, appointment, or chatbot conversation.
    //Really useful for if they forgot a user's ID, for example.

    int nUserInput;

    char userInputKey[100];

    int i;


    while (nUserInput != 4)
    {
        displayPrompt(SEARCH_DATA_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Search User
                displayDivider();
                printf("Enter the name of the user: ");
                scanf("%s", userInputKey);

                for (i = 0; i < MAX_RECORDS; i++)
                {
                    if (strstr(User[i].name, userInputKey) != 0)
                    {
                        printf("\n");
                        printf("User %s:\n", User[i].userID);
                        displayRegistration(User, i);
                    }
                }
                printf("\n");
                printf("All related users have been displayed. If none were shown, then there is no user registered with that name.\n");
                break;

            case 2: // Search Appointment
                displayDivider();
                printf("Enter the name of the user: ");
                scanf("%s", userInputKey);

                for (i = 0; i < MAX_RECORDS; i++)
                {
                    if (strstr(User[i].name, userInputKey) != 0)
                    {
                        printf("\n");
                        printf("Appointment %s:\n", User[i].appID);
                        displayAppointment(User, i);
                    }
                }
                printf("\n");
                printf("All related appointments have been displayed. If none were shown, then either the user does not exist / the user has not requested an appointment.\n");
                break;

            case 3: //Search Question and Answer
                displayDivider();
                printf("Enter a question keyword: ");
                scanf("%s", userInputKey);

                for (i = 0; i < MAX_RECORDS; i++)
                {
                    if (strstr(Conversation[i].question, userInputKey) != 0)
                    {
                        printf("\n");
                        printf("Conversation %s:\n", Conversation[i].conversationID);
                        displayConversation(Conversation, i);
                    }
                }
                printf("\n");
                printf("All related conversations have been displayed. If none were shown, then a question with that keyword does not exist.\n");
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }
    }
}

/*  exportDataMENU is a menu function that lets the admin interact with the Export sub-menu
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
exportDataMENU( Account User[], 
                Chatbot Conversation[])
{
    int nUserInput;
    
    while (nUserInput != 4)
    {
        displayPrompt(EXPORT_DATA_MENU);
        scanf("%d", &nUserInput);

        switch(nUserInput)
        {
            case 1: // Export Users
                exportUsers(User);
                break;

            case 2: // Export Appointments
                exportAppointments(User);
                break;

            case 3: // Export Chatbot Questions and Answers
                exportChatbot(Conversation);
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }
    }
}

/*  importDataMENU is a menu function that lets the admin interact with the Import sub-menu
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
*/
void 
importDataMENU( Account User[], 
                Chatbot Conversation[])
{
    int nUserInput;

    while (nUserInput != 4)
    {
        displayPrompt(IMPORT_DATA_MENU);
        scanf("%d", &nUserInput);

        switch(nUserInput)
        {
            case 1: // Import Users
                importUsers(User); //NOTE: This will not check whether there are entries already loaded in the current run because there is always 1 entry at all times (User 0)
                break;

            case 2: // Import Appointments
                importAppointments(User); //NOTE: This will not check whether there are entries already loaded in the current run because there is always 1 entry at all times (User 0)
                break;

            case 3: // Import Chatbot Questions and Answers
                importChatbot(Conversation); //Since the admin can delete all entries, this function checks if there are questions and answers already in the current run
                break;

            case 4: // Exit
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }
    }
    
}

/*  dataManagementMENU is a menu function that lets the admin interact with the Data Management Menu
    @param User[] - struct containing the details of a user
    @param Conversation[] - struct containing the details of a chatbot conversation
    Pre-condition: A user with isMember = "TRUE"  must exist.
*/
int 
dataManagementMENU( Account User[], 
                    Chatbot Conversation[])
{
    int nUserInput;
    int nUserAccount; //will contain the admin's index if they log in successfully
    int nProgramTerminated;

    nUserInput = 0;
    nProgramTerminated = FALSE;

    /*PROMPT USER TO LOG-IN*/
    nUserAccount = adminLogin(User, 3);

    if (nUserAccount == LOGIN_FAILED)
    {
        nProgramTerminated = terminateProgram(TRUE);
    } 
    else if (nUserAccount != CANCEL_LOGIN)
    {
        while (nUserInput != 8 && nProgramTerminated == FALSE)
        {
                     
            displayPrompt(DATA_MANAGEMENT_MENU);
            scanf("%d", &nUserInput);

            switch (nUserInput)
            {
                case 1: // Manage Users
                    userDataMENU(User);
                    exportAllData(User, Conversation, USER); //exports user data upon exit from user menu
                    break;

                case 2: // Manage Appointments
                    appointmentDataMENU(User);
                    exportAllData(User, Conversation, APPOINTMENT); //exports appointment data upon exit from appointment menu
                    break;
                
                case 3: // Manage Admins
                    adminDataMENU(User);
                    break;

                case 4: // Manage Chatbot
                    chatbotDataMENU(Conversation);
                    exportAllData(User, Conversation, CHATBOT); //exports chatbot data open exit from chatbot menu
                    break;
                
                case 5: // Search
                    searchDataMENU(User, Conversation);
                    break;

                case 6: // Export
                    exportDataMENU(User, Conversation);
                    break;
                
                case 7: // Import
                    importDataMENU(User, Conversation);
                    break;

                case 8: // Exit Menu
                    exportAllData(User, Conversation, ALL);
                    break;

                default:
                    displayPrompt(INVALID_INPUT);
                    break;        
            }
        }
    }

    return nProgramTerminated;
}

/*  main function
*/
int 
main()
{
    SetConsoleOutputCP(CP_UTF8); //this is a function in windows.h that translates the written character values into the images displayed on the console

    Account User[MAX_RECORDS] = {0}; 
    Chatbot Conversation[MAX_RECORDS] = {0};

    int nProgramTerminated;
    int nUserInput;

    initializeMasterAdmin(User); //initializes the master admin
    initializeChatbot(Conversation); //gives the chatbot simple conversations to start with

    nProgramTerminated = FALSE;


    while (nProgramTerminated == FALSE)
    {
        displayPrompt(MAIN_MENU);
        scanf("%d", &nUserInput);

        switch (nUserInput)
        {
            case 1: // Vaccine Registration Menu
                nProgramTerminated = vaccineRegistrationMENU(User, Conversation);
                break;

            case 2: //Data Management Menu
                nProgramTerminated = dataManagementMENU(User, Conversation);
                break;

            default:
                displayPrompt(INVALID_INPUT);
                break;
        }
    }   

    displayPrompt(PROMPT_TERMINATING_PROGRAM);
    exportAllData(User, Conversation, ALL); //exports all of the data into their respective files when the program is terminated

    return 0;
}
