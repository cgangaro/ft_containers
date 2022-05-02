#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <stdlib.h>
#if 1
	#include <vector>
	#include <stack>
	#include <map>
	namespace ft = std;
#else
	#include "../../containers/vector.hpp"
	#include "../../containers/stack.hpp"
	#include "../../containers/map.hpp"
#endif

// struct Trunk
// {
// 	Trunk *prev;
// 	std::string str;

// 	Trunk(Trunk *prev, std::string str)
// 	{
// 		this->prev = prev;
// 		this->str = str;
// 	}
// };

// void showTrunks(Trunk *p)
// {
// 	if (p == nullptr) {
// 		return;
// 	}

// 	showTrunks(p->prev);
// 	std::cout << p->str;
// }

// void printTree(ft::map<int, int>::map_node* root, Trunk *prev, bool isLeft)
// {
//     if (root == nullptr) {
//         return;
//     }
//     std::string prev_str = "    ";
//     Trunk *trunk = new Trunk(prev, prev_str);
//     printTree(root->right, trunk, true);
//     if (!prev) {
//         trunk->str = "———";
//     }
//     else if (isLeft)
//     {
//         trunk->str = ".———";
//         prev_str = "   |";
//     }
//     else {
//         trunk->str = "`———";
//         prev->str = prev_str;
//     }
//     showTrunks(trunk);
//     std::cout << root->value.first << std::endl;
//     if (prev) {
//         prev->str = prev_str;
//     }
//     trunk->str = "   |";
//     printTree(root->left, trunk, false);
// 	delete trunk;
// }

// helper function
void calc_time_taken(struct timeval start, struct timeval end, std::string function_name)
{
	double time_taken;

	time_taken = (end.tv_sec - start.tv_sec) * 1000000;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec));
	std::cout << "--------------------" << std::endl;
	std::cout << function_name << " takes [" << std::fixed << time_taken << std::setprecision(1) << "] milli sec to complete." << std::endl;
	std::cout << "--------------------" << std::endl;
}

void print_vector(ft::vector<int> vector)
{
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<vector.size(); i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
}

//************** Map **************

