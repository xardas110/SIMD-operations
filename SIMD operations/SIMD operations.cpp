#include <iostream>
#include <chrono>
#include <DirectXMath.h>

using namespace DirectX;

int main()
{
	constexpr int n = 32000;
	constexpr int vn = n/4;
	
	float arr1[n];
	float arr2[n];
	float arr3[n];

	XMVECTOR varr1[vn];
	XMVECTOR varr2[vn];
	XMVECTOR varr3[vn];

	__m128 _two = _mm_set1_ps(2);

	for (int i = 0; i< n; i++)
	{
		arr1[i] = (float)(rand() % 40000);
		arr2[i] = (float)(rand() % 40000);
		arr3[i] = (float)(rand() % 40000);
	}

	for (size_t i = 0; i< vn; i++)
	{
		const auto nt = i * 4;
		
		varr1[i] = { arr1[nt], arr1[nt + 1], arr1[nt + 2], arr1[nt + 3] };
		varr2[i] = { arr2[nt], arr2[nt + 1], arr2[nt + 2], arr2[nt + 3] };
		varr3[i] = { arr3[nt], arr3[nt + 1], arr3[nt + 2], arr3[nt + 3] };
	}

	//bevis på at if statements i loop kan vær sikkelig bad pga. unroll, compiler optimization og cpu registers optimization
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++)
	{

		if (arr1[i] == 5000.f)
		{
			arr3[i] = arr1[i];
		}
		else
			arr3[i] = arr1[i] + arr2[i];
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds result = end - start;
    std::cout << result.count();
}
