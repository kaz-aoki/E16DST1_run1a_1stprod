//2022-05-06, uploaded by yokkaich
//E16ANA_MockTrackOutputData.cc 220504 by S. Yokkaichi
//    Last modified at <2022-05-04 21:37:48 >


#include "E16ANA_ErrorMessage.hh"

#include "E16ANA_MockTrackOutputData.hh"

E16ANA_MockTrackOutputData::~E16ANA_MockTrackOutputData(){
  if( fpRead != NULL){    fclose(fpRead);     }
  if( fpWrite != NULL){      fclose(fpWrite); }
}
  

int E16ANA_MockTrackOutputData::CloseReadFile(){
  fclose(fpRead); fpRead=NULL;
  return 0;
}
int E16ANA_MockTrackOutputData::CloseWriteFile(){
  fclose(fpWrite); fpWrite=NULL;
  return 0;
}

int E16ANA_MockTrackOutputData::OpenReadFile(const char* filename){
  if( fpRead != NULL ){
    E16FATAL("file is already opened for reading: %s",filename);
    return OpenERROR;
  }

  fpRead = fopen(filename, "r");

  if ( fpRead==NULL ){
    E16FATAL("file open error for reading: %s",filename);
    return OpenERROR;
  }
  return OK;
}

int E16ANA_MockTrackOutputData::OpenWriteFile(const char* filename){
  if( fpWrite != NULL ){
    E16FATAL("file is already opened for writing: %s",filename);
    return OpenERROR;
  }

  fpWrite = fopen(filename, "w");

  if ( fpWrite==NULL ){
    E16FATAL("file open error for writing: %s",filename);
    return OpenERROR;
  }
  return OK;
}
