#ifndef __HASH_HPP
#define __HASH_HPP

template <class T>
class QHashTable
   {
      struct pair
         {
            QString key;
            T      data;
         };
         
      QLinkedList<pair> **table;
      unsigned size;

      unsigned hash(const char *key)
      {
         return unsigned(crc32(key)) % size;
      }
   public:
      QHashTable(unsigned);
//      HashTable(const HashTable<T>&);

     ~QHashTable();

      T    operator[](const char *);
      bool add(const char *,const T&);

//      void operator=(const HashTable<T>&);
   };


template <class T>
QHashTable<T>::QHashTable(unsigned s)
{
   size = s;

   table = new QLinkedList<pair> *[size];

   for(unsigned i=0;i<size;i++)
      table[i] = NULL;
}

/*
template <class T>
HashTable<T>::HashTable(const HashTable<T>& x)
{
   size = x.size;

   table = new LinkedList<pair> *[size];

   for(unsigned i=0;i<size;i++)
      table[i] = x.table[i];
}
*/

template <class T>
QHashTable<T>::~QHashTable()
{
   for(unsigned i=0;i<size;i++)
      if(table[i])
         delete table[i];
         
   delete [] table;
}

/*
template <class T>
void
HashTable<T>::operator=(const HashTable<T>& x)
{
   delete [] table;
   
   size = x.size;

   table = new LinkedList<pair>[size];

   for(unsigned i=0;i<size;i++)
      table[i] = x.table[i];
}
*/

template <class T>
T
QHashTable<T>::operator[](const char *key)
{
   unsigned h = hash(key);

   if(table[h] != NULL)
   {
      QLinkedList<pair>& ll = *table[hash(key)];

      for(ll.rewind() ; !ll.eol() ; ll++)
      {
         if(ll.get().key == key)
            return ll.get().data;
      }
   }
   
   return T();
}

template <class T>
bool
QHashTable<T>::add(const char *key,const T& obj)
{
   unsigned h = hash(key);

   if(table[h] == NULL)
   {
      table[h] = new QLinkedList<pair>;
   }
   
   QLinkedList<pair>& ll = *table[hash(key)];

   pair p;

   p.key  = key;
   p.data = obj;
   
   ll.add(p);
   
   return true;
}

#endif

