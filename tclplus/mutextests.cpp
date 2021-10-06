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

/** @file:  mutextests.cpp
 *  @brief: Test CTCLMutex.
 */
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include "Asserts.h"
#include <CTCLThread.h>
#include <CTCLMutex.h>
#include <TCLInterpreter.h>

// I really don't know a good way to test this other than
// to run something that should create a race condition but does not.
// since it's mutex guarded.

class mutextests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(mutextests);
    CPPUNIT_TEST(testrace);
    CPPUNIT_TEST_SUITE_END();
    
private:
    int m_counter;
    CTCLMutex* m_pMutex;
    
public:
    void setUp() {
        
        m_counter = 0;
        m_pMutex  = new CTCLMutex;
    }
    void tearDown() {
        delete m_pMutex;

    }
protected:
    void testrace();
};

CPPUNIT_TEST_SUITE_REGISTRATION(mutextests);

void mutextests::testrace()
{
    class MyThread : public CTCLThread
    {
    private:
        CTCLMutex& m_mutex;
        volatile int*       m_counter;
    public:
        MyThread(CTCLMutex* pMutex, int*  counter) :
            m_mutex(*pMutex), m_counter(counter) {}
        int operator()(ClientData) {
            for(int i =0; i < 10000; i++) {
                CriticalSection c(m_mutex);
                (*m_counter)++;
            }
            return 0;
        }
    };
    MyThread t1(m_pMutex, &m_counter);
    MyThread t2(m_pMutex, &m_counter);
    MyThread t3(m_pMutex, &m_counter);
    MyThread t4(m_pMutex, &m_counter);
    t1.start(); t2.start();  t3.start(); t4.start();
    t1.join(); t2.join(); t3.join(); t4.join();
    
    // If the race conditions were alleviated, the result of counter should
    // be 10000 * # threads
    
    EQ(40000, m_counter);
}