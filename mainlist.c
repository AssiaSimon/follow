#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "testListHelpers.h"

void displayInt(s_node *node){
    int *ptrInt = (int*)list_get_data(node);
    
    if(ptrInt != NULL){
        printf("%d",*ptrInt);
    } 
}

int compare(s_node* head, void *param){
    if(head == NULL || head->data == NULL || param == NULL){
        return -1; 
    }

    int * ptr_head = (int*) head->data; 
    int * ptr = (int*) param; 

    if(*ptr_head == *ptr){
        return 0;
    }else if(*ptr < *ptr_head){
        return 1;
    }else{ // *ptr > *ptr_head
        return 2 ;
    }
}

int main(void){
    int i=1, j=2, k=4, m=3, n=3, o=0, ok;
    s_node *node_ajout = NULL; 

    /* TEST 1 : creation d'une liste vide */

    s_node *l = list_create();

    ok = check_list_state(l, &node_int_to_string, "null" );
    
    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 1 : creation d'une liste vide non réussi !\n"); 
        displaylist(l, &displayInt); 
        exit(-1);
    }

    /* TEST 2 : insertion en tête */

    l = list_insert(l,&i); //il faut qu'on fait une verification
    
    ok = check_list_state(l, &node_int_to_string, "1 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 2 : Insertion de 1 a échoué !\n"); 
        displaylist(l, &displayInt); 
        exit(-1);
    } 
    
    l = list_insert(l,&j); //il faut qu'on fait une verification 

    ok = check_list_state(l, &node_int_to_string, "2 -> 1 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 2 : Insertion de 2 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    } 
        

    /* TEST 3 : insertion de NULL */
    
    l = list_insert(l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 1 -> null" );
    if(ok){
        printf("TEST 3 : Insertion de NULL refusée correctement !\n"); 
    }else{
        printf("ERREUR TEST 3 : Insertion de NULL acceptée !\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1); 
    }

    /* TEST 4 : insertion entier apres NULL */
    
    l = list_insert(l, &j); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 2 -> 1 -> null" );
    if(ok){
         displaylist(l, &displayInt);  displaylist(l, &displayInt);  
    }else{
        printf("ERREUR TEST 4 : Insertion de NULL acceptée avant entier !\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1); 
    }


    /* TEST 4 : insertion ordonnée */

    node_ajout = list_orderedAppend(&l, &compare, &k);

    ok = check_list_state(l, &node_int_to_string, "4 -> 2 -> 1 -> null" );
    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 4 : Insertion ordonnée de 4 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    } 


    node_ajout = list_orderedAppend(&l, &compare, &m);

    ok = check_list_state(l, &node_int_to_string, "4 -> 3 -> 2 -> 1 -> null" );
    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 4 : Insertion ordonnée de 3 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    } 


    /* TEST 5 : refus d'insertion ordonnée d'un doublon */

    node_ajout = list_orderedAppend(&l, &compare, &n);

    ok = check_list_state(l, &node_int_to_string, "4 -> 3 -> 2 -> 1 -> null" );
    
    if(ok){
        printf("TEST 5 : Insertion du DOUBLON 3 refusée correctement !\n");
    }else{
        printf("ERREUR TEST 5 : Insertion de DOUBLON 3 acceptée !\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    }

        
    /* TEST 6 : insertion en queue */

    l = list_append(l, &o); 

    ok = check_list_state(l, &node_int_to_string, "4 -> 3 -> 2 -> 1 -> 0 -> null" );
    
    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 6 : Insertion de 0 en queue a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    }


    /* TEST 7 : refus d'insertion de NULL en queue */

    l = list_append(l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "4 -> 3 -> 2 -> 1 -> 0 -> null" );
    
    if(ok){
        printf("TEST 7 : Insertion en queue de NULL correctement refusée !\n");
    }else{
        printf("ERREUR : Insertion en queue de NULL acceptée !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    }


    /* TEST 8 : supression de la tête */

    l = list_remove (l, &k); 

    ok = check_list_state(l, &node_int_to_string, "3 -> 2 -> 1 -> 0 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 8 : Suppression de tête 4 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        // exit(-1);
    }


    /* TEST 9 : supression au milieu */

    l = list_remove (l, &j); 

    ok = check_list_state(l, &node_int_to_string, "3 -> 1 -> 0 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 9 : Suppression de 2 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    /* TEST 10 : supression en queue */

    l = list_remove (l, &o); 

    ok = check_list_state(l, &node_int_to_string, "3 -> 1 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 10 : Suppression de 0 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }

    
    /* TEST 11 : supression d'un element absent */

    l = list_remove (l, &k); 

    ok = check_list_state(l, &node_int_to_string, "3 -> 1 -> null" );

    if(ok){
        printf("TEST 11 : Suppression d'un element absent reussi !\n"); 
    }else{
        printf("ERREUR TEST 11 : Suppression de 4 qui est absent !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    /* TEST 12 : supression de NULL */

    l = list_remove (l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "3 -> 1 -> null" );

    if(ok){
        printf("TEST 12 : Suppression de 0 a échoué !\n"); 
    }else{
        printf("ERREUR TEST 13 : Suppression de 4 qui est absent !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    /* TEST ETAT FINAL de l */

    ok = check_list_state(l, &node_int_to_string, "3 -> 1 -> null" );

    if(ok){
        printf("c'est bon\n");
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR : Insertion de 0 a échoué !\n"); 
        printf("ce n'est pas bon\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        // exit(-1);
    }


    s_node * vide = list_create();
    vide = list_append(vide, &o); 

    ok = check_list_state(vide, &node_int_to_string, "0 -> null" );
    
    if(ok){
        printf("c'est bon\n");
        displaylist(vide, &displayInt); 
    }else{
        printf("ERREUR : Insertion de 0 en queue a échoué !\n"); 
        printf("ce n'est pas bon\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        // exit(-1);
    }

    if(l != NULL){
        listdestroy(l);
    }

    if(vide != NULL){
        listdestroy(vide);
    }

    return 0; 
}

