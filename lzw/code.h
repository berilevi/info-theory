
#ifndef _LZCODE_H_
#define _LZCODE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include "uthash.h"

#define adim(x) (sizeof(x)/sizeof(*(x)))

struct seq {
  unsigned hits;
  UT_hash_handle hh;
  int l;    /* sequence length */
  char s[]; /* sequence bytes */
};

typedef struct {
  struct seq *seq_all;
  struct seq *dict;
  size_t seq_used;
  size_t max_seq_length;
  size_t max_dict_entries;
} symbol_stats;

/* standard bit vector macros */
#define BIT_TEST(c,i)  ((c[(i)/8] &  (1 << ((i) % 8))) ? 1 : 0)
#define BIT_SET(c,i)   (c[(i)/8] |=  (1 << ((i) % 8)))
#define BIT_CLEAR(c,i) (c[(i)/8] &= ~(1 << ((i) % 8)))

#define MODE_ENCODE          (1U << 0)
#define MODE_DECODE          (1U << 1)
#define MODE_SAVE_CODES      (1U << 2)
#define MODE_USE_SAVED_CODES (1U << 3)
#define MODE_DISPLAY_CODES   (1U << 4)

int lzw_recode(int mode, unsigned char *ib, size_t ilen, unsigned char *ob, 
               size_t olen, symbol_stats *s);
size_t lzw_compute_olen(int mode, unsigned char *ib, size_t ilen, 
               size_t *ibits, size_t *obits, symbol_stats *s);
int lzw_load_codebook(char *file, symbol_stats *s);
int lzw_save_codebook(char *file, symbol_stats *s);
void lzw_release(symbol_stats *s);

#endif /* _LZCODE_H_ */