void map_constructor_1()
{
	ft::map<int, char> test_one;

	for (int i = 0; i < 10; i++) {
		test_one.insert(ft::pair<int, char>(i, 'a'));
	}

	ft::map<int, char> test_two(test_one);
	for (ft::map<int, char>::iterator it = test_one.begin(); it != test_one.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
	for (ft::map<int, char>::iterator it = test_two.begin(); it != test_two.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_constructor_2()
{
	ft::map<int, char> test_one;

	for (int i = 0; i < 10; i++)
		test_one.insert(ft::pair<int, char>(i, 'a'));

	ft::map<int, char> test_two(test_one.begin(), test_one.end());
	for (ft::map<int, char>::iterator it = test_one.begin(); it != test_one.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
	for (ft::map<int, char>::iterator it = test_two.begin(); it != test_two.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_equals_overload_1()
{
	ft::map<int, char> test_one;

	for (int i = 0; i < 10; i++)
		test_one.insert(ft::pair<int, char>(i, 'a'));

	ft::map<int, char> test_two = test_one;
	for (ft::map<int, char>::iterator it = test_one.begin(); it != test_one.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
	for (ft::map<int, char>::iterator it = test_two.begin(); it != test_two.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_constructors()
{
	map_constructor_1();
	map_constructor_2();
	map_equals_overload_1();
}

void map_begin_1()
{
	ft::map<int, char> test;

	test.insert(ft::pair<int, char>(100, 'a'));
	ft::map<int, char>::iterator it = test.begin();
	std::cout << it->first << std::endl;
	std::cout << it->second << std::endl;
}

void map_end_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++)
		test.insert(ft::pair<int, int>(i, i + 100));
	for (ft::map<int, int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_end_2()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++)
		test.insert(ft::pair<int, int>(i, i + 100));
	ft::map<int, int>::iterator it = test.end();
	it--;
	for (; it != test.begin(); it--)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_rbegin_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++)
		test.insert(ft::pair<int, int>(i, i + 100));
	for (ft::map<int, int>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;
}

void map_rend_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++)
		test.insert(ft::pair<int, int>(i, i + 100));
	ft::map<int, int>::reverse_iterator it = test.rend();
	it--;
	for (; it != test.rbegin(); it--)
		std::cout << it->first << " -> " << it->second << " ";
	std::cout << std::endl;

}

void map_iterators()
{
	map_begin_1();
	map_end_1();
	map_end_2();
	map_rbegin_1();
	map_rend_1();
}

void map_empty_1()
{
	ft::map<int, int> test;

	std::cout << "test.empty() = " << test.empty() << std::endl;
	test.insert(ft::pair<int, int>(100, 100));
	std::cout << "test.empty() = " << test.empty() << std::endl;
}

void map_size_1()
{
	ft::map<int, int> test;

	std::cout << "test.size() = " << test.size() << std::endl;
	for (int i = 0; i < 10; i++)
		test.insert(ft::pair<int, int>(i, 100));
	std::cout << "test.size() = " << test.size() << std::endl;
}

void map_max_size_1()
{
	ft::map<int, int>		test_one;
	ft::map<int, char>	test_two;

	std::cout << "test_one.max_size() = " << test_one.max_size() << std::endl;
	std::cout << "test_two.max_size() = " << test_two.max_size() << std::endl;
}

void map_capacity()
{
	map_empty_1();
	map_size_1();
	map_max_size_1();
}

void map_brackets_1()
{
	ft::map<int, char> test;

	for (int i = 0 ; i < 10; i++)
		test.insert(ft::pair<int, char>(i, 'a'));
	std::cout << "test.size() = " << test.size() << std::endl;
	std::cout << "test[5] = " << test[5] << std::endl;
	std::cout << "test[50] = " << test[50] << std::endl;
	std::cout << "test[200] = " << test[200] << std::endl;
	std::cout << "test.size() = " << test.size() << std::endl;
}

void map_element_access()
{
	map_brackets_1();
}


void map_insert_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	ft::pair<ft::map<int, int>::iterator, bool> pair = test.insert(ft::pair<int, int>(10, 0));
	std::cout << pair.first->first << " = " << pair.second << std::endl;
	pair = test.insert(ft::pair<int, int>(1234, 0));
	std::cout << pair.first->first << " = " << pair.second << std::endl;
	std::cout << "map.size() = " << test.size() << std::endl;
	std::cout << "test[1] = " << test[1] << std::endl;
	std::cout << "test[10] = " << test[10] << std::endl;
	std::cout << "test[100] = " << test[100] << std::endl;
}

void map_insert_2()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(10 - i, i));
	}
	std::cout << "map.size() = " << test.size() << std::endl;
	std::cout << "test[1] = " << test[1] << std::endl;
	std::cout << "test[10] = " << test[10] << std::endl;
	std::cout << "test[100] = " << test[100] << std::endl;
}

void map_insert_3()
{
	ft::map<int, int> test;
	ft::map<int, int> test_two;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i));
	}
	std::cout << "test.size() = " << test.size() << std::endl;
	std::cout << "test[1] = " << test[1] << std::endl;
	std::cout << "test[10] = " << test[10] << std::endl;
	std::cout << "test[100] = " << test[100] << std::endl;
	test_two.insert(test.begin(), test.end());
	std::cout << "test_two.size() = " << test_two.size() << std::endl;
	std::cout << "test[1] = " << test_two[1] << std::endl;
	std::cout << "test[10] = " << test_two[10] << std::endl;
	std::cout << "test[100] = " << test_two[100] << std::endl;
}

void map_erase_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	test.erase(1);
	test.erase(1);
	test.erase(9);
	test.erase(4);
	test.erase(1);
	test.erase(9);
}

void map_erase_2()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}

	std::cout << test.size() << std::endl;
	test.erase(test.begin(), test.end());
	std::cout << test.size() << std::endl;
}

void map_erase_3()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	for (int i = 0; i < 10; i++) {
		int x = rand() % 10;
		test.erase(x);
	}
}

void map_swap_1()
{
	ft::map<int, int> test;
	ft::map<int, int>	test_two;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	for (int i = 0; i < 10; i++) {
		test_two.insert(ft::pair<int, int>(i + 1, i + 1));
	}
	ft::map<int, int>::iterator it_one = test.begin();
	for (; it_one != test.end(); it_one++) {
		std::cout << it_one->first;
	}
	std::cout << std::endl;
	it_one = test.begin();

	ft::map<int, int>::iterator it_two = test_two.begin();
	for (; it_two != test_two.end(); it_two++) {
		std::cout << it_two->first;
	}
	std::cout << std::endl;
	it_two = test_two.begin();

	std::cout << it_one->first << std::endl;
	std::cout << it_two->first << std::endl;
	test.swap(test_two);
	std::cout << it_one->first << std::endl;
	std::cout << it_two->first << std::endl;
}

void map_modifiers()
{
	map_insert_1();
	map_insert_2();
	map_insert_3();
	map_erase_1();
	map_erase_2();
	map_erase_3();
	map_swap_1();
}

