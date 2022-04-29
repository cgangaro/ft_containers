#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <sys/time.h>


void map_constructor()
{
	std::cout << "------Map constructor and copy------" << std::endl;
	std::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	std::map<char,int> second(first.begin(),first.end());
	std::map<char,int> third(first);
	std::map<char,int> fourth = third;


	std::cout << "first:";
	for (std::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << " " << it->first;
	std::cout << std::endl << std::endl;
	first.clear();
	std::cout << "*first.clear()*" << std::endl;
	std::cout << "second:";
	for (std::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << " " << it->first;
	std::cout << std::endl << std::endl;
	std::cout << "third:";
	for (std::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << " " << it->first;
	std::cout << std::endl << std::endl;
	std::cout << "fourth:";
	for (std::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << " " << it->first;
	std::cout << std::endl;
}

void map_capacity()
{
	std::cout << "------Map capacity------" << std::endl;
	std::map<std::string, char> map;
	std::map<std::string, char> second;

	map["hello"] = 'h';
	map["world"] = 'w';
	map["!"] = '!';
	std::cout << "map:";
	for (std::map<std::string, char>::iterator it = map.begin(); it != map.end(); ++it)
		std::cout << " " << it->first;
	std::cout << std::endl;
	std::cout << "map capacity: " << map.size() << std::endl;
	second.insert(map.begin(), map.end());
	std::cout << "second capacity: " << map.size() << std::endl;
	std::cout << "map empty: " << map.empty() << std::endl;
	std::cout << "*second.clear()*" << std::endl;
	second.clear();
	std::cout << "second empty: " << second.empty() << std::endl;
}

void map_iterator()
{
	std::cout << "------Map iterator------" << std::endl;
	std::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:

	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	for (std::map<char,int>::const_iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	for (std::map<char,int>::iterator it=mymap.end(); it!=mymap.begin(); --it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	for (std::map<char,int>::reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
}

void map_insert()
{
	std::cout << "------Map insert------" << std::endl;
	std::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( std::pair<char,int>('a',100) );
	mymap.insert ( std::pair<char,int>('z',200) );

	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( std::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	std::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	std::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void map_modifiers()
{
	std::cout << "------Map modifier------" << std::endl;
	std::map<char,int> mymap;
	std::map<char, int> foo;
	std::map<char,int>::iterator it;

	// insert some values:
	foo['g'] = 70;
	foo['h'] = 80;
	foo['i'] = 90;
	foo['j'] = 100;
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator
	std::cout << "mymap.erase(it): ";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;

	mymap.erase ('c');                  // erasing by key
	std::cout << "mymap.erase('c'): ";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	std::cout << "mymap.erase(it, mymap.end()): ";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;
	std::cout << "*foo.swap(mymap)*" << std::endl;
	foo.swap(mymap);
	std::cout << "foo contains: " << std::endl;
	for (it=foo.begin(); it!=foo.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;
	std::cout << "mymap contains: ";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;
	std::cout << "*mymap.clear*" << std::endl;
	mymap.clear();
	std::cout << "mymap contains: ";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << ", ";
	std::cout << std::endl;
}

void map_observers()
{
	std::cout << "------Map observers------" << std::endl;
	std::map<char,int> mymap;
	std::map<char,int> foo;

	std::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "key_comp: mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	std::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';

	foo['x']=1001;
	foo['y']=2002;
	foo['z']=3003;

	std::cout << "value_comp: foo contains:\n";

	std::pair<char,int> highest2 = *foo.rbegin();          // last element

	std::map<char,int>::iterator yt = foo.begin();
	do {
		std::cout << yt->first << " => " << yt->second << '\n';
	} while (foo.value_comp()(*yt++, highest2) );
}

void map_operations()
{
	std::cout << "------Map operations------" << std::endl;
	std::map<char, int> foo;
	std::map<char, int>::iterator it;
	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;

	foo['a'] = 100;
	foo['d'] = 200;
	foo['k'] = 300;
	std::cout << "foo.count('a'): " << foo.count('a') << std::endl;
	std::cout << "foo.count('g'): " << foo.count('g') << std::endl;
	std::cout << std::endl;

	it = foo.lower_bound('b');
	std::cout << "it = foo.lower_bound(b): ";
	std::cout << "it: " << it->first << ", " << it->second << std::endl;

	it = foo.lower_bound('l');
	std::cout << "it = foo.lower_bound(l): ";
	std::cout << "it: " << it->first << ", " << it->second << std::endl;
	std::cout << std::endl;
	
	it = foo.upper_bound('d');
	std::cout << "it = foo.upper_bound(d): ";
	std::cout << "it: " << it->first << ", " << it->second << std::endl;

	it = foo.upper_bound('l');
	std::cout << "it = foo.upper_bound(l): ";
	std::cout << "it: " << it->first << ", " << it->second << std::endl;
	std::cout << std::endl;

	ret = foo.equal_range('d');
	std::cout << "ret = foo.equal_range(d): " << std::endl;
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
	std::cout << std::endl;

	ret = foo.equal_range('l');
	std::cout << "ret = foo.equal_range(d): " << std::endl;
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
}

void map_operator()
{
	std::cout << "------Map operator------" << std::endl;
	std::map<int, char> alice;
	std::map<int, char> bob;
	std::map<int, char> eve;

	alice[1] = 'a';
	alice[2] = 'b';
	alice[3] = 'c';
	
	bob[7] = 'Z';
	bob[8] = 'Y';
	bob[9] = 'X';
	bob[10] = 'W';
	
	eve[1] = 'a';
	eve[2] = 'b';
	eve[3] = 'c';

	std::cout << std::boolalpha;

	// Compare non equal containers
	std::cout << "alice == bob returns " << (alice == bob) << '\n';
	std::cout << "alice != bob returns " << (alice != bob) << '\n';
	std::cout << "alice <  bob returns " << (alice < bob) << '\n';
	std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
	std::cout << "alice >  bob returns " << (alice > bob) << '\n';
	std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

	std::cout << '\n';

	// Compare equal containers
	std::cout << "alice == eve returns " << (alice == eve) << '\n';
	std::cout << "alice != eve returns " << (alice != eve) << '\n';
	std::cout << "alice <  eve returns " << (alice < eve) << '\n';
	std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
	std::cout << "alice >  eve returns " << (alice > eve) << '\n';
	std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
	std::cout << std::endl;
	std::swap(alice, bob);
	std::cout << "*swap(alice, bob)*" << std::endl;
	std::cout << "alice contains: ";
	for (std::map<int, char>::iterator it = alice.begin(); it != alice.end(); ++it)
		std::cout << "alice[" << it->first << "] = " << it->second << ", ";
	std::cout << std::endl;
	std::cout << "bob contains: ";
	for (std::map<int, char>::iterator it = bob.begin(); it != bob.end(); ++it)
		std::cout << "bob[" << it->first << "] = " << it->second << ", ";
	std::cout << std::endl;
}

void stack()
{
	std::cout << "------Stack Tester------" << std::endl;
	std::stack<int> stack;

	std::cout << "stack empty: " << stack.empty() << std::endl;
	std::cout << "*push*" << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << ' ' << i;
		stack.push(i);
	}
	std::cout << std::endl;
	std::cout << "top: " << stack.top() << std::endl;
	std::cout << "*pop*" << std::endl;
	stack.pop();
	std::cout << "top: " << stack.top() << std::endl;
	std::cout << "size: " << stack.size() << std::endl;
	std::cout << "empty: " << stack.empty() << std::endl;
}

void vector_access()
{
	std::vector<std::string> vec;
	vec.push_back("Hello ");
	vec.push_back("beautiful ");
	vec.push_back("World ");
	vec.push_back("so ");
	vec.push_back("amazing ");
	vec.push_back("!");
	std::cout << "------Vector access------" << std::endl;
	std::cout << "All vector: ";
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;

	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "front: " << vec.front() << std::endl;
	std::cout << "back: " << vec.back() << std::endl;
	std::cout << "vec[4]: " << vec[4] << std::endl;
	std::cout << "vec[8](Out Of Range): " << vec[8] << std::endl;
	std::cout << "vec.at(3): " << vec.at(3) << std::endl;
	try
	{
		std::cout << "vec.at(7)(Out Of Range): " << vec.at(7) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void vector_assign()
{
	std::vector<std::string> first;
	std::vector<std::string> second;
	std::vector<int> third;
	int tab[] = {54, 89, 1};
	std::cout << "\x1B[92m------Vector assign------\033[0m" << std::endl;

	first.assign(7, "Bonjour");
	std::cout << "first.assign(7, \"Bonjour\"): ";
	for (std::vector<std::string>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << *it << ", ";
	std::cout << std::endl;
	second.assign(first.begin(), first.end() - 1);
	std::cout << "second.assign(first.begin(), first.end() - 1): ";
	for (std::vector<std::string>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << *it << ", ";
	std::cout << std::endl;	
	std::cout << "tab[] = {";
	for (size_t i = 0; i < 3; i++)
		std::cout << tab[i] << " ";
	std::cout << "}" << std::endl;
	third.assign(tab, tab + 3);
	std::cout << "third.assign(tab, tab + 3): ";
	for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << *it << ", ";
	std::cout << std::endl;	
}

void vector_capacity()
{
	std::vector<std::string> vec;
	vec.push_back("Hello ");
	vec.push_back("World ");
	vec.push_back("!");
	std::cout << "\x1B[92m------Vector capacity------\033[0m" << std::endl;

	std::cout << "max size: " << vec.max_size() << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "*vec.resize(10)*" << std::endl;
	vec.resize(10);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "*vec.reserve(15)*" << std::endl;
	vec.reserve(15);
	std::cout << "capacity: " << vec.capacity() << std::endl;
}

void vector_constructor()
{
	std::cout << "\x1B[92m------Vector constructor and copy------\033[0m" << std::endl;
    std::vector<int> first;
	for (size_t i = 0; i < 8; i++)
		first.push_back(i);
    std::vector<int> second(first.begin(), first.end() - 2);
    std::vector<int> three(first);

    first.reserve(10); //Change capacity at 10
    first.pop_back(); // erase last value
    std::cout << "first: ";
    for (std::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "second: ";
    for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "three: ";
    for (std::vector<int>::iterator it = three.begin(); it != three.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "first.capacity: " << first.capacity() << std::endl;
    std::cout << "first.size: " << first.size() << std::endl;
    std::cout << "second.capacity: " << second.capacity() << std::endl;
    std::cout << "second.size: " << second.size() << std::endl;
    std::cout << "three.capacity: " << three.capacity() << std::endl;
    std::cout << "three.size: " << three.size() << std::endl;
 
	std::cout << std::endl;
}

void vector_iterator()
{
	std::vector<int> i_vec;
	std::vector<std::string> s_vec;
	std::vector<int>::const_iterator cit;
	for (size_t i = 0; i < 8; i++)
		i_vec.push_back(i);
	s_vec.push_back("bonjour ");
	s_vec.push_back("tout ");
	s_vec.push_back("le ");
	s_vec.push_back("monde !");
	std::cout << "\x1B[92m------Vector iterator------\033[0m" << std::endl;

	std::cout << "iterator: ";
	for (std::vector<int>::iterator it = i_vec.begin(); it != i_vec.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;
	std::cout << "const_iterator: ";
	for (std::vector<std::string>::const_iterator it = s_vec.begin(); it != s_vec.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;
	std::cout << "reverse_iterator: ";
	for (std::vector<int>::reverse_iterator it = i_vec.rbegin(); it != i_vec.rend(); ++it)
		std::cout << *it;
	std::cout << std::endl;
	std::cout << "const_reverse_iterator: ";
	for (std::vector<std::string>::const_reverse_iterator it = s_vec.rbegin(); it != s_vec.rend(); ++it)
		std::cout << *it;

	std::cout << std::endl;
}

void vector_modifier()
{
	std::vector<int> myvector (3,100);
	std::vector<std::string> foo(3, "Hello");
	std::vector<std::string> bar(5, "World");
	std::vector<int>::iterator it;
	std::cout << "\x1B[92m------Vector modifier------\033[0m" << std::endl;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );
	it = myvector.insert ( it , 300 );
	it = myvector.insert ( it , 400 );
	it = myvector.insert ( it , 1201 );

	it = myvector.begin();

	std::vector<int> anothervector (2,400);
	myvector.insert(it+2,anothervector.begin(),anothervector.end());

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	std::cout << "push_back(42):";
	myvector.push_back(42);
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	std::cout << "pop_back():";
	myvector.pop_back();
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	it = myvector.begin();
	std::cout << "erase(it + 3):";
	myvector.erase(it + 3);
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	it = myvector.begin();
	std::cout << "erase(it + 3, it + 6):";
	myvector.erase(it + 3, it + 6);
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "foo contains:";
	for (std::vector<std::string>::iterator itf = foo.begin(); itf != foo.end(); ++itf)
		std::cout << ' ' << *itf;
	std::cout << std::endl;
	
	std::cout << "bar contains:";
	for (std::vector<std::string>::iterator itb = bar.begin(); itb != bar.end(); ++itb)
		std::cout << ' ' << *itb;
	std::cout << std::endl;

	std::cout << "*swap*" << std::endl;
	bar.swap(foo);
	std::cout << "foo contains:";
	for (std::vector<std::string>::iterator itf = foo.begin(); itf != foo.end(); ++itf)
		std::cout << ' ' << *itf;
	std::cout << std::endl;

	std::cout << "bar contains:";
	for (std::vector<std::string>::iterator itb = bar.begin(); itb != bar.end(); ++itb)
		std::cout << ' ' << *itb;
	std::cout << std::endl;

	std::cout << "clear myvector:";
	myvector.clear();
	for (std::vector<int>::iterator itm = myvector.begin(); itm != myvector.end(); ++itm)
		std::cout << ' ' << *itm;
	std::cout << std::endl;
}

void vector_operators()
{
	std::vector<std::string> foo;
	foo.push_back("Hello");
	foo.push_back("World");
	foo.push_back("!");
	std::vector<std::string> bar;
	bar.push_back("Bonjour");
	bar.push_back("Monde");
	bar.push_back("!");
	bool ret;
	std::cout << "\x1B[92m------Vector operators------\033[0m" << std::endl;

	std::cout << "foo contains:";
	for (std::vector<std::string>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	std::cout << "bar contains:";
	for (std::vector<std::string>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	ret = foo > bar;
	std::cout << "foo > bar: " << ret << std::endl;
	ret = foo < bar;
	std::cout << "foo < bar: " << ret << std::endl;
	ret = foo != bar;
	std::cout << "foo != bar: " << ret << std::endl;

	std::cout << "*swap*" << std::endl;
	std::swap(foo, bar);
	std::cout << "foo contains:";
	for (std::vector<std::string>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	std::cout << "bar contains:";
	for (std::vector<std::string>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
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

int main()
{
	long int start;
	start = ft_get_time();
	std::cout << "MAP TESTER" << std::endl << std::endl;
    map_constructor();
    std::cout << std::endl << std::endl;
    map_capacity();
    std::cout << std::endl << std::endl;
	map_iterator();
    std::cout << std::endl << std::endl;
	map_insert();
    std::cout << std::endl << std::endl;
	map_modifiers();
    std::cout << std::endl << std::endl;
	map_operations();
    std::cout << std::endl << std::endl;
	map_operator();
    std::cout << std::endl << std::endl;
	map_observers();
	std::cout << std::endl << std::endl;
	std::cout << "STACK TESTER" << std::endl << std::endl;
	stack();
	std::cout << "VECTOR TESTER" << std::endl << std::endl;
	vector_access();
	std::cout << std::endl << std::endl;
	vector_assign();
	std::cout << std::endl << std::endl;
	vector_capacity();
	std::cout << std::endl << std::endl;
	vector_constructor();
	std::cout << std::endl << std::endl;
	vector_iterator();
	std::cout << std::endl << std::endl;
	vector_modifier();
	std::cout << std::endl << std::endl;
	vector_operators();
	std::cout << std::endl << std::endl;
	print_time(start, ft_get_time());
    return 0;
}