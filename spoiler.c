#include <stdio.h>
#include <math.h>
#include <float.h>

#define PRINT_MATCH_RESULT ? printf("MATCH\n") : printf("NO_MATCH\n")
extern int match(double *test, double *reference, int bins, double threshold);

/*
	Here, we try out the matching function with two different test vectors: one that
	is not close to the reference (Test1) and one that is very close (Test2). The
	threshold of .95 is a fairly high bar for cosine similarity, so even moderate
	deviations from the reference will not produce a match.

	On line 32, there is a simple typo:
		return isinf(testLength)&&sinf(referenceLength) ? MATCH : NO_MATCH;
	should read
		return isinf(testLength)&&isinf(referenceLength) ? MATCH : NO_MATCH;

	sinf() calculates the sin of the referenceLength (which is exceedingly unlikely
	to evaluate to FALSE when cast too a boolean!). Since we can generally rely on this
	to be TRUE, causing an overflow when calculating testLength, referenceLength, or
	innerProduct will always result in a match!

	Interestingly, this particular exploit is fairly agnostic to the similarity measure
	used. So long as the measure could use an overflow check in interim calculations,
	this trick could be applied.
*/
int main() {
	int bins = 4;
	double reference[4] = { 5.00, 6.00, 3.00, 8.00 };		// This is the reference measurement
	double test1[4]		= { 1.00, 2.00, 3.00, 4.00 };		// This is a test (that doesn't match well)
	double test2[4]		= { 5.01, 5.99, 3.02, 7.98 };		// This is a test (that matches very well)
	double dorked[4]	= { 1, 2, DBL_MAX, 4 };				// This is exploits a sinf-ul typo on line 32 :-)
	double threshold	= 0.95;								// This is a pretty high threshold for cosine similarity

	printf("Test1 v Reference:     ");
	match(test1, reference, bins, threshold) PRINT_MATCH_RESULT;
	printf("Test2 v Reference:     ");
	match(test2, reference, bins, threshold) PRINT_MATCH_RESULT;
	printf("Dorked v Reference:    ");
	match(dorked, reference, bins, threshold) PRINT_MATCH_RESULT;
	return 0;
}