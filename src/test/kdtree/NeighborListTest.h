#include <cpptest.h>

#include "kdtree/NeighborList.h"

namespace KDTree {
	class NeighborListTest : public Test::Suite {
		public:
			NeighborListTest() {
				TEST_ADD(NeighborListTest::new_list_largest_distance_is_infinity);
			}

		private:
			void new_list_largest_distance_is_infinity() {
				NeighborList<int> list(5);

				TEST_ASSERT(list.getLargestDistanceSquared() == std::numeric_limits<double>::infinity());
			}
	};
}
