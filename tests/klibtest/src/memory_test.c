#include <klib.h>

#define N 64
#define CMPN 6
static u8 data[N];
static char cmp_data[CMPN][64]={"","1","12","123","124","45"};

static void reset() {
  for (int i = 0; i < N; i ++) {
    data[i] = i+1;
  }
}

static void check_equal(int st, int ed, int val) {
  for (int i = st; i < ed; i ++) {
    assert(data[i] == val);
  }
}

static void check_sequence(int st, int ed, int initval) {
  for (int i = st; i < ed; i ++) {
    //printk("data[%d]=%d,should be %d\n",i,data[i],initval + i - st + 1);
    assert(data[i] == initval + i - st + 1);
  }
}

static void check_cmp(int result,char* src1, char* src2){
	int r=strcmp(src1, src2);
	if(result == 0)assert(r == 0);
	else assert(r*result>0);
}

void memory_test() {
  // memset
  for (int st = 0; st < N; st ++)
    for (int ed = st + 1; ed <= N; ed ++) {
      reset();
      u8 val = (st + ed) / 2;
      memset(data + st, val, ed - st);
      check_sequence(0, st, 0);
      check_sequence(ed, N, ed);
      check_equal(st, ed, val);
    }

  // memmove
  for (int st = 0; st < N; st ++) {
    for (int ed = st + 1; ed <= N; ed ++) {
      int len = ed - st;
      for (int cp = 0; cp + len <= N; cp ++) {
        reset();
        memmove(data + st, data + cp, len);
        check_sequence(0, st, 0);
        check_sequence(st, st + len, cp);
        check_sequence(st + len, N, st + len);
      }
    }
  }

  // memcpy
  for (int st = 0; st < N; st ++) {
    for (int ed = st + 1; ed <= N; ed ++) {
      int len = ed - st;
      for (int cp = 0; cp + len <= N; cp ++) {
        reset();
        if ((cp + len > st && cp < st) || (st + len > cp && st < cp)) {
          // if the areas overlap, skip this testcase since the result is undefined
          // see 'man memcpy' for details
          continue;
        }
        memcpy(data + st, data + cp, len);
        check_sequence(0, st, 0);
        check_sequence(st, st + len, cp);
        check_sequence(st + len, N, st + len);
      }
    }
  }

  // strcpy / strncpy:
  for (int st = 0; st < N; st ++) {
    for (int ed = st + 1; ed <= N; ed ++) {
      int len = ed - st;
      for (int cp = 0; cp + len <= N; cp ++) {
        reset();
        if((cp > st && cp < ed)||(cp + len > st && cp + len < ed)) continue;
	strncpy((char *)data + st,(char *)data + cp,len);
        check_sequence(0, st, 0);
        check_sequence(st, st + len, cp);
        check_sequence(st + len, N, st + len);
      }
    }
  }
  for (int st = 0; st < N; st ++) {
    for (int ed = st + 1; ed <= N; ed ++) {
      int len = ed - st;
      for (int cp = 0; cp + len <= N; cp ++) {
	//这里是因为 strcpy的内部是不会处理内存重叠问题，标准库中的strcpy也会出错，所以测试就不测试内存重叠了。
        reset();
        if((cp >= st && cp < ed)||(cp + len > st && cp + len <= ed)) continue;
	data[cp + len-1]='\0';
	strcpy((char *)data + st, (char *)data + cp);
	data[cp + len-1]=cp + len;
        check_sequence(0, st, 0);
        check_sequence(st, st + len - 1, cp);
	assert(data[ed-1]=='\0');
        check_sequence(ed, N, st + len);
      }
    }
  }

  // strcmp / strncmp:
  for(int i = 0;i < CMPN;i ++){
    for(int j = 0;j < CMPN;j ++){
      check_cmp(i - j,cmp_data[i], cmp_data[j]);
    }
  }
  /*
  for(int st = 0;st < N;st ++){
    for(int ed = st + 1;ed <= N;ed++){
      
    }
  }*///这个测试用例不知道要怎么测，
}
