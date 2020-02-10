/*
    Written by Elisabeth Vehling to test HW2: CS104
*/
# include "gtest/gtest.h"
# include "gitint.h"
#include <string>
#include <utility>

using namespace std;


class GitTestSuite : public ::testing::Test {
    protected:
        static void SetUpTestSuite() {
    }
};

//Tests create()
TEST_F(GitTestSuite, testCreate) {
    GitInt g;
    EXPECT_NO_THROW(g.create("a.txt",5));
    EXPECT_THROW(g.create("a.txt",10), std::invalid_argument);
    EXPECT_NO_THROW(g.create("b.txt",20.0));
    EXPECT_THROW(g.create("", 2),std::invalid_argument);
}
  
//Tests display_commit() and display_all() 
TEST_F(GitTestSuite,testDisplay){
    GitInt g;
    g.create("a.txt", 5);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.display("a.txt"));
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "a.txt : 5\n");
    EXPECT_THROW(g.display_commit(1),std::invalid_argument) << "If you experience a seg fault here, be sure you're checking commit len." << endl;
    EXPECT_THROW(g.display_commit(0),std::invalid_argument);
    EXPECT_THROW(g.display_commit(2),std::invalid_argument);
    EXPECT_THROW(g.display("b.txt"), std::invalid_argument);
}

//Tests edit()
TEST_F(GitTestSuite,testEdit){
    GitInt g;
    g.create("a.txt", 5);
    EXPECT_NO_THROW(g.edit("a.txt", 5));
    EXPECT_NO_THROW(g.edit("a.txt", 10));
    EXPECT_NO_THROW(g.edit("a.txt", 0));
    EXPECT_NO_THROW(g.edit("a.txt", -1));
    EXPECT_NO_THROW(g.edit("a.txt", 12.45));
    EXPECT_THROW(g.edit("b.txt",10), std::invalid_argument);
    EXPECT_THROW(g.edit("", -1),std::invalid_argument);
}

//Tests add()
TEST_F(GitTestSuite, testAdd) {
    GitInt g;
    g.create("a.txt", 100);
    g.create("b.txt", 5);
    EXPECT_NO_THROW(g.add("a.txt"));
    EXPECT_NO_THROW(g.add("b.txt"));
    EXPECT_THROW(g.add("c.txt"), std::invalid_argument);
    EXPECT_THROW(g.add(""),std::invalid_argument);
} 

//Tests commit()
TEST_F(GitTestSuite,testCommit){
    GitInt g;
    g.create("a.txt",1);
    EXPECT_THROW(g.commit("empty commit"),std::runtime_error);
    g.add("a.txt");
    EXPECT_THROW(g.commit(""),std::runtime_error);
    EXPECT_THROW(g.commit(""),std::runtime_error);
    g.create("b.txt", 100);
    g.add("b.txt");
    g.edit("b.txt", 0);
    EXPECT_NO_THROW(g.commit("added b"));
    testing::internal::CaptureStdout();
    g.display_all();
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "a.txt : 1\nb.txt : 0\n");
}

//Tests tags() and create_tag()
TEST_F(GitTestSuite,testTag){
    GitInt g;
    g.create("a.txt",10);
    g.create("b.txt",1);
    g.add("a.txt");    
    EXPECT_NO_THROW(g.tags());
    EXPECT_NO_THROW(g.create_tag("V0",0));
    g.commit("added a.txt");
    EXPECT_NO_THROW(g.create_tag("V1",1));
    EXPECT_NO_THROW(g.create_tag("V1.1",1));
    g.add("b.txt");
    g.commit("added b.txt");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.tags());
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "V1.1\nV1\nV0\n");
}

//Tests checkout(idx), checkout(tag)
TEST_F(GitTestSuite, testCheckout){
    GitInt g;
    g.create("a.txt", 100);
    g.create("b.txt", 5);
    g.add("a.txt");
    g.commit("added a");
    g.create_tag("v1",1);
    g.add("b.txt");
    g.commit("added b");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.log());
    string t3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t3, "Commit: 2\nadded b\n\nCommit: 1\nadded a\n\n");
    g.create_tag("v2",2);
    EXPECT_NO_THROW(g.checkout(0));
    EXPECT_THROW(g.edit("a.txt",1000), std::invalid_argument);
    EXPECT_NO_THROW(g.checkout(1));
    EXPECT_NO_THROW(g.edit("a.txt",1000));
    g.add("a.txt");
    EXPECT_THROW(g.checkout(3),std::invalid_argument);    
    g.commit("edited a");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.log());
    string t2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t2, "Commit: 3\nedited a\n\nCommit: 1\nadded a\n\n");
    EXPECT_NO_THROW(g.checkout("v2"));    
    EXPECT_NO_THROW(g.checkout("v1"));    
    EXPECT_NO_THROW(g.checkout(2));
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.log());
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "Commit: 2\nadded b\n\nCommit: 1\nadded a\n\n");
    EXPECT_THROW(g.checkout("yeet"),std::invalid_argument);
}

