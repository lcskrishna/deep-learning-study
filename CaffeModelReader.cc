#include <iostream>
#include <fstream>
#include <string>
#include "../output/caffe.pb.h"

using namespace std;

void formNetworkDetails(const caffe::NetParameter& netParameter){

  //Get Name Parameter.
   if(netParameter.has_name()){
     cout<<"Net Parameter Name is : " << netParameter.name()<< endl;
   }
   
  //Check if there are any Input Sizes given.
   int inputSize= netParameter.input_size();
   for(int i=0;i<inputSize;i++){
	cout<<"Net Parameter input : "<< i << " is: " << netParameter.input(i) << endl; 
   }

  //Check for the Blob Shapes.
   int blobShapeSize= netParameter.input_shape_size();
   for(int i=0;i<blobShapeSize;i++){
      const caffe::BlobShape& blobShape = netParameter.input_shape(i);

      for(int j=0;j<blobShape.dim_size();j++){
	cout<<"Dimension of BlobShape Param : "<< i << blobShape.dim(j)<< endl;
      }
   }

 //Check for Input Dimensions.
   int inputDimSize = netParameter.input_dim_size();
   for(int i=0;i<inputDimSize;i++){
       cout<< "Input Dim Size " << i << " is :" << netParameter.input_dim(i);
   }

 //Check for the NetState.
   if(netParameter.has_state()){
     const caffe::NetState& netState= netParameter.state();
     cout<< "Netstate stage is : " << netState.stage() << endl;
   }

 //Access Layer Parameters.
   int layerParameterSize = netParameter.layer_size();
   for(int i=0;i<1;i++){
	const caffe::LayerParameter& layerParameter= netParameter.layer(i);
        //Layer Name.
        if(layerParameter.has_name()){
           cout<<"Layer "<<i << " name : "<<layerParameter.name() << endl;
        }

	//Layer Type.
        if(layerParameter.has_type()){
           cout<< " Layer " << i << " type: "<< layerParameter.type() << endl;
        }

        //Name of the Bottom Layer.
        for(int j=0;j< layerParameter.bottom_size();j++){
          cout<<"Layer " << i << "Bottom Layer "<< j << " is: " << layerParameter.bottom(j) << endl;
        }

        //Name of the Top Layers.
        for(int j=0; j< layerParameter.top_size();j++){
          cout<<"Layer " << i << "Top Layers "<< j << " is : " << layerParameter.top(j) << endl;
        }

        
   }
       
    
}

  
   

} 


int main(int argc, char* argv[]){
    
  //Verify the Google Protobuf Version.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  caffe::NetParameter netParameter;

  //Read the Data.
  {
    fstream input(argv[1], ios::in| ios::binary);
    bool isSuccess = netParameter.ParseFromIstream(&input);
    if(isSuccess){
      cout<<"CaffeModel Read Succeeded" << endl;
      formNetworkDetails(netParameter);
    }else{
      cerr<<"CaffeModel Read Failed" << endl;
    }    
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
    
}
