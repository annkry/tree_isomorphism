#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define mp make_pair
int n;
int D;
vector<int> adj[2][500004];
int queue[2][500004];
bool leaves[2][500004];
int count_neigh[2][500004];
vector<int> buckets[500004];
vector<int> collecting;
pair<int, int> to_not_empty[500004];
vector<int> sort_len[500004];
vector<int> not_empty_cont[500004];
vector<int> queue_words[2];
vector<int> code[2][500004];
int code_e[2][500004];
int queuebfs[2][500004];
int poziom[2][500004];
bool visited[2][500004];
int id_sort[2];
int id_queue_words[2];
bool visitedbfs[2][500004];
vector<int> v_floor[2][500004];
vector<int> to_sort[2];
int parent[2][500004];
pair<int, int> c1;
pair<int, int> c2;

pair<int, int> center(bool bit,int ids,int ide){
	int v;
	int iter = n;
	while (iter > 2) {
		int id_e = ide;
		for (int itt = ids; itt < id_e; itt++) {
			v = queue[bit][itt];
			count_neigh[bit][v] = 0;
			iter--;
			ids++;
			for (int gg = 0; gg < (int)adj[bit][v].size(); gg++) {
				count_neigh[bit][adj[bit][v][gg]]--;
				if (count_neigh[bit][adj[bit][v][gg]] == 1) {
					queue[bit][ide] = adj[bit][v][gg];
					ide++;
				}
			}
		}
	}
	if (bit == 0) {
		return mp(queue[bit][ide-1], 0);
	}
	else {
		if (iter == 2) {
			return mp(queue[bit][ide-2], queue[bit][ide-1]);
		}
		else {
			return mp(queue[bit][ide-1], 0);
		}
	}
}



void part_I(bool bit, int gl, int dist[]) {
	if (gl < dist[bit]) {
		sort_len[0].clear();
		for (int it1 = 0; it1 < (int)to_sort[bit].size(); it1++) {
			code[bit][parent[bit][to_sort[bit][it1]]].clear();
		}
		for (int it1 = 0; it1 < (int)to_sort[bit].size(); it1++) {
			code[bit][parent[bit][to_sort[bit][it1]]].push_back(code_e[bit][to_sort[bit][it1]]);
		}
	}
	to_sort[bit].clear();
	int the_end = 0;
	int l_max = -1;
	for (int it = 0; it < (int)v_floor[bit][gl].size(); it++) {
		if (leaves[bit][v_floor[bit][gl][it]] != 1) {
			sort_len[code[bit][(int)v_floor[bit][gl][it]].size() - 1].clear();
		}
	}
	for (int it = 0; it < (int)v_floor[bit][gl].size(); it++) {
		if (leaves[bit][v_floor[bit][gl][it]] != 1) {
			for (int it4 = 0; it4 < (int)code[bit][v_floor[bit][gl][it]].size(); it4++) {
				to_not_empty[the_end] = make_pair(it4, code[bit][v_floor[bit][gl][it]][it4]);
				the_end++;
			}
			sort_len[code[bit][v_floor[bit][gl][it]].size() - 1].push_back(it);
			if (l_max < (int)code[bit][v_floor[bit][gl][it]].size() - 1) {
				l_max = code[bit][v_floor[bit][gl][it]].size() - 1;
			}
		}
		else {
			to_sort[bit].push_back(v_floor[bit][gl][it]);
		}
	}
	collecting.clear();
	int max1 = 0;
	for (int it4 = 0; it4 < the_end; it4++) {
		buckets[to_not_empty[it4].second].push_back(it4);
		if (to_not_empty[it4].second > max1) {
			max1 = to_not_empty[it4].second;
		}
	}
	for (int it4 = 0; it4 <= max1; it4++) {
		if (!buckets[it4].empty()) {
			for (int it5 = 0; it5 < (int)buckets[it4].size(); it5++) {
				collecting.push_back(buckets[it4][it5]);
			}
			buckets[it4].clear();
		}
	}
	max1 = 0;
	for (int it4 = 0; it4 < the_end; it4++) {
		buckets[to_not_empty[collecting[it4]].first].push_back(collecting[it4]);
		if (to_not_empty[collecting[it4]].first > max1) {
			max1 = to_not_empty[collecting[it4]].first;
		}
	}
	collecting.clear();
	for (int it4 = 0; it4 <= max1; it4++) {
		if (!buckets[it4].empty()) {
			for (int it5 = 0; it5 < (int)buckets[it4].size(); it5++) {
				collecting.push_back(buckets[it4][it5]);
			}
			buckets[it4].clear();
		}
	}
	for (int it4 = 0; it4 <= max1; it4++) {
		not_empty_cont[it4].clear();
	}
	for (int it4 = 0; it4 < (int)collecting.size(); it4++) {
		not_empty_cont[to_not_empty[collecting[it4]].first].push_back(to_not_empty[collecting[it4]].second);
	}
	int pocz = 0;
	int ko = 0;
	int kol;
	int l_ta_skl;
	queue_words[bit].clear();
	int indeks_krotsze_slowa = 0;
	vector<int> copy_v;
	for (int it2 = l_max; it2 >= 0; it2--) {
		indeks_krotsze_slowa = (int)queue_words[bit].size();
		for (int it7 = 0; it7 < (int)sort_len[it2].size(); it7++) {
			queue_words[bit].push_back(sort_len[it2][it7]);
		}
		sort_len[it2].clear();
		pocz = indeks_krotsze_slowa;
		ko = (int)queue_words[bit].size() - 1;
		while (pocz - 1 < ko) {
			kol = queue_words[bit][pocz];
			pocz++;
			l_ta_skl = code[bit][v_floor[bit][gl][kol]][it2];
			buckets[l_ta_skl].push_back(kol);
		}
		pocz = indeks_krotsze_slowa - 1;
		ko = 0;
		while (pocz + 1 > ko) {
			kol = queue_words[bit][pocz];
			pocz--;
			l_ta_skl = code[bit][v_floor[bit][gl][kol]][it2];
			buckets[l_ta_skl].push_back(kol);
		}
		queue_words[bit].clear();
		for (int it5 = (int)not_empty_cont[it2].size() - 1; it5 >= 0; it5--) {
			for (int it6 = (int)buckets[not_empty_cont[it2][it5]].size() - 1; it6 >= 0; it6--) {
				queue_words[bit].push_back(buckets[not_empty_cont[it2][it5]][it6]);
				ko++;
			}
			buckets[not_empty_cont[it2][it5]].clear();
		}
	}
}

