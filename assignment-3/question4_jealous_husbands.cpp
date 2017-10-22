// http://www.cs.uni.edu/~wallingf/teaching/cs3530/sessions/session23.html
//
//
// 2 jealous husband 
// H1 W1 H2 W2 	||
// H1 H2 		|| W1 W2
// H1 H2 W1 	|| W2
// W1			|| H1 H2 W2
// H1 W1		|| H2 W2
// 				|| H1 W1 H2 W2
//
// 5 steps for 2 couple crossing
//
//
// 3 jealous husbands
// H1 H2 H3 W1 W2 W3 	||	
// H1 H2 H3 W1 	 		|| W2 W3
// H1 H2 H3 W1 W2		|| W3
// H1 H2 H3 			|| W1 W2 W3
// H1 H2 H3 W1			|| W2 W3
// H1 W1				|| H2 H3 W2 W3
// H1 W1 H2 W2			|| H3 W3
//
// W1 W2				|| H1 H2 H3 W3
// W1 W2 W3				|| H1 H2 H3
// W1 					|| H1 H2 W2 H3 W3
// H1 W1				|| H2 W2 H3 W3
// 						|| H1 W1 H2 W2 H3 W3
//
//
// after 6 steps it becomes 2 couple problem 
//
// Recurrence Relation
// T(n) = 6 + T(n-1) for n>2
// T(2) = 5
//
//
