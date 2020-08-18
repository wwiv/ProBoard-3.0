template <class T>
  class QRecordFile : public QFile
    {
        public:
            bool read(T& , long rec = -1);
            bool write(T& , long rec = -1);

            bool seek(long rec);

            QRecordFile& operator>>(T&);
            QRecordFile& operator<<(T&);

            void operator+=(long rec) { seek(pos() + rec * sizeof(T)); }
            void operator-=(long rec) { seek(pos() - rec * sizeof(T)); }
    };

template <class T>
bool
QRecordFile<T>::read( T& obj , long rec)
{
   return (((rec < 0 || seek(rec)) && QFile::read(&obj,sizeof(T)) == sizeof(T)) ? true:false);
}

template <class T>
bool
QRecordFile<T>::write( T& obj , long rec)
{
	return (((rec < 0 || seek(rec)) && QFile::write(&obj,sizeof(T)) == sizeof(T)) ? true:false);
}

template <class T>
QRecordFile<T>&
QRecordFile<T>::operator<<(T& obj)
{
    write(obj);

    return *this;
}

template <class T>
QRecordFile<T>&
QRecordFile<T>::operator>>(T& obj)
{
    read(obj);

    return *this;
}

template <class T>
bool
QRecordFile<T>::seek( long rec )
{
    long pos = rec * sizeof(T);

    return (pos == QFile::seek(pos));
}

