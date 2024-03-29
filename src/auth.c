#include <termios.h>
#include "header.h"

const char *USERS = "./data/users.txt";

void saveUsertoFile(FILE *ptr, struct User u)
{
    fprintf(ptr,  "%d %s %s \n",
	    u.id,
        u.name,
	    u.password);
}

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

void createlogin(struct User u)
{
    int option=0;
    FILE *fp = fopen(USERS, "a+");
    struct User userChecker;

    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter your name:");
    scanf("%s", u.name);

    while (fscanf(fp, "%s", userChecker.name) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            printf("\nThis name is already used\n");
            printf("Press 1 to continue\n");
            scanf("%d", &option);
            goto loginuse;
        }
    }
        printf("\nEnter your password:");
        scanf("%s", u.password);
    u.id =3;

    saveUsertoFile(fp, u);
        loginuse:
    fclose(fp);

}

