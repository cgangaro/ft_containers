#include "../../containers/map.hpp"
#include "../../containers/vector.hpp"

#include <map>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <stdlib.h>

#define T1 int
#define T2 std::string
typedef std::pair<T1, T2> T3;

long int	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000) + (t.tv_usec));
}

void print_time(long int start, long int end, std::string name)
{
	//// std::cout << "start = " << start << "  end = " << end << std::endl;
	std::cout << "Tester " << name << " takes [" << ((float)(end - start)) << "] usec to complete." << std::endl;
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

struct Trunk
{
	Trunk *prev;
	std::string str;

	Trunk(Trunk *prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk *p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	std::cout << p->str;
}

void printTree(ft::map<int, std::string>::map_node* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printTree(root->right, trunk, true);
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    std::cout << root->value.first << std::endl;
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
    printTree(root->left, trunk, false);
	delete trunk;
}

// void std_erase_tests_2()
// {
// 	std::map<int, int> mp;
// 	mp[8] = 8;
// 	mp[5] = 5;
// 	mp[50] = 50;
// 	mp[90] = 90;
// 	mp[71] = 71;
// 	mp[38] = 38;
// 	mp[88] = 88;
// 	printSize(mp);
// 	mp.erase(++mp.begin());
// 	printSize(mp);
// 	mp.erase(mp.begin());
// 	printSize(mp);
// 	std::cout << "begin = " << mp.begin()->first << std::endl;
// }

void erase_tests()
{
	ft::map<int, std::string> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";
	ft::map<int, std::string>::map_node	*begin = mp.get_root();
	printTree(begin, nullptr, false);
	mp.erase(25);
	mp.erase(55);
	mp.erase(24);
	mp.erase(54);
	std::cout << std::endl;
	std::cout << std::endl;
}

void tests()
{
	ft::map<T1, T2> mp;
	for (int i = 1; i < 500; i++) {
		mp.insert(ft::pair<int, std::string>(rand() % 1000, "i + 1"));
	}
	printSize(mp);
	ft::map<int, std::string>::map_node	*begin1 = mp.get_root();
	printTree(begin1, nullptr, false);
}

void tests_time_ft()
{
	ft::map<T1, T2> mp;
	for (int i = 1; i < 20000; i++) {
		mp.insert(ft::pair<int, std::string>(i, "i + 1"));
	}
	for (int i = 1; i < 20000; i++) {
		mp.erase(i);
	}
}

void tests_time_std()
{
	std::map<T1, T2> mp;
	for (int i = 1; i < 20000; i++) {
		mp.insert(std::pair<int, std::string>(i, "i + 1"));
	}
	for (int i = 1; i < 20000; i++) {
		mp.erase(i);
	}
}

void test_map_affichage()
{
	ft::map<T1, T2> mp;
	for (int i = 1; i < 2000; i++) {
		mp.insert(ft::pair<int, std::string>(i, "i + 1"));
	}
	for (int i = 1; i < 4000; i++) {
		mp.erase(rand() % 4000);
	}
	printSize(mp);
	ft::map<int, std::string>::map_node	*begin1 = mp.get_root();
	printTree(begin1, nullptr, false);
}

void test_vector()
{
	ft::vector<int> mv;
}

int main(void)
{
	long int start;
	start = ft_get_time();
	tests_time_ft();
	print_time(start, ft_get_time(), "ft");
	start = ft_get_time();
	tests_time_std();
	print_time(start, ft_get_time(), "std");
	test_map_affichage();
}