void gen_new_codes(bool bit, int gl) {
	int codes = 1;
	for (int it8 = (int)queue_words[bit].size() - 1; it8 >= 0; it8--) {
		if (leaves[bit][v_floor[bit][gl][queue_words[bit][it8]]] != 1) {
			code[bit][v_floor[bit][gl][queue_words[bit][it8]]].clear();
			to_sort[bit].push_back(v_floor[bit][gl][queue_words[bit][it8]]);
			code_e[bit][v_floor[bit][gl][queue_words[bit][it8]]] = codes;
			if (it8 > 0 && code[bit][v_floor[bit][gl][queue_words[bit][it8 - 1]]] != code[bit][v_floor[bit][gl][queue_words[bit][it8]]]) {
				codes = codes + 1;
			}
		}
	}
}

bool funn(int cen, int cen2) {
	for (int it2 = 0; it2 < n; it2++) {
		v_floor[0][it2].clear();
		v_floor[1][it2].clear();
	}
	for (int it2 = 0; it2 < n+1; it2++) {
		visited[0][it2] = 0;
		visited[1][it2] = 0;
	}
	int p = 0;
	int k = 0;
	queuebfs[0][0] = cen;
	k++;
	poziom[0][cen] = 0;
	v_floor[0][0].push_back(cen);
	int dist1 = 1;
	int q;
	bool start = true;
	while (p - 1 < k || start) {
		start = false;
		q = queuebfs[0][p];
		visited[0][q] = 1;
		p++;
		for (int hh = 0; hh < (int)adj[0][q].size(); hh++) {
			if (visited[0][adj[0][q][hh]] != 1) {
				poziom[0][adj[0][q][hh]] = poziom[0][q] + 1;
				v_floor[0][poziom[0][q] + 1].push_back(adj[0][q][hh]);
				queuebfs[0][k] = adj[0][q][hh];
				parent[0][adj[0][q][hh]] = q;
				k++;
				dist1 = poziom[0][q] + 1;
			}
		}

	}
	p = 0;
	k = 0;
	queuebfs[1][0] = cen2;
	k++;
	poziom[1][cen2] = 0;
	v_floor[1][0].push_back(cen2);
	int dist2 = 1;
	start = true;
	while (p - 1 < k || start) {
		start = false;
		q = queuebfs[1][p];
		visited[1][q] = 1;
		p++;
		for (int hh = 0; hh < (int)adj[1][q].size(); hh++) {
			if (visited[1][adj[1][q][hh]] != 1) {
				poziom[1][adj[1][q][hh]] = poziom[1][q] + 1;
				v_floor[1][poziom[1][q] + 1].push_back(adj[1][q][hh]);
				queuebfs[1][k] = adj[1][q][hh];
				parent[1][adj[1][q][hh]] = q;
				k++;
				dist2 = poziom[1][q] + 1;
			}
		}

	}
	int gl_max[2];
	if (dist1 != dist2) {
		return false;
	}
	else {
		gl_max[0] = dist1;
		gl_max[1] = dist2;
		for (int gl = dist1; gl >= 1; gl--) {

			if (gl == dist1) {
				to_sort[0].clear();
				to_sort[1].clear();
				for (int poz = 0; poz < (int)v_floor[0][dist1].size(); poz++) {
					to_sort[0].push_back(v_floor[0][dist1][poz]);
				}
				for (int poz = 0; poz < (int)v_floor[1][dist1].size(); poz++) {
					to_sort[1].push_back(v_floor[1][dist1][poz]);
					
				}
				if ((int)to_sort[0].size() != (int)to_sort[1].size()) {
					return false;
				}
			}
			else {
				part_I(0, gl, gl_max);
				part_I(1, gl, gl_max);
				if ((int)to_sort[0].size() != (int)to_sort[1].size()) {
					return false;
				}
				bool incorrect = 0;
				for (int it5 = 0; it5 < (int)queue_words[0].size(); it5++) {
					if (code[0][v_floor[0][gl][queue_words[0][it5]]] != code[1][v_floor[1][gl][queue_words[1][it5]]]) {
						return false;
						incorrect = 1;
					}
				}
				if (incorrect != 1 && gl != dist1) {
					gen_new_codes(0, gl);
					gen_new_codes(1, gl);
					if ((int)to_sort[0].size() != (int)to_sort[1].size()) {
						return false;
					}
				}
			}
		}
		return true;
	}
}


