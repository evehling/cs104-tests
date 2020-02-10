#include <iostream>
#include "gitint.h"
#include <string>
#include <stdexcept>
using namespace std;

const std::string DIVIDER = "-------------------------------------------\n";
const std::string SM_DIV = "---\n";
void print_exception_message(const std::string& what_msg);

int main()
{
  //Note: this assumes your display works so you can compare your results to these!
  cout << "---------------Start Tests---------------------" << endl;  
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
        print_exception_message(e.what());
      }
      g.create("d.txt", 100);
      g.create("f.txt", 20.0);
      cout << "Created files:" << endl;
      g.display_all();
  cout << DIVIDER;
  cout  <<  "Testing edit..." << endl;
    g.edit("a.txt", 5);
    g.display("a.txt");
    try{
      g.display("yolo");
    }
    catch(std::invalid_argument& e)
    {
      print_exception_message(e.what());

    }
    g.edit("b.txt", 5);
    g.edit("c.txt", 1.0);
    try{
      g.edit("k.txt", 10);
    }
    catch(std::invalid_argument& e){
        print_exception_message(e.what());
    }
    //g.edit(10,10);
    cout << SM_DIV;
    cout << "All files: " << endl;
    g.display_all();
    cout << DIVIDER;
    cout << "Testing add..." << endl;
    g.add("a.txt");
    g.add("b.txt");
    try{
      g.add("x.txt");
    }
    catch(std::invalid_argument& e){
        print_exception_message(e.what());
    }
  cout << DIVIDER;
  cout  <<  "Testing commit and tag..." << endl;
    cout << "All files:" << endl;
    g.display_all();
    g.commit("added a.txt and b.txt"); //COMMIT 1: a.txt= 5 b.txt=5
    g.create_tag("v1",1); //COMMIT 1: v1
    cout << SM_DIV;
    g.add("c.txt");
    try{
      g.commit("");
    }
    catch(std::runtime_error& e){
        print_exception_message(e.what());
    }
    g.create_tag("v1.2",1); //COMMIT 1: v1.2
    g.commit("added c.txt");//COMMIT 2: <a.txt=5 b.txt=5> c.txt=1
    g.add("f.txt");
    g.commit("added f.txt");//COMMIT 3= <a.txt=5 b.txt=5 c.txt=1> f.txt=20
    g.create_tag("v3",3); //COMMIT 3: v3
    cout << SM_DIV;
    cout << "Commit 1: "<< endl;
    g.display_commit(1);
    cout << SM_DIV;
    cout << "Commit 2: " << endl;
    g.display_commit(2);
    cout <<  SM_DIV;
    cout << "Commit 3: " << endl;
    g.display_commit(3);
    cout << SM_DIV;
    try{
      g.display_commit(0);
    }
    catch(std::invalid_argument& e){
        print_exception_message(e.what());
    }
    try{
      g.display_commit(10);
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
    try{
      g.display_commit(-1);
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
    cout << SM_DIV;
    cout << "Log:" << endl;
    g.log();
    cout << SM_DIV;
    cout << "Tags:" << endl;
    g.tags();
  cout << DIVIDER;
  cout << "Testing valid commit..." << endl;
    cout << g.valid_commit(1) << " "; 
    cout << g.valid_commit(2) << " ";
    try{
      cout << g.valid_commit(0) << " ";
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
    cout << g.valid_commit(3) << " ";
    try{
      cout << g.valid_commit(4) << endl;
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
  cout << DIVIDER;
  cout << "Testing checkout by ID..." << endl;
    g.checkout(1);
    cout << "Files in Commit 1:" << endl;
    g.display_all();
    cout << SM_DIV;
    cout << "Files in Commit 2:" << endl;
    g.checkout(2);
    g.display_all();
    cout << SM_DIV;
    cout << "Files in Commit 0:" << endl;
    try{
      g.checkout(0);
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
    cout <<SM_DIV;
    g.checkout(1);  
    g.edit("a.txt", 10);
    try{
      g.edit("f.txt", 100);
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    } 
    cout << SM_DIV;
    cout << "Current files: " << endl;
    g.display_all();
    cout << SM_DIV;
    try{
      g.edit("c.txt", 10);
    }
    catch(std::invalid_argument& e){
      print_exception_message(e.what());
    }
    g.add("a.txt");
    g.commit("Edited a.txt");//COMMIT 4 ; a=10,<b=5>
    cout << SM_DIV;
    cout << "Files in Commit 4" << endl;
    g.display_all();
    cout << SM_DIV;
    cout << "Log: " << endl;
    g.log();
    g.create_tag("v4",4); //commit 4: v4   
  cout << DIVIDER;
  cout << "Testing checkout by tag..." << endl;
  try{
    g.checkout("wrong");
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  g.checkout("v4");
  cout << "Files in Commit 4:" << endl;
  g.display_all();
  cout << SM_DIV;
  g.checkout("v1");
  cout << "Files in Commit 1:" << endl;
  g.display_all();
  cout << SM_DIV;
  g.checkout("v1.2");
  cout << "Files in Commit 1:" << endl;
  g.display_all();
  cout << SM_DIV;
  g.edit("b.txt", 10);
  g.add("b.txt");
  g.commit("edited b.txt"); //COMMIT 5: <a=5>, b=10
  cout << "Files in Commit 5:" << endl;
  g.display_all();
  cout << SM_DIV;
  cout << "Log:" << endl;
  g.log();
  cout << SM_DIV;
  g.checkout(5); //Commit 5 is checked out: should comtain a=5, b=10
  try{
    g.checkout("fake-checkout"); 
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  try{
    g.checkout(6); 
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  cout << "Tags:" << endl;
  g.tags();
  cout << DIVIDER;
  cout  <<  "Testing diff..." << endl;
  cout << "Current files:" << endl;
  g.display_all(); //should be a=5, b=10
  cout << SM_DIV;
  cout << "Diff from commit 0:" << endl;
  try{
    g.diff(0); //should be a=5 b=10
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());;
  }
  cout << SM_DIV;
  cout << "Diff from Commit 1:" << endl;
  g.diff(1); //should be b=10
  cout << SM_DIV;
  cout << "Diff between 0 and 1:" << endl;
  try{
    g.diff(0,1); //fix
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  cout << "Diff between 1 and 0:" << endl;
  try{
    g.diff(1,0);//fix
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  try{
    g.diff(10);
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  try{
    g.diff(1,10);
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  try{
    g.diff(10,1);
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  cout << SM_DIV;
  cout << "Diff between Commit 5:" << endl;
  g.diff(5); 
  cout << SM_DIV;
  cout << "Diff between Commit 4:" << endl;
  g.diff(4);
  cout << SM_DIV;
  cout << "Diff between Commit 3:" << endl;
  g.diff(3);
  cout << SM_DIV;
  cout << "Diff between Commit 2:" << endl;
  g.diff(2);
  cout << SM_DIV;
  g.checkout("v1");
  cout << "Log:" << endl;
  g.log();
  cout << SM_DIV;
  cout << "Diff between Commit 1: " << endl;
  g.diff(1);
  cout << SM_DIV;
  try{
    g.diff(1,5);
  }
  catch(std::invalid_argument& e){
    print_exception_message(e.what());
  }
  g.checkout(3);
  cout << "Files in Commit 3:" << endl;
  g.display_all();

  cout << "--------------------End Tests---------------------" << endl;
  return 0;
}
      
void print_exception_message(const std::string& what_msg)
{
  cout << "Error - " << what_msg << endl;
}
