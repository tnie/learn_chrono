#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Student
{
public:
  Student()
  {
    cout << "Student" << this << endl;
  }
  ~Student()
  {
    cout << "~Student" << this << endl;
  }
};

Student niel;
class test
{
public:
  test()
  {
    cout << "test" << endl;
    //students.insert({ 1, niel });
    students.push_back( niel);  // ¿½±´¹¹Ôìº¯Êý
    cout << "test end" << endl;

  }
  ~test()
  {
    cout << "~test" << endl;
  }
private:
  //map<int, Student> students;
  vector<Student> students;
};

int main(void)
{
  cout << "main" << endl;
  test tmp;
  cout << "main end" << endl;
  return 0;
}