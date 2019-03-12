#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>

#include <nt2/include/timing.hpp>

template<typename T>
void* naive_memcpy(T* out, T const* in, std::size_t sz)
{
    for(std::size_t i=0; i != sz; ++i)
        out[i] = in[i];
        
    return out;
}

template<ssize_t Offset, typename T>
void* fast_memcpy_aligned(T* out, T const* in, std::size_t sz)
{
    using namespace nt2::memory;
    static const std::size_t N = nt2::meta::native_cardinal<T>::value;
    
    NT2_ASSERT(is_aligned(sz*sizeof(T)) && is_aligned(in + Offset) && is_aligned(out));
    
    static const std::size_t unroll_size = 1;
	std:size_t rem = (sz/N) % unroll_size;
	std::size_t i = 0;
	for(; i != rem; ++i)
		nt2::store(nt2::load<nt2::simd::pack<T>, Offset>(in, i), out, i);
    for(; i != sz/N; i += unroll_size)
		for(std::size_t j=0; j != unroll_size; ++j)
			nt2::store(nt2::load<nt2::simd::pack<T>, Offset>(in, i+j), out, i+j);
        
    return out;
}

template<typename T>
void* fast_memcpy_aligned(ssize_t offset, T* out, T const* in, std::size_t sz)
{
    #define M0(z,n,t) case n:  return fast_memcpy_aligned<n> (out, in, sz);     \
                      case -n: return fast_memcpy_aligned<-n>(out, in, sz);
    switch(offset)
    {
        case 0:
            return fast_memcpy_aligned<0>(out, in, sz);
            
        BOOST_PP_REPEAT_FROM_TO(1, 32, M0, ~)
        
        default:
            return naive_memcpy(out, in, sz);
    }
    #undef M0
}

template<typename T>
void* fast_memcpy_aligned(T* out, T const* in, std::size_t sz)
{
    return fast_memcpy_aligned<0>(out, in, sz);
}

template<typename T>
void* fast_memcpy(T* out, T const* in, std::size_t sz)
{
    using namespace nt2::memory;
    static const std::size_t N = nt2::meta::native_cardinal<T>::value;
    
    T* orig_out = out;
    
    std::size_t in_diff  = align_on(in)  - in;
    std::size_t out_diff = align_on(out) - out;
    
    naive_memcpy(out, in, out_diff);
    out += out_diff;
    in  += out_diff;
    sz  -= out_diff;
    
    ssize_t offset = out_diff - in_diff;
    std::size_t aligned = sz / N * N;
    fast_memcpy_aligned(
        offset,
        out, in-offset, aligned
    );
    out += aligned;
    in  += aligned;
    sz  -= aligned;
    
    naive_memcpy(out, in, sz);
    return orig_out;
}

extern "C"
{
	void* naive_memcpy(void* dest, void const* src, std::size_t sz)
	{
		return naive_memcpy((char*)dest, (char const*)src, sz);
	}
	
	void* fast_memcpy(void* dest, void const* src, std::size_t sz)
	{
		return fast_memcpy((char*)dest, (char const*)src, sz);
	}
}
