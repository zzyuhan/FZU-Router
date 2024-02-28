//used to check whether the new added edge violates the constraint of maximal capacity. If can add, reture true.
bool CheckP2P(const int& i, const Point& p1, const Point& p2) //aps
{
	Point pt;
	if (p1.x == p2.x) { //x coordinates equal
		for (pt = p2; pt.y > p1.y; --pt.y) {
			if (line_net[i].point_edge.find(pt.y * X_MAX + pt.y + 2 * X_MAX * Y_MAX) == line_net[i].point_edge.end()
				&& record_p[pt.y * X_MAX + pt.x][2] + 1 > (maxline[pt.y * X_MAX + pt.x][2] / 2)) {
				return false;
			}
		}
	}
	else if (p1.y == p2.y) { //y coordinates equal
		for (pt = p2; pt.x > p1.x; --pt.x) {
			if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX) == line_net[i].point_edge.end()
				&& record_p[pt.y * X_MAX + pt.x][0] + 1 > (maxline[pt.y * X_MAX + pt.x][0] / 2)) {
				return false;
			}
		}
	}
	else if (p2.x - p1.x == p2.y - p1.y) { //right-top direction
		for (pt = p2; pt.y > p1.y; --pt.y, --pt.x) {
			if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX) == line_net[i].point_edge.end()
				&& record_p[pt.y * X_MAX + pt.x][1] + 1 > (maxline[pt.y * X_MAX + pt.x][1] * 1)) {
				return false;
			}
		}
	}
	else if (p2.y - p1.y == p1.x - p2.x) { //left-top direciton
		for (pt = p2; pt.x < p1.x; ++pt.x, --pt.y) {
			if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX) == line_net[i].point_edge.end()
				&& record_p[pt.y * X_MAX + pt.x][3] + 1 >(maxline[pt.y * X_MAX + pt.x][3] * 1)) {
				return false;
			}
		}
	}
	return true;
}