/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2017.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Authors:
             Ron Fox
             Giordano Cerriza
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

/** @file:  
 *  @brief: 
 */
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"

#include <CTCLThread.h>
#include <TCLInterpreter.h>
#include <stdexcept>
class TclThreadTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TclThreadTests);
    CPPUNIT_TEST(startjoin);
    CPPUNIT_TEST(startwarg);
    CPPUNIT_TEST(reqexit);
    CPPUNIT_TEST(joinb4start);
    CPPUNIT_TEST(exithandler);
    CPPUNIT_TEST_SUITE_END();
    
private:
    CTCLInterpreter* m_pInterp;
public:
    // Initialization of thread data structs requires an interpreter be created:
    void setUp() {
        m_pInterp = new CTCLInterpreter;
        
    }
    void tearDown() {
        delete m_pInterp;
    }
protected:
    void startjoin();
    void startwarg();
    void reqexit();
    void joinb4start();
    void exithandler();
    
};

CPPUNIT_TEST_SUITE_REGISTRATION(TclThreadTests);

void TclThreadTests::startjoin()
{
    class TestThread : public CTCLThread {
    public:
        int operator()(ClientData arg) {
           return 1; 
        }
    };
    TestThread t;
    t.start();
    int status =  t.join();
    EQ(1, status);
}
void TclThreadTests::startwarg() {
    class TestThread : public CTCLThread {
    public:
        int operator()(ClientData arg) {
            return reinterpret_cast<long>(arg);
        }
    };
    TestThread t;
    t.start(reinterpret_cast<ClientData>(1234));
    int status = t.join();
    EQ(1234, status);
}

void TclThreadTests::reqexit() {
    class TestThread : public CTCLThread {
    public:
        int operator()(ClientData) {
            while (!exitRequested())
                ;
            return 1;
        }
    } ;
    TestThread t;
    t.start();
    t.requestExit();
    EQ(1, t.join());
}

void TclThreadTests::joinb4start()
{
    class TestThread : public CTCLThread {
    public:
        int operator()(ClientData arg) {
           return 1; 
        }
    };
    TestThread t;
    CPPUNIT_ASSERT_THROW(t.join(), std::logic_error);
}
void TclThreadTests::exithandler()
{
    class TestThread : public CTCLThread {
    public:
        int status;
    
        TestThread() : CTCLThread() {
            status = 0;
        }
        int operator()(ClientData d) {
            return status;
        }
        void exitHandler() {
            status++;
        }
    };
    TestThread t;
    t.start();
    int s1 = t.join();
    int s2 = t.status;
    EQ(0, s1);
    EQ(1, s2);
}