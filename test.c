#include "structure.h"

int main() {
    /* char filename[] = "source";
     int file = open(filename, O_RDONLY);
     printf("hello %d\n", file);
     struct stat st;
     stat(filename, &st);
     printf("hello %d\n", st.st_size);
     char *word = malloc(((int) st.st_size) * sizeof(char));
     char *it = word;
     char c;*/
    //printf("hello %d\n", sizeof(TREE));
    TREE *tree = createTree();
    srand(time(NULL));//temporary
    for (int i = 0; i < 10000; i++) {
        if(!addNode(tree, rand() % (2000 + 1 - 1) + 1)) break;
        printf("%d added\n", i);
    }
    I *iterator = createIterator(tree);
    while (!iterator->isLast) {
        printf("key %d: n=%d; isLast=%d\n", iterator->current->key->key, iterator->current->key->n, iterator->isLast);
        deleteNode(tree, iterator->current);
        iterator->next(iterator);
        printf("islast %d\n", iterator->isLast);
    }
    //deleteNode(tree, getNode(tree, 10));
    free(iterator);
    iterator = createIterator(tree);
    /* while (!iterator->isLast) {
         iterator->next(iterator);
         printf("key %d: n=%d; isLast=%d\n", iterator->current->key->key, iterator->current->key->n, iterator->isLast);
         deleteNode(tree, iterator->current);
     }*/
    free(iterator);
    //deleteNode(tree, tree->root);
    free(tree);
}
