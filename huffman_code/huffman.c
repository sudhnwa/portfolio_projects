/*huffmanCode.3
in this code, decoding module is optimised
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ptr and codePtr are two file pointers

int i=0, top=0;                     //i=>loop variable
char *str;                          //used dynamic memory allocation instead

struct Node{
    char data;
    int freq;
    int topNode;
    char code[1000];
    struct Node *nxt, *front, *rear, *left, *right;
};

struct Node *start=NULL, *current, *traverse, *newNode, *temp, *f, *r, *q1=NULL, *q2=NULL, *root;

struct Node *isRep(int);            //function used in charCount
struct Node *deq(struct Node *);
int isEmpty(struct Node *);
int isSizeOne(struct Node *);
struct Node *getFront(struct Node *);
void inOrderTraversal(struct Node *);
struct Node *findMin(struct Node *, struct Node *);
int isLeaf(struct Node *);
void printCode(struct Node *, char [], int);
int height(struct Node *);

//take command line parameters to the main function
int main(int argc, char *argv[]){

    int charCount=0;         
    int length=1;
    char ch;

    //counting number of characters in file
    FILE *ptr=fopen(argv[1], "r");              
    charCount=0;
    ch=fgetc(ptr);
    while(ch!=EOF){
        charCount++;
        ch=fgetc(ptr);
    }
    str=(char *)calloc(charCount, sizeof(char));
    fclose(ptr);

    //copying file as a string
    ptr=fopen(argv[1], "r");
    i=0;
    *(str+i)=fgetc(ptr);
    while(*(str+i)!=EOF){
        i++;
        *(str+i)=fgetc(ptr);
    }
    *(str+i)='\0';                          //appending null character to a string is very important
    fclose(ptr);

    //charCount module starts
    i=0;
    while(*(str+i)!='\0'){
        if(start==NULL){
            newNode=(struct Node *)malloc(sizeof(struct Node));
            ch=*(str+i);
            newNode->data=ch;
            newNode->freq=1;
            start=newNode;
            current=newNode;
            newNode->nxt=NULL;
        }
        else if(isRep(i)!=NULL){
            temp=isRep(i);
            (temp->freq)++;
        }
        else{
            newNode=(struct Node *)malloc(sizeof(struct Node));
            ch=*(str+i);
            newNode->data=ch;
            newNode->freq=1;
            current->nxt=newNode;
            current=newNode;
            newNode->nxt=NULL;
        }
        //printf("%c", str[i]); to check wheather the loop is running correct or not
        i++;
    }//charCount module ends

    //bubbleSort module starts
    f=start;
    current=NULL;
    temp=NULL;
    r=NULL;

    while(f!=NULL){
        f=f->nxt;
        length++;
    }

    for(int i=0; i<length; i++){
        current=start;
        r=start;

        while(current->nxt!=NULL){
            if((current->freq)>(current->nxt->freq)){
                temp=current->nxt;
                current->nxt=current->nxt->nxt;
                temp->nxt=current;

                if(current==start){
                    start=temp;
                    r=temp;
                }
                else{
                    r->nxt=temp;
                }
                current=temp;
            }
                r=current;
                current=current->nxt;
        }
    }
    //bubbleSort Module end

    //setting the rear pointer and front pointer
    f=start;        //pointers to first queue
    r=start;
    while(r->nxt!=NULL){
        r=r->nxt;
    }
    q1=start;
    q1->front=start;
    q1->rear=r;

    //printing data
    traverse=q1->front;
    while(traverse!=NULL){
        printf("\nData: %c", traverse->data);
        printf("\nFreqency: %d", traverse->freq);
        traverse=traverse->nxt;
    }//printing module end

    //Tree building module starts
    //adding first node in the second queue and setting up the pointers
    current=deq(q1);        //current will act as left pointer
    traverse=deq(q1);       //traverse will act as right pointer

    newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->freq=traverse->freq + current->freq;
    newNode->left=current;
    newNode->right=traverse;
    q2=newNode;
    q2->front=newNode;
    q2->rear=newNode;
    newNode->nxt=NULL;
    
    while(!(isEmpty(q1)&&isSizeOne(q2))){
        //current=>left pointer
        //traverse=>right pointer
        current=findMin(q1, q2);
        traverse=findMin(q1, q2);

        newNode=(struct Node *)malloc(sizeof(struct Node));
        newNode->freq=traverse->freq + current->freq;
        newNode->left=current;
        newNode->right=traverse;
        newNode->nxt=NULL;
        if(q2->front==NULL){
            q2->front=newNode;
            q2->rear=newNode;
        }
        else{
            q2->rear->nxt=newNode;
            q2->rear=newNode;
        }
    }
    //Tree building module end
    int maxHeight=height(q2->front);
    char arr[maxHeight];

    printf("\n");
    printCode(q2->front, arr, top);

    printf("\nHeight of the tree is: %d", maxHeight);
    printf("\n\n");
    inOrderTraversal(q2->front);
    
    printf("\n\n");
    //printing datav 
    traverse=q1;
    while(traverse!=NULL){
        printf("\nData: %c", traverse->data);
        printf("\nFreqency: %d", traverse->freq);
        printf("\nCode: ");
        for(i=0; i<traverse->topNode; i++){
            printf("%c", traverse->code[i]);
        }
        traverse=traverse->nxt;
    }//printing module end
    
    //putCodes module starts
    printf("\n");
    printf("Encoded Data is: ");
    FILE *codePtr;
    codePtr=fopen(argv[2], "w");
    i=0;
    while(*(str+i)!='\0'){
        ch=*(str+i);
        traverse=q1;
        while(traverse!=NULL){
            if(ch==traverse->data){
                for(int j=0; j<traverse->topNode; j++){
                    printf("%c", traverse->code[j]);      
                    fprintf(codePtr, "%c", traverse->code[j]);
                }
            }
            traverse=traverse->nxt;
        }
        i++;
    }
    fclose(codePtr);
    //putCodes module end

    //Decoding Module Starts
    codePtr=fopen(argv[2], "r");
    ptr=fopen(argv[3], "w");
    char c=fgetc(codePtr);                    //c=>temporary variable to store the return value of fgetc
    traverse=q2->front;
    while(c!=EOF){
       //c=c-48;
        if(c=='1'){
            traverse=traverse->right;
        }
        else{
            traverse=traverse->left;
        }
        
        if(isLeaf(traverse)){
            fputc(traverse->data, ptr);
            traverse=q2->front;
        }
        c=fgetc(codePtr);
    }
    fclose(codePtr);
    fclose(ptr);
    //Decoding Module ends
    
    return 0;
}

struct Node *isRep(int i){
    int j=i;
        traverse=start;
        while(traverse!=NULL){
            if(*(str+j)==traverse->data){
                return traverse;
            }
            traverse=traverse->nxt;
        }
    return NULL;
}

int isSizeOne(struct Node *q){
    return q->front==q->rear;
}

int isEmpty(struct Node *q){
    return q->front==NULL;
}

struct Node *deq(struct Node *q){
    if(isSizeOne(q)){
        temp=q->front;
        q->front=NULL;
        return temp;
    }
    else{
        temp=q->front;
        q->front=q->front->nxt;
        return temp;
    }
}

struct Node *getFront(struct Node *q){
    if(isEmpty(q)){
        return NULL;
    }
    return q->front;
}

struct Node *findMin(struct Node *q1, struct Node *q2){
    if(isEmpty(q1)){
        return deq(q2);
    }

    if(isEmpty(q2)){
        return deq(q1);
    }

    if(getFront(q1)->freq < getFront(q2)->freq){
        return deq(q1);
    }

    return deq(q2);
}

void inOrderTraversal(struct Node *root){
    if(root!=NULL){
        inOrderTraversal(root->left);
        if(isLeaf(root)){
            printf("\nDATA: %c", root->data);
            printf("\nFREQURNCY: %d", root->freq);
        }
        inOrderTraversal(root->right);
    }
}

int isLeaf(struct Node *root){
    return ((root->left==NULL)&&(root->right==NULL));
}

int height(struct Node *root){
    int leftHeight, rightHeight;

    if(root==NULL){
        return 0;
    }
    else{
        leftHeight=height(root->left);
        rightHeight=height(root->right);
        if(leftHeight>rightHeight){
            return (leftHeight+1);
        }
        else{
            return (rightHeight+1);
        }
    }
}

void printCode(struct Node *root, char arr[], int top){
    if(root->left){
        arr[top]='0';
        printCode(root->left, arr, top+1);
    }

    if(root->right){
        arr[top]='1';
        printCode(root->right, arr, top+1);
    }

    if(isLeaf(root)){
        printf("\n%c: ", root->data);
        root->topNode=top;
        for(i=0; i<top; i++){
          root->code[i]=arr[i];
          printf("%c", arr[i]);  
        }
    }
}
