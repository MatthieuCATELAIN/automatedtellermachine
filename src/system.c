#include "header.h"

const char *RECORDS = "./data/records.txt";
const char *NEWRECORDS = "./data/new_records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                &r->id,
		        &r->userId,
		        name,
                &r->accountNbr,
                &r->deposit.month,
                &r->deposit.day,
                &r->deposit.year,
                r->country,
                &r->phone,
                &r->amount,
                r->accountType) != EOF;
}
int getAccountFromFile2(FILE *ptr, struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                &r->id,
		        &r->userId,
		        r->name,
                &r->accountNbr,
                &r->deposit.month,
                &r->deposit.day,
                &r->deposit.year,
                r->country,
                &r->phone,
                &r->amount,
                r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr,  "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
	    u.id,
        u.id,
	    u.name,
        r.accountNbr,
        r.deposit.month,
        r.deposit.day,
        r.deposit.year,
        r.country,            
        r.phone,
        r.amount,
        r.accountType);
}

void saveAccountToFile2(FILE *ptr, struct Record r)
{
    fprintf(ptr,  "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
	    r.id,
        r.id,
	    r.name,
        r.accountNbr,
        r.deposit.month,
        r.deposit.day,
        r.deposit.year,
        r.country,            
        r.phone,
        r.amount,
        r.accountType);
}

void success(struct User u)
{
    int option;
    printf("\n\nEnd...\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    system("clear");
    noAccount:
    printf("\t\t\t===== New record =====\n");
    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;
    struct Record cr;
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        } 
        }
    fclose(pf);
    success(u);
}


void checkOneAccount(struct User u)
{
    char userName[100];
    struct Record r;
    struct Record cr;
    FILE *pf = fopen(RECORDS, "r");
    double interest;
    int option=0;
    system("clear");
    printf("Enter your account number:");
    scanf("%d", &cr.accountNbr);
    system("clear");
    printf("\t\t====== Account number %d from user %s =====\n\n", cr.accountNbr, u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            option = 1;
            printf("_____________________\n");
            printf("\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            if (strcmp(r.accountType, "current")==0) 
            {
                printf("\nYou will not get interests because the account is of type current\n");
            } else if (strcmp(r.accountType, "saving")==0) 
            {
                printf("\nYou will get %.2f as interest on day %d of every month\n", (r.amount*0.07/12), r.deposit.day);
            } else if (strcmp(r.accountType, "fixed01")==0) 
            {
                printf("\nYou will get %.2f as interest on %d/%d/%d\n", (r.amount*0.04), r.deposit.day, r.deposit.month, r.deposit.year+1);
            } else if (strcmp(r.accountType, "fixed02")==0) 
            {
                printf("\nYou will get %.2f as interest on %d/%d/%d\n", (r.amount*0.05*2), r.deposit.day, r.deposit.month, r.deposit.year+1);
            } else if (strcmp(r.accountType, "fixed03")==0) 
            {
                printf("\nYou will get %.2f as interest on %d/%d/%d\n", (r.amount*0.08*3),  r.deposit.day, r.deposit.month, r.deposit.year+1);
            }
        }
    }
    if (option == 0)
    {
        printf("This account does not exist\n");
    }
    fclose(pf);
    success(u);
}


void updateAccount(struct User u)
{
    char userName[100];
    struct Record r;
    struct Record cr;
    struct Record temp;
    int option=0;
    int flag=0;
    FILE *pf = fopen(RECORDS, "r");
      FILE *new= fopen ("./data/new_records.txt", "a+");
    system("clear");
    printf("Enter your account number:");
    scanf("%d", &cr.accountNbr);
    system("clear");
    
    printf("\t\t====== Account number %d from user %s =====\n\n", cr.accountNbr, u.name);
    printf("What do you want to change?\n\n");
    printf("\n\t\t[1]- Phone number\n");
    printf("\n\t\t[2]- Country\n");

    scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nEnter your new phone number:");
            scanf("%d", &cr.phone);
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
    saveAccountToFile2(new, r);
        }
        if (cr.accountNbr == r.accountNbr){
            flag = 1;
    r.phone = cr.phone;
    saveAccountToFile2(new, r);
        }
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
        break;
        case 2:
            printf("\nEnter your new country location:");
            scanf("%s", cr.country);
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
    saveAccountToFile2(new, r);
        }
        if (cr.accountNbr == r.accountNbr){
            flag = 1;
    strcpy(r.country, cr.country);
    saveAccountToFile2(new, r);
        }
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
        break;
        default:
            printf("Insert a valid operation!\n");
        }
    if (flag == 0)
    {
printf("This account does not exist\n");
    }
    endupdate:
    success(u);
}


