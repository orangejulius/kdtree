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
			 * @param	distanceSquared	the squared distance to the new neighbor
			 */
			void testNeighbor(T newNeighbor, double distanceSquared) {
				if (queue.size() < maxSize || distanceSquared < getLargestDistanceSquared()) {
					QueueItem newItem(distanceSquared, newNeighbor);
					queue.push(newItem);
					if (queue.size() > maxSize) {
						queue.pop();
					}
				}
			}

			/**
			 * Get the list of nearest neighbors.
			 * This resets the stored list of nearest neighbors.
			 * @return list<T> the ordered list of nearest neighbors
			 */
			list<T> getList() const {
				list<T> neighborList;

				priority_queue<QueueItem> queueCopy(queue);

				while (!queueCopy.empty()) {
					neighborList.push_front(queueCopy.top().data);
					queueCopy.pop();
				}
				return neighborList;
			}

			/**
			 * Get the squared distance of the least nearest neighbor found so far
			 * @return double	the squared distance to this neighbor
			 */
			double getLargestDistanceSquared() const {
				if (queue.size() < maxSize) {
					return std::numeric_limits<double>::infinity();
				} else {
					return queue.top().distanceSquared;
				}
			}

		private:
			/**
			 * Class QueueItem
			 * A private class to store NeighborList items
			 * The priority is determined by the squared distance from the search point
			 */
			class QueueItem {
				public:
					/**
					 * Construct a QueueItem
					 * @param distanceSquared	the distance from this point to the search point
					 * @param data		the associated data
					 */
					QueueItem(double distanceSquared, T data): distanceSquared(distanceSquared), data(data) {}

					/**
					 * Compare two QueueItems
					 * @param q	another QueueItem to compare
					 * @return bool	true if this item has the lower distance squared
					 */
					bool operator<(const QueueItem& q) const {
						return distanceSquared < q.distanceSquared;
					}

					/// The distance from this item to the search point
					double distanceSquared;

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
