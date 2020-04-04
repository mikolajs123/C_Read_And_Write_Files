//
//  main.c
//  Temp_C
//
//  Created by Mikołaj Semeniuk on 03/04/2020.
//  Copyright © 2020 Mikołaj Semeniuk. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct Client
{
    int client_number;
    double debt;
    struct Client *next;
};

void append(struct Client **head, int client_number, double debt)
{
    struct Client *temp = (struct Client*) malloc(sizeof(struct Client));
    struct Client *tail = *head;
    temp->client_number = client_number;
    temp->debt = debt;
    temp->next = NULL;
    
    if (*head == NULL)
    {
       *head = temp;
       return;
    }
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = temp;
    return;
}

int how_many_clients_in_debt (struct Client *p)
{
    int result = 0;
    while (p != NULL)
    {
        if (p->debt > 0)
            result++;
        p = p->next;
    }
    return result;
}

double how_high_is_debt (struct Client *p)
{
    double result = 0;
    while (p != NULL)
    {
        result += p->debt;
        p = p->next;
    }
    return result;
}

void display (struct Client *p)
{
    while (p != NULL) {
        printf("client_number: %d\n", p->client_number);
        printf("debt: %f\n", p->debt);
        p = p->next;
    }
    return;
}

void read_and_save_to_linked_list (FILE *fr, struct Client **list, char a[])
{
    fr = fopen(a, "r");
    
    char *client_number = "", *debt = "";
    bool change = true;
    int a = 0;
    double b = 0.0;
    char str = fgetc(fr);
    
    while (str != EOF) {
        if (change)
        {
            asprintf(&client_number, "%s%c", client_number, str);
        }
        else
        {
            asprintf(&debt, "%s%c", client_number, str);
        }
        if (str == ' ' || str == '\n') {
            change = !change;
            if (change) // debt
            {
                b = atof(debt);
            }
            else // client number
            {
                a = atoi(client_number);
            }
        }
        if (a && b)
        {
            append(list, a, b);
            size_t len1 = strlen(client_number), len2 = strlen(debt);
            memset(client_number, 0, len1);
            memset(debt, 0, len2);
            a = 0;
            b = 0;
        }
        str = fgetc(fr);
    }
    return;
}

void write_and_save_to_file(FILE *fw, struct Client **list, char a[])
{
    fw = fopen (a,"w");
    
    fprintf (fw, "How many customers in debt: %d\nHow much is debt: %f", how_many_clients_in_debt(*list), how_high_is_debt(*list));

    fclose (fw);
    return;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    struct Client *list = NULL;
    FILE *fr = NULL, *fw = NULL;
    char input[] = "/Users/mikolajsemeniuk/Desktop/klienci.txt", output[] = "/Users/mikolajsemeniuk/Desktop/wynik.txt";
    read_and_save_to_linked_list(fr, &list, input);
    display(list);
    write_and_save_to_file(fw, &list, output);
    return 0;
}
