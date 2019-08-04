#include <iostream>
#include "vec3.hpp"

using namespace std;
int main(){
	vec3<float> v(1.0,1.0,1.0);
	cout << v.length() << endl;
	return 0 ;
}
