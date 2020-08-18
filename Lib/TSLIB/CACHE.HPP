template <class dataT,class keyT> class QCache;

template <class dataT,class keyT>
class QCachedObject
   {
      friend class QCache<dataT,keyT>;

      dataT data;
      keyT  key;

      QCachedObject *next , *prev;
   public:

      QCachedObject(dataT& d,keyT& k) : data(d) , key(k)
         {
            next = prev = NULL;
         }
   };

template <class dataT,class keyT>
class QCache
   {
      long max,num;

      QCachedObject<dataT,keyT> *last;

      void promote(QCachedObject<dataT,keyT> *);
   public:
      QCache(long n = 2)
         {
            max  = (n<2) ? 2 : n;
            num  = 0;
            last = NULL;
         }
      ~QCache() 
         { 
            purge(); 
         }
      
      bool find(dataT& , keyT);
      bool update(dataT& , keyT);

      void add(dataT& , keyT);
      void purge();
   };

template <class dataT,class keyT>
void
QCache<dataT,keyT>::add( dataT& data , keyT key )
{
   if(!num)
   {
      last = new QCachedObject<dataT,keyT>(data,key);
      last->next = last->prev = last;
      num++;
      return;
   }

   QCachedObject<dataT,keyT> *next , *prev;

   if(num == max)
   {
      next = last->next;
      prev = last->prev;

      delete last;

      prev->next = next;
      next->prev = prev;

      last = prev;

      num--;
   }

   next = last->next;

   last->next       = new QCachedObject<dataT,keyT>(data,key);
   last->next->prev = last;
   last->next->next = next;
   next->prev       = last->next;

   num++;
}

template <class dataT,class keyT>
void
QCache<dataT,keyT>::promote(QCachedObject<dataT,keyT> *obj)
{
   if(obj == last)
   {
      last = obj->prev;
      return;
   }

   QCachedObject<dataT,keyT> *next = obj->next,
                            *prev = obj->prev;

   prev->next = next;        // Object removed from
   next->prev = prev;        // list

   next       = last->next;

   obj->prev  = last;
   obj->next  = next;

   last->next = obj;

   next->prev = obj;
}

template <class dataT,class keyT>
bool
QCache<dataT,keyT>::find(dataT& data , keyT key)
{
   if(!num) return FALSE;

   QCachedObject<dataT,keyT> *p = last->next;

   do
   {
      if(p->key == key)
      {
         data = p->data;
         promote(p);

         return TRUE;
      }

      p = p->next;
   }
   
   while(p != last->next);

   return FALSE;
}

template <class dataT,class keyT>
bool
QCache<dataT,keyT>::update(dataT& data , keyT key)
{
   if(!num) return FALSE;

   QCachedObject<dataT,keyT> *p = last->next;

   do
   {
      if(p->key == key)
      {
         p->data = data;

         promote(p);

         return TRUE;
      }

      p = p->next;
   }
   while(p != last->next);

   return FALSE;
}


template <class dataT,class keyT>
void
QCache<dataT,keyT>::purge()
{
   if(!num) return;

   QCachedObject<dataT,keyT> *p = last;

   do
   {
      QCachedObject<dataT,keyT> *next = p->next;

      delete p;

      p = next;
   }
   while(p != last);

   num  = 0;
   last = NULL;
}
