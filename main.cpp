/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Notice: Please  注意修改SourceFile里需要转换的原码!!!
It's very important!
Beijing University of Posts and Telecommunications
whsyc.All rights (are) reserved.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <io.h> 

typedef struct {
	int parent;
	int weight;
	char ch;
	int lchild, rchild;  
}HNode,*HFMtree;

typedef char** HFMcode;

HFMtree bt;
HFMcode bc;
int n;
int *w;//权值 
char *ch;

void select(HFMtree bt,int j,int &s1,int &s2); //1选择parent为0且weight最小的两个结点 
void init(); //1输入字符及其权值，建立哈夫曼树  
void encoding(); //1编码  
void decoding(); //1译码  
void treeprint(); //1打印哈夫曼树   
void codeprint();//1打印代码   
void HFMCoding(HFMtree &bt,HFMcode &bc,int *w,int n,char *ch);  //1 
void Free();//释放动态分配空间   

int main()
{
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 

	while(1)
	{
		char option;
		scanf("%c",&option); 
		switch(option)  
       	{    
        	case '1':init();break;    
        	case '2':encoding();break;    
        	case '3':decoding();break;    
        	case '4':codeprint();break;   
        	case '5':treeprint();break;  
        	case 'q':  
        	case 'Q':Free();exit(1);  
        	default :printf("输入有误!\n");  
       } 
       getchar();
	}
 	system("pause");
	return 0;
}

void init()
{
	FILE *fp;
	printf("请输入字符个数n：\n");
	scanf("%d",&n);
	ch=(char *)malloc(n*sizeof(char)); 
	printf("请输入所有字符:\n");
	getchar();
	int i;
	for(i=0;i<n;++i)  
        scanf("%c",&ch[i]);
 	w=(int *)malloc(n*sizeof(int));
 	printf("请输入这些字符的权值:\n");
	for(i=0;i<n;++i)  
        scanf("%d",&w[i]);
	HFMCoding(bt,bc,w,n,ch);//调用91 
	fp=fopen("HTree.txt","w");  
	fprintf(fp,"%d",n);
	for(i=0;i<n;++i)  
        fprintf(fp,"%c",ch[i]);  
    for(i=0;i<n;++i)  
        fprintf(fp,"%5d",w[i]);  
    for(i=1;i<=n;++i)  
        fprintf(fp,"\n%c:%s",bt[i].ch,bc[i]);  
    fclose(fp);
    printf("已完成初始化操作\n\n"); 
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 
}

void HFMCoding(HFMtree &bt,HFMcode &bc,int *w,int n,char *ch)//应该没问题 
{
	int m;  
    m=2*n-1;  
    int j,s1,s2,k;  
    bt=(HNode *)malloc((m+1)*sizeof(HNode));  
    HNode *p;  
    int i;  
    for(p=bt+1,i=1;i<=n;++p,++i,++w,++ch)
	{  
        p->ch=*ch;  
        p->weight=*w;  
        p->parent=p->lchild=p->rchild=0;  
    }  
    for(;i<=m;++i,++p)
	{  
        p->ch=0;  
        p->weight=0;  
        p->parent=p->lchild=p->rchild=0;  
    }  
    for(i=n+1;i<=m;++i)
	{  
        select(bt,i-1,s1,s2);  
        bt[s1].parent=i;
		bt[s2].parent=i;  
        bt[i].lchild=s1;
		bt[i].rchild=s2;  
        bt[i].weight=bt[s1].weight+bt[s2].weight;  
    }  
    bc=(char**)malloc((n+1)*sizeof(char*));  
    char *cd;  
    cd=(char *)malloc(n*sizeof(char));  
    cd[n-1]='\0';  
    int start,c,f;  
    for(i=1;i<=n;++i){  
        start=n-1;  
        for(c=i,f=bt[i].parent;f!=0;c=f,f=bt[f].parent)
		{  
            if(bt[f].lchild==c) 
				cd[--start]='0';  
            else 
				cd[--start]='1';  
        }  
        bc[i]=(char *)malloc((n-start)*sizeof(char));  
        strcpy(bc[i],&cd[start]);  
    }  
    free(cd);
}

void select(HFMtree bt,int j,int &s1,int &s2)
{
	int i;  
    for(i=1;i<=j;i++)   
        if(bt[i].parent==0)
		{
			s1=i;
			break;
		}  
    for (;i<=j;i++)  
        if ((bt[i].parent==0)&&(bt[i].weight<bt[s1].weight))  
            s1=i;  
    bt[s1].parent=1;  
    for(i=1;i<=j;i++)  
        if(bt[i].parent==0)
		{
			s2=i;
			break;
		}  
    for(;i<=j;i++)  
        if((bt[i].parent==0)&&(i!=s1)&&(bt[i].weight<bt[s2].weight))  
            s2=i;  
}

