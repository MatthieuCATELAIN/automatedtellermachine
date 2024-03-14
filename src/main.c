#include "header.h"

void mainMenu(struct User u)
{
    int option;

    system("clear");

    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check account\n");
    printf("\n\t\t[4]- Check list of owneds accounts\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
            reset:
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // OK
        updateAccount(u);
        break;
    case 3:
        // OK
        checkOneAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // OK
        transaction(u);
        break;
    case 6:
        // OK
        suppressline(u);
        break;
    case 7:
        // OK
        transfer(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
        goto reset;
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
        resetlog:
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");

    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // OK
            createlogin(*u);
            goto resetlog;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
            goto resetlog;
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