void map_find_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 10));
	}
	ft::map<int, int>::iterator it = test.find(5);
	std::cout << it->first << "->" << it->second << std::endl;
	it = test.find(7);
	if (it == test.end())
		std::cout << "it == test.end()" << std::endl;
}

void map_count_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 100; i++) {
		test.insert(ft::pair<int, int>(i, i + 100));
	}
	size_t c = test.count(50);
	std::cout << c << std::endl;
	c = test.count(1000);
	std::cout << c << std::endl;
}

void map_lower_bound_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 10; i++) {
		test.insert(ft::pair<int, int>(i, i + 10));
	}
	ft::map<int, int>::iterator it = test.lower_bound(4);
	std::cout << it->first << "->" << it->second << std::endl;
	it = test.lower_bound(5);
	if (it == test.end())
		std::cout << "it == test.end()" << std::endl;
}

void map_upper_bound_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 1; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	ft::map<int, int>::iterator it = test.upper_bound(4);
	std::cout << it->first << "->" << it->second << std::endl;
	it = test.upper_bound(5);
	if (it == test.end())
		std::cout << "it == test.end()" << std::endl;
}

void map_equal_range_1()
{
	ft::map<int, int> test;

	for (int i = 0; i < 1; i++) {
		test.insert(ft::pair<int, int>(i, i + 1));
	}
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> it_pair = test.equal_range(5);
	std::cout << it_pair.first->first << "->" << it_pair.first->second << std::endl;
	std::cout << it_pair.second->first << "->" << it_pair.second->second << std::endl;
	it_pair = test.equal_range(1);
	if (it_pair.first == test.end())
		std::cout << "it_pair.first == test.end()" << std::endl;
	if (it_pair.second == test.end())
		std::cout << "it_pair.second == test.second()" << std::endl;
}

void map_operations()
{
	map_find_1();
	map_count_1();
	map_lower_bound_1();
	map_upper_bound_1();
	map_equal_range_1();
}

//************** Vector **************

void vector_test_coplien_form() {

	std::cout << "***VECTOR - COPLIEN FORM***" << std::endl;

	ft::vector<int> vector_first;
	ft::vector<int> vector_first_copy(vector_first);
	ft::vector<int> vector_second(10);
	ft::vector<int> vector_third(10, 900);
	std::cout << "empty vector size: [" << vector_first.size() << "]" << std::endl;
	std::cout << "copied empty vector size: [" << vector_first_copy.size() << "]" << std::endl;
	std::cout << "non-empty vector size: [" << vector_second.size() << "]" << std::endl;
	std::cout << "non-empty vector size: [" << vector_third.size() << "]" << std::endl;

	std::cout << "empty vector capacity: [" << vector_first.capacity() << "]" << std::endl;
	std::cout << "copied empty vector capacity: [" << vector_first_copy.capacity() << "]" << std::endl;
	std::cout << "non-empty vector capacity: [" << vector_second.capacity() << "]" << std::endl;
	std::cout << "non-empty vector capacity: [" << vector_third.capacity() << "]" << std::endl;

}

