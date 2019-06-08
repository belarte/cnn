#pragma once

#include<sstream>

#define ASSERT(cond) \
   do { \
      if (!(cond)) { \
			std::ostringstream oss; \
         oss << "Error in file " << __FILE__ << ":" << __LINE__; \
			oss << " in function " << __func__ << "() => " << #cond << std::endl; \
			throw std::runtime_error(oss.str()); \
		} \
   } while(0)

#define ASSERT_EQ(left, right) \
   do { \
		if (!(left == right)) { \
			std::ostringstream oss; \
			oss << std::string( __FILE__ ); \
			oss << std::string( ":" ); \
			oss << std::to_string( __LINE__ ); \
			oss << std::string( " in " ); \
			oss << std::string( __PRETTY_FUNCTION__ ); \
			oss << std::string( ": " ); \
			oss << left; \
			oss << std::string( " != " ); \
			oss << right; \
			throw std::runtime_error(oss.str()); \
		} \
   } while(0)
