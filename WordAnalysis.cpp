#include <string.h>
#include <stdio.h>
#include "WordAnalysis.h"
#define N 20
WordAnalysis::WordAnalysis(){
    i=0;
    j=0;
    token=new char[N];
    //wordList=new char[16][10];
    char wordList1[16][10]={"BEGIN","END","FOR","DO","IF","THEN","ELSE","��ʶ��",
                            "����",":","+","*",",","(",")",":="};
    for(int k=0;k<16;k++){
        wordList[k]=wordList1[k];
    }
}
void WordAnalysis::analyze(char *word){
    instr=word;
    n=strlen(word);
    getNBC();
    if(isLetter(ch)){
        while(isDigit(ch) || isLetter(ch)){
            cat();
            getChar();
        }
        unGetChar();
        if(isEnd()==false)
            printf("��������");
        else{
            if(isReserve()){
                printf("�����֣�%s ",token);
            }
            else
                printf("��ʶ����%s ",token);
        }
    }
    else if(isDigit(ch)){
        while(isDigit(ch)){
            cat();
            getChar();
        }
        unGetChar();
        if(isEnd()==false){
            printf("��������");
        }
        else{
            int res=str2Int(token);
            printf("���֣�%d ",res);
        }
    }
    else if(ch=='+'||ch=='*'||ch==','||ch=='('||ch==')'){
        if(isEnd()==false)
            printf("��������");
        else
            printf("��������%c ",ch);
    }
    else if(ch==':'){
        if(isEnd())
            printf("��������%c ",ch);
        else{
            getChar();
            if(ch=='=' && isEnd())
                printf("��������:= ");
            else
                printf("��������");
        }
    }
    else
        printf("��������");
}

void WordAnalysis::getChar(){
    if(j<n){
        j++;
        ch=instr[j];
    }
    else
        printf("���������Ͻ����");
}
void WordAnalysis::getNBC(){
    while(instr[j]!='\0'&&instr[j]==' ')
        j++;
    ch=instr[j];
}
void WordAnalysis::cat(){
    token[i]=ch;
    i++;
    token[i]='\0';
}
bool WordAnalysis::isLetter(char ch){
    if(ch>='a'&&ch<='z' || ch>='A'&&ch<='Z')
        return true;
    else
        return false;
}
bool WordAnalysis::isDigit(char ch){
    if(ch>='0'&&ch<='9')
        return true;
    else
        return false;
}
void WordAnalysis::unGetChar(){
    if(j>=0)
        j--;
    else
        printf("���������½����");
}
bool WordAnalysis::isReserve(){
    for(int k=0;k<8;k++){
        if(strcmp(token,wordList[k])==0)
            return true;
    }
    return false;
}
int WordAnalysis::str2Int(char *s){
    int res=0,m=1;
    int start=0;
    while(s[start]=='0')
        start++;
    for(int k=strlen(s)-1;k>=start;k--){
        if(isDigit(s[k])){
            res=res+(s[k]-'0')*m;
            m=m*10;
        }
        else{
            printf("���ڷ������ַ�");
            return -1;
        }
    }
    return res;
}
void WordAnalysis::error(){
    printf("��������");
}
bool WordAnalysis::isEnd(){
    return j==n-1;
}
void WordAnalysis::analyzeSentence(char *s){
    instr=s;
    n=strlen(s);
    while(instr[j]!='\0'){
        getNBC();
        if(j==n)
            break;
        if(isLetter(ch)){
        while(instr[j]!='\0' && (isDigit(ch) || isLetter(ch))){
            cat();
            getChar();
        }
        unGetChar();
        if(isReserve()){
            printf("�����֣�%s\n",token);
        }
        else
            printf("��ʶ����%s\n",token);
        i=0;
        }
    else if(isDigit(ch)){
        while(instr[j]!='\0' && isDigit(ch)){
            cat();
            getChar();
        }
        unGetChar();
        int res=str2Int(token);
        printf("�� �֣�%d\n",res);
        i=0;
    }
    else if(ch=='+'||ch=='*'||ch==','||ch=='('||ch==')'){
        printf("��������%c\n",ch);
    }
    else if(ch==':'){
        getChar();
        if(ch=='=')
            printf("��������:=\n");
        else
            printf("��������:\n");
    }
    else{
        printf("�Ƿ�\n");
    }
    j++;
    }
}
WordAnalysis::~WordAnalysis(){
    delete token;
}
