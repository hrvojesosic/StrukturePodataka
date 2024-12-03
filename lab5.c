#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct StackEl* Position;
typedef struct StackEl{
    //data
    double val;
    //link
    Position next;



}StackEl;

Position create_head();
Position create_element(double valu);
int push(Position head,Position element);
void pop(Position head);
int ReadFromFile(Position head);
void stack_subtraction(Position head);
void stack_multiplication(Position head);
void stack_addition(Position head);
void stack_division(Position head);


int main(){
    	Position P=create_head();
        P->val=0.0;
        ReadFromFile(P);

        printf("Rezultat je: %.2f",P->next->val);


    return 0;
}
Position create_head(){
    Position new_head=NULL;
    new_head=(Position)malloc(sizeof(StackEl));
    
 
    

        return new_head;
}

Position create_element(double valu)
{
    Position newEl=NULL;
    newEl=(Position)malloc(sizeof(StackEl));
    if(newEl==NULL){
        printf("error allocating memory");
        return NULL;
    }
    newEl->val=valu;



    return newEl;
}
int push(Position head,Position element){
 
 Position tmp=head->next;

    head->next=element;
    element->next=tmp;

    return 0;
    
}
void pop(Position head){
    if(head->next==NULL){
        printf("prazan stog");

    }
    Position temp=head->next;

    head->next=temp->next;
    free(temp);
    return;
}
int ReadFromFile(Position head){


    int numBytes=0;
    
    char buffer[MAX_LINE]="";
    FILE* filep=fopen("postfix.txt","r");
    if(filep==NULL){
        printf("Error opening file.\n");
        return -1;
    }
    
    while(fscanf(filep,"%s",buffer)!=EOF){
        //provjera je li prvi simbol operator
        switch(buffer[0]){
            case '+':
                stack_addition(head);
                break;
            case '-':
                stack_subtraction(head);
                break;
            case '*':
                stack_multiplication(head);
                break;
            case '/':
                stack_division(head);
                break;
            default:
            if(buffer[0]<='9'&&buffer[0]>='0'||buffer[0]=='-'){
                double value=atof(buffer);
                Position new_element=create_element(value);
                if(new_element==NULL){
                    printf("Error memory allocation.\n");
                    return -1;
                }
                push(head,new_element); //pushamo cili string kao broj (moze bit bilo koi broj)


            }else{
                printf("Error taking symbol from file.");
                return -1;
            }
            

            
                

        }
    }

    
return 0;
}
void stack_subtraction(Position head){
    Position prvi,drugi;
    double rezultat=0;
    double prviVal=0;
    double drugiVal=0;

    if(head->next==NULL){
        printf("Prazan stog");
        return;
    }
    prvi=head->next;
    prviVal=prvi->val;

    if(prvi->next==NULL){
        rezultat=0-prviVal;
        
    }
    else{
        drugi=prvi->next;
        drugiVal=drugi->val;

        rezultat=drugiVal-prviVal;

    }
    pop(head);
    pop(head); //skinili prvog i drugog

    Position newEl=create_element(rezultat);
    push(head,newEl);
    return;
}
void stack_multiplication(Position head){

       Position prvi,drugi;
    int rezultat=0;
    int prviVal=0;
    int drugiVal=0;

    if(head->next==NULL){
        printf("Prazan stog");
        return;
    }
    prvi=head->next;
    prviVal=prvi->val;

    if(prvi->next==NULL){
        rezultat=0*prviVal;
        
    }
    else{
        drugi=prvi->next;
        drugiVal=drugi->val;

        rezultat=drugiVal*prviVal;

    }
    pop(head);
    pop(head); //skinili prvog i drugog

    Position newEl=create_element(rezultat);
    push(head,newEl);
    return;
}
void stack_addition(Position head){
       Position prvi,drugi;
        double rezultat=0.0;
    double prviVal=0.0;
    double drugiVal=0.0;

    if(head->next==NULL){
        printf("Prazan stog");
        return;
    }
    prvi=head->next;
    prviVal=prvi->val;

    if(prvi->next==NULL){
        rezultat=prviVal;
        
    }
    else{
        drugi=prvi->next;
        drugiVal=drugi->val;

        rezultat=drugiVal+prviVal;

    }
    pop(head);
    pop(head); //skinili prvog i drugog

    Position newEl=create_element(rezultat);
    push(head,newEl);
    return;
}
void stack_division(Position head){
       Position prvi,drugi;
    double rezultat=0;
    double prviVal=0;
    double drugiVal=0;

    if(head->next==NULL){
        printf("Prazan stog");
        return;
    }
    prvi=head->next;
    prviVal=prvi->val;

    if(prvi->next==NULL){
        printf("Greška: dijeljenje s nulom.");
        return;
        
    }
    else{
        drugi=prvi->next;
        drugiVal=drugi->val;

        rezultat=drugiVal/prviVal;

    }
    pop(head);
    pop(head); //skinili prvog i drugog

    Position newEl=create_element(rezultat);
    push(head,newEl);
    return;
}