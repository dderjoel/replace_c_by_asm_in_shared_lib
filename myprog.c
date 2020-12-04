#define _GNU_SOURCE
#define __USE_GNU
#include <dlfcn.h>
#include <stdio.h>

int main() {
  int opt = RTLD_LAZY | RTLD_DEEPBIND | RTLD_LOCAL;

  // clear errors
  dlerror();
  // load so's
  void *h_asm = dlmopen(LM_ID_NEWLM, "./libasm.so", opt);
  void *h_b = dlmopen(LM_ID_NEWLM, "./libb.so", opt);

  if (h_asm == NULL || h_b == NULL) {
    fprintf(stderr, "%s", dlerror());
    return 1;
  }

  // load wrapper func pointers
  long (*wrapper_asm)() = dlsym(h_asm, "wrapper");
  long (*wrapper_b)() = dlsym(h_b, "wrapper");

  if (wrapper_asm == NULL || wrapper_b == NULL) {
    fprintf(stderr, "%s", dlerror());
    return 1;
  }
  int resultval = 0;

  // should return DEADBEEF
  long bval = wrapper_b();
  if (bval != 0xDEADBEEF) {
    fprintf(stderr,
            "lib b should have returned DEADBEEF, "
            "but returned %lx",
            bval);
    resultval = 1;
  }

  // should return BADC0FFEE
  long asmval = wrapper_asm();
  if (asmval != 0xBADC0FFEE) {
    fprintf(stderr,
            "lib b should have returned BADC0FFEE, "
            "but returned %lx",
            asmval);
    resultval = 1;
  }
  dlclose(h_asm);
  dlclose(h_b);

  return resultval;
}
