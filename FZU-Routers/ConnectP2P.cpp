//use to connect two pins by rectilinear line
void ConnectP2P(const int& i, const Point& p1, const Point& p2, bool flag_to_plus = true) {
    Point pt;
	//if (p2 < p1)	swap(p1, p2);
	double tmp = totalwl;
	double sq2 = sqrt(2.0);
    if (p1.x == p2.x) { //x coordinates equal //p2 at the top of p1
        for (pt = p2; pt.y > p1.y; --pt.y) {
            if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX) == line_net[i].point_edge.end()) {
                ++record_p[pt.y * X_MAX + pt.x][2];
                line_net[i].point_edge.insert(pt.y * X_MAX + pt.x + 2 * X_MAX * Y_MAX);
                totalwl += 1.0;
				
            }
        }netvnum++;
    } else if (p1.y == p2.y) { //ycoordinates equal //p2 at the right of p1
        for (pt = p2; pt.x > p1.x; --pt.x) {
            if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX) == line_net[i].point_edge.end()) {
                ++record_p[pt.y * X_MAX + pt.x][0];
                line_net[i].point_edge.insert(pt.y * X_MAX + pt.x + 0 * X_MAX * Y_MAX);
                totalwl += 1.0;
				
            }
        }nethnum++;
    } else if (p2.x - p1.x == p2.y - p1.y) { //p2 at the right-top of p1
        for (pt = p2; pt.y > p1.y; --pt.y, --pt.x) {
            if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX) == line_net[i].point_edge.end()) {
                ++record_p[pt.y * X_MAX + pt.x][1];
                line_net[i].point_edge.insert(pt.y * X_MAX + pt.x + 1 * X_MAX * Y_MAX);
                totalwl += sq2;
				
            }
        }netx45num++;
    } else if (p2.y - p1.y == p1.x - p2.x) { //p2 at the left-top of p1
        for (pt = p2; pt.x < p1.x; ++pt.x, --pt.y) {
            if (line_net[i].point_edge.find(pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX) == line_net[i].point_edge.end()) {
                ++record_p[pt.y * X_MAX + pt.x][3];
                line_net[i].point_edge.insert(pt.y * X_MAX + pt.x + 3 * X_MAX * Y_MAX);
                totalwl += sq2;
				
            }
        }netx135num++;
    }
	if (!flag_to_plus)
		totalwl = tmp;
}