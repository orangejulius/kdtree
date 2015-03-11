#include <cpptest.h>

#include "kdtree/NeighborList.h"

namespace KDTree {
	class NeighborListTest : public Test::Suite {
		public:
			NeighborListTest() {
				TEST_ADD(NeighborListTest::new_list_largest_distance_is_infinity);
				TEST_ADD(NeighborListTest::list_with_one_item_has_largest_distance_squared);
				TEST_ADD(NeighborListTest::list_with_two_items_has_appropriate_largest_distance_squared);
				TEST_ADD(NeighborListTest::full_list_not_affected_by_testing_further_neighbor);
				TEST_ADD(NeighborListTest::full_list_updates_largest_distance_appropriately);
				TEST_ADD(NeighborListTest::new_neighbor_list_returns_empty_list);
				TEST_ADD(NeighborListTest::one_item_list_returned_correctly);
				TEST_ADD(NeighborListTest::get_list_is_non_destructive);
				TEST_ADD(NeighborListTest::get_list_returns_items_ordered_by_distance);
				TEST_ADD(NeighborListTest::get_list_returns_only_the_correct_items);
			}

		private:
			void new_list_largest_distance_is_infinity() {
				NeighborList<int> list(5);

				TEST_ASSERT(list.getLargestDistanceSquared() == std::numeric_limits<double>::infinity());
			}

			void list_with_one_item_has_largest_distance_squared() {
				NeighborList<int> list(3);

				list.testNeighbor(5, 10.0);

				TEST_ASSERT(list.getLargestDistanceSquared() == 10.0);
			}

			void list_with_two_items_has_appropriate_largest_distance_squared() {
				NeighborList<int> list(3);

				list.testNeighbor(1, 10.0);
				list.testNeighbor(2, 12.0);

				TEST_ASSERT(list.getLargestDistanceSquared() == 12.0);
			}

			void full_list_not_affected_by_testing_further_neighbor() {
				NeighborList<int> list(2);

				list.testNeighbor(1, 10.0);
				list.testNeighbor(2, 12.0);
				list.testNeighbor(3, 14.0);

				TEST_ASSERT(list.getLargestDistanceSquared() == 12.0);
			}

			void full_list_updates_largest_distance_appropriately() {
				NeighborList<int> list(2);

				list.testNeighbor(1, 10.0);
				list.testNeighbor(2, 12.0);
				list.testNeighbor(3, 11.0);

				TEST_ASSERT(list.getLargestDistanceSquared() == 11.0);
			}

			void new_neighbor_list_returns_empty_list() {
				NeighborList<int> list(2);

				std::list<int> empty_result_list;
				TEST_ASSERT(list.getList() == empty_result_list);
			}

			void one_item_list_returned_correctly() {
				NeighborList<int> list(2);
				std::list<int> result_list;
				result_list.push_back(5);

				list.testNeighbor(5, 10.0);

				TEST_ASSERT(list.getList() == result_list);
			}

			void get_list_is_non_destructive() {
				NeighborList<int> list(2);
				std::list<int> result_list;
				result_list.push_back(5);

				list.testNeighbor(5, 10.0);
				list.getList();

				TEST_ASSERT(list.getList() == result_list);
			}

			void get_list_returns_items_ordered_by_distance() {
				NeighborList<int> list(3);
				std::list<int> result_list;
				result_list.push_back(1);
				result_list.push_back(2);
				result_list.push_back(3);

				list.testNeighbor(1, 1.0);
				list.testNeighbor(3, 3.0);
				list.testNeighbor(2, 2.0);

				TEST_ASSERT(list.getList() == result_list);
			}

			void get_list_returns_only_the_correct_items() {
				NeighborList<int> list(3);
				std::list<int> result_list;
				result_list.push_back(1);
				result_list.push_back(2);
				result_list.push_back(3);

				list.testNeighbor(1, 1.0);
				list.testNeighbor(3, 3.0);
				list.testNeighbor(4, 4.0);
				list.testNeighbor(2, 2.0);

				TEST_ASSERT(list.getList() == result_list);
			}
	};
}
