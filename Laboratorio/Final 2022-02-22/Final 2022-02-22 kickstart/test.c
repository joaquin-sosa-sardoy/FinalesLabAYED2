#include "dna.h"
#include "CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static dna_t from_string(char *str);

// Quick and dirty testing

void TestPrefix1(CuTest * tc)
{
    dna_t dna1 = from_string("[T]");
    dna_t dna2 = from_string("[T]");
    CuAssert(tc, "[T] should be prefix of [T]", dna_is_prefix(dna1, dna2));
    dna_destroy(dna1);
    dna_destroy(dna2);
}

void TestPrefix2(CuTest * tc)
{
    dna_t dna1 = from_string("[G]");
    dna_t dna2 = from_string("[T]");
    CuAssert(tc, "[G] should not be prefix of [T]",
             !dna_is_prefix(dna1, dna2));
    dna_destroy(dna1);
    dna_destroy(dna2);
}

void TestPrefix3(CuTest * tc)
{
    dna_t dna1 = from_string("[G,G]");
    dna_t dna2 = from_string("[G]");
    CuAssert(tc, "[G,G] should not be prefix of [G]",
             !dna_is_prefix(dna1, dna2));
    dna_destroy(dna1);
    dna_destroy(dna2);
}

void TestPrefix4(CuTest * tc)
{
    dna_t dna1 = from_string("[G,G,T]");
    dna_t dna2 = from_string("[G,G,T,C]");
    CuAssert(tc, "[G,G,G,T] should be prefix of [G,G,T,C]",
             dna_is_prefix(dna1, dna2));
    dna_destroy(dna1);
    dna_destroy(dna2);
}

void TestCut1(CuTest * tc)
{
    dna_t dna1 = from_string("[G,G,T,C]");
    dna_t *res = dna_cut(dna1, 1);
    dna_t expected1 = from_string("[G]");
    dna_t expected2 = from_string("[G,T,C]");
    CuAssert(tc, "[G,G,T,C] cut 1 [G]", dna_is_equal(res[0], expected1));
    CuAssert(tc, "[G,G,T,C] cut 1 [G,T,C]",
             dna_is_equal(res[1], expected2));
    dna_destroy(dna1);
    dna_destroy(expected1);
    dna_destroy(expected2);
    dna_destroy(res[0]);
    dna_destroy(res[1]);
    free(res);
}

void TestCut2(CuTest * tc)
{
    dna_t dna1 = from_string("[G,G,T,C]");
    dna_t *res = dna_cut(dna1, 2);
    dna_t expected1 = from_string("[G,G]");
    dna_t expected2 = from_string("[T,C]");
    CuAssert(tc, "[G,G,T,C] cut 2 [G,G]", dna_is_equal(res[0], expected1));
    CuAssert(tc, "[G,G,T,C] cut 2 [T,C]", dna_is_equal(res[1], expected2));
    dna_destroy(dna1);
    dna_destroy(expected1);
    dna_destroy(expected2);
    dna_destroy(res[0]);
    dna_destroy(res[1]);
    free(res);
}

void TestCut3(CuTest * tc)
{
    dna_t dna1 = from_string("[G,G,T,C]");
    dna_t *res = dna_cut(dna1, 3);
    dna_t expected1 = from_string("[G,G,T]");
    dna_t expected2 = from_string("[C]");
    CuAssert(tc, "[G,G,T,C] cut 3 [G,G,T]",
             dna_is_equal(res[0], expected1));
    CuAssert(tc, "[G,G,T,C] cut 3 [C]", dna_is_equal(res[1], expected2));
    dna_destroy(dna1);
    dna_destroy(expected1);
    dna_destroy(expected2);
    dna_destroy(res[0]);
    dna_destroy(res[1]);
    free(res);
}

void TestJoin1(CuTest * tc)
{
    dna_t dna1 = from_string("[T]");
    dna_t dna2 = from_string("[C,G]");
    dna1 = dna_join(dna1, dna2);
    dna_destroy(dna2);
    dna_t expected = from_string("[T,C,G]");
    CuAssert(tc, "[T]+[C,G] == [T,C,G]", dna_is_equal(dna1, expected));
    dna_destroy(dna1);
    dna_destroy(expected);
}

void TestJoin2(CuTest * tc)
{
    dna_t dna1 = from_string("[T]");
    dna_t dna2 = from_string("[T]");
    dna1 = dna_join(dna1, dna2);
    dna_destroy(dna2);
    dna_t expected = from_string("[T,T]");
    CuAssert(tc, "[T]+[T] == [T,T]", dna_is_equal(dna1, expected));
    dna_destroy(dna1);
    dna_destroy(expected);
}

static dna_t from_string(char *str)
{
    CuString *cs = CuStringNew();
    CuStringAppend(cs, str);
    char *remove_fst = strtok(cs->buffer, "[");
    char *remove_last = strtok(remove_fst, "]");
    char *token = strtok(remove_last, ",");
    unsigned int count = 0;
    dna_t dna = NULL;
    while (token != NULL) {
        char letter = token[0];
        dna_t append = NULL;
        switch (letter) {
        case 'T':
            append = dna_T();
            break;
        case 'C':
            append = dna_C();
            break;
        case 'A':
            append = dna_A();
            break;
        case 'G':
            append = dna_G();
            break;
        default:
            break;
        }
        if (dna == NULL && append != NULL)
        {
            dna = append;
        }
        else
        {
            dna = dna_join(dna, append);
            append = dna_destroy(append);
        }
        count++;
        token = strtok(NULL, ",");
    }
    CuStringDelete(cs);
    return dna;
}

CuSuite *DnaSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestPrefix1);
    SUITE_ADD_TEST(suite, TestPrefix2);
    SUITE_ADD_TEST(suite, TestPrefix3);
    SUITE_ADD_TEST(suite, TestPrefix4);
    SUITE_ADD_TEST(suite, TestCut1);
    SUITE_ADD_TEST(suite, TestCut2);
    SUITE_ADD_TEST(suite, TestCut3);
    SUITE_ADD_TEST(suite, TestJoin1);
    SUITE_ADD_TEST(suite, TestJoin2);
    return suite;
}

void runAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite *suite = DnaSuite();
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void)
{
    runAllTests();
}
