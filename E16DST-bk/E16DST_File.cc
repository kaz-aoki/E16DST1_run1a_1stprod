#include "E16DST_File.hh"
#include <iostream>
#include <cstring>
#include <boost/iostreams/device/file_descriptor.hpp>

E16DST_FileStream::E16DST_FileStream(){
}

E16DST_FileStream::~E16DST_FileStream(){
}

void E16DST_FileStream::open(std::string file_name, int io_mode){
   if (io_mode == WriteMode) {
      fp.open(file_name, std::ios::out | std::ios::binary);
      return;
   }
   if (io_mode == ReadMode) {
      fp.open(file_name, std::ios::in | std::ios::binary);
      return;
   }
   std::cerr << "E16DST_FileStream : Unknown io_mode = " << io_mode << std::endl;
   exit(1);
}

void E16DST_FileStream::close(){
   fp.close();
}

bool E16DST_FileStream::good(){
   return fp.good();
}

int E16DST_FileStream::write(char *buffer, int size){
   fp.write(buffer, size);
   return size;
}

int E16DST_FileStream::read(char *buffer, int size){
   fp.read(buffer, size);
   return fp.gcount();
}

//_____________________________________________________________________________
E16DST_GZFile::E16DST_GZFile(){
}

E16DST_GZFile::~E16DST_GZFile(){
}

void E16DST_GZFile::open(std::string file_name, int io_mode){
   if (io_mode == WriteMode) {
      gzfp = gzopen(file_name.c_str(), "w");
      return;
   }
   if (io_mode == ReadMode) {
      gzfp = gzopen(file_name.c_str(), "r");
      return;
   }
   std::cerr << "E16DST_GZFile : Unknown io_mode = " << io_mode << std::endl;
   exit(1);
}

void E16DST_GZFile::close(){
   gzclose(gzfp);
}

bool E16DST_GZFile::good(){
   return gzfp != NULL;
}

int E16DST_GZFile::write(char *buffer, int size){
   gzwrite(gzfp, buffer, size);
   return size;
}

int E16DST_GZFile::read(char *buffer, int size){
   return gzread(gzfp, buffer, size);
}

//_____________________________________________________________________________
E16DST_ZSTDFile::E16DST_ZSTDFile(){
}

E16DST_ZSTDFile::~E16DST_ZSTDFile(){
}

void E16DST_ZSTDFile::open(std::string file_name, int _io_mode){
   io_mode = _io_mode;
   namespace io = boost::iostreams;
   if (io_mode == WriteMode) {
      ofilter.push(io::zstd_compressor(io::zstd::default_compression, io::default_device_buffer_size));
      ofilter.push(io::file_descriptor_sink(file_name));
      return;
   }
   if (io_mode == ReadMode) {
      ifilter.push(io::zstd_decompressor());
      ifilter.push(io::file_descriptor_source(file_name));
      return;
   }
   std::cerr << "E16DST_ZSTDFile : Unknown io_mode = " << io_mode << std::endl;
   exit(1);
}

void E16DST_ZSTDFile::close(){
   namespace io = boost::iostreams;
   if (io_mode == WriteMode) {
      io::close(ofilter);
      return;
   } else if (io_mode == ReadMode) {
      io::close(ifilter);
      return;
   }
}

bool E16DST_ZSTDFile::good(){
   return true;
}

int E16DST_ZSTDFile::write(char *buffer, int size){
   ofilter.write(buffer, size);
   return size;
}

int E16DST_ZSTDFile::read(char *buffer, int size){
   ifilter.read(buffer, size);
   return ifilter.gcount();
}

//_____________________________________________________________________________
E16DST_MemoryBuffer::E16DST_MemoryBuffer(char *_serialized_data, int _buffer_size) : buffer_size(_buffer_size), serialized_data(_serialized_data), pointer(0) {
   //clear();
}

E16DST_MemoryBuffer::~E16DST_MemoryBuffer(){
}

bool E16DST_MemoryBuffer::good(){
   return serialized_data != NULL;
}

int E16DST_MemoryBuffer::write(char *buffer, int size){ // buffer -> this
   if ((pointer + size) > buffer_size) {
      return 0;
   }
   if (!serialized_data) {
      return -1;
   }
   memcpy(serialized_data + pointer, buffer, size);
   pointer += size;
   return size;
}

int E16DST_MemoryBuffer::read(char *buffer, int size){ // this -> buffer
   if ((pointer + size) > buffer_size) {
      return 0;
   }
   if (!serialized_data) {
      return -1;
   }
   memcpy(buffer, serialized_data + pointer, size);
   pointer += size;
   return size;
}

void E16DST_MemoryBuffer::clear(){
   pointer = 0;
   if (!serialized_data) {
      return;
   }
   memset(serialized_data, 0, buffer_size);
}

