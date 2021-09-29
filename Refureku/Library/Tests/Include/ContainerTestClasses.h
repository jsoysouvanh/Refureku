#pragma once

#include <iostream>	//std::ostream, std::cout, std::endl
#include <cstddef>	//std::size_t

class HugeClass
{
	private:
		static inline std::size_t _instanceCount = 0;
		std::size_t	_array[20];
		int _i = -1;

	public:
		HugeClass() noexcept:
			_array{},
			_i{0}
		{
			_instanceCount++;
			//std::cout << "HugeClass()" << std::endl;
		}

		HugeClass(int i) noexcept:
			_array{},
			_i{i}
		{
			_instanceCount++;
			//std::cout << "HugeClass(int i)" << std::endl;
		}

		HugeClass(HugeClass const& other) noexcept:
			_array{},
			_i{other._i}
		{
			_instanceCount++;
			//std::cout << "HugeClass(HugeClass const&)" << std::endl;
		}

		HugeClass(HugeClass&& other) noexcept:
			_array{},
			_i{other._i}
		{
			//std::cout << "HugeClass(HugeClass&&)" << std::endl;
		}

		~HugeClass() noexcept
		{
			_instanceCount--;
			//std::cout << "~HugeClass()" << std::endl;
		}

		static std::size_t getInstanceCount() noexcept { return _instanceCount; }
		int getI() const noexcept { return _i; }
};

struct CopyOnly
{
	CopyOnly() = default;
	CopyOnly(CopyOnly const&) { /*std::cout << "CopyOnly(CopyOnly const&)" << std::endl;*/ }
	CopyOnly(CopyOnly&&) = delete;
	~CopyOnly() = default;
};

struct MoveOnly
{
	MoveOnly() = default;
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly(MoveOnly&&) { /*std::cout << "MoveOnly(MoveOnly&&)" << std::endl;*/ }
	~MoveOnly() = default;
};

struct NotCopyNorMove
{
	NotCopyNorMove() = default;
	NotCopyNorMove(NotCopyNorMove const&) = delete;
	NotCopyNorMove(NotCopyNorMove&&) = delete;
	~NotCopyNorMove() = default;
};

std::ostream& operator<<(std::ostream& stream, HugeClass const& c) noexcept
{
	stream << c.getI();
	return stream;
}