#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <signal.h>

#include "../utils.h"
#include "../utils_mongodb.h"
#include "MovieInfoHandler.h"

using json = nlohmann::json;
using apache::thrift::server::TThreadedServer;
using apache::thrift::transport::TServerSocket;
using apache::thrift::transport::TFramedTransportFactory;
using apache::thrift::protocol::TBinaryProtocolFactory;

using namespace movies;


// signal handler code
void sigintHandler(int sig) {
	exit(EXIT_SUCCESS);
}

// entry of this service
int main(int argc, char **argv) {
  // 1: notify the singal handler if interrupted
  signal(SIGINT, sigintHandler);
  // 1.1: Initialize logging
  init_logger();


  // 2: read the config file for ports and addresses
  json config_json;
  if (load_config_file("config/service-config.json", &config_json) != 0) {
    exit(EXIT_FAILURE);
  }

  // 3: get my port
  int my_port = config_json["movie-info-service"]["port"];

// Get mongodb client pool
   mongoc_client_pool_t* mongodb_client_pool =
   init_mongodb_client_pool(config_json, "movies", 128);
        	 
 	 	 std::cout << "Mongodb client pool done ..." << std::endl;
   	 	   if (mongodb_client_pool == nullptr) {
	 	        return EXIT_FAILURE;
    	          }
   	 	            
 
	   std::cout << "Mongodb before client pop 11..." << std::endl;
    
   mongoc_client_t *mongodb_client = mongoc_client_pool_pop(mongodb_client_pool);
      if (!mongodb_client) {
          LOG(fatal) << "Failed to pop mongoc client";
	        return EXIT_FAILURE;
	    }
      std::cout << "Mongodb before client pop 22..." << std::endl;

       mongoc_client_pool_push(mongodb_client_pool, mongodb_client);
	std::cout << "Mongodb client push done ..." << std::endl;

			
  // 4: configure this server
  TThreadedServer server(
      std::make_shared<MovieInfoServiceProcessor>(
      std::make_shared<MovieInfoServiceHandler>(mongodb_client_pool)),
      std::make_shared<TServerSocket>("0.0.0.0", my_port),
      std::make_shared<TFramedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>()
  );
  
  // 5: start the server
  std::cout << "Starting the movie info server ..." << std::endl;
  server.serve();
  return 0;
}

