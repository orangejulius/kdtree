#include <cpptest.h>

#include "kdtree/NearestNeighborSearch.h"

using Eigen::Vector2d;

namespace KDTree {
	class NearestNeighborSearchTest : public Test::Suite {
		public:
			NearestNeighborSearchTest() {
				TEST_ADD(NearestNeighborSearchTest::search_with_one_node_returns_node);
				TEST_ADD(NearestNeighborSearchTest::search_with_two_nodes_returns_closer_node);
				TEST_ADD(NearestNeighborSearchTest::search_traverses_all_nodes_up_to_search_limit);
			}

		private:
			void search_with_one_node_returns_node() {
				PointSplitNode<int, 2> node(2, Vector2d(3, 5));
				NearestNeighborSearch<int, 2> search;
				std::list<int> expected;
				expected.push_back(2);

				std::list<int> results = search.search(node, Vector2d(1, 2));

				TEST_ASSERT(results == expected);
			}

			void search_with_two_nodes_returns_closer_node() {
				PointSplitNode<int, 2> node(1, Vector2d(3, 5));
				PointSplitNode<int, 2> child(2, Vector2d(10, 10));
				node.setRight(&child);
				NearestNeighborSearch<int, 2> search;
				std::list<int> expected;
				expected.push_back(2);

				std::list<int> results = search.search(node, Vector2d(9, 9));

				TEST_ASSERT(results == expected);
			}

			void search_traverses_all_nodes_up_to_search_limit() {
				PointSplitNode<int, 2> node(1, Vector2d(3, 5));
				PointSplitNode<int, 2> child(2, Vector2d(4, 5));
				PointSplitNode<int, 2> child2(3, Vector2d(1, 1));
				PointSplitNode<int, 2> child3(4, Vector2d(2, 3));
				node.setRight(&child);
				node.setLeft(&child2);
				child2.setRight(&child3);
				NearestNeighborSearch<int, 2> search;
				std::list<int> expected;
				expected.push_back(2);
				expected.push_back(1);
				expected.push_back(4);

				std::list<int> results = search.search(node, Vector2d(4, 4), 3);

				TEST_ASSERT(results == expected);
			}
	};
}
