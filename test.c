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
    for (int i = 0; i < 1000; i++) {
        addNode(tree, rand() % (200 + 1 - 1) + 1);
        // deleteNode(tree, addNode(tree, rand() % (100 + 1 - 1) + 1));

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
