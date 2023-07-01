/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef RND_SPLITMIX64_H
#define RND_SPLITMIX64_H

#include "rnd_types.h"
#include "rnd_constants.h"

namespace rnd {

	/**
	 * @brief splitmix64 functor a fast PRNG, with 64 bits of state, that can be used to initialize the state of other generators.
	 * It uses a fairly simple algorithm[1] that, though it is considered to be poor for cryptographic purposes, is very fast to calculate.
	 * Considered good enough for "every day"[1] random number needs.
	 * [1] Guy L. Steele, Jr., Doug Lea, and Christine H. Flood. 2014. Fast splittable pseudorandom number generators. In Proceedings of the 2014 ACM International Conference on Object Oriented Programming Systems Languages & Applications (OOPSLA '14). ACM, New York, NY, USA, 453-472. 
	 * @url https://doi.org/10.1145/2660193.2660195
	 * @note It passes several fairly rigorous PRNG "fitness" tests that some more complex algorithms fail..
	 */
	template<uint64_t SEED>
	class splitmix64 {

	public:

		splitmix64() : cummulative_seed(SEED + SPLIT_MIX_MAGIC_INCREMENT) {}

		uint64_t operator()() {
			uint64_t seed = cummulative_seed;
			cummulative_seed = seed + SPLIT_MIX_MAGIC_INCREMENT;
			seed = (seed ^ (seed >> 30)) * SPLIT_MIX_MAGIC_CONSTANT_1;
			seed = (seed ^ (seed >> 27)) * SPLIT_MIX_MAGIC_CONSTANT_2;
			return seed ^ (seed >> 31);
		}

	private:

		uint64_t cummulative_seed;
	};

}

#endif