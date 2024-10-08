#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
    int hashed = hash(key);
    int index = hash(key);
    int full = 1;
    int count = TABLESIZE+1;

    //check first that the key hasn't already existed in the hash table
    for(int i=0;i<TABLESIZE;i++){
        if (hashTable[i].indicator == EMPTY) {
            //Check if table is full or not
            if (full == 1) full = 0;
        }
        else if (hashTable[i].key == key) return -1;
    }

    if (full) return count;

    if (hashTable[hashed].indicator == EMPTY) {
        hashTable[hashed].key = key;
        hashTable[hashed].indicator = USED;
        return hashed;
    }
    else {
        while (hashTable[index].next != -1) {
            index = hashTable[index].next;
        }
        
        int update = index;

        while (hashTable[update].indicator == USED) {
            update = (update+1) % TABLESIZE;
        }

        //need to update next of last hash slot
        hashTable[update].key = key;
        hashTable[update].indicator = USED;
        hashTable[index].next = update;
        return update;
    }
}

int HashFind(int key, HashSlot hashTable[])
{
    int hashed = hash(key);
    int index = hash(key);

    if (hashTable[hashed].indicator == EMPTY) return -1;

    else {
        while (hashTable[index].next != -1) {
            if (hashTable[index].key == key) return index;
            index = hashTable[index].next;
        }
        
        if (hashTable[index].key == key) return index;
        else return -1;
    }
}