void vector_test_iterator() {
	std::cout << std::endl << "***VECTOR - ITERATOR***" << std::endl;

	ft::vector<int> vector_first;
	for (int i=0; i<=10; i++) vector_first.push_back(i);

	ft::vector<int>::iterator begin = vector_first.begin();
	ft::vector<int>::iterator end = vector_first.end();
	ft::vector<int>::const_iterator begin_const = vector_first.begin();
	ft::vector<int>::const_iterator end_const = vector_first.end();
	ft::vector<int>::reverse_iterator reverse_begin = vector_first.rbegin();
	ft::vector<int>::reverse_iterator reverse_end = vector_first.rend();
	ft::vector<int>::const_reverse_iterator reverse_begin_const = vector_first.rbegin();
	ft::vector<int>::const_reverse_iterator reverse_end_const = vector_first.rend();

	if (*begin_const == *begin)
		std::cout << "const iterator and iterator are comparable" << std::endl;

	std::cout << "Vector content: ";
	while (begin != end)
	{
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;

	std::cout << "Vector content: ";
	while (begin_const != end_const)
	{
		std::cout << *begin_const << " ";
		begin_const++;
	}
	std::cout << std::endl;

	std::cout << "Vector content: ";
	while (reverse_begin != reverse_end)
	{
		std::cout << *reverse_begin << " ";
		reverse_begin++;
	}
	std::cout << std::endl;

	std::cout << "Vector content: ";
	while (reverse_begin_const != reverse_end_const)
	{
		std::cout << *reverse_begin_const << " ";
		reverse_begin_const++;
	}
	std::cout << std::endl;
}

void vector_test_capacity() {

	std::cout << std::endl << "***VECTOR - CAPACITY***" << std::endl;

	ft::vector<int> vector;
	for (int i=0; i<=10; i++) vector.push_back(i);

	std::cout << "vector size: " << vector.size() << std::endl;
	std::cout << "vector max_size: " << vector.max_size() << std::endl;
	std::cout << "vector capacity: " << vector.capacity() << std::endl;

	vector.resize(50);
	std::cout << "vector size: " << vector.size() << std::endl;
	std::cout << "vector capacity: " << vector.capacity() << std::endl;

	if (vector.empty())
		std::cout << "vector is empty" << std::endl;
	else
		std::cout << "vector is not empty" << std::endl;

	vector.reserve(100);
	std::cout << "vector size: " << vector.size() << std::endl;
	std::cout << "vector capacity: " << vector.capacity() << std::endl;
}

void vector_test_element_access() {

	std::cout << std::endl << "***VECTOR - ELEMENT ACCESS***" << std::endl;

	ft::vector<int> vect;
	for (int i=0; i<=10; i++) vect.push_back(i);

	std::cout << "Vector content: ";
	for (int i=0; i<=10; i++)
		std::cout << vect.at(i) << " ";
	std::cout << std::endl;

	std::cout << "Vector front: " << vect.front() << std::endl;
	std::cout << "Vector back: " << vect.back() << std::endl;

}

void vector_test_modifier() {

	std::cout << std::endl << "***VECTOR - MODIFIER***" << std::endl;

	//******** push_back() ********

	ft::vector<int> vector;
	for (int i=0; i<=9; i++) vector.push_back(i);

	ft::vector<int> new_vector;
	new_vector.assign(vector.begin(), vector.end());

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<vector.size(); i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;

	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	//******** assign() ********
	ft::vector<int> new_vector_2;
	new_vector_2.assign(10, 10);

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector_2.size(); i++)
		std::cout << new_vector_2[i] << " ";
	std::cout << std::endl;

	std::cout << "vector size: " << new_vector_2.size() << std::endl;
	std::cout << "vector capacity: " << new_vector_2.capacity() << std::endl;

	//******** pop_back() ********
	new_vector.pop_back();
	new_vector.pop_back();

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;

	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	//******** insert() ********

	ft::vector<int>::iterator begin = new_vector.begin();
	new_vector.insert(begin + 3, -222);

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;

	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	ft::vector<int>::iterator begin_new = new_vector.begin();
	new_vector.insert(begin_new + 3, 3, -222);

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;

	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	ft::vector<int>::iterator begin_new_2 = new_vector.begin();

	ft::vector<int>::iterator begin_2 = new_vector_2.begin();
	ft::vector<int>::iterator end_2 = new_vector_2.end();
	new_vector.insert(begin_new_2, begin_2, end_2);

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;
	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	//******** erase() ********
	ft::vector<int>::iterator begin_new_3 = new_vector.begin();

	begin_new_3 = new_vector.erase(begin_new_3);
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;
	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	new_vector.erase(begin_new_3, begin_new_3 + 3);
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;
	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;

	//******** swap() ********

	ft::vector<int> ft_foo (3,100);
	ft::vector<int> ft_bar (5,200);

	std::cout << "Vector content: ";
	for (unsigned int i=0; i<ft_foo.size(); i++)
		std::cout << ft_foo[i] << " ";
	std::cout << std::endl;
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<ft_bar.size(); i++)
		std::cout << ft_bar[i] << " ";
	std::cout << std::endl;
	ft_foo.swap(ft_bar);
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<ft_foo.size(); i++)
		std::cout << ft_foo[i] << " ";
	std::cout << std::endl;
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<ft_bar.size(); i++)
		std::cout << ft_bar[i] << " ";
	std::cout << std::endl;

	//******** clear() ********

	new_vector.clear();
		std::cout << "Vector content: ";
	for (unsigned int i=0; i<new_vector.size(); i++)
		std::cout << new_vector[i] << " ";
	std::cout << std::endl;
	std::cout << "vector size: " << new_vector.size() << std::endl;
	std::cout << "vector capacity: " << new_vector.capacity() << std::endl;
}

void vector_test_relational_operators() {
	ft::vector<int> foo (2,200);
	ft::vector<int> foo_same (2,200);
	ft::vector<int> foo_bigger (3,200);

	if (foo == foo_same)
		std::cout << "foo == foo_same" << std::endl;
	if (foo != foo_bigger)
		std::cout << "foo != foo_bigger" << std::endl;
	if (foo < foo_bigger)
		std::cout << "foo < foo_bigger" << std::endl;
	if (foo <= foo_bigger)
		std::cout << "foo <= foo_bigger" << std::endl;
	if (foo_bigger > foo)
		std::cout << "foo_bigger > foo" << std::endl;
	if (foo_bigger >= foo)
		std::cout << "foo_bigger >= foo" << std::endl;
}

