/* Copyright (C) 2000 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
  Code for handling dubble-linked lists in C
*/

#include "mysys_priv.h"
#include <my_list.h>



	/* Add a element to start of list */

MYLIST *list_add(MYLIST *root, MYLIST *element)
{
  DBUG_ENTER("list_add");
  DBUG_PRINT("enter",("root: 0x%lx  element: %lx", root, element));
  if (root)
  {
    if (root->prev)			/* If add in mid of list */
      root->prev->next= element;
    element->prev=root->prev;
    root->prev=element;
  }
  else
    element->prev=0;
  element->next=root;
  DBUG_RETURN(element);			/* New root */
}


MYLIST *list_delete(MYLIST *root, MYLIST *element)
{
  if (element->prev)
    element->prev->next=element->next;
  else
    root=element->next;
  if (element->next)
    element->next->prev=element->prev;
  return root;
}


void list_free(MYLIST *root, uint free_data)
{
  MYLIST *next;
  while (root)
  {
    next=root->next;
    if (free_data)
      my_free((gptr) root->data,MYF(0));
    my_free((gptr) root,MYF(0));
    root=next;
  }
}


MYLIST *list_cons(void *data, MYLIST *list)
{
  MYLIST *new_charset=(MYLIST*) my_malloc(sizeof(MYLIST),MYF(MY_FAE));
  if (!new_charset)
    return 0;
  new_charset->data=data;
  return list_add(list,new_charset);
}


MYLIST *list_reverse(MYLIST *root)
{
  MYLIST *last;

  last=root;
  while (root)
  {
    last=root;
    root=root->next;
    last->next=last->prev;
    last->prev=root;
  }
  return last;
}

uint list_length(MYLIST *list)
{
  uint count;
  for (count=0 ; list ; list=list->next, count++) ;
  return count;
}


int list_walk(MYLIST *list, list_walk_action action, gptr argument)
{
  int error=0;
  while (list)
  {
    if ((error = (*action)(list->data,argument)))
      return error;
    list=list_rest(list);
  }
  return 0;
}