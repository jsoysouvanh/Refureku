#pragma once

#if __has_include(<optional>)
	#include <optional>
	namespace opt = std;
#elif __has_include(<experimental/optional>)
	#include <experimental/optional>
	namespace opt = std::experimental;
#else
	#error "No optional support"
#endif