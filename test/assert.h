#pragma once

#define ASSERT(cond) \
   do { \
      if (!(cond)) { \
         std::cerr << "Error in file " << __FILE__ << ":" << __LINE__; \
			std::cerr << " in function " << __func__ << "() => " << #cond << std::endl; \
		} \
   } while(0)

#define ASSERT_EQ(left, right) \
   do { \
      if (!(left == right)) { \
         std::cerr << "Error in file " << __FILE__ << ":" << __LINE__; \
			std::cerr << " in function " << __func__ << "() => " << #left << " != " << #right; \
			std::cerr << "\nwith " << #left << " =\n" << left; \
			std::cerr << "\nand " << #right << " =\n" << right << std::endl; \
		} \
   } while(0)
