#ifndef E16DST_FILE_HH
#define E16DST_FILE_HH

#include <string>

class E16DST_File {
public:
   enum {
      WriteMode = 0,
      ReadMode = 1
   };
   E16DST_File(){};
   ~E16DST_File(){};
   virtual void open(std::string file_name, int io_mode) = 0;
   virtual void close() = 0;
   virtual bool good() = 0;
   virtual int write(char *buffer, int size) = 0;
   virtual int read(char *buffer, int size) = 0;

protected:
};

#include <fstream>
// non-compressed using fstream
class E16DST_FileStream : public E16DST_File {
public:
   E16DST_FileStream();
   ~E16DST_FileStream();
   void open(std::string file_name, int io_mode);
   void close();
   bool good();
   int write(char *buffer, int size);
   int read(char *buffer, int size);

private:
   std::fstream fp;

};

#include <zlib.h>
// compressed to gzip by using zlib.h
class E16DST_GZFile : public E16DST_File {
public:
   E16DST_GZFile();
   ~E16DST_GZFile();
   void open(std::string file_name, int io_mode);
   void close();
   bool good();
   int write(char *buffer, int size);
   int read(char *buffer, int size);

private:
   gzFile gzfp;

};

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zstd.hpp>
class E16DST_ZSTDFile : public E16DST_File {
public:
   E16DST_ZSTDFile();
   ~E16DST_ZSTDFile();
   void open(std::string file_name, int io_mode);
   void close();
   bool good();
   int write(char *buffer, int size);
   int read(char *buffer, int size);

private:
   int io_mode;
   boost::iostreams::filtering_ostream ofilter;
   boost::iostreams::filtering_istream ifilter;
};

class E16DST_MemoryBuffer : public E16DST_File {
public:
   E16DST_MemoryBuffer(char *_serialized_data, int _buffer_size);
   ~E16DST_MemoryBuffer();
   void open(std::string file_name, int io_mode){};
   void close(){};
   bool good();
   int write(char *buffer, int size);
   int read(char *buffer, int size);
   void clear();
   int data_size(){return pointer;};
   //const char *data(){return serialized_data;};

private:
   int buffer_size;
   char *serialized_data;
   int pointer;

};

#endif // E16DST_FILE_HH
