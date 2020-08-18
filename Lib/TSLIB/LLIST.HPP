template <class T> class QLinkedList;

template <class T>
class QLinkedListObject
   {
      friend class QLinkedList<T>;

      T data;

      QLinkedListObject *next,
                        *prev;
   public:
      QLinkedListObject(T& d) : data(d)
         {
            next = prev = NULL;
         }
   };

template <class T>
class QLinkedList
   {
      QLinkedListObject<T> *last    ,
                           *current ;

   public:
      QLinkedList();
     ~QLinkedList()
         {
            kill();
         }

      void kill();

      void  add(T& , int append = 1);

      void  append(T& data) { add(data,1); }
      void  insert(T& data) { add(data,0); }

      void  insertHere(T& data);

      void  remove();

      int   empty()
         {
            return (last == NULL);
         }

      T&    get();
      T&    get(int recno);

      void  rewind();
      int   past_end();
      int   eol()
         {
            return past_end();
         }

      int   count();

      void  operator++();
      void  operator++(int);
      void  operator--();
      void  operator--(int);

      T&    operator[](int i)
         {
            return get(i);
         }

      void  sort(int (*compare)(T&,T&));
   };

template <class T>
QLinkedList<T>::QLinkedList()
{
   current = last = NULL;
}


template <class T>
void
QLinkedList<T>::kill()
{
   if(last == NULL) return;

   QLinkedListObject<T> *p = last;

   do
   {
      QLinkedListObject<T> *next = p->next;

      delete p;

      p = next;
   }
   while(p != last);

   last = NULL;
}

template <class T>
int
QLinkedList<T>::count()
{
   int i = 0;

   if(last == NULL) return 0;

   QLinkedListObject<T> *p = last;

   do
   {
      i++;

      p = p->next;
   }
   while(p != last);

   return i;
}


template <class T>
void
QLinkedList<T>::add(T& data , int append )
{
   if(last == NULL)
   {
      last = current = new QLinkedListObject<T>(data);

      last->next = last->prev = last;
   }
   else
   {
      QLinkedListObject<T> *p = new QLinkedListObject<T>(data);

      p->next    = last->next;
      p->prev    = last;

      last->next->prev = p;
      last->next       = p;

      if(append) last = p;
   }
}

template <class T>
void
QLinkedList<T>::insertHere(T& data)
{
   if(current == NULL)
   {
      add(data,1);
      return;
   }

   if(last == NULL || current == last->next)
   {
       add(data,0);
       return;
   }

   QLinkedListObject<T> *p = new QLinkedListObject<T>(data);

   p->next = current;
   p->prev = current->prev;

   current->prev->next = p;
   current->prev = p;
}




template <class T>
void
QLinkedList<T>::remove()
{
   if(current == NULL) return;

   if(last == last->next)
   {
      delete last;

      last = current = NULL;

      return;
   }

   QLinkedListObject<T> *new_current = NULL;

   if(current == last)
   {
      last        = current->prev;
   }
   else
   {
      new_current = current->next;
   }

   current->next->prev = current->prev;
   current->prev->next = current->next;

   delete current;

   current = new_current;
}


template <class T>
void
QLinkedList<T>::rewind()
{
   current = (last != NULL) ? last->next : NULL;
}

template <class T>
T&
QLinkedList<T>::get()
{
   static T dummy;

   return (current != NULL) ? current->data : dummy;
}

template <class T>
T&
QLinkedList<T>::get(int recno)
{
   static T dummy;

   if(last == NULL)
      return dummy;

   QLinkedListObject<T> *p = last->next;

   int i;
   
   for(i=0 ; i<recno ; i++)
   {
      p = p->next;

      if(p == last->next)
         break;
   }

   current = p;

   if(i < recno)
      return dummy;
   else
      return p->data;
}


template <class T>
void
QLinkedList<T>::operator++()
{
    current = current->next;

    if(current == last->next) current = NULL;
}

template <class T>
void
QLinkedList<T>::operator++(int)
{
    current = current->next;

    if(current == last->next) current = NULL;
}

template <class T>
void
QLinkedList<T>::operator--()
{
    current = current->prev;

    if(current == last) current = NULL;
}

template <class T>
void
QLinkedList<T>::operator--(int)
{
    current = current->prev;

    if(current == last) current = NULL;
}

template <class T>
int
QLinkedList<T>::past_end()
{
   return (current == NULL);
}

template <class T>
void
QLinkedList<T>::sort(int (*compare)(T&,T&))
{
   if(count() < 2)
      return;

   QLinkedListObject<T> *lle1,
                        *lle2;

   for(lle1 = last->next; lle1 != last ; lle1 = lle1->next)
   {
      for(lle2 = lle1->next; lle2 != last->next ; lle2 = lle2->next)
      {
         if(compare(lle1->data,lle2->data) > 0)
         {
            T tmp(lle1->data);

            lle1->data = lle2->data;
            lle2->data = tmp;
         }
      }
   }
}
