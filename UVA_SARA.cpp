#include <iostream>
#include <vector>
#include <string>

using namespace std;

void buildTree( vector<int> & arr, vector <int> & segT, int low, int high, int pos) { //high y low delimitan el rango que representa cada nodo
	/*cout << "low "<<low<<endl;
	cout << "high " << high<<endl;*/
	if (low == high) {
		segT[pos] = arr[low]; //Cuando llega a una hoja
//		cout << "segT "<<pos<<": "<< segT[pos]<<"deberia ser " << arr[low] << endl;
		return;
	}

	int m = (low + high) / 2;


	buildTree(arr, segT, low, m, 2 * pos + 1); //2 * pos + 1 es posicion de hijo izquierdo
	buildTree(arr, segT, m + 1, high, 2 * pos + 2); //2 * pos + 2 es posicion de hijo izquierdo

	int a = 2 * pos + 1;
	int b = 2 * pos + 2;
//	cout << "segT[2 * pos + 1]:" << segT[a] <<" a: "<<a<< endl;
//	cout << "segT[2 * pos + 2]:" << segT[b] << endl;
	segT[pos] = segT[a] + segT[b]; //suma entre hijo izquierdo y derecho
//	cout << "segT " << pos << ": " << segT[pos]<<endl;

}


int sum(vector<int> segT, int qlow, int qhigh, int low, int high, int pos) {
	if (low > high) return (1 << 30);

	//fuera de intervalo
	if (qlow > high || qhigh < low) return (1 << 30);

	//totalmente dentro de intervalo
	if (qlow <= low && qhigh >= high) {
		//	cout << "prueba " << segT[pos]<<endl;
		return segT[pos];
	}

	//intersecta con inervalo
	int m = (low + high) / 2;
	//cout << "prueba b " << min(rmq(segT, lazT, qlow, qhigh, low, m, 2 * pos + 1), rmq(segT, lazT, qlow, qhigh, m + 1, high, 2 * pos + 2)) << endl;
	return sum(segT, qlow, qhigh, low, m, 2 * pos + 1);
}


int main() {
	int val,a,b,it=1,n;

	while (cin >> n) {
		if (n == 0) {
			break;
		}
		vector <int> v,r;
		string in;

		
		for (int i = 0; i < n; i++) {
			cin >> val;
			v.push_back(val);
		}

		int h = ceil(log(n));
		int size = 2 * (1 << h) - 1;
		vector <int> st(size);
		vector <int> lazy(size);
		buildTree(v, st, 0, n - 1, 0);

		cout << endl;
		for (int u = 0; u < st.size(); u++) {
			cout << st[u] << " " << endl;
		}

		while (cin >> in) {
			if (in == "END") {
				break;
			}
			cin >> a >> b;

			if (in == "S") {
				v[a-1] = b;
				buildTree(v, st, 0, n - 1, 0);
			}

			else if (in == "M") {
				r.push_back(sum(st, a-1, b-1, 0, n - 1, 0));
			}
			//cout << sum(st, a, b, 0, n - 1, 0);

			a = b = NULL;
		}

		cout<<endl<< "Case " << it << ":" << endl;
		for (int g = 0; g < r.size(); g++) {
			cout << r[g] << endl;
		}
		cout << endl;

		it++;
		v.clear();
		r.clear();
		st.clear();
	}


	return 0;
}