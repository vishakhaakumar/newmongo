#ifndef MOVIES_MICROSERVICES_MOVIEINFOHANDLER_H
#define MOVIES_MICROSERVICES_MOVIEINFOHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <mongoc.h>
#include <bson/bson.h>

#include "../../gen-cpp/MovieInfoService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace movies{

class MovieInfoServiceHandler : public MovieInfoServiceIf {
 public:
  MovieInfoServiceHandler(mongoc_client_pool_t *);
  ~MovieInfoServiceHandler() override=default;

  void GetMoviesByIds(std::vector<std::string>& _return, const std::vector<std::string> & movie_ids) override;
 private:
    mongoc_client_pool_t *_mongodb_client_pool;
};

// Constructor
MovieInfoServiceHandler::MovieInfoServiceHandler(mongoc_client_pool_t *mongodb_client_pool) {
 // Storing the clientpool
       _mongodb_client_pool = mongodb_client_pool;
}

// Remote Procedure "GetMoviesById"

void MovieInfoServiceHandler::GetMoviesByIds(std::vector<std::string>& _return, const std::vector<std::string> & movie_ids) {
    // This is a placeholder, used to confirm that RecommenderService can communicate properly with MovieInfoService
    // Once the MongoDB is up and running, this should return movie titles that match the given ids.
	std::cout << "called hereeeee  here !!!!!!!! ..." << std::endl; 
    // Get mongo client
        mongoc_client_t *mongodb_client = mongoc_client_pool_pop(_mongodb_client_pool);
                if (!mongodb_client) {
              ServiceException se;
                se.errorCode = ErrorCode::SE_MONGODB_ERROR;
                se.message = "Failed to pop a client from MongoDB pool";
                 throw se;
                }

		std::cout << "Mongodb pop pool done here !!!!!!!! ..." << std::endl;

       auto collection = mongoc_client_get_collection(
				         mongodb_client, "movies", "movie-info");

	  if (!collection) {
	          ServiceException se;
	          se.errorCode = ErrorCode::SE_MONGODB_ERROR;
	          se.message = "Failed to create collection user from DB recommender";
	          mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
	          throw se;
		 }

	  std::cout << "Mongodb get coll done here !!!!!!!! ..." << std::endl;

    for (auto &movie_id : movie_ids) {
        _return.push_back("MovieInfoService will provide title for movie with id: " + movie_id);
    }
}

} // namespace movies


#endif //MOVIES_MICROSERVICES_MOVIEINFOHANDLER_H

