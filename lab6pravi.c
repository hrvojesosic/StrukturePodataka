#define _CRT_SECURE_NO_WARNINGS
#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _article* ArticlePosition;
typedef struct _article 
{
    char name[50];
    int quantity;
    double price;
    ArticlePosition next;
}Article;

typedef struct 
{
    int year, month, day;
}Date;

typedef struct _receipt* ReceiptPosition;
typedef struct _receipt 
{
    Date receipt_date;
    ArticlePosition head_A;
    ReceiptPosition next;
}Receipt;
int ReadFromMainReceiptFile(ReceiptPosition head_R);
int AddReceiptSorted(ReceiptPosition head_R, char file_name[]);
int AddArticleSorted(ArticlePosition head_A, char name[], int quantity, double price);
int Request(ReceiptPosition head_R);

int main(){
    ReceiptPosition head=(ReceiptPosition)malloc(sizeof(Receipt));
    head->head_A=NULL;
    head->next=NULL;
    if(ReadFromMainReceiptFile(head)){
        printf("Reading from main file failed.");
        return ERROR;
    }
    if(Request(head)){
        printf("Request failed\n");
        return ERROR;
    }
    
    return 0;
}

int ReadFromMainReceiptFile(ReceiptPosition head_R){
    char file_name[50];
    FILE* fp=NULL;
    fp=fopen("racuni.txt","r");

    if(fp==NULL){
        return EXIT_FAILURE;
    }
    while(fscanf(fp,"%s",file_name)==1){

        if(AddReceiptSorted(head_R,file_name)){
            printf("Error in adding receipt to list\n");
            return ERROR;
        }
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
int AddReceiptSorted(ReceiptPosition head_R, char file_name[]){
    char article_name[50];
    int quantity;
    double price;
    ReceiptPosition temp=head_R;
    ReceiptPosition new_receipt=(ReceiptPosition)malloc(sizeof(Receipt));

    if (new_receipt == NULL) 
    {
        printf("Memory allocation error!\n");
        return ERROR;
    }
    new_receipt->head_A->quantity = 0;
    new_receipt->head_A->price = 0;
    new_receipt->head_A->next = NULL;

    new_receipt->next = NULL;

    new_receipt->receipt_date.year = 0;
    new_receipt->receipt_date.month = 0;
    new_receipt->receipt_date.day = 0;
    FILE* filepointer=NULL;
    filepointer=fopen(file_name,"r");
    if(filepointer==NULL){
        printf("Error opening file");
        return ERROR;
    }
    if(fscanf(filepointer,"%d-%d-%d\n",&new_receipt->receipt_date.year,&new_receipt->receipt_date.month,&new_receipt->receipt_date.day)!=3){
        printf("Error in reading receipt date");
        return ERROR;
    }
    while(fscanf(filepointer,"%s %d %lf\n",article_name,&quantity,&price)==3){
        if(AddArticleSorted(new_receipt->head_A,article_name,quantity,price)){
            printf("Error in add article sorted");
            return ERROR;
        }

    } //1. SLUCAJ = GOD 2 VECA -> SHIFT
    // 2. SLUCAJ = GOD ISTE; MISEC 2 VECI -> SHIFT
    //3. SLUCAJ = GOD ISTE MISECI ISTI DAN 2 VECI -> SHIFT
    while(temp->next&&(temp->next->receipt_date.year<new_receipt->receipt_date.year||
    (temp->next->receipt_date.year==new_receipt->receipt_date.year && temp->next->receipt_date.month<new_receipt->receipt_date.month)||
    (temp->next->receipt_date.year==new_receipt->receipt_date.year && temp->next->receipt_date.month==new_receipt->receipt_date.month && temp->next->receipt_date.day<new_receipt->receipt_date.day))){
        temp=temp->next; //shiftamo u bilo kojem od ova tri slucaja 
    }
    //ako ne vrijedi ni jedan od tri slucaja = na pravom smo mistu za insertat:
    new_receipt->next=temp->next;
    temp->next=new_receipt;

    fclose(filepointer);

    return EXIT_SUCCESS;

}
int AddArticleSorted(ArticlePosition head_A, char name[], int quantity, double price){
    ArticlePosition temp = head_A;
    ArticlePosition new_article = (ArticlePosition)malloc(sizeof(Article));

    if (new_article == NULL) 
    {
        printf("Memory allocation error!\n");
        return ERROR;
    }

    strcpy(new_article->name, name);
    new_article->quantity = quantity;
    new_article->price = price;
    new_article->next = NULL;

    if (head_A->next) 
    {
        while (temp->next && strcmp(new_article->name, temp->next->name) > 0) 
            temp = temp->next;     
    }

    new_article->next = temp->next;
    temp->next = new_article;

    return EXIT_SUCCESS;
}
int Request(ReceiptPosition head_R){
    char name[50];
    Date start;
    Date end;

    int quantity=0;
    double price=0.0;
    int flag=1;

    printf("\nName of article: ");
    scanf("%s",name);

    printf("Type the starting date in YYYY-MM-DD:");
    scanf("%d-%d-%d",&start.year,&start.month,&start.day);

    printf("Type the ending date in YYYY-MM-DD: ");
    scanf("%d-%d-%d", &end.year, &end.month, &end.day);

    ReceiptPosition temp=head_R->next;

    while(temp){
        ArticlePosition temp_A=temp->head_A->next;
        //prvo provjera za end date: usporedujemo svaku komponentu tempa s TIM DATUMOM, onda za start
        if(temp->receipt_date.year>end.year||(temp->receipt_date.year==end.year&&(temp->receipt_date.month>end.month||(temp->receipt_date.month==end.month&&temp->receipt_date.day>end.day))))
        {
            break;
        }
        if(temp->receipt_date.year>start.year||(temp->receipt_date.year==start.year&&(temp->receipt_date.month>start.month||(temp->receipt_date.month==start.month&&temp->receipt_date.day>=start.day)))){
                while(temp_A){
                    if(strcmp(temp_A->name,name)==0){ //ako naidemo na trazeni artikal :
                        flag=0;
                        quantity+=temp_A->quantity;
                        price+=(temp_A->price*temp_A->quantity); // zbrajamo sveukupnu lovu potrosenu 
                    }
                    temp_A=temp_A->next; //gledamo za iduci artikal
                }
        }
        temp=temp->next; //gledamo za iduci racun
    }

if(flag){
    printf("Article doesn't exist in receipts");
    return ERROR;
}
printf("Article quantity: %d\n",quantity);
printf("Total cost: %.2lf\n",price);

return EXIT_SUCCESS;
}