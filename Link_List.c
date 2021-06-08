

/***********************************************************************************************//**
 * @brief
 *      create Linked List Elements
這邊就要用到兩種運算元——NEW 和 DELETE 啦。

鏈結串列由以下元素構成：
起始：指向鏈結串列第一個節點的指標
鏈結串列的節點：
當前節點的資料
下一個節點的地址
結尾：最後一個節點連接的地址寫「NULL」，表示鏈結串列結束。

Step 1：建立第一個節點。
Step 2：我們得先決定，要不要建立一個新的節點？
 **************************************************************************************************/
/***********************************************************************************************//**
 * new
   動態的跟記憶體要空間、在不需要後釋放掉它 
 * 跟記憶體要一個用來存放 4 個 byte 的 int 型變數所需要的空間
   int *ptr = new int;
 *  配置完成後指定儲存值，可以這樣宣告：
   int *ptr = new int(100);
 *  刪除這個空間
   delete ptr;
 *  跟記憶體要了 100 個 int 大小的空間，再回傳空間的第一個位址，存入指標 ptr 裡面
   int * ptr = new int[100];
 *  釋放掉這塊空間
   delete [] ptr;
 * 可惜C不能用new 跟 delete，要用 malloc 跟 free 
 * 動態配置了 1000 個 int 大小的空間
   int *p = malloc(sizeof(int) * 1000);
*  在不使用時使用 free 釋放
   free(p); 
 **************************************************************************************************/
#include <stdio.h>
/*typedef*/
typedef	unsigned char			UI8;
typedef	  signed char			SI8;
typedef	unsigned short			UI16;
typedef	  signed short			SI16;
typedef	unsigned long			UI32;
typedef	  signed long			SI32;
typedef	float					      F32;
typedef	double					F64;
/*struct*/
struct LinkList_Struct{
   int value;
   struct LinkList_Struct * NextList;
};
void PrintList(struct LinkList_Struct * head);
struct LinkList_Struct * reverseList_Iteration(struct LinkList_Struct * head);
// struct LinkList_Struct * reverseListRecursive(struct LinkList_Struct * head);
int main()
{
   UI32 count, i;
   UI32 InputNum;
   /*declear how many node is required*/
   scanf("%d", &count);
   /*create new gead*/
   struct LinkList_Struct * ListHead = malloc(sizeof(struct LinkList_Struct));
   scanf("%d", &InputNum);
   
   /*first node*/
   ListHead->value = InputNum;
   ListHead->NextList = NULL;

   /*next node*/
   struct LinkList_Struct * CurrentList = ListHead;

   for (i = 1; i < count; i++){
      scanf("%d", &InputNum);
      CurrentList->NextList = malloc(sizeof(struct LinkList_Struct));
      CurrentList = CurrentList->NextList;
      CurrentList->value = InputNum;
      CurrentList->NextList = NULL; 
   }
   printf("\n");
   printf("the input number is :");
  
  PrintList(ListHead);


   printf("\n");

   printf("the reverse input number is :");
   ListHead = reverseList_Iteration(ListHead);
   PrintList(ListHead);
   system("pause");
   return 0;
}
/***********************************************************************************************//**
 * 迭代法反轉
   1.取出NextList
   2.改變head的NextList
   3.取出head
   4.改變head
 **************************************************************************************************/
struct LinkList_Struct * reverseList_Iteration(struct LinkList_Struct * head) // 迭代
{
    struct LinkList_Struct *p = NULL, *q;
    
    while (head)
    {
        q = head->NextList;
        head->NextList = p;
        p = head;
        head = q;
    }
    return p;
}
/***********************************************************************************************//**
 * 匯出linked list
   1.輸入head
   2.print 直到 Null
 **************************************************************************************************/
void PrintList(struct LinkList_Struct * currentlinked){
  while(1){
    printf("%d", currentlinked->value);
    
    if (currentlinked->NextList == NULL){
      break;
    }
    else{
      currentlinked = currentlinked->NextList;
    }
  }
}