void vector_test_non_member_swap() {

	ft::vector<int> foo (3,-100);
	ft::vector<int> bar (5,200);
	for (unsigned int i=0; i<foo.size(); i++)
		std::cout << foo[i] << " ";
	std::cout << std::endl;
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<bar.size(); i++)
		std::cout << bar[i] << " ";
	std::cout << std::endl;
	foo.swap(bar);
	for (unsigned int i=0; i<foo.size(); i++)
		std::cout << foo[i] << " ";
	std::cout << std::endl;
	std::cout << "Vector content: ";
	for (unsigned int i=0; i<bar.size(); i++)
		std::cout << bar[i] << " ";
	std::cout << std::endl;
}

//************** Stack **************

void stack_test_constructor() {
	ft::stack<int, ft::vector<int> > mystack;
	std::cout << "stack size: " << mystack.size() << std::endl;

	ft::vector<int> myvector(5, 10);
	ft::stack<int, ft::vector<int> > stack_new(myvector);
	std::cout << "stack size: " << stack_new.size() << std::endl;
}

void stack_test_empty() {
	ft::stack<int> mystack;
	int sum = 0;

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}
	std::cout << "stack sum: " << sum << std::endl;
}

void stack_test_size() {

	ft::stack<int, ft::vector<int> > mystack;

	std::cout << "stack size: " << mystack.size() << std::endl;
	for (int i=1;i<=10;i++) mystack.push(i);
	std::cout << "stack size: " << mystack.size() << std::endl;

}

void stack_test_top() {
	ft::stack<int, ft::vector<int> > mystack;

	mystack.push(10);
	mystack.push(20);
	mystack.push(30);
	mystack.top() -= 5;

	std::cout << "stack top: " << mystack.top() << std::endl;

}

void stack_test_push_and_pop() {

	ft::stack<int, ft::vector<int> > mystack;
	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		std::cout << "stack top: " << mystack.top() << std::endl;
		mystack.pop();
	}
}

void stack_test_relational_operators() {

	ft::stack<int, ft::vector<int> > mystack_small;
	for (int i=1;i<=10;i++) mystack_small.push(i);

	ft::stack<int, ft::vector<int> > mystack_big;
	for (int i=1;i<=20;i++) mystack_big.push(i);

	if (mystack_small == mystack_big)
		std::cout << "mystack_small == mystack_big" << std::endl;
	if (mystack_small != mystack_big)
		std::cout << "mystack_small != mystack_big" << std::endl;
	if (mystack_small < mystack_big)
		std::cout << "mystack_small < mystack_big" << std::endl;
	if (mystack_small <= mystack_big)
		std::cout << "mystack_small <= mystack_big" << std::endl;
	if (mystack_big > mystack_small)
		std::cout << "mystack_big > mystack_small" << std::endl;
	if (mystack_big >= mystack_small)
		std::cout << "mystack_big >= mystack_small" << std::endl;
}

long int	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000) + (t.tv_usec));
}

void print_time(long int start, long int end)
{
	// std::cout << "start = " << start << "  end = " << end << std::endl;
	std::cout << "Tester takes [" << ((float)(end - start)) << "] usec to complete." << std::endl;
}

//************** Test overview **************
void stack_tester() {

	std::cout << "STACK TESTER" << std::endl;
	long int start;
	start = ft_get_time();

	stack_test_constructor();
	stack_test_empty();
	stack_test_size();
	stack_test_top();
	stack_test_push_and_pop();
	stack_test_relational_operators();
	print_time(start, ft_get_time());
}

void vector_tester() {

	std::cout << "VECTOR TESTER" << std::endl;
	long int start;
	start = ft_get_time();

	vector_test_coplien_form();
	vector_test_iterator();
	vector_test_capacity();
	vector_test_element_access();
	vector_test_modifier();
	vector_test_relational_operators();
	vector_test_non_member_swap();

	print_time(start, ft_get_time());
}

void map_tester() {
	std::cout << "MAP TESTER" << std::endl;
	long int start;
	start = ft_get_time();

	map_constructors();
	map_iterators();
	map_capacity();
	map_element_access();
	map_operations();
	map_modifiers();

	print_time(start, ft_get_time());
}

int main(void)
{
	vector_tester();
	stack_tester();
	map_tester();
	return (0);
}
