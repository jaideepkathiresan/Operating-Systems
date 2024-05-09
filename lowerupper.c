#include <stdio.h>
#include <ctype.h>
void main(){
    char str[100];
    int i;
    printf("Enter string : ");
    fgets(str,sizeof(str),stdin);
    printf("Original string : %s",str);
    for (i=0;str[i]!='\0';i++){
        if (islower(str[i])){
            str[i]=toupper(str[i]);
        }
        else if (isupper(str[i])){
            str[i]=tolower(str[i]);
        }
        printf("%c",str[i]);
    }
}
