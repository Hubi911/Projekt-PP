
#ifndef STRUCT_H
#define STRUCT_H

#define MAX 100

typedef struct {
  char model[MAX];
  char klasa[MAX];
  int moc;
  char pilot[MAX];
  char stan[MAX];
  } Mech;

typedef struct Element{
   Mech dane;
   struct Element *next;
 } Element;

typedef struct {
  Element *head;
  } List;

#endif
