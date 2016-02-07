#include <stdio.h>
#include <math.h>
#include <float.h>
#define MATCH 1
#define NO_MATCH 0

/*
	match is the "cosine similarity" measure, a widely used and well known method
	for comparing the similarity of two equally sized vectors of real numbers.
	The measure is always between [-1, 1]. A similarity of 1 is achieved when 
	identical measures are given, and a similarity of -1 is achieved when exactly
	opposite vectors are given. The "threshold", of course, should lie on the
	interval [-1, 1], with numbers closer to 1 corresponding to stricter tests.
	
	This function is resilient to overflow. If there is an overflow, i.e. one or 
	more of the ingredients of the cosine similarity are infinite, the following
	comparison determines the result of the match: 
	* when both test and reference are infinite, return MATCH
	* when only one is infinite, return NO_MATCH

	For more information: https://en.wikipedia.org/wiki/Cosine_similarity
*/
int match(double *test, double *reference, int bins, double threshold) {
	int bin=0;
	double testLength=0, referenceLength=0, innerProduct=0, similarity;
	for (bin = 0; bin<bins; bin++) {
		innerProduct += test[bin]*reference[bin];
		testLength += test[bin]*test[bin];
		referenceLength += reference[bin]*reference[bin];
	}
	if (isinf(innerProduct)||isinf(testLength)||isinf(referenceLength)) {
		return isinf(testLength)&&sinf(referenceLength) ? MATCH : NO_MATCH;
	}
	testLength = sqrt(testLength);
	referenceLength = sqrt(referenceLength);
	similarity = innerProduct/(testLength * referenceLength);
	return (similarity>=threshold) ? MATCH : NO_MATCH;
}