int main() {
	scanf("%d", &D);
	int w1;
	int	w2;
	int ids1 = 0;
	int ids2 = 0;
	int ide1 = 0;
	int ide2 = 0;
	char cc;
	
		for (int i = 0; i < D; i++) {
			ids1 = 0;
			ids2 = 0;
			ide1 = 0;
			ide2 = 0;
			scanf("%d", &n);
			for (int a = 0; a < n+1; a++) {
				count_neigh[0][a] = 0;
				count_neigh[1][a] = 0;
			}
			scanf("%c", &cc);
			for (int j = 0; j < n - 1; j++) {
				scanf("%d %d", &w1, &w2);
				adj[0][w1].push_back(w2);
				adj[0][w2].push_back(w1);
				count_neigh[0][w1] ++;
				count_neigh[0][w2]++;
				scanf("%c", &cc);
			}
			for (int j = 0; j < n - 1; j++) {
				scanf("%d %d", &w1, &w2);
				adj[1][w1].push_back(w2);
				adj[1][w2].push_back(w1);
				count_neigh[1][w1] ++;
				count_neigh[1][w2]++;
				scanf("%c", &cc);
			}
			for (int f = 1; f < n + 1; f++) {
				leaves[0][f] = 0;
				leaves[1][f] = 0;
			}
			for (int f = 1; f < n + 1; f++) {
				if (count_neigh[0][f] == 1) {
					queue[0][ide1] = f;
					leaves[0][f] = 1;
					code_e[0][f] = 0;
					ide1++;
				}
				if (count_neigh[1][f] == 1) {
					queue[1][ide2] = f;
					leaves[1][f] = 1;
					code_e[1][f] = 0;
					ide2++;
				}
			}
			c1 = center(0, ids1, ide1);
			c2 = center(1, ids2, ide2);
			if (c2.second == 0) {
				if (funn(c1.first, c2.first)) {
					printf("YES\n");
				}
				else {
					printf("NO\n");
				}
			}
			else {
				if (funn(c1.first, c2.second) || funn(c1.first, c2.first)) {
					printf("YES\n");
				}
				else {
					printf("NO\n");
				}
			}
			for (int itt = 0; itt < n + 1; itt++) {
				adj[0][itt].clear();
				adj[1][itt].clear();
			}
		}
	return 0;
}