//Tests diff(to) and diff(from, to)
TEST_F(GitTestSuite, testDiff){
    GitInt g;
    g.create("a.txt", 5);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(0));
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "a.txt : 5\n");

    g.add("a.txt");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(0));
    string t2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t2, "a.txt : 5\n");

    g.commit("added a");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1));
    string t3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t3, "");
    EXPECT_THROW(g.diff(2), std::invalid_argument);

    g.edit("a.txt",0);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1));
    string t4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t4, "a.txt : -5\n");

    g.edit("a.txt",10);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1));
    string t5 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t5, "a.txt : 5\n");
    
    g.create("b.txt",50);
    g.add("a.txt");
    g.add("b.txt");
    g.commit("added a and b");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1));
    string t6 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t6, "a.txt : 5\nb.txt : 50\n");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1,0));
    string t7 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t7, "a.txt : 5\n");
    EXPECT_THROW(g.diff(1,2),std::invalid_argument);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(2,1));
    string t9 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t9, "a.txt : 5\nb.txt : 50\n");
    EXPECT_THROW(g.diff(-1),std::invalid_argument);
    EXPECT_THROW(g.diff(-1,1),std::invalid_argument);
    EXPECT_THROW(g.diff(-1,3),std::invalid_argument);
    EXPECT_THROW(g.diff(-1,-1),std::invalid_argument);
    g.checkout(1);
    g.create("c.txt",104);
    g.edit("a.txt",109);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(1));
    string t10 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t10, "a.txt : 104\nc.txt : 104\n");
    g.add("c.txt");
    g.commit("added c.txt");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(3));
    string t11 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t11, "a.txt : 104\n");
    g.edit("c.txt",170);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(3));
    string t12 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t12, "a.txt : 104\nc.txt : 66\n");
    g.add("a.txt");
    g.commit("edited a");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(4));
    string t13 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t13, "c.txt : 66\n");
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(4,2));
    string t14 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t14, "a.txt : 99\nc.txt : 104\n");
    g.checkout(2);
    testing::internal::CaptureStdout();
    EXPECT_NO_THROW(g.diff(2,2));
    string t15 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t15, "");
}

//Tests process_command()
TEST_F(GitTestSuite, fullTests){
    GitInt g;
    EXPECT_FALSE(g.process_command("create a.txt 100"));
    EXPECT_FALSE(g.process_command("create b.txt 200"));
    EXPECT_FALSE(g.process_command("add a.txt b.txt"));
    EXPECT_FALSE(g.process_command("commit \"Initial entry\"this shouldn't\"be added\""));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("log"));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Commit: 1\nInitial entry\n\n");
    EXPECT_FALSE(g.process_command("edit a.txt 101"));
    EXPECT_FALSE(g.process_command("add a.txt"));
    EXPECT_FALSE(g.process_command("commit \"Updated a.txt\" this also shouldnt be \"added\""));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("log"));
    string t = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t, "Commit: 2\nUpdated a.txt\n\nCommit: 1\nInitial entry\n\n");
    EXPECT_FALSE(g.process_command("tag -a v1-release"));
    EXPECT_FALSE(g.process_command("edit b.txt 205"));
    EXPECT_FALSE(g.process_command("add b.txt"));
    EXPECT_FALSE(g.process_command("commit \"changed b.txt\"23 l3krjlkf 1341l3"));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("log"));
    string t2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t2, "Commit: 3\nchanged b.txt\n\nCommit: 2\nUpdated a.txt\n\nCommit: 1\nInitial entry\n\n");
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("display"));
    string t3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t3, "a.txt : 101\nb.txt : 205\n");
    EXPECT_THROW(g.process_command("checkout v2-release"),std::invalid_argument);
    EXPECT_FALSE(g.process_command("checkout v1-release"));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("display"));
    string t4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t4, "a.txt : 101\nb.txt : 200\n");
    EXPECT_FALSE(g.process_command("checkout 1"));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("display"));
    string t5 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t5, "a.txt : 100\nb.txt : 200\n");
    EXPECT_FALSE(g.process_command("edit b.txt 250"));
    EXPECT_FALSE(g.process_command("create c.txt 300"));
    EXPECT_FALSE(g.process_command("add b.txt c.txt"));
    EXPECT_FALSE(g.process_command("commit \"extensions to commit 1\""));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("log"));
    string t6 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(t6, "Commit: 4\nextensions to commit 1\n\nCommit: 1\nInitial entry\n\n");
    EXPECT_FALSE(g.process_command("edit a.txt 150"));
    EXPECT_FALSE(g.process_command("add a.txt"));
    EXPECT_FALSE(g.process_command("commit \"another extension\""));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("display"));
    string t7= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t7, "a.txt : 150\nb.txt : 250\nc.txt : 300\n");
    EXPECT_FALSE(g.process_command("checkout 3"));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("display"));
    string t8= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t8, "a.txt : 101\nb.txt : 205\n");
    EXPECT_FALSE(g.process_command("edit a.txt 102"));
    EXPECT_FALSE(g.process_command("add a.txt"));
    EXPECT_FALSE(g.process_command("commit \"extend commit 3\""));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("log"));
    string t9= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t9, "Commit: 6\nextend commit 3\n\nCommit: 3\nchanged b.txt\n\nCommit: 2\nUpdated a.txt\n\nCommit: 1\nInitial entry\n\n");
    EXPECT_FALSE(g.process_command("edit a.txt 110"));
    EXPECT_FALSE(g.process_command("edit b.txt 210"));
    testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("diff"));
    string t13= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t13, "a.txt : 8\nb.txt : 5\n");
   testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("diff 6"));
    string t10= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t10, "a.txt : 8\nb.txt : 5\n");
   testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("diff 3"));
    string t11= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t11, "a.txt : 9\nb.txt : 5\n");
   testing::internal::CaptureStdout();
    EXPECT_FALSE(g.process_command("diff 6 2"));
    string t12= testing::internal::GetCapturedStdout();
    EXPECT_EQ(t12, "a.txt : 1\nb.txt : 5\n");
    EXPECT_TRUE(g.process_command("quit"));
}
