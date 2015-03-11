#ifndef NEIGHBORLIST_H
#define NEIGHBORLIST_H

#include <list>
#include <limits>
#include <queue>

using std::list;
using std::priority_queue;

namespace KDTree {

	/**
	 * Class NeighborList
	 * Holds a list of the maxSize nearest neighbors to a point
	 * @tparam	T	the type of neighbor object to store
	 */
	template <class T>
	class NeighborList
	{
		public:
			/**
			 * Construct a new NeighborList
			 * @param size	the maximum number of neighbors to hold
			 */
			NeighborList<T>(int size): maxSize(size) {};

			/**
			 * Check if a given item is a new nearest neighbor.
			 * Add the item to the list of nearest neighbors if true,
			 * do nothing if false.
			 *
			 * @param	newNeighbor	the potential new neighbor
			 * @param	distance	the distance to the new neighbor
			 */
			void testNeighbor(T newNeighbor, double distance) {
				QueueItem newItem(distance, newNeighbor);
				queue.push(newItem);
				if (queue.size() > maxSize) {
					queue.pop();
				}
			}

			/**
			 * Get the list of nearest neighbors.
			 * This resets the stored list of nearest neighbors.
			 * @return list<T> the ordered list of nearest neighbors
			 */
			list<T> getList() {
				list<T> neighborList;

				while (!queue.empty()) {
					neighborList.push_front(queue.top().data);
					queue.pop();
				}
				return neighborList;
			}

			/**
			 * Get the distance of the least nearest neighbor found so far
			 * @return double	the distance to this neighbor
			 */
			double getLargestDistanceSquared() const {
				if (queue.size() == 0) {
					return std::numeric_limits<double>::infinity();
				} else {
					return queue.top().priority;
				}
			}

		private:
			/**
			 * Class QueueItem
			 * A private class to store data with a priority in a queue
			 */
			class QueueItem {
				public:
					/**
					 * Construct a QueueItem
					 * @param priority	the priority of this item in the queue
					 * @param data		the associated data
					 */
					QueueItem(double priority, T data): priority(priority), data(data) {}

					/**
					 * Compare two QueueItems
					 * @param q	another QueueItem to compare
					 * @return bool	true if this item has the lower priority
					 */
					bool operator<(const QueueItem& q) const {
						return priority < q.priority;
					}

					/// The priority of this QueueItem
					double priority;

					/// The data associated with this QueueItem
					T data;
			};

			/// The maximum number of neighbors to store
			unsigned int maxSize;

			/// The priority queue of nearest neighbors
			priority_queue<QueueItem> queue;
	};
}

#endif //NEIGHBORLIST_H
