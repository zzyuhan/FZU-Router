bool ILP_CheckConnect(const Point& p1, const Point& p2, const bool& flag, const int& net_id) { //check whether the extended 2-pin net can be connected,
	// if it can be, then return true, otherwise, return false
	Point pt;
	if (flag) { // 1  represents first rectilinear then X-architecture
		if (p2.x > p1.x) { //right_top direction
			pt = p2;
			if (p2.x - p1.x < p2.y - p1.y) {
				for (; pt.x > p1.x; --pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
						return false;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
						return false;
					}
				}
			}
			else {
				for (; pt.y > p1.y; --pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
						return false;
					}
				}
				for (; pt.x > p1.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
						return false;
					}
				}
			}
		}
		else { //left_top direction
			pt = p2;
			if (p2.y - p1.y < p1.x - p2.x) {
				for (; pt.y > p1.y; ++pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
						return false;
					}
				}
				for (pt.x = p1.x; pt.x > p2.x + (p2.y - p1.y); --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
						return false;
					}
				}
			}
			else {
				for (; pt.x < p1.x; --pt.y, ++pt.x) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
						return false;
					}
				}
				for (; pt.y > p1.y; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
						return false;
					}
				}
			}
		}
	}
	else { // 0 represents first X-architecture then rectilinear
		if (p2.x > p1.x) { //right_top direction
			pt = p2;
			if (p2.x - p1.x < p2.y - p1.y) {
				for (; pt.y > p1.y + p2.x - p1.x; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
						return false;
					}
				}
				for (; pt.y > p1.y; --pt.y, --pt.x) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
						return false;
					}
				}
			}
			else {
				for (; pt.x > p1.x + p2.y - p1.y; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
						return false;
					}
				}
				for (; pt.y > p1.y; --pt.y, --pt.x) {
					int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
						return false;
					}
				}
			}
		}
		else { // left_top direction
			if (p2.y - p1.y < p1.x - p2.x) {
				pt.y = p2.y;
				pt.x = p1.x - (p2.y - p1.y);
				for (; pt.x > p2.x; --pt.x) {
					int num = pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
						return false;
					}
				}
				pt.y = p2.y;
				pt.x = p1.x - (p2.y - p1.y);
				for (; pt.x < p1.x; ++pt.x, --pt.y) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
						return false;
					}
				}
			}
			else {
				for (pt = p2; pt.y > p1.y + p1.x - p2.x; --pt.y) {
					int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
						return false;
					}
				}
				for (; pt.x < p1.x; --pt.y, ++pt.x) {
					int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
					if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
						&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool ILP_CheckConnect2(const Point& p1, const Point& p2, const bool& flag, const int& net_id) { //check whether the extended 2-pin net can be connected,
	// if it can be, then return true, otherwise, return false
	Point pt, pt1, pt2;
	if (flag) { // 1 represents down or left
		if (p2.x == p1.x) { //left direction
			if ((p1.y + p2.y) % 2 == 0){
				if ((p1.x - (p2.y - p1.y) / 2) >= 0){
					pt = p1;
					for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
							return false;
						}
					}
					pt = p2;
					for (; pt.x > (p1.x - (p2.y - p1.y) / 2); --pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x > 0; --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
			}
			else{
				if ((p1.x - (p2.y - p1.y) / 2) >= 0){
					pt1 = p1;
					for (; pt1.x > (p1.x - (p2.y - p1.y) / 2); --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x > 0; --pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x < p1.x; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
			}
		}
		else { //down direction
			if ((p1.x + p2.x) % 2 == 0){
				if ((p1.y - (p2.x - p1.x) / 2) >= 0){
					pt = p1;
					for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.y, ++pt.x) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
							return false;
						}
					}
					pt = p2;
					for (; pt.y > (p1.y - (p2.x - p1.x) / 2); --pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y > 0; --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
			}
			else{
				if ((p1.y - (p2.x - p1.x) / 2) >= 0){
					pt1 = p1;
					for (; pt1.y > (p1.y - (p2.x - p1.x) / 2); --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y > 0; --pt1.y, ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][1] + 1 > maxline[pt1.y * X_MAX + pt1.x][1]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y < p1.y; ++pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][3] + 1 > maxline[pt2.y * X_MAX + pt2.x][3]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
			}
		}
	}
	else { // 0 repsents up or right
		if (p2.x == p1.x) { //right direction
			if ((p1.y + p2.y) % 2 == 0){
				if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
					pt = p1;
					for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
							return false;
						}
					}
					pt = p2;
					for (; pt.x < (p1.x + (p2.y - p1.y) / 2); ++pt.x, --pt.y) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
			}
			else{
				if ((p1.x + (p2.y - p1.y) / 2) <= X_MAX){
					pt1 = p1;
					for (; pt1.x < (p1.x + (p2.y - p1.y) / 2); ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.x < X_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.x > p1.x; --pt2.x, ++pt2.y) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.y < p2.y; ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 2 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][2] + 1 > maxline[pt1.y * X_MAX + pt1.x][2]) {
							return false;
						}
					}
				}
			}
		}
		else { //up direction
			if ((p1.x + p2.x) % 2 == 0){
				if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
					pt = p1;
					for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.x, ++pt.y) {
						int num = pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][3] + 1 > maxline[pt.y * X_MAX + pt.x][3]) {
							return false;
						}
					}
					pt = p2;
					for (; pt.y < (p1.y + (p2.x - p1.x) / 2); ++pt.y, --pt.x) {
						int num = pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt.y * X_MAX + pt.x][1] + 1 > maxline[pt.y * X_MAX + pt.x][1]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
			}
			else{
				if ((p1.y + (p2.x - p1.x) / 2) <= Y_MAX){
					pt1 = p1;
					for (; pt1.y < (p1.y + (p2.x - p1.x) / 2); ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
				else{
					pt1 = p1;
					for (; pt1.y < Y_MAX; ++pt1.x, ++pt1.y) {
						int num = pt1.y * X_MAX + pt1.x + 3 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][3] + 1 > maxline[pt1.y * X_MAX + pt1.x][3]) {
							return false;
						}
					}
					pt2 = pt1;
					for (; pt2.y > p1.y; --pt2.y, ++pt2.x) {
						int num = pt2.y * X_MAX + pt2.x + 1 * X_MAX * Y_MAX;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt2.y * X_MAX + pt2.x][1] + 1 > maxline[pt2.y * X_MAX + pt2.x][1]) {
							return false;
						}
					}
					pt1 = pt2;
					for (; pt1.x < p2.x; ++pt1.x) {
						int num = pt1.y * X_MAX + pt1.x;
						if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
							&& record_p[pt1.y * X_MAX + pt1.x][0] + 1 > maxline[pt1.y * X_MAX + pt1.x][0]) {
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}
bool ILP_CheckConnect3(const Point& p1, const Point& p2, const bool& flag, const int& net_id) { //check whether the extended 2-pin net can be connected,
	// if it can be, then return true, otherwise, return false
	Point pt;
	if (flag) { // 1  represents horizontal then vertical
		if (p1.x < p2.x){//right-top
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
					return false;
				}
			}
			for (; pt.x > p1.x; --pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
					return false;
				}
			}
		}
		else{//left-top
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
					return false;
				}
			}
			for (; pt.x < p1.x; ++pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
					return false;
				}
			}
		}
	}
	else { // 0 represents first vertical then horizontal
		if (p1.x < p2.x){//right-top
			for (; pt.x > p1.x; --pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
					return false;
				}
			}
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
					return false;
				}
			}
		}
		else{//left-top
			for (; pt.x < p1.x; ++pt.x) {
				int num = pt.y * X_MAX + pt.x;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][0] + 1 > maxline[pt.y * X_MAX + pt.x][0]) {
					return false;
				}
			}
			for (; pt.y > p1.y; --pt.y) {
				int num = pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX;
				if (line_net[net_id].point_edge.find(num) == line_net[net_id].point_edge.end()
					&& record_p[pt.y * X_MAX + pt.x][2] + 1 > maxline[pt.y * X_MAX + pt.x][2]) {
					return false;
				}
			}

		}
	}
	return true;
}
