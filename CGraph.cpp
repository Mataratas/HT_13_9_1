#include "CGraph.h"
//==============================================================================
CGraph::CGraph() {
	for (size_t i = 0; i < SIZE; i++)
		for (size_t j = 0; j < SIZE; j++)
			matrix[i][j] = VERYBIGINT;
}
//-------------------------------------------------------------------------------
void CGraph::add_vertex(size_t vrt) {
	vertexes[vertexCount++] = vrt;
}
//-------------------------------------------------------------------------------
void CGraph::add_edge(size_t v1, size_t v2, size_t weight) {
	matrix[v1][v2] = weight;
	matrix[v2][v1] = weight;
}
//-------------------------------------------------------------------------------
void CGraph::show(bool fulldata) {
	if (fulldata) {
		std::cout << "Vertexes:" << std::endl;
		for (size_t i = 0; i < vertexCount; i++)
			std::cout << vertexes[i] << ' ';
		std::cout << std::endl;


		std::cout << "Graph matrix:" << std::endl;
		for (size_t r = 0; r < vertexCount; r++) {
			for (size_t c = 0; c < vertexCount; c++)
				std::cout << matrix[r][c] << ' ';
			std::cout << std::endl;
		}
	}

	std::cout << "Участники:" << std::endl;
	for (size_t r = 0; r < vertexCount; r++) {
		size_t friend_count{};
		std::cout << _persons[vertexes[r]].Name <<"(id:"<< _persons[vertexes[r]].id << ") знаком(а) с :";
		for (size_t c = 0; c < vertexCount; c++) {
			if (matrix[r][c] != VERYBIGINT) {
				std::cout << _persons[vertexes[c]].Name <<"(id:" << _persons[vertexes[r]].id << ")"<< ' ';
				friend_count++;
			}
		}
		if (!friend_count)
			std::cout << "никем";
		std::cout << std::endl;
	}
}
//----------------------------------------------------------------------------------
bool CGraph::is_ajecent_vertex(size_t curr, size_t next) {
	return matrix[curr][next] != VERYBIGINT || matrix[next][curr] != VERYBIGINT;
}
//----------------------------------------------------------------------------------
bool CGraph::vertex_exists(size_t vtx) {
	for (size_t i = 0; i < vertexCount; i++) {
		if (vertexes[i] == vtx)
			return true;
	}
	return false;
}
//==================================================================================
auto CGraph::_get_new_id() -> size_t {
	std::random_device rd;
	std::uniform_int_distribution<size_t> dist(1, SIZE * SIZE - 1);
	return dist(rd);
}
//----------------------------------------------------------------------------------
auto CGraph::_get_friend_id_by_pid(size_t pid) -> size_t {
	for (size_t i = 0; i < _personsCount; i++)
		if (_persons[i].id == pid)
			return i;
	return VERYBIGINT;
}
//----------------------------------------------------------------------------------
auto CGraph::_get_friend_id_by_name(const char* name) -> size_t {
	for (size_t i = 0; i < _personsCount; i++)
		if (_persons[i].Name == name)
			return i;
	return VERYBIGINT;
}
//----------------------------------------------------------------------------------
auto CGraph::add_person(const char* p_name, size_t friend_id) -> void {
	_persons[_personsCount].Name = p_name;
	_persons[_personsCount].id = _get_new_id();
	add_vertex(_personsCount);

	if (friend_id)
		set_friend(_persons[_personsCount].id, friend_id);
	_personsCount++;
}
//----------------------------------------------------------------------------------
auto CGraph::set_friend(size_t pid_1, size_t pid_2) -> void {
	size_t id1 = _get_friend_id_by_pid(pid_1);
	size_t id2 = _get_friend_id_by_pid(pid_2);
	if (id1 == VERYBIGINT || id2 == VERYBIGINT) return;
	if (!is_ajecent_vertex(vertexes[id1], vertexes[id2]))
		add_edge(vertexes[id1], vertexes[id2]);
}
//----------------------------------------------------------------------------------
auto CGraph::set_friend(const char* name1, const char* name2) -> void {
	size_t id1 = _get_friend_id_by_name(name1);
	size_t id2 = _get_friend_id_by_name(name2);
	if (id1 == VERYBIGINT || id2 == VERYBIGINT) return;
	if (!is_ajecent_vertex(vertexes[id1], vertexes[id2]))
		add_edge(vertexes[id1], vertexes[id2]);
}
//----------------------------------------------------------------------------------
auto  CGraph::_pair_exists(size_t vt1, size_t vt2, size_t a_pairs[][2]) -> bool {
	for (size_t i = 0; i < SIZE; i++){
		if ((a_pairs[i][0] == vt1 && a_pairs[i][1] == vt2) || (a_pairs[i][0] == vt2 && a_pairs[i][1] == vt1))
			return true;
		if (a_pairs[i][0] == 0 && a_pairs[i][1] == 0)
			return false;
	}
	return false;
}
//----------------------------------------------------------------------------------
auto CGraph::_add_pair(size_t head_vt, size_t curr_vt, size_t a_pairs[][2], size_t max_dist, size_t& dist_counter, size_t& pairs_counter, bool *visited) -> void {
	if (dist_counter == max_dist) {
		if (!_pair_exists(head_vt, curr_vt, a_pairs)) {
			a_pairs[pairs_counter][0] = head_vt;
			a_pairs[pairs_counter][1] = curr_vt;
			pairs_counter++;
		}
		dist_counter--;
		return;
	}
	visited[curr_vt] = true;
	for (size_t i = 0; i < vertexCount ; i++){
		if (visited[vertexes[i]]) continue;
		if (is_ajecent_vertex(vertexes[i], curr_vt)) {
			a_pairs[pairs_counter][0] = head_vt;
			a_pairs[pairs_counter][1] = vertexes[i];
			pairs_counter++;				
			dist_counter++;
			_add_pair(head_vt,vertexes[i], a_pairs, max_dist, dist_counter, pairs_counter, visited);
		}
	}
	dist_counter--;
}
//----------------------------------------------------------------------------------
auto CGraph::_show_pairs(size_t pairs_counter,size_t a_pairs[][2]) -> void {
	std::cout << "=======================================================================================================\n";
	for (size_t i = 0; i < pairs_counter; i++) 
		std::cout << "Pair (" << i<<")->"<< a_pairs[i][0]<<":"<< a_pairs[i][1]<<"->" << _persons[vertexes[a_pairs[i][0]]].Name << ":" << _persons[vertexes[a_pairs[i][1]]].Name << ")" << std::endl;
		
}
//----------------------------------------------------------------------------------
auto CGraph::show_depth(size_t max_dist) -> void {
	size_t a_pairs[SIZE][2]{};
	bool visited[SIZE]{ false };
	size_t dist_counter{}, pairs_counter{};
	for (size_t i = 0; i < vertexCount; i++) {
		_add_pair(vertexes[i], vertexes[i], a_pairs, max_dist, dist_counter, pairs_counter, visited);
		dist_counter = 0;
		for (size_t j = 0; j < vertexCount; j++) visited[j] = false;
		//_show_pairs(pairs_counter, a_pairs);
	}
		

	std::cout << "Количество пар знакомых в пределах "<< max_dist<<" рукопожатий:\n";
	for (size_t i = 0; i < pairs_counter; i++)
		std::cout << _persons[vertexes[a_pairs[i][0]]].Name << "(id:" << _persons[vertexes[a_pairs[i][0]]].id << ") -> " << _persons[vertexes[a_pairs[i][1]]].Name << "(id:" << _persons[vertexes[a_pairs[i][1]]].id<<")" << std::endl;

}