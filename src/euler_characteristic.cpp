#include "euler_characteristic.h"
#include "edges.h"
#include "igl/edges.h"
#include <unordered_set>;
#include <iostream>

int euler_characteristic(const Eigen::MatrixXi &F)
{
  int Chi = 0;
 
	// Chi = |V| - |E| + |F|

	std::unordered_set<int> vertices;
	for (int i = 0; i < F.rows(); i++) {
		Eigen::RowVectorXi F_row = F.row(i);
		for (int j = 0; j < F_row.size(); j++) {
			if (vertices.count(F(i, j)) == 0) {
				vertices.insert(F(i, j));
			}
		}
	}

	// TEST CODE
	/*std::cout << vertices.size() << std::endl;
	std::cout << F.rows() << std::endl;
	std::cout << edges(F).rows() << std::endl;

	Eigen::MatrixXi E;
	igl::edges(F, E);
	std::cout << E.rows() << std::endl;*/

	Chi = vertices.size() - edges(F).rows() + F.rows();

  return Chi;
}
