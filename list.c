// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  // create a list
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l) {
  // delete list and deallocate memory used for it
   node_t *curr = l->head;
  node_t *next;
  while (curr != NULL){
    next = curr->next;
    free(curr);
    curr = NULL;
    curr = next;
  }
  l->head = NULL;
}

void list_print(list_t *l) {
  // print out list as string
  if (l->head == NULL){
    printf("NULL\n");
    return;
  }

  node_t *curr = l->head;
  printf("%d", curr->value);
  
  curr = curr->next;
  while (curr != NULL){
    printf("->%d", curr->value);
    curr = curr->next;
  }
  printf("->NULL\n");
  return;
}

char * listToString(list_t *l) {
  // convert list to string and return string
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  if (l->head != NULL){
    sprintf(tbuf, "%d", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  else{
    strcat(buf, "NULL");
    return;
  }
  
  while (curr != NULL) {
    sprintf(tbuf, "->%d", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }

  strcat(buf, "->NULL"); // indicate that the last pointer points to null
  return buf;
}

int list_length(list_t *l) { 
  // return length of list
  int list_length = 0;
  node_t* curr = l->head;

  while (curr != NULL){
    curr = curr->next;
    list_length ++;
  }
    return list_length; 
  }

void list_add_to_back(list_t *l, elem value) {
  // add node with given value at the end of the list
  
  if (l->head==NULL){ // edge case where list is empty
    list_add_to_front(l, value);
    return;
  }

  node_t *curr = l->head;
  while (curr->next != NULL){
    curr = curr->next;
  }

  node_t* new_node = (node_t *) malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
      
  curr->next = new_node;

}

void list_add_to_front(list_t *l, elem value) {
    // add node with given value at the front of the list

     node_t* cur_node = (node_t *) malloc(sizeof(node_t));
     cur_node->value = value;
     cur_node->next = NULL;

     /* Insert to front */

     node_t* head = l->head;  // get head of list

     cur_node->next = head;
     l->head = cur_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
    // add node with given value at the given index
  
  if (index == 1){
    list_add_to_front(l, value);
    return;
  }
  int current_index = 1;

  node_t *curr = l->head;
  node_t *prev = NULL;
  
  while (curr != NULL){
    if (current_index == index){
      node_t* new_node = (node_t *) malloc(sizeof(node_t));
      new_node->value = value;
      new_node->next = curr;
      prev->next = new_node;
      return;
    }
    prev = curr;
    curr = curr->next;
    current_index ++;
  }

  if (current_index == index){ // in case the index is at the end of the list
      list_add_to_back(l, value);
    }
  
}

elem list_remove_from_back(list_t *l) { 
    // remove node at the back of the list and deallocate its memory

  node_t *prev;
  node_t *curr = l->head;
  elem output_value;
  
  if (l->head==NULL){ // edge case where list is empty
    return -1;
  }

  if (curr->next == NULL){ // edge case where list is length 1
    output_value = curr->value;
    l->head = NULL;
    free(curr);
    curr = NULL;
    return output_value;
  }
  
  while (curr->next != NULL){
    prev = curr;
    curr = curr->next;
  }

  output_value = curr->value;

  prev->next = NULL;
  free(curr);
  curr = NULL;
  
  return output_value;
  }

elem list_remove_from_front(list_t *l) { 
  // remove node at the front of the list and deallocate its memory

  if (l->head==NULL){ // edge case where list is empty
    return -1;
  }

  node_t *curr = l->head;
  node_t *next = curr->next;

  elem output_value = curr->value;
  l->head = next;
  free(curr);
  curr = NULL;

  return output_value; 
  }

elem list_remove_at_index(list_t *l, int index) { 
  // remove node at the given index of the list and deallocate its memory
  elem output_value;
  if (index == 1){
    output_value = list_remove_from_front(l);
    return output_value;
  }
  int current_index = 1;

  node_t *curr = l->head;
  node_t *prev;

  while (curr != NULL){
    if (current_index == index){
      output_value = curr->value;
      
      prev->next = curr->next;
      free(curr);
      curr = NULL;

      return output_value;
    }
    prev = curr;
    curr = curr->next;
    current_index++;
  }
  
  return -1;
  }

bool list_is_in(list_t *l, elem value) { 
  // return true or false of if given value is in list
  node_t *curr = l->head;
  while (curr != NULL){
    if (curr->value == value){
      return true;
    }
    curr = curr->next;
  }
  return false; 
}

elem list_get_elem_at(list_t *l, int index) { 
  // return elem value at given index or -1 if index is out of range
  int current_index = 1;
  node_t *curr = l->head;
  while (curr != NULL){
    if (current_index == index){
      return curr->value;
    }
    curr = curr->next;
    current_index ++;
  }
return -1; 
}

int list_get_index_of(list_t *l, elem value) { 
  // return first index where given value occurs or -1 if not found
  int current_index = 1;
  node_t *curr = l->head;
  while (curr != NULL){
    if (curr->value == value){
      return current_index;
    }
    curr = curr->next;
    current_index ++;
  }

  return -1; 
}

