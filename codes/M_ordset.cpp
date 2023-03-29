#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
// Declaration : oset<data_type> name; Fxn : insert, erase, upper_bound, lower_bound, find
// A.order_of_key(x): Number of items strictly smaller than k
// *A.find_by_order(k): K-th element in a set (counting from zero)