void encoding()
{
	FILE *fp,*fp1; 
	int i;
	char in;
	//in = '\0';//用于测试 
	if(n==0)  
    {  
        fp=fopen("HTree.txt","r");  
        fscanf(fp,"%d",&n);  
        if(feof(fp))
		{  
            printf("请初始化哈夫曼树后再试！\n");  
        }  
        ch=(char *)malloc(n*sizeof(char));  
        for(i=0;i<n;++i)  
            fscanf(fp,"%c",&ch[i]);  
        w=(int *)malloc(n*sizeof(int));  
        for(i=0;i<n;++i)  
            fscanf(fp,"%d",&w[i]);  
        HFMCoding(bt,bc,w,n,ch);  
        printf("已载入哈夫曼树！\n");  
        fclose(fp);  
    }  
    if((fp=fopen("SourceFile.txt","r"))==NULL)
    {
    	printf("无法打开文件SourceFile.txt\n");
    }
    else
    {
    	printf("成功读取SourceFile.txt\n");      	
    }
    if((fp1=fopen("CodeFile.txt","w"))==NULL)
    {
    	printf("无法打开文件CodeFile.txt\n");    	
    }
    else
    {
    	printf("成功读取CodeFile.txt\n");      	
    }
    fscanf(fp,"%c",&in);  
    while(!feof(fp))  
    {  
        for(i=1;i<=n;++i)
		{  
			if(bt[i].ch==in)  
			break;  
        }  
  
        fprintf(fp1,"%s",bc[i]);  
        fscanf(fp,"%c",&in);  
    }  
    printf("\n编码结束，结果已存入CodeFile.txt文件中！\n\n");  
    fclose(fp);  
    fclose(fp1);
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 
}

void decoding()
{
	int i,m;
	char in;
	FILE *fp,*fp1;
	if(n==0)
	{
		fp=fopen("HTree.txt","r");  
        fscanf(fp,"%d",&n);  
        if(feof(fp))
		{  
            printf("请先初始化哈夫曼树！\n");  
        }  
        ch=(char *)malloc(n*sizeof(char));  
        for(i=0;i<n;++i)  
            fscanf(fp,"%c",&ch[i]);  
        w=(int *)malloc(n*sizeof(int));  
        for(i=0;i<n;++i)  
            fscanf(fp,"%d",&w[i]);  
        HFMCoding(bt,bc,w,n,ch);  
        printf("已载入哈夫曼树！\n");  
        fclose(fp);
	}
	fp=fopen("CodeFile.txt","r");  
    fp1=fopen("TextFile.txt","w");  
    for(i=1;bt[i].parent!=0;++i);  
		m=i;  
    while(!feof(fp))
	{  
    	if(bt[m].lchild && bt[m].rchild)
		{  
			fscanf(fp,"%c",&in);  
			if(in=='0')
				m=bt[m].lchild;  
			else
				m=bt[m].rchild;  
        }  
		else
		{  
			fprintf(fp1,"%c",bt[m].ch);  
			m=i;  
        }  
    }  
        printf("\n译码结束，译码结果已保存到TextFile.txt文件中！\n\n");  
        fclose(fp);  
        fclose(fp1);
        
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 
}

void codeprint()
{
	FILE *fp,*fp1;  
    int i=0;  
    char in;  
    printf("代码文件为:\n");  
    fp=fopen("CodeFile.txt","r");  
    fp1=fopen("CodePrint.txt","w");  
    fscanf(fp,"%c",&in);  
    while(!feof(fp))  
    {  
        printf("%c",in);  
        fprintf(fp1,"%c",in);  
            i++;  
        if(i==50)
		{  
            printf("\n");  
            fprintf(fp1,"\n");  
            i=0;  
        }  
        fscanf(fp,"%c",&in);  
    }  
    printf("\n");  
    fclose(fp);  
    fclose(fp1);  
    printf("代码文件已存入CodePrint.txt文件中\n\n");  
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 
}

void treeprint()
{
	FILE *fp;  
    fp=fopen("TreePrint.txt","w");  
    int i;  
    for(i=1;i<2*n;i++)
	{  
        printf("%c%8d%8d%8d%8d\n",bt[i].ch,bt[i].weight,bt[i].parent,bt[i].lchild,bt[i].rchild);  
        fprintf(fp,"%c%8d%8d%8d%8d",bt[i].ch,bt[i].weight,bt[i].parent,bt[i].lchild,bt[i].rchild);  
        fprintf(fp,"\n");  
    }  
    fclose(fp);  
    printf("哈夫曼树已存入TreePrint.txt\n\n");
	printf("***************\n");  
	printf("请选择如下操作:\n");  
	printf("1.初始化\n");  
	printf("2.编码\n");  
	printf("3.译码\n");  
	printf("4.印代码文件\n");  
	printf("5.打印哈夫曼树\n");  
	printf("Q.退出\n");  
	printf("***************\n"); 
}

void Free()  
{  
    free(bt);   
    free(bc);  
    free(w);  
    free(ch);  
}
