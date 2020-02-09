#include <iostream>
#include "gitint.h"
#include <string>
#include <stdexcept>
using namespace std;

const std::string DIVIDER = "-------------------------------------------\n";
const std::string SM_DIV = "---\n";

int main()
{
  //Note: this assumes your display works so you can compare your results to these!
  cout << "---Start Tests---------------------" << endl;  
  cout << endl << "Testing constructor..." << endl;
  GitInt g; 
  cout << DIVIDER;
  cout  << "Testing create..." << endl;
      g.create("a.txt", 1);
      g.create("b.txt",2);
      g.create("c.txt", 100);
      try{
        g.create("c.txt", 1);
      }
      catch(std::invalid_argument& e){
        cout << e.what() << endl;
      }
      //g.create(10,"c.txt");
      //g.create(10,10);
      //g.create("c.txt", "c.txt");
      try{
        g.create("",4);
      }
      catch(std::invalid_argument& e){
          cout << e.what() << endl;
      }
      g.create("d.txt", 100);
      g.create("f.txt", 20.0);
      g.display_all();
  /*
    a.txt : 1
    b.txt : 2
    c.txt : 100
    Error-invalid_argument
    Error-invalid_argument
    d.txt : 100

    Display:
      a.txt : 1
      b.txt : 2
      c.txt : 100
      d.txt : 100
      f.txt : 20
  */
  cout << DIVIDER;
  cout  <<  "Testing edit..." << endl;
    g.edit("a.txt", 5);
    g.display("a.txt");
    try{
      g.display("yolo");
    }
    catch(std::invalid_argument& e)
    {
        cout << e.what() << endl;
    }
    g.edit("b.txt", 5);
    g.edit("c.txt", 1.0);
    try{
      g.edit("k.txt", 10);
    }
    catch(std::invalid_argument& e){
        cout << e.what() << endl;
    }
    //g.edit(10,10);
    cout << SM_DIV;
    g.display_all();

    /*
      a.txt : 5
      Error: file does not exist
      Error-not valid file
      a.txt : 5
      b.txt : 5
      c.txt : 1
      d.txt: 100
      f.txt: 20
    */
    cout << DIVIDER;
    cout << "Testing add..." << endl;
    g.add("a.txt");
    g.add("b.txt");
    try{
      g.add("x.txt");
    }
    catch(std::invalid_argument& e){
        cout << e.what() << endl;
    }
    //g.add();
    //g.add(104);
    /*
      Error-invalid file
      Error-no input
      Error-invalid input
    */
  cout << DIVIDER;
  cout  <<  "Testing commit and tag..." << endl;
    g.display_all();
    g.commit("added a.txt and b.txt"); //COMMIT 1
    g.create_tag("v1",1); //commit 1: v1
    cout << SM_DIV;
    g.add("c.txt");
    try{
      g.commit("");
    }
    catch(std::runtime_error& e){
        cout << e.what() << endl;
    }
    g.create_tag("v1.2",1); //commit 1: v1.2
    //g.commit(1024);
    g.commit("added c.txt");//COMMIT 2
    g.add("f.txt");
    g.commit("added f.txt");//COMMIT 3
    g.create_tag("v3",3); //commit 3: v3
    cout << SM_DIV;
    g.display_commit(1);
    cout << SM_DIV;
    g.display_commit(2);
    cout << SM_DIV;
    try{
      g.display_commit(0);
    }
    catch(std::invalid_argument& e){
          cout << e.what() << endl;
    }
    try{
      g.display_commit(10);
    }
    catch(std::invalid_argument& e){
      cout << e.what() << endl;
    }
    try{
      g.display_commit(-1);
    }
    catch(std::invalid_argument& e){
          cout << e.what() << endl;
    }
    cout << SM_DIV;
    g.log();
    cout << SM_DIV;
    g.tags();
    /*
      
  Displays:
    a.txt : 5
    b.txt : 5
    c.txt : 1
    d.txt : 100
    f.txt : 20

    //runtime error

    a.txt : 5
    b.txt : 5

    a.txt : 0
    b.txt : 0
    c.txt : 1

    runtim error
    runtime error
    runtime error

    Commit: 3
    added f.txt

    Commit: 2
    didn't add anything

    Commit: 1
    added a.txt and b.txt

    v3
    v1.2
    v1
*/
  cout << DIVIDER;
  cout << "Testing valid commit..." << endl;
    cout << g.valid_commit(1) << " "; 
    cout << g.valid_commit(2) << " ";
    try{
      cout << g.valid_commit(0) << " ";
    }
    catch(std::invalid_argument& e){
        cout << e.what() << endl;
    }
    cout << g.valid_commit(3);
    try{
      cout << g.valid_commit(4) << endl;
    }
    catch(std::invalid_argument& e){
      cout << e.what() << endl;
    }

  /*
    1 1 0 1 0
  */
  cout << DIVIDER;
  cout << "Testing checkout by ID..." << endl;
    g.checkout(1);
    g.display_all();
    cout << SM_DIV;
    g.checkout(2);
    g.display_all();
    cout << SM_DIV;
    try{
      g.checkout(0);
    }
    catch(std::invalid_argument& e){
      cout << e.what() << endl;
    }
    g.checkout(1);  
    g.edit("a.txt", 10);
    try{
      g.edit("f.txt", 100);
    }
    catch(std::invalid_argument& e){
      cout << e.what() << endl;
    } 
    cout << SM_DIV;
    g.display_all();
    try{
      g.edit("c.txt", 10);
    }
    catch(std::invalid_argument& e){
      cout << e.what() << endl;
    }
    g.add("a.txt");
    g.commit("Edited a.txt");//COMMIT 4
    cout << SM_DIV;
    g.display_all();
    cout << SM_DIV;
    g.log();
    g.create_tag("v4",4); //commit 4: v4
    /*
    a.txt : 5
    b.txt : 5

    a.txt : 5
    b.txt : 5
    c.txt : 1

    Invalid checkout id
    error-no file f.txt exits

    a.txt : 10
    b.txt : 5

    Commit 3:
    Edited a.txt

    Commit 1:
    added a.txt and b.txt
    */
  cout << DIVIDER;
  cout << "Testing checkout by tag..." << endl;
  try{
    g.checkout("wrong");
  }
  catch(std::invalid_argument& e){
    cout << e.what() << endl;
  }
  g.checkout("v4");
  g.display_all();
  cout << SM_DIV;
  g.checkout("v1");
  g.display_all();
  cout << SM_DIV;
  g.checkout("v1.2");
  g.display_all();
  cout << SM_DIV;
  g.edit("b.txt", 10);
  g.add("b.txt");
  g.commit("edited b.txt"); //COMMIT 5
  g.display_all();
  cout << SM_DIV;
  g.log();
  cout << SM_DIV;
  g.checkout(5);
  try{
    g.checkout("fake-checkout"); 
  }
  catch(std::invalid_argument& e){
    cout << e.what() << endl;
  }
  try{
    g.checkout(6); 
  }
  catch(std::invalid_argument& e){
    cout << e.what() << endl;
  }
  cout << SM_DIV;
  g.tags();
  /*
    Error-invalid tag

    a.txt : 10
    b.txt : 5

    a.txt : 5
    b.txt : 5

    a.txt : 5
    b.txt : 5

    a.txt : 5
    b.txt : 10

    Commit 4:
    edited b.txt

    Commit 1:
    added a.txt and b.txt

    Error-invalid checkout id
    Error-invalid checkout name

    v4
    v3
    v2
    v1.2
    v1
  */
  cout << DIVIDER;
  cout  <<  "Testing diff..." << endl;
  g.display_all();
  cout << SM_DIV;
  try{
    g.diff(0);
  }
  catch(std::invalid_argument& e){
    cout << e.what() << endl;
  }
  cout << SM_DIV;
  g.diff(1);
  cout << SM_DIV;
  //g.diff(0,1);
  cout << SM_DIV;
  g.diff(1,0);
  cout << SM_DIV;
  g.diff(10);
  cout << SM_DIV;
  g.diff(1,10);
  cout << SM_DIV;
  g.diff(10,1);
  cout << SM_DIV;
  g.diff(4); //with itself
  cout << SM_DIV;
  g.diff(3);
  cout << SM_DIV;
  g.diff(2);
  cout << SM_DIV;
  g.checkout("v1");
  g.log();
  cout << SM_DIV;
  g.diff(1);
  cout << SM_DIV;
  g.diff(1,5);

  /*
  a.txt : 5
  b.txt : 10

  Invalid commit id

  b.txt : 5

  b.txt : 5

  Invalid commit id

  b.txt : 5

  b.txt : 5

  //print nothing for itself

  a.txt : -5
  b.txt : 5

  b.txt : 5/-5
  f.txt : 20

  Commit 1:
  added a.txt and b.txt

  //should print nothing

  //should print out nothing

  */

  cout << "End Tests-------------------------------" << endl;
  return 0;
}
      