#include <iostream>
#include "request.pb.h"
#include <fstream>
using namespace std;


int main(){
  
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    request::SearchRequest search;
       
    fstream input("test", ios::in | ios::binary);
    if (!search.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }

      cout<<"query: "<< search.query()<<'\n';
      cout<<"page_number: "<<search.page_number()<<'\n';
      cout<<"result_per_page: "<<search.result_per_page()<<'\n';
       

  return 0;
}
