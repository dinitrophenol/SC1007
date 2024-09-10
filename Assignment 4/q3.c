#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);DE
            comparison = HashInsert(key,hashTable);DE
            if(comparison <0)DE
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    //Write your code here

    //actually doesnt need this part of the if-statement because it is already considered in the while loop but just in case
    if (hashTable[hash1(key)].indicator == EMPTY) {
        hashTable[hash1(key)].key = key;
        hashTable[hash1(key)].indicator = USED;
        return 0;
    }

    int finalkey;
    int i=0; //number of key comparisons
    int found=0;
    int noCount=0;

    for (i;i<TABLESIZE;i++) {
        int newkey = key + (i*hash2(key));
        int hashed = newkey%TABLESIZE;

        if (hashTable[hashed].indicator == USED && hashTable[hashed].key == key) {
            return -1; //Duplicate key found
        }
        //Put key in first seen DELETED slot
        else if (hashTable[hashed].indicator == DELETED && found == 0) {
            finalkey = hashed;
            found = 1;
        }
        else if (hashTable[hashed].indicator == DELETED && found == 1) {
            //DELETED slots do not count towards key comparison
            noCount++;
        }
        //Put key in first seen EMPTY slot
        else if (hashTable[hashed].indicator == EMPTY && found == 0) {
            finalkey = hashed;
            found = 1;
            break;
        }
        //To check that there is no duplicate, we need to find the next EMPTY slot after found == 1
        else if (hashTable[hashed].indicator == EMPTY && found == 1) {
            i--; //-1 because the last EMPTY slot itself does not count towards comparison
            break;
        }
    }

    if (i==TABLESIZE && found == 0) return i; //full Table 
    else if (i==TABLESIZE && found == 1) { //case where every key is put in a DELETED slot, and rest of slots is either DELETED or USED
        hashTable[finalkey].key = key;
        hashTable[finalkey].indicator = USED;
        return i-1-noCount; //-1 because the key's own DELETED slot does not count towards comparison 
    }
    else {
        hashTable[finalkey].key = key;
        hashTable[finalkey].indicator = USED;
        return i-noCount; //key is put in EMPTY slot
    }
}

int HashDelete(int key, HashSlot hashTable[])
{
    //Write your code here
    int nocount = 0;
    int newkey = 0;
    int hashed = 0;

    for (int i=0;i<TABLESIZE;i++) {
        newkey = key + (i*hash2(key));
        hashed = newkey%TABLESIZE;
        
        if (hashTable[hashed].indicator == DELETED) nocount++;
    
        if (hashTable[hashed].indicator == USED && hashTable[hashed].key == key) {
            hashTable[hashed].indicator = DELETED;
            return i+1-nocount;
        }
    }
    return -1;
}