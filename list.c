#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// céation d'une nouvelle liste vide
s_node *list_create(void){
    return NULL;
} 

// écrire la donnée d'un noeud
void list_set_data(s_node *node,void *data){
    if(data != NULL && node != NULL){
        node->data = data;
    }
}

// lire la donnée d'un noeud
void * list_get_data(s_node *node){
    if(node == NULL){
        return NULL;
    }
    return node->data;
}

// Récupère le noeud suivant
s_node *list_next(s_node *node){
    if(node == NULL){
        return NULL; 
    }
    return node->next;
}

// Création et insertion d'un noeud en tête  de la liste 
// retourne la tête de la liste
s_node *list_insert(s_node *head,void *data){
    if(data == NULL){
        return head; 
    }

    s_node * n = (s_node *) malloc(sizeof(s_node));
    
    // vérifie que le malloc a fonctionné
    if(n == NULL){
        // malloc échoué
        return head; 
    }

    n->next = head; 
    list_set_data (n,data);
    return n; 
}

// Afficher une liste en applelant la fonction en paramètre 
void displaylist(s_node*head, void(*dispaly)(s_node*)){
    s_node *ptr = head ;
    
    while(ptr!=NULL){
        (*dispaly)(ptr);
        ptr = ptr->next; /* ptr = list_next(ptr) ;*/
        printf("->");
    }
    
    printf("NULL\n");

}

// Création et ajout d'un noeud en queue de liste 
// retourne tête de la liste 
s_node * list_append(s_node * head, void * data){
    
    if(data == NULL){
        return head; 
    }

    s_node *ptr = head; 
    
    if(head == NULL){ // liste vide
        // création nouvelle queue 
        s_node * nv_node = list_create();//
        nv_node = list_insert(nv_node, data);

        //list_set_data(nv_node, data);
        nv_node->next = NULL; 

        return nv_node; 
    }
    
    while(ptr->next != NULL){
        ptr = list_next(ptr); // avance jusqu'à la fin
    }
    // queue de la liste

    // création nouvelle queue 
    s_node * nv_node = list_create(); 
    nv_node = list_insert(nv_node, data);

    //list_set_data(nv_node, data);
    nv_node->next = NULL; 

    // ajout à la fin 
    ptr->next = nv_node; 

    return head;

}

// ajout d'un noeud dans une liste ordonnée
// selon le résultat "compare"
// si la donnée existe déjà, elle n'est pas ajoutée 
// retourne le pointeur de la donnée ajoutée dans liste 
s_node * list_orderedAppend(s_node **head, int (*compare)(s_node*,void*), 
                            void * param){
    
    if(head == NULL || param == NULL){
        return NULL; 
    }

    s_node * ptr = *head; 
    s_node * ptr_avant = NULL; 

    while(ptr != NULL){
        int res = (compare)(ptr, param); 

        if(res == 0){
            // cas : existe déjà
            return ptr;  
        } 
         
        if (res == 1 ){
            // cas : *param  >  ptr->data  => avance 
            ptr_avant = ptr; // avant ajout 
            ptr = ptr->next;
        }
        else {
            // res == -1
            // cas : *param  <  ptr->data  => insère
            break; 
        } 
    }

    s_node * ptr_param = list_insert(ptr, param); 

    // vérifier si l'allocation a réussi 
    if(ptr_param == ptr){
        return NULL; 
    }

    // vérifie si c'est en début de liste 
    if(ptr_avant == NULL){
        // ajoute en tête le s_node contenat le param
        *head = ptr_param;  
    }else{
        // c'est au milieu de liste 
        // relie s_node avant insertion avec le nouveau s_node avec insertion 
        ptr_avant->next = ptr_param; 
    }

    return ptr_param; 
}

// suppresssion de la tete liste 
// retourne la nouvelle tete de  liste 
s_node * list_headRemove(s_node *head){

    if(head == NULL){
        return NULL; 
    }

    s_node * tmp = head->next; 
    free(head);
    return tmp; 
}


// destruction de la liste 
// (La libération des des données n'est pas prise en charge)
s_node * listdestroy(s_node *head){
    s_node *ptr = head; 

    while(ptr != NULL){
        ptr = list_headRemove(ptr); 
    }
    return NULL;
}

// supression de la première instance d'une donnée dans la liste
// retourne la tete de la liste
s_node * list_remove (s_node * head, void * data){

    if(head == NULL || data == NULL){
        return head; 
    }

    // recherche ptr contenant 1ere occurence de data
    s_node * ptr = head;
    s_node * ancienne_tete = NULL;  
    
    while(ptr != NULL){

        if(ptr->data == data){

            // data est la tête à supprimer
            if(ancienne_tete == NULL){
                return list_headRemove(ptr); 
            }

            // data au milieu ou à la fin
            ancienne_tete->next = list_next(ptr); 
            ptr = list_headRemove(ptr); 
        }

        ancienne_tete = ptr; 
        ptr = list_next(ptr); // avance
    }

    return head; 
}
