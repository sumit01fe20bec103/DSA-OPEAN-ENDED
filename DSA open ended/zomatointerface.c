#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Customer
{
    int custId;
    char name[20];
    int age;
    int password;
    struct Customer *left;
    struct Customer *right;
}*Cust;
typedef struct Item
{
    int itemId;
    char itemName[30];
    int price;
    struct Item *left;
    struct Item *right;
}*Items;
Items items[10],headItem=NULL;
Cust cust[10],headCust=NULL;
int custCount=5;
Cust insert_into_bst_cust(Cust t){
    t->left = NULL;
    t->right = NULL;
    if(headCust==NULL){
        headCust = t;
        return headCust;
    }
    Cust curr,parent;
    curr = headCust;
    parent = NULL;
    while(curr!=NULL){
        parent = curr;
        if(t->password<curr->password)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if(t->password<parent->password)
        parent->left = t;
    else
        parent->right = t;
    return headCust;
}
Items insert_into_bst(Items t){
    t->left = NULL;
    t->right = NULL;
    if(headItem==NULL){
        headItem = t;
        return headItem;
    }
    Items curr,parent;
    curr = headItem;
    parent = NULL;
    while(curr!=NULL){
        parent = curr;
        if(t->itemId<curr->itemId)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if(t->itemId<parent->itemId)
        parent->left = t;
    else
        parent->right = t;
    return headItem;
}

void initialFun()
{
    int c;
    FILE *fp;
    fp=fopen("Customer_ec.txt","r");
    if(fp==NULL)
        printf("File not opened\n");
    for(int i=0;i<custCount;i++)
    {
        cust[i]=(Cust)malloc(1*sizeof(struct Customer));
        fscanf(fp,"%d%s%d%d",&cust[i]->custId,cust[i]->name,&cust[i]->age,&cust[i]->password);
        headCust=insert_into_bst_cust(cust[i]);
    }
    fclose(fp);
     fp=fopen("Items_ec.txt","r");
    for(int i=0;i<10;i++)
    {
        items[i]=(Items)malloc(1*sizeof(struct Item));
        fscanf(fp,"%d%s%d",&items[i]->itemId,items[i]->itemName,&items[i]->price);
        headItem=insert_into_bst(items[i]);
    }
    fclose(fp);
}
int binary_search(int id)
{
    Items cur=headItem;
    while(cur->itemId!=id)
    {
        if(id<cur->itemId)
            cur=cur->left;
        else
            cur=cur->right;

        if(cur==NULL)
            return 0;
    }
    return 1;
}
Cust binary_search_cust(int t)
{
    Cust cur=headCust;
    while((cur->password-13)!=t)
    {
        if(cur->password<t)
            cur=cur->right;
        else
            cur=cur->left;

        if(cur==NULL)
            return NULL;
    }
    return cur;
}
int main()
{
    int temp;
    Cust tempCust;
    int choice;
    initialFun();
    printf("---------------WELCOME TO ZOMATO INTERFACE-----------------\n");
    while(1)
    {
        printf("1 - SignIn\n2 - SignUp\n3 - OrderItems\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter Password\n");
                scanf("%d",&temp);
                tempCust=binary_search_cust(temp);
                if(tempCust==NULL)
                {
                    printf("User not found\nIf new user Please SignUp\n");
                }
                else
                    printf("Valid User\n");
                break;
              case 2:printf("Signing Up----\n");
                    Cust cur=(Cust)malloc(1*sizeof(struct Customer));
                    custCount++;
                    printf("Enter Customer Details\n");
                    scanf("%d%s%d%d",&cur->custId,cur->name,&cur->age,&cur->password);
                    cust[custCount]=cur;
                    cur->password = cur->password+13;
                    headCust=insert_into_bst_cust(cur);
                    FILE *fp=fopen("Customer_ec.txt","a");
                    fprintf(fp,"%d%s%d%d",cur->custId,cur->name,cur->age,cur->password);
                    fclose(fp);
                    break;
              case 3:printf(" Items available\n");
                     printf("Item_Id\t ItemName\t Price(Rs)\n");
                     for(int i=0;i<10;i++)
                     {
                         printf("%d\t%s\t%d\n",items[i]->itemId,items[i]->itemName,items[i]->price);
                     }
                     int id;
                     printf("Enter the item Id\n");
                     scanf("%d",&id);
                     id=binary_search(id);
                     if(id==0)
                     {
                         printf("Item searched not found\t(Please try our other Items)\n");
                     }
                     else
                     {
                         printf("HOOOO!!!\nItem Ordered successfully!!\n");
                     }
                     break;
        }
    }
    return 0;
}
