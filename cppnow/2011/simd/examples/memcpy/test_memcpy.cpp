#include <nt2/include/timing.hpp>
#include <iostream>

#ifdef MEMCPY_INLINE
#include "memcpy.cpp"
#else
extern "C"
{
	void* naive_memcpy(void* dest, void const* src, std::size_t sz);
	void* fast_memcpy(void* dest, void const* src, std::size_t sz);
}
#endif

typedef void* (*memcpy_fn)(void*, void const*, std::size_t);
void bench(char const* name, memcpy_fn fn, char* buffer_out, char const* buffer_in, std::size_t N)
{
	nt2::ctic();
	time_t t = time(0);
	double cycles = 1/0.;
	do
	{
		nt2::ctic();
		fn(buffer_out, buffer_in, N);
		double new_cycles = nt2::ctoc(false) / (N*1.);
		if(new_cycles < cycles)
			cycles = new_cycles;
	}
	while( (time(0)-t) < 5);
	std::cout << name << ": " << cycles << " (best)" << std::endl;
	
	for(std::size_t i=0; i!=N; ++i)
    {
        if(buffer_out[i] != char(i))
        {
            std::cout << "Invalid!" << std::endl;
            break;
        }
    }
}

int main()
{
    const std::size_t N = 1024*1024+42;
    void* p1 = std::malloc(N + 100);
    void* p2 = std::malloc(N + 100);
    
    char* buffer_in  = (char*)p1 + 11;
    char* buffer_out = (char*)p2 + 5;
    
    for(std::size_t i=0; i!=N; ++i)
        buffer_in[i] = char(i);
    
    bench("naive_memcpy", naive_memcpy, buffer_out, buffer_in, N);
    bench("fast_memcpy",  fast_memcpy,  buffer_out, buffer_in, N);
    bench("std::memcpy",  std::memcpy,  buffer_out, buffer_in, N);
}
