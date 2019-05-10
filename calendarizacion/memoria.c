#ifndef MEMORIA_C
#define MEMORIA_C
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
typedef struct bloque bloque;
void pushM(bloque **head, int id, int tama, int duracion, int *tamtotal);
void popM(bloque **head, int pos,int * tamtotal);
void pushMpos(bloque **head, int id, int tama, int duracion, int pos);
void print_listM(bloque **head);
void restaDuracion(bloque**head);
bloque* remove_back(bloque** head);
bloque* remove_front(bloque** head);
bloque* lastM(bloque**head);
bool remove_any(bloque** head);
void limpiaId(bloque **head);

typedef struct bloque
{
    int id;
    int tama;
    int duracion;
    struct bloque *next;
} bloque;

static int cantMem = 0;
void pushM(bloque **head, int id, int tama, int duracion, int *tamtotal)
{
    bloque *current = *head;
    bloque *temp = (bloque *)malloc(sizeof(bloque));
    temp->id = id;
    temp->tama = tama;
    temp->duracion = duracion;
    temp->next = NULL;

    if (current == NULL)

        {
            bloque *temp2 = (bloque *)malloc(sizeof(bloque));
            temp2->id = -1;
            temp2->tama = *tamtotal - temp->tama;
            *tamtotal -= temp->tama;
            temp2->duracion = 0;
            temp->next = temp2;
            temp2->next = NULL;
            *head = temp;
            cantMem += 2;
        }
    else
    {
        bloque *aux = NULL;
        while (current->next != NULL)
        {
            aux = current;
            current = current->next;
        }

        aux->next = temp;
        free(current);
        bloque *temp2 = (bloque *)malloc(sizeof(bloque));
        temp2->id = -1;
        temp2->tama = *tamtotal - temp->tama;
        *tamtotal -= temp->tama;
        temp2->duracion = 0;
        temp->next = temp2;
        temp2->next = NULL;
        cantMem++;
    }
}
void popM(bloque **head, int pos, int * tamtotal)
{
    if ((*head) == NULL)
    {
        return;
    }
    bloque *t = NULL;
    bloque* t2 = NULL;
    bloque * t3= NULL;
    int cont = 0;
    t = (*head);
    while (t->next != NULL && cont <= pos)
    {

        if (cont == pos)
        {
            t->id = 0;
            t->duracion = 0;
            //*tamtotal-=t->tama;
            if (t->next->duracion == 0 && t2 != NULL)
            {

                t->next->tama += t->tama;
                t2->next = t->next;
                t->next = NULL;
               // *tamtotal-=t->tama;
                free(t);
                cantMem--;
                if(t3 != NULL){
                    t2 = t2->next;
                    t3 = t3->next;
                    if(t3->duracion==0){
                        t3->tama+=t2->tama;
                        t3->next=t2->next;
                    //*tamtotal -= t2->tama;
                        t2->next = NULL;
                        free(t2);
                        return;
                    }
                }
                return;
            }
            if (t2 != NULL)
            {
                if (t2->duracion == 0)
                {
                    t2->tama += t->tama;
                    t2->next = t->next;
                 //   *tamtotal -= t->tama;
                    t->next = NULL;
                    free(t);
                    cantMem--;
                    return;
                }
            }
        }
        t2 = t;
        t = t->next;
        cont++;
    }
}
void pushMpos(bloque **head, int id, int tama, int duracion, int pos)
{
    if ((*head) == NULL)
    {
        return;
    }
    bloque *t, *t2;
    t = (*head);
    int cont = 0;
    if(pos==0 && t->tama >= tama){
       bloque *nuevo = (bloque *)malloc(sizeof(bloque));
            nuevo->id = id;
            nuevo->tama = tama;
            nuevo->duracion = duracion;
            bloque *temp = (bloque *)malloc(sizeof(bloque));
            temp->id = -1;
            temp->tama = t->tama - tama;
            temp->duracion = -1;
            (*head)=nuevo;
            temp->next = t->next;
            nuevo->next = temp;
            t->next=NULL;
            free(t);  
            return;
    }
    while (t->next != NULL && cont <= pos)
    {
        if (t->tama >= tama)
        {
            bloque *nuevo = (bloque *)malloc(sizeof(bloque));
            nuevo->id = id;
            nuevo->tama = tama;
            nuevo->duracion = duracion;

            if (t->tama - tama == 0)
            {
                t2->next = nuevo;
                nuevo->next = t->next;
                t->next = NULL;
                free(t);
                return;
            }
            else
            {
                bloque *temp = (bloque *)malloc(sizeof(bloque));
                temp->id = -1;
                temp->tama = t->tama - tama;
                temp->duracion = -1;
                nuevo->next = temp;
                t2->next = nuevo;
                temp->next = t->next;
                t->next = NULL;
                free(t);
                return;
            }
        }
        else
        {
            return;
        }
        t2 = t;
        t = t->next;
        cont++;
    }
}
void print_listM(bloque **head)
{
    bloque *current = *head;

 //printf("\n\n**********************\n\n");
    while (current != NULL)
    {
       
        printf("%d, %d, %d\n", current->id, current->duracion,
               current->tama);
        current = current->next;
    }
          //printf("\n\n**********************\n\n");
}
int isEmptyM(bloque **head)
{
    return ((*head) == NULL ? 0 : 1);
}

bool verificaCero(bloque** head){
    bloque* current=(*head);
     while(current->next !=NULL){
         if(current->duracion==0 && current->id != -1)
            return true;
        current = current->next;
     }
       

        return false;
}

int retornaPos_En_Cero(bloque** head){
 bloque* current=(*head);
 int cont=0;
     while(current->next !=NULL){
         if(current->duracion==0 && current->id != -1)
            return cont;
        current = current->next;
        cont++;
     }
     return-1;
}
 bloque* lastM(bloque**head){
     bloque* current=(*head);
     while(current->next !=NULL)
        current = current->next;

        return current;
}




bloque* remove_front(bloque** head)
{
    if((*head) == NULL)
        return NULL;
    bloque *front = (*head);
    (*head) = (*head)->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == (*head))
        head = NULL;
    free(front);
    return (*head);
}


bloque* remove_back(bloque** head)
{
    if((*head) == NULL)
        return NULL;
 
    bloque *cursor = (*head);
    bloque *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if(back != NULL)
        back->next = NULL;
 
    /* if this is the last node in the list*/
    if(cursor == (*head))
       (*head) = NULL;
 
    free(cursor);
 
    return (*head);
}

void restaDuracion(bloque**head){
    bloque* current= (*head);
    while(current != NULL ){
        if(current->duracion > 0)
        current->duracion--;
        current=current->next;
    }
}
bool buscaEspacio(bloque**head, int id, int duracion, int tam){
    int pos=0;
    bloque * current = (*head);
    while(current->next != NULL ){
        if(tam <= current->tama){
            pushMpos(head,id,tam,duracion,pos);
            return true;
        }
        pos++;
        current=current->next;
    }
    return false;
}

void limpiaId(bloque **head){

     bloque * current = (*head);
    while(current != NULL ){
        if(current->id != 0 && current->duracion==0 ){
            current->id=0;
        }
        current->next;
    }

}
#endif