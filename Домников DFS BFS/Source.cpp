#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>


void input();
void output();
void BFS(int v);
void components();
void SHORTEST_PATH();
void DFS(int v);
void SHORTEST_PATH_FOR_ALL();


using namespace std;
vector <vector<int>> k;
vector <int> path;
vector <bool> visited;

int main()
{
	setlocale(LC_ALL, "Russian");
	input();
	int v;
	cout << "������� ������� ";
	cin >> v;
	v--;;
	DFS(v);
	cout << "����� � �������" << endl;
	for (int i = 0; i < path.size(); i++)
		cout << path[i] + 1 << endl;
	BFS(v);
	components();
	SHORTEST_PATH();
	SHORTEST_PATH_FOR_ALL();
	system("pause");
}

void input() // ���� ����� �� ������ ���������
{
	int m, n, maxSize = 0;
	fstream fin("C://work.txt");
	if (!fin.is_open())
		cout << "File not open";
	else
	{
		while (!fin.eof())
		{
			fin >> m;
			fin >> n;
			if (m > maxSize)
				maxSize = m;
			if (n > maxSize)
				maxSize = n;
			k.resize(maxSize);
			k[m - 1].push_back(n - 1);
			k[n - 1].push_back(m - 1);
		}
	}
	for (size_t i = 0; i < k.size(); i++)
		sort(k[i].begin(), k[i].end());
	fin.close();
}

void output() // ����� � ����
{
	fstream fout("C://foutWork.txt");
	if (!fout.is_open())
		cout << "File not open";
	else
	{
		for (size_t i = 0; i < k.size(); i++)
		{
			fout << i + 1 << ":";
			for (size_t j = 0; j < k[i].size(); j++)
				fout << "  " << k[i][j];
			fout << endl;
		}
	}
	fout.close();
}

void DFS(int v) // ���������� ����� � �������
{
	visited.resize(k.size());
	visited[v] = true;
	path.push_back(v);
	for (size_t i = 0; i < k.size(); i++)
	{
		for (size_t j = 0; j < k[v].size(); j++)
		{
			if (!visited[k[v][j]])
				DFS(k[v][j]);
		}
	}
}

void components() // ����� ��������� �����
{
	vector <vector<int>> component;
	visited.resize(k.size());
	component.push_back(path);
	for (size_t i = 0; i < k.size(); i++)
	{
		if (!visited[i])
		{
			path.clear();
			DFS(i);
			component.push_back(path);
		}
	}
	if (component.size() == 0)
		component.push_back(path);
	for (size_t i = 0; i < component.size(); i++)
	{
		cout << "���������� " << i + 1 << ":";
		for (size_t j = 0; j < component[i].size(); j++)
			cout << component[i][j] + 1 << " ";
		cout << endl;
	}
}

void SHORTEST_PATH() // ���������� ���� ����� ����� ��������� � ������� ������ � ������
{
	cout << "���������� ���� ����� ����� ���������" << endl;
	vector <int> path;
	vector <bool> visited;
	vector <int> p, d; // p - ������ �������, d - ������ ���� �����
	p.resize(k.size());
	d.resize(k.size());
	visited.resize(k.size());
	int first, second;
	cout << "������� �������: ";
	cin >> first;
	cout << endl;
	cout << "������� ������ �������: ";
	cin >> second;
	first--; // ������ �������
	second--; // ������ �������
	queue <int> s;
	visited.resize(k.size());
	visited[first] = true;
	p[first] = -1;
	s.push(first);
	while (!s.empty())
	{
		int w = s.front();

		s.pop();
		path.push_back(w);
		for (size_t i = 0; i < k[w].size(); i++)
		{
			if (!visited[k[w][i]])
			{
				s.push(k[w][i]);
				visited[k[w][i]] = true;
				d[k[w][i]] = d[w] + 1; // ����������� �������� ����
				p[k[w][i]] = w; // ��������� ������
			}
		}
	}
	if (!visited[second])
		cout << "���� �� ���������� \n";
	else
	{
		vector <int> shortest_path;
		for (int v = second; v != -1; v = p[v])
			shortest_path.push_back(v);                        // ���������� ����� ����� ����� ���������
		reverse(shortest_path.begin(), shortest_path.end());
		cout << "Path: ";
		for (size_t i = 0; i < shortest_path.size(); ++i)
			cout << shortest_path[i] + 1 << " ";
	}
}

void SHORTEST_PATH_FOR_ALL() // ���������� ���� ����� ����� ������ ������
{
	cout << "���������� ���� ����� ����� ������ ������" << endl;
	vector <int> path;
	vector <bool> visited;
	vector <int> shortest_path, p, d; // p - ������ �������, d - ������ ���� �����
	p.resize(k.size());
	d.resize(k.size());
	int first;
	cout << "������� �������: ";
	cin >> first;
	first--;
	queue <int> s;
	visited.resize(k.size());
	visited[first] = true;
	p[first] = -1;
	s.push(first);
	while (!s.empty())
	{
		int w = s.front();

		s.pop();
		path.push_back(w);
		for (size_t i = 0; i < k[w].size(); i++)
		{
			if (!visited[k[w][i]])
			{
				s.push(k[w][i]);
				visited[k[w][i]] = true;
				d[k[w][i]] = d[w] + 1; // ����������� �������� ����
				p[k[w][i]] = w; // ��������� ������
			}
		}
	}
	vector <pair<int, int>> shortest_path2;
	for (int v = 0; v < d.size(); v++)
	{
		if (d[v] != 0)
			shortest_path2.push_back(make_pair(v, d[v])); // ���������� ���� ����� ����� ������ ������
	}
	cout << "Shortest path: " << endl;;
	for (vector <pair<int, int>> ::iterator it = shortest_path2.begin(); it != shortest_path2.end(); it++)
		cout << it->first + 1 << " " << it->second << " " << endl;
}

void BFS(int v)
{
	cout << "����� � ������ " << endl;
	vector <int> path;
	vector <bool> visited;
	queue <int> s;
	visited.resize(k.size());
	s.push(v);
	visited[v] = true;
	while (!s.empty())
	{
		int w = s.front();
		s.pop();
		path.push_back(w);
		for (size_t i = 0; i < k[w].size(); i++)
		{
			if (!visited[k[w][i]])
			{
				s.push(k[w][i]);
				visited[k[w][i]] = true;
			}
		}
	}
	for (int i = 0; i < path.size(); i++)
		cout << path[i] + 1 << endl;
}