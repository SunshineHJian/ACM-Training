/* &*#()&*#)&E*F& */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define CLR(A) A.clear()
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define INS(A, P, B) A.insert(A.begin() + P, B)
#define ERS(A, P) A.erase(A.begin() + P)
#define SRT(A) sort(ALL(A))
#define SZ(A) int(A.size())
#define PB push_back
#define MP(A, B) make_pair(A, B)

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

/* -&$&#*( &#*@)^$@&*)*/

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

const int N = int(2e6) + 9;

LL dp[N], dep[N], sz[N], sv[N];
LL A[2*N];

// dp[u] = dep[u]*val[u]*sz[u] + sigma dp[v]

class RootItRight {
public:
	long long findMinimumTotalCost(int n, vector <int> par, vector <int> val, int D, int seed, int MX) {

	    A[0] = seed; FOR(i, 1, 2*n) A[i] = (A[i-1] * 1103515245 + 12345) % 2147483648;
	    FOR(i, SZ(par), n) par.PB((A[i] % min(i, D)) + i - min(i, D));
	    FOR(i, SZ(val), n) val.PB(A[i+n] % MX);

	    RST(dp); RST(sz); RST(sv);

#define p par[u]
	    FOR(u, 1, n) dep[u] = dep[p] + 1;

	    DWN(u, n, 0) {
	        sz[u] += 1;
	        sv[u] += val[u]*sz[u];
	        dp[u] += dep[u]*val[u]*sz[u];
	        sz[p] += sz[u];
	        sv[p] += sv[u];
	        dp[p] += dp[u];
	    }

		LL z = dp[0];
	    FOR(u, 1, n) {
            LL svp = (sv[p]-val[p]*(sz[p]-(n-sz[u])))-sv[u];
            dp[u] = dp[p]+svp-sv[u];
            sv[u] += svp;
            checkMin(z, dp[u]);
	    }
		return z;
	}
};


// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			int N                     = 4;
			int edge[]                = {-1,0,1,2};
			int val[]                 = {4,3,3,4};
			int D                     = 1;
			int seed                  = 0;
			int MX                    = 5;
			long long expected__      = 18;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int edge[]                = {-1,0,0,0};
			int val[]                 = {3,2,3,0};
			int D                     = 1;
			int seed                  = 0;
			int MX                    = 4;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 5;
			int edge[]                = {-1,0,0,1,3};
			int val[]                 = {5,0,3,2,3};
			int D                     = 1;
			int seed                  = 0;
			int MX                    = 6;
			long long expected__      = 20;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 17;
			int edge[]                = {-1};
			int val[]                 = {};
			int D                     = 7;
			int seed                  = 176;
			int MX                    = 15;
			long long expected__      = 620;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 200000;
			int edge[]                = {-1,0,0,0};
			int val[]                 = {4,7};
			int D                     = 1;
			int seed                  = 0;
			int MX                    = 1000;
			long long expected__      = 166346919874650680LL;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int edge[]                = ;
			int val[]                 = ;
			int D                     = ;
			int seed                  = ;
			int MX                    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int edge[]                = ;
			int val[]                 = ;
			int D                     = ;
			int seed                  = ;
			int MX                    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int edge[]                = ;
			int val[]                 = ;
			int D                     = ;
			int seed                  = ;
			int MX                    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RootItRight().findMinimumTotalCost(N, vector <int>(edge, edge + (sizeof edge / sizeof edge[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), D, seed, MX);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
