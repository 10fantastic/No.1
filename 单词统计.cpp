#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW	-1
#define _CRT_SECURE_NO_WARNINGS
typedef struct {
	unsigned int weight;//权重
	unsigned int partent, lchild, rchild;
}HTNode,* HuffmanTree;
typedef int Status;
typedef char** HuffmanCode;

typedef struct Follow *PtrTo;
typedef struct Follow{
	char Letter;
	PtrTo Next;
}Follow;


typedef struct FirstLetter{
	int sum;
	char FLetter;
	struct FirstLetter *NEW;
	struct FirstLetter *Old;
	PtrTo This;
}FirstLetter;
typedef struct FirstLetter *Ptr;

//哈夫曼编码//

void Select(HuffmanTree* HT, int n, int* s1, int* s2) {
	int i;
	unsigned int min = 9999;
	int temp1 = 0, temp2 = 0;
	for (i = 1;i <= n;i++) {
		if ((*HT)[i].partent == 0 && (*HT)[i].weight < min) {
			min = (*HT)[i].weight;
			temp1 = i;
		}
	}
	*s1 = temp1;
	min = 9999;
	for (i = 1;i <= n;i++) {
		if ((*HT)[i].partent == 0 && (*HT)[i].weight < min && temp1 != i) {
			min = (*HT)[i].weight;
			temp2 = i;
		}
	}
	*s2 = temp2;
}
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, int w[], int n) {
	//w存放n个字符的权值(均>0)，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC。
	if (n <= 1)return;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!(*HT))exit(OVERFLOW);
	int i;
	for (i = 1;i <= n;++i) {
		(*HT)[i].weight = w[i];//权值
		(*HT)[i].partent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	for (i=n+1;i <= m;++i) {
		(*HT)[i].weight = 0;
		(*HT)[i].partent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	int s1, s2;
	for (i = n + 1;i <= m;++i) {	//建哈夫曼树
		//在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		Select(HT, i - 1, &s1, &s2);
		(*HT)[s1].partent = i;(*HT)[s2].partent = i;
		(*HT)[i].lchild = s1;(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	//---从叶子到根逆向求每个字符的哈夫曼编码---
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	if (!(*HC))exit(OVERFLOW);
	char* cd = (char*)malloc(n * sizeof(char));
	if (!cd)exit(OVERFLOW);
	cd[n - 1] = '\0';
	for (int i = 1;i <= n;++i) {
		int start = n - 1;
		int f = 0;
		for (int c = i, f = (*HT)[i].partent;f != 0;c = f, f = (*HT)[f].partent)
			if ((*HT)[f].lchild == c)cd[--start] = '0';
			else cd[--start] = '1';
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));
		if (!(*HC)[i])exit(OVERFLOW);
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);
}
 
//建立链表一个单词链表 
Ptr CreateWord(char *Word) 
{
	Ptr M;
	M=(Ptr)malloc(sizeof(struct FirstLetter));
	M->FLetter=Word[0];
	M->NEW=NULL;
	M->sum=1;
	M->This=NULL;
	M->Old=NULL;
	int i=1;
	PtrTo Temp,P;
	while(Word[i]!='\0')
	{
	    Temp=(PtrTo)malloc(sizeof(struct Follow));
	    Temp->Next=NULL;
	    Temp->Letter=Word[i];

	    if(i==1)
	    M->This=Temp;
	    if(i>=2)
	    P->Next=Temp;
	    
	    P=Temp;
	    i++;
	}	
	return M;
}

//将一个单词链表加入大家庭
void Add(Ptr Head,Ptr K)
{
	Ptr Temp=Head;
	int flag=0;
	if(Temp->NEW==NULL)
	{   Temp->Old=Head;
		Temp->NEW=K;
	}
	else
	{
		while(Temp->NEW!=NULL)
		{   
		    Temp=Temp->NEW;
		    //先搜索首字符是否相同 
		    if(Temp->FLetter==K->FLetter)
		    {
		    	PtrTo T2,K2;
		    	T2=Temp->This;
		    	K2=K->This;
		    	//搜索之后的字符 
		    	while(T2!=NULL&&K2!=NULL&&T2->Letter==K2->Letter)
		    	{
		    		T2=T2->Next;
		    		K2=K2->Next;
				}
				//同一个单词判定条件 
				if(T2==NULL&&K2==NULL)
				{   flag=1;
				    Temp->sum++;
				    free(K);
					break; 
				}
				
				
			}
			
		}
		if(Temp->NEW==NULL&&flag==0)
		{
			Temp->NEW=K;
			K->Old=Temp;
		}
	}
} 
//交换函数
void swap(Ptr Front,Ptr After) 
{
	PtrTo T;
	T=Front->This;
	char tt;
	tt=Front->FLetter;
	int ttt=Front->sum;
	
	Front->FLetter=After->FLetter;
	Front->sum=After->sum;
	Front->This=After->This;
	
	After->FLetter=tt;
	After->sum=ttt;
	After->This=T; 
}

//排序函数 --冒泡排序 
bool Sort(Ptr Head)
{
	if(Head->NEW==NULL)
	return false;

    int sum=0;
	Ptr Temp=Head->NEW;
	
	
	bool flag;
	
	while(Temp!=NULL)
	{
		Temp=Temp->NEW;
		sum++;
	}
	
	
	
	for(sum=sum-1;sum>0;sum--)
	{   flag=false;
	    int T=sum;
	    Temp=Head->NEW;
	    while(T>0)
	    {    
	        if(Temp->sum<Temp->NEW->sum)
	        {    
	            
	            swap(Temp,Temp->NEW);
	        	flag=true;
			}
		
			Temp=Temp->NEW;
	    	T--;
		}
	    if(flag==false)break;
	}
	
	return true;
	
	
}

//打印函数 
void Wprintf(Ptr Head,int sum)
{
    Ptr Temp=Head,Temp1=Head;
    PtrTo T;
    int i;int y=1;//使打印得整齐// 
    //哈夫曼编码
HuffmanTree HT;
HuffmanCode HC;	
int w[sum+1];
do{
	Temp=Temp->NEW;
	w[y++]=Temp->sum;
}while(Temp->NEW!=NULL);
y--;
HuffmanCoding(&HT, &HC, w, y);

//打印// 
Temp=Head;int j=1;
	do{   
	      i=0;
		  Temp=Temp->NEW;
		  free(Temp1);
		  Temp1=Temp;
		  printf("%c",Temp->FLetter);
		  T=Temp->This;i++;
		  while(T!=NULL)
		  {
		       printf("%c",T->Letter);
		       T=T->Next;
		       i++;
		  }
		  for(i;i<15;i++)
		  printf(" ");
		  printf("%d     频率：%.10lf     哈夫曼编码  %s\n",Temp->sum,Temp->sum*1.0/sum*1.0,HC[j]);free(HC[j]);
		  j++;
	  }while(Temp->NEW!=NULL);
	  printf("本文出现了%d种单词\n",y);
}  

int main()
{  

	 printf(" \n\n\n\n\n                                                  词频统计与编码\n");
	 printf("                                 说明：对给定的英文文本，统计单词出现的频率，并用哈夫曼编码为这些单词编码。\n");

while(1){
    FILE *fp;
	char ch,ch1;
	int WordQuantity;
	char Word[20];
	Ptr T;
	int sum=0;
	
	 //定义排序表//
	 Ptr Head;
	 Head=(Ptr)malloc(sizeof(struct FirstLetter));
	 Head->FLetter='\0';
	 Head->NEW=NULL;
	 Head->sum=-1;
	 Head->This=NULL;
	 
	 //打开文件// 
	 char p[80],P[]="return";
	 
	 printf("          请选择文本给定方式：目前只支持给定文本路径\n          如果退出请输入return后回车\n          请输入内容：");
	 scanf("%s",p);
	 
	 if(strcmp(p,P)==0)break;
	if((fp=fopen(p,"r"))==NULL){
		printf("File open error!\n");
		exit(0);
	}                                //如何把单词读取做成函数？// 
	
	while(!feof(fp)){
		ch=fgetc(fp);
		WordQuantity=0;
		
		//找出单个单词// 
		while(!feof(fp))
	        	{   
	                if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
	                {     //大小写转换// 
	                    if(ch>='A'&&ch<='Z')
	                    ch=ch+32;
	
	                	Word[WordQuantity++]=ch;
	                	ch=fgetc(fp);
	                	if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z');
	                	else
	                	{
	                		Word[WordQuantity]='\0';
						    break;
						}
					}
					else
					ch=fgetc(fp);
					
                 }
            //  Word即为单词//
            if(ch!=EOF){
            	sum++;
              T=CreateWord(Word);
              Add(Head,T);
			}
              
}
if(fclose(fp)){
	printf("Can Not close the file! \n");exit(0);
	return 0;
}
Sort(Head);
Wprintf(Head,sum);
printf("本文共出现了%d个单词\n\n",sum);
}
	return 0;
}