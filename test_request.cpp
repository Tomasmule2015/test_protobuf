
#include <iostream>
#include <fstream>
#include <string>
#include "request.pb.h"
using namespace std;
typedef int INT32;
typedef long long int INT64;
struct BaseDesc{
	INT64		nBaseID;			   
	std::string	strBaseName;		    
	INT32		nBaseThreashold;		
	INT32		nStatus;			     
	INT32		nLoadMode;			
};

struct FaceFeatDesc{
     INT64 nObjectID;
	INT32 nObjectThreshold;
	INT64 nFeatureID;
	INT32 nFeatureThreashold;
	
};


int CreateProtoString(const BaseDesc* baseDesc,const FaceFeatDesc* facedesc,
	const int baseDescSize ,std::string &strProto,const int inputnum){

     INF::INF_Desc desc;
     
     if(NULL != baseDesc){
     	for(int i = 0; i < baseDescSize;i++){
     		INF::INF_Desc_INF_Base*  base = desc.add_base();
              base->set_nbaseid(baseDesc[i].nBaseID);
              base->set_strbasename(baseDesc[i].strBaseName);
              base->set_nbasethreashold(baseDesc[i].nBaseThreashold);
              base->set_nstatus(baseDesc[i].nStatus);
              base->set_nloadmode(baseDesc[i].nLoadMode);
     	}
     }
     if(NULL != facedesc){
           INF::INF_Desc_INF_Feature* feature = desc.add_feature();
           feature->set_nobjectid(facedesc->nObjectID);
           feature->set_nobjectthreashold(facedesc->nObjectThreshold);
           feature->set_nfeatureid(facedesc->nFeatureID);
           std::cout<<"feature ID: "<<facedesc->nFeatureID<<'\n';
           feature->set_nfeaturethreashold(facedesc->nFeatureThreashold);
     }
     desc.set_inputnum(inputnum);
     


     desc.SerializeToString(&strProto);
     cout<<strProto<<'\n';
     return 0;
}




int main(int argc,char* argv[]){
     GOOGLE_PROTOBUF_VERIFY_VERSION;
    // request::SearchRequest   seacher;
     INF::INF_Desc  search;
     char buffer[40];

     BaseDesc  t_base_1[3];
	t_base_1[0].nBaseID = 1;
     t_base_1[0].strBaseName = "base1";
     t_base_1[0].nBaseThreashold = 50;
     t_base_1[0].nStatus = 1;
     t_base_1[0].nLoadMode = 1; 

     t_base_1[1].nBaseID = 2;
     t_base_1[1].strBaseName = "base2";
     t_base_1[1].nBaseThreashold = 50;
     t_base_1[1].nStatus = 1;
     t_base_1[1].nLoadMode = 1; 
     string str(buffer);

     FaceFeatDesc t_featuredesc_1; 
     t_featuredesc_1.nObjectID = 10;
	t_featuredesc_1.nObjectThreshold = 80;
	t_featuredesc_1.nFeatureID = 1000;
	t_featuredesc_1.nFeatureThreashold = 90;


     CreateProtoString((const BaseDesc*)t_base_1,(const FaceFeatDesc*)&t_featuredesc_1 ,2,str,11);

     search.ParseFromString(str);

     cout<<"Input Num: "<<search.inputnum()<<'\n';

     for(int i = 0; i < search.base_size();i++){
     	INF::INF_Desc_INF_Base base = search.base(i);
     	cout<<"base name: "<<base.strbasename()<<'\n';
     }
     if(0 == search.feature_size()){
     	std::cout<<"feature failed!\n";
     }else{
          INF::INF_Desc_INF_Feature feature = search.feature(0);
     
          std::cout<<"feature id: "<<feature.nfeatureid();
     }

  google::protobuf::ShutdownProtobufLibrary();
  return 0;


}
