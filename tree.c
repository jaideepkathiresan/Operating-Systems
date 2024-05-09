#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void print_process(int process_id, int parent_id, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("P%d (parent: P%d)\n", process_id, parent_id);
}

int main() {
    printf("Creating process tree\n");
    print_process(1, 0, 0);
    pid_t p2, p3;

    p2 = fork();
    if (p2 == 0) {
        print_process(2, 1, 1);
        pid_t p5, p6, p7;
        p5 = fork();
        if (p5 == 0) {
            print_process(5, 2, 2);
            exit(0);
        }
        p6 = fork();
        if (p6 == 0) {
            print_process(6, 2, 2);
            exit(0);
        }
        p7 = fork();
        if (p7 == 0) {
            print_process(7, 2, 2);
            exit(0);
        }
        exit(0);
    }

    p3 = fork();
    if (p3 == 0) {
        print_process(3, 1, 1);
        pid_t p4, p8;
        p4 = fork();
        if (p4 == 0) {
            print_process(4, 3, 2);
            pid_t p11;
            p11 = fork();
            if (p11 == 0) {
                print_process(11, 4, 3);
                exit(0);
            }
            exit(0);
        }
        p8 = fork();
        if (p8 == 0) {
            print_process(8, 3, 2);
            exit(0);
        }
        exit(0);
}
}
/*
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct node {
    char name[10];
    struct node* children[10];
    int child_count;
} Node;

Node* create_node(char* name) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->child_count = 0;
    return node;
}

void add_child(Node* parent, Node* child) {
    parent->children[parent->child_count++] = child;
}

void print_tree(Node* root, int depth) {
    for (int i = 0; i < depth; i++) printf("\t");
    printf("%s\n", root->name);
    for (int i = 0; i < root->child_count; i++) {
        print_tree(root->children[i], depth + 1);
    }
}

int main() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    Node* nodes[n];
    for (int i = 0; i < n; i++) {
        char name[10];
        printf("Enter the name of node %d: ", i + 1);
        scanf("%s", name);
        nodes[i] = create_node(name);
    }

    for (int i = 0; i < n; i++) {
        int m;
        printf("Enter the number of children for node %s: ", nodes[i]->name);
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
            char name[10];
            printf("Enter the name of child %d: ", j + 1);
            scanf("%s", name);
            for (int k = 0; k < n; k++) {
                if (strcmp(nodes[k]->name, name) == 0) {
                    add_child(nodes[i], nodes[k]);
                    break;
                }
            }
        }
    }

    printf("\nProcess Tree:\n");
    print_tree(nodes[0], 0);

    return 0;
}

*/
