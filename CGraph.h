#pragma once
#include <iostream>
#include <random>

#define VERYBIGINT 1000000000 
#define SIZE 100

//========================================================================================================

struct Person {
	const char* Name{};
	size_t id{};
	Person(const char* name, size_t _id) :Name(name), id(_id) {};
	Person() = default;
};

//------------------------------------------------------------------------------------------------------------

class CGraph {
public:
	CGraph();
	auto add_person(const char*, size_t friend_id = 0) -> void;
	auto set_friend(size_t, size_t) -> void;
	auto set_friend(const char*, const char*) -> void;
	auto show_depth(size_t max_dist = 3)->void;
	void show(bool fulldata=false);
	
private:
	void add_vertex(size_t);
	void add_edge(size_t, size_t, size_t w = 1);
	bool vertex_exists(size_t);

	bool is_ajecent_vertex(size_t, size_t);

	auto _get_new_id() -> size_t;
	auto _get_friend_id_by_pid(size_t) -> size_t;
	auto _get_friend_id_by_name(const char*) -> size_t;
	auto _add_pair(size_t, size_t, size_t [][2], size_t,size_t&, size_t&,bool*) -> void;
	auto _show_pairs(size_t,size_t[][2]) -> void;
	auto _pair_exists(size_t, size_t, size_t[][2]) -> bool;

	size_t matrix[SIZE][SIZE]{};
	size_t vertexes[SIZE]{};
	Person _persons[SIZE];
	size_t _personsCount{};
	size_t vertexCount{};

};


