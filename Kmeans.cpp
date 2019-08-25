#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Kmeans {
public:
	class Point {
	public:
		int x, y, label;
		double distance;

		Point(){
			x = y = label = 0;
			distance = 9999;
		}
	};
	int k, numPts, numRow, numCol, minVal, maxVal, **imgArr, change;
	Point *ptSet, *kCentroids;

	Kmeans(int r, int c, int mi, int mx, int kVal, int pts, int **arr){
		change = 0;
		kCentroids = new Point[kVal+1];
		imgArr = arr;
		k = kVal;
		numPts = pts;
		numRow = r;
		numCol = c;
		minVal = mi;
		maxVal = mx;
		ptSet = NULL;
	}

	void kMeanClustering(ofstream &out2){
		int iter = 1;
		assignLabel(); // partitioning of points (randomize labels)

		do{
			pt2Img(); // give the image (points) labels
			out2 << "*** Result of iteration " << iter << " ****\n";
			out2 << "https://github.com/jevangelista0" << '\n';
			printImg(out2); // already in pt2Img

			change = 0; // reset to 0 because distanceMinLabel() will check if there are more changes

			computeCentroids();

			for(int i=0; i<numPts; i++) // getting the minLabel
				distanceMinLabel(ptSet[i]); // assign closest label

			iter++;
		}while(change != 0);

		out2.close();
	}

	void writePtSet(ofstream &out){
		out << numPts << '\n' << numRow << ' ' << numCol << '\n';

		for(int i=0; i<numPts; i++)
			out << ptSet[i].x << ' ' << ptSet[i].y << ' ' << ptSet[i].label << '\n';

		out.close();
	}

	void distanceMinLabel(Point &pt){ // looking for the closest point to the center-point and the smallest pt's label
		int minDist = 9999;
		int minLabel = 0;

		for(int label=1; label<k+1; label++){ // go through all labels while getting the...
											// minimum distance between point and kCentroid
			int dist = computeDist(pt, kCentroids[label]); // get distance of point from center point

			if(dist < minDist){
				minLabel = label;
				minDist = dist;
			}
		}

		if(pt.label != minLabel){
			pt.label = minLabel;
			pt.distance = minDist;
			change++;
		}
	}

	int computeDist(Point p, Point centroid){ // compute distance from point to center-point
		int x1 = p.x, y1 = p.y; // p1 (x y)
		int x2 = centroid.x, y2 = centroid.y; // p2 (x y)

		return sqrt((pow((x2-x1), 2) + pow((y2-y1), 2)));
	}

	void computeCentroids(){ // get average distance from the center and assign to kCentroids
		int sumX[k+1] = {}, sumY[k+1] = {}, totalPts[k+1] = {};

		for(int i=0; i<numPts; i++){ // go through all points
			int label = ptSet[i].label; // get label of current point
			sumX[label] += ptSet[i].x; // sum all x coordinates
			sumY[label] += ptSet[i].y; // sum all y coordinates
			totalPts[label]++; // use to get total amount of points for specific label
		}

		for(int label=1; label<k+1; label++){ // go through all labels
			if(totalPts[label] != 0){
				kCentroids[label].x = sumX[label]/totalPts[label]; // average or mean of the x coordinates
				kCentroids[label].y = sumY[label]/totalPts[label]; // average or mean of the y coordinates
			}
		}
	} // works

	void printImg(ofstream &out){ // print labeled points
		for(int i=0; i<numRow; i++){
			for(int j=0; j<numCol; j++){
				if(imgArr[i][j] > 0) out << imgArr[i][j] << ' ';
				else out << ' ';
			}
			out << '\n';
		}
	}

	void pt2Img(){ // set point labels in imgArr
		for(int i=0; i<numPts; i++)
			imgArr[ptSet[i].x][ptSet[i].y] = ptSet[i].label; // swap the 1's with labels
	} // correct.. but still if-y

	void assignLabel(){
		int front = 0, back = numPts - 1;

		for(int label = 1; front <= back; front++, back--){
			ptSet[front].label = label;
			label++;
			if(label > k) // reset k
				label = 1;
			ptSet[back].label = label;
			label++;
			if(label > k) // reset k
				label = 1;
		}
	}

	void loadPtSet(ifstream &in){
		ptSet = new Point[numPts]; // init ptSet

		for(int i=0; in >> ptSet[i].x >> ptSet[i].y; i++); // store points

		in.close();
	}

};

int main(int argc, char** argv){
	ifstream in(argv[1]);
	ofstream out1(argv[3]); // arg3
	ofstream out2(argv[4]); // arg4
	ofstream out3(argv[5]); // arg5

	try{
		int numRow = 0, numCol = 0, minVal = 0, maxVal = 0, numPts = 0;

		in >> numRow >> numCol >> minVal >> maxVal;

		int k = atoi(argv[2]); // set k
		int **imgArr = new int *[numRow]; // init imgArr

		for(int i=0; i<numRow; i++){
			imgArr[i] = new int [numCol];
			imgArr[i][i] = {}; // init to 0
		}

		for(int i=0; i<numRow; i++){ // init imgArr
			for(int j=0; j<numCol; j++){
				in >> imgArr[i][j];

				if(imgArr[i][j] > 0){
					numPts++; // count points
					out1 << i << " " << j << '\n';
				}
			}
		}

		out1.close();
		ifstream pts(argv[3]);

		Kmeans *kmean = new Kmeans(numRow, numCol, minVal, maxVal, k, numPts, imgArr);
		kmean->loadPtSet(pts);
		kmean->kMeanClustering(out2);
		kmean->writePtSet(out3);

		pts.close();
		in.close();
		out2.close();
		out3.close();
	}catch(int e){
		cout << e;
	}

	cout << "Thinking Bit: ON!!!";

	return 0;
}
