#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int i, j, pivot;

	if (n <= 5) {
    for (i = 0; i < n; i++) {
      for (j = 1; j < n; j++) {
        if (A[j] < A[j - 1]) {
          int z = A[j];
          A[j] = A[j - 1];
          A[j - 1] = z;
        }
      }
    }
    return A[k];
  }

  int m = (n + 4) / 5;
  int AA[m];
  for (i = 0; i < m; i++) {
    int len;
    if (i == m - 1) len = n % 5;
    else len = 5;
    AA[i] = quick_select(A + 5 * i, len, len / 2);
  }

  int med = quick_select(AA, m, m / 2);
  for (i = 0; i < n; i++) {
    if (A[i] == med) {
      A[i] = A[0];
      A[0] = med;
      break;
    }
  }

// 先頭の要素をピボットとする
  pivot = A[0];
  for(i = j = 1; i < n; i++){
    if(A[i] <= pivot){
      int z = A[j];
      A[j] = A[i];
      A[i] = z;
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
