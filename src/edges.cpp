#include "edges.h"
#include <unordered_set>
#include <unordered_map>

typedef std::unordered_set<int> edge_set;

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
  
  
	// Idea: use a map.
  // - Assuming F is an |F| by 3 matrix, we know that there are 3 edges in a face
  
	std::unordered_map<int, edge_set> edges;
	int num_edges = 0;

	for (int i = 0; i < F.rows(); i++) {

		Eigen::RowVectorXi F_row = F.row(i);
		assert(F_row.size() == 3);

		

		// Traverse through the edges on the face, and add them into the edgeSet
		for (int j = 0; j < 3; j++) {

			// Need to check both directed edges, since we only want undirected edges
			int v1 = F_row(j);
			int v2 = F_row((j + 1) % 3);
			if (edges.count(v1) > 0 || edges.count(v2) > 0) {
				if (edges.count(v1) > 0 && edges[v1].count(v2) > 0) {
					continue;
				}
				else if (edges.count(v2) > 0 && edges[v2].count(v1) > 0) {
					continue;
				}
				else {
					edges[v1].insert(v2);
					num_edges++;
				}
			}
			else {
				edges[v1].insert(v2);
				num_edges++;
			}
		}
  }

	Eigen::MatrixXi E(num_edges, 2);
	int i = 0;
	std::unordered_map<int, edge_set>::iterator edgeSet;
	for (edgeSet = edges.begin(); edgeSet != edges.end(); edgeSet++) {
		int v1 = (*edgeSet).first;
		for (edge_set::iterator v2 = (*edgeSet).second.begin(); v2 != (*edgeSet).second.end(); v2++, i++) {
			
			E(i, 0) = v1;
			E(i, 1) = (*v2);
		}
	}
  
  return E;
}
