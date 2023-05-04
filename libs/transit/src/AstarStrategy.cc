#include "AstarStrategy.h"
#include "routing/astar.h"
using namespace std;

AstarStrategy::AstarStrategy(Vector3 pos, Vector3 des,
                             const routing::IGraph* g) {
  std::vector<float> start = {pos[0], pos[1], pos[2]};
  std::vector<float> end   = {des[0], des[1], des[2]};

  // cout << "p0:" << pos[0] << endl;
  // cout << "p1:" << pos[1] << endl;
  // cout << "p2:" << pos[2] << endl;
  
  // cout << "d0:" << des[0] << endl;
  // cout << "d1:" << des[1] << endl;
  // cout << "d2:" << des[2] << endl;

  // cout << g << endl;
  cout << "before get path" << endl;
  path = g->GetPath(start, end, AStar::Default());
  cout << "after get path" << endl;

}
