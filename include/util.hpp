#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <cmath>

inline std::string read_file(std::string file_name){

	std::ifstream input_file(file_name);

	if (!input_file.is_open()){
		std::cout << file_name << " could not be opened" << std::endl;
		return "";
	}

	std::stringstream buf;
	buf << input_file.rdbuf();
	input_file.close();
	return buf.str();
}

inline void PrettyPrintUINT64(uint64_t i, std::stringstream* ss) {

	*ss << "[" << std::bitset<15>(i) << "]";
	*ss << "[" << std::bitset<1>(i >> 15) << "]";
	*ss << "[" << std::bitset<8>(i >> 16) << "]";
	*ss << "[" << std::bitset<8>(i >> 24) << "]";
	*ss << "[" << std::bitset<32>(i >> 32) << "]";
}

inline void PrettyPrintUINT64(uint64_t i) {

	std::cout << "[" << std::bitset<15>(i) << "]";
	std::cout << "[" << std::bitset<1>(i >> 15) << "]";
	std::cout << "[" << std::bitset<8>(i >> 16) << "]";
	std::cout << "[" << std::bitset<8>(i >> 24) << "]";
	std::cout << "[" << std::bitset<32>(i >> 32) << "]" << std::endl;
}

inline void DumpLog(std::stringstream* ss, std::string file_name) {
	
	std::ofstream log_file;
	log_file.open(file_name);

	log_file << ss->str();
	log_file.close();
}

#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount _mm_popcnt_u32
#  define __builtin_popcountll _mm_popcnt_u64
#endif

inline int count_bits(int32_t v) {
	return static_cast<int>(__builtin_popcount(v));
}

inline int count_bits(int64_t v) {
	return static_cast<int>(__builtin_popcountll(v));
}

inline void SetBit(int position, char* c) {
	*c |= (uint64_t)1 << position;
}

inline void FlipBit(int position, char* c) {
	*c ^= (uint64_t)1 << position;
}

inline int GetBit(int position, char* c) {
	return (*c >> position) & (uint64_t)1;
}

inline void SetBit(int position, uint64_t* c) {
	*c |= (uint64_t)1 << position;
}

inline void FlipBit(int position, uint64_t* c) {
	*c ^= (uint64_t)1 << position;
}

inline int GetBit(int position, uint64_t* c) {
	return (*c >> position) & (uint64_t)1;
}

inline bool CheckLeafSign(const uint64_t descriptor) {

	uint64_t valid_mask = 0xFF0000;

	// Return true if all 1's, false if contiguous 0's
	if ((descriptor & valid_mask) == valid_mask) {
		return true;
	}
	if ((descriptor & valid_mask) == 0) {
		return false;
	}

	// Error out, something funky
	abort();
}

inline bool CheckContiguousValid(const uint64_t c) {
	uint64_t bitmask = 0xFF0000;
	return (c & bitmask) == bitmask;
}

inline bool IsLeaf(const uint64_t descriptor) {

	uint64_t leaf_mask = 0xFF000000;
	uint64_t valid_mask = 0xFF0000;

	// Check for contiguous valid values of either 0's or 1's
	if (((descriptor & valid_mask) == valid_mask) || ((descriptor & valid_mask) == 0)) {

		// Check for a full leaf mask
		// Only if valid and leaf are contiguous, then it's a leaf
		if ((descriptor & leaf_mask) == leaf_mask)
			return true;
	}
	return false;
}