void suppressline(struct User u)
{
  FILE *pf= fopen (RECORDS, "r");
  FILE *new= fopen ("./data/new_records.txt", "a+");
struct Record r;
struct Record cr;
int flag=0;
char userName[100];
    system("clear");
printf("Enter the account number you want to delete :");
    scanf("%d", &cr.accountNbr);
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
            flag = 0;
    saveAccountToFile2(new, r);
        }
        if ( cr.accountNbr == r.accountNbr)
        {
            flag = 1;
        }
}
if (flag == 0)
{
    printf("\nThis account does not exist\n");
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
success(u);
}


void transfer(struct User u)
{
  FILE *pf= fopen (RECORDS, "r");
  FILE *new= fopen ("./data/new_records.txt", "a+");
struct Record r;
struct Record cr;
char userName[100];
    system("clear");
printf("Enter the account number you want to transfer :");
    scanf("%d", &cr.accountNbr);
    printf("Enter the name of the new owner :");
        scanf("%s", cr.name);
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
    saveAccountToFile2(new, r);
        }
        if (cr.accountNbr == r.accountNbr) {
    strcpy(r.name, cr.name);
    saveAccountToFile2(new, r);       
        }
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
success(u);
}

void transaction(struct User u)
{
    char userName[100];
    char variable[20];
    struct Record r;
    struct Record cr;
    struct Record temp;
    FILE *pf = fopen(RECORDS, "r");
    FILE *new= fopen ("./data/new_records.txt", "a+");
    int option=0;
    double somme=0;
    system("clear");
    printf("Enter your account number:");
    scanf("%d", &cr.accountNbr);
/*     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr == r.accountNbr)
        {   
            if ((r.accountType == "fixed01") || (r.accountType == "fixed02") || (r.accountType == "fixed03"))
            {
            printf("Impossible to make a transaction with this type of account");
                goto quitrans;
        }
        }
    } */
    system("clear");
    
    printf("\t\t====== Account number %d from user %s =====\n\n", cr.accountNbr, u.name);

    printf("Select the operation?\n\n");
    printf("\n\t\t[1]- Deposit\n");
    printf("\n\t\t[2]- Withdraw\n");

    scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nEnter the amount:");
            scanf("%lf", &somme);
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
    saveAccountToFile2(new, r);
        }
        if (cr.accountNbr == r.accountNbr){

        if ((strcmp(r.accountType, "current")== 0) || (strcmp(r.accountType, "saving")== 0))  {
        r.amount = r.amount + somme;
    saveAccountToFile2(new, r);
        } else {
     printf("Impossible to withdraw this type account");
            saveAccountToFile2(new, r);
        }
        }
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
        break;
        case 2:
            printf("\nEnter the amount:");
            scanf("%lf", &somme);
/*      while (getAccountFromFile2(pf, &r)) {
        if (cr.accountNbr == r.accountNbr){
            if  (somme >= r.amount)
            {
                printf("\nVous ne disposez pas des fonds nécessaires:");
                goto endwith;
            } 
     }
     }  */
     while (getAccountFromFile2(pf, &r))
    {
        if ( cr.accountNbr != r.accountNbr)
        {
    saveAccountToFile2(new, r);
        }
        if (cr.accountNbr == r.accountNbr){
            if (somme < r.amount){
    r.amount = r.amount - somme;
    saveAccountToFile2(new, r);
    } else {
        printf("Impossible to withdraw this amount");
            saveAccountToFile2(new, r);
    }

        }
}
  fclose (pf);
  fclose (new);
  remove("./data/records.txt");
  rename(NEWRECORDS,RECORDS);
  endwith:
        break;
        default:
            printf("Insert a valid operation!\n");
        }

    if (option == 0)
    {
        printf("This account does not exist\n");
    }
    quitrans:
    success(u);
}




