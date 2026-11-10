#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "testListHelpers.h"

// Affiche un seul entier 
void displayInt(s_node *node){
    // cast en pointeur entier (*int)
    int *ptrInt = (int*)list_get_data(node);
    
    if(ptrInt != NULL){
        printf("%d",*ptrInt);
    } 
}

int compareInt(s_node* head, void *param){

    // cast en pointeur entier (*int)
    int * ptr_head = (int*) head->data; 
    int * ptr = (int*) param; 

    if(*ptr_head == *ptr){
        return 0;
    }else if(*ptr < *ptr_head){
        return -1;
    }else{ // *ptr > *ptr_head
        return 1 ;
    }
}

int main(void){
    int i=1, j=2, k=4, m=3, n=6, p=7, o=8, ok; 

    printf("----------------------------- TEST LISTE NON ORDONNEE ----------------------------- \n\n"); 

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

    l = list_insert(l,&p); //il faut qu'on fait une verification
    
    ok = check_list_state(l, &node_int_to_string, "7 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 2 : Insertion de 7 a échoué !\n"); 
        displaylist(l, &displayInt); 
        exit(-1);
    } 
    
    l = list_insert(l,&n); //il faut qu'on fait une verification 

    ok = check_list_state(l, &node_int_to_string, "6 -> 7 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 2 : Insertion de 6 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    } 

    l = list_insert(l,&n); //il faut qu'on fait une verification 

    ok = check_list_state(l, &node_int_to_string, "6 -> 6 -> 7 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 2 : Insertion de 6 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    } 
        

    /* TEST 3 : insertion de NULL */
    
    l = list_insert(l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "6 -> 6 -> 7 -> null" );
    if(ok){
        printf("TEST 3 : Insertion de NULL refusée correctement !\n"); 
    }else{
        printf("ERREUR TEST 3 : Insertion de NULL acceptée !\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1); 
    }

    /* TEST 4 : insertion d'un entier apres NULL pour vérifier que NULL n'est pas affiché*/
    
    l = list_insert(l, &j); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 6 -> 7 -> null" );
    if(ok){
         displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 4 : Insertion de NULL acceptée avant entier !\n");
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1); 
    }

    /* TEST 5 : insertion en queue */

    l = list_append(l, &o); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 6 -> 7 -> 8 -> null" );
    
    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 5 : Insertion de 8 en queue a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    }


    /* TEST 6 : refus d'insertion de NULL en queue */

    l = list_append(l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 6 -> 7 -> 8 -> null" );
    
    if(ok){
        printf("TEST  : Insertion en queue de NULL correctement refusée !\n");
    }else{
        printf("ERREUR TEST 6 : Insertion en queue de NULL acceptée !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        exit(-1);
    }


    /* TEST 7 : supression de la tête */

    l = list_remove (l, &n); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 7 -> 8 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 7 : Suppression de tête 6 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        // exit(-1);
    }


    /* TEST 8 : supression en queue */

    l = list_remove (l, &o); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 7 -> null" );

    if(ok){
        displaylist(l, &displayInt); 
    }else{
        printf("ERREUR TEST 8 : Suppression de 8 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }

    
    /* TEST 9 : supression d'un element absent */

    l = list_remove (l, &k); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 7 -> null" );

    if(ok){
        printf("TEST 9 : Suppression d'un element absent correctement refusée !\n"); 
    }else{
        printf("ERREUR TEST 9 : Suppression de 4 qui est absent !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    /* TEST 10 : supression de NULL */

    l = list_remove (l, NULL); 

    ok = check_list_state(l, &node_int_to_string, "2 -> 6 -> 7 -> null" );

    if(ok){
        printf("TEST 10 : Suppression de NULL correctement refusée !\n");
        printf("c'est bon\n\n"); 
    }else{
        printf("ERREUR TEST 10 : Suppression de 4 qui est absent !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    
    printf("----------------------------- TEST LISTE ORDONNEE ----------------------------- \n\n");

    s_node *node_ajout = list_create(); 


    /* TEST 11 : insertion ordonnée dans une liste ordonnée */

    s_node * order = list_create();

    node_ajout = list_orderedAppend(&order, &compareInt, &k);

    ok = check_list_state(order, &node_int_to_string, "4 -> null" );
    if(ok){
        displaylist(order, &displayInt); 
    }else{
        printf("ERREUR TEST 11 : Insertion ordonnée de 4 a échoué !\n"); 
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    } 


    node_ajout = list_orderedAppend(&order, &compareInt, &m);

    ok = check_list_state(order, &node_int_to_string, "3 -> 4 -> null" );
    if(ok){
        displaylist(order, &displayInt); 
    }else{
        printf("ERREUR TEST 11 : Insertion ordonnée de 3 a échoué !\n"); 
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    } 

    node_ajout = list_orderedAppend(&order, &compareInt, &i);

    ok = check_list_state(order, &node_int_to_string, "1 -> 3 -> 4 -> null" );
    if(ok){
        displaylist(order, &displayInt); 
    }else{
        printf("ERREUR TEST 11 : Insertion ordonnée de 1 a échoué !\n"); 
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    } 


    node_ajout = list_orderedAppend(&order, &compareInt, &j);

    ok = check_list_state(order, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> null" );
    if(ok){
        displaylist(order, &displayInt); 
    }else{
        printf("ERREUR TEST 11 : Insertion ordonnée de 1 a échoué !\n"); 
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    } 

    /* TEST 12 : Vérifier que list_orderedAppend renvoie le pointeur de la s_node insérée */

    if(node_ajout == order) {
        printf("ERREUR TEST 12 : le retour de list_orderedAppend  n'est pas correct !\n"); 
    } else{
        printf("Liste insérée : \n"); 
        displaylist(node_ajout, &displayInt); 
    }

  
    /* TEST 13 : refus d'insertion ordonnée d'un doublon */

    node_ajout = list_orderedAppend(&order, &compareInt, &m);

    ok = check_list_state(order, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> null" );
    
    if(ok){
        printf("TEST 12 : Insertion du DOUBLON 3 refusée correctement !\n");
    }else{
        printf("ERREUR TEST 12 : Insertion de DOUBLON 3 acceptée !\n");
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    }


    /* TEST 14 : refus d'insertion ordonnée d'un NULL */

    node_ajout = list_orderedAppend(&order, &compareInt, NULL);

    ok = check_list_state(order, &node_int_to_string, "1 -> 2 -> 3 -> 4 -> null" );
    
    if(ok){
        printf("TEST 14 : Insertion du NULL refusée correctement !\n");
    }else{
        printf("ERREUR TEST 14 : Insertion de NULL acceptée !\n");
        displaylist(order, &displayInt); 
        listdestroy(order);
        exit(-1);
    }
    

    /* TEST 15 : supression au milieu */

    order = list_remove (order, &m); 

    ok = check_list_state(order, &node_int_to_string, "1 -> 2 -> 4 -> null" );

    if(ok){
        displaylist(order, &displayInt);
        printf("c'est bon\n\n");  
    }else{
        printf("ERREUR TEST 15 : Suppression de 3 a échoué !\n"); 
        displaylist(l, &displayInt); 
        listdestroy(l);
        //exit(-1);
    }


    printf("----------------------------- TEST LISTE VIDE ----------------------------- \n\n"); 

    /* TEST 16 : insertion de 8 en queue dans une liste vide */

    s_node * vide = list_create();
    vide = list_append(vide, &o); 

    ok = check_list_state(vide, &node_int_to_string, "8 -> null" );
    
    if(ok){
        displaylist(vide, &displayInt); 
        printf("c'est bon\n");
    }else{
        printf("ERREUR TEST 16 : Insertion de 8 en queue a échoué !\n"); 
        printf("ce n'est pas bon\n");
        displaylist(vide, &displayInt); 
        listdestroy(vide);
        // exit(-1);
    }

    // Si les listes ne sont pas détruites 
    if(l != NULL){
        listdestroy(l);
    }

    if(vide != NULL){
        listdestroy(vide);
    }

    if(order != NULL){
        listdestroy(order);
    }

    return 0; 
}