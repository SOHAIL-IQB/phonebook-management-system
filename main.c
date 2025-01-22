#include<stdio.h>
#include <termios.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

struct contact {
    long long int ph;
    char name[20], add[50], email[30];
} list;

void clear_screen() {
    system("clear");
}

int main() {
    char query[20], name[20];
    FILE *fp, *ft;
    int i, n, ch, l, found;

main:
    clear_screen(); /* *****Main menu ********  */
    printf("\n\t ** Welcome to Phonebook Management System **");
    printf("\n\n\n\t\t\tMAIN MENU\n\t\t\t=========\n");
    printf("[1] Add a new Contact\n");
    printf("[2] View all Contact\n");
    printf("[3] Search for Contact\n");
    printf("[4] Edit a Contact\n");
    printf("[5] Delete a Contact\n");
    printf("[0] Exit\n");
    printf("\nEnter the choice : ");
    scanf("%d", &ch);
    switch (ch) {
    case 0:
        printf("\n\n\t\tAre you sure you want to exit?");
        break;

    case 1: /* ********Add new contacts*****  */
        clear_screen();
        fp = fopen("contact.dll", "a");
        for (;;) {
            fflush(stdin);
            printf("To exit enter blank space in the name input\nEnter Name : ");
            scanf("%[^\n]", list.name);
            if (strcasecmp(list.name, "") == 0 || strcasecmp(list.name, " ") == 0)
                break;
            fflush(stdin);
            printf("Enter Phone No. : ");
            scanf("%lld", &list.ph);
            fflush(stdin);
            printf("Enter Address : ");
            scanf("%[^\n]", list.add);
            fflush(stdin);
            printf("Enter Email Address : ");
            scanf("%s", list.email);
            printf("\n");

            fwrite(&list, sizeof(list), 1, fp);
            printf("**Contact is Added**\n\n");
        }
        fclose(fp);
        break;

    case 2: /* ********list of contacts********  */
        clear_screen();
        printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n");
        for (i = 97; i <= 122; i = i + 1) {
            fp = fopen("contact.dll", "r");
            fflush(stdin);
            found = 0;
            while (fread(&list, sizeof(list), 1, fp) == 1) {
                if (list.name[0] == i || list.name[0] == i - 32) {
                    printf("\nName\t: %s\nPhone\t: %lld\nAddress\t: %s\nEmail\t: %s\n\n", list.name, list.ph, list.add, list.email);
                    found++;
                }
            }

            fclose(fp);
        }
        break;

    case 3: /* ******search contacts*******  */
        clear_screen();
        do {
            found = 0;
            printf("\n\tCONTACT SEARCH\n\t==============\n");
            printf("Name of contact to search (Identical) : ");
            fflush(stdin);
            scanf("%[^\n]", query);
            l = strlen(query);
            fp = fopen("contact.dll", "r");
            clear_screen();
            printf("\nSearch result for '%s' \n=================================\n", query);
            while (fread(&list, sizeof(list), 1, fp) == 1) {
                for (i = 0; i <= l; i++)
                    name[i] = list.name[i];
                name[l] = '\0';
                if (strcasecmp(name, query) == 0) {
                    printf("\nName\t: %s\nPhone\t: %lld\nAddress\t: %s\nEmail\t: %s\n", list.name, list.ph, list.add, list.email);
                    found++;
                }
            }
            if (found == 0)
                printf("\nNo match found!");
            else
                printf("\n%d match(s) found!", found);
            fclose(fp);
            printf("\n\nWant to search again?\n[1] Yes\t\t[0] No\n");
            scanf("%d", &ch);
        } while (ch == 1);
        break;

    case 4: /* ********edit contacts*********/
        clear_screen();
        fp = fopen("contact.dll", "r");
        ft = fopen("temp.dat", "w");
        fflush(stdin);
        printf("Edit contact\n==============\n");
        printf("Enter the name of Contact you want to Edit (Identical) : ");
        scanf("%[^\n]", name);
        while (fread(&list, sizeof(list), 1, fp) == 1) {
            if (strcasecmp(name, list.name) != 0)
                fwrite(&list, sizeof(list), 1, ft);
        }
        fflush(stdin);
        printf("\n\nEditing '%s'\n\n", name);
        printf("Enter Name : ");
        scanf("%[^\n]", list.name);
        fflush(stdin);
        printf("Enter Phone : ");
        scanf("%lld", &list.ph);
        fflush(stdin);
        printf("Enter Address : ");
        scanf("%[^\n]", list.add);
        fflush(stdin);
        printf("Enter Email Address : ");
        scanf("%s", list.email);
        fwrite(&list, sizeof(list), 1, ft);
        fclose(fp);
        fclose(ft);
        remove("contact.dll");
        rename("temp.dat", "contact.dll");
        printf("\n**Contact is Edited**\n");
        break;

    case 5: /* *******delete contacts*******/
        clear_screen();
        fflush(stdin);
        printf("\n\n\tDELETE A CONTACT\n\t================\n");
        printf("Enter the Name of the Contact you want to Delete (Identical) : ");
        scanf("%[^\n]", name);
        fp = fopen("contact.dll", "r");
        ft = fopen("temp.dat", "w");
        while (fread(&list, sizeof(list), 1, fp) != 0)
            if (strcasecmp(name, list.name) != 0)
                fwrite(&list, sizeof(list), 1, ft);
        fclose(fp);
        fclose(ft);
        remove("contact.dll");
        rename("temp.dat", "contact.dll");
        printf("\n***Contact is Deleted***\n");
        break;

    default:
        printf("Invalid choice");
        break;
    }

    printf("\nEnter the Choice:\n[1] Main Menu\t\t[0] Exit\n");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
        goto main;

    case 0:
        break;

    default:
        printf("Invalid choice");
        break;
    }
    return 0;
}