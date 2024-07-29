#include "fixed_conversions.h"

namespace math {

	namespace fixed {

		Q10_6_t saturate(int32_t n) {
			if (n > Q_INFINITY) return Q_INFINITY;
			if (n < Q_NINFINITY) return Q_NINFINITY;
			return (Q10_6_t)n;
		}

		UQ10_6_t saturate(uint32_t n) {
			if (n > UQ_INFINITY) return UQ_INFINITY;
			return (UQ10_6_t)n;
		}

	}

}