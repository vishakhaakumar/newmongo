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
  void GetMoviesByTitle(std::vector<std::string> & _return, const std::string& movie_string) override;
 private:
    mongoc_client_pool_t *_mongodb_client_pool;
};

// Constructor
MovieInfoServiceHandler::MovieInfoServiceHandler(mongoc_client_pool_t *mongodb_client_pool) {
 // Storing the clientpool
       _mongodb_client_pool = mongodb_client_pool;
}
	
 void MovieInfoServiceHandler::GetMoviesByTitle(std::vector<std::string> & _return, const std::string& movie_string){
     _return = "By title here";	
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
		bson_t *movie_doc = bson_new();
          	//BSON_APPEND_UTF8(movie_doc, "movie_id", movie_id);
	  	//BSON_APPEND_UTF8(movie_doc, "movie_name", "Batman");
	  	  BSON_APPEND_INT64(movie_doc, "movie_id", 123);
		  BSON_APPEND_UTF8(movie_doc, "title", "Batman");

		   std::cout << "data title insert done !!!!!!! ..." << std::endl;

  	  	bson_error_t error;
	        bool movieinsert = mongoc_collection_insert_one (collection, movie_doc, nullptr, nullptr, &error);

		std::cout << "Mongodb after insert here !!!!!!!! ..." << std::endl;

		 bson_t *movie_doc1 = bson_new();
		 BSON_APPEND_INT64(movie_doc1, "movie_id", 456);
                 BSON_APPEND_UTF8(movie_doc1, "title", "Spiderman");
                 std::cout << "data title2 insert done !!!!!!! ..." << std::endl;

	         bool movieinsert1 = mongoc_collection_insert_one (collection, movie_doc1, nullptr, nullptr, &error);

		 std::cout << "Mongodb after insert2 here !!!!!!!! ..." << std::endl;

						  
    if (!movieinsert||!movieinsert1) {
            // LOG(error) << "Failed to insert Movies for " << std::to_string(movie_id) << " to MongoDB: " << error.message;
              ServiceException se;
               se.errorCode = ErrorCode::SE_MONGODB_ERROR;
               se.message = error.message;
               bson_destroy(movie_doc);
             //  mongoc_cursor_destroy(cursor);
             //  mongoc_collection_destroy(collection);
               //mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
               throw se;
           }
          bson_destroy(movie_doc);

	  std::cout << "Mongodb after destroy done here !!!!!!!! ..." << std::endl;
	}

	  bson_t *query = bson_new();
          BSON_APPEND_INT64(query, "movie_id", 123);

          mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, nullptr, nullptr);
          const bson_t *doc;
          bool found = mongoc_cursor_next(cursor, &doc);

	  if (found) {
	         std::cout << "data founddddddddddd yayayayayayyaayyy !!!!!!!! ..." << std::endl;
              //  se.message = "User ID " + std::to_string(user_id) + " already existed in MongoDB Recommender";
	      auto movietitle_json_char = bson_as_json(doc, nullptr);
	      json movietitle_json = json::parse(movietitle_json_char);
	       for (auto &titlev : movietitle_json["title"]) {
		       std::cout << "movie found is ------>>>>  !!!!!!! ..."<< titlev <<" this " << std::endl;
	                 _return.push_back(titlev);
		        }
	      //std::cout << "movie found is ------>>>>  !!!!!!! ..."<< title <<" this " << std::endl;     	   
              // _return.push_back(title);
	        mongoc_cursor_destroy(cursor);
	      //  mongoc_collection_destroy(collection);
	        mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
	        //throw se;
	     }else {
		 for (auto &movie_id : movie_ids) {
		 _return.push_back("MovieInfoService will provide title for movie with id: " + movie_id);
		 }
	     }
	  std::cout << "Mongodb after query done 111 here !!!!!!!! ..." << std::endl;

    //for (auto &movie_id : movie_ids) {
      //  _return.push_back("MovieInfoService will provide title for movie with id: " + movie_id);
    //}
}

} // namespace movies


#endif //MOVIES_MICROSERVICES_MOVIEINFOHANDLER_H

