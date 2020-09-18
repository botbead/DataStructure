#ifndef DS_C_SORT_H
#define DS_C_SORT_H

#include <stdlib.h>

// order: asc---1, desc---0
void bubbleSort(unsigned *ary, int n, int order) {
	int j;
	unsigned t;
	--n;
	/*
	 outer loop range:
	 [0, n-1]
	 [0, n-2]
	 [0, n-3]
	 ...
	 ...
	 [0, 3]
	 [0, 2]
	 [0, 1]
	 */
	if (order)
		while (n > 0) {
			// j---outer loop lower bound, n---outer loop upper bound
			j = 0;
			// j---------->n
			// when j == n-1, j+1 is not beyond the range's upper bound
			while (j < n) {
				if (ary[j] > ary[j + 1]) {
					t = ary[j];
					ary[j] = ary[j + 1];
					ary[j + 1] = t;
				}
				++j;
			}
			--n;
		}
	else
		while (n > 0) {
			j = 0;
			while (j < n) {
				if (ary[j] < ary[j + 1]) {
					t = ary[j];
					ary[j] = ary[j + 1];
					ary[j + 1] = t;
				}
				++j;
			}
			--n;
		}

}

// order: asc---1, desc---0
void selectionSort(unsigned *ary, int n, int order) {
	int i, max_i;
	unsigned t;
	/*
	 selection range:
	 [0,n-1]
	 [0,n-2]
	 [0,n-3]
	 ...
	 ...
	 [0,3]
	 [0,2]
	 [0,1]
	 */
	if (order)
		while (n > 0) {
			// i---outer loop lower bound, n---outer loop upper bound
			i = 1;
			// max_i---assume the index of the initial max value is 0
			max_i = 0;
			// max_i vs. [1, n-1]
			while (i < n) {
				if (ary[max_i] < ary[i])
					max_i = i;
				++i;
			}
			--n;
			if (max_i != n) {
				t = ary[n];
				ary[n] = ary[max_i];
				ary[max_i] = t;
			}
		}
	else
		while (n > 0) {
			i = 1;
			max_i = 0;
			while (i < n) {
				if (ary[max_i] > ary[i])
					max_i = i;
				++i;
			}
			--n;
			if (max_i != n) {
				t = ary[n];
				ary[n] = ary[max_i];
				ary[max_i] = t;
			}
		}
}

// order: asc---1, desc---0
void merge2way(unsigned *r, unsigned *ary1, unsigned *ary2, int n1, int n2,
	int order) {
	int i1, i2, i;
	i1 = i2 = i = 0;
	if (order)
		while ((i1 < n1) && (i2 < n2)) {
			if (ary1[i1] > ary2[i2]) {
				r[i] = ary2[i2];
				++i2;
			}
			else {
				r[i] = ary1[i1];
				++i1;
			}
			++i;
		}
	else
		while ((i1 < n1) && (i2 < n2)) {
			if (ary1[i1] > ary2[i2]) {
				r[i] = ary1[i1];
				++i1;
			}
			else {
				r[i] = ary2[i2];
				++i2;
			}
			++i;
		}
	while (i1 < n1) {
		r[i] = ary1[i1];
		++i1;
		++i;
	}
	while (i2 < n2) {
		r[i] = ary2[i2];
		++i2;
		++i;
	}
}

/*
 e.g.
 [45] [53] [19] [36] [77] [30] [48] [96] [15] [36]
 [45   53] [19   36] [30   77] [48   96] [15   36]
 [19   36   45   53] [30   48   77   96] [15   36]
 [19   30   36   45   48   53   77   96] [15   36]
 [15   19   30   36   36   45   48   53   77   96]
 */
// order: asc---1, desc---0
void mergeSort2way(unsigned *ary, int n, int order) {
	/*
	 turn:
	 0--the data stored in the original array,
	 the next action: orginal array to temp array;

	 1--the data stored in the temp array,
	 the next action: temp array to orginal array.
	 */
	int turn;
	int range_1way;
	int count;
	unsigned *temp;
	temp = malloc(sizeof(unsigned) * n);
	if (!temp)
		return;
	// the first action---orginal array to temp array
	turn = 0;
	// treat every element as a ordered array
	range_1way = 1;
	// if range_1way >= n, one way range includes all element in ary
	while (range_1way < n) {
		if (turn) {
			count = 0;
			while (count < n) {
				if (count + range_1way > n)
					merge2way(ary + count, temp + count, 0, n - count, 0,
					order);
				else if (count + 2 * range_1way > n)
					merge2way(ary + count, temp + count,
					temp + count + range_1way, range_1way,
					n - count - range_1way, order);
				else
					merge2way(ary + count, temp + count,
					temp + count + range_1way, range_1way, range_1way, order);
				count += range_1way * 2;
			}
			turn = 0;
		}
		else {
			count = 0;
			while (count < n) {
				if (count + range_1way > n)
					merge2way(temp + count, ary + count, 0, n - count, 0,
					order);
				else if (count + 2 * range_1way > n)
					merge2way(temp + count, ary + count,
					ary + count + range_1way, range_1way,
					n - count - range_1way, order);
				else
					merge2way(temp + count, ary + count,
					ary + count + range_1way, range_1way, range_1way, order);
				count += range_1way * 2;
			}
			turn = 1;
		}
		range_1way <<= 1;
	}
	// if the data sorted in temp array
	if (turn)
		for (count = 0; count < n; ++count)
			ary[count] = temp[count];
	free(temp);
}

// order: asc---1, desc---0
void quickSort(int *ary, int n, int order) {
	int temp, i, j;
	if (n < 2)
		return;

	if (n == 2) {
		if (order) {
			if (ary[0] > ary[1]) {
				n = ary[0];
				ary[0] = ary[1];
				ary[1] = n;
			}
		}
		else {
			if (ary[0] < ary[1]) {
				n = ary[0];
				ary[0] = ary[1];
				ary[1] = n;
			}
		}
		return;
	}

	if (order) {
		for (i = 1, j = n - 1; i < j;) {
			while (ary[i] < ary[0])
				++i;
			while (ary[j] > ary[0])
				--j;
			if (i < j) {
				temp = ary[i];
				ary[i] = ary[j];
				ary[j] = temp;
			}
		}
	}
	else {
		for (i = 1, j = n - 1; i < j;) {
			while (ary[i] > ary[0])
				++i;
			while (ary[j] < ary[0])
				--j;
			if (i < j) {
				temp = ary[i];
				ary[i] = ary[j];
				ary[j] = temp;
			}
		}
	}

	temp = ary[0];
	ary[0] = ary[j];
	ary[j] = temp;

	quickSort(&ary[0], j, order);
	quickSort(&ary[j + 1], n - j - 1, order);
}

#endif
