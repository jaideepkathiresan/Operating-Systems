#include <stdio.h>
int main(){
    int arr[10];
    int arr2[10];
    printf("Enter array elements ");
    for (int i=0;i<5;i++){
        scanf("%d",&arr[i]);
    }
    for (int i=0;i<5;i++){
        arr2[i]=arr[i];
    }
    printf("Original array : ");
    for (int i=0;i<5;i++){
        printf("%d",arr[i]);
    }
    printf("Duplicated array : ");
    for (int i=0;i<5;i++){
        printf("%d",arr2[i]);
    }    
    return 0;
}

