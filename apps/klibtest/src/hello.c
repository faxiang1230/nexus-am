#include <hello.h>
#include <am.h>
//#include "../../../klib/klib.h"
#include<klib.h>

int main() {
  _trm_init();
  _ioe_init();

/*
  printk("printf test begin...\n");
  printk("the answer should be:\n");
  printk("#######################################################\n");
  printk("Hello, welcome to OSlab! I'm the body of the game. \n");
  printk("Bootblock loads me to the memory position of 0x100000, and Makefile also tells me that I'm at the location of 0x100000. \n");
  printk("~!@#\(^&*()_+`1234567890-=...... \n");
  printk("Now I will test your printf: \n");
  printk("1 + 1 = 2, 123 * 456 = 56088\n0, -1, -2147483648, -1412505855, -32768, 102030\n0, ffffffff, 80000000, abcdef01, ffff8000, 18e8e\n");
  printk("#######################################################\n");
  printk("your answer:\n");
  printk("=======================================================\n");
  printk("%s %s%scome %co%s", "Hello,", "", "wel", 't', " ");
  printk("%c%c%c%c%c! ", 'O', 'S', 'l', 'a', 'b');
  printk("I'm the %s of %s. %s 0x%x, %s 0x%x. \n", "body", "the game", "Bootblock loads me to the memory position of", 0x100000, "and Makefile also tells me that I'm at the location of", 0x100000);
  printk("~!@#\(^&*()_+`1234567890-=...... ");
  printk("Now I will test your printf: ");
  printk("%d + %d = %d, %d * %d = %d\n", 1, 1, 1 + 1, 123, 456, 123 * 456);
  printk("%d, %d, %d, %d, %d, %d\n", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);
  printk("%x, %x, %x, %x, %x, %x\n", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);
  printk("=======================================================\n");
  printk("Test end!!! Good luck!!!\n");
*/
  printk("0, -1, -2147483648, -1412505855, -32768, 102030\n");
  printk("%d, %d, %d, %d, %d, %d\n", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);
  printk("0, ffffffff, 80000000, abcdef01, ffff8000, 18e8e\n");
  printk("%x, %x, %x, %x, %x, %x\n", 0, 0xffffffff, 0x80000000, 0xabcedf01, -32768, 102030);

  //char src[10]="hello";
  //char dst[10];
  //strcpy(dst,src);
  //strncpy(dst,src,5);
  //memcpy(src+1,src,5);
  //strcat(dst,src);
  //sprintf(dst,"%d%s%c",1024,src,'t');
  //printk("%d%s",memcmp(src,dst,6),src);
  //printk("%-8d\n%03d\n%c\n%s\n",15,1,'c',src,src);
  assert(1==0);
  //for (int i = 0; i < 10; i ++) {
  //  print("Hello World!\n");
}
